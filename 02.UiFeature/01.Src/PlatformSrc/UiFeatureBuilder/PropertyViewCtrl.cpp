#include "StdAfx.h"
#include "PropertyViewCtrl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "PropetryDialogGridProperty.h"

CPropertyViewCtrl::CPropertyViewCtrl(void)
{
	m_pPropGroup = NULL;
}

CPropertyViewCtrl::~CPropertyViewCtrl(void)
{
}

void CPropertyViewCtrl::SetShowPropGroup(IPropertyGroup *pPropGroup)
{
	ClearAll();
	if (pPropGroup == NULL)
		return;

	m_pPropGroup = pPropGroup;
	AppendPropGroup(NULL, m_pPropGroup);
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
		if (ObjTypeId == PT_GROUP)
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
		case PT_BOOL:
			AppendBoolProp(pParentPropGroup, (IPropertyBool*)pProp);
			break;

		case PT_COLOR:
			AppendColorProp(pParentPropGroup, (IPropertyColor*)pProp);
			break;

		case PT_COMBOBOX:
			AppendComboboxProp(pParentPropGroup, (IPropertyComboBox*)pProp);
			break;

		case PT_CURSOR:
			AppendCursorProp(pParentPropGroup, (IPropertyCursor*)pProp);
			break;

		case PT_FONT:
			AppendFontProp(pParentPropGroup, (IPropertyFont*)pProp);
			break;

		case PT_IMAGE:
			AppendImageProp(pParentPropGroup, (IPropertyImage*)pProp);
			break;

		case PT_INT:
			AppendIntProp(pParentPropGroup, (IPropertyInt*)pProp);
			break;

		case PT_STRING:
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
	m_pPropGroup = NULL;
	this->RemoveAll();
}

void CPropertyViewCtrl::AppendComboboxProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyComboBox *pComboboxProp)
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
	pNewProp->AllowEdit(FALSE);

	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);
}

void CPropertyViewCtrl::AppendIntProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyInt *pIntProp)
{
	if (pParentPropGroup == NULL || pIntProp == NULL)
		return;

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
