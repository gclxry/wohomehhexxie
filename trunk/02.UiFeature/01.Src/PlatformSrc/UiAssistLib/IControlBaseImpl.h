
#pragma once
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\IUiEngine.h"

class IControlBaseImpl : public IControlBase
{
public:
	IControlBaseImpl(void);
	virtual ~IControlBaseImpl(void);

	// 重绘控件
	virtual void RedrawControl(bool bDrawImmediately = true);
	// 重绘控件，这个重绘动画定时器中调用
	virtual void RedrawControlInAnimationTimer();
	// 设置控件在下次绘制的时候是否需要进行重绘
	virtual void SetNeedRedraw(bool bNeedRedraw);
	// 取得子控件列表
	virtual CHILD_CTRLS_VEC* GetChildCtrlsVec();
	// 取得属性
	virtual IPropertyControlInWindow* GetControlBaseProp();

	// 鼠标是否Hover
	virtual void SetMouseHover(bool bHover);
	virtual bool IsMousehover();

protected:
	// 绘制控件
	virtual void OnPaint();

private:
	// 设置子控件都必须自绘
	virtual void SetChildCtrlToRedraw();
	// 绘制当前控件，参数为父窗口/父控件的内存DC
	virtual void OnPaintControl(CMemoryDC &WndMemDc);

private:
	// 整个控件的内存DC
	CMemoryDC m_CtrlMemDc;
	// 附着的窗口
	IWindowBase* m_pParentWindowBase;
	// 子控件列表
	CHILD_CTRLS_VEC m_ChildCtrlsVec;
	// 是否需重绘控件
	bool m_bNeedRedraw;
	// 绘图引擎
	IUiEngine *m_pUiEngine;
	// 控件属性
	IPropertyControlInWindow *m_pCtrlProp;
	// 鼠标Hover状态
	bool m_bMouseHover;
};
