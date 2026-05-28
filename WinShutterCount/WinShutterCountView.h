
// WinShutterCountView.h : interface of the CWinShutterCountView class
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#include "MetadataReader.h"


class CWinShutterCountView : public CFormView
{
protected: // create from serialization only
	CWinShutterCountView();
	DECLARE_DYNCREATE(CWinShutterCountView)

public:
	enum{ IDD = IDD_WINSHUTTERCOUNT_FORM };

// Attributes
public:
	CWinShutterCountDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CWinShutterCountView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	int exampleUsed = -1;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
//	CString m_shutterCount;
//	CListBox m_details;
//	CString m_filePathBox;
	CEdit m_filePathBox;
	CListBox m_details;
	CStatic m_shutterCount;
	afx_msg void OnFileExport();
	afx_msg void OnEditUseexamples();
	afx_msg void OnEditSearchcameramodelongoogle();
	afx_msg void On32774();
	//CStatic m_preview;
	afx_msg void OnBnClickedButton3();
};

#ifndef _DEBUG  // debug version in WinShutterCountView.cpp
inline CWinShutterCountDoc* CWinShutterCountView::GetDocument() const
   { return reinterpret_cast<CWinShutterCountDoc*>(m_pDocument); }
#endif

