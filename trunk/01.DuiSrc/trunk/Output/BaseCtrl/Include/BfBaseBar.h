#pragma once

#include "BaseCtrlDefs.h"
#include "ResImage.h"

class CBfBaseBar : public CDirectUiWindow
{
public:
	CBfBaseBar(void);
	~CBfBaseBar(void);

	// ��ʼ�� bar �ĸ������ԣ��Լ�bar�е��Ӵ���
	virtual bool InitBar() = 0;

protected:
	virtual void OnLButtonDown(CPoint point);
};
