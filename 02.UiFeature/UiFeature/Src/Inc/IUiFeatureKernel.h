
#pragma once
#include "IWindowBase.h"
#include "IControlBase.h"
#include "IPropertyFontBase.h"
#include "IUiEngine.h"

class IUiFeatureKernel
{
	friend class CMainFrame;
	friend class CWindowsViewTree;
	friend class CLocalImageList;

public:
	virtual IPropertySkinManager* GetSkinManager() = 0;
	virtual IUiEngine* GetUiEngine() = 0;

	// ����һ������δ�������ԵĿؼ�
	virtual IControlBase* CreateControlEmptyPropetry(IWindowBase *pParentWnd, IControlBase *pParentCtrl, char *pszNewCtrlTypeName, char *pszNewCtrlName = NULL) = 0;

	// �˳�����ǰ���ã�ж��kernel����Դ���ⲿ�����������˳�Ӧ�ó���ǰ���е���
	// Ҳ�ɲ����ã���������GDI+�Ĳ����ڴ�й¶
	virtual void UnInitialized() = 0;
	// �Ƿ�Ϊ���ģʽ
	virtual bool IsDesignMode() = 0;
	// �Ƿ��Ѿ���ʼ��
	virtual bool IsInitialized() = 0;

//////////////////////////////////////////////////////////////////////////
	// һ���Ի����һ��Ƥ������ʹ��ָ���ĶԻ���Ƥ����Դ��ʼ���Լ�
	// �����ͷ�Ƥ����Դ���ͷ����ڲ��Զ����
	virtual IWindowBase* PG_InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName) = 0;
	// һ���Ի����ͷ�Ƥ����Դ�����Kernel�ں˻���ã��ⲿ�Ի�����Ҫ����
	virtual void PG_ReleaseFeatureSkin(HWND hWnd) = 0;
	// ��zip�ļ����ҵ�ָ���ļ�
	virtual bool FindUnZipFile(const char *pFileName, BYTE **ppOutBuffer, int *pnFileLen, ZIP_FILE **ppFindZipFile = NULL) = 0;

	// ����һ��Builderʹ�õĿؼ���������������
	virtual IControlBase* CreateControlByPropetry(IWindowBase *pParentWnd, IControlBase *pParentCtrl, IPropertyControl *pPropCtrl) = 0;
	// ȡ��ȫ��Ψһ��ʱ����
	virtual int GetTimerId() = 0;
	// ȡ����������Ĭ�ϵ�������Ϣ
	virtual IPropertyFontBase* GetDefaultFontBase() = 0;
	// ȡ��Ƥ����·��
	virtual char* GetSkinFilePath() = 0;
	// ȡ������֧�ֵĶ����б�
	virtual int GetAnimationList(const char* &strType) = 0;

protected:
//////////////////////////////////////////////////////////////////////////
	// Builder ʹ�ú���
	// ���õ�ǰΪ���ģʽ
	virtual void BD_SetDesignMode(bool bIsDesignMode) = 0;
	// ����/��һ���µ�Ƥ������
	virtual bool BD_OpenProject(char *pszSkinDir, char *pszSkinName) = 0;
	// ����һ��Builderʹ�õĿյĴ���
	virtual IWindowBase* BD_CreateWindowEmptyPropetry() = 0;
	// ����һ��Builderʹ�õĴ��ڣ�������������
	virtual IWindowBase* BD_CreateWindowByPropetry(IPropertyWindow *pPropWnd) = 0;
	// ����Ƥ����
	virtual bool BD_SaveProject(char *pszSkinDir, char *pszSkinName) = 0;
	// �ر�һ������
	virtual bool BD_CloseProject() = 0;
	// ���ÿ��Ա������Ч����
	virtual void BD_SetWindowPropetryActiveProp(IWindowBase *pWndBase, bool bActive) = 0;
	// ɾ��һ��windows
	virtual bool BD_DeleteWindow(IWindowBase *pWndBase) = 0;
	// ɾ��һ��control
	virtual bool BD_DeleteControl(IControlBase *pCtrlBase) = 0;
	// ɾ��һ��ͼƬ
	virtual bool BD_DeleteZipImage(ZIP_FILE* pZipImage) = 0;
	// ȡ������֧�ֵĿؼ�
	virtual CONTROL_REG_TLIST *BD_GetRegisterControl() = 0;

//////////////////////////////////////////////////////////////////////////
	// ���·��򽻻��ؼ�λ��
	virtual bool BD_UpDownChangeControlPostion(IControlBase *pToUpCtrl, IControlBase *pToDownCtrl) = 0;
	// ת�ƿؼ�������Ŀؼ�������
	virtual bool BD_MoveControlToOtherParentControl(IControlBase *pFromCtrl, IFeatureObject *pToParentCtrl) = 0;

};

//////////////////////////////////////////////////////////////////////////
// �ں˶ԡ��Ի��򡿵Ľӿ�
IUiFeatureKernel *GetUiKernelInterface();
typedef IUiFeatureKernel* (*GETUIKERNELINTERFACE)();
