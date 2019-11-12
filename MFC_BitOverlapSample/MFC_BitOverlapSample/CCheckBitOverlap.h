#pragma once
#include "CCheckOverlap.h"

class CCheckBitOverlap : public CCheckOverlap
{
public:
	CCheckBitOverlap() {}
	virtual ~CCheckBitOverlap() {}

	virtual BOOL CheckOverlap(const CArray<CDataType*>* DataToCheck);

protected:
	virtual BOOL CheckOverlap(const CDataType* Target, const CDataType* Comp);
};

