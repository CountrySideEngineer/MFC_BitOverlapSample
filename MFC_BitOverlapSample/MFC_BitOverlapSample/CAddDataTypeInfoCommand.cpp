#include "pch.h"
#include "CAddDataTypeInfoCommand.h"

/**
 *	デフォルトコンストラクタ
 */
CAddDataTypeInfoCommand::CAddDataTypeInfoCommand()
	: m_Receiver(NULL)
	, m_DataType(NULL)
{}

/**
 *	追加するデータ型情報を含むオブジェクトへのポインタをセットする。
 *
 *	@param[in]	DataType	追加したいデータ型情報
 */
VOID CAddDataTypeInfoCommand::SetDataType(CDataType* DataType)
{
	ASSERT(NULL != DataType);

	this->m_DataType = DataType;
}

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
	ASSERT(NULL != this->m_DataType);

	return this->AddNewDataType(this->m_DataType);
}

/**
 *	入力された新規データ型情報を、格納先に設定する。
 *
 *	@param[in]	DataType	新規データ型情報へのポインタ
 */
BOOL CAddDataTypeInfoCommand::AddNewDataType(CDataType* DataType)
{
	ASSERT(NULL != this->m_Receiver);
	ASSERT(NULL != DataType);

	this->m_Receiver->Add(new CDataType(DataType));
	return TRUE;
}