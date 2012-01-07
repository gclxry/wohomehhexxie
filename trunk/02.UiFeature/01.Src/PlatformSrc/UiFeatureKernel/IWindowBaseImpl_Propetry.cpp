//////////////////////////////////////////////////////////////////////////
// ObjectId命名规则
// Window

#include "StdAfx.h"
#include "IWindowBaseImpl.h"
#include "IPropertySkinManagerImpl.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyGroup* IWindowBaseImpl::PP_GetWindowPropetryGroup()
{
	if (m_pXmlPropWindow == NULL)
		return NULL;

	return m_pXmlPropWindow->GetWindowPropGroup();
}

IPropertyWindow* IWindowBaseImpl::PP_GetWindowPropetry()
{
	return m_pXmlPropWindow;
}

// 将xml中的属性设置到manager中
void IWindowBaseImpl::PP_SetWindowPropetry(IPropertyWindow *pWndPropInXml, bool bSetDftProp)
{
	if (pWndPropInXml == NULL)
		return;

	m_pXmlPropWindow = pWndPropInXml;
	CreateWindowPropetry(bSetDftProp);
}

// 窗口Object名称
void IWindowBaseImpl::PP_SetWindowObjectName(char *pszWndName)
{
	if (pszWndName == NULL || m_pPropBase_Name == NULL)
		return;

	m_pPropBase_Name->SetString(pszWndName);
}

const char * IWindowBaseImpl::PP_GetWindowObjectName()
{
	if (m_pPropBase_Name == NULL)
		return NULL;

	return m_pPropBase_Name->GetString();
}

// 窗口名称
void IWindowBaseImpl::PP_SetWindowText(char *pszWndText)
{
	if (pszWndText == NULL || m_pPropBase_WindowText == NULL)
		return;

	m_pPropBase_WindowText->SetString(pszWndText);
}

const char * IWindowBaseImpl::PP_GetWindowText()
{
	if (m_pPropBase_WindowText == NULL)
		return NULL;

	return m_pPropBase_WindowText->GetString();
}

// 是否支持全窗口点击移动
void IWindowBaseImpl::PP_SetDragWindow(bool bDrag)
{
	if (m_pPropDrag_Enable == NULL)
		return;

	m_pPropDrag_Enable->SetValue(bDrag);
}

bool IWindowBaseImpl::PP_GetDragWindow()
{
	if (m_pPropDrag_Enable == NULL)
		return false;

	return m_pPropDrag_Enable->GetValue();
}

// 是否最大化
void IWindowBaseImpl::PP_SetCanFullScreen(bool bCanFull)
{
	if (m_pPropSysBase_CanFullScreen == NULL)
		return;

	m_pPropSysBase_CanFullScreen->SetValue(bCanFull);
}

bool IWindowBaseImpl::PP_IsCanFullScreen()
{
	if (m_pPropSysBase_CanFullScreen == NULL)
		return false;

	return m_pPropSysBase_CanFullScreen->GetValue();
}

void IWindowBaseImpl::PP_SetFullScreen(bool bFull)
{
	m_bIsFullScreen = false;
	if (m_pPropSysBase_CanFullScreen == NULL)
		return;

	if (m_pPropSysBase_CanFullScreen->GetValue())
		m_bIsFullScreen = bFull;
}

bool IWindowBaseImpl::PP_IsFullScreen()
{
	return m_bIsFullScreen;
}

IPropertyBase* IWindowBaseImpl::CreateCtrlOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo)
{
	if (m_pSkinPropMgr == NULL || m_pXmlPropWindow == NULL || pszPropName == NULL || strlen(pszPropName) <= 0 || propType <= OTID_NONE || propType >= OTID_LAST)
		return NULL;

	if (pGroup == NULL)
		pGroup = m_pXmlPropWindow->GetWindowPropGroup();

	return CreateResourcePropetry(m_pSkinPropMgr, pGroup, propType, pszPropName, pszPropInfo);
}

// 创建空的属性队列
void IWindowBaseImpl::CreateWindowPropetry(bool bSetDftProp)
{
	if (m_pXmlPropWindow == NULL)
		return;

	// Group:base
	m_pPropGroupBase = (IPropertyGroup*)CreateCtrlOnePropetry(NULL, OTID_GROUP, "WindowBase", "窗口/面板基本属性");
	if (m_pPropGroupBase == NULL)
		return;

	// base-类型名称
	m_pPropBase_TypeName = (IPropertyString*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_TYPE, "当前 Object 类型");
	if (m_pPropBase_TypeName == NULL)
		return;
	m_pPropBase_TypeName->SetString(PROP_TYPE_WINDOW_NAME);

	// base-objectid
	m_pPropBase_ObjectId = (IPropertyString*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_OBJ_ID, "当前 Object Id");
	if (m_pPropBase_ObjectId == NULL)
		return;
	m_pPropBase_ObjectId->SetString((char*)m_pXmlPropWindow->GetObjectId());

	// base-name
	m_pPropBase_Name = (IPropertyString*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME, "当前 Object 名称");
	if (m_pPropBase_Name == NULL)
		return;
	if (m_pPropBase_Name->GetString() != NULL && strlen(m_pPropBase_Name->GetString()) <= 0)
		m_pPropBase_Name->SetString("新建窗口/面板");

	// base-windowtitle
	m_pPropBase_WindowText = (IPropertyString*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_STRING, "WindowText", "当前窗口标题");
	if (m_pPropBase_WindowText == NULL)
		return;
	if (m_pPropBase_WindowText->GetString() != NULL && strlen(m_pPropBase_WindowText->GetString()) <= 0)
		m_pPropBase_WindowText->SetString("无窗口标题");

	// base-visible
	m_pPropBase_Visible = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "Visible", "是否可见");
	if (m_pPropBase_Visible == NULL)
		return;

	// base-支持分层窗口
	m_pPropBase_Layered = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "LayeredWindow", "是否支持分层窗口");
	if (m_pPropBase_Layered == NULL)
		return;

	// base-topmost
	m_pPropBase_TopMost = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "TopMost", "窗口是否在最上层");
	if (m_pPropBase_TopMost == NULL)
		return;

	// base-sysbase
	m_pPropGroupSysBase = (IPropertyGroup*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_GROUP, "SysBase", "窗口系统属性，只限于窗口，其他类型不适用");
	if (m_pPropGroupSysBase == NULL)
		return;

	// base-sysbase-最大化
	m_pPropSysBase_CanFullScreen = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupSysBase, OTID_BOOL, "CanFullScreen", "是否可以最大化");
	if (m_pPropSysBase_CanFullScreen == NULL)
		return;

	// base-sysbase-最小化
	m_pPropSysBase_CanMiniSize = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupSysBase, OTID_BOOL, "CanMiniSize", "是否可以最小化");
	if (m_pPropSysBase_CanMiniSize == NULL)
		return;

	// base-sysbase-最小尺寸
	// base-sysbase-最大尺寸

	// Group-size
	m_pPropGroupSize = (IPropertyGroup*)CreateCtrlOnePropetry(NULL, OTID_GROUP, "Size", "窗口/面板大小");
	if (m_pPropGroupSize == NULL)
		return;

	// size-width
	m_pPropSize_Width = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropGroupSize, OTID_INT, "Width", "窗口宽度");
	if (m_pPropSize_Width == NULL)
		return;

	// size-height
	m_pPropSize_Height = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropGroupSize, OTID_INT, "Height", "窗口高度");
	if (m_pPropSize_Height == NULL)
		return;

	// Group-drag(拖拽窗口)
	m_pPropGroupDrag = (IPropertyGroup*)CreateCtrlOnePropetry(NULL, OTID_GROUP, "Drag", "拖拽窗口");
	if (m_pPropGroupDrag == NULL)
		return;

	// drag-enable
	m_pPropDrag_Enable = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupDrag, OTID_BOOL, "Enable", "是否可以拖动窗口，随处移动");
	if (m_pPropDrag_Enable == NULL)
		return;

	// Group-stretching(拉伸窗口)
	m_pPropGroupStretching = (IPropertyGroup*)CreateCtrlOnePropetry(NULL, OTID_GROUP, "Stretching", "拉伸窗口");
	if (m_pPropGroupStretching == NULL)
		return;

	// stretching-enable
	m_pPropStretching_Enable = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupStretching, OTID_BOOL, "Enable", "是否可以拉伸窗口，使窗口可以变大变小");
	if (m_pPropStretching_Enable == NULL)
		return;

	// stretching-leftspace
	m_pPropStretching_LeftSpace = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropGroupStretching, OTID_INT, "LeftSpace", "拉伸窗口，窗口左侧鼠标探测范围");
	if (m_pPropStretching_LeftSpace == NULL)
		return;

	// stretching-rightspace
	m_pPropStretching_RightSpace = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropGroupStretching, OTID_INT, "RightSpace", "拉伸窗口，窗口右侧鼠标探测范围");
	if (m_pPropStretching_RightSpace == NULL)
		return;

	// stretching-topspace
	m_pPropStretching_TopSpace = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropGroupStretching, OTID_INT, "TopSpace", "拉伸窗口，窗口上方鼠标探测范围");
	if (m_pPropStretching_TopSpace == NULL)
		return;

	// stretching-bottomspace
	m_pPropStretching_BottomSpace = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropGroupStretching, OTID_INT, "BottomSpace", "拉伸窗口，窗口下方鼠标探测范围");
	if (m_pPropStretching_BottomSpace == NULL)
		return;

//	// Group-WindowRgn
//	m_pPropGroupWindowRgn = (IPropertyGroup*)CreateCtrlOnePropetry(NULL, OTID_GROUP, "WindowRgn", "窗口裁剪");
//	if (m_pPropGroupWindowRgn == NULL)
//		return;

	if (bSetDftProp)
	{
		// 设置默认值
		m_pPropBase_WindowText->SetString("窗口标题");
		m_pPropBase_Visible->SetValue(true);
		m_pPropBase_Layered->SetValue(false);
		m_pPropBase_TopMost->SetValue(false);
		m_pPropSysBase_CanFullScreen->SetValue(false);
		m_pPropSysBase_CanMiniSize->SetValue(false);
		m_pPropSize_Width->SetValue(500);
		m_pPropSize_Height->SetValue(500);
		m_pPropDrag_Enable->SetValue(false);
		m_pPropStretching_Enable->SetValue(false);
		m_pPropStretching_LeftSpace->SetValue(0);
		m_pPropStretching_RightSpace->SetValue(0);
		m_pPropStretching_TopSpace->SetValue(0);
		m_pPropStretching_BottomSpace->SetValue(0);
	}
}

bool IWindowBaseImpl::PP_GetLayeredWindow()
{
	if (m_pPropBase_Layered == NULL)
		return false;

	return m_pPropBase_Layered->GetValue();
}

// 设置窗体的透明特性
void IWindowBaseImpl::PP_SetLayeredWindow(bool bIsLayered)
{
	if (m_pPropBase_Layered == NULL)
		return;
	m_pPropBase_Layered->SetValue(bIsLayered);

	DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if (bIsLayered)
	{
		// 透明
		if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
		{
			dwExStyle |= WS_EX_LAYERED;
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle);
		}
	}
	else
	{
		// 不透明
		if ((dwExStyle & WS_EX_LAYERED) == WS_EX_LAYERED)
		{
			dwExStyle &= (~WS_EX_LAYERED);
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle);
		}
	}
}

// 取得子控件的属性列表：Layout.xml 中的布局
PROP_CONTROL_VEC* IWindowBaseImpl::GetChildPropControlVec()
{
	if (m_pXmlPropWindow == NULL)
		return NULL;

	return m_pXmlPropWindow->GetChildPropControlVec();
}
