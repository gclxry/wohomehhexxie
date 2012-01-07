//////////////////////////////////////////////////////////////////////////
// һ��������xml�еĶ�ȡ������
// �洢 Layout.xml �� window �ڵ����������ԵĶ���

#pragma once
#include "IPropertyBase.h"
#include "IPropertyControl.h"


class IPropertyWindow : public IPropertyBase
{
public:
	IPropertyWindow();
	virtual ~IPropertyWindow();

	PROP_CONTROL_VEC* GetChildPropControlVec();
	void SetWindowPropGroup(IPropertyGroup *pWindowProp);
	IPropertyGroup* GetWindowPropGroup();
	void AppendChildCtrlProp(IPropertyControl *pPropCtrl);

private:
	IPropertyGroup *m_pWindowProp;
	// �ӿؼ����Խڵ� ���б�
	PROP_CONTROL_VEC m_ChildCtrlPropVec;
};
