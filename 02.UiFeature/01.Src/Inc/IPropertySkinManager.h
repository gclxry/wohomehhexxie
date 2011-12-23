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
	virtual IPropertyBase* FindProperty(PROP_TYPE propType, int nPropId) = 0;
	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType) = 0;
	// ����һ�����ԣ����������Է������
	virtual IPropertyBase* CreateProperty(PROP_TYPE propType, int nPropId) = 0;
};
