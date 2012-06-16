//////////////////////////////////////////////////////////////////////////
// 当前皮肤所有窗口中所有控件的属性管理类

#pragma once
#include "IPropertyBase.h"
#include "IPropertyWindow.h"
#include "IZipFile.h"
#include "IPropertyFontBase.h"
#include "IPropertyImageBase.h"
#include "IPropertyString.h"

class IPropertySkinManager
{
	friend class CLocalImageList;
	friend class CMainFrame;
	friend class CPropertyViewCtrl;
	friend class CImageBaseNameList;
	friend class CFontBaseNameList;
	friend class CModifyFontBaseDlg;
	friend class CModifyMouseStyleDlg;
	friend class CWindowsViewTree;

public:
	// 清空4个xml文件的属性队列
	virtual void ReleaseSkinManagerPropetry() = 0;
	// 删除属性
	virtual bool DeletePropetryBaseProp(IPropertyBase *pPropBase) = 0;
	// 初始化鼠标手势属性
	virtual bool InitCursorBasePropetry() = 0;

	// 加载本地图片，如果这个路径的图片已经加载过了，返回原有的
	virtual IPropertyImageBase* LoadLocalImage(char *pszLocalImgPath) = 0;
	// 删除图片
	virtual bool DeleteImageBase(IPropertyImageBase *pPropImgBase) = 0;

//////////////////////////////////////////////////////////////////////////
	// 初始化Window皮肤
	virtual IPropertyWindow* PG_InitWindowSkin(const char *pszSkinPath, const char *pszWndName) = 0;
	// 设置显示的语言种类
	virtual void SetArea(AREA_TYPE areaType) = 0;
	// 创建一个属性，并将次属性放入队列
	virtual IPropertyBase* CreateEmptyBaseProp(OBJECT_TYPE_ID propType, char *pszObjectId = NULL) = 0;
	// 取得整个程序默认的字体信息
	virtual IPropertyFontBase* GetDefaultFontBase() = 0;

	// 查找指定的属性
	virtual IPropertyBase* FindBasePropertyByPropId(OBJECT_TYPE_ID propType, const char* pszPropId) = 0;
	virtual IPropertyBase* FindBasePropertyByPropId(const char* pszPropType, const char* pszPropId) = 0;
	// 查找指定的属性
	virtual IPropertyBase* FindBasePropertyByPropName(OBJECT_TYPE_ID propType, const char* pszPropName) = 0;
	virtual IPropertyBase* FindBasePropertyByPropName(const char* pszPropType, const char* pszPropName) = 0;

protected:

	// 解析Resource.xml
	virtual bool BD_TranslateResourceXml(char *pszXmlPath) = 0;
	// 解析Controls.xml
	virtual bool BD_TranslateControlsXml(char *pszXmlPath) = 0;
	// 解析Windows.xml
	virtual bool BD_TranslateWindowsXml(char *pszXmlPath) = 0;
	// 解析Layout.xml
	virtual bool BD_TranslateLayoutXml(char *pszXmlPath) = 0;
	// 得到Layout.xml队列
	virtual ONE_RESOURCE_PROP_MAP* BD_GetWindowPropMap() = 0;

	// 得到Resource.xml队列
	virtual RESOURCE_PROP_MAP* BD_GetResourcePropMap() = 0;
	// 修改属性名称
	virtual bool BD_ModifyPropetryName(IPropertyBase *pPropBase, char *pszNewPropName) = 0;

	// 取得指定组的属性
	virtual ONE_RESOURCE_PROP_MAP* GetOneResourcePropMap(char *pPropGroupName, bool bIsCreate = false) = 0;

//////////////////////////////////////////////////////////////////////////
	// 内存管理
	virtual ZIP_FILE_MAP* MEM_GetUnZipFileMap() = 0;
	virtual ZIP_FILE* MEM_CreateZipFile(int nFileBufLen, BYTE byFileType, char *pszFileName) = 0;
	virtual void MEM_DeleteZipFileByCom(ZIP_FILE *pComZipFile) = 0;
};
