
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "ZipFileList.h"
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
	virtual bool BD_TranslateResourceXml(char *pszXmlPath);
	// 解析Controls.xml
	virtual bool BD_TranslateControlsXml(char *pszXmlPath);
	// 解析Windows.xml
	virtual bool BD_TranslateWindowsXml(char *pszXmlPath);
	// 解析Layout.xml
	virtual bool BD_TranslateLayoutXml(char *pszXmlPath);
	// 取得所有窗口的队列
	virtual ONE_RESOURCE_PROP_MAP* BD_GetWindowPropMap();
	// 向控件队列添加一个控件
	virtual bool BD_AppendControlToVec(char *pszCtrlType, IPropertyGroup* pCtrlPropGroup);

	// 保存皮肤包
	virtual bool BD_SaveProject(char *pszSkinDir, char *pszSkinName);

	// 清空属性队列
	virtual void ReleaseSkinManagerPropetry();

//////////////////////////////////////////////////////////////////////////
	// 初始化Window皮肤
	virtual IPropertyWindow* PG_InitWindowSkin(const char *pszSkinPath, const char *pszWndName);
	// 查找指定的属性
	virtual IPropertyBase* FindBaseProperty(OBJECT_TYPE_ID propType, const char* pszPropId);
	virtual IPropertyBase* FindBaseProperty(const char* pszPropType, const char* pszPropId);
	// 设置显示的语言种类
	virtual void SetArea(AREA_TYPE areaType);
	// 创建一个属性，并将次属性放入队列
	virtual IPropertyBase* CreateEmptyBaseProp(OBJECT_TYPE_ID propType, char *pszObjectId = NULL);
	// 取得ID号
	virtual int GetNewId();

//////////////////////////////////////////////////////////////////////////
	ONE_RESOURCE_PROP_MAP * GetAllWindowPropMap();

	void ReleaseBaseProp(IPropertyBase *pCtrlProp);
private:
//////////////////////////////////////////////////////////////////////////
	// Builder使用函数
	bool BuilderCreateFileItem(char *pFilePath, ZIP_FILE &FileItem);
	void BuilderFreeFileItem(ZIP_FILE &FileItem);

//////////////////////////////////////////////////////////////////////////
	// 初始化皮肤包
	bool InitSkinPackage(const char *pszSkinPath);
	void ResetBaseObjectId(int nObjectId);

//////////////////////////////////////////////////////////////////////////
	// Resource.xml相关
	// 解析Resource.xml
	bool TranslateResourceXml(ZIP_FILE *pResurceXml);
	void ReleasePropMap(RESOURCE_PROP_MAP &PropMap);
	void ReleasePropMapItem(ONE_RESOURCE_PROP_MAP* pPropMapItem);
	// 通用的从资源xml中创建属性
	bool GeneralCreateBaseProp(char *pPropType, XmlNode* pXmlNode, ONE_RESOURCE_PROP_MAP* pPropMap);
	// 设置属性与base属性的关联
	void SetPropetryBaseRelevancy();
	void SetPropRelevancy(ONE_RESOURCE_PROP_MAP* pFromMap, ONE_RESOURCE_PROP_MAP* pToMap);

	bool SaveResourceXml(const char *pszSavePath, string &strXmlData);

//////////////////////////////////////////////////////////////////////////
	// Controls.xml 相关
	bool TranslateControlsXml(ZIP_FILE *pControlsXml);
	bool GeneralCreateSubProp(XmlNode* pXmlNode, ONE_RESOURCE_PROP_MAP* pCtrlPropMap);
	bool AppendBasePropToGroup(IPropertyGroup *pGroup, XmlNode* pXmlNode);

	bool SaveControlsXml(const char *pszSavePath, string &strXmlData);

//////////////////////////////////////////////////////////////////////////
	// Windows.xml 相关
	// 解析Windows.xml
	bool TranslateWindowsXml(ZIP_FILE *pWindowsXml);

	bool SaveWindowsXml(const char *pszSavePath, string &strXmlData);
	bool SaveXml_GroupProp(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentNode, IPropertyGroup *pPropGroup);

//////////////////////////////////////////////////////////////////////////
	// Layout.xml 相关
	bool TranslateLayoutXml(ZIP_FILE *pLayoutXml);
	bool GeneralCreateWindowLayoutProp(XmlNode* pXmlNode, PROP_CONTROL_VEC* pChildCtrlVec, IPropertyControl* pParentProp);
	IPropertyGroup* FindControlPropGroup(char *pszObjectId, string &strCtrlType);
	void ReleaseLayoutMap();
	void ReleaseLayoutMapPropControlVec(PROP_CONTROL_VEC* pCtrlVec);

	bool SaveLayoutXml(const char *pszSavePath, string &strXmlData);
	bool SaveLayoutXml_ChildCtrl(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pNode, PROP_CONTROL_VEC* pWndChildVec);

	void SaveToFile(char *pszFilePath, BYTE *pData, int nDataLen);
private:
	// 皮肤路径
	string m_strSkinPath;

	// Resource.xml 所有种类的属性的队列
	RESOURCE_PROP_MAP m_AllPropMap;
	// Controls.xml 所有控件种类的属性的队列，KEY：控件类型名称，如：Button
	// 存储每一个控件的具体的属性，所有控件属性都存放在一个 IPropertyGroup 下
	RESOURCE_PROP_MAP m_AllCtrlPropMap;
	// Windows.xml 所有窗口的属性管理器map
	// 存储每一个窗口的具体的属性，所有窗口属性都存放在一个 IPropertyGroup 下
	ONE_RESOURCE_PROP_MAP m_AllWindowPropMap;
	// 布局队列，KEY：ObjectID，存储 IPropertyWindow IPropertyControl
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
	CZipFileList *m_pZipFile;

	AREA_TYPE m_AreaType;

	// 整个资源ObjectId
	int m_nObjectIdInRes;
	int m_nEmptyObjectId;
};
