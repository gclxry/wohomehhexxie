//////////////////////////////////////////////////////////////////////////
// 一个窗口在xml中的读取的属性

#pragma once
#include "IFeatureObject.h"
#include "IPropertyControl.h"

// Window属性队列，KEY：ObjectID
class IPropertyWindow;
typedef map<string, IPropertyWindow*>			WINDOW_PROP_MAP;

class IPropertyWindow : public IFeatureObject
{
public:
	IPropertyWindow();
	virtual ~IPropertyWindow();

	CHILD_CTRL_PROP_VEC* GetChildControlVec();

private:
	// 子控件属性节点 的列表
	CHILD_CTRL_PROP_VEC m_ChildCtrlPropVec;
};
