#pragma once
#include "pch.h"
#include "CDataType.h"

class CCheckOverlap
{
public:
	virtual BOOL CheckOverlap(const CArray<CDataType*>* DataToCheck) = 0;
};

