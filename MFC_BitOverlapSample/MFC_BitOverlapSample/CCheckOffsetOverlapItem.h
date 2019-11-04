#pragma once
#include "CCheckOffsetOverlap.h"
class CCheckOffsetOverlapItem : public CCheckOffsetOverlap
{
public:
	CCheckOffsetOverlapItem();
	virtual ~CCheckOffsetOverlapItem() {}
protected:
	virtual BOOL CheckOverlap(const CArray<CDataOffset>& DataToCheck);
	template <typename T> BOOL SetBitData(CDataOffset* DataToCheck);
	template <typename T> BOOL CheckOverlap(CDataOffset* DataToCheck);
	template <typename T> void GetBitData(CDataOffset* DataToCheckTaget, T** Data, T* BitData);

protected:
	INT_PTR m_OverlapDataIndex;
	INT_PTR m_OverlapDataTargetIndex;
};

