
#pragma once
#include "..\..\Inc\IUiFeatureKernel.h"
#include "IUiEngineImpl.h"
#include "IPropertySkinManagerImpl.h"
#include "ZipFileList.h"
#include "..\..\Inc\IControlManager.h"
#include "ControlImpl.h"

class IWindowBaseImpl;
typedef map<HWND, IWindowBaseImpl*>		WINDOW_IMPL_MAP;

class IUiFeatureKernelImpl : public IUiFeatureKernel
{
public:
	IUiFeatureKernelImpl(void);
	virtual ~IUiFeatureKernelImpl(void);

	static IUiFeatureKernel* GetInstance();

	virtual IPropertySkinManager* GetSkinManager();
	virtual IUiEngine* GetUiEngine();

//////////////////////////////////////////////////////////////////////////
	// Builder 使用函数
	// 创建/打开一个新的皮肤工程
	virtual bool BD_OpenProject(char *pszSkinDir, char *pszSkinName);
	// 取得所有支持的控件
	virtual CONTROL_REG_MAP *BD_GetRegisterControl();
	// 创建一个Builder使用的空的窗口
	virtual IWindowBase* BD_CreateWindowEmptyPropetry();
	// 创建一个Builder使用的窗口，并配置上属性
	virtual IWindowBase* BD_CreateWindowByPropetry(IPropertyWindow *pPropWnd);
	// 创建一个Builder使用的空的控件
	virtual IControlBase* BD_CreateControlEmptyPropetry(IWindowBase *pParentWnd, IControlBase *pParentCtrl, char *pszNewCtrlTypeName);
	// 创建一个Builder使用的控件，并配置上属性
	virtual IControlBase* CreateControlByPropetry(IWindowBase *pParentWnd, IControlBase *pParentCtrl, IPropertyControl *pPropCtrl);
	// 保存皮肤包
	virtual bool BD_SaveProject(char *pszSkinDir, char *pszSkinName);
	// 关闭一个工程
	virtual bool BD_CloseProject();
	// 设置可以保存的有效属性
	virtual void BD_SetWindowPropetryActiveProp(IWindowBase *pWndBase, bool bActive);
	// 删除一个windows
	virtual bool BD_DeleteWindow(IWindowBase *pWndBase);
	// 删除一个control
	virtual bool BD_DeleteControl(IControlBase *pCtrlBase);
	// 删除一张图片
	virtual bool BD_DeleteZipImage(ZIP_FILE* pZipImage);

//////////////////////////////////////////////////////////////////////////
	// 一个对话框从一个皮肤包里使用指定的对话框皮肤资源初始化自己
	virtual IWindowBase* PG_InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName);
	// 一个对话框释放皮肤资源，这个Kernel内核会调用，外部对话框不需要调用
	virtual void PG_ReleaseFeatureSkin(HWND hWnd);
	// 取得全局唯一定时器号
	virtual int GetTimerId();

	// 从zip文件中找到指定文件
	virtual bool FindUnZipFile(const char *pFileName, BYTE **ppOutBuffer, int *pnFileLen);

	CZipFileList *GetZipFile();
private:
	void ReleaseKernelWindow();
	bool BD_DeleteControl_FromCtrlVec(CHILD_CTRLS_VEC* pCtrlVec, IControlBase *pCtrlBase);

private:
	ULONG_PTR m_gdiplusToken;
	CControlImpl* m_pCtrlDllMgr;

	CZipFileList m_KernelZipFile;
	IUiEngineImpl *m_pUiEngine;
	IPropertySkinManagerImpl *m_pSkinMgr;

	WINDOW_IMPL_MAP m_WndImplMap;
	// 所有支持的控件
	CONTROL_REG_MAP m_CtrlRegMap;
	// Builder中使用的hwnd的索引值
	int m_nBuilderHwnd;
	// 全局唯一定时器号
	int m_nTimerId;
};
