
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

	// 初始化Window皮肤
	virtual IPropertyGroup* InitWindowSkin(const char *pszSkinPath, const char *pszWndName);
	// 查找指定的属性
	virtual IPropertyBase* FindBaseProperty(PROP_TYPE propType, const char* pszPropId);
	virtual IPropertyBase* FindBaseProperty(const char* pszPropType, const char* pszPropId);
	// 设置显示的语言种类
	virtual void SetArea(AREA_TYPE areaType);
	// 创建一个属性，并将次属性放入队列
	virtual IPropertyBase* CreateEmptyBaseProp(PROP_TYPE propType);
	// 取得ID号
	virtual int GetNewId();

private:
	// 初始化皮肤包
	bool InitSkinPackage(const char *pszSkinPath);
	// 加载zip文件
	void LoadZipDll();
	string PropTypeToString(PROP_TYPE propType);
	PROP_TYPE PropStringToType(string strPropType);
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
	// 布局队列
	WINDOW_PROP_MAP m_LayoutWindowVec;

	// zip文件
	IZipFileList *m_pZipFile;
	HMODULE m_hZipModule;

	AREA_TYPE m_AreaType;

	// 整个资源ObjectId
	int m_nObjectIdInRes;
	int m_nEmptyObjectId;
};
