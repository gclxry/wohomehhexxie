//////////////////////////////////////////////////////////////////////////
// ��ǰƤ�����д��������пؼ������Թ�����

#pragma once
#include "IPropertyWindow.h"
#include "IPropertyBase.h"

class IPropertySkinManager
{
public:
	// ��ʼ��WindowƤ��
	virtual IPropertyWindow* InitWindowSkin(const char *pszSkinPath, const char *pszWndName) = 0;
	// ����ָ��������
	virtual IPropertyBase* FindProperty(PROP_TYPE propType, const char* pszPropId) = 0;
	virtual IPropertyBase* FindProperty(const char* pszPropType, const char* pszPropId) = 0;
	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType) = 0;
	// ����һ�����ԣ����������Է������
	virtual IPropertyBase* CreateEmptyProperty(PROP_TYPE propType) = 0;
	// ȡ��ID��
	virtual int GetNewId() = 0;
};
