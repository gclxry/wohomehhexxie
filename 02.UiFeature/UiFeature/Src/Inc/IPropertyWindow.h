//////////////////////////////////////////////////////////////////////////
// һ��������xml�еĶ�ȡ������
// �洢 Layout.xml �� window �ڵ����������ԵĶ���

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

	// ������Ե��������ĸ����ڵ���Ϣ
	virtual void ClearPropertyOwner() = 0;
};
