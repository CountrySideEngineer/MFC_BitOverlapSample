#include "pch.h"
#include "CCheckOffsetOverlapItem.h"

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CCheckOffsetOverlapItem::CCheckOffsetOverlapItem()
	: m_OverlapDataIndex(0)
	, m_OverlapDataTargetIndex(0)
{}

/**
 *	�r�b�g�̏d�����m�F����B
 *
 *	@param[in]	DataToCheck	�d�����m�F����f�[�^�̈ꗗ
 *	@return	�d�������������ꍇ�ɂ�TRUE���A�d����������Ȃ������ꍇ�ɂ�FALSE��
 *			�Ԃ��B
 */
BOOL CCheckOffsetOverlapItem::CheckOverlap(const CArray<CDataOffset>& DataToCheck)
{
	BOOL CheckResult = FALSE;
	for (INT_PTR Index = 0; Index < DataToCheck.GetCount(); Index++) {
		this->InitData();	//�f�[�^�z��̏�����
		CDataOffset DataToCheckItem = DataToCheck.GetAt(Index);
		DWORD BitData = DataToCheckItem.GetBitMask();
		if (CDataOffset::DataBitArray_32bit == BitData) {
			this->SetBitData<DWORD>(&DataToCheckItem);
		}
		else {
			this->SetBitData<WORD>(&DataToCheckItem);
		}
		for (INT_PTR TargetIndex = Index + 1; TargetIndex < DataToCheck.GetCount(); TargetIndex++) {
			CDataOffset DataToCheckTarget = DataToCheck.GetAt(TargetIndex);
			DWORD BitDataTarget = DataToCheckTarget.GetBitMask();
			if (CDataOffset::DataBitArray_32bit == BitData) {
				CheckResult = this->CheckOverlap<DWORD>(&DataToCheckTarget);
			}
			else {
				CheckResult = this->CheckOverlap<WORD>(&DataToCheckTarget);
			}
			if (TRUE == CheckResult) {
				this->m_OverlapDataIndex = (Index + 1);
				this->m_OverlapDataTargetIndex = (TargetIndex + 1);
				/*
				 *	�d�����Ă���͈͂����������ꍇ�ɂ́A�����ɏ����𔲂���B
				 */
				return CheckResult;
			}
		}
	}
	return CheckResult;
}

/**
 *	�d���m�F�̑ΏۂƂȂ�f�[�^�̃r�b�g�����A�o�b�t�@�ɃZ�b�g����B
 *
 *	@param	DataToCheck	�d���m�F�ΏۂƂȂ�f�[�^���
 *	@return	�f�[�^�̐ݒ肪����Ɋ��������ꍇ�ɂ�TRUE���A���s�����ꍇ�ɂ�FALSE��Ԃ��B
 */
template <typename T>
BOOL CCheckOffsetOverlapItem::SetBitData(CDataOffset* DataToCheck)
{
	T* Data = NULL;
	T BitData = 0;
	this->GetBitData(DataToCheck, &Data, &BitData);
	*Data |= BitData;

	return TRUE;
}

/**
 *	�w�肳�ꂽ�f�[�^�̏d�����m�F����B
 *
 *	@param[in]	DataToCheckTarget	�d���m�F�Ώۂ̃f�[�^���
 *	@return	�I�t�Z�b�g�͈͂̏d�������������ꍇ�ɂ�TRUE���A�d����������Ȃ������ꍇ�ɂ�
 *			FALSE��Ԃ��B
 */
template <typename T>
BOOL CCheckOffsetOverlapItem::CheckOverlap(CDataOffset* DataToCheckTaget)
{
	T* Data = NULL;
	T BitData = 0;
	this->GetBitData(DataToCheckTaget, &Data, &BitData);
	if (0 == ((*Data) & BitData)) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

/**
 *	�f�[�^�z�񂩂�A�w�肳�ꂽ�I�t�Z�b�g���ɑΉ�����f�[�^���擾����B
 *
 *	@param[in]	DataToCheckTarget	�I�t�Z�b�g���ւ̃|�C���^
 *	@param[in,out]	Data	�I�t�Z�b�g��񂪎w�肷��o�b�t�@�ւ̃|�C���^
 *	@param[out]	BitData	�I�t�Z�b�g��񂪎����r�b�g�z��
 */
template <typename T>
void CCheckOffsetOverlapItem::GetBitData(CDataOffset* DataToCheck, T** Data, T* BitData)
{
	INT_PTR DataOffset = DataToCheck->GetDataOffset();
	*Data = (T*)(&(this->m_DataArray[DataOffset]));
	INT_PTR BitOffset = DataToCheck->GetBitOffset();
	T BitArray = DataToCheck->GetBitMask();
	*BitData = BitArray << BitOffset;
}
