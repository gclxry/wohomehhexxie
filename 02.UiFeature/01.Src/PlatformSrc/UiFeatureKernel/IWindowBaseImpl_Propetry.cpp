//////////////////////////////////////////////////////////////////////////
// ObjectId��������
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

// ��xml�е��������õ�manager��
void IWindowBaseImpl::PP_SetWindowPropetry(IPropertyWindow *pWndPropInXml, bool bSetDftProp)
{
	if (pWndPropInXml == NULL)
		return;

	m_pXmlPropWindow = pWndPropInXml;
	CreateWindowPropetry(bSetDftProp);
}

// ����Object����
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

// ��������
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

// �Ƿ�֧��ȫ���ڵ���ƶ�
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

// �Ƿ����
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

IPropertyBase* IWindowBaseImpl::CreateWindowOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo)
{
	if (m_pSkinPropMgr == NULL || m_pXmlPropWindow == NULL || pszPropName == NULL || strlen(pszPropName) <= 0 || propType <= OTID_NONE || propType >= OTID_LAST)
		return NULL;

	if (pGroup == NULL)
		pGroup = m_pXmlPropWindow->GetWindowPropGroup();

	return CreateResourcePropetry(this, m_pSkinPropMgr, pGroup, propType, pszPropName, pszPropInfo);
}

// �����յ����Զ���
void IWindowBaseImpl::CreateWindowPropetry(bool bSetDftProp)
{
	if (m_pXmlPropWindow == NULL)
		return;

	// Group:base
	m_pPropGroupBase = (IPropertyGroup*)CreateWindowOnePropetry(NULL, OTID_GROUP, "WindowBase", "����/����������");
	if (m_pPropGroupBase == NULL)
		return;

	// base-��������
	m_pPropBase_TypeName = (IPropertyString*)CreateWindowOnePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_TYPE, "��ǰ Object ����");
	if (m_pPropBase_TypeName == NULL)
		return;
	m_pPropBase_TypeName->SetString(PROP_TYPE_WINDOW_NAME);

	// base-objectid
	m_pPropBase_ObjectId = (IPropertyString*)CreateWindowOnePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_OBJ_ID, "��ǰ Object Id");
	if (m_pPropBase_ObjectId == NULL)
		return;
	m_pPropBase_ObjectId->SetString((char*)m_pXmlPropWindow->GetObjectId());

	// base-name
	m_pPropBase_Name = (IPropertyString*)CreateWindowOnePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME, "��ǰ Object ����");
	if (m_pPropBase_Name == NULL)
		return;
	if (m_pPropBase_Name->GetString() != NULL && strlen(m_pPropBase_Name->GetString()) <= 0)
		m_pPropBase_Name->SetString("�½�����/���");

	// base-windowtitle
	m_pPropBase_WindowText = (IPropertyString*)CreateWindowOnePropetry(m_pPropGroupBase, OTID_STRING, "WindowText", "��ǰ���ڱ���");
	if (m_pPropBase_WindowText == NULL)
		return;
	if (m_pPropBase_WindowText->GetString() != NULL && strlen(m_pPropBase_WindowText->GetString()) <= 0)
		m_pPropBase_WindowText->SetString("�޴��ڱ���");

	// base-visible
	m_pPropBase_Visible = (IPropertyBool*)CreateWindowOnePropetry(m_pPropGroupBase, OTID_BOOL, "Visible", "�Ƿ�ɼ�");
	if (m_pPropBase_Visible == NULL)
		return;

	// base-����������ʾ��ť
	m_pPropBase_ShowInTaskbar = (IPropertyBool*)CreateWindowOnePropetry(m_pPropGroupBase, OTID_BOOL, "ShowInTaskbar", "�Ƿ�����������ʾ��ť");
	if (m_pPropBase_ShowInTaskbar == NULL)
		return;

	// base-֧�ֲַ㴰��
	m_pPropBase_Layered = (IPropertyBool*)CreateWindowOnePropetry(m_pPropGroupBase, OTID_BOOL, "LayeredWindow", "�Ƿ�֧�ֲַ㴰��");
	if (m_pPropBase_Layered == NULL)
		return;

	// base-topmost
	m_pPropBase_TopMost = (IPropertyBool*)CreateWindowOnePropetry(m_pPropGroupBase, OTID_BOOL, "TopMost", "�����Ƿ������ϲ�");
	if (m_pPropBase_TopMost == NULL)
		return;

//	// base-sysbase
//	m_pPropGroupSysBase = (IPropertyGroup*)CreateWindowOnePropetry(m_pPropGroupBase, OTID_GROUP, "SysBase", "����ϵͳ���ԣ�ֻ���ڴ��ڣ��������Ͳ�����");
//	if (m_pPropGroupSysBase == NULL)
//		return;
//
//	// base-sysbase-���
//	m_pPropSysBase_CanFullScreen = (IPropertyBool*)CreateWindowOnePropetry(m_pPropGroupSysBase, OTID_BOOL, "CanFullScreen", "�Ƿ�������");
//	if (m_pPropSysBase_CanFullScreen == NULL)
//		return;
//
//	// base-sysbase-��С��
//	m_pPropSysBase_CanMiniSize = (IPropertyBool*)CreateWindowOnePropetry(m_pPropGroupSysBase, OTID_BOOL, "CanMiniSize", "�Ƿ������С��");
//	if (m_pPropSysBase_CanMiniSize == NULL)
//		return;

	// Group-WindowSize
	m_pPropGroupWindowSize = (IPropertyGroup*)CreateWindowOnePropetry(NULL, OTID_GROUP, "WindowSize", "����/����С");
	if (m_pPropGroupWindowSize == NULL)
		return;

	// size-width
	m_pPropSize_WindowWidth = (IPropertyInt*)CreateWindowOnePropetry(m_pPropGroupWindowSize, OTID_INT, NAME_WINDOW_WIDTH, "���ڿ��");
	if (m_pPropSize_WindowWidth == NULL)
		return;

	// size-height
	m_pPropSize_WindowHeight = (IPropertyInt*)CreateWindowOnePropetry(m_pPropGroupWindowSize, OTID_INT, NAME_WINDOW_HEIGHT, "���ڸ߶�");
	if (m_pPropSize_WindowHeight == NULL)
		return;

	// Group-drag(��ק����)
	m_pPropGroupDrag = (IPropertyGroup*)CreateWindowOnePropetry(NULL, OTID_GROUP, "Drag", "��ק����");
	if (m_pPropGroupDrag == NULL)
		return;

	// drag-enable
	m_pPropDrag_Enable = (IPropertyBool*)CreateWindowOnePropetry(m_pPropGroupDrag, OTID_BOOL, "Enable", "�Ƿ�����϶����ڣ��洦�ƶ�");
	if (m_pPropDrag_Enable == NULL)
		return;

	// Group-Size(���ڵı仯��С)
	m_pPropGroupSize = (IPropertyGroup*)CreateWindowOnePropetry(NULL, OTID_GROUP, "WindowMaxMinSize", "���ڱ仯�ĳߴ�");
	if (m_pPropGroupSize == NULL)
		return;

	// Size-enable
	m_pPropSize_Enable = (IPropertyBool*)CreateWindowOnePropetry(m_pPropGroupSize, OTID_BOOL, "Enable", "�Ƿ����ô��ڵ����ߴ����С�ߴ�");
	if (m_pPropSize_Enable == NULL)
		return;

	// Size-MaxWidth
	m_pPropSize_MaxWidth = (IPropertyInt*)CreateWindowOnePropetry(m_pPropGroupSize, OTID_INT, "MaxWidth", "��������ȣ���λ������");
	if (m_pPropSize_MaxWidth == NULL)
		return;

	// Size-MaxHeight
	m_pPropSize_MaxHeight = (IPropertyInt*)CreateWindowOnePropetry(m_pPropGroupSize, OTID_INT, "MaxHeight", "�������߶ȣ���λ������");
	if (m_pPropSize_MaxHeight == NULL)
		return;

	// Size-MinWidth
	m_pPropSize_MinWidth = (IPropertyInt*)CreateWindowOnePropetry(m_pPropGroupSize, OTID_INT, "MinWidth", "������С��ȣ���λ������");
	if (m_pPropSize_MinWidth == NULL)
		return;

	// Size-MinHeight
	m_pPropSize_MinHeight = (IPropertyInt*)CreateWindowOnePropetry(m_pPropGroupSize, OTID_INT, "MinHeight", "������С�߶ȣ���λ������");
	if (m_pPropSize_MinHeight == NULL)
		return;

	// Group-stretching(���촰��)
	m_pPropGroupStretching = (IPropertyGroup*)CreateWindowOnePropetry(NULL, OTID_GROUP, "Stretching", "���촰��");
	if (m_pPropGroupStretching == NULL)
		return;

	// stretching-enable
	m_pPropStretching_Enable = (IPropertyBool*)CreateWindowOnePropetry(m_pPropGroupStretching, OTID_BOOL, "Enable", "�Ƿ�������촰�ڣ�ʹ���ڿ��Ա���С");
	if (m_pPropStretching_Enable == NULL)
		return;

	// stretching-leftspace
	m_pPropStretching_LeftSpace = (IPropertyInt*)CreateWindowOnePropetry(m_pPropGroupStretching, OTID_INT, "LeftSpace", "���촰�ڣ�����������̽�ⷶΧ");
	if (m_pPropStretching_LeftSpace == NULL)
		return;

	// stretching-rightspace
	m_pPropStretching_RightSpace = (IPropertyInt*)CreateWindowOnePropetry(m_pPropGroupStretching, OTID_INT, "RightSpace", "���촰�ڣ������Ҳ����̽�ⷶΧ");
	if (m_pPropStretching_RightSpace == NULL)
		return;

	// stretching-topspace
	m_pPropStretching_TopSpace = (IPropertyInt*)CreateWindowOnePropetry(m_pPropGroupStretching, OTID_INT, "TopSpace", "���촰�ڣ������Ϸ����̽�ⷶΧ");
	if (m_pPropStretching_TopSpace == NULL)
		return;

	// stretching-bottomspace
	m_pPropStretching_BottomSpace = (IPropertyInt*)CreateWindowOnePropetry(m_pPropGroupStretching, OTID_INT, "BottomSpace", "���촰�ڣ������·����̽�ⷶΧ");
	if (m_pPropStretching_BottomSpace == NULL)
		return;

//	// Group-WindowRgn
//	m_pPropGroupWindowRgn = (IPropertyGroup*)CreateWindowOnePropetry(NULL, OTID_GROUP, "WindowRgn", "���ڲü�");
//	if (m_pPropGroupWindowRgn == NULL)
//		return;

	if (bSetDftProp)
	{
		// ����Ĭ��ֵ
		m_pPropBase_WindowText->SetString("���ڱ���");
		m_pPropBase_Visible->SetValue(true);
		m_pPropBase_ShowInTaskbar->SetValue(true);
		m_pPropBase_Layered->SetValue(false);
		m_pPropBase_TopMost->SetValue(false);
//		m_pPropSysBase_CanFullScreen->SetValue(false);
//		m_pPropSysBase_CanMiniSize->SetValue(false);

		m_pPropSize_WindowWidth->SetValue(500);
		m_pPropSize_WindowHeight->SetValue(500);

		m_pPropDrag_Enable->SetValue(false);

		m_pPropStretching_Enable->SetValue(false);
		m_pPropStretching_LeftSpace->SetValue(0);
		m_pPropStretching_RightSpace->SetValue(0);
		m_pPropStretching_TopSpace->SetValue(0);
		m_pPropStretching_BottomSpace->SetValue(0);

		m_pPropSize_Enable->SetValue(false);
		m_pPropSize_MaxWidth->SetValue(0);
		m_pPropSize_MaxHeight->SetValue(0);
		m_pPropSize_MinWidth->SetValue(0);
		m_pPropSize_MinHeight->SetValue(0);
	}
}

bool IWindowBaseImpl::PP_GetLayeredWindow()
{
	if (m_pPropBase_Layered == NULL)
		return false;

	return m_pPropBase_Layered->GetValue();
}

// ���ô����͸������
void IWindowBaseImpl::PP_SetLayeredWindow(bool bIsLayered)
{
	if (m_pPropBase_Layered == NULL)
		return;
	m_pPropBase_Layered->SetValue(bIsLayered);

	DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if (bIsLayered)
	{
		// ͸��
		if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
		{
			dwExStyle |= WS_EX_LAYERED;
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle);
		}
	}
	else
	{
		// ��͸��
		if ((dwExStyle & WS_EX_LAYERED) == WS_EX_LAYERED)
		{
			dwExStyle &= (~WS_EX_LAYERED);
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle);
		}
	}
}

// ȡ���ӿؼ��������б�Layout.xml �еĲ���
PROP_CONTROL_VEC* IWindowBaseImpl::GetChildPropControlVec()
{
	if (m_pXmlPropWindow == NULL)
		return NULL;

	return m_pXmlPropWindow->GetChildPropControlVec();
}

// Builder�������޸ģ�����ˢ�½���
void IWindowBaseImpl::BD_RefreshWindowPropetry()
{
	// ���¼������пؼ���λ��
	if (m_pPropSize_WindowWidth == NULL || m_pPropSize_WindowHeight == NULL)
		return;
	OnSize(-1, m_pPropSize_WindowWidth->GetValue(), m_pPropSize_WindowHeight->GetValue());
}
