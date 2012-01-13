
// UiFeatureBuilderDoc.cpp : CUiFeatureBuilderDoc 类的实现
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


// CUiFeatureBuilderDoc 构造/析构

CUiFeatureBuilderDoc::CUiFeatureBuilderDoc()
{
	// TODO: 在此添加一次性构造代码

}

CUiFeatureBuilderDoc::~CUiFeatureBuilderDoc()
{
}

BOOL CUiFeatureBuilderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CUiFeatureBuilderDoc 序列化

void CUiFeatureBuilderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CUiFeatureBuilderDoc 诊断

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


// CUiFeatureBuilderDoc 命令

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
