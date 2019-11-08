#pragma once
class CUtility
{
protected:
	enum {
		CDATA_OFFSET_BASE_DECIMAL = 10,
		CDATA_OFFSET_BASE_HEX_DECIMAL = 16,
	};
public:
	template <class T> void Release(CArray<T*>* Target);
	virtual void ExtractOffset(CString OffsetString, INT_PTR& DataOffset, INT_PTR& BitOffset);
	virtual CString SetupOffset(const INT_PTR DataOffset, const INT_PTR BitOffset);

protected:
	virtual BOOL CheckBitOffsetFormat(CString BitOffset);
	virtual INT_PTR ExtractOffset(CString BitOffset, INT_PTR StartIndex, INT_PTR DataLen, int Base);
};

/**
 *	�z��̓��e���������B
 *
 *	@param[in,out]	Target	�v�f������������z��ւ̃|�C���^
 */
template <class T>
void CUtility::Release(CArray<T*>* Target)
{
	ASSERT(NULL != Target);

	for (INT_PTR Index = 0; Index < Target->GetCount(); Index++) {
		T* TargetItem = Target->GetAt(Index);
		if (NULL != TargetItem) {
			delete TargetItem;
			TargetItem = NULL;
		}
	}
	Target->RemoveAll();
}