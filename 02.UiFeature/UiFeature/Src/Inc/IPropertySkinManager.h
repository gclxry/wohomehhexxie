//////////////////////////////////////////////////////////////////////////
// ��ǰƤ�����д��������пؼ������Թ�����

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
	// ���4��xml�ļ������Զ���
	virtual void ReleaseSkinManagerPropetry() = 0;
	// ɾ������
	virtual bool DeletePropetryBaseProp(IPropertyBase *pPropBase) = 0;
	// ��ʼ�������������
	virtual bool InitCursorBasePropetry() = 0;

	// ���ر���ͼƬ��������·����ͼƬ�Ѿ����ع��ˣ�����ԭ�е�
	virtual IPropertyImageBase* LoadLocalImage(char *pszLocalImgPath) = 0;
	// ɾ��ͼƬ
	virtual bool DeleteImageBase(IPropertyImageBase *pPropImgBase) = 0;

//////////////////////////////////////////////////////////////////////////
	// ��ʼ��WindowƤ��
	virtual IPropertyWindow* PG_InitWindowSkin(const char *pszSkinPath, const char *pszWndName) = 0;
	// ������ʾ����������
	virtual void SetArea(AREA_TYPE areaType) = 0;
	// ����һ�����ԣ����������Է������
	virtual IPropertyBase* CreateEmptyBaseProp(OBJECT_TYPE_ID propType, char *pszObjectId = NULL) = 0;
	// ȡ����������Ĭ�ϵ�������Ϣ
	virtual IPropertyFontBase* GetDefaultFontBase() = 0;

	// ����ָ��������
	virtual IPropertyBase* FindBasePropertyByPropId(OBJECT_TYPE_ID propType, const char* pszPropId) = 0;
	virtual IPropertyBase* FindBasePropertyByPropId(const char* pszPropType, const char* pszPropId) = 0;
	// ����ָ��������
	virtual IPropertyBase* FindBasePropertyByPropName(OBJECT_TYPE_ID propType, const char* pszPropName) = 0;
	virtual IPropertyBase* FindBasePropertyByPropName(const char* pszPropType, const char* pszPropName) = 0;

protected:

	// ����Resource.xml
	virtual bool BD_TranslateResourceXml(char *pszXmlPath) = 0;
	// ����Controls.xml
	virtual bool BD_TranslateControlsXml(char *pszXmlPath) = 0;
	// ����Windows.xml
	virtual bool BD_TranslateWindowsXml(char *pszXmlPath) = 0;
	// ����Layout.xml
	virtual bool BD_TranslateLayoutXml(char *pszXmlPath) = 0;
	// �õ�Layout.xml����
	virtual ONE_RESOURCE_PROP_MAP* BD_GetWindowPropMap() = 0;

	// �õ�Resource.xml����
	virtual RESOURCE_PROP_MAP* BD_GetResourcePropMap() = 0;
	// �޸���������
	virtual bool BD_ModifyPropetryName(IPropertyBase *pPropBase, char *pszNewPropName) = 0;

	// ȡ��ָ���������
	virtual ONE_RESOURCE_PROP_MAP* GetOneResourcePropMap(char *pPropGroupName, bool bIsCreate = false) = 0;

//////////////////////////////////////////////////////////////////////////
	// �ڴ����
	virtual ZIP_FILE_MAP* MEM_GetUnZipFileMap() = 0;
	virtual ZIP_FILE* MEM_CreateZipFile(int nFileBufLen, BYTE byFileType, char *pszFileName) = 0;
	virtual void MEM_DeleteZipFileByCom(ZIP_FILE *pComZipFile) = 0;
};
