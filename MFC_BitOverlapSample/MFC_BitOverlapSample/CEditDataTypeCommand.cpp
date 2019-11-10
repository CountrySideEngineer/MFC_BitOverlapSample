#include "pch.h"
#include "CEditDataTypeCommand.h"
#include "CEditNewDataDlg.h"

/**
 *	デフォルトコンストラクタ
 */
CEditDataTypeCommand::CEditDataTypeCommand()
	: m_Receiver(NULL)
{}

/**
 *	編集対象のデータを設定する。
 */
VOID CEditDataTypeCommand::SetReceiver(CDataType* Receiver)
{
	ASSERT(NULL != Receiver);

	this->m_Receiver = Receiver;
}

/**
 *	編集処理を実行する。
 *
 *	@return	編集処理が正常に完了した場合にはTRUEを返す。
 *			処理が正常に完了しなかった場合には、FALSEを返す。
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