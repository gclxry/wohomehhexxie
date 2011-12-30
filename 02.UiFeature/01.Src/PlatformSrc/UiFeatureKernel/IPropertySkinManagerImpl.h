
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "..\..\Inc\IZipFileList.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\CUiXmlWrite.h"

//////////////////////////////////////////////////////////////////////////
// ��Դ���Զ���


class IPropertySkinManagerImpl : public IPropertySkinManager
{
public:
	IPropertySkinManagerImpl(void);
	virtual ~IPropertySkinManagerImpl(void);

	static IPropertySkinManager* GetInstance();

//////////////////////////////////////////////////////////////////////////
	// ��һ��Ƥ����ʱ����Ҫ��ȡƤ�������ļ�
	// ����Resource.xml
	virtual bool BuilderTranslateResourceXml(char *pszXmlPath);
	// ����Controls.xml
	virtual bool BuilderTranslateControlsXml(char *pszXmlPath);
	// ����Windows.xml
	virtual bool BuilderTranslateWindowsXml(char *pszXmlPath);
	// ����Layout.xml
	virtual bool BuilderTranslateLayoutXml(char *pszXmlPath);

	virtual ONE_RESOURCE_PROP_MAP* BuilderGetWindowPropMap();

	// ����Ƥ����
	virtual bool BuilderSaveSkin(char *pszSkinDir, char *pszSkinName);

	// ������Զ���
	virtual void ReleaseSkinManagerPropetry();

//////////////////////////////////////////////////////////////////////////
	// ��ʼ��WindowƤ��
	virtual IPropertyWindow* InitWindowSkin(const char *pszSkinPath, const char *pszWndName);
	// ����ָ��������
	virtual IPropertyBase* FindBaseProperty(OBJECT_TYPE_ID propType, const char* pszPropId);
	virtual IPropertyBase* FindBaseProperty(const char* pszPropType, const char* pszPropId);
	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType);
	// ����һ�����ԣ����������Է������
	virtual IPropertyBase* CreateEmptyBaseProp(OBJECT_TYPE_ID propType, char *pszObjectId = NULL);
	// ȡ��ID��
	virtual int GetNewId();

private:
//////////////////////////////////////////////////////////////////////////
	// Builderʹ�ú���
	bool BuilderCreateFileItem(char *pFilePath, ZIP_FILE &FileItem);
	void BuilderFreeFileItem(ZIP_FILE &FileItem);

//////////////////////////////////////////////////////////////////////////
	// ��ʼ��Ƥ����
	bool InitSkinPackage(const char *pszSkinPath);
	// ����zip�ļ�
	void LoadZipDll();
	void ResetBaseObjectId(int nObjectId);

//////////////////////////////////////////////////////////////////////////
	// Resource.xml���
	// ����Resource.xml
	bool TranslateResourceXml(ZIP_FILE *pResurceXml);
	void ReleasePropMap(RESOURCE_PROP_MAP &PropMap);
	void ReleaseBaseProp(IPropertyBase *pCtrlProp);
	void ReleasePropMapItem(ONE_RESOURCE_PROP_MAP* pPropMapItem);
	// ͨ�õĴ���Դxml�д�������
	bool GeneralCreateBaseProp(char *pPropType, XmlNode* pXmlNode, ONE_RESOURCE_PROP_MAP* pPropMap);
	// ����������base���ԵĹ���
	void SetPropetryBaseRelevancy();
	void SetPropRelevancy(ONE_RESOURCE_PROP_MAP* pFromMap, ONE_RESOURCE_PROP_MAP* pToMap);

//////////////////////////////////////////////////////////////////////////
	// Controls.xml ���
	bool TranslateControlsXml(ZIP_FILE *pControlsXml);
	bool GeneralCreateSubProp(XmlNode* pXmlNode, ONE_RESOURCE_PROP_MAP* pCtrlPropMap);
	bool AppendBasePropToGroup(IPropertyGroup *pGroup, XmlNode* pXmlNode);

//////////////////////////////////////////////////////////////////////////
	// Windows.xml ���
	// ����Windows.xml
	bool TranslateWindowsXml(ZIP_FILE *pWindowsXml);

//////////////////////////////////////////////////////////////////////////
	// Layout.xml ���
	bool TranslateLayoutXml(ZIP_FILE *pLayoutXml);
	bool GeneralCreateWindowLayoutProp(XmlNode* pXmlNode, CHILD_CTRL_PROP_VEC* pChildCtrlVec, IPropertyControl* pParentProp);
	IPropertyGroup* FindControlPropGroup(char *pszObjectId);
	void ReleaseLayoutMap();
	void ReleaseLayoutMapChildCtrlVec(CHILD_CTRL_PROP_VEC* pCtrlVec);

	bool SaveLayoutXml(const char *pszSavePath, string &strXmlData);
	bool SaveLayoutXml_ChildCtrl(CXmlStreamWrite &XmlStrObj, CNode* pNode, CHILD_CTRL_PROP_VEC* pWndChildVec);

	bool SaveResourceXml(const char *pszSavePath, string &strXmlData);

	void SaveToFile(char *pszFilePath, BYTE *pData, int nDataLen);
private:
	// Ƥ��·��
	string m_strSkinPath;
	// ������������ԵĶ���
	RESOURCE_PROP_MAP m_AllPropMap;
	// ���пؼ���������ԵĶ��У�KEY���ؼ��������ƣ��磺Button
	RESOURCE_PROP_MAP m_AllCtrlPropMap;
	// ���д��ڵ����Թ�����map
	ONE_RESOURCE_PROP_MAP m_AllWindowPropMap;
	// ���ֶ��У�KEY��ObjectID
	ONE_RESOURCE_PROP_MAP m_LayoutWindowMap;

	// ImageBase ���Զ���
	ONE_RESOURCE_PROP_MAP* m_pImageBasePropMap;
	ONE_RESOURCE_PROP_MAP* m_pImagePropMap;
	// FontBase ���Զ���
	ONE_RESOURCE_PROP_MAP* m_pFontBasePropMap;
	ONE_RESOURCE_PROP_MAP* m_pFontPropMap;
	// CursorBase ���Զ���
	ONE_RESOURCE_PROP_MAP* m_pCursorBasePropMap;
	ONE_RESOURCE_PROP_MAP* m_pCursorPropMap;
	// ColorBase ���Զ���
	ONE_RESOURCE_PROP_MAP* m_pColorBasePropMap;
	ONE_RESOURCE_PROP_MAP* m_pColorPropMap;

	// zip�ļ�
	IZipFileList *m_pZipFile;
	HMODULE m_hZipModule;

	AREA_TYPE m_AreaType;

	// ������ԴObjectId
	int m_nObjectIdInRes;
	int m_nEmptyObjectId;
};
