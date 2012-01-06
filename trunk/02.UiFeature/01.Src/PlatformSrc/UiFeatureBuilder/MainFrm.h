
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "FileView.h"
#include "WindowsView.h"
#include "PropertiesWnd.h"
#include "UiFeatureBuilderDoc.h"
#include "UiFeatureBuilderView.h"
#include "ControlsWnd.h"
#include "UiFeatureKernel.h"

class CMainFrame : public CFrameWndEx
{
// 实现
public:
	virtual ~CMainFrame();

	void SetViewCursor(int nCursor);
	void SetView(CUiFeatureBuilderView *pView);
	void ResetShowWindow(IWindowBase *pCurrentWnd);
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
//	CFileView         m_wndFileView;
	CWindowsView	  m_wndWindowView;
	CPropertiesWnd    m_wndProperties;
	CControlsWnd      m_wndControls;
	CUiFeatureBuilderView *m_pView;

private:
//////////////////////////////////////////////////////////////////////////
	// Kernel 相关
	HMODULE m_hKernelDll;
	IUiFeatureKernel* m_pUiKernel;
	IPropertySkinManager* m_pSkinMgr;
	CONTROL_REG_MAP* m_pRegControlMap;

//////////////////////////////////////////////////////////////////////////
	// 控件相关
	HMODULE			m_hControlDll;

//////////////////////////////////////////////////////////////////////////
	bool	m_bInitOk;
	// 光标
	int m_nViewCursor;

	// 当前项目工程文件
	CString m_strCurUfpPath;
	CString m_strCurSkinName;
	CString m_strCurSkinDir;

	CString m_strNewUfpPath;
	CString m_strNewSkinName;
	CString m_strNewSkinDir;

private:
	void InitUiFeatureKernel();
	// 设置所有显示的控件的初始化状态
	void SetProjectInitState(bool bInitOk);

	// 打开一个工程
	bool OpenSkinProject(bool bIsNew, CString strSkinDir, CString strSkinName);
	// 保存
	bool SaveSkinProject(CString strSkinDir, CString strSkinName, bool bNeedErroInfo);
	// 保存
	bool CloseSkinProject();

// 生成的消息映射函数
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
	afx_msg void OnFileClose();
	afx_msg void OnAppExit();
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


