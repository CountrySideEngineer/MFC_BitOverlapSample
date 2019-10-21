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
 *	�f�[�^�̃T�C�Y�A�r�b�g�z����`����}�b�v������������B
 */
void CDataOffset::InitMap()
{
	if (TRUE == CDataOffset::IsInit) {
		//�������ς�
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
 *	�f�[�^�̌^��ݒ肷��B
 *
 *	@param	DataType	�f�[�^�̌^�ɑΉ�����ID
 */
void CDataOffset::SetDataType(INT_PTR DataType)
{
	this->m_DataType = DataType;

	this->m_DataSize = TypeBitSizeMap[this->m_DataType];
	this->m_BitArray = TypeBitArrayMap[this->m_DataType];
}

/**
 *	�f�[�^�̃r�b�g�ʒu�����Z�b�g����B
 *
 *	@param	BitOffset	�I�t�Z�b�g���̕�����
 *						[���[�h�I�t�Z�b�g(10�i��)].[�r�b�g�I�t�Z�b�g(16�i��)]��
 *						�t�H�[�}�b�g�ł��邱�ƁB
 *						�܂��A�r�b�g�I�t�Z�b�g����n�܂�f�[�^�͈̔͂����[�h���ׂ���
 *						�����ꍇ�ɂ́A�G���[�Ƃ���B
 */
void CDataOffset::SetOffset(CString BitOffset)
{
	//�t�H�[�}�b�g�̊m�F
	if (FALSE == this->CheckFormat(BitOffset)) {
		//@ToDo:��O�𓊂���
		TRACE(_T("BitOffset format invalid\r\n"));
		return;
	}

	INT_PTR TokenIndex = BitOffset.Find(_T('.'));
	this->m_DataOffset = this->ExtractOffset(BitOffset, 0, TokenIndex, CDATA_OFFSET_BASE_DECIMAL);	//�f�[�^�̃C���f�b�N�X�́A10�i���\�L
	this->m_BitOffset = this->ExtractOffset(
		BitOffset, TokenIndex + 1, BitOffset.GetLength() - TokenIndex, CDATA_OFFSET_BASE_HEX_DECIMAL);	//�f�[�^�̃C���f�b�N�X�́A10�i���\�L

	INT_PTR BitSize = TypeBitSizeMap[this->m_DataType];
	INT_PTR DataSize = this->m_BitOffset + BitSize;
	if (this->m_DataSize < DataSize) {
		//@ToDo:��O�𓊂���
		TRACE(_T("Bit offset error!\r\n"));
	}
}

/**
 *	�r�b�g�I�t�Z�b�g�̃t�H�[�}�b�g���m�F����B
 *	�t�H�[�}�b�g���������ꍇ�ɂ�TRUE�A�������Ȃ��ꍇ�ɂ�FALSE��Ԃ��B
 *
 *	@param	BitOffset	�I�t�Z�b�g���̕�����
 *						[���[�h�I�t�Z�b�g(10�i��)].[�r�b�g�I�t�Z�b�g(16�i��)]��
 *						�t�H�[�}�b�g�ł��邱�ƁB
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
 *	�I�t�Z�b�g�̕����񂩂�A�Ή�����I�t�Z�b�g�l�𔲂��o���B
 *
 *	@param	BitOffset	�I�t�Z�b�g������������
 *	@param	StartIndex	������̔����o���J�n�ʒu
 *	@param	DataLen		�����o��������̒���
 *	@param	Base		�I�t�Z�b�g�̃f�[�^�̊
 *	@return	�I�t�Z�b�g�l
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