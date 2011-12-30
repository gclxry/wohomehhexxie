
#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "MainFrm.h"
#include "UiFeatureDefs.h"
#include "CreateNewSkinProject.h"
#include "..\..\Inc\ICommonFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CMainFrame::InitUiFeatureKernel()
{
	USES_CONVERSION;
	string strPath = PathHelper(NAME_KERNEL_DLL);
	CString strKernelPath = A2W(strPath.c_str());
	m_hKernelDll = ::LoadLibrary(strKernelPath);
	if (m_hKernelDll == NULL)
	{
		AfxMessageBox(_T("找不到UiFeature内核DLL！"), MB_OK | MB_ICONERROR);
		return;
	}

	GETKERNELWINDOWINTERFACE GetKernel = (GETKERNELWINDOWINTERFACE)::GetProcAddress(m_hKernelDll, "GetKernelWindowInterface");
	if (GetKernel == NULL)
	{
		AfxMessageBox(_T("找不到UiFeature内核DLL的【GetKernelWindowInterface】函数！"), MB_OK | MB_ICONERROR);
		return;
	}

	m_pKernelWindow = GetKernel();
	if (m_pKernelWindow == NULL)
	{
		AfxMessageBox(_T("找不到UiFeature内核DLL的【IKernelWindow】接口！"), MB_OK | MB_ICONERROR);
		return;
	}
	m_pSkinMgr = m_pKernelWindow->GetSkinManager();

	m_wndWindowView.Init(m_pKernelWindow, m_wndProperties.GetPropetryCtrl());
	m_wndProperties.Init(m_pKernelWindow, m_wndWindowView.GetViewTreeCtrl());

	// 加载控件显示数据
	m_pRegControlMap = m_pKernelWindow->BuilderRegisterControl();
	// 显示控件
	m_wndControls.SetControlList(m_pRegControlMap);

	m_bInitOk = true;
	SetProjectInitState(false);
}

void CMainFrame::OnFileNew()
{
	// 创建新工程
	CCreateNewSkinProject NewSkinDlg;
	if (NewSkinDlg.DoModal() != IDOK)
		return;

	// 关闭现有工程
	OnFileClose();

	NewSkinDlg.GetNewProjectPath(m_strCurSkinDir, m_strCurSkinName);
	m_strNewUfpPath.Format(_T("%s\\%s%s"), m_strCurSkinDir, m_strCurSkinName, _T(NAME_SKIN_PROJ_EX_NAME));

	OnFileOpen();
}

void CMainFrame::OnFileOpen()
{
	USES_CONVERSION;

	// 打开工程文件
	if (!OpenUfpFile())
		return;

	OnFileClose();

	// 初始化一个工程
	OpenNewProject();

	m_strCurUfpPath = m_strNewUfpPath;
	m_strCurSkinName = m_strNewSkinName;
	m_strCurSkinDir = m_strNewSkinDir;
	m_strNewUfpPath = _T("");
	m_strNewSkinName = _T("");
	m_strNewSkinDir = _T("");
}

void CMainFrame::SetProjectInitState(bool bInitOk)
{
	m_wndWindowView.SetProjectInitState(bInitOk);
	m_wndProperties.SetProjectInitState(bInitOk);
}

void CMainFrame::OnFileSave()
{
	if (m_strCurUfpPath.GetLength() <= 0)
		return;


}

void CMainFrame::OnAppExit()
{
	OnFileClose();
}

void CMainFrame::OnFileClose()
{
	// 保存现有工程
	OnFileSave();

	if (m_strCurUfpPath.GetLength() <= 0)
		return;




	m_strCurUfpPath = _T("");
	m_strCurSkinName = _T("");
	m_strCurSkinDir = _T("");
	SetProjectInitState(false);
}

bool CMainFrame::OpenUfpFile()
{
	m_strNewUfpPath = _T("");

	CFileDialog UfpFileSelDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING,
		_T("ufp Files (*.ufp)|*.ufp;)||"), NULL);
	UfpFileSelDlg.DoModal();
	
	m_strNewUfpPath = UfpFileSelDlg.GetPathName();
	m_strNewSkinName = UfpFileSelDlg.GetFileTitle();
	m_strNewSkinDir = m_strNewUfpPath.Left(m_strNewUfpPath.ReverseFind('\\') + 1);

	return (m_strNewUfpPath.GetLength() > 0 && m_strNewSkinName.GetLength() > 0 && m_strNewSkinDir.GetLength() > 0);
}

bool CMainFrame::OpenNewProject()
{
	SetProjectInitState(true);

	if (m_pSkinMgr == NULL)
		return false;

	m_pSkinMgr->ReleaseSkinManagerPropetry();

	CString strLayoutXml(_T(""));
	CString strWindowsXml(_T(""));
	CString strControlsXml(_T(""));
	CString strResourceXml(_T(""));

	// 初始化：Layout.xml
	strLayoutXml.Format(_T("%s\\%s"), m_strNewSkinDir, m_strNewSkinName, _T(LAYOUT_XML_NAME));
	strWindowsXml.Format(_T("%s\\%s"), m_strNewSkinDir, m_strNewSkinName, _T(WINDOWS_XML_NAME));
	strControlsXml.Format(_T("%s\\%s"), m_strNewSkinDir, m_strNewSkinName, _T(CONTROLS_XML_NAME));
	strResourceXml.Format(_T("%s\\%s"), m_strNewSkinDir, m_strNewSkinName, _T(RESOURCE_XML_NAME));

	if (!InitResourceXml(strResourceXml))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("导入配置文件【%s】错误！"), _T(RESOURCE_XML_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

	if (!InitControlsXml(strControlsXml))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("导入配置文件【%s】错误！"), _T(CONTROLS_XML_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

	if (!InitWindowsXml(strWindowsXml))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("导入配置文件【%s】错误！"), _T(WINDOWS_XML_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

	if (!InitLayoutXml(strLayoutXml))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("导入配置文件【%s】错误！"), _T(LAYOUT_XML_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

	m_wndWindowView.InitShowNewProject();
	return true;
}

bool CMainFrame::InitResourceXml(CString strXmlFile)
{
	USES_CONVERSION;
	if (FileExists(W2A(strXmlFile)))
		return m_pSkinMgr->BuilderTranslateResourceXml(W2A(strXmlFile));

	return true;
}

bool CMainFrame::InitControlsXml(CString strXmlFile)
{
	USES_CONVERSION;
	if (FileExists(W2A(strXmlFile)))
		return m_pSkinMgr->BuilderTranslateControlsXml(W2A(strXmlFile));

	return true;
}

bool CMainFrame::InitWindowsXml(CString strXmlFile)
{
	USES_CONVERSION;
	if (FileExists(W2A(strXmlFile)))
		return m_pSkinMgr->BuilderTranslateWindowsXml(W2A(strXmlFile));

	return true;
}

bool CMainFrame::InitLayoutXml(CString strXmlFile)
{
	USES_CONVERSION;
	if (FileExists(W2A(strXmlFile)))
		return m_pSkinMgr->BuilderTranslateLayoutXml(W2A(strXmlFile));

	return true;
}
