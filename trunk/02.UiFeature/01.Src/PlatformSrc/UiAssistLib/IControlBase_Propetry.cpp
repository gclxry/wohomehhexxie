
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\ICommonFun.h"


// 初始化在builder中的属性
bool IControlBase::BD_InitControlBase(IPropertyControl *pCtrlProp)
{
	if (pCtrlProp == NULL)
		return false;

	m_pXmlPropCtrl = m_pXmlPropCtrl;
	CreateCtrlPropetry();
	return true;
}

IPropertyBase* IControlBase::CreatePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo)
{
	if (m_pSkinPropMgr == NULL || m_pXmlPropCtrl == NULL || pszPropName == NULL || strlen(pszPropName) <= 0 || propType <= OTID_NONE || propType >= OTID_LAST)
		return NULL;

	if (pGroup == NULL)
		pGroup = m_pXmlPropCtrl->GetCtrlGroupProp();

	return CreateResourcePropetry(m_pSkinPropMgr, pGroup, propType, pszPropName, pszPropInfo);
}

// 创建空的属性队列
void IControlBase::CreateCtrlPropetry()
{
	if (m_pXmlPropCtrl == NULL)
		return;

	// Group:base
	m_pPropGroupBase = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "WindowBase", "窗口/面板基本属性");
	if (m_pPropGroupBase == NULL)
		return;

	// base-类型名称
	m_pPropBase_TypeName = (IPropertyString*)CreatePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_TYPE, "当前 Object 类型");
	if (m_pPropBase_TypeName == NULL)
		return;
	m_pPropBase_TypeName->SetString(PROP_TYPE_WINDOW_NAME);

	// base-objectid
	m_pPropBase_ObjectId = (IPropertyString*)CreatePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_OBJ_ID, "当前 Object Id");
	if (m_pPropBase_ObjectId == NULL)
		return;
	m_pPropBase_ObjectId->SetString((char*)m_pXmlPropCtrl->GetObjectId());

	// base-name
	m_pPropBase_Name = (IPropertyString*)CreatePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME, "当前 Object 名称");
	if (m_pPropBase_Name == NULL)
		return;
	if (m_pPropBase_Name->GetString() != NULL && strlen(m_pPropBase_Name->GetString()) <= 0)
		m_pPropBase_Name->SetString("新建窗口/面板");

	// base-windowtitle
	m_pPropBase_WindowText = (IPropertyString*)CreatePropetry(m_pPropGroupBase, OTID_STRING, "WindowText", "当前窗口标题");
	if (m_pPropBase_WindowText == NULL)
		return;
	if (m_pPropBase_WindowText->GetString() != NULL && strlen(m_pPropBase_WindowText->GetString()) <= 0)
		m_pPropBase_WindowText->SetString("无窗口标题");

	// base-visible
	m_pPropBase_Visible = (IPropertyBool*)CreatePropetry(m_pPropGroupBase, OTID_BOOL, "Visible", "是否可见");
	if (m_pPropBase_Visible == NULL)
		return;

	// base-支持分层窗口
	m_pPropBase_Layered = (IPropertyBool*)CreatePropetry(m_pPropGroupBase, OTID_BOOL, "LayeredWindow", "是否支持分层窗口");
	if (m_pPropBase_Layered == NULL)
		return;

	// base-topmost
	m_pPropBase_TopMost = (IPropertyBool*)CreatePropetry(m_pPropGroupBase, OTID_BOOL, "TopMost", "窗口是否在最上层");
	if (m_pPropBase_TopMost == NULL)
		return;

	// base-sysbase
	m_pPropGroupSysBase = (IPropertyGroup*)CreatePropetry(m_pPropGroupBase, OTID_GROUP, "SysBase", "窗口系统属性，只限于窗口，其他类型不适用");
	if (m_pPropGroupSysBase == NULL)
		return;

	// base-sysbase-最大化
	m_pPropSysBase_CanFullScreen = (IPropertyBool*)CreatePropetry(m_pPropGroupSysBase, OTID_BOOL, "CanFullScreen", "是否可以最大化");
	if (m_pPropSysBase_CanFullScreen == NULL)
		return;

	// base-sysbase-最小化
	m_pPropSysBase_CanMiniSize = (IPropertyBool*)CreatePropetry(m_pPropGroupSysBase, OTID_BOOL, "CanMiniSize", "是否可以最小化");
	if (m_pPropSysBase_CanMiniSize == NULL)
		return;

	// base-sysbase-最小尺寸
	// base-sysbase-最大尺寸

	// Group-size
	m_pPropGroupSize = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Size", "窗口/面板大小");
	if (m_pPropGroupSize == NULL)
		return;

	// size-width
	m_pPropSize_Width = (IPropertyInt*)CreatePropetry(m_pPropGroupSize, OTID_INT, "Width", "窗口宽度");
	if (m_pPropSize_Width == NULL)
		return;

	// size-height
	m_pPropSize_Height = (IPropertyInt*)CreatePropetry(m_pPropGroupSize, OTID_INT, "Height", "窗口高度");
	if (m_pPropSize_Height == NULL)
		return;

	// Group-drag(拖拽窗口)
	m_pPropGroupDrag = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Drag", "拖拽窗口");
	if (m_pPropGroupDrag == NULL)
		return;

	// drag-enable
	m_pPropDrag_Enable = (IPropertyBool*)CreatePropetry(m_pPropGroupDrag, OTID_BOOL, "Enable", "是否可以拖动窗口，随处移动");
	if (m_pPropDrag_Enable == NULL)
		return;

	// Group-stretching(拉伸窗口)
	m_pPropGroupStretching = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Stretching", "拉伸窗口");
	if (m_pPropGroupStretching == NULL)
		return;

	// stretching-enable
	m_pPropStretching_Enable = (IPropertyBool*)CreatePropetry(m_pPropGroupStretching, OTID_BOOL, "Enable", "是否可以拉伸窗口，使窗口可以变大变小");
	if (m_pPropStretching_Enable == NULL)
		return;

	// stretching-leftspace
	m_pPropStretching_LeftSpace = (IPropertyInt*)CreatePropetry(m_pPropGroupStretching, OTID_INT, "LeftSpace", "拉伸窗口，窗口左侧鼠标探测范围");
	if (m_pPropStretching_LeftSpace == NULL)
		return;

	// stretching-rightspace
	m_pPropStretching_RightSpace = (IPropertyInt*)CreatePropetry(m_pPropGroupStretching, OTID_INT, "RightSpace", "拉伸窗口，窗口右侧鼠标探测范围");
	if (m_pPropStretching_RightSpace == NULL)
		return;

	// stretching-topspace
	m_pPropStretching_TopSpace = (IPropertyInt*)CreatePropetry(m_pPropGroupStretching, OTID_INT, "TopSpace", "拉伸窗口，窗口上方鼠标探测范围");
	if (m_pPropStretching_TopSpace == NULL)
		return;

	// stretching-bottomspace
	m_pPropStretching_BottomSpace = (IPropertyInt*)CreatePropetry(m_pPropGroupStretching, OTID_INT, "BottomSpace", "拉伸窗口，窗口下方鼠标探测范围");
	if (m_pPropStretching_BottomSpace == NULL)
		return;

	//	// Group-WindowRgn
	//	m_pPropGroupWindowRgn = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "WindowRgn", "窗口裁剪");
	//	if (m_pPropGroupWindowRgn == NULL)
	//		return;
}








//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void IControlBase::InitControlPropetry()
{
	m_pXmlPropCtrl = NULL;

	m_pSkinPropMgr = NULL;


	m_bVisible = true;
	m_bEnable = true;
	m_bIsReceiveMouseMsg = true;
	INIT_RECT(m_RectInWindow);
	INIT_RECT(m_RectInParentCtrl);
	m_strCtrlName = "";
	m_bDragCtrl = false;
}

// 可用属性
void IControlBase::SetEnable(bool bEnable)
{
	m_bEnable = bEnable;
}

bool IControlBase::IsEnable()
{
	return m_bEnable;
}

// 可见属性
void IControlBase::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

bool IControlBase::IsVisible()
{
	return m_bVisible;
}

// 是否接受鼠标消息
void IControlBase::SetReceiveMouseMessage(bool bIsReceive)
{
	m_bIsReceiveMouseMsg = bIsReceive;
}

bool IControlBase::GetReceiveMouseMessage()
{
	return m_bIsReceiveMouseMsg;
}

// 控件显示位置和大小，这个位置是相对于附着的窗口的
void IControlBase::SetCtrlInWindowRect(RECT CtrlWndRct)
{
	m_RectInWindow = CtrlWndRct;
	int nWidth = RECT_WIDTH(m_RectInWindow);
	int nHeight = RECT_HEIGHT(m_RectInWindow);

	INIT_RECT(m_RectInParentCtrl);
	if (m_LayoutInfo.clType == CL_G_LEFT_TOP)
	{
		// 固定大小：左上角定位
		m_RectInParentCtrl.left = m_LayoutInfo.nLeftSpace;
		m_RectInParentCtrl.right = m_RectInParentCtrl.left + m_LayoutInfo.nWidth;
		m_RectInParentCtrl.top = m_LayoutInfo.nTopSpace;
		m_RectInParentCtrl.bottom = m_RectInParentCtrl.top + m_LayoutInfo.nHeight;
	}
	else if (m_LayoutInfo.clType == CL_G_LEFT_BOTTOM)
	{
		// 固定大小：左下角定位
		m_RectInParentCtrl.left = m_LayoutInfo.nLeftSpace;
		m_RectInParentCtrl.right = m_RectInParentCtrl.left + m_LayoutInfo.nWidth;
		m_RectInParentCtrl.bottom = m_LayoutInfo.nBottomSpace;
		m_RectInParentCtrl.top = m_RectInParentCtrl.bottom - m_LayoutInfo.nHeight;
	}
	else if (m_LayoutInfo.clType == CL_G_RIGHT_TOP)
	{
		// 固定大小：右上角定位
		m_RectInParentCtrl.right = nWidth - m_LayoutInfo.nRightSpace;
		m_RectInParentCtrl.left = m_RectInParentCtrl.right - m_LayoutInfo.nWidth;
		m_RectInParentCtrl.top = m_LayoutInfo.nTopSpace;
		m_RectInParentCtrl.bottom = m_RectInParentCtrl.top + m_LayoutInfo.nHeight;
	}
	else if (m_LayoutInfo.clType == CL_G_RIGHT_BOTTOM)
	{
		// 固定大小：右下角定位
		m_RectInParentCtrl.right = nWidth - m_LayoutInfo.nRightSpace;
		m_RectInParentCtrl.left = m_RectInParentCtrl.right - m_LayoutInfo.nWidth;
		m_RectInParentCtrl.bottom = nHeight - m_LayoutInfo.nBottomSpace;
		m_RectInParentCtrl.top = m_RectInParentCtrl.bottom - m_LayoutInfo.nHeight;
	}
	else if (m_LayoutInfo.clType == CL_L_LEFT)
	{
		// 拉伸变动大小：撑满左侧
		m_RectInParentCtrl.left = m_LayoutInfo.nLeftSpace;
		m_RectInParentCtrl.right = m_RectInParentCtrl.left + m_LayoutInfo.nWidth;
		m_RectInParentCtrl.top = m_LayoutInfo.nTopSpace;
		m_RectInParentCtrl.bottom = nHeight - m_LayoutInfo.nBottomSpace;
	}
	else if (m_LayoutInfo.clType == CL_L_RIGHT)
	{
		// 拉伸变动大小：撑满右侧
		m_RectInParentCtrl.right = nWidth - m_LayoutInfo.nRightSpace;
		m_RectInParentCtrl.left = m_RectInParentCtrl.right - m_LayoutInfo.nWidth;
		m_RectInParentCtrl.top = m_LayoutInfo.nTopSpace;
		m_RectInParentCtrl.bottom = nHeight - m_LayoutInfo.nBottomSpace;
	}
	else if (m_LayoutInfo.clType == CL_L_TOP)
	{
		// 拉伸变动大小：撑满上方
		m_RectInParentCtrl.left = m_LayoutInfo.nLeftSpace;
		m_RectInParentCtrl.right = nWidth - m_LayoutInfo.nRightSpace;
		m_RectInParentCtrl.top = m_LayoutInfo.nTopSpace;
		m_RectInParentCtrl.bottom = m_RectInParentCtrl.top + m_LayoutInfo.nHeight;
	}
	else if (m_LayoutInfo.clType == CL_L_BOTTOM)
	{
		// 拉伸变动大小：撑满下方
		m_RectInParentCtrl.left = m_LayoutInfo.nLeftSpace;
		m_RectInParentCtrl.right = nWidth - m_LayoutInfo.nRightSpace;
		m_RectInParentCtrl.bottom = nHeight - m_LayoutInfo.nBottomSpace;
		m_RectInParentCtrl.top = m_RectInParentCtrl.bottom - m_LayoutInfo.nHeight;
	}
	else if (m_LayoutInfo.clType == CL_L_ALL)
	{
		// 拉伸变动大小：撑满全部
		m_RectInParentCtrl.right = nWidth;
		m_RectInParentCtrl.bottom = nHeight;
	}
	else if (m_LayoutInfo.clType == CL_L_MIDDLE)
	{
		// 拉伸变动大小：居中
		m_RectInParentCtrl.left = m_LayoutInfo.nLeftSpace;
		m_RectInParentCtrl.right = nWidth - m_LayoutInfo.nRightSpace;
		m_RectInParentCtrl.top = m_LayoutInfo.nTopSpace;
		m_RectInParentCtrl.bottom = nHeight - m_LayoutInfo.nBottomSpace;
	}
}

RECT IControlBase::GetCtrlInWindowRect()
{
	return m_RectInWindow;
}

RECT IControlBase::GetCtrlInControlRect()
{
	return m_RectInParentCtrl;
}

// 取得控件的大小
RECT IControlBase::GetCtrlRect()
{
	RECT CtrlRct;
	INIT_RECT(CtrlRct);
	CtrlRct.right = RECT_WIDTH(m_RectInWindow);
	CtrlRct.bottom = RECT_HEIGHT(m_RectInWindow);
	return CtrlRct;
}

// 相对于父控件的布局信息
void IControlBase::SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo)
{
	m_LayoutInfo = cliLayoutInfo;
}

CONTROL_LAYOUT_INFO IControlBase::GetLayout()
{
	return m_LayoutInfo;
}

// 控件名称，唯一识别窗口的标志
void IControlBase::PP_SetObjectName(char *pCtrlName)
{
	if (pCtrlName != NULL)
		m_strCtrlName = pCtrlName;
}

const char* IControlBase::PP_GetObjectName()
{
	return m_strCtrlName.c_str();
}

// 拖动控件属性
void IControlBase::SetDragControl(bool bDrag)
{
	m_bDragCtrl = bDrag;
}

bool IControlBase::GetDragControl()
{
	return m_bDragCtrl;
}

// 1. 创建空的属性列表
bool IControlBase::CreateEmptyPropList()
{
	// 基础属性组
	IPropertyGroup *pBaseGroupProp = (IPropertyGroup *)CreateProperty(NULL, OTID_GROUP, "控件基本属性", NULL);

	// 控件类型(只读)
	// 控件ID(只读)

	// 控件名称
	IPropertyBase* pNameProp = CreateProperty(pBaseGroupProp, OTID_STRING, "Name", "控件名称");

	// Visible
	// Enable
	// 是否接受鼠标消息
	// 布局
	// 是否支持动画

	return true;
}

// 2.从Builder中新创建一个控件，需要初始化属性的PropId
bool IControlBase::InitObjectIdByBuilder(const char* pszBaseId)
{
	if (pszBaseId == NULL || m_pSkinPropMgr == NULL || m_pOwnerWindowBase == NULL || m_pOwnerWindowBase->GetObjectType() == NULL)
		return false;

	string strCtrlType = m_pOwnerWindowBase->GetObjectType();
	if (strCtrlType.size() <= 0)
		return false;

	// 设置控件自身的ObjectId
	int nId = m_pSkinPropMgr->GetNewId();
	char szId[1024];
	memset(szId, 0, 1024);
	sprintf_s(szId, 1023, "%s.%s%d", pszBaseId, strCtrlType.c_str(), nId);
	SetObjectType(szId);

	// 循环设置属性的ID
//	InitControlPropObjectId(&m_ControlPropList);

	return true;
}

void IControlBase::InitControlPropObjectId(GROUP_PROP_VEC *pPropList)
{
	if (pPropList == NULL || m_pSkinPropMgr == NULL || m_pOwnerWindowBase == NULL)
		return;

	string strCtrlType = m_pOwnerWindowBase->GetObjectType();
	if (strCtrlType.size() <= 0)
		return;

	char szId[1024];
	for (GROUP_PROP_VEC::iterator pPropItem = pPropList->begin(); pPropItem != pPropList->end(); pPropItem++)
	{
		IPropertyBase* pProp = *pPropItem;
		if (pProp == NULL)
			continue;

		string strTypeName = pProp->GetObjectType();

		memset(szId, 0, 1024);
		int nId = m_pSkinPropMgr->GetNewId();
		sprintf_s(szId, 1023, "%s.%s%d", strCtrlType.c_str(), strTypeName.c_str(), nId);
		pProp->SetObjectType(szId);

		if (pProp->GetObjectTypeId() == OTID_GROUP)
		{
			IPropertyGroup *pGroup = dynamic_cast<IPropertyGroup*>(pProp);
			if (pGroup != NULL)
				InitControlPropObjectId(pGroup->GetPropVec());
		}
	}
}

// 2. 从xml文件填充控件属性
bool IControlBase::ReadPropFromControlsXml(const char* pszControlId)
{
	return true;
}

// 3. 创建Builder显示用的属性
bool IControlBase::CreateBuilderShowPropList()
{
	return true;
}

// 创建一个属性
IPropertyBase* IControlBase::CreateProperty(IPropertyGroup *pPropGroup, OBJECT_TYPE_ID propType, char *pPropName, char *pPropInfo)
{
	if (m_pSkinPropMgr == NULL)
		return NULL;

	return NULL;
}

// 设置附属控件
void IControlBase::SetPropertySkinManager(IPropertySkinManager *pMgr)
{
	m_pSkinPropMgr = pMgr;
}
