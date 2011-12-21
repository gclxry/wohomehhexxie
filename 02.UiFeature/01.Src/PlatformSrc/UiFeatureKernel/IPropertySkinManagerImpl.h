
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "ZipFileList.h"

// KEY:�������ƣ����д��ڵĹ�����map
typedef map<string, IPropertyWindow*>			WND_PROP_MAP;

// ��Դ���Զ���
// һ�����ԵĶ��У��磺font��string��image�ȣ�KEY����������
typedef map<string, IPropertyBase*>				PROP_MAP;
// ������������ԵĶ��У�KEY�������������ƣ��磺font
typedef map<string, PROP_MAP*>					ALL_PROP_MAP;

class IPropertySkinManagerImpl : public IPropertySkinManager
{
public:
	IPropertySkinManagerImpl(void);
	virtual ~IPropertySkinManagerImpl(void);

	static IPropertySkinManager* GetInstance();

	// ��ʼ��WindowƤ��
	virtual IPropertyWindow* InitWindowSkin(const char *pszSkinPath, const char *pszWndName);
	// ����ָ��������
	virtual IPropertyBase* FindProperty(char* pszPropType, char* pszPropName);
	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType);

protected:
	// ��ʼ��Ƥ����
	bool InitSkinPackage(const char *pszSkinPath);
	// ����Resource.xml
	bool TranslateResourceXml(FILE_ITEM *pResurceXml);

private:
	// ������Զ���
	void Release();
	void ReleaseProp(IPropertyBase *pCtrlProp);

	// �ж������Ƿ��Ѿ�����
	bool IsPropExist(XmlNode* pXmlNode, PROP_MAP* pPropMap, string &strPropName);
	// ͨ�õĴ���Դxml�д�������
	bool GeneralCreateProp(char *pPropType, XmlNode* pXmlNode, PROP_MAP* pPropMap);

private:
	// ���д��ڵ����Թ�����map
	WND_PROP_MAP m_WndPropMap;
	// Ƥ��·��
	string m_strSkinPath;
	// zip�ļ�
	CZipFileList m_ZipFile;
	// ������������ԵĶ���
	ALL_PROP_MAP m_AllPropMap;
};
