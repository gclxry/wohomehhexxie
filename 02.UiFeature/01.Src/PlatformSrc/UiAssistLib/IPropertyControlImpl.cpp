
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

// ��������
void IPropertyControlImpl::SetEnable(bool bEnable)
{
	m_bEnable = bEnable;
}

bool IPropertyControlImpl::IsEnable()
{
	return m_bEnable;
}

// ���ø����ؼ�
void IPropertyControlImpl::SetControlBase(IControlBase *pCtrl)
{
	m_pBaseCtrl = pCtrl;
}

IControlBase* IPropertyControlImpl::GetControlBase()
{
	return m_pBaseCtrl;
}

// �ɼ�����
void IPropertyControlImpl::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

bool IPropertyControlImpl::IsVisible()
{
	return m_bVisible;
}

// �Ƿ���������Ϣ
void IPropertyControlImpl::SetReceiveMouseMessage(bool bIsReceive)
{
	m_bIsReceiveMouseMsg = bIsReceive;
}

bool IPropertyControlImpl::GetReceiveMouseMessage()
{
	return m_bIsReceiveMouseMsg;
}

// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ŵĴ��ڵ�
void IPropertyControlImpl::SetCtrlInWindowRect(RECT CtrlWndRct)
{
	m_RectInWindow = CtrlWndRct;
	int nWidth = RECT_WIDTH(m_RectInWindow);
	int nHeight = RECT_HEIGHT(m_RectInWindow);

	INIT_RECT(m_RectInParentCtrl);
	if (m_LayoutInfo.clType == CL_G_LEFT_TOP)
	{
		// �̶���С�����ϽǶ�λ
		m_RectInParentCtrl.left = m_LayoutInfo.nLeftSpace;
		m_RectInParentCtrl.right = m_RectInParentCtrl.left + m_LayoutInfo.nWidth;
		m_RectInParentCtrl.top = m_LayoutInfo.nTopSpace;
		m_RectInParentCtrl.bottom = m_RectInParentCtrl.top + m_LayoutInfo.nHeight;
	}
	else if (m_LayoutInfo.clType == CL_G_LEFT_BOTTOM)
	{
		// �̶���С�����½Ƕ�λ
		m_RectInParentCtrl.left = m_LayoutInfo.nLeftSpace;
		m_RectInParentCtrl.right = m_RectInParentCtrl.left + m_LayoutInfo.nWidth;
		m_RectInParentCtrl.bottom = m_LayoutInfo.nBottomSpace;
		m_RectInParentCtrl.top = m_RectInParentCtrl.bottom - m_LayoutInfo.nHeight;
	}
	else if (m_LayoutInfo.clType == CL_G_RIGHT_TOP)
	{
		// �̶���С�����ϽǶ�λ
		m_RectInParentCtrl.right = nWidth - m_LayoutInfo.nRightSpace;
		m_RectInParentCtrl.left = m_RectInParentCtrl.right - m_LayoutInfo.nWidth;
		m_RectInParentCtrl.top = m_LayoutInfo.nTopSpace;
		m_RectInParentCtrl.bottom = m_RectInParentCtrl.top + m_LayoutInfo.nHeight;
	}
	else if (m_LayoutInfo.clType == CL_G_RIGHT_BOTTOM)
	{
		// �̶���С�����½Ƕ�λ
		m_RectInParentCtrl.right = nWidth - m_LayoutInfo.nRightSpace;
		m_RectInParentCtrl.left = m_RectInParentCtrl.right - m_LayoutInfo.nWidth;
		m_RectInParentCtrl.bottom = nHeight - m_LayoutInfo.nBottomSpace;
		m_RectInParentCtrl.top = m_RectInParentCtrl.bottom - m_LayoutInfo.nHeight;
	}
	else if (m_LayoutInfo.clType == CL_L_LEFT)
	{
		// ����䶯��С���������
		m_RectInParentCtrl.left = m_LayoutInfo.nLeftSpace;
		m_RectInParentCtrl.right = m_RectInParentCtrl.left + m_LayoutInfo.nWidth;
		m_RectInParentCtrl.top = m_LayoutInfo.nTopSpace;
		m_RectInParentCtrl.bottom = nHeight - m_LayoutInfo.nBottomSpace;
	}
	else if (m_LayoutInfo.clType == CL_L_RIGHT)
	{
		// ����䶯��С�������Ҳ�
		m_RectInParentCtrl.right = nWidth - m_LayoutInfo.nRightSpace;
		m_RectInParentCtrl.left = m_RectInParentCtrl.right - m_LayoutInfo.nWidth;
		m_RectInParentCtrl.top = m_LayoutInfo.nTopSpace;
		m_RectInParentCtrl.bottom = nHeight - m_LayoutInfo.nBottomSpace;
	}
	else if (m_LayoutInfo.clType == CL_L_TOP)
	{
		// ����䶯��С�������Ϸ�
		m_RectInParentCtrl.left = m_LayoutInfo.nLeftSpace;
		m_RectInParentCtrl.right = nWidth - m_LayoutInfo.nRightSpace;
		m_RectInParentCtrl.top = m_LayoutInfo.nTopSpace;
		m_RectInParentCtrl.bottom = m_RectInParentCtrl.top + m_LayoutInfo.nHeight;
	}
	else if (m_LayoutInfo.clType == CL_L_BOTTOM)
	{
		// ����䶯��С�������·�
		m_RectInParentCtrl.left = m_LayoutInfo.nLeftSpace;
		m_RectInParentCtrl.right = nWidth - m_LayoutInfo.nRightSpace;
		m_RectInParentCtrl.bottom = nHeight - m_LayoutInfo.nBottomSpace;
		m_RectInParentCtrl.top = m_RectInParentCtrl.bottom - m_LayoutInfo.nHeight;
	}
	else if (m_LayoutInfo.clType == CL_L_ALL)
	{
		// ����䶯��С������ȫ��
		m_RectInParentCtrl.right = nWidth;
		m_RectInParentCtrl.bottom = nHeight;
	}
	else if (m_LayoutInfo.clType == CL_L_MIDDLE)
	{
		// ����䶯��С������
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

// ȡ�ÿؼ��Ĵ�С
RECT IPropertyControlImpl::GetCtrlRect()
{
	RECT CtrlRct;
	INIT_RECT(CtrlRct);
	CtrlRct.right = RECT_WIDTH(m_RectInWindow);
	CtrlRct.bottom = RECT_HEIGHT(m_RectInWindow);
	return CtrlRct;
}

// ����ڸ��ؼ��Ĳ�����Ϣ
void IPropertyControlImpl::SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo)
{
	m_LayoutInfo = cliLayoutInfo;
}

CONTROL_LAYOUT_INFO IPropertyControlImpl::GetLayout()
{
	return m_LayoutInfo;
}

// �ؼ����ƣ�Ψһʶ�𴰿ڵı�־
void IPropertyControlImpl::SetName(char *pCtrlName)
{
	if (pCtrlName != NULL)
		m_strCtrlName = pCtrlName;
}

const char* IPropertyControlImpl::GetName()
{
	return m_strCtrlName.c_str();
}

// �϶��ؼ�����
void IPropertyControlImpl::SetDragControl(bool bDrag)
{
	m_bDragCtrl = bDrag;
}

bool IPropertyControlImpl::GetDragControl()
{
	return m_bDragCtrl;
}

// 1. �����յ������б�
bool IPropertyControlImpl::CreateEmptyPropList()
{
	m_ControlPropList.clear();

	// ����������
	IPropertyGroup *pBaseGroupProp = (IPropertyGroup *)CreateProperty(NULL, PT_GROUP, 1, "�ؼ���������", NULL);

	// �ؼ�����
	IPropertyBase* pNameProp = CreateProperty(pBaseGroupProp, PT_STRING, 1, "Name", "�ؼ�����");

	// Visible
	// Enable
	// �Ƿ���������Ϣ
	// ����
	// �Ƿ�֧�ֶ���

	return true;
}

// 2. ��xml�ļ����ؼ�����
bool IPropertyControlImpl::ReadPropFromControlsXml(const char* pszControlId)
{
	return true;
}

// 3. ����Builder��ʾ�õ�����
bool IPropertyControlImpl::CreateBuilderShowPropList()
{
	return true;
}

// ����һ������
IPropertyBase* IPropertyControlImpl::CreateProperty(IPropertyGroup *pPropGroup, PROP_TYPE propType, UINT nPropId, char *pPropName, char *pPropInfo)
{
	if (m_pSkinPropMgr == NULL)
		return NULL;

	return NULL;
}
