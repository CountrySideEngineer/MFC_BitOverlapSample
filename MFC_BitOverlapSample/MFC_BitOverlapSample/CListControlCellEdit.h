#pragma once
#include <afxwin.h>

/**
 *	Edit control to edit content of cell in CListControl.
 */
class CListControlCellEdit : public CEdit
{
	DECLARE_DYNAMIC(CListControlCellEdit);

public:
	CListControlCellEdit();
	virtual ~CListControlCellEdit() {}

protected:
	INT_PTR	m_Row;
	INT_PTR m_Col;
};

