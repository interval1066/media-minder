#pragma once

// CMFCDynLayoutDemoDlg dialog
class CMFCDynLayoutDemoDlg : public CDialogEx
{
	WINDOWPLACEMENT m_wp;
	void SaveWindowPlacement();
	void RestoreWindowPlacement();

	void EnableDynamicLayoutHelper(bool const enable);

public:
	CMFCDynLayoutDemoDlg(CWnd* pParent = NULL);	// standard constructor

	afx_msg void OnBnClickedCheckEnableDynlayout();
	afx_msg void OnDestroy();
	afx_msg void OnClickedButton2();

	afx_msg void OnBnClickedOk2();
	CEdit m_DirPath;
	CListBox m_DirList;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDYNLAYOUTDEMO_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();

	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
