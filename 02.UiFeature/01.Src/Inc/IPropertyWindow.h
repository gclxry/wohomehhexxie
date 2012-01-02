//////////////////////////////////////////////////////////////////////////
// һ��������xml�еĶ�ȡ������

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
	// �ӿؼ����Խڵ� ���б�
	CHILD_CTRL_PROP_VEC m_ChildCtrlPropVec;
};
