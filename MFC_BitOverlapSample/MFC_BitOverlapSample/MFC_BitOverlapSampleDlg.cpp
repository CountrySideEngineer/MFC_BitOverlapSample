
// MFC_BitOverlapSampleDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MFC_BitOverlapSample.h"
#include "MFC_BitOverlapSampleDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "CDataType.h"
#include "CDataTypeInfo.h"
#include "CDataOffset.h"
#include "CCheckOffsetOverlap.h"
#include "CEditNewDataDlg.h"
#include "CAddDataTypeInfoCommand.h"
#include "CDeleteDataTypeInfoCommand.h"
#include "CEditDataTypeCommand.h"
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
	DDX_Control(pDX, IDC_BUTTON_ADD_ITEM, m_AddItemButton);
	DDX_Control(pDX, IDC_BUTTON_DELETE_ITEM, m_DeleteItemButton);
	DDX_Control(pDX, IDC_BUTTON_CHECK_ITEM, m_ValidateItemButton);
	DDX_Control(pDX, IDC_BUTTON_EXPORT_DATA, m_ExportDataInfoButton);
	DDX_Control(pDX, IDC_BUTTON_EDIT_DATA, m_EditDataButton);
}

BEGIN_MESSAGE_MAP(CMFCBitOverlapSampleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RUN_CHECK, &CMFCBitOverlapSampleDlg::OnBnClickedButtonRunCheck)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ITEM, &CMFCBitOverlapSampleDlg::OnBnClickedButtonAddItem)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ITEM, &CMFCBitOverlapSampleDlg::OnBnClickedButtonDeleteItem)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_DATA, &CMFCBitOverlapSampleDlg::OnBnClickedButtonEditData)
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

	this->UpdateView();

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

	this->m_DataTypeListView.InsertColumn(1, ColHeader_No, LVCFMT_RIGHT, 100);	//No.
	this->m_DataTypeListView.InsertColumn(DATA_TYPE_TABLE_COL_INDEX_DATA_TYPE, ColHeader_DataType, LVCFMT_CENTER, 100);	//データ型名
	this->m_DataTypeListView.InsertColumn(DATA_TYPE_TABLE_COL_INDEX_NAME, ColHeader_Name, LVCFMT_LEFT, 100);	//データ型の説明
	this->m_DataTypeListView.InsertColumn(DATA_TYPE_TABLE_COL_INDEX_OFFSET, ColHeader_Offset, LVCFMT_RIGHT, 100);	//オフセット
	this->m_DataTypeListView.InsertColumn(DATA_TYPE_TABLE_COL_INDEX_REMARKS, ColHeader_Remarks, LVCFMT_LEFT, 100);	//備考
	/*
	 *	各列のヘッダーを中央寄せ、各列の要素はそれぞれに設定したい。
	 *	そのため、ヘッダーのみ設定を変更する。
	 *		→	検討の結果、実現できないことが判明。
	 *			検討の結果は下記(アプリケーションとしては不要なコードだが、検討結果として残しておく)。
	 */
	//for (INT_PTR Index = DATA_TYPE_TABLE_COL_INDEX_NO; Index < DATA_TYPE_TABLE_COL_INDEX_MAX; Index++) {
	//	HDITEM HeaderItem;
	//	CHeaderCtrl* HeaderCtrl = this->m_DataTypeListView.GetHeaderCtrl();
	//	HeaderCtrl->GetItem(Index, &HeaderItem);
	//	HeaderItem.mask |= HDI_FORMAT;
	//	HeaderItem.fmt &= ~HDF_JUSTIFYMASK;
	//	HeaderItem.fmt |= HDF_CENTER;
	//	HeaderCtrl->SetItem(Index, &HeaderItem);
	//}
	return TRUE;
}

/**
 *	追加ボタンのイベントハンドラ
 */
void CMFCBitOverlapSampleDlg::OnBnClickedButtonAddItem()
{
	this->EditNewDataTypeInfo();
}

/**
 *	削除ボタンのイベントハンドラ
 */
void CMFCBitOverlapSampleDlg::OnBnClickedButtonDeleteItem()
{
	this->DeleteDataTypeInfo();
}

/**
 *	編集ボタンのイベントハンドラ
 */
void CMFCBitOverlapSampleDlg::OnBnClickedButtonEditData()
{
	this->EditDataTypeInfo();
}

/**
 *	新規データ型情報を追加する。
 */
void CMFCBitOverlapSampleDlg::EditNewDataTypeInfo()
{
	CDataType DataType;
	CEditNewDataDlg EditNewDataDlg;
	EditNewDataDlg.SetDataType(&DataType);
	if (IDOK == EditNewDataDlg.DoModal()) {
		this->EditNewDataTypeInfo(&DataType);
		this->UpdateView();
	}
	else {
		//OK以外が選択された場合には、何もしない。
	}
}

/**
 *	データの追加コマンドを実行する。
 *
 *	@param[in]	DataType	追加したいデータ型情報へのポインタ
 */
void CMFCBitOverlapSampleDlg::EditNewDataTypeInfo(CDataType* DataType)
{
	ASSERT(NULL != DataType);

	CAddDataTypeInfoCommand* Command = new CAddDataTypeInfoCommand();
	Command->SetReceiver(&(this->m_DataTypeCollection));
	Command->SetDataType(DataType);
	this->RunCommand(Command);
}

/**
 *	データ型処理を削除する。
 */
void CMFCBitOverlapSampleDlg::DeleteDataTypeInfo()
{
	INT_PTR CurSel = this->m_DataTypeListView.GetNextItem(-1, LVNI_SELECTED);
	if (CurSel < 0) {
		/*
		 *	アイテムが選択されていない場合は、削除処理を実施しない。
		 *	代替処理として、エラーメッセージを表示する。
		 */
		CString ErrMessage = _T("");
		if (0 == ErrMessage.LoadString(IDS_STRING_ERROR_DEL_NO_ROW_SELECTED)) {
			ErrMessage.LoadString(IDS_STRING_ERROR_WHILE_LOAD_STRING_TABLE);
		}
		AfxMessageBox(ErrMessage, MB_OK | MB_ICONSTOP);
		return;
	}
	else {
		this->DeleteDataTypeInfo(CurSel);
		this->UpdateView();
	}
}

/**
 *	データ型情報の削除を実施する。
 *
 *	@param	TargetDataIndex	削除するデータのインデックス
 */
void CMFCBitOverlapSampleDlg::DeleteDataTypeInfo(INT_PTR TargetDataIndex)
{
	ASSERT(0 <= TargetDataIndex);

	CDeleteDataTypeInfoCommand* Command = new CDeleteDataTypeInfoCommand();
	Command->SetReceiver(&(this->m_DataTypeCollection));
	Command->SetTargetIndex(TargetDataIndex);
	this->RunCommand(Command);
}

/**
 *	既存のデータ型情報を編集する。
 *	編集には、編集用画面を表示する。
 */
void CMFCBitOverlapSampleDlg::EditDataTypeInfo()
{
	INT_PTR CurSel = this->m_DataTypeListView.GetNextItem(-1, LVNI_SELECTED);
	if (CurSel < 0) {
		/*
		 *	アイテムが選択されていない場合は、削除処理を実施しない。
		 *	代替処理として、エラーメッセージを表示する。
		 */
		CString ErrMessage = _T("");
		if (0 == ErrMessage.LoadString(IDS_STRING_ERROR_EDIT_NO_ROW_SELECTED)) {
			ErrMessage.LoadString(IDS_STRING_ERROR_WHILE_LOAD_STRING_TABLE);
		}
		AfxMessageBox(ErrMessage, MB_OK | MB_ICONSTOP);
		return;
	}
	else {
		CDataType* DataTypeToEditSrc = this->m_DataTypeCollection.GetAt(CurSel);
		CDataType* DataTypeToEdit = new CDataType(DataTypeToEditSrc);
		CEditNewDataDlg EditNewDataDlg;
		EditNewDataDlg.SetDataType(DataTypeToEdit);
		if (IDOK == EditNewDataDlg.DoModal()) {
			this->EditDataTypeInfo(CurSel, DataTypeToEdit);
			this->UpdateView();

			CUtility Util;
			Util.Release(&DataTypeToEdit);
		}
		else {
			//OK以外が選択された場合には、何もしない。
		}
	}
}

void CMFCBitOverlapSampleDlg::EditDataTypeInfo(INT_PTR TargetDataIndex, CDataType* DataType)
{
	ASSERT(0 <= TargetDataIndex);
	ASSERT(NULL != DataType);

	CEditDataTypeCommand* Command = new CEditDataTypeCommand();
	Command->SetReceiver(&(this->m_DataTypeCollection));
	Command->SetDataType(DataType);
	Command->SetDataTypeIndex(TargetDataIndex);
	this->RunCommand(Command);
}


/**
 *	画面表示を更新する。
 */
void CMFCBitOverlapSampleDlg::UpdateView()
{
	this->UpdateTable();
	this->UpdateButton();
}

/**
 *	データ型テーブルの表示を更新する。
 */
void CMFCBitOverlapSampleDlg::UpdateTable()
{
	this->m_DataTypeListView.DeleteAllItems();	//一度、全ての内容を破棄する。

	CDataTypeInfo* Instance = CDataTypeInfo::GetInstance();
	for (INT_PTR RowIndex = 0; RowIndex < this->m_DataTypeCollection.GetCount(); RowIndex++) {
		CDataType* DataType = this->m_DataTypeCollection.GetAt(RowIndex);
		CUtility Util;
		CString Offset = Util.SetupOffset(DataType->GetDataOffset(), DataType->GetBitOffset());
		CString DataNo = _T("");
		DataNo.Format(_T("%d"), (int)(RowIndex + 1));

		this->m_DataTypeListView.InsertItem(RowIndex, _T(""));
		this->m_DataTypeListView.SetItemText(RowIndex, DATA_TYPE_TABLE_COL_INDEX_NO, DataNo);
		this->m_DataTypeListView.SetItemText(RowIndex, DATA_TYPE_TABLE_COL_INDEX_DATA_TYPE, Instance->GetTypeName(DataType->GetDataTypeId()));
		this->m_DataTypeListView.SetItemText(RowIndex, DATA_TYPE_TABLE_COL_INDEX_NAME, DataType->GetDataDesc());
		this->m_DataTypeListView.SetItemText(RowIndex, DATA_TYPE_TABLE_COL_INDEX_REMARKS, DataType->GetRemarks());
		this->m_DataTypeListView.SetItemText(RowIndex, DATA_TYPE_TABLE_COL_INDEX_OFFSET, Offset);
	}
}

/**
 *	ボタンの有効/無効を変更する。
 */
void CMFCBitOverlapSampleDlg::UpdateButton()
{
	if (0 < this->m_DataTypeCollection.GetCount()) {
		this->UpdateButton(TRUE);
	}
	else {
		this->UpdateButton(FALSE);
	}
}

/**
 *	画面のボタンの有効/無効を、引数での指定に従って切り替える。
 *
 *	@param	IsEnable	ボタンの有効/無効の設定値
 *						TRUEを設定した場合には有効に、FALSEを設定した場合には無効に設定される。
 */
void CMFCBitOverlapSampleDlg::UpdateButton(BOOL IsEnable)
{
	this->m_DeleteItemButton.EnableWindow(IsEnable);
	this->m_ValidateItemButton.EnableWindow(IsEnable);
	this->m_EditDataButton.EnableWindow(IsEnable);
	this->m_ExportDataInfoButton.EnableWindow(IsEnable);
}

/**
 *	指定されたコマンドを実行する。
 *
 *	@param[in]	Command	実行するコマンドクラスへのポインタ
 *	@param	CommandName	実行するコマンド名
 */
void CMFCBitOverlapSampleDlg::RunCommand(ACommand* Command, CString CommandName)
{
	if (TRUE == this->m_CommandManager.ExecuteCommand(Command)) {
		TRACE(_T("Command : OK (%s)\n"), CommandName);
	}
	else {
		TRACE(_T("Command : NG (%s)\n"), CommandName);
	}
}