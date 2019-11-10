#include "pch.h"
#include "CCommandManager.h"
#include "CUtility.h"

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CBOSCommandManager::CBOSCommandManager()
{
	this->m_CommandStack.RemoveAll();
}

/**
 *	�f�X�g���N�^
 */
CBOSCommandManager::~CBOSCommandManager()
{
	CUtility Util;
	while (0 < this->m_CommandStack.GetCount()) {
		ACommand* Item = this->m_CommandStack.RemoveTail();
		Util.Release(&Item);
	}
}

/**
 *	�R�}���h�����s����B
 *
 *	@param[in]	Command	���s����R�}���h�ւ̃|�C���^
 */
BOOL CBOSCommandManager::ExecuteCommand(ACommand* Command, BOOL DoesStack)
{
	ASSERT(NULL != Command);

	BOOL CommandResult = Command->Execute();
	if (TRUE == CommandResult) {
		if (TRUE == DoesStack) {
			this->m_CommandStack.AddTail(Command);
		}
		else {
			//�X�^�b�N�ɒǉ����Ȃ��ݒ�̏ꍇ�ɂ́A�R�}���h�����s���ď����I���Ƃ���B
		}
	}
	else {
		//�R�}���h�̏������ʂ��u���s�v�̏ꍇ�ɂ́A�������Ȃ��B
	}
	return CommandResult;
}