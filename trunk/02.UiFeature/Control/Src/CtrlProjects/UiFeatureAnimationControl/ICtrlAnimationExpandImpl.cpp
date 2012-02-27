
#include "StdAfx.h"
#include "ICtrlAnimationExpandImpl.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"
#include <complex>

#define EXPAND_ANIMATION_TIME				(2)
#define EXPAND_ANIMATION_DRAW_TIME			(600)

ICtrlAnimationExpandImpl::ICtrlAnimationExpandImpl(void)
{
	// 添加控件，步骤3：向内核系统注册控件
	SetObjectType(CTRL_NAME_ANIMATION_EXPAND);

	INIT_RECT(m_DstExpandRct);
	INIT_RECT(m_NowExpandRct);
	m_nAnimationTime = 0;
	m_nHighTimerId = 0;
	INIT_RECT(m_IconRect);
	m_bIsUpMode = true;
	m_pPropPanelName = NULL;
	m_pPropSjGroup = NULL;
	m_pPropAnimationTopBound = NULL;
	m_pPropAnimationBottomBound = NULL;
	// 是否在动画过程中显示容器中的内容
	m_pPropIsShowPanel = NULL;
	// 三角形箭头：上
	m_pPropUpSjImg = NULL;
	// 三角形箭头Mark：上
	m_pPropUpSjMarkImg = NULL;
	// 三角形箭头：下
	m_pPropDownSjImg = NULL;
	// 三角形箭头Mark：下
	m_pPropDownSjMarkImg = NULL;
	// 展开的边框
	m_pPropFrameImg = NULL;
	// 展开的内容
	m_pPropFrameMidImg = NULL;
}

ICtrlAnimationExpandImpl::~ICtrlAnimationExpandImpl(void)
{
	m_HTimer.KillTimer();
}

// 派生控件用于创建属于自己的控件属性
bool ICtrlAnimationExpandImpl::CreateControlPropetry(bool bNeedSetDftProp)
{
	m_pPropPanelName = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "PanelName", "动画控件中包含的Panel控件的名字，Panel控件为一个容器");
	m_pPropIsShowPanel = (IPropertyBool*)CreatePropetry(NULL, OTID_BOOL, "ShowPanelInAnmation", "在动画的过程中，是否显示容器中控件的图像");
	m_pPropAnimationTopBound = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "TopBound", "动画的上边界，单位：像素");
	m_pPropAnimationBottomBound = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "BottomBound", "动画的下边界，单位：像素");
	m_pPropSjGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "SjGroup", "箭头图像组");
	m_pPropUpSjImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "UpSjImage", "方向向上的三角形图片");
	m_pPropSjWidth = (IPropertyInt*)CreatePropetry(m_pPropSjGroup, OTID_INT, "ImageWidth", "三角形图片的宽度，单位：像素");
	m_pPropSjHeight = (IPropertyInt*)CreatePropetry(m_pPropSjGroup, OTID_INT, "ImageHeight", "三角形图片的高度，单位：像素");
	m_pPropUpSjMarkImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "UpSjMarkImage", "方向向上的三角形的Alpha蒙罩图片");
	m_pPropDownSjImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "DownSjImage", "方向向下的三角形图片");
	m_pPropDownSjMarkImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "DownSjMarkImage", "方向向下的三角形的Alpha蒙罩图片");
	m_pPropFrameImg = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "ExpandFrame", "展开区域的边框图片");
	m_pPropFrameMidImg = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "ExpandMidImage", "展开区域的中间图片");

	return true;
}

// 开始动画
void ICtrlAnimationExpandImpl::BeginAnimation()
{
//	// 提高线程优先级
//	HANDLE hThreadMe = GetCurrentThread();
//	INT priority = GetThreadPriority(hThreadMe);
//	SetThreadPriority( hThreadMe,THREAD_PRIORITY_HIGHEST );

	m_DstExpandRct = this->GetClientRect();
	m_DstExpandRct.top = 100;
	m_DstExpandRct.bottom -= 100;

	m_nHighTimerId = m_HTimer.SetTimer(this->GetOwnerWindow(), EXPAND_ANIMATION_TIME);
}

// 取得用于绘制背景的图片DC
CDrawingImage* ICtrlAnimationExpandImpl::GetAnimationBackgroudMemDc()
{
	return &m_BkImageDc;
}

// 初始化控件
void ICtrlAnimationExpandImpl::OnCreate()
{
}

// 控件初始化完毕
void ICtrlAnimationExpandImpl::OnFinalCreate()
{
}

// 销毁控件
void ICtrlAnimationExpandImpl::OnDestroy()
{
}

// 绘制控件
void ICtrlAnimationExpandImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (!IS_SAFE_HANDLE(m_BkImageDc.GetBmpHandle()))
		return;

	RECT ctrlRct = this->GetClientRect();
	RECT UpRct = ctrlRct;
	RECT DownRct = ctrlRct;
	UpRct.bottom = m_NowExpandRct.top;
	DownRct.top = m_NowExpandRct.bottom;

	m_BkImageDc.BitBltTo(DrawBoard, UpRct, ctrlRct);
	m_BkImageDc.BitBltTo(DrawBoard, DownRct, m_NowExpandRct);

	m_pPropUpSjImg->DrawImage(DrawBoard, ctrlRct);
}

// 设置需要操作的图片的位置
void ICtrlAnimationExpandImpl::SetIconPostion(RECT iconRct)
{
	m_IconRect = iconRct;
}

// 设置箭头方向，true：向上
void ICtrlAnimationExpandImpl::SetUpMode(bool bIsUpMode)
{
	m_bIsUpMode = bIsUpMode;
}

// 定时器
void ICtrlAnimationExpandImpl::OnTimer(UINT nTimerId)
{
	if (m_nHighTimerId != 0 && m_nHighTimerId == nTimerId && m_pOwnerWindowBase != NULL)
	{
		RECT rcSrc = this->GetClientRect();
		RECT rcNow = rcSrc;

		m_nAnimationTime += EXPAND_ANIMATION_TIME;
		double time = (double)m_nAnimationTime / (double)EXPAND_ANIMATION_DRAW_TIME - 1.0;
		int nHeight = (int)ceil((double)(-1 * RECT_HEIGHT(m_DstExpandRct)) * ((double)pow(time, (double)6) - 1.0));

		int nY = 0;
		if (m_bIsUpMode)
		{
			double dbOffset = floor((double)(-1 * (m_DstExpandRct.top - rcSrc.top)) * ((double)pow(time, (double)6) - 1.0));
			nY = rcSrc.top + (int)(dbOffset);
		}
		else
		{
			nY = rcSrc.bottom - nHeight;
		}

		rcNow.top = nY;
		rcNow.bottom = nY + nHeight;
		if (m_NowExpandRct.top != rcNow.top || m_NowExpandRct.bottom != rcNow.bottom)
		{
			m_NowExpandRct = rcNow;
			this->RedrawControl(true);
		}

		if (m_nAnimationTime >= EXPAND_ANIMATION_DRAW_TIME)
		{
			m_NowExpandRct = m_DstExpandRct;
			m_HTimer.KillTimer();
			this->RedrawControl(true);
		}

		DEBUG_INFO("m_NowExpandRct left=%d, top=%d, right=%d, bottom=%d", m_NowExpandRct.left, m_NowExpandRct.top, m_NowExpandRct.right, m_NowExpandRct.bottom);
	}
}

//////////////////////////////////////////////////////////////////////////
