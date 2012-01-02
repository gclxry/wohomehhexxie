
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\ICommonFun.h"


// ��ʼ����builder�е�����
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

// �����յ����Զ���
void IControlBase::CreateCtrlPropetry()
{
	if (m_pXmlPropCtrl == NULL)
		return;

	// Group:base
	m_pPropGroupBase = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "WindowBase", "����/����������");
	if (m_pPropGroupBase == NULL)
		return;

	// base-��������
	m_pPropBase_TypeName = (IPropertyString*)CreatePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_TYPE, "��ǰ Object ����");
	if (m_pPropBase_TypeName == NULL)
		return;
	m_pPropBase_TypeName->SetString(PROP_TYPE_WINDOW_NAME);

	// base-objectid
	m_pPropBase_ObjectId = (IPropertyString*)CreatePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_OBJ_ID, "��ǰ Object Id");
	if (m_pPropBase_ObjectId == NULL)
		return;
	m_pPropBase_ObjectId->SetString((char*)m_pXmlPropCtrl->GetObjectId());

	// base-name
	m_pPropBase_Name = (IPropertyString*)CreatePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME, "��ǰ Object ����");
	if (m_pPropBase_Name == NULL)
		return;
	if (m_pPropBase_Name->GetString() != NULL && strlen(m_pPropBase_Name->GetString()) <= 0)
		m_pPropBase_Name->SetString("�½�����/���");

	// base-windowtitle
	m_pPropBase_WindowText = (IPropertyString*)CreatePropetry(m_pPropGroupBase, OTID_STRING, "WindowText", "��ǰ���ڱ���");
	if (m_pPropBase_WindowText == NULL)
		return;
	if (m_pPropBase_WindowText->GetString() != NULL && strlen(m_pPropBase_WindowText->GetString()) <= 0)
		m_pPropBase_WindowText->SetString("�޴��ڱ���");

	// base-visible
	m_pPropBase_Visible = (IPropertyBool*)CreatePropetry(m_pPropGroupBase, OTID_BOOL, "Visible", "�Ƿ�ɼ�");
	if (m_pPropBase_Visible == NULL)
		return;

	// base-֧�ֲַ㴰��
	m_pPropBase_Layered = (IPropertyBool*)CreatePropetry(m_pPropGroupBase, OTID_BOOL, "LayeredWindow", "�Ƿ�֧�ֲַ㴰��");
	if (m_pPropBase_Layered == NULL)
		return;

	// base-topmost
	m_pPropBase_TopMost = (IPropertyBool*)CreatePropetry(m_pPropGroupBase, OTID_BOOL, "TopMost", "�����Ƿ������ϲ�");
	if (m_pPropBase_TopMost == NULL)
		return;

	// base-sysbase
	m_pPropGroupSysBase = (IPropertyGroup*)CreatePropetry(m_pPropGroupBase, OTID_GROUP, "SysBase", "����ϵͳ���ԣ�ֻ���ڴ��ڣ��������Ͳ�����");
	if (m_pPropGroupSysBase == NULL)
		return;

	// base-sysbase-���
	m_pPropSysBase_CanFullScreen = (IPropertyBool*)CreatePropetry(m_pPropGroupSysBase, OTID_BOOL, "CanFullScreen", "�Ƿ�������");
	if (m_pPropSysBase_CanFullScreen == NULL)
		return;

	// base-sysbase-��С��
	m_pPropSysBase_CanMiniSize = (IPropertyBool*)CreatePropetry(m_pPropGroupSysBase, OTID_BOOL, "CanMiniSize", "�Ƿ������С��");
	if (m_pPropSysBase_CanMiniSize == NULL)
		return;

	// base-sysbase-��С�ߴ�
	// base-sysbase-���ߴ�

	// Group-size
	m_pPropGroupSize = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Size", "����/����С");
	if (m_pPropGroupSize == NULL)
		return;

	// size-width
	m_pPropSize_Width = (IPropertyInt*)CreatePropetry(m_pPropGroupSize, OTID_INT, "Width", "���ڿ��");
	if (m_pPropSize_Width == NULL)
		return;

	// size-height
	m_pPropSize_Height = (IPropertyInt*)CreatePropetry(m_pPropGroupSize, OTID_INT, "Height", "���ڸ߶�");
	if (m_pPropSize_Height == NULL)
		return;

	// Group-drag(��ק����)
	m_pPropGroupDrag = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Drag", "��ק����");
	if (m_pPropGroupDrag == NULL)
		return;

	// drag-enable
	m_pPropDrag_Enable = (IPropertyBool*)CreatePropetry(m_pPropGroupDrag, OTID_BOOL, "Enable", "�Ƿ�����϶����ڣ��洦�ƶ�");
	if (m_pPropDrag_Enable == NULL)
		return;

	// Group-stretching(���촰��)
	m_pPropGroupStretching = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Stretching", "���촰��");
	if (m_pPropGroupStretching == NULL)
		return;

	// stretching-enable
	m_pPropStretching_Enable = (IPropertyBool*)CreatePropetry(m_pPropGroupStretching, OTID_BOOL, "Enable", "�Ƿ�������촰�ڣ�ʹ���ڿ��Ա���С");
	if (m_pPropStretching_Enable == NULL)
		return;

	// stretching-leftspace
	m_pPropStretching_LeftSpace = (IPropertyInt*)CreatePropetry(m_pPropGroupStretching, OTID_INT, "LeftSpace", "���촰�ڣ�����������̽�ⷶΧ");
	if (m_pPropStretching_LeftSpace == NULL)
		return;

	// stretching-rightspace
	m_pPropStretching_RightSpace = (IPropertyInt*)CreatePropetry(m_pPropGroupStretching, OTID_INT, "RightSpace", "���촰�ڣ������Ҳ����̽�ⷶΧ");
	if (m_pPropStretching_RightSpace == NULL)
		return;

	// stretching-topspace
	m_pPropStretching_TopSpace = (IPropertyInt*)CreatePropetry(m_pPropGroupStretching, OTID_INT, "TopSpace", "���촰�ڣ������Ϸ����̽�ⷶΧ");
	if (m_pPropStretching_TopSpace == NULL)
		return;

	// stretching-bottomspace
	m_pPropStretching_BottomSpace = (IPropertyInt*)CreatePropetry(m_pPropGroupStretching, OTID_INT, "BottomSpace", "���촰�ڣ������·����̽�ⷶΧ");
	if (m_pPropStretching_BottomSpace == NULL)
		return;

	//	// Group-WindowRgn
	//	m_pPropGroupWindowRgn = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "WindowRgn", "���ڲü�");
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

// ��������
void IControlBase::SetEnable(bool bEnable)
{
	m_bEnable = bEnable;
}

bool IControlBase::IsEnable()
{
	return m_bEnable;
}

// �ɼ�����
void IControlBase::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

bool IControlBase::IsVisible()
{
	return m_bVisible;
}

// �Ƿ���������Ϣ
void IControlBase::SetReceiveMouseMessage(bool bIsReceive)
{
	m_bIsReceiveMouseMsg = bIsReceive;
}

bool IControlBase::GetReceiveMouseMessage()
{
	return m_bIsReceiveMouseMsg;
}

// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ŵĴ��ڵ�
void IControlBase::SetCtrlInWindowRect(RECT CtrlWndRct)
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

RECT IControlBase::GetCtrlInWindowRect()
{
	return m_RectInWindow;
}

RECT IControlBase::GetCtrlInControlRect()
{
	return m_RectInParentCtrl;
}

// ȡ�ÿؼ��Ĵ�С
RECT IControlBase::GetCtrlRect()
{
	RECT CtrlRct;
	INIT_RECT(CtrlRct);
	CtrlRct.right = RECT_WIDTH(m_RectInWindow);
	CtrlRct.bottom = RECT_HEIGHT(m_RectInWindow);
	return CtrlRct;
}

// ����ڸ��ؼ��Ĳ�����Ϣ
void IControlBase::SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo)
{
	m_LayoutInfo = cliLayoutInfo;
}

CONTROL_LAYOUT_INFO IControlBase::GetLayout()
{
	return m_LayoutInfo;
}

// �ؼ����ƣ�Ψһʶ�𴰿ڵı�־
void IControlBase::PP_SetObjectName(char *pCtrlName)
{
	if (pCtrlName != NULL)
		m_strCtrlName = pCtrlName;
}

const char* IControlBase::PP_GetObjectName()
{
	return m_strCtrlName.c_str();
}

// �϶��ؼ�����
void IControlBase::SetDragControl(bool bDrag)
{
	m_bDragCtrl = bDrag;
}

bool IControlBase::GetDragControl()
{
	return m_bDragCtrl;
}

// 1. �����յ������б�
bool IControlBase::CreateEmptyPropList()
{
	// ����������
	IPropertyGroup *pBaseGroupProp = (IPropertyGroup *)CreateProperty(NULL, OTID_GROUP, "�ؼ���������", NULL);

	// �ؼ�����(ֻ��)
	// �ؼ�ID(ֻ��)

	// �ؼ�����
	IPropertyBase* pNameProp = CreateProperty(pBaseGroupProp, OTID_STRING, "Name", "�ؼ�����");

	// Visible
	// Enable
	// �Ƿ���������Ϣ
	// ����
	// �Ƿ�֧�ֶ���

	return true;
}

// 2.��Builder���´���һ���ؼ�����Ҫ��ʼ�����Ե�PropId
bool IControlBase::InitObjectIdByBuilder(const char* pszBaseId)
{
	if (pszBaseId == NULL || m_pSkinPropMgr == NULL || m_pOwnerWindowBase == NULL || m_pOwnerWindowBase->GetObjectType() == NULL)
		return false;

	string strCtrlType = m_pOwnerWindowBase->GetObjectType();
	if (strCtrlType.size() <= 0)
		return false;

	// ���ÿؼ������ObjectId
	int nId = m_pSkinPropMgr->GetNewId();
	char szId[1024];
	memset(szId, 0, 1024);
	sprintf_s(szId, 1023, "%s.%s%d", pszBaseId, strCtrlType.c_str(), nId);
	SetObjectType(szId);

	// ѭ���������Ե�ID
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

// 2. ��xml�ļ����ؼ�����
bool IControlBase::ReadPropFromControlsXml(const char* pszControlId)
{
	return true;
}

// 3. ����Builder��ʾ�õ�����
bool IControlBase::CreateBuilderShowPropList()
{
	return true;
}

// ����һ������
IPropertyBase* IControlBase::CreateProperty(IPropertyGroup *pPropGroup, OBJECT_TYPE_ID propType, char *pPropName, char *pPropInfo)
{
	if (m_pSkinPropMgr == NULL)
		return NULL;

	return NULL;
}

// ���ø����ؼ�
void IControlBase::SetPropertySkinManager(IPropertySkinManager *pMgr)
{
	m_pSkinPropMgr = pMgr;
}
