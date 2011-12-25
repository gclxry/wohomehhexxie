
#pragma once
#include "..\..\Inc\IPropertyWindowInWindow.h"

class IPropertyWindowImpl : public IPropertyWindowInWindow
{
public:
	IPropertyWindowImpl(void);
	virtual ~IPropertyWindowImpl(void);

	// �Ƿ�֧��ȫ���ڵ���ƶ�
	virtual void SetDragWindow(bool bDrag);
	virtual bool GetDragWindow();

	// �Ƿ����
	virtual void SetCanFullScreen(bool bCanFull);
	virtual bool IsCanFullScreen();
	virtual void SetFullScreen(bool bFull);
	virtual bool IsFullScreen();

	// ��������
	virtual void SetWindowName(char *pszWndName);
	virtual const char * GetWindowName();

private:
	bool m_bDragWindow;
	bool m_bCanFullScreen;
	bool m_bIsFullScreen;
	string m_strWndName;
};
