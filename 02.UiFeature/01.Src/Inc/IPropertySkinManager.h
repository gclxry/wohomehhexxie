//////////////////////////////////////////////////////////////////////////
// ��ǰƤ�����д��������пؼ������Թ�����

#pragma once
#include "IPropertyWindowManager.h"
#include "IPropertyBase.h"
#include "IPropertyWindow.h"

class IPropertySkinManager
{
public:
	// ����Resource.xml
	virtual bool BuilderTranslateResourceXml(char *pszXmlPath) = 0;
	// ����Controls.xml
	virtual bool BuilderTranslateControlsXml(char *pszXmlPath) = 0;
	// ����Windows.xml
	virtual bool BuilderTranslateWindowsXml(char *pszXmlPath) = 0;
	// ����Layout.xml
	virtual bool BuilderTranslateLayoutXml(char *pszXmlPath) = 0;

	virtual PROP_BASE_ITEM* BuilderGetWindowPropMap() = 0;

	// ������Զ���
	virtual void ReleaseSkinManagerPropetry() = 0;

//////////////////////////////////////////////////////////////////////////
	// ��ʼ��WindowƤ��
	virtual IPropertyGroup* InitWindowSkin(const char *pszSkinPath, const char *pszWndName) = 0;
//	// ����ָ��������
//	virtual IPropertyBase* FindBaseProperty(OBJECT_TYPE_ID propType, const char* pszPropId) = 0;
//	virtual IPropertyBase* FindBaseProperty(const char* pszPropType, const char* pszPropId) = 0;
	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType) = 0;
	// ����һ�����ԣ����������Է������
	virtual IPropertyBase* CreateEmptyBaseProp(OBJECT_TYPE_ID propType, char *pszObjectId = NULL) = 0;
	// ȡ��ID��
	virtual int GetNewId() = 0;
};
