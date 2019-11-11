#include "pch.h"
#include "CAddDataTypeInfoCommand.h"

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CAddDataTypeInfoCommand::CAddDataTypeInfoCommand()
	: m_Receiver(NULL)
	, m_DataType(NULL)
{}

/**
 *	�ǉ�����f�[�^�^�����܂ރI�u�W�F�N�g�ւ̃|�C���^���Z�b�g����B
 *
 *	@param[in]	DataType	�ǉ��������f�[�^�^���
 */
VOID CAddDataTypeInfoCommand::SetDataType(CDataType* DataType)
{
	ASSERT(NULL != DataType);

	this->m_DataType = DataType;
}

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
	ASSERT(NULL != this->m_DataType);

	return this->AddNewDataType(this->m_DataType);
}

/**
 *	���͂��ꂽ�V�K�f�[�^�^�����A�i�[��ɐݒ肷��B
 *
 *	@param[in]	DataType	�V�K�f�[�^�^���ւ̃|�C���^
 */
BOOL CAddDataTypeInfoCommand::AddNewDataType(CDataType* DataType)
{
	ASSERT(NULL != this->m_Receiver);
	ASSERT(NULL != DataType);

	this->m_Receiver->Add(new CDataType(DataType));
	return TRUE;
}