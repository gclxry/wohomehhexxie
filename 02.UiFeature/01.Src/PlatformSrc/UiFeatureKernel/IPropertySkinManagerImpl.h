
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "..\..\Inc\IZipFileList.h"
#include "..\..\Inc\IPropertyGroup.h"

//////////////////////////////////////////////////////////////////////////
// ��Դ���Զ���
// һ�����ԵĶ��У��磺font��string��image�ȣ�KEY��ObjectId
typedef map<string, IPropertyBase*>				PROP_MAP;
// ������������ԵĶ��У�KEY�������������ƣ��磺font
typedef map<string, PROP_MAP*>					ALL_PROP_MAP;

//////////////////////////////////////////////////////////////////////////
// �ؼ����Զ���
// һ�ֿؼ������Զ��У��磺Button��CheckBox�ȣ�KEY��ObjectId
typedef PROP_MAP								CONTROL_PROP_MAP;
// ���пؼ���������ԵĶ��У�KEY���ؼ��������ƣ��磺Button
typedef map<string, CONTROL_PROP_MAP*>			ALL_CONTROL_PROP_MAP;

//////////////////////////////////////////////////////////////////////////
// �������Զ���
// KEY:����ID�����д��ڵĹ�����map
typedef map<string, IPropertyWindow*>			WND_PROP_MAP;

class IPropertySkinManagerImpl : public IPropertySkinManager
{
public:
	IPropertySkinManagerImpl(void);
	virtual ~IPropertySkinManagerImpl(void);

	static IPropertySkinManager* GetInstance();

	// ��ʼ��WindowƤ��
	virtual IPropertyWindow* InitWindowSkin(const char *pszSkinPath, const char *pszWndName);
	// ����ָ��������
	virtual IPropertyBase* FindBaseProperty(PROP_TYPE propType, const char* pszPropId);
	virtual IPropertyBase* FindBaseProperty(const char* pszPropType, const char* pszPropId);
	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType);
	// ����һ�����ԣ����������Է������
	virtual IPropertyBase* CreateEmptyBaseProp(PROP_TYPE propType);
	// ȡ��ID��
	virtual int GetNewId();

private:
	// ��ʼ��Ƥ����
	bool InitSkinPackage(const char *pszSkinPath);
	// ����zip�ļ�
	void LoadZipDll();
	string PropTypeToString(PROP_TYPE propType);
	PROP_TYPE PropStringToType(string strPropType);
	void ResetBaseObjectId(int nObjectId);

//////////////////////////////////////////////////////////////////////////
	// Resource.xml���
	// ����Resource.xml
	bool TranslateResourceXml(FILE_ITEM *pResurceXml);
	void ReleaseResourceXml();
	void ReleaseBaseProp(IPropertyBase *pCtrlProp);
	// ͨ�õĴ���Դxml�д�������
	bool GeneralCreateBaseProp(char *pPropType, XmlNode* pXmlNode, PROP_MAP* pPropMap);

//////////////////////////////////////////////////////////////////////////
	// Controls.xml ���
	bool TranslateControlsXml(FILE_ITEM *pControlsXml);
	void ReleaseControlsXml();
	bool GeneralCreateCtrlProp(char *pCtrlType, XmlNode* pXmlNode, CONTROL_PROP_MAP* pCtrlPropMap);
	void AppendBasePropToGroup(IPropertyGroup *pGroup, XmlNode* pXmlNode);

//////////////////////////////////////////////////////////////////////////
	// Windows.xml ���
	// ����Windows.xml
	bool TranslateWindowsXml(FILE_ITEM *pWindowsXml);

//////////////////////////////////////////////////////////////////////////
	// Layout.xml ���

private:
	// Ƥ��·��
	string m_strSkinPath;
	// ������������ԵĶ���
	ALL_PROP_MAP m_AllPropMap;
	// ���пؼ���������ԵĶ��У�KEY���ؼ��������ƣ��磺Button
	ALL_CONTROL_PROP_MAP m_AllCtrlPropMap;
	// ���д��ڵ����Թ�����map
	WND_PROP_MAP m_WndPropMap;

	// zip�ļ�
	IZipFileList *m_pZipFile;
	HMODULE m_hZipModule;

	AREA_TYPE m_AreaType;

	// ������ԴObjectId
	int m_nObjectIdInRes;
	int m_nEmptyObjectId;
};
