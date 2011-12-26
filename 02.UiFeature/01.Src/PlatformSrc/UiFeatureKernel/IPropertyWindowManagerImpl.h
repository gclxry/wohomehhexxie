
#pragma once
#include "..\..\Inc\IPropertyWindowManager.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\IPropertySkinManager.h"

class IPropertyWindowManagerImpl : public IPropertyWindowManager
{
public:
	IPropertyWindowManagerImpl(void);
	virtual ~IPropertyWindowManagerImpl(void);

	virtual bool IsInit();

	// ��xml�е��������õ�manager��
	virtual void SetWindowPropetry(IPropertyGroup *pWndPropInXml);

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
	void CreateWindowPropetry();
	IPropertyBase* CreatePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);

private:
	IPropertySkinManager* m_pSkinPropMgr;
	bool m_bIsInit;
	bool m_bIsFullScreen;

	// ��xml�ж��벢��Ҫд��xml�е����Դ��������б�
	IPropertyGroup *m_pWndPropInXml;

	// Group:base
	IPropertyGroup* m_pPropGroupBase;
	// base-��������
	IPropertyString *m_pPropBase_TypeName;
	// base-objectid
	IPropertyString *m_pPropBase_ObjectId;
	// base-name
	IPropertyString *m_pPropBase_Name;
	// base-visible
	IPropertyBool *m_pPropBase_Visible;
	// base-֧�ֲַ㴰��
	IPropertyBool *m_pPropBase_Layered;
	// base-topmost
	IPropertyBool *m_pPropBase_TopMost;
	// base-sysbase
	IPropertyGroup* m_pPropGroupSysBase;
	// base-sysbase-���
	IPropertyBool *m_pPropSysBase_CanFullScreen;
	// base-sysbase-��С��
	IPropertyBool *m_pPropSysBase_CanMiniSize;
	// base-sysbase-��С�ߴ�
	// base-sysbase-���ߴ�
	// Group-size
	IPropertyGroup* m_pPropGroupSize;
	// size-width
	IPropertyInt *m_pPropSize_Width;
	// size-height
	IPropertyInt *m_pPropSize_Height;
	// Group-drag(��ק����)
	IPropertyGroup* m_pPropGroupDrag;
	// drag-enable
	IPropertyBool *m_pPropDrag_Enable;
	// Group-stretching(���촰��)
	IPropertyGroup* m_pPropGroupStretching;
	// stretching-enable
	IPropertyBool *m_pPropStretching_Enable;
	// stretching-leftspace
	IPropertyInt *m_pPropStretching_LeftSpace;
	// stretching-rightspace
	IPropertyInt *m_pPropStretching_RightSpace;
	// stretching-topspace
	IPropertyInt *m_pPropStretching_TopSpace;
	// stretching-bottomspace
	IPropertyInt *m_pPropStretching_BottomSpace;
	// Group-WindowRgn
	IPropertyGroup* m_pPropGroupWindowRgn;
};
