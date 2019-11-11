#include "pch.h"
#include "CDeleteDataTypeInfoCommand.h"
#include "CUtility.h"

/**
 *	デフォルトコンストラクタ
 */
CDeleteDataTypeInfoCommand::CDeleteDataTypeInfoCommand()
	: m_TargetIndex(0)
	, m_Receiver(NULL)
{}

/**
 *	コマンドの処理対象をセットする。
 */
VOID CDeleteDataTypeInfoCommand::SetReceiver(CArray<CDataType*>* Receiver)
{
	ASSERT(NULL != Receiver);

	this->m_Receiver = Receiver;
}

/**
 *	コマンドを実行する。
 *
 *	@return	削除処理が正常に完了した場合にはTRUEを、処理が失敗した場合には
 *			FALSEを返す。
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
