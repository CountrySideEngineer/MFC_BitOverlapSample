#include "pch.h"
#include "CEditNewDataDlg.h"
#include "CAddDataTypeInfoCommand.h"

/**
 *	デフォルトコンストラクタ
 */
CAddDataTypeInfoCommand::CAddDataTypeInfoCommand()
	: m_Receiver(NULL)
{}

/**
 *	データの追加先へのポインタをセットする。
 */
VOID CAddDataTypeInfoCommand::SetReceiver(CArray<CDataType*>* Receiver)
{
	ASSERT(NULL != Receiver);

	this->m_Receiver = Receiver;
}

/**
 *	追加コマンドを実行する。
 *
 *	@return	追加処理が正常に完了した場合にはTRUEを返す。処理が正常に完了しなかった
 *			場合にはFALSEを返す。
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
 *	入力された新規データ型情報を、格納先に設定する。
 *
 *	@param[in]	DataType	新規データ型情報へのポインタ
 */
BOOL CAddDataTypeInfoCommand::AddNewDataType(CDataType* DataType)
{
	ASSERT(NULL != DataType);

	this->m_Receiver->Add(new CDataType(DataType));
	return TRUE;
}