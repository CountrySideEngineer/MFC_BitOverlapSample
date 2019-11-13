#include "pch.h"
#include "CCsvFormatter.h"
#include "CDataTypeInfo.h"
#include "CUtility.h"

const CString CCsvFormatter::Separator = _T(",");
const CString CCsvFormatter::CrLf = _T("\r\n");
const CString CCsvFormatter::Lf = _T("\n");
const CString CCsvFormatter::DoubleQuotation = _T("\"");

/**
 *	�f�[�^�^��񂩂�A�t�@�C���o�͗p�t�H�[�}�b�g���쐬����B
 *
 *	@param[in]	Src	�t�@�C���ɏo�͂������f�[�^�^���ւ̃|�C���^
 *	@return	�o�͏��ւ̃|�C���^
 */
CString CCsvFormatter::Format(CArray<CDataType*>* Src)
{
	ASSERT(NULL != Src);
	ASSERT(0 < Src->GetCount());

	CString FormattedString = _T("");
	for (INT_PTR Index = 0; Index < Src->GetCount(); Index++) {
		CDataType* SrcItem = Src->GetAt(Index);
		FormattedString += this->Format(SrcItem);
	}
	return FormattedString;
}

/**
 *	�f�[�^�^��񂩂�A�t�@�C���ɏo�͂���CSV�`���̕�����𐶐�����B
 *
 *	@param[in]	Src	CSV(�P�s��)�ɏo�͂��镶����f�[�^
 */
CString CCsvFormatter::Format(CDataType* Src)
{
	ASSERT(NULL != Src);

	CDataTypeInfo* Instance = CDataTypeInfo::GetInstance();
	CString DataTypeName = Instance->GetTypeName(Src->GetDataTypeId());
	CString DataDesc = Src->GetDataDesc();
	CUtility Util;
	CString Offset = Util.SetupOffset(Src->GetDataOffset(), Src->GetBitOffset());
	CString Remarks = Src->GetRemarks();
	if (0 < Remarks.Find(CrLf)) {
		//���l�ɉ��s���������ꍇ�A���s�R�[�h��ύX���������Łu"�v�ň͂ށB
		Remarks.Replace(CrLf, Lf);
		Remarks = DoubleQuotation + Remarks + DoubleQuotation;
	}

	CString FormattedString = _T("");
	FormattedString += (DataTypeName + Separator);
	FormattedString += (DataDesc + Separator);
	FormattedString += (Offset + Separator);
	FormattedString += (Remarks + CrLf);

	return FormattedString;
}