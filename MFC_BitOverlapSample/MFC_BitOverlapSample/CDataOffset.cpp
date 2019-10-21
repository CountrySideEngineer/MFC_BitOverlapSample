#include "pch.h"
#include "CDataOffset.h"
#include <regex>

CMap<INT_PTR, INT_PTR, UINT32, UINT32> CDataOffset::TypeBitArrayMap;
CMap<INT_PTR, INT_PTR, INT_PTR, INT_PTR> CDataOffset::TypeBitSizeMap;
CMap<INT_PTR, INT_PTR, INT_PTR, INT_PTR> CDataOffset::TypeDataSizeMap;
BOOL CDataOffset::IsInit = FALSE;

CDataOffset::CDataOffset()
	: m_DataType(CDATA_OFFSET_DATA_TYPE_BOOL)
	, m_DataName(_T(""))
	, m_DataSize(DataSize_01bit)
	, m_BitArray(DataBitArray_01bit)
	, m_DataOffset(0)
	, m_BitOffset(0)
{
	CDataOffset::InitMap();
}

/**
 *	データのサイズ、ビット配列を定義するマップを初期化する。
 */
void CDataOffset::InitMap()
{
	if (TRUE == CDataOffset::IsInit) {
		//初期化済み
		return;
	}

	TypeBitArrayMap.RemoveAll();
	TypeBitArrayMap.SetAt(CDATA_OFFSET_DATA_TYPE_BOOL, DataBitArray_01bit);
	TypeBitArrayMap.SetAt(CDATA_OFFSET_DATA_TYPE_BYTE, DataBitArray_08bit);
	TypeBitArrayMap.SetAt(CDATA_OFFSET_DATA_TYPE_WORD, DataBitArray_16bit);
	TypeBitArrayMap.SetAt(CDATA_OFFSET_DATA_TYPE_DWORD, DataBitArray_32bit);
	TypeBitArrayMap.SetAt(CDATA_OFFSET_DATA_TYPE_INT8, DataBitArray_08bit);
	TypeBitArrayMap.SetAt(CDATA_OFFSET_DATA_TYPE_INT16, DataBitArray_16bit);
	TypeBitArrayMap.SetAt(CDATA_OFFSET_DATA_TYPE_INT32, DataBitArray_32bit);
	TypeBitArrayMap.SetAt(CDATA_OFFSET_DATA_TYPE_UINT8, DataBitArray_08bit);
	TypeBitArrayMap.SetAt(CDATA_OFFSET_DATA_TYPE_UINT16, DataBitArray_16bit);
	TypeBitArrayMap.SetAt(CDATA_OFFSET_DATA_TYPE_UINT32, DataBitArray_32bit);

	TypeBitSizeMap.RemoveAll();
	TypeBitSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_BOOL, DataSize_01bit);
	TypeBitSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_BYTE, DataSize_08bit);
	TypeBitSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_WORD, DataSize_16bit);
	TypeBitSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_DWORD, DataSize_32bit);
	TypeBitSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_INT8, DataSize_08bit);
	TypeBitSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_INT16, DataSize_16bit);
	TypeBitSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_INT32, DataSize_32bit);
	TypeBitSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_UINT8, DataSize_08bit);
	TypeBitSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_UINT16, DataSize_16bit);
	TypeBitSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_UINT32, DataSize_32bit);

	TypeDataSizeMap.RemoveAll();
	TypeDataSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_BOOL, DataSize_16bit);
	TypeDataSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_BYTE, DataSize_16bit);
	TypeDataSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_WORD, DataSize_16bit);
	TypeDataSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_DWORD, DataSize_32bit);
	TypeDataSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_INT8, DataSize_16bit);
	TypeDataSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_INT16, DataSize_16bit);
	TypeDataSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_INT32, DataSize_32bit);
	TypeDataSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_UINT8, DataSize_16bit);
	TypeDataSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_UINT16, DataSize_16bit);
	TypeDataSizeMap.SetAt(CDATA_OFFSET_DATA_TYPE_UINT32, DataSize_32bit);

	CDataOffset::IsInit = TRUE;
}

/**
 *	データの型を設定する。
 *
 *	@param	DataType	データの型に対応するID
 */
void CDataOffset::SetDataType(INT_PTR DataType)
{
	this->m_DataType = DataType;

	this->m_DataSize = TypeBitSizeMap[this->m_DataType];
	this->m_BitArray = TypeBitArrayMap[this->m_DataType];
}

/**
 *	データのビット位置情報をセットする。
 *
 *	@param	BitOffset	オフセット情報の文字列
 *						[ワードオフセット(10進数)].[ビットオフセット(16進数)]の
 *						フォーマットであること。
 *						また、ビットオフセットから始まるデータの範囲がワードを跨いで
 *						いた場合には、エラーとする。
 */
void CDataOffset::SetOffset(CString BitOffset)
{
	//フォーマットの確認
	if (FALSE == this->CheckFormat(BitOffset)) {
		//@ToDo:例外を投げる
		TRACE(_T("BitOffset format invalid\r\n"));
		return;
	}

	INT_PTR TokenIndex = BitOffset.Find(_T('.'));
	this->m_DataOffset = this->ExtractOffset(BitOffset, 0, TokenIndex, CDATA_OFFSET_BASE_DECIMAL);	//データのインデックスは、10進数表記
	this->m_BitOffset = this->ExtractOffset(
		BitOffset, TokenIndex + 1, BitOffset.GetLength() - TokenIndex, CDATA_OFFSET_BASE_HEX_DECIMAL);	//データのインデックスは、10進数表記

	INT_PTR BitSize = TypeBitSizeMap[this->m_DataType];
	INT_PTR DataSize = this->m_BitOffset + BitSize;
	if (this->m_DataSize < DataSize) {
		//@ToDo:例外を投げる
		TRACE(_T("Bit offset error!\r\n"));
	}
}

/**
 *	ビットオフセットのフォーマットを確認する。
 *	フォーマットが正しい場合にはTRUE、正しくない場合にはFALSEを返す。
 *
 *	@param	BitOffset	オフセット情報の文字列
 *						[ワードオフセット(10進数)].[ビットオフセット(16進数)]の
 *						フォーマットであること。
 */
BOOL CDataOffset::CheckFormat(CString BitOffset)
{
	std::regex pattern(_T("[0-9]{1,}(\.[0-9A-Fa-f]){1,1}"));
	std::cmatch Match;
	TCHAR* PatternEnd = BitOffset.GetBuffer() + BitOffset.GetLength();
	LPTSTR Buffer = BitOffset.GetBuffer();

	return std::regex_match((const TCHAR*)Buffer, (const TCHAR*)PatternEnd, Match, pattern);
}

/**
 *	オフセットの文字列から、対応するオフセット値を抜き出す。
 *
 *	@param	BitOffset	オフセットを示す文字列
 *	@param	StartIndex	文字列の抜き出し開始位置
 *	@param	DataLen		抜き出す文字列の長さ
 *	@param	Base		オフセットのデータの基数
 *	@return	オフセット値
 */
INT_PTR CDataOffset::ExtractOffset(CString BitOffset, INT_PTR StartIndex, INT_PTR DataLen, int Base)
{
	CString DataOffset = BitOffset.Mid(StartIndex, DataLen);

	TCHAR* EndChar = NULL;
	INT_PTR OffsetValue = _tcstol(DataOffset, &EndChar, Base);
	if ((NULL != EndChar) && (NULL != _doserrno)) {
		TRACE(_T("FormatError\r\n"));
		return (-1);
	}
	return OffsetValue;
}