
#include "StdAfx.h"
#include "..\..\Inc\ICtrlAnimatenExpand.h"
#include "..\..\Inc\IControlManager.h"

ICtrlAnimatenExpand::ICtrlAnimatenExpand(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_ANIMATEN_EXPAND);
}

ICtrlAnimatenExpand::~ICtrlAnimatenExpand(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlAnimatenExpand::CreateControlPropetry(bool bNeedSetDftProp)
{
//	m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "����ͼƬ");
//	IPropertyGroup* pPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "BkGroup", "����Group");
//	CreatePropetry(pPropGroup, OTID_CURSOR, "BkCursor", "����Cursor");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont", "����font");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont1", "����font1");
	return true;
}

// ��ʼ���ؼ�
void ICtrlAnimatenExpand::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlAnimatenExpand::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlAnimatenExpand::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlAnimatenExpand::OnPaint(CDrawingBoard &DrawBoard)
{
//	if (m_pPropImage != NULL)
//		m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());
}
