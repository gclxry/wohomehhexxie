//////////////////////////////////////////////////////////////////////////
// һ���ؼ���xml�еĶ�ȡ������

#pragma once
#include "IFeatureObject.h"
#include "IPropertyBase.h"
#include "IPropertyGroup.h"

// �ӿؼ����Զ���
class IPropertyControl;
typedef vector<IPropertyControl*>			CHILD_CTRL_PROP_VEC;

class IPropertyControl : public IFeatureObject
{
public:
	IPropertyControl(void);
	virtual ~IPropertyControl(void);

	IPropertyControl* GetParentProp();
	void SetParentProp(IPropertyControl* pCtrlProp);
	
	void AppendControlProp(IPropertyControl* pCtrlProp);
	
	void SetControlBaseProp(IPropertyGroup *pBasePropGroup);
	IPropertyGroup *GetControlBaseProp();

	CHILD_CTRL_PROP_VEC* GetChildControlVec();

private:
	// �ӿؼ����Խڵ� ���б�
	CHILD_CTRL_PROP_VEC m_ChildCtrlPropVec;
	// ���ؼ����Խڵ�
	IPropertyControl* m_pPrentCtrlProp;
	// ����ؼ������б�
	IPropertyGroup *m_pCtrlPropGroup;
};
