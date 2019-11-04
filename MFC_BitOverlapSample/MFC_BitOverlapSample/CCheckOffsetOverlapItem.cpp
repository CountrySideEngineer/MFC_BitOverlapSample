#include "pch.h"
#include "CCheckOffsetOverlapItem.h"

/**
 *	デフォルトコンストラクタ
 */
CCheckOffsetOverlapItem::CCheckOffsetOverlapItem()
	: m_OverlapDataIndex(0)
	, m_OverlapDataTargetIndex(0)
{}

/**
 *	ビットの重複を確認する。
 *
 *	@param[in]	DataToCheck	重複を確認するデータの一覧
 *	@return	重複が見つかった場合にはTRUEを、重複が見つからなかった場合にはFALSEを
 *			返す。
 */
BOOL CCheckOffsetOverlapItem::CheckOverlap(const CArray<CDataOffset>& DataToCheck)
{
	BOOL CheckResult = FALSE;
	for (INT_PTR Index = 0; Index < DataToCheck.GetCount(); Index++) {
		this->InitData();	//データ配列の初期化
		CDataOffset DataToCheckItem = DataToCheck.GetAt(Index);
		DWORD BitData = DataToCheckItem.GetBitMask();
		if (CDataOffset::DataBitArray_32bit == BitData) {
			this->SetBitData<DWORD>(&DataToCheckItem);
		}
		else {
			this->SetBitData<WORD>(&DataToCheckItem);
		}
		for (INT_PTR TargetIndex = Index + 1; TargetIndex < DataToCheck.GetCount(); TargetIndex++) {
			CDataOffset DataToCheckTarget = DataToCheck.GetAt(TargetIndex);
			DWORD BitDataTarget = DataToCheckTarget.GetBitMask();
			if (CDataOffset::DataBitArray_32bit == BitData) {
				CheckResult = this->CheckOverlap<DWORD>(&DataToCheckTarget);
			}
			else {
				CheckResult = this->CheckOverlap<WORD>(&DataToCheckTarget);
			}
			if (TRUE == CheckResult) {
				this->m_OverlapDataIndex = (Index + 1);
				this->m_OverlapDataTargetIndex = (TargetIndex + 1);
				/*
				 *	重複している範囲が見つかった場合には、即座に処理を抜ける。
				 */
				return CheckResult;
			}
		}
	}
	return CheckResult;
}

/**
 *	重複確認の対象となるデータのビット情報を、バッファにセットする。
 *
 *	@param	DataToCheck	重複確認対象となるデータ情報
 *	@return	データの設定が正常に完了した場合にはTRUEを、失敗した場合にはFALSEを返す。
 */
template <typename T>
BOOL CCheckOffsetOverlapItem::SetBitData(CDataOffset* DataToCheck)
{
	T* Data = NULL;
	T BitData = 0;
	this->GetBitData(DataToCheck, &Data, &BitData);
	*Data |= BitData;

	return TRUE;
}

/**
 *	指定されたデータの重複を確認する。
 *
 *	@param[in]	DataToCheckTarget	重複確認対象のデータ情報
 *	@return	オフセット範囲の重複が見つかった場合にはTRUEを、重複が見つからなかった場合には
 *			FALSEを返す。
 */
template <typename T>
BOOL CCheckOffsetOverlapItem::CheckOverlap(CDataOffset* DataToCheckTaget)
{
	T* Data = NULL;
	T BitData = 0;
	this->GetBitData(DataToCheckTaget, &Data, &BitData);
	if (0 == ((*Data) & BitData)) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

/**
 *	データ配列から、指定されたオフセット情報に対応するデータを取得する。
 *
 *	@param[in]	DataToCheckTarget	オフセット情報へのポインタ
 *	@param[in,out]	Data	オフセット情報が指定するバッファへのポインタ
 *	@param[out]	BitData	オフセット情報が示すビット配列
 */
template <typename T>
void CCheckOffsetOverlapItem::GetBitData(CDataOffset* DataToCheck, T** Data, T* BitData)
{
	INT_PTR DataOffset = DataToCheck->GetDataOffset();
	*Data = (T*)(&(this->m_DataArray[DataOffset]));
	INT_PTR BitOffset = DataToCheck->GetBitOffset();
	T BitArray = DataToCheck->GetBitMask();
	*BitData = BitArray << BitOffset;
}
