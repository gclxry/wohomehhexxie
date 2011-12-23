
#pragma once
#include "..\..\Inc\IPropertyControl.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IPropertySkinManager.h"

class IPropertyControlImpl : public IPropertyControl
{
public:
	IPropertyControlImpl(void);
	virtual ~IPropertyControlImpl(void);

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
	// 2. 从xml文件填充控件属性
	virtual bool ReadPropFromControlsXml(const char* pszControlId);
	// 3. 创建Builder显示用的属性
	virtual bool CreateBuilderShowPropList();

protected:
//	// 1.1 在派生控件中创建属性
//	virtual bool CreateDedicationProp() = 0;
	// 创建一个属性
	IPropertyBase* CreateProperty(IPropertyGroup *pPropGroup, PROP_TYPE propType, UINT nPropId, char *pPropName, char *pPropInfo);

private:

private:
	// 存储Builder可见可设置属性列表
	GROUP_PROP_VEC m_ControlPropList;
	// 附属控件
	IControlBase *m_pBaseCtrl;
	IPropertySkinManager *m_pSkinPropMgr;

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
