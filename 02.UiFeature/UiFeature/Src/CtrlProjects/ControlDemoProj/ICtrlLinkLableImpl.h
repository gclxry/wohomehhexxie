
#pragma once
#include "..\..\Inc\Control\ICtrlLinkLable.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IPropertyCursor.h"
#include "..\..\Inc\IPropertyFont.h"
#include "..\..\Inc\IPropertyFontBase.h"

class ICtrlLinkLableImpl : public ICtrlLinkLable
{
public:
	ICtrlLinkLableImpl();
	virtual ~ICtrlLinkLableImpl();

	// 设置Link文字
	virtual void SetLinkText(char *pText, bool bRedraw);
	// 设置Link链接地址URL
	virtual void SetLinkUrl(char *pUrl);
	// 取得Link链接地址URL
	virtual const char * GetLinkUrl();

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
	virtual void OnPaint(CDrawingBoard &DrawBoard);
	// 鼠标进入
	virtual void OnMouseEnter(POINT pt);
	// 鼠标移出
	virtual void OnMouseLeave(POINT pt);
	// 鼠标左键点击
	virtual void OnLButtonDown(POINT pt);
	// 鼠标左键抬起
	virtual void OnLButtonUp(POINT pt);
	// 设置控件光标
	virtual IPropertyCursor* OnSetCursor(POINT pt);

private:
	bool m_bIsLButtonDown;

	IPropertyString* m_pPropLinkText;
	IPropertyString* m_pPropLinkUrl;
	IPropertyCursor* m_pPropCursor;
	IPropertyGroup* m_PropFontGroup;
	IPropertyFont* m_pPropFontNormal;
	IPropertyFont* m_pPropFontHover;
	IPropertyFont* m_pPropFontDown;
};
