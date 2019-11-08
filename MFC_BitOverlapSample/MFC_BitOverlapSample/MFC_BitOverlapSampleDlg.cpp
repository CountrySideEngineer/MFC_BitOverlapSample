
// MFC_BitOverlapSampleDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MFC_BitOverlapSample.h"
#include "MFC_BitOverlapSampleDlg.h"
#include "afxdialogex.h"
#include "CDataType.h"
#include "CDataTypeInfo.h"
#include "CDataOffset.h"
#include "CCheckOffsetOverlap.h"
#include "CEditNewDataDlg.h"
#include "CUtility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBitOverlapSampleDlg ダイアログ



CMFCBitOverlapSampleDlg::CMFCBitOverlapSampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_BITOVERLAPSAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	this->m_DataTypeCollection.RemoveAll();
}

CMFCBitOverlapSampleDlg::~CMFCBitOverlapSampleDlg()
{
	CUtility Util;
	Util.Release(&(this->m_DataTypeCollection));
}

void CMFCBitOverlapSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_DataTypeListView);
}

BEGIN_MESSAGE_MAP(CMFCBitOverlapSampleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RUN_CHECK, &CMFCBitOverlapSampleDlg::OnBnClickedButtonRunCheck)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ITEM, &CMFCBitOverlapSampleDlg::OnBnClickedButtonAddItem)
END_MESSAGE_MAP()


// CMFCBitOverlapSampleDlg メッセージ ハンドラー

BOOL CMFCBitOverlapSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	if (FALSE == this->SetupTable()) {
		return FALSE;
	}
	this->UpdateTable();

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMFCBitOverlapSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCBitOverlapSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCBitOverlapSampleDlg::OnBnClickedButtonRunCheck()
{
}

/**
 *	画面に表示するテーブルの設定を行う。
 */
BOOL CMFCBitOverlapSampleDlg::SetupTable()
{
	return this->SetupDataTypeTable();
}

/**
 *	データタイプテーブルの設定を行う。
 */
BOOL CMFCBitOverlapSampleDlg::SetupDataTypeTable()
{
	//常に行選択で表示する。
	this->m_DataTypeListView.SetExtendedStyle(this->m_DataTypeListView.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	//列のヘッダーを設定する。
	CString ColHeader_No = _T("");
	CString ColHeader_DataType = _T("");
	CString ColHeader_Name = _T("");
	CString ColHeader_Offset = _T("");
	CString ColHeader_Remarks = _T("");
	if ((0 == ColHeader_No.LoadString(IDS_STRING_DATA_TYPE_TABLE_COL_TITLE_NO)) ||
		(0 == ColHeader_DataType.LoadString(IDS_STRING_DATA_TYPE_TABLE_COL_TITLE_DATA_TYPE)) ||
		(0 == ColHeader_Name.LoadString(IDS_STRING_DATA_TYPE_TABLE_COL_TITLE_NAME)) ||
		(0 == ColHeader_Offset.LoadString(IDS_STRING_DATA_TYPE_TABLE_COL_TITLE_OFFSET)) ||
		(0 == ColHeader_Remarks.LoadString(IDS_STRING_DATA_TYPE_TABLE_COL_TITLE_REMARKS)))
	{
		//初期化中にエラー発生→その場で終了！
		CString DataTypeLoadError = _T("");
		if (0 == DataTypeLoadError.LoadString(IDS_STRING_ERROR_WHILE_INIT)) {
			//読み込みエラー：何も表示しない
		}
		AfxMessageBox(DataTypeLoadError, MB_OK | MB_ICONSTOP);
		return FALSE;

	}

	this->m_DataTypeListView.InsertColumn(DATA_TYPE_TABLE_COL_INDEX_NO, ColHeader_No, LVCFMT_CENTER, 100);
	this->m_DataTypeListView.InsertColumn(DATA_TYPE_TABLE_COL_INDEX_DATA_TYPE, ColHeader_DataType, LVCFMT_CENTER, 100);
	this->m_DataTypeListView.InsertColumn(DATA_TYPE_TABLE_COL_INDEX_NAME, ColHeader_Name, LVCFMT_CENTER, 100);
	this->m_DataTypeListView.InsertColumn(DATA_TYPE_TABLE_COL_INDEX_OFFSET, ColHeader_Offset, LVCFMT_CENTER, 100);
	this->m_DataTypeListView.InsertColumn(DATA_TYPE_TABLE_COL_INDEX_REMARKS, ColHeader_Remarks, LVCFMT_CENTER, 100);
	return TRUE;
}

/**
 *	追加ボタンのイベントハンドラ
 */
void CMFCBitOverlapSampleDlg::OnBnClickedButtonAddItem()
{
	this->OpenEditDataTypeDlg();
}

/**
 *	データ追加用のダイアログを開く。
 */
void CMFCBitOverlapSampleDlg::OpenEditDataTypeDlg()
{
	CDataType NewDataType;
	CEditNewDataDlg EditNewItemDlg(this);
	EditNewItemDlg.SetDataTypeStore(&NewDataType);
	INT_PTR EditResult = EditNewItemDlg.DoModal();
	if (IDOK == EditResult) {
		this->AddNewDataType(&NewDataType);
		this->UpdateTable();
	}
	else {
		//OK以外(キャンセル)を選択→何もしない
	}
}

/**
 *	新しいアイテムを追加する。
 */
void CMFCBitOverlapSampleDlg::AddNewDataType(CDataType* Src)
{
	ASSERT(NULL != Src);

	this->m_DataTypeCollection.Add(new CDataType(Src));
}

void CMFCBitOverlapSampleDlg::UpdateTable()
{
	this->m_DataTypeListView.DeleteAllItems();	//一度、全ての内容を破棄する。

	CDataTypeInfo* Instance = CDataTypeInfo::GetInstance();
	for (INT_PTR RowIndex = 0; RowIndex < this->m_DataTypeCollection.GetCount(); RowIndex++) {
		CDataType* DataType = this->m_DataTypeCollection.GetAt(RowIndex);
		CUtility Util;
		CString Offset = Util.SetupOffset(DataType->GetDataOffset(), DataType->GetBitOffset());

		this->m_DataTypeListView.InsertItem(RowIndex, _T(""));
		this->m_DataTypeListView.SetItemText(RowIndex, DATA_TYPE_TABLE_COL_INDEX_DATA_TYPE, Instance->GetTypeName(DataType->GetDataTypeId()));
		this->m_DataTypeListView.SetItemText(RowIndex, DATA_TYPE_TABLE_COL_INDEX_NAME, DataType->GetDataDesc());
		this->m_DataTypeListView.SetItemText(RowIndex, DATA_TYPE_TABLE_COL_INDEX_REMARKS, DataType->GetRemarks());
		this->m_DataTypeListView.SetItemText(RowIndex, DATA_TYPE_TABLE_COL_INDEX_OFFSET, Offset);

	}
}