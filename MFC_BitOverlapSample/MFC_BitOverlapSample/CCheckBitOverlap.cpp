#include "pch.h"
#include "CCheckBitOverlap.h"
#include "CDataTypeInfo.h"
#include "CUtility.h"

/**
 *	�f�[�^�͈̔͐ݒ�ɏd�����Ȃ����̊m�F�����{����B
 *
 *	@param[in]	DataToCheck	�m�F�Ώۂ̃f�[�^�ݒ�ւ̃|�C���^
 *	@return	�f�[�^�̐ݒ���e�ɏd�����������ꍇ�ɂ�TRUE���A�d�����Ȃ������ꍇ�ɂ�FALSE��
 *			�Ԃ��B
 */
BOOL CCheckBitOverlap::CheckOverlap(const CArray<CDataType*>* DataToCheck)
{
	ASSERT(NULL != DataToCheck);

	BOOL CheckResult = FALSE;
	for (INT_PTR TargetIndex = 0; TargetIndex < DataToCheck->GetCount(); TargetIndex++) {
		CDataType* Target = DataToCheck->GetAt(TargetIndex);
		for (INT_PTR CompIndex = (TargetIndex + 1); CompIndex < DataToCheck->GetCount(); CompIndex++) {
			CDataType* Comp = DataToCheck->GetAt(CompIndex);
			if (TRUE == this->CheckOverlap(Target, Comp)) {
				CheckResult = TRUE;
				break;
			}
		}
	}
	return CheckResult;
}

/**
 *	�w�肳�ꂽ2�̃f�[�^�^���/�I�t�Z�b�g�Ŏw�肵���͈͂��A�d�����Ă��邩�ۂ����m�F����B
 *
 *	@param[in]	Target	�m�F�Ώۂ̃f�[�^�^���ւ̃|�C���^
 *	@param[in]	Comp	�m�F�ΏۂƔ�r����f�[�^�^���ւ̃|�C���^
 *	@return	
 */
BOOL CCheckBitOverlap::CheckOverlap(const CDataType* Target, const CDataType* Comp)
{
	ASSERT(NULL != Target);
	ASSERT(NULL != Comp);

	CDataTypeInfo* Instance = CDataTypeInfo::GetInstance();
	CUtility Util;
	INT_PTR TargetOffset =
		Util.Type2Bit<BYTE>(Target->GetDataOffset()) + Target->GetBitOffset();
	INT_PTR CompOffset =
		Util.Type2Bit<BYTE>(Comp->GetDataOffset()) + Comp->GetBitOffset();

	BOOL CheckResult = FALSE;
	if (TargetOffset < CompOffset) {
		INT_PTR BitLen = Instance->GetBitLen(Target->GetDataTypeId());
		if ((TargetOffset + BitLen - 1) < CompOffset) {
			//�d���Ȃ�
			CheckResult = FALSE;
		}
		else {
			CheckResult = TRUE;
		}
	}
	else if (CompOffset < TargetOffset) {
		INT_PTR BitLen = Instance->GetBitLen(Comp->GetDataTypeId());
		if ((CompOffset + BitLen - 1) < TargetOffset) {
			//�d���Ȃ�
			CheckResult = FALSE;
		}
		else {
			CheckResult = TRUE;
		}
	}
	else {
		//�f�[�^�J�n�ʒu���d��
		CheckResult = TRUE;
	}
	return CheckResult;
}