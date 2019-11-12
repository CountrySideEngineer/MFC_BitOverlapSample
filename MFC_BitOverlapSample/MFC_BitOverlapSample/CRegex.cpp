#include "pch.h"
#include "CRegex.h"
#include <regex>

/**
 *	�����Ŏw�肳�ꂽ�����񂪁A�I�t�Z�b�g�̃t�H�[�}�b�g(xxx.x)�Ɉ�v���Ă��邩
 *	�ۂ��𔻒肷��B
 *
 *	@param[in]	Target	�m�F�Ώۂ̕�����
 *	@return	Target���I�t�Z�b�g�̃t�H�[�}�b�g�Ɉ�v���Ă����ꍇ�ɂ�TRUE���A
 *			��v���Ă��Ȃ��ꍇ�ɂ�FALSE��Ԃ��B
 */
BOOL CRegex::CheckOffset(CString& Target)
{
	CString Regex = _T("[0-9]{1,}[\.]?[0-9]");

	return this->RunCheck(Target, Regex);
}

/**
 *	���K�\���ƈ�v���邩�ۂ����m�F����B
 *
 *	@param[in]	Target	�m�F�Ώۂ̕�����
 *	@param[in]	Regex	���K�\���̌���������
 *	@return	���K�\���Ɉ�v�����ꍇ�ɂ�TRUE�A��v���Ȃ������ꍇ�ɂ�FALSE��Ԃ��B
 */
BOOL CRegex::RunCheck(CString& Target, CString& Regex)
{
	USES_CONVERSION;
	std::string TargetString = T2A(Target.GetBuffer());
	std::string RegExString = T2A(Regex.GetBuffer());
	std::regex RegExPattern(RegExString);

	BOOL IsMatch = std::regex_match(TargetString.c_str(), RegExPattern);
	return IsMatch;
}


