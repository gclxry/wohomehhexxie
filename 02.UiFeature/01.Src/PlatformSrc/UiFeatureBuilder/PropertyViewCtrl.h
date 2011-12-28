#pragma once
#include "afxpropertygridctrl.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\IPropertyColor.h"
#include "..\..\Inc\IPropertyComboBox.h"
#include "..\..\Inc\IPropertyCursor.h"
#include "..\..\Inc\IPropertyFont.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\IPropertyString.h"

class CPropertyViewCtrl : public CMFCPropertyGridCtrl
{
public:
	CPropertyViewCtrl(void);
	~CPropertyViewCtrl(void);

	void ClearAll();
	void SetShowPropGroup(IPropertyGroup *pPropGroup);

private:
	void AppendPropGroup(CMFCPropertyGridProperty* pParentPropGroup, IPropertyGroup *pPropGroup);
	void AppendBoolProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyBool *pBoolProp);
	void AppendColorProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyColor *pColorProp);
	void AppendComboboxProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyComboBox *pComboboxProp);
	void AppendCursorProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyCursor *pCursorProp);
	void AppendFontProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyFont *pFontProp);
	void AppendImageProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyImage *pImageProp);
	void AppendIntProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyInt *pIntProp);
	void AppendStringProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyString *pStringProp);

private:
	IPropertyGroup *m_pPropGroup;
};
