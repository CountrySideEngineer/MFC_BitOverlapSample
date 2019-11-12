#include "pch.h"
#include "CCommandManager.h"
#include "CUtility.h"

/**
 *	デフォルトコンストラクタ
 */
CBOSCommandManager::CBOSCommandManager()
{
	this->m_CommandStack.RemoveAll();
}

/**
 *	デストラクタ
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
 *	コマンドを実行する。
 *
 *	@param[in]	Command	実行するコマンドへのポインタ
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
			//スタックに追加しない設定の場合には、コマンドを実行して処理終了とする。
		}
	}
	else {
		//コマンドの処理結果が「失敗」の場合には、何もしない。
	}
	return CommandResult;
}