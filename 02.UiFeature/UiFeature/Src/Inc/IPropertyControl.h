//////////////////////////////////////////////////////////////////////////
// 一个控件在xml中的读取的属性
// 存储 Layout.xml 中 ctrl 节点下所有属性的队列

#pragma once
#include "IPropertyBase.h"
#include "IPropertyGroup.h"

// 子控件属性队列
class IPropertyControl;
typedef vector<IPropertyControl*>			PROP_CONTROL_VEC;

class IPropertyControl : public IPropertyBase
{
public:
	virtual IPropertyControl* GetParentCtrlProp() = 0;
	virtual void SetParentCtrlProp(IPropertyControl* pCtrlProp) = 0;
	
	virtual void AppendChildCtrlProp(IPropertyControl* pCtrlProp) = 0;
	
	virtual void SetCtrlGroupProp(IPropertyGroup *pBasePropGroup) = 0;
	virtual IPropertyGroup *GetControlPropGroup() = 0;

	virtual const char * GetControlType() = 0;
	virtual void SetControlType(char *pszCtrlType) = 0;

	virtual PROP_CONTROL_VEC* GetChildPropControlVec() = 0;

	// 清空属性的隶属于哪个控件的信息
	virtual void ClearPropertyOwner() = 0;
};
