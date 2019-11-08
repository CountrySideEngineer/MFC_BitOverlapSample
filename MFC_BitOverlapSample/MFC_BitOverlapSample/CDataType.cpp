#include "pch.h"
#include "CDataType.h"

/**
 *	デフォルトコンストラクタ
 */
CDataType::CDataType()
	: m_DataTypeID(0)
	, m_DataDesc(_T(""))
	, m_DataOffset(0)
	, m_BitOffset(0)
	, m_Remarks(_T(""))
{}

/**
 *	コピーコンストラクタ
 *
 *	@param[in]	Src	コピー元へのポインタ

 */
CDataType::CDataType(CDataType* Src)
{
	ASSERT(NULL != Src);

	this->m_DataTypeID = Src->m_DataTypeID;
	this->m_DataDesc = Src->m_DataDesc;
	this->m_DataOffset = Src->m_DataOffset;
	this->m_BitOffset = Src->m_BitOffset;
	this->m_Remarks = Src->m_Remarks;
}
