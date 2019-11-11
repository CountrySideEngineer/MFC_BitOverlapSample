#include "pch.h"
#include "CEditDataTypeCommand.h"
#include "CEditNewDataDlg.h"
#include "CUtility.h"

/**
 *	デフォルトコンストラクタ
 */
CEditDataTypeCommand::CEditDataTypeCommand()
	: m_Receiver(NULL)
	, m_DataType(NULL)
	, m_DataTypeIndex(0)
{}

/**
 *	編集対象のデータを設定する。
 *
 *	@param[in]	Receiver	編集したデータの反映先へのポインタ
 */
VOID CEditDataTypeCommand::SetReceiver(CArray<CDataType*>* Receiver)
{
	ASSERT(NULL != Receiver);

	this->m_Receiver = Receiver;
}

/**
 *	編集後のデータをセットする。
 *
 *	@param[in]	DataType	編集後のデータ型情報へのポインタ
 */
VOID CEditDataTypeCommand::SetDataType(CDataType* DataType)
{
	ASSERT(NULL != DataType);

	this->m_DataType = DataType;
}

/**
 *	編集後のデータの反映先をセットする。
 *
 *	@param	DataTypeIndex	データの反映先のインデックス
 */
VOID CEditDataTypeCommand::SetDataTypeIndex(INT_PTR DataTypeIndex)
{
	ASSERT(0 <= DataTypeIndex);

	this->m_DataTypeIndex = DataTypeIndex;
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