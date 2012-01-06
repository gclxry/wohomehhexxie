//////////////////////////////////////////////////////////////////////////
// һ���ؼ���xml�еĶ�ȡ������

#pragma once
#include "IPropertyBase.h"
#include "IPropertyGroup.h"

// �ӿؼ����Զ���
class IPropertyControl;
typedef vector<IPropertyControl*>			PROP_CONTROL_VEC;

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

	PROP_CONTROL_VEC* GetChildPropControlVec();

private:
	// �ӿؼ����Խڵ� ���б�
	PROP_CONTROL_VEC m_ChildCtrlPropVec;
	// ���ؼ����Խڵ�
	IPropertyControl* m_pPrentCtrlProp;
	// ����ؼ������б�
	IPropertyGroup *m_pCtrlPropGroup;
};
