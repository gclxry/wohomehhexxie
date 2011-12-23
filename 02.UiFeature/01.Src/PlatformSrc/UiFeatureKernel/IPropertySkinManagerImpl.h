
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "..\..\Inc\IZipFileList.h"

// KEY:窗口名称，所有窗口的管理器map
typedef map<string, IPropertyWindow*>			WND_PROP_MAP;

// 资源属性队列
// 一种属性的队列，如：font、string、image等
typedef vector<IPropertyBase*>					PROP_VEC;
// 所有种类的属性的队列，KEY：属性类型名称，如：font
typedef map<string, PROP_VEC*>					ALL_PROP_MAP;

class IPropertySkinManagerImpl : public IPropertySkinManager
{
public:
	IPropertySkinManagerImpl(void);
	virtual ~IPropertySkinManagerImpl(void);

	static IPropertySkinManager* GetInstance();

	// 初始化Window皮肤
	virtual IPropertyWindow* InitWindowSkin(const char *pszSkinPath, const char *pszWndName);
	// 查找指定的属性
	virtual IPropertyBase* FindProperty(PROP_TYPE propType, const char* pszPropId);
	virtual IPropertyBase* FindProperty(const char* pszPropType, const char* pszPropId);
	// 设置显示的语言种类
	virtual void SetArea(AREA_TYPE areaType);
	// 创建一个属性，并将次属性放入队列
	virtual IPropertyBase* CreateEmptyProperty(PROP_TYPE propType);
	// 取得ID号
	virtual int GetNewId();

private:
	// 初始化皮肤包
	bool InitSkinPackage(const char *pszSkinPath);
	// 加载zip文件
	void LoadZipDll();
	string PropTypeToString(PROP_TYPE propType);
	PROP_TYPE PropStringToType(string strPropType);

//////////////////////////////////////////////////////////////////////////
	// Resource.xml相关
	// 解析Resource.xml
	bool TranslateResourceXml(FILE_ITEM *pResurceXml);
	void ReleaseResourceXml();
	void ReleaseProperty(IPropertyBase *pCtrlProp);
	// 判断属性是否已经存在
	bool IsPropExist(XmlNode* pXmlNode, PROP_VEC* pPropVec, string &strPropId);
	// 通用的从资源xml中创建属性
	bool GeneralCreateProp(char *pPropType, XmlNode* pXmlNode, PROP_VEC* pPropMap);
	// 设置当前最大的PropId
	void ResetPropId(int nPropId);

//////////////////////////////////////////////////////////////////////////
	// Controls.xml 相关
	bool TranslateControlsXml(FILE_ITEM *pWindowsXml);

//////////////////////////////////////////////////////////////////////////
	// Windows.xml 相关
	// 解析Windows.xml
	bool TranslateWindowsXml(FILE_ITEM *pWindowsXml);

//////////////////////////////////////////////////////////////////////////
	// Layout.xml 相关

private:
	// 所有窗口的属性管理器map
	WND_PROP_MAP m_WndPropMap;
	// 皮肤路径
	string m_strSkinPath;
	// 所有种类的属性的队列
	ALL_PROP_MAP m_AllPropMap;

	// zip文件
	IZipFileList *m_pZipFile;
	HMODULE m_hZipModule;

	AREA_TYPE m_AreaType;

	// 皮肤各个属性的ID
	int m_bPropId;
};
