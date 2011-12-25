
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

// ��������
void IPropertyControlInWindow::SetEnable(bool bEnable)
{
	m_bEnable = bEnable;
}

bool IPropertyControlInWindow::IsEnable()
{
	return m_bEnable;
}

// ���ø����ؼ�
void IPropertyControlInWindow::SetControlBase(IControlBase *pCtrl)
{
	m_pBaseCtrl = pCtrl;
}

IControlBase* IPropertyControlInWindow::GetControlBase()
{
	return m_pBaseCtrl;
}

// �ɼ�����
void IPropertyControlInWindow::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

bool IPropertyControlInWindow::IsVisible()
{
	return m_bVisible;
}

// �Ƿ���������Ϣ
void IPropertyControlInWindow::SetReceiveMouseMessage(bool bIsReceive)
{
	m_bIsReceiveMouseMsg = bIsReceive;
}

bool IPropertyControlInWindow::GetReceiveMouseMessage()
{
	return m_bIsReceiveMouseMsg;
}

// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ŵĴ��ڵ�
void IPropertyControlInWindow::SetCtrlInWindowRect(RECT CtrlWndRct)
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

RECT IPropertyControlInWindow::GetCtrlInWindowRect()
{
	return m_RectInWindow;
}

RECT IPropertyControlInWindow::GetCtrlInControlRect()
{
	return m_RectInParentCtrl;
}

// ȡ�ÿؼ��Ĵ�С
RECT IPropertyControlInWindow::GetCtrlRect()
{
	RECT CtrlRct;
	INIT_RECT(CtrlRct);
	CtrlRct.right = RECT_WIDTH(m_RectInWindow);
	CtrlRct.bottom = RECT_HEIGHT(m_RectInWindow);
	return CtrlRct;
}

// ����ڸ��ؼ��Ĳ�����Ϣ
void IPropertyControlInWindow::SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo)
{
	m_LayoutInfo = cliLayoutInfo;
}

CONTROL_LAYOUT_INFO IPropertyControlInWindow::GetLayout()
{
	return m_LayoutInfo;
}

// �ؼ����ƣ�Ψһʶ�𴰿ڵı�־
void IPropertyControlInWindow::SetName(char *pCtrlName)
{
	if (pCtrlName != NULL)
		m_strCtrlName = pCtrlName;
}

const char* IPropertyControlInWindow::GetName()
{
	return m_strCtrlName.c_str();
}

// �϶��ؼ�����
void IPropertyControlInWindow::SetDragControl(bool bDrag)
{
	m_bDragCtrl = bDrag;
}

bool IPropertyControlInWindow::GetDragControl()
{
	return m_bDragCtrl;
}

// 1. �����յ������б�
bool IPropertyControlInWindow::CreateEmptyPropList()
{
	m_ControlPropList.clear();

	// ����������
	IPropertyGroup *pBaseGroupProp = (IPropertyGroup *)CreateProperty(NULL, PT_GROUP, "�ؼ���������", NULL);

	// �ؼ�����(ֻ��)
	// �ؼ�ID(ֻ��)

	// �ؼ�����
	IPropertyBase* pNameProp = CreateProperty(pBaseGroupProp, PT_STRING, "Name", "�ؼ�����");

	// Visible
	// Enable
	// �Ƿ���������Ϣ
	// ����
	// �Ƿ�֧�ֶ���

	return true;
}

// 2.��Builder���´���һ���ؼ�����Ҫ��ʼ�����Ե�PropId
bool IPropertyControlInWindow::InitObjectIdByBuilder(const char* pszBaseId)
{
	if (pszBaseId == NULL || m_pSkinPropMgr == NULL || m_pBaseCtrl == NULL || m_pBaseCtrl->GetObjectType() == NULL)
		return false;

	string strCtrlType = m_pBaseCtrl->GetObjectType();
	if (strCtrlType.size() <= 0)
		return false;

	// ���ÿؼ������ObjectId
	int nId = m_pSkinPropMgr->GetNewId();
	char szId[1024];
	memset(szId, 0, 1024);
	sprintf_s(szId, 1023, "%s.%s%d", pszBaseId, strCtrlType.c_str(), nId);
	SetObjectType(szId);

	// ѭ���������Ե�ID
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

// 2. ��xml�ļ����ؼ�����
bool IPropertyControlInWindow::ReadPropFromControlsXml(const char* pszControlId)
{
	return true;
}

// 3. ����Builder��ʾ�õ�����
bool IPropertyControlInWindow::CreateBuilderShowPropList()
{
	return true;
}

// ����һ������
IPropertyBase* IPropertyControlInWindow::CreateProperty(IPropertyGroup *pPropGroup, PROP_TYPE propType, char *pPropName, char *pPropInfo)
{
	if (m_pSkinPropMgr == NULL)
		return NULL;

	return NULL;
}
