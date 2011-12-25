
#include "StdAfx.h"
#include "..\..\Inc\IPropertyControlInWindow.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"

IPropertyControlInWindow::IPropertyControlInWindow(void)
{
	SetObjectType("PropertyControl");
	m_pBaseCtrl = NULL;
	m_pSkinPropMgr = NULL;
	m_pParentPropertyControl = NULL;
	m_ControlPropList.clear();


	m_bVisible = true;
	m_bEnable = true;
	m_bIsReceiveMouseMsg = true;
	INIT_RECT(m_RectInWindow);
	INIT_RECT(m_RectInParentCtrl);
	m_strCtrlName = "";
	m_bDragCtrl = false;
}

IPropertyControlInWindow::~IPropertyControlInWindow(void)
{
}

void IPropertyControlInWindow::SetParentPropertyControl(IPropertyControlInWindow *pParent)
{
	if (pParent != NULL)
		m_pParentPropertyControl = pParent;
}

IPropertyControlInWindow* IPropertyControlInWindow::GetParentPropertyControl()
{
	return m_pParentPropertyControl;
}

void IPropertyControlInWindow::SetPropertySkinManager(IPropertySkinManager *pMgr)
{
	m_pSkinPropMgr = pMgr;
}

// 可用属性
void IPropertyControlInWindow::SetEnable(bool bEnable)
{
	m_bEnable = bEnable;
}

bool IPropertyControlInWindow::IsEnable()
{
	return m_bEnable;
}

// 设置附属控件
void IPropertyControlInWindow::SetControlBase(IControlBase *pCtrl)
{
	m_pBaseCtrl = pCtrl;
}

IControlBase* IPropertyControlInWindow::GetControlBase()
{
	return m_pBaseCtrl;
}

// 可见属性
void IPropertyControlInWindow::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

bool IPropertyControlInWindow::IsVisible()
{
	return m_bVisible;
}

// 是否接受鼠标消息
void IPropertyControlInWindow::SetReceiveMouseMessage(bool bIsReceive)
{
	m_bIsReceiveMouseMsg = bIsReceive;
}

bool IPropertyControlInWindow::GetReceiveMouseMessage()
{
	return m_bIsReceiveMouseMsg;
}

// 控件显示位置和大小，这个位置是相对于附着的窗口的
void IPropertyControlInWindow::SetCtrlInWindowRect(RECT CtrlWndRct)
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

RECT IPropertyControlInWindow::GetCtrlInWindowRect()
{
	return m_RectInWindow;
}

RECT IPropertyControlInWindow::GetCtrlInControlRect()
{
	return m_RectInParentCtrl;
}

// 取得控件的大小
RECT IPropertyControlInWindow::GetCtrlRect()
{
	RECT CtrlRct;
	INIT_RECT(CtrlRct);
	CtrlRct.right = RECT_WIDTH(m_RectInWindow);
	CtrlRct.bottom = RECT_HEIGHT(m_RectInWindow);
	return CtrlRct;
}

// 相对于父控件的布局信息
void IPropertyControlInWindow::SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo)
{
	m_LayoutInfo = cliLayoutInfo;
}

CONTROL_LAYOUT_INFO IPropertyControlInWindow::GetLayout()
{
	return m_LayoutInfo;
}

// 控件名称，唯一识别窗口的标志
void IPropertyControlInWindow::SetName(char *pCtrlName)
{
	if (pCtrlName != NULL)
		m_strCtrlName = pCtrlName;
}

const char* IPropertyControlInWindow::GetName()
{
	return m_strCtrlName.c_str();
}

// 拖动控件属性
void IPropertyControlInWindow::SetDragControl(bool bDrag)
{
	m_bDragCtrl = bDrag;
}

bool IPropertyControlInWindow::GetDragControl()
{
	return m_bDragCtrl;
}

// 1. 创建空的属性列表
bool IPropertyControlInWindow::CreateEmptyPropList()
{
	m_ControlPropList.clear();

	// 基础属性组
	IPropertyGroup *pBaseGroupProp = (IPropertyGroup *)CreateProperty(NULL, PT_GROUP, "控件基本属性", NULL);

	// 控件类型(只读)
	// 控件ID(只读)

	// 控件名称
	IPropertyBase* pNameProp = CreateProperty(pBaseGroupProp, PT_STRING, "Name", "控件名称");

	// Visible
	// Enable
	// 是否接受鼠标消息
	// 布局
	// 是否支持动画

	return true;
}

// 2.从Builder中新创建一个控件，需要初始化属性的PropId
bool IPropertyControlInWindow::InitObjectIdByBuilder(const char* pszBaseId)
{
	if (pszBaseId == NULL || m_pSkinPropMgr == NULL || m_pBaseCtrl == NULL || m_pBaseCtrl->GetObjectType() == NULL)
		return false;

	string strCtrlType = m_pBaseCtrl->GetObjectType();
	if (strCtrlType.size() <= 0)
		return false;

	// 设置控件自身的ObjectId
	int nId = m_pSkinPropMgr->GetNewId();
	char szId[1024];
	memset(szId, 0, 1024);
	sprintf_s(szId, 1023, "%s.%s%d", pszBaseId, strCtrlType.c_str(), nId);
	SetObjectType(szId);

	// 循环设置属性的ID
	InitControlPropObjectId(&m_ControlPropList);

	return true;
}

void IPropertyControlInWindow::InitControlPropObjectId(GROUP_PROP_VEC *pPropList)
{
	if (pPropList == NULL || m_pSkinPropMgr == NULL || m_pBaseCtrl == NULL)
		return;

	string strCtrlType = m_pBaseCtrl->GetObjectType();
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

		if (pProp->GetPropType() == PT_GROUP)
		{
			IPropertyGroup *pGroup = dynamic_cast<IPropertyGroup*>(pProp);
			if (pGroup != NULL)
				InitControlPropObjectId(pGroup->GetPropVec());
		}
	}
}

// 2. 从xml文件填充控件属性
bool IPropertyControlInWindow::ReadPropFromControlsXml(const char* pszControlId)
{
	return true;
}

// 3. 创建Builder显示用的属性
bool IPropertyControlInWindow::CreateBuilderShowPropList()
{
	return true;
}

// 创建一个属性
IPropertyBase* IPropertyControlInWindow::CreateProperty(IPropertyGroup *pPropGroup, PROP_TYPE propType, char *pPropName, char *pPropInfo)
{
	if (m_pSkinPropMgr == NULL)
		return NULL;

	return NULL;
}
