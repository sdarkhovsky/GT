
// GTMFCUIDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CGTMFCUIDlg dialog
class CGTMFCUIDlg : public CDialogEx
{
// Construction
public:
	CGTMFCUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GTMFCUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CRichEditCtrl m_rich_edit_ctrl;
    afx_msg void OnBnClickedButton1();
};
