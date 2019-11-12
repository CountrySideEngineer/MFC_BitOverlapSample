#pragma once
#include "CCheckOverlap.h"

class CCheckBitOverlap : public CCheckOverlap
{
public:
	CCheckBitOverlap();
	virtual ~CCheckBitOverlap() {}

	virtual BOOL CheckOverlap(const CArray<CDataType*>* DataToCheck);
	virtual INT_PTR GetTargetRowIndex() const { return this->m_TargetRowIndex; }
	virtual INT_PTR GetCompRowIndex() const { return this->m_CompRowIndex; }

protected:
	virtual BOOL CheckOverlap(const CDataType* Target, const CDataType* Comp);

protected:
	INT_PTR m_TargetRowIndex;
	INT_PTR m_CompRowIndex;
};

