
#pragma once
#include "..\..\Inc\Control\ICtrlTabBar.h"
#include "..\..\Inc\Control\ICtrlButton.h"
#include "..\..\Inc\IPropertyInt.h"


typedef vector<ICtrlButton*>	BUTTON_VEC;

class ICtrlTabBarImpl : public ICtrlTabBar, public IControlMessage
{
public:
	ICtrlTabBarImpl();
	virtual ~ICtrlTabBarImpl();

	// 设置当前选中项
	virtual void SetCheck(int nBtnNum);
	// 取得指定项的矩形位置，相对于整个窗口
	virtual RECT GetButtonWindowRect(int nBtnNum);

protected:
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);
	// 派生控件用于创建属于自己的控件属性
	// bIsNewCtrl：true时说明是Builder调用，新创建一个控件，需要初始化属性的各个默认值
	// false：说明整个皮肤包已经初始化完毕，属性创建完毕的时候，从xml中读取的属性值已经赋值完毕了，不能再初始化，否则xml中的值会被冲掉
	virtual bool CreateControlPropetry(bool bIsNewCtrl);
	// 初始化控件
	virtual void OnCreate();
	// 控件初始化完毕
	virtual void OnFinalCreate();
	// 销毁控件
	virtual void OnDestroy();
	// 绘制控件
	virtual void OnPaint(CDrawingBoard &DrawBoard);
	// 移动、设置控件位置
	virtual void OnSize();
	// 当一个控件包含了其他子控件的时候，系统会发送创建或加载子控件的消息
	virtual void OnCreateSubControl(bool bIsCreate);
	// Builder刷新属性，此函数中只要重新加载控件属性即可
	virtual void OnBuilderRefreshProp(IPropertyBase* pPropBase);
	// 这个接口会在整个对话框初始化完成的时候调用
	// 控件通过派生这个接口，可以在这个接口函数里通过其他控件的名称取得当前对话框里的其他控件。
	virtual void OnWindowFinalCreate();

private:
	IPropertyInt* m_pPropTabButtonCtns;
	BUTTON_VEC m_ButtonVec;
};
