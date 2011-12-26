
#pragma once
#include "..\..\Inc\IPropertyWindowManager.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\IPropertySkinManager.h"

class IPropertyWindowManagerImpl : public IPropertyWindowManager
{
public:
	IPropertyWindowManagerImpl(void);
	virtual ~IPropertyWindowManagerImpl(void);

	virtual bool IsInit();

	// 将xml中的属性设置到manager中
	virtual void SetWindowPropetry(IPropertyGroup *pWndPropInXml);

	// 是否支持全窗口点击移动
	virtual void SetDragWindow(bool bDrag);
	virtual bool GetDragWindow();

	// 是否最大化
	virtual void SetCanFullScreen(bool bCanFull);
	virtual bool IsCanFullScreen();
	virtual void SetFullScreen(bool bFull);
	virtual bool IsFullScreen();

	// 窗口名称
	virtual void SetWindowName(char *pszWndName);
	virtual const char * GetWindowName();

private:
	// 创建空的属性队列
	void CreateWindowPropetry();
	IPropertyBase* CreatePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);

private:
	IPropertySkinManager* m_pSkinPropMgr;
	bool m_bIsInit;
	bool m_bIsFullScreen;

	// 从xml中读入并需要写入xml中的属性窗口属性列表
	IPropertyGroup *m_pWndPropInXml;

	// Group:base
	IPropertyGroup* m_pPropGroupBase;
	// base-类型名称
	IPropertyString *m_pPropBase_TypeName;
	// base-objectid
	IPropertyString *m_pPropBase_ObjectId;
	// base-name
	IPropertyString *m_pPropBase_Name;
	// base-visible
	IPropertyBool *m_pPropBase_Visible;
	// base-支持分层窗口
	IPropertyBool *m_pPropBase_Layered;
	// base-topmost
	IPropertyBool *m_pPropBase_TopMost;
	// base-sysbase
	IPropertyGroup* m_pPropGroupSysBase;
	// base-sysbase-最大化
	IPropertyBool *m_pPropSysBase_CanFullScreen;
	// base-sysbase-最小化
	IPropertyBool *m_pPropSysBase_CanMiniSize;
	// base-sysbase-最小尺寸
	// base-sysbase-最大尺寸
	// Group-size
	IPropertyGroup* m_pPropGroupSize;
	// size-width
	IPropertyInt *m_pPropSize_Width;
	// size-height
	IPropertyInt *m_pPropSize_Height;
	// Group-drag(拖拽窗口)
	IPropertyGroup* m_pPropGroupDrag;
	// drag-enable
	IPropertyBool *m_pPropDrag_Enable;
	// Group-stretching(拉伸窗口)
	IPropertyGroup* m_pPropGroupStretching;
	// stretching-enable
	IPropertyBool *m_pPropStretching_Enable;
	// stretching-leftspace
	IPropertyInt *m_pPropStretching_LeftSpace;
	// stretching-rightspace
	IPropertyInt *m_pPropStretching_RightSpace;
	// stretching-topspace
	IPropertyInt *m_pPropStretching_TopSpace;
	// stretching-bottomspace
	IPropertyInt *m_pPropStretching_BottomSpace;
	// Group-WindowRgn
	IPropertyGroup* m_pPropGroupWindowRgn;
};
