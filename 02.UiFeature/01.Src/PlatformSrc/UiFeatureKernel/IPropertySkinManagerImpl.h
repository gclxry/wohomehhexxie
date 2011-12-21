
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "ZipFileList.h"

// KEY:窗口名称，所有窗口的管理器map
typedef map<string, IPropertyWindow*>			WND_PROP_MAP;

// 资源属性队列
// 一种属性的队列，如：font、string、image等，KEY：属性名称
typedef map<string, IPropertyBase*>				PROP_MAP;
// 所有种类的属性的队列，KEY：属性类型名称，如：font
typedef map<string, PROP_MAP*>					ALL_PROP_MAP;

class IPropertySkinManagerImpl : public IPropertySkinManager
{
public:
	IPropertySkinManagerImpl(void);
	virtual ~IPropertySkinManagerImpl(void);

	static IPropertySkinManager* GetInstance();

	// 初始化Window皮肤
	virtual IPropertyWindow* InitWindowSkin(const char *pszSkinPath, const char *pszWndName);
	// 查找指定的属性
	virtual IPropertyBase* FindProperty(char* pszPropType, char* pszPropName);
	// 设置显示的语言种类
	virtual void SetArea(AREA_TYPE areaType);

protected:
	// 初始化皮肤包
	bool InitSkinPackage(const char *pszSkinPath);
	// 解析Resource.xml
	bool TranslateResourceXml(FILE_ITEM *pResurceXml);

private:
	// 清空属性队列
	void Release();
	void ReleaseProp(IPropertyBase *pCtrlProp);

	// 判断属性是否已经存在
	bool IsPropExist(XmlNode* pXmlNode, PROP_MAP* pPropMap, string &strPropName);
	// 通用的从资源xml中创建属性
	bool GeneralCreateProp(char *pPropType, XmlNode* pXmlNode, PROP_MAP* pPropMap);

private:
	// 所有窗口的属性管理器map
	WND_PROP_MAP m_WndPropMap;
	// 皮肤路径
	string m_strSkinPath;
	// zip文件
	CZipFileList m_ZipFile;
	// 所有种类的属性的队列
	ALL_PROP_MAP m_AllPropMap;
};
