
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
		AfxMessageBox(_T("�Ҳ���UiFeature�ں�DLL��"), MB_OK | MB_ICONERROR);
		return;
	}

	GETKERNELWINDOWINTERFACE GetKernel = (GETKERNELWINDOWINTERFACE)::GetProcAddress(m_hKernelDll, "GetKernelWindowInterface");
	if (GetKernel == NULL)
	{
		AfxMessageBox(_T("�Ҳ���UiFeature�ں�DLL�ġ�GetKernelWindowInterface��������"), MB_OK | MB_ICONERROR);
		return;
	}

	m_pKernelWindow = GetKernel();
	if (m_pKernelWindow == NULL)
	{
		AfxMessageBox(_T("�Ҳ���UiFeature�ں�DLL�ġ�IKernelWindow���ӿڣ�"), MB_OK | MB_ICONERROR);
		return;
	}
	m_pSkinMgr = m_pKernelWindow->GetSkinManager();

	m_wndWindowView.Init(m_pKernelWindow, m_wndProperties.GetPropetryCtrl());
	m_wndProperties.Init(m_pKernelWindow, m_wndWindowView.GetViewTreeCtrl());

	// ���ؿؼ���ʾ����
	m_pRegControlMap = m_pKernelWindow->BuilderRegisterControl();
	// ��ʾ�ؼ�
	m_wndControls.SetControlList(m_pRegControlMap);

	m_bInitOk = true;
}

void CMainFrame::OnFileNew()
{
	// �����¹���
	CCreateNewSkinProject NewSkinDlg;
	if (NewSkinDlg.DoModal() != IDOK)
		return;

	// �ر����й���
	OnFileClose();

	NewSkinDlg.GetNewProjectPath(m_strSkinDir, m_strSkinName);
	m_strOpenUfpPath.Format(_T("%s\\%s%s"), m_strSkinDir, m_strSkinName, _T(NAME_SKIN_PROJ_EX_NAME));

	OnFileOpen();
}

void CMainFrame::OnFileOpen()
{
	USES_CONVERSION;
	OnFileClose();

	if (m_strOpenUfpPath.GetLength() <= 0)
		return;

	// ��ʼ��һ������
	InitProject();

	m_strCurUfpPath = m_strOpenUfpPath;
	m_strOpenUfpPath = _T("");
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
	// �������й���
	OnFileSave();

	if (m_strCurUfpPath.GetLength() <= 0)
		return;




	m_strCurUfpPath = _T("");
}

bool CMainFrame::InitProject()
{
	CString strLayoutXml(_T(""));
	CString strWindowsXml(_T(""));
	CString strControlsXml(_T(""));
	CString strResourceXml(_T(""));

	// ��ʼ����Layout.xml
	strLayoutXml.Format(_T("%s\\%s"), m_strSkinDir, m_strSkinName, _T(LAYOUT_XML_NAME));
	strWindowsXml.Format(_T("%s\\%s"), m_strSkinDir, m_strSkinName, _T(WINDOWS_XML_NAME));
	strControlsXml.Format(_T("%s\\%s"), m_strSkinDir, m_strSkinName, _T(CONTROLS_XML_NAME));
	strResourceXml.Format(_T("%s\\%s"), m_strSkinDir, m_strSkinName, _T(RESOURCE_XML_NAME));

	if (!InitResourceXml(strResourceXml))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("���������ļ���%s������"), _T(RESOURCE_XML_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

	if (!InitControlsXml(strControlsXml))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("���������ļ���%s������"), _T(CONTROLS_XML_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

	if (!InitWindowsXml(strWindowsXml))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("���������ļ���%s������"), _T(WINDOWS_XML_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

	if (!InitLayoutXml(strLayoutXml))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("���������ļ���%s������"), _T(LAYOUT_XML_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

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
