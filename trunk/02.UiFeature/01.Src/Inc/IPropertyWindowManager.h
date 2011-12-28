//////////////////////////////////////////////////////////////////////////
// һ�����ڵ�����

#pragma once
#include "IPropertyGroup.h"

class IPropertyWindowManager
{
public:
	// �Ƿ��Ѿ���ʼ��
	virtual bool IsInit() = 0;

	// ��xml�е��������õ�manager��
	virtual void SetWindowPropetry(IPropertyGroup *pWndPropInXml) = 0;

	// �Ƿ�֧��ȫ���ڵ���ƶ�
	virtual void SetDragWindow(bool bDrag) = 0;
	virtual bool GetDragWindow() = 0;

	// �Ƿ����
	virtual void SetCanFullScreen(bool bCanFull) = 0;
	virtual bool IsCanFullScreen() = 0;
	virtual void SetFullScreen(bool bFull) = 0;
	virtual bool IsFullScreen() = 0;

	// ��������
	virtual void SetWindowName(char *pszWndName) = 0;
	virtual const char * GetWindowName() = 0;

	virtual IPropertyGroup *GetWindowPropetryBaseGroup() = 0;

};
