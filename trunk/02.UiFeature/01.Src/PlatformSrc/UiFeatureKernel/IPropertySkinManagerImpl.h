
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "..\..\Inc\IZipFileList.h"
#include "..\..\Inc\IPropertyGroup.h"

//////////////////////////////////////////////////////////////////////////
// 资源属性队列
// 一种属性的队列，如：font、string、image等，KEY：ObjectId
typedef map<string, IPropertyBase*>				PROP_MAP;
// 所有种类的属性的队列，KEY：属性类型名称，如：font
typedef map<string, PROP_MAP*>					ALL_PROP_MAP;

//////////////////////////////////////////////////////////////////////////
// 控件属性队列
// 一种控件的属性队列，如：Button、CheckBox等，KEY：ObjectId
typedef PROP_MAP								CONTROL_PROP_MAP;
// 所有控件种类的属性的队列，KEY：控件类型名称，如：Button
typedef map<string, CONTROL_PROP_MAP*>			ALL_CONTROL_PROP_MAP;

//////////////////////////////////////////////////////////////////////////
// 窗口属性队列
// KEY:窗口ID，所有窗口的管理器map
typedef map<string, IPropertyWindow*>			WND_PROP_MAP;

class IPropertySkinManagerImpl : public IPropertySkinManager
{
public:
	IPropertySkinManagerImpl(void);
	virtual ~IPropertySkinManagerImpl(void);

	static IPropertySkinManager* GetInstance();

	// 初始化Window皮肤
	virtual IPropertyWindow* InitWindowSkin(const char *pszSkinPath, const char *pszWndName);
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
	void ReleaseResourceXml();
	void ReleaseBaseProp(IPropertyBase *pCtrlProp);
	// 通用的从资源xml中创建属性
	bool GeneralCreateBaseProp(char *pPropType, XmlNode* pXmlNode, PROP_MAP* pPropMap);

//////////////////////////////////////////////////////////////////////////
	// Controls.xml 相关
	bool TranslateControlsXml(FILE_ITEM *pControlsXml);
	void ReleaseControlsXml();
	bool GeneralCreateCtrlProp(char *pCtrlType, XmlNode* pXmlNode, CONTROL_PROP_MAP* pCtrlPropMap);
	void AppendBasePropToGroup(IPropertyGroup *pGroup, XmlNode* pXmlNode);

//////////////////////////////////////////////////////////////////////////
	// Windows.xml 相关
	// 解析Windows.xml
	bool TranslateWindowsXml(FILE_ITEM *pWindowsXml);

//////////////////////////////////////////////////////////////////////////
	// Layout.xml 相关

private:
	// 皮肤路径
	string m_strSkinPath;
	// 所有种类的属性的队列
	ALL_PROP_MAP m_AllPropMap;
	// 所有控件种类的属性的队列，KEY：控件类型名称，如：Button
	ALL_CONTROL_PROP_MAP m_AllCtrlPropMap;
	// 所有窗口的属性管理器map
	WND_PROP_MAP m_WndPropMap;

	// zip文件
	IZipFileList *m_pZipFile;
	HMODULE m_hZipModule;

	AREA_TYPE m_AreaType;

	// 整个资源ObjectId
	int m_nObjectIdInRes;
	int m_nEmptyObjectId;
};
