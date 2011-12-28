//////////////////////////////////////////////////////////////////////////
// ObjectId命名规则
// Window

#include "StdAfx.h"
#include "IPropertyWindowManagerImpl.h"
#include "IPropertySkinManagerImpl.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyWindowManagerImpl::IPropertyWindowManagerImpl(void)
{
	m_pSkinPropMgr = IPropertySkinManagerImpl::GetInstance();

	m_bIsInit = false;
	m_bIsFullScreen = false;

	m_pWndPropInXml = NULL;
	// Group:base
	m_pPropGroupBase = NULL;
	// base-类型名称
	m_pPropBase_TypeName = NULL;
	// base-objectid
	m_pPropBase_ObjectId = NULL;
	// base-name
	m_pPropBase_Name = NULL;
	// base-visible
	m_pPropBase_Visible = NULL;
	// base-支持分层窗口
	m_pPropBase_Layered = NULL;
	// base-topmost
	m_pPropBase_TopMost = NULL;
	// base-sysbase
	m_pPropGroupSysBase = NULL;
	// base-sysbase-最大化
	m_pPropSysBase_CanFullScreen = NULL;
	// base-sysbase-最小化
	m_pPropSysBase_CanMiniSize = NULL;
	// Group-size
	m_pPropGroupSize = NULL;
	// size-width
	m_pPropSize_Width = NULL;
	// size-height
	m_pPropSize_Height = NULL;
	// Group-drag(拖拽窗口)
	m_pPropGroupDrag = NULL;
	// drag-enable
	m_pPropDrag_Enable = NULL;
	// Group-stretching(拉伸窗口)
	m_pPropGroupStretching = NULL;
	// stretching-enable
	m_pPropStretching_Enable = NULL;
	// stretching-leftspace
	m_pPropStretching_LeftSpace = NULL;
	// stretching-rightspace
	m_pPropStretching_RightSpace = NULL;
	// stretching-topspace
	m_pPropStretching_TopSpace = NULL;
	// stretching-bottomspace
	m_pPropStretching_BottomSpace = NULL;
	// Group-WindowRgn
	m_pPropGroupWindowRgn = NULL;
}

IPropertyWindowManagerImpl::~IPropertyWindowManagerImpl(void)
{
}

// 将xml中的属性设置到manager中
void IPropertyWindowManagerImpl::SetWindowPropetry(IPropertyGroup *pWndPropInXml)
{
	if (pWndPropInXml == NULL)
		return;

	m_pWndPropInXml = pWndPropInXml;
	CreateWindowPropetry();
}

bool IPropertyWindowManagerImpl::IsInit()
{
	return m_bIsInit;
}

// 窗口名称
void IPropertyWindowManagerImpl::SetWindowName(char *pszWndName)
{
	if (pszWndName == NULL || m_pPropBase_Name == NULL)
		return;

	m_pPropBase_Name->SetString(pszWndName);
}

const char * IPropertyWindowManagerImpl::GetWindowName()
{
	if (m_pPropBase_Name == NULL)
		return NULL;

	return m_pPropBase_Name->GetString();
}

// 是否支持全窗口点击移动
void IPropertyWindowManagerImpl::SetDragWindow(bool bDrag)
{
	if (m_pPropDrag_Enable == NULL)
		return;

	m_pPropDrag_Enable->SetValue(bDrag);
}

bool IPropertyWindowManagerImpl::GetDragWindow()
{
	if (m_pPropDrag_Enable == NULL)
		return false;

	return m_pPropDrag_Enable->GetValue();
}

// 是否最大化
void IPropertyWindowManagerImpl::SetCanFullScreen(bool bCanFull)
{
	if (m_pPropSysBase_CanFullScreen == NULL)
		return;

	m_pPropSysBase_CanFullScreen->SetValue(bCanFull);
}

bool IPropertyWindowManagerImpl::IsCanFullScreen()
{
	if (m_pPropSysBase_CanFullScreen == NULL)
		return false;

	return m_pPropSysBase_CanFullScreen->GetValue();
}

void IPropertyWindowManagerImpl::SetFullScreen(bool bFull)
{
	m_bIsFullScreen = false;
	if (m_pPropSysBase_CanFullScreen == NULL)
		return;

	if (m_pPropSysBase_CanFullScreen->GetValue())
		m_bIsFullScreen = bFull;
}

bool IPropertyWindowManagerImpl::IsFullScreen()
{
	return m_bIsFullScreen;
}

IPropertyBase* IPropertyWindowManagerImpl::CreatePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo)
{
	if (m_pSkinPropMgr == NULL || m_pWndPropInXml == NULL || pszPropName == NULL || strlen(pszPropName) <= 0 || propType <= PT_NONE || propType >= PT_LAST)
		return NULL;

	if (pGroup == NULL)
		pGroup = m_pWndPropInXml;

	return CreateResourcePropetry(m_pSkinPropMgr, pGroup, propType, pszPropName, pszPropInfo);
}

// 创建空的属性队列
void IPropertyWindowManagerImpl::CreateWindowPropetry()
{
	if (m_pWndPropInXml == NULL)
		return;

	// Group:base
	m_pPropGroupBase = (IPropertyGroup*)CreatePropetry(NULL, PT_GROUP, "WindowBase", NULL);
	if (m_pPropGroupBase == NULL)
		return;

	// base-类型名称
	m_pPropBase_TypeName = (IPropertyString*)CreatePropetry(m_pPropGroupBase, PT_STRING, NAME_SKIN_PROP_NAME_TYPE, "当前 Object 类型");
	if (m_pPropBase_TypeName == NULL)
		return;
	m_pPropBase_TypeName->SetString(PROP_TYPE_WINDOW_NAME);

	// base-objectid
	m_pPropBase_ObjectId = (IPropertyString*)CreatePropetry(m_pPropGroupBase, PT_STRING, NAME_SKIN_PROP_NAME_OBJ_ID, "当前 Object Id");
	if (m_pPropBase_ObjectId == NULL)
		return;
	m_pPropBase_ObjectId->SetString((char*)m_pWndPropInXml->GetObjectId());

	// base-name
	m_pPropBase_Name = (IPropertyString*)CreatePropetry(m_pPropGroupBase, PT_STRING, "Name", "当前 Object 名称");
	if (m_pPropBase_Name == NULL)
		return;

	// base-visible
	m_pPropBase_Visible = (IPropertyBool*)CreatePropetry(m_pPropGroupBase, PT_BOOL, "Visible", "是否可见");
	if (m_pPropBase_Visible == NULL)
		return;
	m_pPropBase_Visible->SetValue(true);

	// base-支持分层窗口
	m_pPropBase_Layered = (IPropertyBool*)CreatePropetry(m_pPropGroupBase, PT_BOOL, "LayeredWindow", "是否支持分层窗口");
	if (m_pPropBase_Layered == NULL)
		return;
	m_pPropBase_Layered->SetValue(false);

	// base-topmost
	m_pPropBase_TopMost = (IPropertyBool*)CreatePropetry(m_pPropGroupBase, PT_BOOL, "TopMost", "窗口是否在最上层");
	if (m_pPropBase_TopMost == NULL)
		return;
	m_pPropBase_TopMost->SetValue(false);

	// base-sysbase
	m_pPropGroupSysBase = (IPropertyGroup*)CreatePropetry(m_pPropGroupBase, PT_GROUP, "SysBase", NULL);
	if (m_pPropGroupSysBase == NULL)
		return;

	// base-sysbase-最大化
	m_pPropSysBase_CanFullScreen = (IPropertyBool*)CreatePropetry(m_pPropGroupSysBase, PT_BOOL, "CanFullScreen", "是否可以最大化");
	if (m_pPropSysBase_CanFullScreen == NULL)
		return;

	// base-sysbase-最小化
	m_pPropSysBase_CanMiniSize = (IPropertyBool*)CreatePropetry(m_pPropGroupSysBase, PT_BOOL, "CanMiniSize", "是否可以最小化");
	if (m_pPropSysBase_CanMiniSize == NULL)
		return;

	// base-sysbase-最小尺寸
	// base-sysbase-最大尺寸

	// Group-size
	m_pPropGroupSize = (IPropertyGroup*)CreatePropetry(NULL, PT_GROUP, "Size", NULL);
	if (m_pPropGroupSize == NULL)
		return;

	// size-width
	m_pPropSize_Width = (IPropertyInt*)CreatePropetry(m_pPropGroupSize, PT_INT, "Width", "窗口宽度");
	if (m_pPropSize_Width == NULL)
		return;

	// size-height
	m_pPropSize_Height = (IPropertyInt*)CreatePropetry(m_pPropGroupSize, PT_INT, "Height", "窗口高度");
	if (m_pPropSize_Height == NULL)
		return;

	// Group-drag(拖拽窗口)
	m_pPropGroupDrag = (IPropertyGroup*)CreatePropetry(NULL, PT_GROUP, "Drag", NULL);
	if (m_pPropGroupDrag == NULL)
		return;

	// drag-enable
	m_pPropDrag_Enable = (IPropertyBool*)CreatePropetry(m_pPropGroupDrag, PT_BOOL, "Enable", "是否可以拖动窗口，随处移动");
	if (m_pPropDrag_Enable == NULL)
		return;

	// Group-stretching(拉伸窗口)
	m_pPropGroupStretching = (IPropertyGroup*)CreatePropetry(NULL, PT_GROUP, "Stretching", NULL);
	if (m_pPropGroupStretching == NULL)
		return;

	// stretching-enable
	m_pPropStretching_Enable = (IPropertyBool*)CreatePropetry(m_pPropGroupStretching, PT_BOOL, "Enable", "是否可以拉伸窗口，使窗口可以变大变小");
	if (m_pPropStretching_Enable == NULL)
		return;

	// stretching-leftspace
	m_pPropStretching_LeftSpace = (IPropertyInt*)CreatePropetry(m_pPropGroupStretching, PT_INT, "LeftSpace", "拉伸窗口，窗口左侧鼠标探测范围");
	if (m_pPropStretching_LeftSpace == NULL)
		return;

	// stretching-rightspace
	m_pPropStretching_RightSpace = (IPropertyInt*)CreatePropetry(m_pPropGroupStretching, PT_INT, "RightSpace", "拉伸窗口，窗口右侧鼠标探测范围");
	if (m_pPropStretching_RightSpace == NULL)
		return;

	// stretching-topspace
	m_pPropStretching_TopSpace = (IPropertyInt*)CreatePropetry(m_pPropGroupStretching, PT_INT, "TopSpace", "拉伸窗口，窗口上方鼠标探测范围");
	if (m_pPropStretching_TopSpace == NULL)
		return;

	// stretching-bottomspace
	m_pPropStretching_BottomSpace = (IPropertyInt*)CreatePropetry(m_pPropGroupStretching, PT_INT, "BottomSpace", "拉伸窗口，窗口下方鼠标探测范围");
	if (m_pPropStretching_BottomSpace == NULL)
		return;

	// Group-WindowRgn
	m_pPropGroupWindowRgn = (IPropertyGroup*)CreatePropetry(NULL, PT_GROUP, "WindowRgn", NULL);
	if (m_pPropGroupWindowRgn == NULL)
		return;
}

IPropertyGroup* IPropertyWindowManagerImpl::GetWindowPropetryBaseGroup()
{
	return m_pWndPropInXml;
}
