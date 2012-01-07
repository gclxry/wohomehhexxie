//////////////////////////////////////////////////////////////////////////
// 一个窗口在xml中的读取的属性
// 存储 Layout.xml 中 window 节点下所有属性的队列

#pragma once
#include "IPropertyBase.h"
#include "IPropertyControl.h"


class IPropertyWindow : public IPropertyBase
{
public:
	IPropertyWindow();
	virtual ~IPropertyWindow();

	PROP_CONTROL_VEC* GetChildPropControlVec();
	void SetWindowPropGroup(IPropertyGroup *pWindowProp);
	IPropertyGroup* GetWindowPropGroup();
	void AppendChildCtrlProp(IPropertyControl *pPropCtrl);

private:
	IPropertyGroup *m_pWindowProp;
	// 子控件属性节点 的列表
	PROP_CONTROL_VEC m_ChildCtrlPropVec;
};
