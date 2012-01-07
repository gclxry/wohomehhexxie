
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "ZipFileList.h"
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
	virtual bool BD_TranslateResourceXml(char *pszXmlPath);
	// ����Controls.xml
	virtual bool BD_TranslateControlsXml(char *pszXmlPath);
	// ����Windows.xml
	virtual bool BD_TranslateWindowsXml(char *pszXmlPath);
	// ����Layout.xml
	virtual bool BD_TranslateLayoutXml(char *pszXmlPath);
	// ȡ�����д��ڵĶ���
	virtual ONE_RESOURCE_PROP_MAP* BD_GetWindowPropMap();
	// ��ؼ��������һ���ؼ�
	virtual bool BD_AppendControlToVec(char *pszCtrlType, IPropertyGroup* pCtrlPropGroup);

	// ����Ƥ����
	virtual bool BD_SaveProject(char *pszSkinDir, char *pszSkinName);

	// ������Զ���
	virtual void ReleaseSkinManagerPropetry();

//////////////////////////////////////////////////////////////////////////
	// ��ʼ��WindowƤ��
	virtual IPropertyWindow* PG_InitWindowSkin(const char *pszSkinPath, const char *pszWndName);
	// ����ָ��������
	virtual IPropertyBase* FindBaseProperty(OBJECT_TYPE_ID propType, const char* pszPropId);
	virtual IPropertyBase* FindBaseProperty(const char* pszPropType, const char* pszPropId);
	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType);
	// ����һ�����ԣ����������Է������
	virtual IPropertyBase* CreateEmptyBaseProp(OBJECT_TYPE_ID propType, char *pszObjectId = NULL);
	// ȡ��ID��
	virtual int GetNewId();

//////////////////////////////////////////////////////////////////////////
	ONE_RESOURCE_PROP_MAP * GetAllWindowPropMap();

	void ReleaseBaseProp(IPropertyBase *pCtrlProp);
private:
//////////////////////////////////////////////////////////////////////////
	// Builderʹ�ú���
	bool BuilderCreateFileItem(char *pFilePath, ZIP_FILE &FileItem);
	void BuilderFreeFileItem(ZIP_FILE &FileItem);

//////////////////////////////////////////////////////////////////////////
	// ��ʼ��Ƥ����
	bool InitSkinPackage(const char *pszSkinPath);
	void ResetBaseObjectId(int nObjectId);

//////////////////////////////////////////////////////////////////////////
	// Resource.xml���
	// ����Resource.xml
	bool TranslateResourceXml(ZIP_FILE *pResurceXml);
	void ReleasePropMap(RESOURCE_PROP_MAP &PropMap);
	void ReleasePropMapItem(ONE_RESOURCE_PROP_MAP* pPropMapItem);
	// ͨ�õĴ���Դxml�д�������
	bool GeneralCreateBaseProp(char *pPropType, XmlNode* pXmlNode, ONE_RESOURCE_PROP_MAP* pPropMap);
	// ����������base���ԵĹ���
	void SetPropetryBaseRelevancy();
	void SetPropRelevancy(ONE_RESOURCE_PROP_MAP* pFromMap, ONE_RESOURCE_PROP_MAP* pToMap);

	bool SaveResourceXml(const char *pszSavePath, string &strXmlData);

//////////////////////////////////////////////////////////////////////////
	// Controls.xml ���
	bool TranslateControlsXml(ZIP_FILE *pControlsXml);
	bool GeneralCreateSubProp(XmlNode* pXmlNode, ONE_RESOURCE_PROP_MAP* pCtrlPropMap);
	bool AppendBasePropToGroup(IPropertyGroup *pGroup, XmlNode* pXmlNode);

	bool SaveControlsXml(const char *pszSavePath, string &strXmlData);

//////////////////////////////////////////////////////////////////////////
	// Windows.xml ���
	// ����Windows.xml
	bool TranslateWindowsXml(ZIP_FILE *pWindowsXml);

	bool SaveWindowsXml(const char *pszSavePath, string &strXmlData);
	bool SaveXml_GroupProp(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentNode, IPropertyGroup *pPropGroup);

//////////////////////////////////////////////////////////////////////////
	// Layout.xml ���
	bool TranslateLayoutXml(ZIP_FILE *pLayoutXml);
	bool GeneralCreateWindowLayoutProp(XmlNode* pXmlNode, PROP_CONTROL_VEC* pChildCtrlVec, IPropertyControl* pParentProp);
	IPropertyGroup* FindControlPropGroup(char *pszObjectId, string &strCtrlType);
	void ReleaseLayoutMap();
	void ReleaseLayoutMapPropControlVec(PROP_CONTROL_VEC* pCtrlVec);

	bool SaveLayoutXml(const char *pszSavePath, string &strXmlData);
	bool SaveLayoutXml_ChildCtrl(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pNode, PROP_CONTROL_VEC* pWndChildVec);

	void SaveToFile(char *pszFilePath, BYTE *pData, int nDataLen);
private:
	// Ƥ��·��
	string m_strSkinPath;

	// Resource.xml ������������ԵĶ���
	RESOURCE_PROP_MAP m_AllPropMap;
	// Controls.xml ���пؼ���������ԵĶ��У�KEY���ؼ��������ƣ��磺Button
	// �洢ÿһ���ؼ��ľ�������ԣ����пؼ����Զ������һ�� IPropertyGroup ��
	RESOURCE_PROP_MAP m_AllCtrlPropMap;
	// Windows.xml ���д��ڵ����Թ�����map
	// �洢ÿһ�����ڵľ�������ԣ����д������Զ������һ�� IPropertyGroup ��
	ONE_RESOURCE_PROP_MAP m_AllWindowPropMap;
	// ���ֶ��У�KEY��ObjectID���洢 IPropertyWindow IPropertyControl
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
	CZipFileList *m_pZipFile;

	AREA_TYPE m_AreaType;

	// ������ԴObjectId
	int m_nObjectIdInRes;
	int m_nEmptyObjectId;
};
