#include "pch.h"
#include "CDataOffset.h"
#include <regex>

CMap<CString, LPCTSTR, INT_PTR, INT_PTR> CDataOffset::TypeDataMap;
CMap<INT_PTR, INT_PTR, UINT32, UINT32> CDataOffset::TypeBitMaskMap;
CMap<INT_PTR, INT_PTR, INT_PTR, INT_PTR> CDataOffset::TypeBitSizeMap;
CMap<INT_PTR, INT_PTR, INT_PTR, INT_PTR> CDataOffset::TypeDataSizeMap;
BOOL CDataOffset::IsInit = FALSE;

CDataOffset::CDataOffset()
	: m_DataType(CDATA_OFFSET_DATA_TYPE_BOOL)
	, m_DataOffset(0)
	, m_BitOffset(0)
{
	CDataOffset::InitMap();
}

CDataOffset::CDataOffset(int DataType, INT_PTR DataOffset, INT_PTR BitOffset)
	: m_DataType(DataType)
	, m_DataOffset(DataOffset)
	, m_BitOffset(BitOffset)
{}

/**
 *	データのサイズ、ビット配列を定義するマップを初期化する。
 */
void CDataOffset::InitMap()
{
	if (TRUE == CDataOffset::IsInit) {
		//初期化済み
		return;
	}

	TypeDataMap.RemoveAll();
	TypeDataMap.SetAt(_T("BOOL"), CDATA_OFFSET_DATA_TYPE_BOOL);
	TypeDataMap.SetAt(_T("BYTE"), CDATA_OFFSET_DATA_TYPE_BYTE);
	TypeDataMap.SetAt(_T("WORD"), CDATA_OFFSET_DATA_TYPE_WORD);
	TypeDataMap.SetAt(_T("DWORD"), CDATA_OFFSET_DATA_TYPE_DWORD);
	TypeDataMap.SetAt(_T("INT8"), CDATA_OFFSET_DATA_TYPE_INT8);
	TypeDataMap.SetAt(_T("INT16"), CDATA_OFFSET_DATA_TYPE_INT16);
	TypeDataMap.SetAt(_T("INT32"), CDATA_OFFSET_DATA_TYPE_INT32);
	TypeDataMap.SetAt(_T("UINT8"), CDATA_OFFSET_DATA_TYPE_UINT8);
	TypeDataMap.SetAt(_T("UINT16"), CDATA_OFFSET_DATA_TYPE_UINT16);
	TypeDataMap.SetAt(_T("UINT32"), CDATA_OFFSET_DATA_TYPE_UINT32);

	TypeBitMaskMap.RemoveAll();
	TypeBitMaskMap.SetAt(CDATA_OFFSET_DATA_TYPE_BOOL, DataBitArray_01bit);
	TypeBitMaskMap.SetAt(CDATA_OFFSET_DATA_TYPE_BYTE, DataBitArray_08bit);
	TypeBitMaskMap.SetAt(CDATA_OFFSET_DATA_TYPE_WORD, DataBitArray_16bit);
	TypeBitMaskMap.SetAt(CDATA_OFFSET_DATA_TYPE_DWORD, DataBitArray_32bit);
	TypeBitMaskMap.SetAt(CDATA_OFFSET_DATA_TYPE_INT8, DataBitArray_08bit);
	TypeBitMaskMap.SetAt(CDATA_OFFSET_DATA_TYPE_INT16, DataBitArray_16bit);
	TypeBitMaskMap.SetAt(CDATA_OFFSET_DATA_TYPE_INT32, DataBitArray_32bit);
	TypeBitMaskMap.SetAt(CDATA_OFFSET_DATA_TYPE_UINT8, DataBitArray_08bit);
	TypeBitMaskMap.SetAt(CDATA_OFFSET_DATA_TYPE_UINT16, DataBitArray_16bit);
	TypeBitMaskMap.SetAt(CDATA_OFFSET_DATA_TYPE_UINT32, DataBitArray_32bit);

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

void CDataOffset::SetDataType(CString DataType)
{
	this->m_DataType = CDataOffset::TypeDataMap[DataType];
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
	INT_PTR DataOffsetTmp = this->ExtractOffset(BitOffset, 
		0, 
		TokenIndex, 
		CDATA_OFFSET_BASE_DECIMAL);	//データのインデックスは、10進数表記
	INT_PTR BitOffsetTmp = this->ExtractOffset(BitOffset, 
		TokenIndex + 1, 
		BitOffset.GetLength() - TokenIndex, 
		CDATA_OFFSET_BASE_HEX_DECIMAL);	//データのインデックスは、16進数表記

	INT_PTR BitSize = TypeBitSizeMap[this->m_DataType];
	INT_PTR DataSize =  BitOffsetTmp + BitSize;
	if (this->GetDataSize() < DataSize) {
		//@ToDo:例外を投げる
		TRACE(_T("Bit offset error!\r\n"));
		return;
	}

	this->m_DataOffset = DataOffsetTmp;
	this->m_BitOffset = BitOffsetTmp;
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
	std::regex pattern(_T("[0-9]{1,}(.[0-9A-Fa-f]){1,1}"));
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