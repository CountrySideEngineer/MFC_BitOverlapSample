#include "pch.h"
#include "CUtility.h"
#include "CRegex.h"
#include <regex>

/**
 *	�f�[�^�I�t�Z�b�g�̕����񂩂�A�f�[�^/�r�b�g�̃I�t�Z�b�g���擾����B
 *
 *	@param	OffsetString	�I�t�Z�b�g������������
 *	@param[out]	DataOffset	�����o�����f�[�^�I�t�Z�b�g�̊i�[��
 *							����������Ɋ������Ȃ������ꍇ�ɂ́A-1���Z�b�g�����B
 *	@param[out]	BitOffset	�����o�����r�b�g�I�t�Z�b�g�̊i�[��
 *							����������Ɋ������Ȃ������ꍇ�ɂ́A-1���Z�b�g�����B
 */
void CUtility::ExtractOffset(CString OffsetString, INT_PTR& DataOffset, INT_PTR& BitOffset)
{
	//�t�H�[�}�b�g�̊m�F
	if (FALSE == this->CheckBitOffsetFormat(OffsetString)) {
		TRACE(_T("Offset format ERROR!\n"));

		DataOffset = (-1);
		BitOffset = (-1);
		return;
	}

	INT_PTR TokenIndex = OffsetString.Find(_T("."));
	INT_PTR DataOffsetTemp = this->ExtractOffset(OffsetString,
		0,
		TokenIndex,
		CDATA_OFFSET_BASE_DECIMAL);	//�f�[�^�̃C���f�b�N�X�́A10�i���\�L
	if ((-1) == DataOffsetTemp) {
		/*
		 *	�ϊ��Ɏ��s�����ꍇ�ɂ́A�G���[�l��ݒ肵�ď������I������B
		 *	(�{���A�����͓��B�s�\�̂͂��B�O�̂��߂ɃG���[�������������Ă����B
		 */
		DataOffset = (-1);
		BitOffset = (-1);
		return;
	}
	INT_PTR BitOffsetTmp = this->ExtractOffset(OffsetString,
		TokenIndex + 1,
		OffsetString.GetLength() - TokenIndex,
		CDATA_OFFSET_BASE_DECIMAL);	//�r�b�g�̃C���f�b�N�X�́A10�i���\�L
	if ((-1) == BitOffsetTmp) {
		/*
		 *	�ϊ��Ɏ��s�����ꍇ�ɂ́A�G���[�l��ݒ肵�ď������I������B
		 *	(�{���A�����͓��B�s�\�̂͂��B�O�̂��߂ɃG���[�������������Ă����B
		 */
		DataOffset = (-1);
		BitOffset = (-1);
		return;
	}

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
	std::regex pattern(_T("[0-9]{1,}(\.[0-7])"));
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

/**
 *	�f�[�^/�r�b�g�̃I�t�Z�b�g�̒l�ɑΉ����镶����𐶐�����B
 *
 *	@param	DataOffset	�f�[�^�I�t�Z�b�g�l
 *	@param	BitOffset	�r�b�g�I�t�Z�b�g�l
 *	@return	�I�t�Z�b�g�l�ɑΉ������������Ԃ��B
 *			���͂���l���s���ł������ꍇ�ɂ́A�󕶎���Ԃ��B
 */
CString CUtility::SetupOffset(const INT_PTR DataOffset, const INT_PTR BitOffset)
{
	CString OffsetString = _T("");

	if ((DataOffset < 0) ||
		((BitOffset < 0) || (7 < BitOffset)))
	{
		/*
		 *	�f�[�^�I�t�Z�b�g�́A0�ȏ�łȂ���΂Ȃ�Ȃ��B
		 *	�܂��A�r�b�g�I�t�Z�b�g��1�o�C�g�ȓ�(0�`7)�łȂ���΂Ȃ�Ȃ��B
		 *	��L�ȏ�͈̔͂̏ꍇ�ɂ́u�ϊ��s�v�Ƃ��āA�󕶎���Ԃ��B
		 *	@ToDo:��O�𓊂���B
		 */
		return _T("");
	}
	OffsetString.Format(_T("%d.%d"), (int)DataOffset, (int)BitOffset);
	return OffsetString;
}