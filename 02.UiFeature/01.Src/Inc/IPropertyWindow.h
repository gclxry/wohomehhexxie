//////////////////////////////////////////////////////////////////////////
// һ��������xml�еĶ�ȡ������

#pragma once
#include "IFeatureObject.h"
#include "IPropertyControl.h"

// Window���Զ��У�KEY��ObjectID
class IPropertyWindow;
typedef map<string, IPropertyWindow*>			WINDOW_PROP_MAP;

class IPropertyWindow : public IFeatureObject
{
public:
	IPropertyWindow();
	virtual ~IPropertyWindow();

	CHILD_CTRL_PROP_VEC* GetChildControlVec();

private:
	// �ӿؼ����Խڵ� ���б�
	CHILD_CTRL_PROP_VEC m_ChildCtrlPropVec;
};
