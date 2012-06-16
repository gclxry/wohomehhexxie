
#pragma once
#include "IFeatureObject.h"
#include "IPropertySkinManager.h"
#include "IPropertyImageBase.h"
#include "IWindowBase.h"
#include "CUiXmlWrite.h"

// 在output窗口输出debug信息，请使用宏 DEBUG_INFO 来输出
void DebugInfoOutput(char *pszFormat, ...);
#ifndef _DEBUG
#define DEBUG_INFO
#else
#define DEBUG_INFO				DebugInfoOutput
#endif

// 根据当前运行的exe的绝对目录，加上参数目录，得到的完整路径
string PathHelper(char *pszFileName);
// 根据属性类型字符串得到属性类型的ID值
OBJECT_TYPE_ID PropStringToType(string strPropType);
// 根据属性类型ID值得到属性类型字符串
string PropTypeToString(OBJECT_TYPE_ID propType);
// 创建一个属性，如果这个属性在 group 中已经有了，就返回这个属性，如果没有就新建一个属性
IPropertyBase* CreateResourcePropetry(IFeatureObject *pOwnerObj, IPropertySkinManager* pSkinPropMgr, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
// 判断指定文件是否存在
bool FileExists(const char *pszFilePath);
// 向一个xml节点插入一个int属性
void AddIntAttrToNode(CUiXmlWriteNode* pNode, const char* pszAttrName, int nInt);
// 从一个属性组中查找名为 "@Object_Name" 的属性
IPropertyString* FindObjectNameProperty(IPropertyGroup *pGroupProp);

void RectScreenToClient(HWND hWnd, RECT& rct);
void RectClientToScreen(HWND hWnd, RECT& rct);
void InitPropImageBase(IMAGE_BASE_PROP *pImgBaseProp);

// 清空属性的隶属于哪个控件/窗口的信息
void ClearGroupPropertyOwner(IPropertyGroup *pPropGroup);
