
#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "MainFrm.h"
#include "UiFeatureDefs.h"
#include "CreateNewSkinProject.h"
#include "..\..\Inc\ICommonFun.h"
#include "UiFeatureBuilderDoc.h"
#include "UiFeatureBuilderView.h"

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
		AfxMessageBox(_T("找不到UiFeature内核DLL的【IUiFeatureKernel】接口！"), MB_OK | MB_ICONERROR);
		return;
	}
	m_pSkinMgr = m_pKernelWindow->GetSkinManager();

	m_wndWindowView.Init(m_pKernelWindow, m_wndProperties.GetPropetryCtrl());
	m_wndProperties.Init(m_pKernelWindow, m_wndWindowView.GetViewTreeCtrl());

	// 加载控件显示数据
	m_pRegControlMap = m_pKernelWindow->BD_GetRegisterControl();
	// 显示控件
	m_wndControls.SetControlList(m_pRegControlMap);

	m_bInitOk = true;
	SetProjectInitState(false);
}

void CMainFrame::SetCrossCursor(bool bIsCross)
{
	m_bIsCross = bIsCross;
}

void CMainFrame::OnFileNew()
{
	// 创建新工程
	CCreateNewSkinProject NewSkinDlg;
	if (NewSkinDlg.DoModal() != IDOK)
		return;

	// 取得新工程路径信息
	NewSkinDlg.GetNewProjectPath(m_strNewSkinDir, m_strNewSkinName);
	if (m_strNewSkinDir.GetLength() <= 0 || m_strNewSkinName.GetLength() <= 0)
		return;

	if (m_strNewSkinDir.GetAt(m_strNewSkinDir.GetLength() - 1) != '\\')
		m_strNewSkinDir += "\\";

//	CString strInfo(_T(""));
//	strInfo.Format(_T("创建皮肤工程文件【%s%s】成功！"), m_strNewSkinName, _T(NAME_SKIN_FILE_EX_NAME));

	m_strNewUfpPath.Format(_T("%s%s%s"), m_strNewSkinDir, m_strNewSkinName, _T(NAME_SKIN_PROJ_EX_NAME));

	// 保存老工程
	if (!SaveSkinProject(m_strCurSkinDir, m_strCurSkinName, true))
		return;

	// 关闭老工程
	if (!CloseSkinProject())
		return;

	if (!OpenSkinProject(true, m_strNewSkinDir, m_strNewSkinName))
		return;

//	AfxMessageBox(strInfo, MB_OK | MB_ICONINFORMATION);
}

void CMainFrame::OnFileOpen()
{
	USES_CONVERSION;
	// 打开工程文件
	CFileDialog UfpFileSelDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING,
		_T("ufp Files (*.ufp)|*.ufp;)||"), NULL);
	UfpFileSelDlg.DoModal();

	m_strNewUfpPath = UfpFileSelDlg.GetPathName();
	m_strNewSkinName = UfpFileSelDlg.GetFileTitle();
	m_strNewSkinDir = m_strNewUfpPath.Left(m_strNewUfpPath.ReverseFind('\\') + 1);

	if (m_strNewUfpPath.GetLength() <= 0 || m_strNewSkinName.GetLength() <= 0 || m_strNewSkinDir.GetLength() <= 0)
		return;

	if (m_strNewSkinDir.CompareNoCase(m_strCurSkinDir) == 0 && m_strNewSkinName.CompareNoCase(m_strCurSkinName) == 0)
	{
		AfxMessageBox(_T("此工程已经被打开！"), MB_OK | MB_ICONERROR);
		return;
	}

	// 保存老工程
	if (!SaveSkinProject(m_strCurSkinDir, m_strCurSkinName, true))
		return;

	// 关闭老工程
	if (!CloseSkinProject())
		return;

	// 打开工程
	if (!OpenSkinProject(false, m_strNewSkinDir, m_strNewSkinName))
		return;

//	CString strInfo(_T(""));
//	strInfo.Format(_T("打开皮肤工程文件【%s%s】成功！"), m_strCurSkinName, _T(NAME_SKIN_FILE_EX_NAME));
//	AfxMessageBox(strInfo, MB_OK | MB_ICONINFORMATION);
}

void CMainFrame::SetProjectInitState(bool bInitOk)
{
	m_wndWindowView.SetProjectInitState(bInitOk);
	m_wndProperties.SetProjectInitState(bInitOk);
	m_wndControls.SetProjectInitState(bInitOk);
	if (m_pView != NULL)
		m_pView->SetProjectInitState(bInitOk);
}

void CMainFrame::OnDestroy()
{
	CFrameWndEx::OnDestroy();

	// 保存老工程
	SaveSkinProject(m_strCurSkinDir, m_strCurSkinName, false);
}

void CMainFrame::OnAppExit()
{
	// 保存老工程
	if (!SaveSkinProject(m_strCurSkinDir, m_strCurSkinName, false))
		return;

	// 关闭老工程
	if (!CloseSkinProject())
		return;
}

void CMainFrame::OnFileClose()
{
	// 保存老工程
	if (!SaveSkinProject(m_strCurSkinDir, m_strCurSkinName, true))
		return;

	// 关闭老工程
	if (!CloseSkinProject())
		return;
}

void CMainFrame::OnFileSave()
{
	// 保存老工程
	if (!SaveSkinProject(m_strCurSkinDir, m_strCurSkinName, true))
		return;
}

// 打开一个工程
bool CMainFrame::OpenSkinProject(bool bIsNew, CString strSkinDir, CString strSkinName)
{
	USES_CONVERSION;
	SetProjectInitState(true);
	if (m_pKernelWindow == NULL || m_pSkinMgr == NULL)
		return false;

	if (!bIsNew)
	{
		if (!m_pKernelWindow->BD_OpenProject(W2A(m_strNewSkinDir), W2A(m_strNewSkinName)))
		{
			CString strInfo(_T(""));
			strInfo.Format(_T("没有发现匹配的皮肤文件【%s%s】！"), m_strNewSkinName, _T(NAME_SKIN_FILE_EX_NAME));
			AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
			return false;
		}

		if (!m_pSkinMgr->BD_TranslateResourceXml(RESOURCE_XML_NAME))
		{
			CString strInfo(_T(""));
			strInfo.Format(_T("导入配置文件【%s】错误！"), _T(RESOURCE_XML_NAME));
			AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
			return false;
		}

		if (!m_pSkinMgr->BD_TranslateControlsXml(CONTROLS_XML_NAME))
		{
			CString strInfo(_T(""));
			strInfo.Format(_T("导入配置文件【%s】错误！"), _T(CONTROLS_XML_NAME));
			AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
			return false;
		}

		if (!m_pSkinMgr->BD_TranslateWindowsXml(WINDOWS_XML_NAME))
		{
			CString strInfo(_T(""));
			strInfo.Format(_T("导入配置文件【%s】错误！"), _T(WINDOWS_XML_NAME));
			AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
			return false;
		}

		if (!m_pSkinMgr->BD_TranslateLayoutXml(LAYOUT_XML_NAME))
		{
			CString strInfo(_T(""));
			strInfo.Format(_T("导入配置文件【%s】错误！"), _T(LAYOUT_XML_NAME));
			AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
			return false;
		}

		SetProjectInitState(true);
		m_wndWindowView.InitShowNewProject();
	}
	else
	{
		SetProjectInitState(true);
	}

	m_strCurUfpPath = m_strNewUfpPath;
	m_strCurSkinName = m_strNewSkinName;
	m_strCurSkinDir = m_strNewSkinDir;

	m_strNewUfpPath = _T("");
	m_strNewSkinName = _T("");
	m_strNewSkinDir = _T("");

	return true;
}

// 保存
bool CMainFrame::SaveSkinProject(CString strSkinDir, CString strSkinName, bool bNeedErroInfo)
{
	USES_CONVERSION;

	if (strSkinDir.GetLength() <= 0 || strSkinName.GetLength() <= 0)
		return true;

	if (m_pKernelWindow == NULL)
		return false;

	bool bOk = m_pKernelWindow->BD_SaveProject(W2A(strSkinDir), W2A(strSkinName));
	if (bNeedErroInfo && !bOk)
		AfxMessageBox(_T("保存皮肤工程失败！"), MB_OK | MB_ICONERROR);
	return bOk;
}

// 保存
bool CMainFrame::CloseSkinProject()
{
	SetProjectInitState(false);

	if (m_pKernelWindow == NULL)
		return false;

	m_pKernelWindow->BD_CloseProject();

	m_strCurUfpPath = _T("");
	m_strCurSkinName = _T("");
	m_strCurSkinDir = _T("");
	return true;
}
