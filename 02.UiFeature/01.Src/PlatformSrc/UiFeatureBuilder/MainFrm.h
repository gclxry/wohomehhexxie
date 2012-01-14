
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "FileView.h"
#include "WindowsView.h"
#include "PropertiesWnd.h"
#include "UiFeatureBuilderDoc.h"
#include "UiFeatureBuilderView.h"
#include "ControlsWnd.h"
#include "UiFeatureKernel.h"
#include "LocalImageList.h"
#include "..\..\Inc\IZipFile.h"

class CMainFrame : public CFrameWndEx
{
// ʵ��
public:
	virtual ~CMainFrame();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

	// �������Է����仯����Ҫ����
	void SetPropetryChange();

	ZIP_FILE_VEC* GetZipFileVec() { return &m_LocalImageFileVec; };

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);

private:
	HICON m_hClassViewIcon;
	HICON m_hPropertiesBarIcon;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

public:
	void SetViewCursor(int nCursor);
	void SetView(CUiFeatureBuilderView *pView);
	
protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
//	CFileView         m_wndFileView;
	CWindowsView	  m_wndWindowView;
	CPropertiesWnd    m_wndProperties;
	CControlsWnd      m_wndControls;
	CUiFeatureBuilderView *m_pView;

	bool m_bNeedSave;

private:
//////////////////////////////////////////////////////////////////////////
	// Kernel ���
	HMODULE m_hKernelDll;
	IUiFeatureKernel* m_pUiKernel;
	IPropertySkinManager* m_pSkinMgr;
	CONTROL_REG_MAP* m_pRegControlMap;

	ZIP_FILE_VEC m_LocalImageFileVec;

//////////////////////////////////////////////////////////////////////////
	// �ؼ����
	HMODULE m_hControlDll;

//////////////////////////////////////////////////////////////////////////
	bool m_bInitOk;
	// ���
	int m_nViewCursor;

	// ��ǰ��Ŀ�����ļ�
	CString m_strCurUfpPath;
	CString m_strCurSkinName;
	CString m_strCurSkinDir;

	CString m_strNewUfpPath;
	CString m_strNewSkinName;
	CString m_strNewSkinDir;

private:
	void InitUiFeatureKernel();
	// ����������ʾ�Ŀؼ��ĳ�ʼ��״̬
	void SetProjectInitState(bool bInitOk);

	// ��һ������
	bool OpenSkinProject(bool bIsNew, CString strSkinDir, CString strSkinName);
	// ����
	bool SaveSkinProject(CString strSkinDir, CString strSkinName, bool bNeedErroInfo);
	// ����
	bool CloseSkinProject();

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileClose();
	afx_msg void OnAppExit();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnClose();
};


