#include "pch.h"
#include "CCheckBitOverlap.h"
#include "CDataTypeInfo.h"
#include "CUtility.h"

/**
 *	データの範囲設定に重複がないかの確認を実施する。
 *
 *	@param[in]	DataToCheck	確認対象のデータ設定へのポインタ
 *	@return	データの設定内容に重複があった場合にはTRUEを、重複がなかった場合にはFALSEを
 *			返す。
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
 *	指定された2つのデータ型情報/オフセットで指定した範囲が、重複しているか否かを確認する。
 *
 *	@param[in]	Target	確認対象のデータ型情報へのポインタ
 *	@param[in]	Comp	確認対象と比較するデータ型情報へのポインタ
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
			//重複なし
			CheckResult = FALSE;
		}
		else {
			CheckResult = TRUE;
		}
	}
	else if (CompOffset < TargetOffset) {
		INT_PTR BitLen = Instance->GetBitLen(Comp->GetDataTypeId());
		if ((CompOffset + BitLen - 1) < TargetOffset) {
			//重複なし
			CheckResult = FALSE;
		}
		else {
			CheckResult = TRUE;
		}
	}
	else {
		//データ開始位置が重複
		CheckResult = TRUE;
	}
	return CheckResult;
}