//////////////////////////////////////////////////////////////////////////
// һ���ؼ���xml�еĶ�ȡ������

#pragma once
#include "IPropertyBase.h"
#include "IPropertyGroup.h"

// �ӿؼ����Զ���
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
	// �ӿؼ����Խڵ� ���б�
	CHILD_CTRL_PROP_VEC m_ChildCtrlPropVec;
	// ���ؼ����Խڵ�
	IPropertyControl* m_pPrentCtrlProp;
	// ����ؼ������б�
	IPropertyGroup *m_pCtrlPropGroup;
};
