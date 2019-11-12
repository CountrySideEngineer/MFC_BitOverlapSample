#pragma once
#ifdef _UTEST
#include <afxtempl.h>
#endif

class CUtility
{
protected:
	enum {
		CDATA_OFFSET_BASE_DECIMAL = 10,
		CDATA_OFFSET_BASE_HEX_DECIMAL = 16,
	};
public:
	template <class T> void Release(CArray<T*>* Target);
	template <class T> void Release(T** Target);
	virtual void ExtractOffset(CString OffsetString, INT_PTR& DataOffset, INT_PTR& BitOffset);
	virtual CString SetupOffset(const INT_PTR DataOffset, const INT_PTR BitOffset);
	template <typename T> INT_PTR Type2Bit(INT_PTR TypeSize);

protected:
	virtual BOOL CheckBitOffsetFormat(CString BitOffset);
	virtual INT_PTR ExtractOffset(CString BitOffset, INT_PTR StartIndex, INT_PTR DataLen, int Base);
};

/**
 *	配列の内容を解放する。
 *
 *	@param[in,out]	Target	要素を解放したい配列へのポインタ
 */
template <class T>
void CUtility::Release(CArray<T*>* Target)
{
	ASSERT(NULL != Target);

	for (INT_PTR Index = 0; Index < Target->GetCount(); Index++) {
		T* TargetItem = Target->GetAt(Index);
		if (NULL != TargetItem) {
			this->Release(&TargetItem);
		}
	}
	Target->RemoveAll();
}

/**
 *	オブジェクトを解放する。
 *
 *	@param[in,out]	Target	解放したい領域へのポインタへのポインタ
 */
template <class T>
void CUtility::Release(T** Target)
{
	ASSERT(NULL != Target);
	ASSERT(NULL != *Target);

	delete *Target;
	*Target = NULL;
}

/**
 *	データ型とそのサイズに対応したビット長を返す。
 *	(例：T = BYTE、TpyeSize = 2 → 16(bit))
 *
 *	@param	TypeBitSize	データの(ビット)サイズ
 *	@return	データ型とサイズに対応したビット長
 */
template <typename T>
INT_PTR CUtility::Type2Bit(INT_PTR TypeSize)
{
	const INT_PTR BitPerByte = 8;
	INT_PTR BitSizeOfType = sizeof(T);

	return (TypeSize * BitSizeOfType * BitPerByte);
}