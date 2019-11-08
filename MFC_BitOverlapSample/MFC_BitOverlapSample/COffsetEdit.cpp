// COffestEdit.cpp : 実装ファイル
//

#include "pch.h"
#include "MFC_BitOverlapSample.h"
#include "COffsetEdit.h"
#include "CRegex.h"

CString COffsetEdit::OffsetEditAvailable = _T("01234567890.");

// COffestEdit

IMPLEMENT_DYNAMIC(COffsetEdit, CEdit)

COffsetEdit::COffsetEdit()
	: m_PrevText(_T("0.0"))
{}

COffsetEdit::~COffsetEdit() {}


BEGIN_MESSAGE_MAP(COffsetEdit, CEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, &COffsetEdit::OnEnChange)
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()
// COffestEdit メッセージ ハンドラー

/**
 *	COffsetEditの内容変更(EN_CHANGE)イベントのイベントハンドラ
 */
void COffsetEdit::OnEnChange()
{
	this->UpdateText();
}

/**
 *	エディットボックスの表示を更新する。
 */
void COffsetEdit::UpdateText()
{
	CString CurText = _T("");
	this->GetWindowText(CurText);
	if (CurText == this->m_PrevText) {
		//文字列に変更がない場合には、何もしない。
		return;
	}

	CString CheckedText = CurText.SpanIncluding(COffsetEdit::OffsetEditAvailable);
	if (CheckedText != CurText) {
		/*
		 *	使用不可の文字が入力された場合には、その文字を削除する。
		 */
		INT_PTR StartPos = CheckedText.GetLength();
		CurText.Replace(CurText.Mid(StartPos, 1), _T(""));
		this->SetWindowText(CurText);
	}
}

/**
 *	フォーカスを外れた場合の処理を実施する。
 */
void COffsetEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
}