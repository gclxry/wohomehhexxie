
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "..\..\Inc\IZipFileList.h"

// KEY:�������ƣ����д��ڵĹ�����map
typedef map<string, IPropertyWindow*>			WND_PROP_MAP;

// ��Դ���Զ���
// һ�����ԵĶ��У��磺font��string��image�ȣ�KEY������ID
typedef map<int, IPropertyBase*>				PROP_MAP;
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
	virtual IPropertyBase* FindProperty(char* pszPropType, int nPropId);
	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType);

private:
	// ��ʼ��Ƥ����
	bool InitSkinPackage(const char *pszSkinPath);
	// ����zip�ļ�
	void LoadZipDll();

//////////////////////////////////////////////////////////////////////////
	// Resource.xml���
	// ����Resource.xml
	bool TranslateResourceXml(FILE_ITEM *pResurceXml);
	void ReleaseResourceXml();
	void ReleaseResourceXmlProp(IPropertyBase *pCtrlProp);
	// �ж������Ƿ��Ѿ�����
	bool IsPropExist(XmlNode* pXmlNode, PROP_MAP* pPropMap, int &nPropId);
	// ͨ�õĴ���Դxml�д�������
	bool GeneralCreateProp(char *pPropType, XmlNode* pXmlNode, PROP_MAP* pPropMap);
	// ���õ�ǰ����PropId
	void ResetPropId(int nPropId);

//////////////////////////////////////////////////////////////////////////
	// Controls.xml ���
	bool TranslateControlsXml(FILE_ITEM *pWindowsXml);

//////////////////////////////////////////////////////////////////////////
	// Windows.xml ���
	// ����Windows.xml
	bool TranslateWindowsXml(FILE_ITEM *pWindowsXml);

//////////////////////////////////////////////////////////////////////////
	// Layout.xml ���

private:
	// ���д��ڵ����Թ�����map
	WND_PROP_MAP m_WndPropMap;
	// Ƥ��·��
	string m_strSkinPath;
	// ������������ԵĶ���
	ALL_PROP_MAP m_AllPropMap;

	// zip�ļ�
	IZipFileList *m_pZipFile;
	HMODULE m_hZipModule;

	AREA_TYPE m_AreaType;

	// Ƥ���������Ե�ID
	int m_bPropId;
};
