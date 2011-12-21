
#include "StdAfx.h"
#include "IPropertyWindowImpl.h"

IPropertyWindowImpl::IPropertyWindowImpl(void)
{
	m_bDragWindow = false;
	m_bCanFullScreen = false;
	m_bIsFullScreen = false;
	m_strWndName = "";
}

IPropertyWindowImpl::~IPropertyWindowImpl(void)
{
}

// ��������
void IPropertyWindowImpl::SetWindowName(char *pszWndName)
{
	if (pszWndName != NULL)
		m_strWndName = pszWndName;
}

const char * IPropertyWindowImpl::GetWindowName()
{
	return m_strWndName.c_str();
}

// �Ƿ�֧��ȫ���ڵ���ƶ�
void IPropertyWindowImpl::SetDragWindow(bool bDrag)
{
	m_bDragWindow = bDrag;
}

bool IPropertyWindowImpl::GetDragWindow()
{
	return m_bDragWindow;
}

// �Ƿ����
void IPropertyWindowImpl::SetCanFullScreen(bool bCanFull)
{
	m_bCanFullScreen = bCanFull;
}

bool IPropertyWindowImpl::IsCanFullScreen()
{
	return m_bCanFullScreen;
}

void IPropertyWindowImpl::SetFullScreen(bool bFull)
{
	if (m_bCanFullScreen)
		m_bIsFullScreen = bFull;
	else
		m_bIsFullScreen = false;
}

bool IPropertyWindowImpl::IsFullScreen()
{
	return m_bIsFullScreen;
}
