#include "pch.h"
#include "CUtility.h"
#include "CRegex.h"
#include <regex>

/**
 *	�f�[�^�I�t�Z�b�g�̕����񂩂�A�f�[�^/�r�b�g�̃I�t�Z�b�g���擾����B
 *
 *	@param	OffsetString	�I�t�Z�b�g������������
 *	@param[out]	DataOffset	�����o�����f�[�^�I�t�Z�b�g�̊i�[��
 *	@param[out]	BitOffset	�����o�����r�b�g�I�t�Z�b�g�̊i�[��
 */
void CUtility::ExtractOffset(CString OffsetString, INT_PTR& DataOffset, INT_PTR& BitOffset)
{
	//�t�H�[�}�b�g�̊m�F
	if (FALSE == this->CheckBitOffsetFormat(OffsetString)) {
		TRACE(_T("Offset format ERROR!\n"));

		return;
	}

	INT_PTR TokenIndex = OffsetString.Find(_T("."));
	INT_PTR DataOffsetTemp = this->ExtractOffset(OffsetString,
		0,
		TokenIndex,
		CDATA_OFFSET_BASE_DECIMAL);	//�f�[�^�̃C���f�b�N�X�́A10�i���\�L
	INT_PTR BitOffsetTmp = this->ExtractOffset(OffsetString,
		TokenIndex + 1,
		OffsetString.GetLength() - TokenIndex,
		CDATA_OFFSET_BASE_DECIMAL);	//�r�b�g�̃C���f�b�N�X�́A10�i���\�L

	DataOffset = DataOffsetTemp;
	BitOffset = BitOffsetTmp;
}

/**
 *	�r�b�g�I�t�Z�b�g�̃t�H�[�}�b�g���m�F����B
 *	�t�H�[�}�b�g���������ꍇ�ɂ�TRUE�A�������Ȃ��ꍇ�ɂ�FALSE��Ԃ��B
 *
 *	@param	BitOffset	�I�t�Z�b�g���̕�����
 *						[���[�h�I�t�Z�b�g(10�i��)].[�r�b�g�I�t�Z�b�g(16�i��)]��
 *						�t�H�[�}�b�g�ł��邱�ƁB
 */
BOOL CUtility::CheckBitOffsetFormat(CString BitOffset)
{
	std::regex pattern(_T("[0-9]{1,}(\.[0-9])"));
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
INT_PTR CUtility::ExtractOffset(CString BitOffset, INT_PTR StartIndex, INT_PTR DataLen, int Base)
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

CString CUtility::SetupOffset(const INT_PTR DataOffset, const INT_PTR BitOffset)
{
	CString OffsetString = _T("");

	if ((BitOffset < 0) || (8 < BitOffset)) {
		/*
		 *	�r�b�g�I�t�Z�b�g��1�o�C�g�ȓ�(0�`7)�łȂ���΂Ȃ�Ȃ��B
		 *	��L�ȏ�͈̔͂̏ꍇ�ɂ́u�ϊ��s�v�Ƃ��āA�󕶎���Ԃ��B
		 *	@ToDo:��O�𓊂���B
		 */
		return _T("");
	}
	OffsetString.Format(_T("%d.%d"), DataOffset, BitOffset);
	return OffsetString;
}