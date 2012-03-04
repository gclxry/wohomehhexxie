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
#include "..\..\Inc\IUiFeatureKernel.h"


class CWindowsViewTree;
class CPropertyViewCtrl : public CMFCPropertyGridCtrl
{
public:
	CPropertyViewCtrl(void);
	~CPropertyViewCtrl(void);

	// 清空所有的属性
	void ClearAll();
	// 属性发生改变的时候
	void OnPropertyChanged(CMFCPropertyGridProperty* pProperty);
	void Init(IUiFeatureKernel* pKernelWindow, CWindowsViewTree *pViewTree);
	void SetProjectInitState(bool bInitOk);

	// 刷新整个界面
	void RefreshAllData();

	// 显示一组新的属性
	void SetShowPropGroup(IPropertyGroup *pPropGroup);

	// 鼠标拖动控件，改变布局，刷新到属性列表界面
	void RefreshLayoutData();

private:
	CMFCPropertyGridProperty* m_pWindowWidthProp;
	CMFCPropertyGridProperty* m_pWindowHeightProp;
	CMFCPropertyGridProperty* m_pCtrlLayoutTypeProp;
	CMFCPropertyGridProperty* m_pCtrlWidthProp;
	CMFCPropertyGridProperty* m_pCtrlHeightProp;
	CMFCPropertyGridProperty* m_pCtrlLeftSpaceProp;
	CMFCPropertyGridProperty* m_pCtrlRightSpaceProp;
	CMFCPropertyGridProperty* m_pCtrlTopSpaceProp;
	CMFCPropertyGridProperty* m_pCtrlBottomSpaceProp;

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
	void RefreshHaveBasePropPropetry(CMFCPropertyGridProperty* pProperty, IPropertyBase *pBaseProp);

	void SetNeedSave();
	void InitSetCtrlProp();
	void EnableLayoutState();
	void SetIntValueToPropView(int nValue, CMFCPropertyGridProperty* pGridProp);
	void RefreshToPropViewIntProp(CMFCPropertyGridProperty* pProperty);
private:
	bool m_bProjectInitOk;
	IPropertyGroup* m_pCurrentPropGroup;
	IUiFeatureKernel* m_pUiKernel;
	CWindowsViewTree* m_pViewTree;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnRefreshPropetryView(WPARAM wp, LPARAM lp);
};
