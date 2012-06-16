//////////////////////////////////////////////////////////////////////////
// 一个窗口在xml中的读取的属性
// 存储 Layout.xml 中 window 节点下所有属性的队列

#pragma once
#include "IPropertyBase.h"
#include "IPropertyControl.h"


class IPropertyWindow : public IPropertyBase
{
public:
	virtual PROP_CONTROL_VEC* GetChildPropControlVec() = 0;
	virtual void SetWindowPropGroup(IPropertyGroup *pWindowProp) = 0;
	virtual IPropertyGroup* GetWindowPropGroup() = 0;
	virtual void AppendChildCtrlProp(IPropertyControl *pPropCtrl) = 0;

	// 清空属性的隶属于哪个窗口的信息
	virtual void ClearPropertyOwner() = 0;
};
