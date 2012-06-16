
#pragma once
#include "..\..\Inc\Control\ICtrlStaticBox.h"

class ICtrlStaticBoxImpl : public ICtrlStaticBox
{
public:
	ICtrlStaticBoxImpl();
	virtual ~ICtrlStaticBoxImpl();

	// 设置控件的文本
	virtual bool SetText(char* pszText);
	virtual bool SetBackgroundImage(CDrawingImage* pBkImg);

protected:
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
	void OnPaint(CDrawingBoard &DrawBoard);

private:
	IPropertyImage* m_pPropImage;
	IPropertyFont* m_pPropFont; 
	IPropertyString* m_pPropText;
};
