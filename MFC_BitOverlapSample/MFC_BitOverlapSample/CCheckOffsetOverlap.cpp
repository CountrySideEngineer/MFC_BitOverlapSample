#include "pch.h"
#include "CCheckOffsetOverlap.h"

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CCheckOffsetOverlap::CCheckOffsetOverlap()
	: m_DataArray(NULL)
{}

/**
 *	�f�X�g���N�^
 */
CCheckOffsetOverlap::~CCheckOffsetOverlap()
{
	if (NULL != this->m_DataArray) {
		delete[] this->m_DataArray;
		this->m_DataArray = NULL;
	}
}

/**
 *	�I�t�Z�b�g�l�̏d���m�F�����{����B
 *
 *	@param[in]	DataToCheck	�m�F�Ώۂ̃I�t�Z�b�g���
 *	@return	�f�[�^�̃I�t�Z�b�g���ɏd�����Ȃ����TRUE���A�d���������FALSE��Ԃ��B
 */
BOOL CCheckOffsetOverlap::RunCheck(const CArray<CDataOffset>& DataToCheck)
{
	INT_PTR DataSize = this->GetDataSize(DataToCheck);
	this->AllocData(DataSize);
	BOOL bCheckResult = this->CheckOverlap(DataToCheck);

	return bCheckResult;
}

/**
 *	�d���m�F�ΏۂƂȂ�f�[�^�̃T�C�Y���擾����B
 *
 *	@param[in]	DataToCheck	�m�F�Ώۂ̃I�t�Z�b�g���
 *	@return	�d���m�F�ΏۂƂȂ�f�[�^�̃T�C�Y(���[�h�P��)
 */
INT_PTR CCheckOffsetOverlap::GetDataSize(const CArray<CDataOffset>& DataToCheck)
{
	INT_PTR MaxDataSize = 0;

	for (INT_PTR Index = 0; Index < DataToCheck.GetCount(); Index++) {
		CDataOffset DataItem = DataToCheck.GetAt(Index);
		INT_PTR DataSize = DataItem.GetDataOffset() +
			(DataItem.GetBitOffset() + DataItem.GetDataSize()) / 16;	//16:WORD�^�̃r�b�g�T�C�Y
		if (MaxDataSize < DataSize) {
			MaxDataSize = DataSize;
		}
	}
	return (MaxDataSize + 1);
}

/**
 *	�d���m�F�̂��߂ɕK�v�ȃf�[�^�̈���m�ۂ���B
 *
 *	@param	DataSize	�d���m�F�̂��߂ɕK�v�ȗ̈�̃T�C�Y(���[�h�P��)
 */
void CCheckOffsetOverlap::AllocData(const INT_PTR DataSize)
{
	this->m_DataArray = new WORD[DataSize];
	for (INT_PTR Index = 0; Index < DataSize; Index++) {
		this->m_DataArray[Index] = 0;
	}
}

/**
 *	�d���m�F�����s����B
 *
 *	@param[in]	DataToCheck	�d���m�F�Ώۂ̃f�[�^�̔z��
 *	@return	�d���m�F���ʁB
 *			�d�����Ȃ����TRUE���A�����FALSE��Ԃ��B
 */
BOOL CCheckOffsetOverlap::CheckOverlap(const CArray<CDataOffset>& DataToCheck)
{
	BOOL CheckResult = FALSE;
	for (INT_PTR Index = 0; Index < DataToCheck.GetCount(); Index++) {
		CDataOffset DataToCheckItem = DataToCheck.GetAt(Index);
		CheckResult = this->CheckOverlap(DataToCheckItem);
		if (FALSE == CheckResult) {
			break;
		}
	}
	return CheckResult;
}

/**
 *	1�̃I�t�Z�b�g���ɑ΂��āA�f�[�^�̏d�����m�F����B
 *
 *	@param[in]	DataToCheck	�m�F�Ώۂ̃f�[�^
 *	@return	�d���m�F���ʁB
 *			�d�����Ȃ����TRUE���A�����FALSE��Ԃ��B
 */
BOOL CCheckOffsetOverlap::CheckOverlap(const CDataOffset& DataToCheck)
{
	DWORD BitData = CDataOffset::TypeBitMaskMap[DataToCheck.GetDataType()];
	if (CDataOffset::DataBitArray_32bit == BitData) {
		return this->CheckOverlap<DWORD>(DataToCheck);
	}
	else {
		return this->CheckOverlap<WORD>(DataToCheck);
	}
}

/**
 *	1�̃I�t�Z�b�g���ɑ΂��āA�f�[�^�̏d���̗L�����m�F����B
 *	�f�[�^�̏d�����Ȃ������ꍇ�́A�f�[�^�d���m�F�̂��߂̗̈���X�V����B
 *
 *	@param[in]	DataToCheck	�m�F�Ώۂ̃f�[�^
 *	@return	�d���m�F���ʁB
 *			�d�����Ȃ����TRUE���A�����FALSE��Ԃ��B
 */
template <typename T>
BOOL CCheckOffsetOverlap::CheckOverlap(const CDataOffset& DataToCheck)
{
	INT_PTR DataOffset = DataToCheck.GetDataOffset();
	T* Data = (T*)(&(this->m_DataArray[DataOffset]));
	INT_PTR BitOffset = DataToCheck.GetBitOffset();
	T BitArray = CDataOffset::TypeBitMaskMap[DataToCheck.GetDataType()];
	T BitData = BitArray << BitOffset;
	BOOL CheckResult = FALSE;
	if (0 == ((*Data) & BitData)) {
		CheckResult = TRUE;
	}
	else {
		CheckResult = FALSE;
	}
	*Data |= BitData;

	return CheckResult;
}