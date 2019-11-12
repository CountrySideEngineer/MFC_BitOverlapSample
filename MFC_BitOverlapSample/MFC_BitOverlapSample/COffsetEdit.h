#pragma once
// COffestEdit

class COffsetEdit : public CEdit
{
	DECLARE_DYNAMIC(COffsetEdit)

public:
	COffsetEdit();
	virtual ~COffsetEdit();

protected:
	void	UpdateText();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnEnChange();
	afx_msg void OnKillFocus(CWnd* pNewWnd);

protected:
	CString m_PrevText;

protected:

	static CString OffsetEditAvailable;
};


