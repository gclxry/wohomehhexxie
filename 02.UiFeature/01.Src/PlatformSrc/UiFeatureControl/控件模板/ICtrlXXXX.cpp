
#include "StdAfx.h"
#include "..\..\Inc\ICtrlXXXX.h"
#include "..\..\Inc\IControlManager.h"

ICtrlXXXX::ICtrlXXXX(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_BASE_PANEL);
}

ICtrlXXXX::~ICtrlXXXX(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlXXXX::CreateControlPropetry(bool bNeedSetDftProp)
{
//	m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "����ͼƬ");
//	IPropertyGroup* pPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "BkGroup", "����Group");
//	CreatePropetry(pPropGroup, OTID_CURSOR, "BkCursor", "����Cursor");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont", "����font");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont1", "����font1");
	return true;
}

// ��ʼ���ؼ�
void ICtrlXXXX::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlXXXX::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlXXXX::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlXXXX::OnPaint(CDrawingBoard &DrawBoard)
{
//	if (m_pPropImage != NULL)
//		m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());
}
