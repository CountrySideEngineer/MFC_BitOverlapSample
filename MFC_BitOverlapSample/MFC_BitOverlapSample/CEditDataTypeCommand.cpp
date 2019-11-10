#include "pch.h"
#include "CEditDataTypeCommand.h"
#include "CEditNewDataDlg.h"

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CEditDataTypeCommand::CEditDataTypeCommand()
	: m_Receiver(NULL)
{}

/**
 *	�ҏW�Ώۂ̃f�[�^��ݒ肷��B
 */
VOID CEditDataTypeCommand::SetReceiver(CDataType* Receiver)
{
	ASSERT(NULL != Receiver);

	this->m_Receiver = Receiver;
}

/**
 *	�ҏW���������s����B
 *
 *	@return	�ҏW����������Ɋ��������ꍇ�ɂ�TRUE��Ԃ��B
 *			����������Ɋ������Ȃ������ꍇ�ɂ́AFALSE��Ԃ��B
 */
BOOL CEditDataTypeCommand::Execute()
{
	ASSERT(NULL != this->m_Receiver);

	CEditNewDataDlg EditDlg;
	EditDlg.SetDataType(this->m_Receiver);
	INT_PTR EditResult = EditDlg.DoModal();
	if (IDOK == EditResult) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}