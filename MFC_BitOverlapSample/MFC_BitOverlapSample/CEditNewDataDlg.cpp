// CEditNewDataDlg.cpp : 実装ファイル
//

#include "pch.h"
#include <afxwin.h>
#include "MFC_BitOverlapSample.h"
#include "CEditNewDataDlg.h"
#include "afxdialogex.h"
#include "CDataTypeInfo.h"
#include "CUtility.h"

// CEditNewDataDlg ダイアログ

IMPLEMENT_DYNAMIC(CEditNewDataDlg, CDialogEx)

CEditNewDataDlg::CEditNewDataDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_INPUT_NEW_DATA_TYPE_DIALOG, pParent)
{
	this->m_DataName = _T("");
	this->m_DataDesc = _T("");
	this->m_Offset = _T("");
	this->m_DataType = 0;
	this->m_DataTypeBuff = NULL;
}

CEditNewDataDlg::~CEditNewDataDlg()
{
}

void CEditNewDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DATA_NAME, this->m_DataNameEdit);
	DDX_Control(pDX, IDC_EDIT_DATA_OFFSET, this->m_OffsetEdit);
	DDX_Control(pDX, IDC_EDIT_DATA_REMARK, this->m_DataDescEdit);
	DDX_Control(pDX, IDC_COMBO_DATA_TYPE, this->m_DataTypeComboBox);
	DDX_Text(pDX, IDC_EDIT_DATA_NAME, this->m_DataName);
	DDX_Text(pDX, IDC_EDIT_DATA_OFFSET, this->m_Offset);
	DDX_Text(pDX, IDC_EDIT_DATA_REMARK, this->m_DataDesc);
	DDX_CBIndex(pDX, IDC_COMBO_DATA_TYPE, (int&)(this->m_DataType));
}


BEGIN_MESSAGE_MAP(CEditNewDataDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CEditNewDataDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CEditNewDataDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEditNewDataDlg メッセージ ハンドラー

BOOL CEditNewDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	//コンボボックスの設定
	CDataTypeInfo* Instance = CDataTypeInfo::GetInstance();
	for (INT_PTR Index = 0; Index < CDataTypeInfo::DATA_TYPE_INFO_NAME_MAX; Index++) {
		this->m_DataTypeComboBox.AddString(Instance->GetTypeName(Index));
	}
	this->m_DataTypeComboBox.SetCurSel(0);
	/*
	 *	コンボボックスを展開した際に、全てのアイテムが表示されるようにするために、
	 *	コンボボックスのサイズを変更する。
	 */
	CRect ComboBoxRect;
	this->m_DataTypeComboBox.GetWindowRect(&ComboBoxRect);
	this->ScreenToClient(&ComboBoxRect);
	ComboBoxRect.bottom = ComboBoxRect.top + 500;	//500：テキトー値
	this->m_DataTypeComboBox.MoveWindow(&ComboBoxRect);

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

/**
 *	ユーザーからのキー入力をキャッチする。
 */
BOOL CEditNewDataDlg::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message) {
		if (VK_RETURN == pMsg->wParam) {
			//ENTERキー押下をキャッチ
			if ((&(this->m_OffsetEdit)) == this->GetFocus()) {
				this->m_OffsetEdit.SendMessage(WM_KILLFOCUS);
				return TRUE;
			}
			else {
				return CDialogEx::PreTranslateMessage(pMsg);
			}
		}
		else if (VK_ESCAPE == pMsg->wParam) {
			return TRUE;
		}
		else {
			return CDialogEx::PreTranslateMessage(pMsg);
		}
	}
	else {
		return CDialogEx::PreTranslateMessage(pMsg);
	}
}

/**
 *	OKボタンのイベントハンドラ
 */
void CEditNewDataDlg::OnBnClickedButtonOk()
{ 
	this->UpdateDataType();
	this->OnOK();
}

/**
 *	キャンセルボタンのイベントハンドラ
 */
void CEditNewDataDlg::OnBnClickedButtonCancel() { this->OnCancel(); }

/**
 *	入力内容をモデルに反映する。
 */
void CEditNewDataDlg::UpdateDataType()
{
	ASSERT(NULL != this->m_DataTypeBuff);

	this->UpdateData();

	this->m_DataTypeBuff->SetDataTypeID(this->m_DataType);
	this->m_DataTypeBuff->SetDataDesc(this->m_DataName);
	this->m_DataTypeBuff->SetRemarks(this->m_DataDesc);

	INT_PTR DataOffset = 0;
	INT_PTR BitOffset = 0;
	CUtility Util;
	Util.ExtractOffset(this->m_Offset, DataOffset, BitOffset);
	this->m_DataTypeBuff->SetDataOffset(DataOffset);
	this->m_DataTypeBuff->SetBitOffset(BitOffset);
}

