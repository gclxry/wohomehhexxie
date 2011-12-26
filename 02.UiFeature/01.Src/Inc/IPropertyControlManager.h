//////////////////////////////////////////////////////////////////////////
// 一个控件的属性

#pragma once
#include "IFeatureObject.h"
#include "IPropertyBase.h"
#include "IPropertyGroup.h"
#include "IPropertySkinManager.h"

class IControlBase;
class IPropertySkinManager;
class IPropertyControlManager;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 当前控件相对于父控件的布局类型
enum CONTROL_LAYOUT
{
	// 固定大小：左上角定位
	CL_G_LEFT_TOP		= 0,
	// 固定大小：左下角定位
	CL_G_LEFT_BOTTOM	= 1,
	// 固定大小：右上角定位
	CL_G_RIGHT_TOP		= 2,
	// 固定大小：右下角定位
	CL_G_RIGHT_BOTTOM	= 3,
	// 拉伸变动大小：撑满左侧
	CL_L_LEFT			= 4,
	// 拉伸变动大小：撑满右侧
	CL_L_RIGHT			= 5,
	// 拉伸变动大小：撑满上方
	CL_L_TOP			= 6,
	// 拉伸变动大小：撑满下方
	CL_L_BOTTOM			= 7,
	// 拉伸变动大小：撑满全部
	CL_L_ALL			= 8,
	// 拉伸变动大小：居中
	CL_L_MIDDLE			= 9,
};
// 当前控件相对于父控件的布局信息
struct CONTROL_LAYOUT_INFO
{
	// 布局类型
	CONTROL_LAYOUT clType;
	// 控件宽
	int nWidth;
	// 控件高
	int nHeight;
	// 距离父控件左侧距离
	int nLeftSpace;
	// 距离父控件右侧距离
	int nRightSpace;
	// 距离父控件上方距离
	int nTopSpace;
	// 距离父控件下方距离
	int nBottomSpace;
};


// 子控件列表
typedef map<string, IPropertyControlManager*>			CHILD_CTRL_PROP_MAP;

class IPropertyControlManager : public IFeatureObject
{
public:
	IPropertyControlManager(void);
	virtual ~IPropertyControlManager(void);

	// 父控件属性
	void SetParentPropertyControl(IPropertyControlManager *pParent);
	virtual IPropertyControlManager* GetParentPropertyControl();

	// 设置附属控件
	virtual void SetControlBase(IControlBase *pCtrl);
	virtual IControlBase* GetControlBase();
	virtual void SetPropertySkinManager(IPropertySkinManager *pMgr);

	// 控件显示位置和大小，这个位置是相对于附着的窗口的
	virtual void SetCtrlInWindowRect(RECT CtrlWndRct);
	virtual RECT GetCtrlInWindowRect();
	// 控件显示位置和大小，这个位置是相对于父控件的
	virtual RECT GetCtrlInControlRect();
	// 取得控件的大小
	virtual RECT GetCtrlRect();

	// 是否接受鼠标消息
	virtual void SetReceiveMouseMessage(bool bIsReceive);
	virtual bool GetReceiveMouseMessage();

	// 可见属性
	virtual void SetVisible(bool bVisible);
	virtual bool IsVisible();

	// 相对于父控件的布局信息
	virtual void SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo);
	virtual CONTROL_LAYOUT_INFO GetLayout();

	// 控件名称，唯一识别窗口的标志
	virtual void SetName(char *pCtrlName);
	virtual const char* GetName();

	// 拖动控件属性
	virtual void SetDragControl(bool bDrag);
	virtual bool GetDragControl();

	// 可用属性
	virtual void SetEnable(bool bEnable);
	virtual bool IsEnable();

	//////////////////////////////////////////////////////////////////////////
	// 以下3个函数创建、显示属性用，执行顺序由上到下
	// 1. 创建空的属性列表
	virtual bool CreateEmptyPropList();
	// 2. 从xml文件中读取控件属性时，不需要初始化属性的PropId，PropId来源于xml文件
	virtual bool ReadPropFromControlsXml(const char* pszControlId);
	// 2.从Builder中新创建一个控件，需要初始化属性的PropId
	virtual bool InitObjectIdByBuilder(const char* pszBaseId);
	// 3. 创建Builder显示用的属性
	virtual bool CreateBuilderShowPropList();

protected:
	//	// 1.1 在派生控件中创建属性
	//	virtual bool CreateDedicationProp() = 0;
	// 创建一个属性
	IPropertyBase* CreateProperty(IPropertyGroup *pPropGroup, OBJECT_TYPE_ID propType, char *pPropName, char *pPropInfo);

private:
	// 2.从Builder中新创建一个控件，需要初始化属性的PropId
	void InitControlPropObjectId(GROUP_PROP_VEC *pPropList);

private:
	// 存储Builder可见可设置属性列表，也就是当前控件的属性列表
	GROUP_PROP_VEC m_ControlPropList;
	// 附属控件
	IControlBase *m_pBaseCtrl;
	IPropertySkinManager *m_pSkinPropMgr;
	IPropertyControlManager* m_pParentPropertyControl;

	// 是否可见
	bool m_bVisible;
	bool m_bEnable;
	// 是否接受鼠标消息
	bool m_bIsReceiveMouseMsg;
	// 控件位置，这个位置是相对于窗口的位置
	RECT m_RectInWindow;
	// 控件位置，这个位置是相对于父控件的位置
	RECT m_RectInParentCtrl;
	// 控件布局信息
	CONTROL_LAYOUT_INFO m_LayoutInfo;
	// 控件名称
	string m_strCtrlName;
	// 拖动控件
	bool m_bDragCtrl;
};
