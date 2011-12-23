
#include "StdAfx.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "IPropertyControlImpl.h"

IPropertyControlImpl::IPropertyControlImpl(void)
{
	m_pBaseCtrl = NULL;
	m_pSkinPropMgr = NULL;
	m_ControlPropList.clear();


	m_bVisible = true;
	m_bEnable = true;
	m_bIsReceiveMouseMsg = true;
	INIT_RECT(m_RectInWindow);
	INIT_RECT(m_RectInParentCtrl);
	m_strCtrlName = "";
	m_bDragCtrl = false;
}

IPropertyControlImpl::~IPropertyControlImpl(void)
{
}

void IPropertyControlImpl::SetPropertySkinManager(IPropertySkinManager *pMgr)
{
	m_pSkinPropMgr = pMgr;
}

// 可用属性
void IPropertyControlImpl::SetEnable(bool bEnable)
{
	m_bEnable = bEnable;
}

bool IPropertyControlImpl::IsEnable()
{
	return m_bEnable;
}

// 设置附属控件
void IPropertyControlImpl::SetControlBase(IControlBase *pCtrl)
{
	m_pBaseCtrl = pCtrl;
}

IControlBase* IPropertyControlImpl::GetControlBase()
{
	return m_pBaseCtrl;
}

// 可见属性
void IPropertyControlImpl::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

bool IPropertyControlImpl::IsVisible()
{
	return m_bVisible;
}

// 是否接受鼠标消息
void IPropertyControlImpl::SetReceiveMouseMessage(bool bIsReceive)
{
	m_bIsReceiveMouseMsg = bIsReceive;
}

bool IPropertyControlImpl::GetReceiveMouseMessage()
{
	return m_bIsReceiveMouseMsg;
}

// 控件显示位置和大小，这个位置是相对于附着的窗口的
void IPropertyControlImpl::SetCtrlInWindowRect(RECT CtrlWndRct)
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

RECT IPropertyControlImpl::GetCtrlInWindowRect()
{
	return m_RectInWindow;
}

RECT IPropertyControlImpl::GetCtrlInControlRect()
{
	return m_RectInParentCtrl;
}

// 取得控件的大小
RECT IPropertyControlImpl::GetCtrlRect()
{
	RECT CtrlRct;
	INIT_RECT(CtrlRct);
	CtrlRct.right = RECT_WIDTH(m_RectInWindow);
	CtrlRct.bottom = RECT_HEIGHT(m_RectInWindow);
	return CtrlRct;
}

// 相对于父控件的布局信息
void IPropertyControlImpl::SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo)
{
	m_LayoutInfo = cliLayoutInfo;
}

CONTROL_LAYOUT_INFO IPropertyControlImpl::GetLayout()
{
	return m_LayoutInfo;
}

// 控件名称，唯一识别窗口的标志
void IPropertyControlImpl::SetName(char *pCtrlName)
{
	if (pCtrlName != NULL)
		m_strCtrlName = pCtrlName;
}

const char* IPropertyControlImpl::GetName()
{
	return m_strCtrlName.c_str();
}

// 拖动控件属性
void IPropertyControlImpl::SetDragControl(bool bDrag)
{
	m_bDragCtrl = bDrag;
}

bool IPropertyControlImpl::GetDragControl()
{
	return m_bDragCtrl;
}

// 1. 创建空的属性列表
bool IPropertyControlImpl::CreateEmptyPropList()
{
	m_ControlPropList.clear();

	// 基础属性组
	IPropertyGroup *pBaseGroupProp = (IPropertyGroup *)CreateProperty(NULL, PT_GROUP, 1, "控件基本属性", NULL);

	// 控件名称
	IPropertyBase* pNameProp = CreateProperty(pBaseGroupProp, PT_STRING, 1, "Name", "控件名称");

	// Visible
	// Enable
	// 是否接受鼠标消息
	// 布局
	// 是否支持动画

	return true;
}

// 2. 从xml文件填充控件属性
bool IPropertyControlImpl::ReadPropFromControlsXml(const char* pszControlId)
{
	return true;
}

// 3. 创建Builder显示用的属性
bool IPropertyControlImpl::CreateBuilderShowPropList()
{
	return true;
}

// 创建一个属性
IPropertyBase* IPropertyControlImpl::CreateProperty(IPropertyGroup *pPropGroup, PROP_TYPE propType, UINT nPropId, char *pPropName, char *pPropInfo)
{
	if (m_pSkinPropMgr == NULL)
		return NULL;

	return NULL;
}
