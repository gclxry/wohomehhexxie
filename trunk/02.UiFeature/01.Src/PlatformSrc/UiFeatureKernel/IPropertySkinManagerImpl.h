
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "..\..\Inc\IZipFileList.h"

// KEY:�������ƣ����д��ڵĹ�����map
typedef map<string, IPropertyWindow*>			WND_PROP_MAP;

// ��Դ���Զ���
// һ�����ԵĶ��У��磺font��string��image��
typedef vector<IPropertyBase*>					PROP_VEC;
// ������������ԵĶ��У�KEY�������������ƣ��磺font
typedef map<string, PROP_VEC*>					ALL_PROP_MAP;

class IPropertySkinManagerImpl : public IPropertySkinManager
{
public:
	IPropertySkinManagerImpl(void);
	virtual ~IPropertySkinManagerImpl(void);

	static IPropertySkinManager* GetInstance();

	// ��ʼ��WindowƤ��
	virtual IPropertyWindow* InitWindowSkin(const char *pszSkinPath, const char *pszWndName);
	// ����ָ��������
	virtual IPropertyBase* FindProperty(PROP_TYPE propType, const char* pszPropId);
	virtual IPropertyBase* FindProperty(const char* pszPropType, const char* pszPropId);
	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType);
	// ����һ�����ԣ����������Է������
	virtual IPropertyBase* CreateEmptyProperty(PROP_TYPE propType);
	// ȡ��ID��
	virtual int GetNewId();

private:
	// ��ʼ��Ƥ����
	bool InitSkinPackage(const char *pszSkinPath);
	// ����zip�ļ�
	void LoadZipDll();
	string PropTypeToString(PROP_TYPE propType);
	PROP_TYPE PropStringToType(string strPropType);

//////////////////////////////////////////////////////////////////////////
	// Resource.xml���
	// ����Resource.xml
	bool TranslateResourceXml(FILE_ITEM *pResurceXml);
	void ReleaseResourceXml();
	void ReleaseProperty(IPropertyBase *pCtrlProp);
	// �ж������Ƿ��Ѿ�����
	bool IsPropExist(XmlNode* pXmlNode, PROP_VEC* pPropVec, string &strPropId);
	// ͨ�õĴ���Դxml�д�������
	bool GeneralCreateProp(char *pPropType, XmlNode* pXmlNode, PROP_VEC* pPropMap);
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
