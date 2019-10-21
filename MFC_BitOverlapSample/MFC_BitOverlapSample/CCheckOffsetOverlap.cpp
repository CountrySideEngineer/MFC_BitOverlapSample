#include "pch.h"
#include "CCheckOffsetOverlap.h"

/**
 *	デフォルトコンストラクタ
 */
CCheckOffsetOverlap::CCheckOffsetOverlap()
	: m_DataArray(NULL)
{}

/**
 *	デストラクタ
 */
CCheckOffsetOverlap::~CCheckOffsetOverlap()
{
	if (NULL != this->m_DataArray) {
		delete[] this->m_DataArray;
		this->m_DataArray = NULL;
	}
}

/**
 *	オフセット値の重複確認を実施する。
 *
 *	@param[in]	DataToCheck	確認対象のオフセット情報
 *	@return	データのオフセット情報に重複がなければTRUEを、重複があればFALSEを返す。
 */
BOOL CCheckOffsetOverlap::RunCheck(const CArray<CDataOffset>& DataToCheck)
{
	INT_PTR DataSize = this->GetDataSize(DataToCheck);
	this->AllocData(DataSize);
	BOOL bCheckResult = this->CheckOverlap(DataToCheck);

	return bCheckResult;
}

/**
 *	重複確認対象となるデータのサイズを取得する。
 *
 *	@param[in]	DataToCheck	確認対象のオフセット情報
 *	@return	重複確認対象となるデータのサイズ(ワード単位)
 */
INT_PTR CCheckOffsetOverlap::GetDataSize(const CArray<CDataOffset>& DataToCheck)
{
	INT_PTR MaxDataSize = 0;

	for (INT_PTR Index = 0; Index < DataToCheck.GetCount(); Index++) {
		CDataOffset DataItem = DataToCheck.GetAt(Index);
		INT_PTR DataSize = DataItem.GetDataOffset() +
			(DataItem.GetBitOffset() + DataItem.GetDataSize()) / 16;	//16:WORD型のビットサイズ
		if (MaxDataSize < DataSize) {
			MaxDataSize = DataSize;
		}
	}
	return (MaxDataSize + 1);
}

/**
 *	重複確認のために必要なデータ領域を確保する。
 *
 *	@param	DataSize	重複確認のために必要な領域のサイズ(ワード単位)
 */
void CCheckOffsetOverlap::AllocData(const INT_PTR DataSize)
{
	this->m_DataArray = new WORD[DataSize];
	for (INT_PTR Index = 0; Index < DataSize; Index++) {
		this->m_DataArray[Index] = 0;
	}
}

/**
 *	重複確認を実行する。
 *
 *	@param[in]	DataToCheck	重複確認対象のデータの配列
 *	@return	重複確認結果。
 *			重複がなければTRUEを、あればFALSEを返す。
 */
BOOL CCheckOffsetOverlap::CheckOverlap(const CArray<CDataOffset>& DataToCheck)
{
	BOOL CheckResult = FALSE;
	for (INT_PTR Index = 0; Index < DataToCheck.GetCount(); Index++) {
		CDataOffset DataToCheckItem = DataToCheck.GetAt(Index);
		CheckResult = this->CheckOverlap(DataToCheckItem);
		if (FALSE == CheckResult) {
			break;
		}
	}
	return CheckResult;
}

/**
 *	1つのオフセット情報に対して、データの重複を確認する。
 *
 *	@param[in]	DataToCheck	確認対象のデータ
 *	@return	重複確認結果。
 *			重複がなければTRUEを、あればFALSEを返す。
 */
BOOL CCheckOffsetOverlap::CheckOverlap(const CDataOffset& DataToCheck)
{
	DWORD BitData = CDataOffset::TypeBitMaskMap[DataToCheck.GetDataType()];
	if (CDataOffset::DataBitArray_32bit == BitData) {
		return this->CheckOverlap<DWORD>(DataToCheck);
	}
	else {
		return this->CheckOverlap<WORD>(DataToCheck);
	}
}

/**
 *	1つのオフセット情報に対して、データの重複の有無を確認する。
 *	データの重複がなかった場合は、データ重複確認のための領域を更新する。
 *
 *	@param[in]	DataToCheck	確認対象のデータ
 *	@return	重複確認結果。
 *			重複がなければTRUEを、あればFALSEを返す。
 */
template <typename T>
BOOL CCheckOffsetOverlap::CheckOverlap(const CDataOffset& DataToCheck)
{
	INT_PTR DataOffset = DataToCheck.GetDataOffset();
	T* Data = (T*)(&(this->m_DataArray[DataOffset]));
	INT_PTR BitOffset = DataToCheck.GetBitOffset();
	T BitArray = CDataOffset::TypeBitMaskMap[DataToCheck.GetDataType()];
	T BitData = BitArray << BitOffset;
	BOOL CheckResult = FALSE;
	if (0 == ((*Data) & BitData)) {
		CheckResult = TRUE;
	}
	else {
		CheckResult = FALSE;
	}
	*Data |= BitData;

	return CheckResult;
}