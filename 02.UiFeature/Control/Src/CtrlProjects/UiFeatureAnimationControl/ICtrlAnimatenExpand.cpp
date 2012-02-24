
#include "StdAfx.h"
#include "..\..\Inc\ICtrlAnimatenExpand.h"
#include "..\..\Inc\IControlManager.h"

ICtrlAnimatenExpand::ICtrlAnimatenExpand(void)
{
	// 添加控件，步骤3：向内核系统注册控件
	SetObjectType(CTRL_NAME_ANIMATION_EXPAND);

	m_pPropPanelName = NULL;
	m_pPropSjGroup = NULL;
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

ICtrlAnimatenExpand::~ICtrlAnimatenExpand(void)
{
}

// 派生控件用于创建属于自己的控件属性
bool ICtrlAnimatenExpand::CreateControlPropetry(bool bNeedSetDftProp)
{
	m_pPropPanelName = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "PanelName", "动画控件中包含的Panel控件的名字，Panel控件为一个容器");
	m_pPropIsShowPanel = (IPropertyBool*)CreatePropetry(NULL, OTID_BOOL, "ShowPanelInAnmation", "在动画的过程中，是否显示容器中控件的图像");
	m_pPropSjGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "SjGroup", "箭头图像组");
	m_pPropUpSjImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "UpSjImage", "方向向上的三角形图片");
	m_pPropUpSjMarkImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "UpSjMarkImage", "方向向上的三角形的Alpha蒙罩图片");
	m_pPropDownSjImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "DownSjImage", "方向向下的三角形图片");
	m_pPropDownSjMarkImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "DownSjMarkImage", "方向向下的三角形的Alpha蒙罩图片");
	m_pPropFrameImg = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "ExpandFrame", "展开区域的边框图片");
	m_pPropFrameMidImg = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "ExpandMidImage", "展开区域的中间图片");

	return true;
}

// 开始动画
void ICtrlAnimatenExpand::BeginAnimation()
{

}

// 取得用于绘制背景的图片DC
CDrawingBoard* ICtrlAnimatenExpand::GetAnimationBackgroudMemDc()
{
	return &m_BkImageDc;
}

// 初始化控件
void ICtrlAnimatenExpand::OnCreate()
{
}

// 控件初始化完毕
void ICtrlAnimatenExpand::OnFinalCreate()
{
}

// 销毁控件
void ICtrlAnimatenExpand::OnDestroy()
{
}

// 绘制控件
void ICtrlAnimatenExpand::OnPaint(CDrawingBoard &DrawBoard)
{
//	if (m_pPropImage != NULL)
//		m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());
}
