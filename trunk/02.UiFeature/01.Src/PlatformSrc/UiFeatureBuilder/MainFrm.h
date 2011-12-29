
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "FileView.h"
#include "WindowsView.h"
#include "PropertiesWnd.h"
#include "ControlsWnd.h"
#include "UiFeatureKernel.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CFileView         m_wndFileView;
	CWindowsView    m_wndWindowView;
	CPropertiesWnd    m_wndProperties;
	CControlsWnd      m_wndControls;

private:
//////////////////////////////////////////////////////////////////////////
	// Kernel ���
	HMODULE m_hKernelDll;
	IKernelWindow* m_pKernelWindow;
	IPropertySkinManager* m_pSkinMgr;
	CONTROL_REG_MAP* m_pRegControlMap;

//////////////////////////////////////////////////////////////////////////
	// �ؼ����
	HMODULE			m_hControlDll;

//////////////////////////////////////////////////////////////////////////
	bool	m_bInitOk;

	CString m_strSkinName;
	CString m_strSkinDir;
	// ��ǰ��Ŀ�����ļ�
	CString m_strCurUfpPath;
	CString m_strOpenUfpPath;

private:
	void InitUiFeatureKernel();
	bool InitProject();

	bool InitResourceXml(CString strXmlFile);
	bool InitControlsXml(CString strXmlFile);
	bool InitWindowsXml(CString strXmlFile);
	bool InitLayoutXml(CString strXmlFile);


// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnAppExit();
	afx_msg void OnFileClose();
};

