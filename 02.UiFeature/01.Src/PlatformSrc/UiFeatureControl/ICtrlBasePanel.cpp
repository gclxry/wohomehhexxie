
#include "StdAfx.h"
#include "..\..\Inc\ICtrlBasePanel.h"
#include "..\..\Inc\IControlManager.h"

ICtrlBasePanel::ICtrlBasePanel(void)
{
	// 添加控件，步骤3：向内核系统注册控件
	SetObjectType(CTRL_NAME_BASE_PANEL);

	m_pPropImage = NULL;
}

ICtrlBasePanel::~ICtrlBasePanel(void)
{
}

// 派生控件用于创建属于自己的控件属性
bool ICtrlBasePanel::CreateControlPropetry(bool bNeedSetDftProp)
{
	m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "背景图片");
	IPropertyGroup* pPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "BkGroup", "背景Group");
	CreatePropetry(pPropGroup, OTID_CURSOR, "BkCursor", "背景Cursor");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont", "背景font");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont1", "背景font1");
	return true;
}

// 初始化控件
void ICtrlBasePanel::OnCreate()
{
}

// 控件初始化完毕
void ICtrlBasePanel::OnFinalCreate()
{
}

// 销毁控件
void ICtrlBasePanel::OnDestroy()
{
}

// 绘制控件
void ICtrlBasePanel::OnPaint(CDrawingBoard &DrawBoard)
{
	if (m_pPropImage != NULL)
		m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());
}
