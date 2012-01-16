
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\ICommonFun.h"


// 初始化在builder中的属性
bool IControlBase::BD_InitControlBase(IPropertyControl *pCtrlProp, bool bNeedSetDftProp)
{
	if (pCtrlProp == NULL)
		return false;

	m_pXmlPropCtrl = pCtrlProp;
	CreateCtrlAllPropetry(bNeedSetDftProp);
	// 控件创建
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
		pGroup = m_pXmlPropCtrl->GetControlPropGroup();

	return CreateResourcePropetry(this, m_pSkinPropMgr, pGroup, propType, pszPropName, pszPropInfo);
}

// 创建空的属性队列
void IControlBase::CreateCtrlAllPropetry(bool bNeedSetDftProp)
{
	if (m_pXmlPropCtrl == NULL)
		return;

	// Group:base
	m_pPropGroupBase = (IPropertyGroup*)CreateCtrlOnePropetry(NULL, OTID_GROUP, "ControlBase", "控件基本属性");
	if (m_pPropGroupBase == NULL)
		return;

	// base-类型名称
	m_pPropBase_TypeName = (IPropertyString*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_TYPE, "控件类型");
	if (m_pPropBase_TypeName == NULL)
		return;
	m_pPropBase_TypeName->SetString((char*)this->GetObjectType());

	// base-objectid
	m_pPropBase_ObjectId = (IPropertyString*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_OBJ_ID, "控件 Object Id");
	if (m_pPropBase_ObjectId == NULL)
		return;
	m_pPropBase_ObjectId->SetString((char*)this->GetObjectId());

	// base-name
	m_pPropBase_Name = (IPropertyString*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME, "控件名称");
	if (m_pPropBase_Name == NULL)
		return;
	if (m_pPropBase_Name->GetString() != NULL && strlen(m_pPropBase_Name->GetString()) <= 0)
		m_pPropBase_Name->SetString("新建控件");

	// base-lock
	m_pPropBase_Lock = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "Lock", "是否锁定在Builder中鼠标改变控件大小和位置");
	if (m_pPropBase_Lock == NULL)
		return;

	// base-visible
	m_pPropBase_Visible = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "Visible", "是否可见");
	if (m_pPropBase_Visible == NULL)
		return;

	// base-enable
	m_pPropBase_Enable = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "Enable", "是否可用");
	if (m_pPropBase_Enable == NULL)
		return;

	// base-ReceiveMouseMessage
	m_pPropBase_RcvMouseMsg = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "ReceiveMouseMessage", "是否接收鼠标消息");
	if (m_pPropBase_RcvMouseMsg == NULL)
		return;

	// base-DragInCtrl
	m_pPropBase_DragInCtrl = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "DragInCtrl", "控件内部是否接受鼠标拖拽消息");
	if (m_pPropBase_DragInCtrl == NULL)
		return;

	// tab 键顺序
	// base-taborder
	m_pPropBase_TabOrder = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_INT, "TabOrder", "tab键的跳转序号，0为不接受tab键");
	if (m_pPropBase_TabOrder == NULL)
		return;

	// 是否为默认回车接受键
	// base-defaultenterctrl
	m_pPropBase_DefaultEnterCtrl = (IPropertyBool*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_BOOL, "DefaultEnterCtrl", "控件是否为当前对话框默认回车键接收控件");
	if (m_pPropBase_DefaultEnterCtrl == NULL)
		return;

	// 控件布局
	// Group:base-layout
	m_pPropBase_LayoutGroup = (IPropertyGroup*)CreateCtrlOnePropetry(m_pPropGroupBase, OTID_GROUP, "Layout", "控件布局信息");
	if (m_pPropBase_LayoutGroup == NULL)
		return;

	// layout-width
	m_pPropBase_Layout_Width = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_INT, NAME_LAYOUT_WIDTH, "窗口宽度");
	if (m_pPropBase_Layout_Width == NULL)
		return;

	// layout-height
	m_pPropBase_Layout_Height = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_INT, NAME_LAYOUT_HEIGHT, "窗口高度");
	if (m_pPropBase_Layout_Height == NULL)
		return;

	// layout-layoutType
	m_pPropBase_Layout_Layout = (IPropertyComboBox*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_COMBOBOX, NAME_LAYOUT_TYPE, "控件相对于父控件/窗口的布局类型");
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
	m_pPropBase_Layout_LeftSpace = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_INT, NAME_LAYOUT_LEFTSPACE, "距离父控件/窗口左侧距离");
	if (m_pPropBase_Layout_LeftSpace == NULL)
		return;

	// layout-rightspace
	m_pPropBase_Layout_RightSpace = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_INT, NAME_LAYOUT_RIGHTSPACE, "距离父控件/窗口右侧距离");
	if (m_pPropBase_Layout_RightSpace == NULL)
		return;

	// layout-topspace
	m_pPropBase_Layout_TopSpace = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_INT, NAME_LAYOUT_TOPSPACE, "距离父控件/窗口上方距离");
	if (m_pPropBase_Layout_TopSpace == NULL)
		return;

	// layout-bottomspace
	m_pPropBase_Layout_BottomSpace = (IPropertyInt*)CreateCtrlOnePropetry(m_pPropBase_LayoutGroup, OTID_INT, NAME_LAYOUT_BOTTOMSPACE, "距离父控件/窗口下方距离");
	if (m_pPropBase_Layout_BottomSpace == NULL)
		return;

	// Group:base-layout
	m_pPropGroupCtrlDefs = (IPropertyGroup*)CreateCtrlOnePropetry(NULL, OTID_GROUP, "ControlPropetry", "控件自定义属性信息");
	if (m_pPropGroupCtrlDefs == NULL)
		return;

	if (bNeedSetDftProp)
	{
		m_pPropBase_Lock->SetValue(false);
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

	// 从属性更新数据到成员变量
	PropetyValueToMemberValue();

	// 控件创建自定义的属性
	CreateControlPropetry(bNeedSetDftProp);
}

IPropertyBase* IControlBase::CreatePropetry(OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo)
{
	if (m_pPropGroupCtrlDefs == NULL || m_pSkinPropMgr == NULL || m_pXmlPropCtrl == NULL || pszPropName == NULL || strlen(pszPropName) <= 0 || propType <= OTID_NONE || propType >= OTID_LAST)
		return NULL;

	return CreateResourcePropetry(this, m_pSkinPropMgr, m_pPropGroupCtrlDefs, propType, pszPropName, pszPropInfo);
}


// 从属性更新数据到成员变量
void IControlBase::PropetyValueToMemberValue()
{
	if (m_pOwnerWindowBase == NULL)
		return;

	RECT ParentRct;
	INIT_RECT(ParentRct);
	FANGKUAI_8* pFk8 = NULL;
	if (m_pParentCtrl == NULL)
	{
		ParentRct = m_pOwnerWindowBase->GetClientRect();
		pFk8 = m_pOwnerWindowBase->BD_GetFangKuai8Rect();
	}
	else
	{
		ParentRct = m_pParentCtrl->GetWindowRect();
		pFk8 = m_pParentCtrl->BD_GetFangKuai8Rect();
	}

	if (pFk8 == NULL)
		return;

	m_pOwnerWindowBase->SetControlWindowPostion(this, ParentRct);

	m_BD_FangKuai8.EntityRct.left = pFk8->EntityRct.left + (m_RectInWindow.left - ParentRct.left);
	m_BD_FangKuai8.EntityRct.right = m_BD_FangKuai8.EntityRct.left + RECT_WIDTH(m_RectInWindow);
	m_BD_FangKuai8.EntityRct.top = pFk8->EntityRct.top + (m_RectInWindow.top - ParentRct.top);
	m_BD_FangKuai8.EntityRct.bottom = m_BD_FangKuai8.EntityRct.top + RECT_HEIGHT(m_RectInWindow);

	// 通知控件属性刷新了
	this->OnBuilderRefreshProp();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// 可用属性
void IControlBase::SetEnable(bool bEnable, bool bSetChild)
{
	if (m_pPropBase_Enable != NULL)
		m_pPropBase_Enable->SetValue(bEnable);

	// 设置子控件
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

// 可见属性
void IControlBase::SetVisible(bool bVisible, bool bSetChild)
{
	if (m_pPropBase_Visible != NULL)
		m_pPropBase_Visible->SetValue(bVisible);

	// 设置子控件
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

// 是否接受鼠标消息
void IControlBase::SetReceiveMouseMessage(bool bIsReceive)
{
	if (m_pPropBase_RcvMouseMsg != NULL)
		m_pPropBase_RcvMouseMsg->SetValue(bIsReceive);
}

bool IControlBase::GetReceiveMouseMessage()
{
	return m_pPropBase_RcvMouseMsg->GetValue();
}

// 拖动控件属性
void IControlBase::SetDragInControl(bool bDrag)
{
	if (m_pPropBase_DragInCtrl != NULL)
		m_pPropBase_DragInCtrl->SetValue(bDrag);
}

bool IControlBase::GetDragInControl()
{
	return m_pPropBase_DragInCtrl->GetValue();
}

CONTROL_LAYOUT_INFO IControlBase::GetLayout()
{
	CONTROL_LAYOUT_INFO LayoutInfo;
	memset(&LayoutInfo, 0, sizeof(CONTROL_LAYOUT_INFO));

	if (m_pPropBase_Layout_Width == NULL || m_pPropBase_Layout_Height == NULL || m_pPropBase_Layout_Layout == NULL
	 || m_pPropBase_Layout_LeftSpace == NULL || m_pPropBase_Layout_RightSpace == NULL || m_pPropBase_Layout_TopSpace == NULL || m_pPropBase_Layout_BottomSpace == NULL)
		return LayoutInfo;

	LayoutInfo.clType = (CONTROL_LAYOUT)m_pPropBase_Layout_Layout->GetSelect();
	LayoutInfo.nBottomSpace = m_pPropBase_Layout_BottomSpace->GetValue();
	LayoutInfo.nHeight = m_pPropBase_Layout_Height->GetValue();
	LayoutInfo.nLeftSpace = m_pPropBase_Layout_LeftSpace->GetValue();
	LayoutInfo.nRightSpace = m_pPropBase_Layout_RightSpace->GetValue();
	LayoutInfo.nTopSpace = m_pPropBase_Layout_TopSpace->GetValue();
	LayoutInfo.nWidth = m_pPropBase_Layout_Width->GetValue();

	return LayoutInfo;
}

// 移动控件，会改变布局信息，参数：CtrlInWndRct控件位于窗口的位置
void IControlBase::MoveWindowRect(RECT CtrlInWndRct)
{
	if (m_pOwnerWindowBase == NULL)
		return;

	if (m_pPropBase_Layout_Width == NULL || m_pPropBase_Layout_Height == NULL || m_pPropBase_Layout_Layout == NULL
	 || m_pPropBase_Layout_LeftSpace == NULL || m_pPropBase_Layout_RightSpace == NULL || m_pPropBase_Layout_TopSpace == NULL || m_pPropBase_Layout_BottomSpace == NULL)
		return;

	m_RectInWindow = CtrlInWndRct;

	m_pPropBase_Layout_Width->SetValue(RECT_WIDTH(m_RectInWindow));
	m_pPropBase_Layout_Height->SetValue(RECT_HEIGHT(m_RectInWindow));

	RECT ParentRct;
	INIT_RECT(ParentRct);
	IControlBase* pParentCtrl = GetParentControl();
	if (pParentCtrl != NULL)
		ParentRct = pParentCtrl->GetWindowRect();
	else
		ParentRct = GetOwnerWindow()->GetClientRect();

	// 设置本控件相对父控件的布局位置
	m_pPropBase_Layout_LeftSpace->SetValue(m_RectInWindow.left - ParentRct.left);
	m_pPropBase_Layout_TopSpace->SetValue(m_RectInWindow.top - ParentRct.top);
	m_pPropBase_Layout_RightSpace->SetValue(ParentRct.right - m_RectInWindow.right);
	m_pPropBase_Layout_BottomSpace->SetValue(ParentRct.bottom - m_RectInWindow.bottom);
}

// 控件显示位置和大小，这个位置是相对于附着的窗口的
void IControlBase::SetWindowRect(RECT CtrlInWndRct)
{
	m_RectInWindow = CtrlInWndRct;
}

RECT IControlBase::GetWindowRect()
{
	return m_RectInWindow;
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

// 设置附属控件
void IControlBase::SetPropertySkinManager(IPropertySkinManager *pMgr)
{
	m_pSkinPropMgr = pMgr;
}

IPropertyGroup* IControlBase::PP_GetControlPropetryGroup()
{
	if (m_pXmlPropCtrl == NULL)
		return NULL;

	return m_pXmlPropCtrl->GetControlPropGroup();
}

// 取得子控件的属性列表：Layout.xml 中的布局
PROP_CONTROL_VEC* IControlBase::GetChildPropControlVec()
{
	if (m_pXmlPropCtrl == NULL)
		return NULL;

	return m_pXmlPropCtrl->GetChildPropControlVec();
}

// 是否锁定在Builder中鼠标改变控件大小和位置
void IControlBase::SetLockControl(bool bLock)
{
	if (m_pPropBase_Lock == NULL)
		return;

	m_pPropBase_Lock->SetValue(bLock);	
}

bool IControlBase::GetLockControl()
{
	if (m_pPropBase_Lock == NULL)
		return false;

	return m_pPropBase_Lock->GetValue();
}
