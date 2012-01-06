
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\ICommonFun.h"


// ��ʼ����builder�е�����
bool IControlBase::BD_InitControlBase(IPropertyControl *pCtrlProp, bool bNeedSetDftProp)
{
	if (pCtrlProp == NULL)
		return false;

	m_pXmlPropCtrl = m_pXmlPropCtrl;
	CreateCtrlAllPropetry(bNeedSetDftProp);
	// �ؼ�����
	OnCreate();
	return true;
}

IPropertyControl* IControlBase::PP_GetControlPropetry()
{
	return m_pXmlPropCtrl;
}

IPropertyBase* IControlBase::CreateCtrlOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo)
{
	if (m_pSkinPropMgr == NULL || m_pXmlPropCtrl == NULL || pszPropName == NULL || strlen(pszPropName) <= 0 || propType <= OTID_NONE || propType >= OTID_LAST)
		return NULL;

	if (pGroup == NULL)
		pGroup = m_pXmlPropCtrl->GetCtrlGroupProp();

	return CreateResourcePropetry(m_pSkinPropMgr, pGroup, propType, pszPropName, pszPropInfo);
}

// �����յ����Զ���
void IControlBase::CreateCtrlAllPropetry(bool bNeedSetDftProp)
{
	if (m_pXmlPropCtrl == NULL)
		return;

	// Group:base
	m_pPropGroupBase = (IPropertyGroup*)CreateCtrlOnePropetry(NULL, OTID_GROUP, "ControlBase", "�ؼ���������");
	if (m_pPropGroupBase == NULL)
		return;

	// base-��������
	m_pPropBase_TypeName = (IPropertyString*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_TYPE, "�ؼ�����");
	if (m_pPropBase_TypeName == NULL)
		return;
	m_pPropBase_TypeName->SetString((char*)this->GetObjectType());

	// base-objectid
	m_pPropBase_ObjectId = (IPropertyString*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_OBJ_ID, "�ؼ� Object Id");
	if (m_pPropBase_ObjectId == NULL)
		return;
	m_pPropBase_ObjectId->SetString((char*)this->GetObjectId());

	// base-name
	m_pPropBase_Name = (IPropertyString*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME, "�ؼ�����");
	if (m_pPropBase_Name == NULL)
		return;
	if (m_pPropBase_Name->GetString() != NULL && strlen(m_pPropBase_Name->GetString()) <= 0)
		m_pPropBase_Name->SetString("�½��ؼ�");

	// base-visible
	m_pPropBase_Visible = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "Visible", "�Ƿ�ɼ�");
	if (m_pPropBase_Visible == NULL)
		return;

	// base-visible
	m_pPropBase_Enable = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "Enable", "�Ƿ����");
	if (m_pPropBase_Enable == NULL)
		return;

	// base-ReceiveMouseMessage
	m_pPropBase_RcvMouseMsg = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "ReceiveMouseMessage", "�Ƿ���������Ϣ");
	if (m_pPropBase_RcvMouseMsg == NULL)
		return;

	// base-DragInCtrl
	m_pPropBase_DragInCtrl = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "DragInCtrl", "�ؼ��ڲ��Ƿ���������ק��Ϣ");
	if (m_pPropBase_DragInCtrl == NULL)
		return;

	// tab ��˳��
	// base-taborder
	m_pPropBase_TabOrder = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_INT, "TabOrder", "tab������ת��ţ�0Ϊ������tab��");
	if (m_pPropBase_TabOrder == NULL)
		return;

	// �Ƿ�ΪĬ�ϻس����ܼ�
	// base-defaultenterctrl
	m_pPropBase_DefaultEnterCtrl = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "DefaultEnterCtrl", "�ؼ��Ƿ�Ϊ��ǰ�Ի���Ĭ�ϻس������տؼ�");
	if (m_pPropBase_DefaultEnterCtrl == NULL)
		return;

	// �ؼ�����
	// Group:base-layout
	m_pPropBase_LayoutGroup = (IPropertyGroup*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_GROUP, "Layout", "�ؼ�������Ϣ");
	if (m_pPropBase_LayoutGroup == NULL)
		return;

	// layout-width
	m_pPropBase_Layout_Width = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_INT, "Width", "���ڿ��");
	if (m_pPropBase_Layout_Width == NULL)
		return;

	// layout-height
	m_pPropBase_Layout_Height = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_INT, "Height", "���ڸ߶�");
	if (m_pPropBase_Layout_Height == NULL)
		return;

	// layout-layoutType
	m_pPropBase_Layout_Layout = (IPropertyComboBox*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_COMBOBOX, NAME_LAYOUT_TYPE, "�ؼ�����ڸ��ؼ�/���ڵĲ�������");
	if (m_pPropBase_Layout_Layout == NULL)
		return;
	if (!m_pPropBase_Layout_Layout->IsRightData())
	{
		COMBOBOX_PROP* pComboBox = m_pPropBase_Layout_Layout->GetComboBoxData();
		if (pComboBox != NULL)
		{
			pComboBox->DataVec.clear();
			pComboBox->DataVec.push_back(TN_CL_G_LEFT_TOP);
			pComboBox->DataVec.push_back(TN_CL_G_LEFT_BOTTOM);
			pComboBox->DataVec.push_back(TN_CL_G_RIGHT_TOP);
			pComboBox->DataVec.push_back(TN_CL_G_RIGHT_BOTTOM);
			pComboBox->DataVec.push_back(TN_CL_L_LEFT);
			pComboBox->DataVec.push_back(TN_CL_L_RIGHT);
			pComboBox->DataVec.push_back(TN_CL_L_TOP);
			pComboBox->DataVec.push_back(TN_CL_L_BOTTOM);
			pComboBox->DataVec.push_back(TN_CL_L_ALL);
			pComboBox->DataVec.push_back(TN_CL_L_MIDDLE);
			pComboBox->nSelect = CL_G_LEFT_TOP;
		}
	}

	// layout-leftspace
	m_pPropBase_Layout_LeftSpace = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_INT, "LeftSpace", "���븸�ؼ�/����������");
	if (m_pPropBase_Layout_LeftSpace == NULL)
		return;

	// layout-rightspace
	m_pPropBase_Layout_RightSpace = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_INT, "RightSpace", "���븸�ؼ�/�����Ҳ����");
	if (m_pPropBase_Layout_RightSpace == NULL)
		return;

	// layout-topspace
	m_pPropBase_Layout_TopSpace = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_INT, "TopSpace", "���븸�ؼ�/�����Ϸ�����");
	if (m_pPropBase_Layout_TopSpace == NULL)
		return;

	// layout-bottomspace
	m_pPropBase_Layout_BottomSpace = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_INT, "BottomSpace", "���븸�ؼ�/�����·�����");
	if (m_pPropBase_Layout_BottomSpace == NULL)
		return;

	// Group:base-layout
	m_pPropGroupCtrlDefs = (IPropertyGroup*)CreateCtrlOnePropetry(NULL, OTID_GROUP, "ControlPropetry", "�ؼ��Զ���������Ϣ");
	if (m_pPropGroupCtrlDefs == NULL)
		return;

	if (bNeedSetDftProp)
	{
		m_pPropBase_Visible->SetValue(true);
		m_pPropBase_RcvMouseMsg->SetValue(true);
		m_pPropBase_Enable->SetValue(true);
		m_pPropBase_DragInCtrl->SetValue(false);
		m_pPropBase_TabOrder->SetValue(0);
		m_pPropBase_DefaultEnterCtrl->SetValue(false);
		m_pPropBase_Layout_Width->SetValue(20);
		m_pPropBase_Layout_Height->SetValue(20);
		m_pPropBase_Layout_LeftSpace->SetValue(0);
		m_pPropBase_Layout_RightSpace->SetValue(0);
		m_pPropBase_Layout_TopSpace->SetValue(0);
		m_pPropBase_Layout_BottomSpace->SetValue(0);
	}

	// �ؼ������Զ��������
	CreateControlPropetry(bNeedSetDftProp);
}

IPropertyBase* IControlBase::CreatePropetry(OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo)
{
	if (m_pPropGroupCtrlDefs == NULL || m_pSkinPropMgr == NULL || m_pXmlPropCtrl == NULL || pszPropName == NULL || strlen(pszPropName) <= 0 || propType <= OTID_NONE || propType >= OTID_LAST)
		return NULL;

	return CreateResourcePropetry(m_pSkinPropMgr, m_pPropGroupCtrlDefs, propType, pszPropName, pszPropInfo);
}








//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// ��������
void IControlBase::SetEnable(bool bEnable, bool bSetChild)
{
	if (m_pPropBase_Enable != NULL)
		m_pPropBase_Enable->SetValue(bEnable);

	// �����ӿؼ�
	if (bSetChild)
	{
		for (CHILD_CTRLS_VEC::iterator pCtrlItem = m_ChildCtrlsVec.begin(); pCtrlItem != m_ChildCtrlsVec.end(); pCtrlItem++)
		{
			IControlBase* pCtrl = *pCtrlItem;
			if (pCtrl == NULL)
				continue;

			pCtrl->SetEnable(bEnable);
		}
	}
}

bool IControlBase::IsEnable()
{
	if (m_pPropBase_Enable == NULL)
		return true;

	return m_pPropBase_Enable->GetValue();
}

// �ɼ�����
void IControlBase::SetVisible(bool bVisible, bool bSetChild)
{
	if (m_pPropBase_Visible != NULL)
		m_pPropBase_Visible->SetValue(bVisible);

	// �����ӿؼ�
	if (bSetChild)
	{
		for (CHILD_CTRLS_VEC::iterator pCtrlItem = m_ChildCtrlsVec.begin(); pCtrlItem != m_ChildCtrlsVec.end(); pCtrlItem++)
		{
			IControlBase* pCtrl = *pCtrlItem;
			if (pCtrl == NULL)
				continue;

			pCtrl->SetVisible(bVisible);
		}
	}
}

bool IControlBase::IsVisible()
{
	if (m_pPropBase_Visible == NULL)
		return true;

	return m_pPropBase_Visible->GetValue();
}

const char * IControlBase::PP_GetControlObjectName()
{
	if (m_pPropBase_Name == NULL)
		return NULL;

	return m_pPropBase_Name->GetString();
}

// �Ƿ���������Ϣ
void IControlBase::SetReceiveMouseMessage(bool bIsReceive)
{
	if (m_pPropBase_RcvMouseMsg != NULL)
		m_pPropBase_RcvMouseMsg->SetValue(bIsReceive);
}

bool IControlBase::GetReceiveMouseMessage()
{
	return m_pPropBase_RcvMouseMsg->GetValue();
}

// �϶��ؼ�����
void IControlBase::SetDragInControl(bool bDrag)
{
	if (m_pPropBase_DragInCtrl != NULL)
		m_pPropBase_DragInCtrl->SetValue(bDrag);
}

bool IControlBase::GetDragInControl()
{
	return m_pPropBase_DragInCtrl->GetValue();
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

// ���ø����ؼ�
void IControlBase::SetPropertySkinManager(IPropertySkinManager *pMgr)
{
	m_pSkinPropMgr = pMgr;
}
