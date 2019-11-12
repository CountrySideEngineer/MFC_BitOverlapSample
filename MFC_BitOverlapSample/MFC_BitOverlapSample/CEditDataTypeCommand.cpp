#include "pch.h"
#include "CEditDataTypeCommand.h"
#include "CEditNewDataDlg.h"
#include "CUtility.h"

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CEditDataTypeCommand::CEditDataTypeCommand()
	: m_Receiver(NULL)
	, m_DataType(NULL)
	, m_DataTypeIndex(0)
{}

/**
 *	�ҏW�Ώۂ̃f�[�^��ݒ肷��B
 *
 *	@param[in]	Receiver	�ҏW�����f�[�^�̔��f��ւ̃|�C���^
 */
VOID CEditDataTypeCommand::SetReceiver(CArray<CDataType*>* Receiver)
{
	ASSERT(NULL != Receiver);

	this->m_Receiver = Receiver;
}

/**
 *	�ҏW��̃f�[�^���Z�b�g����B
 *
 *	@param[in]	DataType	�ҏW��̃f�[�^�^���ւ̃|�C���^
 */
VOID CEditDataTypeCommand::SetDataType(CDataType* DataType)
{
	ASSERT(NULL != DataType);

	this->m_DataType = DataType;
}

/**
 *	�ҏW��̃f�[�^�̔��f����Z�b�g����B
 *
 *	@param	DataTypeIndex	�f�[�^�̔��f��̃C���f�b�N�X
 */
VOID CEditDataTypeCommand::SetDataTypeIndex(INT_PTR DataTypeIndex)
{
	ASSERT(0 <= DataTypeIndex);

	this->m_DataTypeIndex = DataTypeIndex;
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
	ASSERT(NULL != m_DataType);
	ASSERT(0 <= this->m_DataTypeIndex);
	ASSERT(this->m_DataTypeIndex < this->m_Receiver->GetCount());

	CDataType* DataType = this->m_Receiver->GetAt(this->m_DataTypeIndex);
	CUtility Util;
	Util.Release(&DataType);
	this->m_Receiver->RemoveAt(this->m_DataTypeIndex);
	this->m_Receiver->InsertAt(this->m_DataTypeIndex, new CDataType(this->m_DataType));

	return TRUE;
}