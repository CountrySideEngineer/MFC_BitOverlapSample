#include "pch.h"
#include "CEditNewDataDlg.h"
#include "CAddDataTypeInfoCommand.h"

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CAddDataTypeInfoCommand::CAddDataTypeInfoCommand()
	: m_Receiver(NULL)
{}

/**
 *	�f�[�^�̒ǉ���ւ̃|�C���^���Z�b�g����B
 */
VOID CAddDataTypeInfoCommand::SetReceiver(CArray<CDataType*>* Receiver)
{
	ASSERT(NULL != Receiver);

	this->m_Receiver = Receiver;
}

/**
 *	�ǉ��R�}���h�����s����B
 *
 *	@return	�ǉ�����������Ɋ��������ꍇ�ɂ�TRUE��Ԃ��B����������Ɋ������Ȃ�����
 *			�ꍇ�ɂ�FALSE��Ԃ��B
 */
BOOL CAddDataTypeInfoCommand::Execute()
{
	ASSERT(NULL != this->m_Receiver);

	CDataType NewDataType;
	CEditNewDataDlg EditDataDlg;
	EditDataDlg.SetDataTypeStore(&NewDataType);
	INT_PTR EditResult = EditDataDlg.DoModal();
	if (IDOK == EditResult) {
		return this->AddNewDataType(&NewDataType);
	}
	else {
		return FALSE;
	}
}

/**
 *	���͂��ꂽ�V�K�f�[�^�^�����A�i�[��ɐݒ肷��B
 *
 *	@param[in]	DataType	�V�K�f�[�^�^���ւ̃|�C���^
 */
BOOL CAddDataTypeInfoCommand::AddNewDataType(CDataType* DataType)
{
	ASSERT(NULL != DataType);

	this->m_Receiver->Add(new CDataType(DataType));
	return TRUE;
}