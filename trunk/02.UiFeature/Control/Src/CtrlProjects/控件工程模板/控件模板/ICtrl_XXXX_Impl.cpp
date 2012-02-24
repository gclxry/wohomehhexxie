
#include "StdAfx.h"
#include "ICtrl_XXXX_Impl.h"
#include "..\..\Inc\IControlManager.h"

ICtrl_XXXX_Impl::ICtrl_XXXX_Impl(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_BASE_PANEL);

	m_pPropImage = NULL;
}

ICtrl_XXXX_Impl::~ICtrl_XXXX_Impl(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrl_XXXX_Impl::CreateControlPropetry(bool bNeedSetDftProp)
{
	m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "����ͼƬ");
	IPropertyGroup* pPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "BkGroup", "����Group");
	CreatePropetry(pPropGroup, OTID_CURSOR, "BkCursor", "����Cursor");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont", "����font");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont1", "����font1");
	return true;
}

// ��ʼ���ؼ�
void ICtrl_XXXX_Impl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrl_XXXX_Impl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrl_XXXX_Impl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrl_XXXX_Impl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (m_pPropImage != NULL)
		m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());
}
