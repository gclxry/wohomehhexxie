//////////////////////////////////////////////////////////////////////////
// һ�����ڵ�����

#pragma once

class IPropertyWindow
{
public:
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
};
