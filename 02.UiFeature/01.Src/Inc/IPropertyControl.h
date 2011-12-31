//////////////////////////////////////////////////////////////////////////
// 一个控件在xml中的读取的属性

#pragma once
#include "IPropertyBase.h"
#include "IPropertyGroup.h"

// 子控件属性队列
class IPropertyControl;
typedef vector<IPropertyControl*>			CHILD_CTRL_PROP_VEC;

class IPropertyControl : public IPropertyBase
{
public:
	IPropertyControl(void);
	virtual ~IPropertyControl(void);

	IPropertyControl* GetParentCtrlProp();
	void SetParentCtrlProp(IPropertyControl* pCtrlProp);
	
	void AppendChildCtrlProp(IPropertyControl* pCtrlProp);
	
	void SetCtrlGroupProp(IPropertyGroup *pBasePropGroup);
	IPropertyGroup *GetCtrlGroupProp();

	CHILD_CTRL_PROP_VEC* GetChildCtrlVec();

private:
	// 子控件属性节点 的列表
	CHILD_CTRL_PROP_VEC m_ChildCtrlPropVec;
	// 父控件属性节点
	IPropertyControl* m_pPrentCtrlProp;
	// 自身控件属性列表
	IPropertyGroup *m_pCtrlPropGroup;
};
