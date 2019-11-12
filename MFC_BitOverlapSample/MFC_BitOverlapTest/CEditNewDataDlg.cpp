#include "CEditNewDataDlg.h"

INT_PTR CEditNewDataDlg::DoModalResult = 0;

CEditNewDataDlg::CEditNewDataDlg(CWnd* parent)
	: m_DataTypeBuff(NULL)
{}

CEditNewDataDlg::~CEditNewDataDlg() {}

INT_PTR CEditNewDataDlg::DoModal()
{
	return DoModalResult;
}