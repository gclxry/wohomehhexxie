
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "..\..\Inc\IZipFileList.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\CUiXmlWrite.h"

//////////////////////////////////////////////////////////////////////////
// 资源属性队列


class IPropertySkinManagerImpl : public IPropertySkinManager
{
public:
	IPropertySkinManagerImpl(void);
	virtual ~IPropertySkinManagerImpl(void);

	static IPropertySkinManager* GetInstance();

//////////////////////////////////////////////////////////////////////////
	// 打开一个皮肤包时，需要读取皮肤包的文件
	// 解析Resource.xml
	virtual bool BuilderTranslateResourceXml(char *pszXmlPath);
	// 解析Controls.xml
	virtual bool BuilderTranslateControlsXml(char *pszXmlPath);
	// 解析Windows.xml
	virtual bool BuilderTranslateWindowsXml(char *pszXmlPath);
	// 解析Layout.xml
	virtual bool BuilderTranslateLayoutXml(char *pszXmlPath);

	virtual ONE_RESOURCE_PROP_MAP* BuilderGetWindowPropMap();

	// 保存皮肤包
	virtual bool BuilderSaveSkin(char *pszSkinDir, char *pszSkinName);

	// 清空属性队列
	virtual void ReleaseSkinManagerPropetry();

//////////////////////////////////////////////////////////////////////////
	// 初始化Window皮肤
	virtual IPropertyWindow* InitWindowSkin(const char *pszSkinPath, const char *pszWndName);
	// 查找指定的属性
	virtual IPropertyBase* FindBaseProperty(OBJECT_TYPE_ID propType, const char* pszPropId);
	virtual IPropertyBase* FindBaseProperty(const char* pszPropType, const char* pszPropId);
	// 设置显示的语言种类
	virtual void SetArea(AREA_TYPE areaType);
	// 创建一个属性，并将次属性放入队列
	virtual IPropertyBase* CreateEmptyBaseProp(OBJECT_TYPE_ID propType, char *pszObjectId = NULL);
	// 取得ID号
	virtual int GetNewId();

private:
//////////////////////////////////////////////////////////////////////////
	// Builder使用函数
	bool BuilderCreateFileItem(char *pFilePath, ZIP_FILE &FileItem);
	void BuilderFreeFileItem(ZIP_FILE &FileItem);

//////////////////////////////////////////////////////////////////////////
	// 初始化皮肤包
	bool InitSkinPackage(const char *pszSkinPath);
	// 加载zip文件
	void LoadZipDll();
	void ResetBaseObjectId(int nObjectId);

//////////////////////////////////////////////////////////////////////////
	// Resource.xml相关
	// 解析Resource.xml
	bool TranslateResourceXml(ZIP_FILE *pResurceXml);
	void ReleasePropMap(RESOURCE_PROP_MAP &PropMap);
	void ReleaseBaseProp(IPropertyBase *pCtrlProp);
	void ReleasePropMapItem(ONE_RESOURCE_PROP_MAP* pPropMapItem);
	// 通用的从资源xml中创建属性
	bool GeneralCreateBaseProp(char *pPropType, XmlNode* pXmlNode, ONE_RESOURCE_PROP_MAP* pPropMap);
	// 设置属性与base属性的关联
	void SetPropetryBaseRelevancy();
	void SetPropRelevancy(ONE_RESOURCE_PROP_MAP* pFromMap, ONE_RESOURCE_PROP_MAP* pToMap);

//////////////////////////////////////////////////////////////////////////
	// Controls.xml 相关
	bool TranslateControlsXml(ZIP_FILE *pControlsXml);
	bool GeneralCreateSubProp(XmlNode* pXmlNode, ONE_RESOURCE_PROP_MAP* pCtrlPropMap);
	bool AppendBasePropToGroup(IPropertyGroup *pGroup, XmlNode* pXmlNode);

//////////////////////////////////////////////////////////////////////////
	// Windows.xml 相关
	// 解析Windows.xml
	bool TranslateWindowsXml(ZIP_FILE *pWindowsXml);

//////////////////////////////////////////////////////////////////////////
	// Layout.xml 相关
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
	// 皮肤路径
	string m_strSkinPath;
	// 所有种类的属性的队列
	RESOURCE_PROP_MAP m_AllPropMap;
	// 所有控件种类的属性的队列，KEY：控件类型名称，如：Button
	RESOURCE_PROP_MAP m_AllCtrlPropMap;
	// 所有窗口的属性管理器map
	ONE_RESOURCE_PROP_MAP m_AllWindowPropMap;
	// 布局队列，KEY：ObjectID
	ONE_RESOURCE_PROP_MAP m_LayoutWindowMap;

	// ImageBase 属性队列
	ONE_RESOURCE_PROP_MAP* m_pImageBasePropMap;
	ONE_RESOURCE_PROP_MAP* m_pImagePropMap;
	// FontBase 属性队列
	ONE_RESOURCE_PROP_MAP* m_pFontBasePropMap;
	ONE_RESOURCE_PROP_MAP* m_pFontPropMap;
	// CursorBase 属性队列
	ONE_RESOURCE_PROP_MAP* m_pCursorBasePropMap;
	ONE_RESOURCE_PROP_MAP* m_pCursorPropMap;
	// ColorBase 属性队列
	ONE_RESOURCE_PROP_MAP* m_pColorBasePropMap;
	ONE_RESOURCE_PROP_MAP* m_pColorPropMap;

	// zip文件
	IZipFileList *m_pZipFile;
	HMODULE m_hZipModule;

	AREA_TYPE m_AreaType;

	// 整个资源ObjectId
	int m_nObjectIdInRes;
	int m_nEmptyObjectId;
};
