#include "pch.h"
#include "CDeleteDataTypeInfoCommand.h"
#include "CUtility.h"

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CDeleteDataTypeInfoCommand::CDeleteDataTypeInfoCommand()
	: m_TargetIndex(0)
	, m_Receiver(NULL)
{}

/**
 *	�R�}���h�̏����Ώۂ��Z�b�g����B
 */
VOID CDeleteDataTypeInfoCommand::SetReceiver(CArray<CDataType*>* Receiver)
{
	ASSERT(NULL != Receiver);

	this->m_Receiver = Receiver;
}

/**
 *	�R�}���h�����s����B
 *
 *	@return	�폜����������Ɋ��������ꍇ�ɂ�TRUE���A���������s�����ꍇ�ɂ�
 *			FALSE��Ԃ��B
 */
BOOL CDeleteDataTypeInfoCommand::Execute()
{
	ASSERT(NULL != this->m_Receiver);
	ASSERT(0 <= this->m_TargetIndex);
	ASSERT(this->m_TargetIndex < this->m_Receiver->GetCount());

	CDataType* TargetItem = this->m_Receiver->GetAt(this->m_TargetIndex);
	CUtility Util;
	Util.Release(&TargetItem);

	this->m_Receiver->RemoveAt(this->m_TargetIndex);

	return TRUE;
}
