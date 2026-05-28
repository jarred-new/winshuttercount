
// WinShutterCountView.cpp : implementation of the CWinShutterCountView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "WinShutterCount.h"
#endif

#include "WinShutterCountDoc.h"
#include "WinShutterCountView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_EXAMPLE1 10250
#define ID_EXAMPLE2 10251


// CWinShutterCountView

IMPLEMENT_DYNCREATE(CWinShutterCountView, CFormView)

BEGIN_MESSAGE_MAP(CWinShutterCountView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON1, &CWinShutterCountView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWinShutterCountView::OnBnClickedButton2)
	ON_COMMAND(ID_FILE_EXPORT, &CWinShutterCountView::OnFileExport)
	ON_COMMAND(ID_EDIT_USEEXAMPLES, &CWinShutterCountView::OnEditUseexamples)
	ON_COMMAND(ID_EDIT_SEARCHCAMERAMODELONGOOGLE, &CWinShutterCountView::OnEditSearchcameramodelongoogle)
	ON_COMMAND(32774, &CWinShutterCountView::On32774)
	ON_BN_CLICKED(IDC_BUTTON3, &CWinShutterCountView::OnBnClickedButton3)
END_MESSAGE_MAP()

// CWinShutterCountView construction/destruction

CWinShutterCountView::CWinShutterCountView()
	: CFormView(CWinShutterCountView::IDD)
{
	// TODO: add construction code here

}

CWinShutterCountView::~CWinShutterCountView()
{
}

void CWinShutterCountView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_STATIC_COUNT, m_shutterCount);
	//  DDX_Control(pDX, IDC_LIST1, m_details);
	//  DDX_Text(pDX, IDC_EDIT1, m_filePathBox);
	DDX_Control(pDX, IDC_EDIT1, m_filePathBox);
	DDX_Control(pDX, IDC_LIST1, m_details);
	DDX_Control(pDX, IDC_STATIC_COUNT, m_shutterCount);
	//DDX_Control(pDX, IDC_IMAGE_PREVIEW, m_preview);
}

BOOL CWinShutterCountView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CWinShutterCountView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate(); // Or CView::OnInitialUpdate()

	// 1. Get the total size of the document/view content
	CSize totalSize = GetTotalSize();

	// 2. Get the size of the client area (what's visible)
	CRect clientRect;
	GetClientRect(&clientRect);

	// 3. Calculate center point
	int x = (totalSize.cx - clientRect.Width()) / 2;
	int y = (totalSize.cy - clientRect.Height()) / 2;

	// 4. Scroll to center
	ScrollToPosition(CPoint(x, y));
}

void CWinShutterCountView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWinShutterCountView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWinShutterCountView diagnostics

#ifdef _DEBUG
void CWinShutterCountView::AssertValid() const
{
	CFormView::AssertValid();
}

void CWinShutterCountView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CWinShutterCountDoc* CWinShutterCountView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinShutterCountDoc)));
	return (CWinShutterCountDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinShutterCountView message handlers


BOOL CWinShutterCountView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == 'S' && (GetKeyState(VK_CONTROL) & 0x8000))
		{
			// This will remove "save" as this is not included in this app...
			return TRUE;
		}
		if (pMsg->wParam == 'O' && (GetKeyState(VK_CONTROL) & 0x8000))
		{
			// Also, open too...
			return TRUE;
		}
		if (pMsg->wParam == 'E' && (GetKeyState(VK_CONTROL) & 0x8000))
		{
			this->OnFileExport();
			return TRUE;
		}
	}

	return CFormView::PreTranslateMessage(pMsg);
}

CString sFilePath = _T("");
void CWinShutterCountView::OnBnClickedButton1()
{
	// browse button
	CFileDialog fileDlg(TRUE, _T("jpg"), _T(""), OFN_EXPLORER | OFN_READONLY,
		_T("JPG Files (*.jpg)|*.jpg|Canon Raw (*.crw; *.cr2; *.cr3; *.craw)|*.crw; *.cr2; *.cr3; *.craw|Nikon Raw (*.nef; *.nrw)|*.nef; *.nrw|Sony Alpha Raw (*.arw; *.srf; *.sr2)|*.arw; *.srf; *.sr2|Fujifilm Raw (*.raf)|*.raf|Olympus/OM Raw (*.orf; *.ori)|*.orf; *.ori|Lumix Raw (*.rw2)|*.rw2|Hasselblad Raw (*.3fr; *.fff)|*.3fr; *.fff|Pentax Raw (*.pef; *.dng)|*.pef; *.dng|Kodak Raw (*.dcr; *.k25; *.kdc)|*.dcr; *.k25; *.kdc|Phase One Raw (*.iiq)|*.iiq|Adobe DNG/Generic Raw (*.dng)|*.dng|All Files (*.*)|*.*|"), this);

	if (fileDlg.DoModal() == IDOK)
	{
		CString filepath;
		filepath = fileDlg.GetPathName();
		m_filePathBox.SetWindowTextW(filepath);
		m_filePathBox.UpdateData();
		m_filePathBox.GetWindowTextW(sFilePath);
		UpdateWindow();
		exampleUsed = 0;
	}
}


void CWinShutterCountView::OnBnClickedButton2()
{
	// Start data button

	// Create the image object
	CImage image;
	HRESULT hr = image.Load(sFilePath); // Path to JPG

	CMetadataReader cmr;
	CString shuttercount = cmr.GetShutterCount(sFilePath);

	if (shuttercount.IsEmpty())
		m_shutterCount.SetWindowTextW(L"No Shutter Count can be found on this picture...");
	else
		m_shutterCount.SetWindowTextW(shuttercount);

	m_shutterCount.UpdateData();

	m_details.ResetContent();

	m_details.AddString(cmr.GetCameraModel(sFilePath));
	m_details.AddString(cmr.GetDate(sFilePath));
	m_details.AddString(cmr.GetAperture(sFilePath));
	m_details.AddString(cmr.GetShutterSpeed(sFilePath));
	m_details.AddString(cmr.GetISO(sFilePath));
	m_details.AddString(cmr.GetFocalLength(sFilePath));
	m_details.AddString(cmr.GetSize(sFilePath));
	m_details.UpdateData();

	UpdateWindow();
}

CString example1Path;
CString example2Path;
void CWinShutterCountView::OnEditUseexamples()
{
	// TODO: Add your command handler code here
	CTaskDialog examplesDialog(_T("Pick an example image to test..."), _T("Here are some examples:"), _T("Examples"), TDCBF_CLOSE_BUTTON);
	examplesDialog.AddCommandControl(ID_EXAMPLE1, L"Example 1", 1, NULL);
	examplesDialog.AddCommandControl(ID_EXAMPLE2, L"Example 2", 1, NULL);

	INT_PTR dialogResult = examplesDialog.DoModal();
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strAppPath(szPath);
	int nSlash = strAppPath.ReverseFind(_T('\\'));
	CString strDir = strAppPath.Left(nSlash + 1);

	if (dialogResult == ID_EXAMPLE1) {
		example1Path = strDir + _T("examples\\nikon.jpg");
		CMetadataReader cmr;
		m_shutterCount.SetWindowTextW(cmr.GetShutterCount(example1Path));
		m_shutterCount.UpdateData();

		m_details.ResetContent();

		m_details.AddString(cmr.GetCameraModel(example1Path));
		m_details.AddString(cmr.GetDate(example1Path));
		m_details.AddString(cmr.GetAperture(example1Path));
		m_details.AddString(cmr.GetShutterSpeed(example1Path));
		m_details.AddString(cmr.GetISO(example1Path));
		m_details.AddString(cmr.GetFocalLength(example1Path));
		m_details.AddString(cmr.GetSize(example1Path));
		m_details.UpdateData();

		exampleUsed = 1;
		UpdateWindow();
	}
	else if (dialogResult == ID_EXAMPLE2) {
		example2Path = strDir + _T("examples\\sony.jpg");
		CMetadataReader cmr;
		m_shutterCount.SetWindowTextW(cmr.GetShutterCount(example2Path));
		m_shutterCount.UpdateData();

		m_details.ResetContent();

		m_details.AddString(cmr.GetCameraModel(example2Path));
		m_details.AddString(cmr.GetDate(example2Path));
		m_details.AddString(cmr.GetAperture(example2Path));
		m_details.AddString(cmr.GetShutterSpeed(example2Path));
		m_details.AddString(cmr.GetISO(example2Path));
		m_details.AddString(cmr.GetFocalLength(example2Path));
		m_details.AddString(cmr.GetSize(example2Path));
		m_details.UpdateData();

		exampleUsed = 2;
		UpdateWindow();
	}
}


void CWinShutterCountView::OnEditSearchcameramodelongoogle()
{
	CMetadataReader cmr;
	CString modelToSearch = NULL;
	if (exampleUsed == 0) {
		modelToSearch = cmr.GetCameraModelWithoutLabel(sFilePath);
		ShellExecute(NULL, L"open", L"https://www.google.com/search?q=" + modelToSearch, NULL, NULL, SW_SHOWMAXIMIZED);
	}
	else if (exampleUsed == 1) {
		modelToSearch = cmr.GetCameraModelWithoutLabel(example1Path);
		ShellExecute(NULL, L"open", L"https://www.google.com/search?q=" + modelToSearch, NULL, NULL, SW_SHOWMAXIMIZED);
	}
	else if (exampleUsed == 2) {
		modelToSearch = cmr.GetCameraModelWithoutLabel(example2Path);
		ShellExecute(NULL, L"open", L"https://www.google.com/search?q=" + modelToSearch, NULL, NULL, SW_SHOWMAXIMIZED);
	}
}

void CWinShutterCountView::OnFileExport()
{
	CFileDialog fileDlg(FALSE, _T("txt"), _T("export.txt"), OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"), this);

	if (fileDlg.DoModal() == IDOK)
	{
		CString sFilePath2 = fileDlg.GetPathName();
		CStdioFile file;
		CFileException fileException;

		// Attempt to open the file for writing (create a new file or overwrite existing)
		if (!file.Open(sFilePath2, CFile::modeCreate | CFile::modeWrite | CFile::typeText, &fileException))
		{
			// Handle file open error, e.g., display an error message
			TCHAR szError[1024];
			fileException.GetErrorMessage(szError, sizeof(szError) / sizeof(TCHAR));
			AfxMessageBox(szError);
			return;
		}

		// Get the total number of items in the listbox
		int nItems = m_details.GetCount();
		CString sItem;

		// Loop through each item
		file.WriteString(_T("WinShutterCount Details\n"));
		file.WriteString(_T("File Path: ") + sFilePath + ("\n"));
		if (exampleUsed == 0) {
			CMetadataReader cmr;
			file.WriteString(cmr.GetShutterCount(sFilePath));
		}
		else if (exampleUsed == 1) {
			CMetadataReader cmr;
			file.WriteString(cmr.GetShutterCount(example1Path));
		}
		else if (exampleUsed == 2) {
			CMetadataReader cmr;
			file.WriteString(cmr.GetShutterCount(example2Path));
		}
		for (int i = 0; i < nItems; i++)
		{
			// Get the text of the current item
			m_details.GetText(i, sItem);

			// Write the item string to the file
			// Add a newline character to separate each item in the text file
			file.WriteString(sItem + _T("\n"));
		}

		// Close the file
		file.Close();
	}
}


void CWinShutterCountView::On32774()
{
	// TODO: Add your command handler code here
}


void CWinShutterCountView::OnBnClickedButton3()
{
	if (exampleUsed == 0) {
		ShellExecute(NULL, L"open", sFilePath, NULL, NULL, SW_SHOW);
	}
	if (exampleUsed == 1) {
		ShellExecute(NULL, L"open", example1Path, NULL, NULL, SW_SHOW);
	}
	if (exampleUsed == 2) {
		ShellExecute(NULL, L"open", example2Path, NULL, NULL, SW_SHOW);
	}
}
