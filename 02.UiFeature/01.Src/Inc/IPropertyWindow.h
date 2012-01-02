//////////////////////////////////////////////////////////////////////////
// 一个窗口在xml中的读取的属性

#pragma once
#include "IPropertyBase.h"
#include "IPropertyControl.h"


class IPropertyWindow : public IPropertyBase
{
public:
	IPropertyWindow();
	virtual ~IPropertyWindow();

	CHILD_CTRL_PROP_VEC* GetChildCtrlVec();
	void SetWindowPropGroup(IPropertyGroup *pWindowProp);
	IPropertyGroup* GetWindowPropGroup();

private:
	IPropertyGroup *m_pWindowProp;
	// 子控件属性节点 的列表
	CHILD_CTRL_PROP_VEC m_ChildCtrlPropVec;
};
