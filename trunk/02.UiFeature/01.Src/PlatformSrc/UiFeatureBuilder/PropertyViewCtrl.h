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
#include "..\..\Inc\IKernelWindow.h"

class CWindowsViewTree;
class CPropertyViewCtrl : public CMFCPropertyGridCtrl
{
public:
	CPropertyViewCtrl(void);
	~CPropertyViewCtrl(void);

	// 清空所有的属性
	void ClearAll();
	// 显示一组新的属性
	void SetShowPropGroup(IPropertyGroup *pPropGroup);
	// 属性发生改变的时候
	void OnPropertyChanged(CMFCPropertyGridProperty* pProperty);
	void Init(IKernelWindow* pKernelWindow, CWindowsViewTree *pViewTree);

private:
	void AppendPropGroup(CMFCPropertyGridProperty* pParentPropGroup, IPropertyGroup *pPropGroup);
	void AppendBoolProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyBool *pBoolProp);
	void AppendColorProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyColor *pColorProp);
	void AppendComboBoxProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyComboBox *pComboboxProp);
	void AppendCursorProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyCursor *pCursorProp);
	void AppendFontProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyFont *pFontProp);
	void AppendImageProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyImage *pImageProp);
	void AppendIntProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyInt *pIntProp);
	void AppendStringProp(CMFCPropertyGridProperty* pParentPropGroup, IPropertyString *pStringProp);

	void RefreshBoolProp(CMFCPropertyGridProperty* pProperty, IPropertyBool *pBoolProp);
	void RefreshColorProp(CMFCPropertyGridProperty* pProperty, IPropertyColor *pColorProp);
	void RefreshComboBoxProp(CMFCPropertyGridProperty* pProperty, IPropertyComboBox *pComboboxProp);
	void RefreshCursorProp(CMFCPropertyGridProperty* pProperty, IPropertyCursor *pCursorProp);
	void RefreshFontProp(CMFCPropertyGridProperty* pProperty, IPropertyFont *pFontProp);
	void RefreshImageProp(CMFCPropertyGridProperty* pProperty, IPropertyImage *pImageProp);
	void RefreshIntProp(CMFCPropertyGridProperty* pProperty, IPropertyInt *pIntProp);
	void RefreshStringProp(CMFCPropertyGridProperty* pProperty, IPropertyString *pStringProp);

private:
	IPropertyGroup* m_pCurrentPropGroup;
	IKernelWindow* m_pKernelWindow;
	CWindowsViewTree* m_pViewTree;
};
