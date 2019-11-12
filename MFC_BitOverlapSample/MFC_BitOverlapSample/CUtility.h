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
			this->Release(&TargetItem);
		}
	}
	Target->RemoveAll();
}

/**
 *	�I�u�W�F�N�g���������B
 *
 *	@param[in,out]	Target	����������̈�ւ̃|�C���^�ւ̃|�C���^
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
 *	�f�[�^�^�Ƃ��̃T�C�Y�ɑΉ������r�b�g����Ԃ��B
 *	(��FT = BYTE�ATpyeSize = 2 �� 16(bit))
 *
 *	@param	TypeBitSize	�f�[�^��(�r�b�g)�T�C�Y
 *	@return	�f�[�^�^�ƃT�C�Y�ɑΉ������r�b�g��
 */
template <typename T>
INT_PTR CUtility::Type2Bit(INT_PTR TypeSize)
{
	const INT_PTR BitPerByte = 8;
	INT_PTR BitSizeOfType = sizeof(T);

	return (TypeSize * BitSizeOfType * BitPerByte);
}