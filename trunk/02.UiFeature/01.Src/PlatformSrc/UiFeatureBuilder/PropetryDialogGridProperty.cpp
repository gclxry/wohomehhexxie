#include "StdAfx.h"
#include "PropetryDialogGridProperty.h"
#include "ImageBasePropEditDlg.h"
#include "ModifyMouseStyleDlg.h"
#include "ModifyFontBaseDlg.h"
#include "PropertyViewCtrl.h"
#include "UiFeatureBuilderDoc.h"
#include "UiFeatureBuilderView.h"
#include "MainFrm.h"

CPropetryDialogGridProperty::CPropetryDialogGridProperty(const CString& strName, const COleVariant& varValue, CString& strInfo) : CMFCPropertyGridProperty(strName, varValue, strInfo)
{
	m_ObjType = OTID_NONE;
	m_pUiKernel = NULL;
	m_pPropViewList = NULL;
}

CPropetryDialogGridProperty::~CPropetryDialogGridProperty()
{
}

void CPropetryDialogGridProperty::InitDialogPropetry(CPropertyViewCtrl *pPropView, IUiFeatureKernel* pUiKernel, OBJECT_TYPE_ID ObjType)
{
	m_pPropViewList = pPropView;
	m_ObjType = ObjType;
	m_pUiKernel = pUiKernel;
	AllowEdit(FALSE);
}

void CPropetryDialogGridProperty::OnClickButton(CPoint /*point*/)
{
	if (m_ObjType == OTID_IMAGE_BASE)
	{
		ImageBaseDialog();
	}
	else if (m_ObjType == OTID_FONT_BASE)
	{
		FontBaseDialog();
	}
	else if (m_ObjType == OTID_CURSOR_BASE)
	{
		CursorBaseDialog();
	}
	else
	{
		SetValue(_T(""));
		AfxMessageBox(_T("错误的属性类型"));
	}

	m_pPropViewList->RedrawWindow();

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
	{
		pMain->SetPropetryChange();
		CUiFeatureBuilderView* pView = pMain->GetView();
		if (pView != NULL)
			pView->RedrawWindow();
	}
}

void CPropetryDialogGridProperty::ImageBaseDialog()
{
	USES_CONVERSION;
	IPropertyBase *pPropBase = (IPropertyBase*)this->GetData();
	IPropertyImage* pParentImgProp = dynamic_cast<IPropertyImage*>(pPropBase);
	if (pParentImgProp == NULL)
		return;

	pParentImgProp->SetNeedRedraw();

	CImageBasePropEditDlg ImageBaseDlg;
	ImageBaseDlg.InitImageBaseShow(m_pUiKernel, pParentImgProp);
	ImageBaseDlg.DoModal();

	COleVariant varValue(_T(""));
	int nSelectItem = -1;
	IPropertyImageBase *pImgBase = ImageBaseDlg.GetSelectImageBase(nSelectItem);
	if (pImgBase == NULL)
	{
		pParentImgProp->SetImageBaseProp(NULL);
		pParentImgProp->SetRelevancyPropName(NULL);
	}
	else
	{
		pParentImgProp->SetImageBaseProp(pImgBase);
		pParentImgProp->SetRelevancyPropName((char*)pImgBase->GetObjectName());
		varValue = A2W(pParentImgProp->GetRelevancyPropName());
	}

	SetValue(varValue);
	RefreshMainView();
}

void CPropetryDialogGridProperty::CursorBaseDialog()
{
	USES_CONVERSION;
	IPropertyBase *pPropBase = (IPropertyBase*)this->GetData();
	IPropertyCursor* pParentCursorProp = dynamic_cast<IPropertyCursor*>(pPropBase);
	if (pParentCursorProp == NULL)
		return;

	CModifyMouseStyleDlg CursorBaseDlg;
	CursorBaseDlg.InitCursorBaseShow(m_pUiKernel, pParentCursorProp);
	CursorBaseDlg.DoModal();

	COleVariant varValue(_T(""));
	if (pParentCursorProp->GetRelevancyProp() != NULL)
		varValue = A2W(pParentCursorProp->GetRelevancyPropName());
	SetValue(varValue);
	RefreshMainView();
}

void CPropetryDialogGridProperty::FontBaseDialog()
{
	USES_CONVERSION;
	IPropertyBase *pPropBase = (IPropertyBase*)this->GetData();
	IPropertyFont* pParentFontProp = dynamic_cast<IPropertyFont*>(pPropBase);
	if (pParentFontProp == NULL)
		return;

	CModifyFontBaseDlg FontBaseDlg;
	FontBaseDlg.InitFontBaseShow(m_pUiKernel, pParentFontProp);
	FontBaseDlg.DoModal();

	COleVariant varValue(_T(""));
	if (pParentFontProp->GetRelevancyProp() != NULL)
		varValue = A2W(pParentFontProp->GetRelevancyPropName());
	SetValue(varValue);
	RefreshMainView();
}

void CPropetryDialogGridProperty::RefreshMainView()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL && pMain->GetView() != NULL)
	{
		// 强迫重新绘制整个窗口
		if (pMain->GetView()->GetCurrentWindow() != NULL)
			pMain->GetView()->GetCurrentWindow()->CompelRedrawWindow();

		pMain->GetView()->RedrawWindow();
	}
}
