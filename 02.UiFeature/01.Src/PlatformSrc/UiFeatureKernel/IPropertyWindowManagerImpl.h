
#pragma once
#include "..\..\Inc\IPropertyWindowManager.h"
#include "..\..\Inc\IPropertyGroup.h"

class IPropertyWindowManagerImpl : public IPropertyWindowManager
{
public:
	IPropertyWindowManagerImpl(void);
	virtual ~IPropertyWindowManagerImpl(void);

	virtual bool IsInit();

	// ��xml�е��������õ�manager��
	virtual void SetXmlPropetry(IPropertyGroup *pWndPropInXml);

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
	// �����յ����Զ���
	void CreateEmptyWindowPropetry();

private:
	bool m_bIsInit;
	bool m_bDragWindow;
	bool m_bCanFullScreen;
	bool m_bIsFullScreen;
	string m_strWndName;

	// ��xml�ж��벢��Ҫд��xml�е����Դ��������б�
	IPropertyGroup *m_pWndPropInXml;
};
