
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
	SetProjectInitState(false);
}

void CMainFrame::OnFileNew()
{
	// �����¹���
	CCreateNewSkinProject NewSkinDlg;
	if (NewSkinDlg.DoModal() != IDOK)
		return;

	NewSkinDlg.GetNewProjectPath(m_strNewSkinDir, m_strNewSkinName);
	m_strNewUfpPath.Format(_T("%s\\%s%s"), m_strNewSkinDir, m_strNewSkinName, _T(NAME_SKIN_PROJ_EX_NAME));

	OnFileOpen();
}

void CMainFrame::OnFileOpen()
{
	USES_CONVERSION;

	if (m_strNewUfpPath.GetLength() <= 0)
	{
		// �򿪹����ļ�
		if (!OpenUfpFile())
			return;
	}

	OnFileClose();

	// ��ʼ��һ������
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
	m_strCurSkinName = _T("");
	m_strCurSkinDir = _T("");
	SetProjectInitState(false);
}

void CMainFrame::OnFileSave()
{
	USES_CONVERSION;
	if (m_strCurUfpPath.GetLength() <= 0 || m_pKernelWindow == NULL)
		return;

	if (m_pKernelWindow->BD_SaveSkin(W2A(m_strCurSkinDir), W2A(m_strCurSkinName)))
	{
		AfxMessageBox(_T("����Ƥ�����̳ɹ���"), MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		AfxMessageBox(_T("����Ƥ������ʧ�ܣ�"), MB_OK | MB_ICONERROR);
	}
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
	USES_CONVERSION;
	SetProjectInitState(true);
	if (m_pKernelWindow == NULL || m_pSkinMgr == NULL)
		return false;

	if (!m_pKernelWindow->BuilderCreateOrOpenProject(W2A(m_strNewSkinDir), W2A(m_strNewSkinName)))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("û�з���ƥ���Ƥ���ļ���%s%s����"), m_strNewSkinName, _T(NAME_SKIN_FILE_EX_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

	if (!m_pSkinMgr->BD_TranslateResourceXml(RESOURCE_XML_NAME))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("���������ļ���%s������"), _T(RESOURCE_XML_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

	if (!m_pSkinMgr->BD_TranslateControlsXml(CONTROLS_XML_NAME))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("���������ļ���%s������"), _T(CONTROLS_XML_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

	if (!m_pSkinMgr->BD_TranslateWindowsXml(WINDOWS_XML_NAME))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("���������ļ���%s������"), _T(WINDOWS_XML_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

	if (!m_pSkinMgr->BD_TranslateLayoutXml(LAYOUT_XML_NAME))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("���������ļ���%s������"), _T(LAYOUT_XML_NAME));
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return false;
	}

	m_wndWindowView.InitShowNewProject();
	return true;
}
