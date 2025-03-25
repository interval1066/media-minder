
// MFCDynLayoutDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDynLayoutDemo.h"
#include "MFCDynLayoutDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCDynLayoutDemoDlg dialog

CMFCDynLayoutDemoDlg::CMFCDynLayoutDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCDYNLAYOUTDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDynLayoutDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CMFCDynLayoutDemoDlg::EnableDynamicLayoutHelper(bool const enable)
{
   if (enable && this->IsDynamicLayoutEnabled())
      return;

   this->EnableDynamicLayout(enable ? TRUE : FALSE);

   if (enable) 
      this->LoadDynamicLayoutResource(m_lpszTemplateName);
}

BEGIN_MESSAGE_MAP(CMFCDynLayoutDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_ENABLE_DYNLAYOUT, &CMFCDynLayoutDemoDlg::OnBnClickedCheckEnableDynlayout)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCDynLayoutDemoDlg::OnClickedButton2)
	ON_BN_CLICKED(IDOK2, &CMFCDynLayoutDemoDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CMFCDynLayoutDemoDlg message handlers

BOOL CMFCDynLayoutDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_wp.length = sizeof(WINDOWPLACEMENT);
	RestoreWindowPlacement();

	((CButton*)GetDlgItem(IDC_CHECK_ENABLE_DYNLAYOUT))->SetCheck(BST_CHECKED);
	EnableDynamicLayoutHelper(true);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCDynLayoutDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCDynLayoutDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;

		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCDynLayoutDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCDynLayoutDemoDlg::OnBnClickedOk2()
{
	CString selectedPath;
	CFolderPickerDialog dlg(NULL, OFN_EXPLORER, NULL, 0);

	if (dlg.DoModal() == IDOK) {
		selectedPath = dlg.GetPathName();
		// Use selectedPath, which contains the path of the selected directory
	}
	AfxMessageBox(selectedPath, MB_OK | MB_ICONINFORMATION);
}

void CMFCDynLayoutDemoDlg::OnBnClickedCheckEnableDynlayout()
{
   auto enable = ((CButton*)GetDlgItem(IDC_CHECK_ENABLE_DYNLAYOUT))->GetCheck() == BST_CHECKED;
   
}

void CMFCDynLayoutDemoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	SaveWindowPlacement();
}

void CMFCDynLayoutDemoDlg::SaveWindowPlacement()
{
	// Get the current window placement
	GetWindowPlacement(&m_wp);

	// Save the window placement data (e.g., to the registry or a file)
	// Example using CWinApp::WriteProfileBinary:
	AfxGetApp()->WriteProfileBinary(_T("Settings"), _T("WindowPlacement"), (LPBYTE)&m_wp, sizeof(WINDOWPLACEMENT));
}

void CMFCDynLayoutDemoDlg::RestoreWindowPlacement()
{
	// Read the saved window placement data (e.g., from the registry or a file)
	// Example using CWinApp::GetProfileBinary:
	LPBYTE pData;
	UINT nSize;
	AfxGetApp()->GetProfileBinary(_T("Settings"), _T("WindowPlacement"), &pData, &nSize);

	if (nSize == sizeof(WINDOWPLACEMENT)) {
		// Restore the window placement

		WINDOWPLACEMENT* pwp = (WINDOWPLACEMENT*)pData;
		SetWindowPlacement(pwp);
		free(pData);
	}
}

void CMFCDynLayoutDemoDlg::OnClickedButton2()
{
	AfxMessageBox(_T("Alert"), MB_OK | MB_ICONINFORMATION);
}
