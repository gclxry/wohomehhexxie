
#pragma once
#include "IFeatureObject.h"
#include "IPropertySkinManager.h"
#include "IPropertyImageBase.h"
#include "IWindowBase.h"
#include "CUiXmlWrite.h"

// ��output�������debug��Ϣ����ʹ�ú� DEBUG_INFO �����
void DebugInfoOutput(char *pszFormat, ...);
#ifndef _DEBUG
#define DEBUG_INFO
#else
#define DEBUG_INFO				DebugInfoOutput
#endif

// ���ݵ�ǰ���е�exe�ľ���Ŀ¼�����ϲ���Ŀ¼���õ�������·��
string PathHelper(char *pszFileName);
// �������������ַ����õ��������͵�IDֵ
OBJECT_TYPE_ID PropStringToType(string strPropType);
// ������������IDֵ�õ����������ַ���
string PropTypeToString(OBJECT_TYPE_ID propType);
// ����һ�����ԣ������������� group ���Ѿ����ˣ��ͷ���������ԣ����û�о��½�һ������
IPropertyBase* CreateResourcePropetry(IFeatureObject *pOwnerObj, IPropertySkinManager* pSkinPropMgr, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
// �ж�ָ���ļ��Ƿ����
bool FileExists(const char *pszFilePath);
// ��һ��xml�ڵ����һ��int����
void AddIntAttrToNode(CUiXmlWriteNode* pNode, const char* pszAttrName, int nInt);
// ��һ���������в�����Ϊ "@Object_Name" ������
IPropertyString* FindObjectNameProperty(IPropertyGroup *pGroupProp);

void RectScreenToClient(HWND hWnd, RECT& rct);
void RectClientToScreen(HWND hWnd, RECT& rct);
void InitPropImageBase(IMAGE_BASE_PROP *pImgBaseProp);

// ������Ե��������ĸ��ؼ�/���ڵ���Ϣ
void ClearGroupPropertyOwner(IPropertyGroup *pPropGroup);
