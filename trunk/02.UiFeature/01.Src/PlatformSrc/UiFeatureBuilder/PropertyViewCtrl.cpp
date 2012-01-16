#include "StdAfx.h"
#include "PropertyViewCtrl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "PropetryDialogGridProperty.h"
#include "WindowsViewTree.h"
#include "MainFrm.h"

// 刷新属性界面
#define REFRESH_PROPETRY					(WM_USER + 0x7000)

BEGIN_MESSAGE_MAP(CPropertyViewCtrl, CMFCPropertyGridCtrl)
	ON_MESSAGE(REFRESH_PROPETRY, OnRefreshPropetryView)
END_MESSAGE_MAP()

CPropertyViewCtrl::CPropertyViewCtrl(void)
{
	m_pCurrentPropGroup = NULL;
	m_pUiKernel = NULL;
	m_pViewTree = NULL;
	m_bProjectInitOk = false;

	InitSetCtrlProp();
}

CPropertyViewCtrl::~CPropertyViewCtrl(void)
{
}

void CPropertyViewCtrl::InitSetCtrlProp()
{
	m_pCtrlLayoutTypeProp = NULL;
	m_pCtrlWidthProp = NULL;
	m_pCtrlHeightProp = NULL;
	m_pCtrlLeftSpaceProp = NULL;
	m_pCtrlTopSpaceProp = NULL;
	m_pCtrlRightSpaceProp = NULL;
	m_pCtrlBottomSpaceProp = NULL;
}

// 鼠标拖动控件，改变布局，刷新到属性列表界面
void CPropertyViewCtrl::RefreshLayoutData()
{
	RefreshToPropViewIntProp(m_pCtrlWidthProp);
	RefreshToPropViewIntProp(m_pCtrlHeightProp);
	RefreshToPropViewIntProp(m_pCtrlLeftSpaceProp);
	RefreshToPropViewIntProp(m_pCtrlTopSpaceProp);
	RefreshToPropViewIntProp(m_pCtrlRightSpaceProp);
	RefreshToPropViewIntProp(m_pCtrlBottomSpaceProp);
	this->RedrawWindow();
}

void CPropertyViewCtrl::RefreshToPropViewIntProp(CMFCPropertyGridProperty* pProperty)
{
	if (pProperty == NULL)
		return;

	IPropertyBase *pPropBase = (IPropertyBase*)pProperty->GetData();
	if (pPropBase == NULL)
		return;

	IPropertyInt *pIntProp = dynamic_cast<IPropertyInt*>(pPropBase);
	if (pIntProp == NULL)
		return;

	pProperty->SetValue((_variant_t)(pIntProp->GetValue()));
}

void CPropertyViewCtrl::SetProjectInitState(bool bInitOk)
{
	m_bProjectInitOk = bInitOk;
	if (!m_bProjectInitOk)
	{
		this->ClearAll();
	}
}

void CPropertyViewCtrl::Init(IUiFeatureKernel* pKernelWindow, CWindowsViewTree *pViewTree)
{
	if (pKernelWindow == NULL || pViewTree == NULL)
		return;

	m_pUiKernel = pKernelWindow;
	m_pViewTree = pViewTree;
}

LRESULT CPropertyViewCtrl::OnRefreshPropetryView(WPARAM wp, LPARAM lp)
{
	SetShowPropGroup(m_pCurrentPropGroup);
	return 0;
}

// 刷新整个界面
void CPropertyViewCtrl::RefreshAllData()
{
	::PostMessage(m_hWnd, REFRESH_PROPETRY, NULL, NULL);
}

void CPropertyViewCtrl::SetShowPropGroup(IPropertyGroup *pPropGroup)
{
	ClearAll();
	if (pPropGroup == NULL)
		return;

	m_pCurrentPropGroup = pPropGroup;
	AppendPropGroup(NULL, m_pCurrentPropGroup);
	EnableLayoutState();
	this->RedrawWindow();
}

void CPropertyViewCtrl::AppendPropGroup(CMFCPropertyGridProperty* pParentPropGroup, IPropertyGroup *pPropGroup)
{
	USES_CONVERSION;
	if (pPropGroup == NULL)
		return;

	GROUP_PROP_VEC *pPropVec = pPropGroup->GetPropVec();
	if (pPropVec == NULL)
		return;

	for (GROUP_PROP_VEC::iterator pPropItem = pPropVec->begin(); pPropItem != pPropVec->end(); pPropItem++)
	{
		IPropertyBase* pProp = *pPropItem;
		if (pProp == NULL)
			continue;

		OBJECT_TYPE_ID ObjTypeId = pProp->GetObjectTypeId();
		if (ObjTypeId == OTID_GROUP)
		{
			// 创建一个属性组
			CString strName = A2W(pProp->GetObjectName());
			CMFCPropertyGridProperty* pShowPropGroup = new CMFCPropertyGridProperty(strName);
			if (pShowPropGroup == NULL)
				continue;

			pShowPropGroup->SetData((DWORD_PTR)pProp);
			AppendPropGroup(pShowPropGroup, (IPropertyGroup*)pProp);

			if (pParentPropGroup != NULL)
				pParentPropGroup->AddSubItem(pShowPropGroup);
			else
				this->AddProperty(pShowPropGroup);
			continue;
		}

		// 普通属性
		switch (ObjTypeId)
		{
		case OTID_BOOL:
			AppendBoolProp(pParentPropGroup, (IPropertyBool*)pProp);
			break;

		case OTID_COLOR:
			AppendColorProp(pParentPropGroup, (IPropertyColor*)pProp);
			break;

		case OTID_COMBOBOX:
			AppendComboBoxProp(pParentPropGroup, (IPropertyComboBox*)pProp);
			break;

		case OTID_CURSOR:
			AppendCursorProp(pParentPropGroup, (IPropertyCursor*)pProp);
			break;

		case OTID_FONT:
			AppendFontProp(pParentPropGroup, (IPropertyFont*)pProp);
			break;

		case OTID_IMAGE:
			AppendImageProp(pParentPropGroup, (IPropertyImage*)pProp);
			break;

		case OTID_INT:
			AppendIntProp(pParentPropGroup, (IPropertyInt*)pProp);
			break;

		case OTID_STRING:
			AppendStringProp(pParentPropGroup, (IPropertyString*)pProp);
			break;

		default:
			continue;
		}
	}
}

void CPropertyViewCtrl::AppendBoolProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyBool *pBoolProp)
{
	USES_CONVERSION;
	if (pParentPropGroup == NULL || pBoolProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pBoolProp);
	if (pPropBase == NULL)
		return;

	CString strName = A2W(pPropBase->GetObjectName());
	CString strInfo = A2W(pPropBase->GetObjectInfo());

	CMFCPropertyGridProperty *pNewProp = new CMFCPropertyGridProperty(strName, (_variant_t)pBoolProp->GetValue(), strInfo);
	if (pNewProp == NULL)
		return;

	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);
}

void CPropertyViewCtrl::AppendColorProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyColor *pColorProp)
{
	USES_CONVERSION;
	if (pParentPropGroup == NULL || pColorProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pColorProp);
	if (pPropBase == NULL)
		return;

	CString strName = A2W(pPropBase->GetObjectName());
	CString strInfo = A2W(pPropBase->GetObjectInfo());

	//CMFCPropertyGridProperty *pNewProp = new CMFCPropertyGridProperty(strName, (_variant_t)pColorProp->GetValue(), strInfo);
	//if (pNewProp == NULL)
	//	return;

	//pNewProp->SetData((DWORD_PTR)pPropBase);
	//pParentPropGroup->AddSubItem(pNewProp);
}

void CPropertyViewCtrl::ClearAll()
{
	InitSetCtrlProp();
	m_pCurrentPropGroup = NULL;
	this->RemoveAll();
	this->RedrawWindow();
}

void CPropertyViewCtrl::AppendComboBoxProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyComboBox *pComboboxProp)
{
	USES_CONVERSION;
	if (pParentPropGroup == NULL || pComboboxProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pComboboxProp);
	if (pPropBase == NULL)
		return;

	CString strName = A2W(pPropBase->GetObjectName());
	CString strInfo = A2W(pPropBase->GetObjectInfo());

	COMBOBOX_PROP* pComboData = pComboboxProp->GetComboBoxData();
	if (pComboData == NULL)
		return;

	string strData = pComboData->DataVec[pComboData->nSelect];
	CMFCPropertyGridProperty* pNewProp = new CMFCPropertyGridProperty(strName, A2W(strData.c_str()), strInfo);
	for (STRING_VEC::iterator pVecItem = pComboData->DataVec.begin(); pVecItem != pComboData->DataVec.end(); pVecItem++)
	{
		strData = *pVecItem;
		pNewProp->AddOption(A2W(strData.c_str()));
	}
	pNewProp->AllowEdit(FALSE);

	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);

	if (strName.CompareNoCase(_T(NAME_LAYOUT_TYPE)) == 0)
		m_pCtrlLayoutTypeProp = pNewProp;
}

void CPropertyViewCtrl::AppendCursorProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyCursor *pCursorProp)
{
	if (pParentPropGroup == NULL || pCursorProp == NULL)
		return;
}

void CPropertyViewCtrl::AppendFontProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyFont *pFontProp)
{
	if (pParentPropGroup == NULL || pFontProp == NULL)
		return;

}

void CPropertyViewCtrl::AppendImageProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyImage *pImageProp)
{
	USES_CONVERSION;
	if (pParentPropGroup == NULL || pImageProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pImageProp);
	if (pPropBase == NULL)
		return;

	CString strName = A2W(pPropBase->GetObjectName());
	CString strInfo = A2W(pPropBase->GetObjectInfo());
	CString strData = A2W(pImageProp->GetImageBaseName());

	CPropetryDialogGridProperty *pNewProp = new CPropetryDialogGridProperty(strName, (_variant_t)strData, strInfo);
	if (pNewProp == NULL)
		return;
	pNewProp->InitDialogPropetry(this, m_pUiKernel, OTID_IMAGE_BASE);
	pNewProp->AllowEdit(FALSE);
	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);
}

void CPropertyViewCtrl::AppendIntProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyInt *pIntProp)
{
	USES_CONVERSION;
	if (pParentPropGroup == NULL || pIntProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pIntProp);
	if (pPropBase == NULL)
		return;

	CString strName = A2W(pPropBase->GetObjectName());
	CString strInfo = A2W(pPropBase->GetObjectInfo());

	CMFCPropertyGridProperty *pNewProp = new CMFCPropertyGridProperty(strName, (_variant_t)pIntProp->GetValue(), strInfo);
	if (pNewProp == NULL)
		return;

	pNewProp->EnableSpinControl(TRUE, -(0x7FFFFFFF), 0x7FFFFFFF);
	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);

	const char *pObjName = pPropBase->GetObjectName();
	if (lstrcmpiA(pObjName, NAME_LAYOUT_WIDTH) == 0)
	{
		m_pCtrlWidthProp = pNewProp;
	}
	else if (lstrcmpiA(pObjName, NAME_LAYOUT_HEIGHT) == 0)
	{
		m_pCtrlHeightProp = pNewProp;
	}
	else if (lstrcmpiA(pObjName, NAME_LAYOUT_LEFTSPACE) == 0)
	{
		m_pCtrlLeftSpaceProp = pNewProp;
	}
	else if (lstrcmpiA(pObjName, NAME_LAYOUT_RIGHTSPACE) == 0)
	{
		m_pCtrlRightSpaceProp = pNewProp;
	}
	else if (lstrcmpiA(pObjName, NAME_LAYOUT_TOPSPACE) == 0)
	{
		m_pCtrlTopSpaceProp = pNewProp;
	}
	else if (lstrcmpiA(pObjName, NAME_LAYOUT_BOTTOMSPACE) == 0)
	{
		m_pCtrlBottomSpaceProp = pNewProp;
	}
}

void CPropertyViewCtrl::AppendStringProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyString *pStringProp)
{
	USES_CONVERSION;
	if (pParentPropGroup == NULL || pStringProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pStringProp);
	if (pPropBase == NULL)
		return;

	CString strName = A2W(pPropBase->GetObjectName());
	CString strInfo = A2W(pPropBase->GetObjectInfo());
	CString strData = A2W(pStringProp->GetString());

	CMFCPropertyGridProperty *pNewProp = new CMFCPropertyGridProperty(strName, (_variant_t)strData, strInfo);
	if (pNewProp == NULL)
		return;

	if ((lstrcmpA(pPropBase->GetObjectName(), NAME_SKIN_PROP_NAME_OBJ_ID) == 0)
	|| (lstrcmpA(pPropBase->GetObjectName(), NAME_SKIN_PROP_NAME_TYPE) == 0))
	{
		pNewProp->Enable(FALSE);
		pNewProp->AllowEdit(FALSE);
	}

	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);
}

void CPropertyViewCtrl::OnPropertyChanged(CMFCPropertyGridProperty* pProperty)
{
	SetNeedSave();
	if (pProperty == NULL)
		return;

	IPropertyBase *pPropBase = (IPropertyBase*)pProperty->GetData();
	if (pPropBase == NULL)
		return;

	OBJECT_TYPE_ID ObjectTypeId = pPropBase->GetObjectTypeId();
	switch (ObjectTypeId)
	{
	case OTID_BOOL:
		RefreshBoolProp(pProperty, (IPropertyBool*)pPropBase);
		break;

	case OTID_COLOR:
		RefreshColorProp(pProperty, (IPropertyColor*)pPropBase);
		break;

	case OTID_COMBOBOX:
		RefreshComboBoxProp(pProperty, (IPropertyComboBox*)pPropBase);
		break;

	case OTID_CURSOR:
		RefreshCursorProp(pProperty, (IPropertyCursor*)pPropBase);
		break;

	case OTID_FONT:
		RefreshFontProp(pProperty, (IPropertyFont*)pPropBase);
		break;

	case OTID_IMAGE:
		RefreshImageProp(pProperty, (IPropertyImage*)pPropBase);
		break;

	case OTID_INT:
		RefreshIntProp(pProperty, (IPropertyInt*)pPropBase);
		break;

	case OTID_STRING:
		RefreshStringProp(pProperty, (IPropertyString*)pPropBase);
		break;

	default:
		return;
	}

	IFeatureObject *pOwnerObj = pPropBase->GetOwnerObject();
	if (pOwnerObj != NULL)
	{
		IControlBase *pCtrlBase = dynamic_cast<IControlBase*>(pOwnerObj);
		if (pCtrlBase != NULL)
		{
			// 从属性更新数据到成员变量
			pCtrlBase->PropetyValueToMemberValue();
			pCtrlBase->RedrawControl(true);
		}
	}

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL && pMain->GetView() != NULL)
		pMain->GetView()->RedrawWindow();
}

void CPropertyViewCtrl::RefreshBoolProp(CMFCPropertyGridProperty* pProperty, IPropertyBool *pBoolProp)
{
	if (pProperty == NULL || pBoolProp == NULL)
		return;

	COleVariant NewVariant = pProperty->GetValue();
	pBoolProp->SetValue(NewVariant.boolVal != VARIANT_FALSE);
}

void CPropertyViewCtrl::RefreshColorProp(CMFCPropertyGridProperty* pProperty, IPropertyColor *pColorProp)
{
	RefreshHaveBasePropPropetry(pProperty, dynamic_cast<IPropertyBase*>(pColorProp));
}

void CPropertyViewCtrl::RefreshCursorProp(CMFCPropertyGridProperty* pProperty, IPropertyCursor *pCursorProp)
{
	RefreshHaveBasePropPropetry(pProperty, dynamic_cast<IPropertyBase*>(pCursorProp));
}

void CPropertyViewCtrl::RefreshFontProp(CMFCPropertyGridProperty* pProperty, IPropertyFont *pFontProp)
{
	RefreshHaveBasePropPropetry(pProperty, dynamic_cast<IPropertyBase*>(pFontProp));
}

void CPropertyViewCtrl::RefreshHaveBasePropPropetry(CMFCPropertyGridProperty* pProperty, IPropertyBase *pBaseProp)
{
	USES_CONVERSION;
	if (pProperty == NULL || pBaseProp == NULL)
		return;

	pBaseProp->SetRelevancyProp(NULL);
	COleVariant NewVariant = pProperty->GetValue();
	if (NewVariant.bstrVal == NULL)
	{
		pBaseProp->SetRelevancyPropName(NULL);
		return;
	}

	CString strValue(NewVariant.bstrVal);
	::SysFreeString(NewVariant.bstrVal);

	pBaseProp->SetRelevancyPropName(W2A(strValue));
}

void CPropertyViewCtrl::RefreshImageProp(CMFCPropertyGridProperty* pProperty, IPropertyImage *pImageProp)
{
	RefreshHaveBasePropPropetry(pProperty, dynamic_cast<IPropertyBase*>(pImageProp));
}

void CPropertyViewCtrl::RefreshIntProp(CMFCPropertyGridProperty* pProperty, IPropertyInt *pIntProp)
{
	if (pProperty == NULL)
		return;

	COleVariant NewVariant = pProperty->GetValue();
	pIntProp->SetValue(NewVariant.lVal);
}

void CPropertyViewCtrl::RefreshStringProp(CMFCPropertyGridProperty* pProperty, IPropertyString *pStringProp)
{
	USES_CONVERSION;
	if (pProperty == NULL || pStringProp == NULL)
		return;

	COleVariant NewVariant = pProperty->GetValue();
	if (NewVariant.bstrVal == NULL)
		return;

	CString strValue(NewVariant.bstrVal);
	::SysFreeString(NewVariant.bstrVal);

	CString strName = pProperty->GetName();
	if (strName.CompareNoCase(_T(NAME_SKIN_PROP_NAME)) == 0)
	{
		if (strValue.GetLength() <= 0)
		{
			string strOld = pStringProp->GetString();
			COleVariant OldVariant(A2W(strOld.c_str()));
			pProperty->SetValue(OldVariant);
			AfxMessageBox(_T("【@Object_Name】字段不允许为空！"), MB_OK | MB_ICONERROR);
			return;
		}
	}

	pStringProp->SetString(W2A(strValue));

	// 刷新树形列表
	if (strName.CompareNoCase(_T(NAME_SKIN_PROP_NAME)) == 0 && m_pViewTree != NULL)
		m_pViewTree->RefreshObjectName();
}

void CPropertyViewCtrl::RefreshComboBoxProp(CMFCPropertyGridProperty* pProperty, IPropertyComboBox *pComboboxProp)
{
	USES_CONVERSION;
	if (pProperty == NULL || pComboboxProp == NULL)
		return;

	COleVariant NewVariant = pProperty->GetValue();
	if (NewVariant.bstrVal == NULL)
		return;

	CString strValue(NewVariant.bstrVal);
	::SysFreeString(NewVariant.bstrVal);

	pComboboxProp->SetSelectString(W2A(strValue));

	CString strName = pProperty->GetName();
	if (strName.CompareNoCase(_T(NAME_LAYOUT_TYPE)) == 0)
		EnableLayoutState();
}

void CPropertyViewCtrl::SetIntValueToPropView(int nValue, CMFCPropertyGridProperty* pGridProp)
{
	if (pGridProp == NULL)
		return;

	IPropertyBase *pPropBase = (IPropertyBase*)pGridProp->GetData();
	if (pPropBase == NULL)
		return;

	IPropertyInt* pIntProp = dynamic_cast<IPropertyInt*>(pPropBase);
	if (pIntProp == NULL)
		return;

	pGridProp->SetValue((_variant_t)(nValue));
	pIntProp->SetValue(nValue);
}

void CPropertyViewCtrl::EnableLayoutState()
{
	if (m_pCtrlLayoutTypeProp == NULL)
		return;

	IPropertyBase *pPropBase = (IPropertyBase*)m_pCtrlLayoutTypeProp->GetData();
	if (pPropBase == NULL)
		return;

	IPropertyComboBox* pComboProp = dynamic_cast<IPropertyComboBox*>(pPropBase);
	if (pComboProp == NULL)
		return;

	IFeatureObject *pOwnerObj = pComboProp->GetOwnerObject();
	if (pOwnerObj == NULL)
		return;

	COleVariant NewVariant;
	int nSel = pComboProp->GetSelect();
	if (m_pCtrlWidthProp != NULL && m_pCtrlHeightProp != NULL)
	{
		m_pCtrlWidthProp->Enable(TRUE);
		m_pCtrlHeightProp->Enable(TRUE);

		if (nSel == CL_L_ALL)
		{
			// 得到实际的大小
			if (pOwnerObj->GetObjectTypeId() != OTID_WINDOW)
			{
				IControlBase *pCtrlBase = dynamic_cast<IControlBase*>(pOwnerObj);
				if (pCtrlBase == NULL)
					return;

				IControlBase* pParentCtrl = pCtrlBase->GetParentControl();
				if (pParentCtrl == NULL)
				{
					IWindowBase *pWndBase = pCtrlBase->GetOwnerWindow();
					if (pWndBase == NULL)
						return;

					SIZE wndSize = pWndBase->PP_GetWindowPropSize();
					SetIntValueToPropView(wndSize.cx, m_pCtrlWidthProp);
					SetIntValueToPropView(wndSize.cy, m_pCtrlHeightProp);
				}
				else
				{
					RECT CtrlRct = pParentCtrl->GetWindowRect();
					SetIntValueToPropView(RECT_WIDTH(CtrlRct), m_pCtrlWidthProp);
					SetIntValueToPropView(RECT_HEIGHT(CtrlRct), m_pCtrlHeightProp);
				}
			}
			m_pCtrlWidthProp->Enable(FALSE);
			m_pCtrlHeightProp->Enable(FALSE);
		}

		if (nSel == CL_L_LEFT || nSel == CL_L_RIGHT)
			m_pCtrlHeightProp->Enable(FALSE);

		if (nSel == CL_L_TOP || nSel == CL_L_BOTTOM)
			m_pCtrlWidthProp->Enable(FALSE);
	}

	if (m_pCtrlLeftSpaceProp != NULL)
	{
		m_pCtrlLeftSpaceProp->Enable(TRUE);
		if (nSel == CL_L_ALL)
		{
			SetIntValueToPropView(0, m_pCtrlLeftSpaceProp);
			m_pCtrlLeftSpaceProp->Enable(FALSE);
		}

		if (nSel == CL_G_RIGHT_TOP || nSel == CL_G_RIGHT_BOTTOM || nSel == CL_L_RIGHT)
			m_pCtrlLeftSpaceProp->Enable(FALSE);
	}

	if (m_pCtrlRightSpaceProp != NULL)
	{
		m_pCtrlRightSpaceProp->Enable(TRUE);
		if (nSel == CL_L_ALL)
		{
			SetIntValueToPropView(0, m_pCtrlRightSpaceProp);
			m_pCtrlRightSpaceProp->Enable(FALSE);
		}

		if (nSel == CL_G_LEFT_TOP || nSel == CL_G_LEFT_BOTTOM || nSel == CL_L_LEFT)
			m_pCtrlRightSpaceProp->Enable(FALSE);
	}

	if (m_pCtrlTopSpaceProp != NULL)
	{
		m_pCtrlTopSpaceProp->Enable(TRUE);
		if (nSel == CL_L_ALL)
		{
			SetIntValueToPropView(0, m_pCtrlTopSpaceProp);
			m_pCtrlTopSpaceProp->Enable(FALSE);
		}

		if (nSel == CL_G_LEFT_BOTTOM || nSel == CL_G_RIGHT_BOTTOM || nSel == CL_L_BOTTOM)
			m_pCtrlTopSpaceProp->Enable(FALSE);
	}

	if (m_pCtrlBottomSpaceProp != NULL)
	{
		m_pCtrlBottomSpaceProp->Enable(TRUE);
		if (nSel == CL_L_ALL)
		{
			SetIntValueToPropView(0, m_pCtrlBottomSpaceProp);
			m_pCtrlBottomSpaceProp->Enable(FALSE);
		}

		if (nSel == CL_G_LEFT_TOP || nSel == CL_G_RIGHT_TOP || nSel == CL_L_TOP)
			m_pCtrlBottomSpaceProp->Enable(FALSE);
	}
}

void CPropertyViewCtrl::SetNeedSave()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
		pMain->SetPropetryChange();
}
