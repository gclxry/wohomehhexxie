
// UiFeatureBuilderDoc.cpp : CUiFeatureBuilderDoc ���ʵ��
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "UiFeatureBuilderDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUiFeatureBuilderDoc

IMPLEMENT_DYNCREATE(CUiFeatureBuilderDoc, CDocument)

BEGIN_MESSAGE_MAP(CUiFeatureBuilderDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE, &CUiFeatureBuilderDoc::OnFileSave)
	ON_COMMAND(ID_FILE_CLOSE, &CUiFeatureBuilderDoc::OnFileClose)
END_MESSAGE_MAP()


// CUiFeatureBuilderDoc ����/����

CUiFeatureBuilderDoc::CUiFeatureBuilderDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CUiFeatureBuilderDoc::~CUiFeatureBuilderDoc()
{
}

BOOL CUiFeatureBuilderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CUiFeatureBuilderDoc ���л�

void CUiFeatureBuilderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CUiFeatureBuilderDoc ���

#ifdef _DEBUG
void CUiFeatureBuilderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUiFeatureBuilderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CUiFeatureBuilderDoc ����

void CUiFeatureBuilderDoc::OnFileSave()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
		pMain->OnFileSave();
}

void CUiFeatureBuilderDoc::OnFileClose()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
		pMain->OnFileClose();
}
