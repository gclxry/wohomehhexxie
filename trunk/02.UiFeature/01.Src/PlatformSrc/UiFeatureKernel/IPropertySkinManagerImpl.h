
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "..\..\Inc\IZipFileList.h"
#include "..\..\Inc\IPropertyGroup.h"

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

	virtual PROP_BASE_ITEM* BuilderGetWindowPropMap();

	// 清空属性队列
	virtual void ReleaseSkinManagerPropetry();

//////////////////////////////////////////////////////////////////////////
	// 初始化Window皮肤
	virtual IPropertyGroup* InitWindowSkin(const char *pszSkinPath, const char *pszWndName);
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
	bool BuilderCreateFileItem(char *pFilePath, FILE_ITEM &FileItem);
	void BuilderFreeFileItem(FILE_ITEM &FileItem);

//////////////////////////////////////////////////////////////////////////
	// 初始化皮肤包
	bool InitSkinPackage(const char *pszSkinPath);
	// 加载zip文件
	void LoadZipDll();
	void ResetBaseObjectId(int nObjectId);

//////////////////////////////////////////////////////////////////////////
	// Resource.xml相关
	// 解析Resource.xml
	bool TranslateResourceXml(FILE_ITEM *pResurceXml);
	void ReleasePropMap(PROP_BASE_MAP &PropMap);
	void ReleaseBaseProp(IPropertyBase *pCtrlProp);
	void ReleasePropMapItem(PROP_BASE_ITEM* pPropMapItem);
	// 通用的从资源xml中创建属性
	bool GeneralCreateBaseProp(char *pPropType, XmlNode* pXmlNode, PROP_BASE_ITEM* pPropMap);

//////////////////////////////////////////////////////////////////////////
	// Controls.xml 相关
	bool TranslateControlsXml(FILE_ITEM *pControlsXml);
	bool GeneralCreateSubProp(XmlNode* pXmlNode, PROP_BASE_ITEM* pCtrlPropMap);
	bool AppendBasePropToGroup(IPropertyGroup *pGroup, XmlNode* pXmlNode);

//////////////////////////////////////////////////////////////////////////
	// Windows.xml 相关
	// 解析Windows.xml
	bool TranslateWindowsXml(FILE_ITEM *pWindowsXml);

//////////////////////////////////////////////////////////////////////////
	// Layout.xml 相关
	bool TranslateLayoutXml(FILE_ITEM *pLayoutXml);
	bool GeneralCreateWindowLayoutProp(XmlNode* pXmlNode, CHILD_CTRL_PROP_VEC* pChildCtrlVec, IPropertyControl* pParentProp);
	IPropertyGroup* FindControlPropGroup(char *pszObjectId);
	void ReleaseLayoutMap();
	void ReleaseLayoutMapChildCtrlVec(CHILD_CTRL_PROP_VEC* pCtrlVec);

private:
	// 皮肤路径
	string m_strSkinPath;
	// 所有种类的属性的队列
	PROP_BASE_MAP m_AllPropMap;
	// 所有控件种类的属性的队列，KEY：控件类型名称，如：Button
	PROP_BASE_MAP m_AllCtrlPropMap;
	// 所有窗口的属性管理器map
	PROP_BASE_ITEM m_AllWindowPropMap;
	// 布局队列，KEY：ObjectID
	PROP_BASE_ITEM m_LayoutWindowVec;

	// ImageBase 属性队列
	PROP_BASE_ITEM* m_pImageBasePropMap;
	// FontBase 属性队列
	PROP_BASE_ITEM* m_pFontBasePropMap;
	// CursorBase 属性队列
	PROP_BASE_ITEM* m_pCursorBasePropMap;
	// ColorBase 属性队列
	PROP_BASE_ITEM* m_pColorBasePropMap;

	// zip文件
	IZipFileList *m_pZipFile;
	HMODULE m_hZipModule;

	AREA_TYPE m_AreaType;

	// 整个资源ObjectId
	int m_nObjectIdInRes;
	int m_nEmptyObjectId;
};
