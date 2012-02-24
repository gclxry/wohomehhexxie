
#pragma once
#include "..\..\Inc\Control\ICtrlAnimationExpand.h"
#include "..\..\Inc\CHighAccuracyTimer.h"

class ICtrlAnimationExpandImpl : public ICtrlAnimationExpand
{
public:
	ICtrlAnimationExpandImpl();
	virtual ~ICtrlAnimationExpandImpl();

	// 开始动画
	virtual void BeginAnimation();
	// 取得用于绘制背景的图片DC
	virtual CDrawingImage* GetAnimationBackgroudMemDc();
	// 设置需要操作的图片的位置
	virtual void SetIconPostion(RECT iconRct);
	// 设置箭头方向，true：向上，false：向下
	virtual void SetUpMode(bool bIsUpMode);

protected:
	// 派生控件用于创建属于自己的控件属性
	// bNeedSetDftProp：true时说明是Builder调用，新创建一个控件，需要初始化属性的各个默认值
	// false：说明整个皮肤包已经初始化完毕，属性创建完毕的时候，从xml中读取的属性值已经赋值完毕了，不能再初始化，否则xml中的值会被冲掉
	virtual bool CreateControlPropetry(bool bNeedSetDftProp);
	// 初始化控件
	virtual void OnCreate();
	// 控件初始化完毕
	virtual void OnFinalCreate();
	// 销毁控件
	virtual void OnDestroy();
	// 绘制控件
	virtual void OnPaint(CDrawingBoard &DrawBoard);
	// 定时器
	virtual void OnTimer(UINT nTimerId);

private:
	int m_nAnimationTime;
	RECT m_DstExpandRct;
	RECT m_NowExpandRct;
	CHighAccuracyTimer m_HTimer;
	int m_nHighTimerId;
	// 设置需要操作的图片的位置
	RECT m_IconRect;
	// 设置箭头方向，true：向上，false：向下
	bool m_bIsUpMode;
	// 背景图的内存DC
	CDrawingImage m_BkImageDc;
	// 容器名称
	IPropertyString* m_pPropPanelName;
	// 是否在动画过程中显示容器中的内容
	IPropertyBool* m_pPropIsShowPanel;
	IPropertyGroup* m_pPropSjGroup;
	// 三角形箭头：宽
	IPropertyInt* m_pPropSjWidth;
	// 三角形箭头：高
	IPropertyInt* m_pPropSjHeight;
	// 三角形箭头：上
	IPropertyImage* m_pPropUpSjImg;
	// 三角形箭头Mark：上
	IPropertyImage* m_pPropUpSjMarkImg;
	// 三角形箭头：下
	IPropertyImage* m_pPropDownSjImg;
	// 三角形箭头Mark：下
	IPropertyImage* m_pPropDownSjMarkImg;
	// 展开的边框
	IPropertyImage* m_pPropFrameImg;
	// 展开的内容
	IPropertyImage* m_pPropFrameMidImg;
	// 动画上边界
	IPropertyInt* m_pPropAnimationTopBound;
	// 动画下边界
	IPropertyInt* m_pPropAnimationBottomBound;

};
