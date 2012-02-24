
#include "StdAfx.h"
#include "..\..\Inc\Control\ICtrlPanel.h"
#include "..\..\Inc\IControlManager.h"

ICtrlPanel::ICtrlPanel(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_BASE_PANEL);

	m_pPropImage = NULL;
}

ICtrlPanel::~ICtrlPanel(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlPanel::CreateControlPropetry(bool bNeedSetDftProp)
{
	m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "����ͼƬ");
	IPropertyGroup* pPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "BkGroup", "����Group");
	CreatePropetry(pPropGroup, OTID_CURSOR, "BkCursor", "����Cursor");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont", "����font");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont1", "����font1");
	return true;
}

// ��ʼ���ؼ�
void ICtrlPanel::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlPanel::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlPanel::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlPanel::OnPaint(CDrawingBoard &DrawBoard)
{
	if (m_pPropImage != NULL)
		m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());
}
