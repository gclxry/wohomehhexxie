#pragma once
#include "UiFeaturePropertyGrid.h"
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
	void OnPropertyChanged(CUiFeaturePropertyGrid* pProperty);
	void Init(IUiFeatureKernel* pKernelWindow, CWindowsViewTree *pViewTree);
	void SetProjectInitState(bool bInitOk);

	// 刷新整个界面
	void RefreshAllData();

	// 显示一组新的属性
	void SetShowPropGroup(IPropertyGroup *pPropGroup);

	// 鼠标拖动控件，改变布局，刷新到属性列表界面
	void RefreshLayoutData();

private:
	CUiFeaturePropertyGrid* m_pWindowWidthProp;
	CUiFeaturePropertyGrid* m_pWindowHeightProp;
	CUiFeaturePropertyGrid* m_pCtrlLayoutTypeProp;
	CUiFeaturePropertyGrid* m_pCtrlWidthProp;
	CUiFeaturePropertyGrid* m_pCtrlHeightProp;
	CUiFeaturePropertyGrid* m_pCtrlLeftSpaceProp;
	CUiFeaturePropertyGrid* m_pCtrlRightSpaceProp;
	CUiFeaturePropertyGrid* m_pCtrlTopSpaceProp;
	CUiFeaturePropertyGrid* m_pCtrlBottomSpaceProp;

private:
	void AppendPropGroup(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyGroup *pPropGroup);
	void AppendBoolProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyBool *pBoolProp);
	void AppendColorProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyColor *pColorProp);
	void AppendComboBoxProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyComboBox *pComboboxProp);
	void AppendCursorProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyCursor *pCursorProp);
	void AppendFontProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyFont *pFontProp);
	void AppendImageProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyImage *pImageProp);
	void AppendIntProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyInt *pIntProp);
	void AppendStringProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyString *pStringProp);

	void RefreshBoolProp(CUiFeaturePropertyGrid* pProperty, IPropertyBool *pBoolProp);
	void RefreshColorProp(CUiFeaturePropertyGrid* pProperty, IPropertyColor *pColorProp);
	void RefreshComboBoxProp(CUiFeaturePropertyGrid* pProperty, IPropertyComboBox *pComboboxProp);
	void RefreshCursorProp(CUiFeaturePropertyGrid* pProperty, IPropertyCursor *pCursorProp);
	void RefreshFontProp(CUiFeaturePropertyGrid* pProperty, IPropertyFont *pFontProp);
	void RefreshImageProp(CUiFeaturePropertyGrid* pProperty, IPropertyImage *pImageProp);
	void RefreshIntProp(CUiFeaturePropertyGrid* pProperty, IPropertyInt *pIntProp);
	void RefreshStringProp(CUiFeaturePropertyGrid* pProperty, IPropertyString *pStringProp);
	void RefreshHaveBasePropPropetry(CUiFeaturePropertyGrid* pProperty, IPropertyBase *pBaseProp);

	void SetNeedSave();
	void InitSetCtrlProp();
	void EnableLayoutState();
	void SetIntValueToPropView(int nValue, CUiFeaturePropertyGrid* pGridProp);
	void RefreshToPropViewIntProp(CUiFeaturePropertyGrid* pProperty);
private:
	bool m_bProjectInitOk;
	IPropertyGroup* m_pCurrentPropGroup;
	IUiFeatureKernel* m_pUiKernel;
	CWindowsViewTree* m_pViewTree;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnRefreshPropetryView(WPARAM wp, LPARAM lp);
};
