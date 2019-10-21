#pragma once
#include "CDataOffset.h"

class CCheckOffsetOverlap
{
public:
	CCheckOffsetOverlap();
	virtual ~CCheckOffsetOverlap();
	virtual BOOL RunCheck(const CArray<CDataOffset>& DataToCheck);

#ifdef _UTEST
	virtual WORD* GetDataArray() const { return this->m_DataArray; }
#endif	//_UTEST

protected:
	virtual INT_PTR	GetDataSize(const CArray<CDataOffset>& DataToCheck);
	virtual void AllocData(const INT_PTR DataSize);
	virtual BOOL CheckOverlap(const CArray<CDataOffset>& DataToCheck);
	virtual BOOL CheckOverlap(const CDataOffset& DataToCheck);
	template <typename T> BOOL CheckOverlap(const CDataOffset& DataToCheck);

protected:
	WORD* m_DataArray;
};

