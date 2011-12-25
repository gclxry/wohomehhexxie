
#include "StdAfx.h"
#include "IPropertyWindowManagerImpl.h"

IPropertyWindowManagerImpl::IPropertyWindowManagerImpl(void)
{
	m_bDragWindow = false;
	m_bCanFullScreen = false;
	m_bIsFullScreen = false;
	m_strWndName = "";
}

IPropertyWindowManagerImpl::~IPropertyWindowManagerImpl(void)
{
}

// ��������
void IPropertyWindowManagerImpl::SetWindowName(char *pszWndName)
{
	if (pszWndName != NULL)
		m_strWndName = pszWndName;
}

const char * IPropertyWindowManagerImpl::GetWindowName()
{
	return m_strWndName.c_str();
}

// �Ƿ�֧��ȫ���ڵ���ƶ�
void IPropertyWindowManagerImpl::SetDragWindow(bool bDrag)
{
	m_bDragWindow = bDrag;
}

bool IPropertyWindowManagerImpl::GetDragWindow()
{
	return m_bDragWindow;
}

// �Ƿ����
void IPropertyWindowManagerImpl::SetCanFullScreen(bool bCanFull)
{
	m_bCanFullScreen = bCanFull;
}

bool IPropertyWindowManagerImpl::IsCanFullScreen()
{
	return m_bCanFullScreen;
}

void IPropertyWindowManagerImpl::SetFullScreen(bool bFull)
{
	if (m_bCanFullScreen)
		m_bIsFullScreen = bFull;
	else
		m_bIsFullScreen = false;
}

bool IPropertyWindowManagerImpl::IsFullScreen()
{
	return m_bIsFullScreen;
}
