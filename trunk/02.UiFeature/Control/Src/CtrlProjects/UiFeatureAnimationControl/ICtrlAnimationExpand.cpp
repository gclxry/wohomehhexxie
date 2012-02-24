
#include "StdAfx.h"
#include "..\..\Inc\Control\ICtrlAnimationExpand.h"
#include "..\..\Inc\IControlManager.h"

ICtrlAnimationExpand::ICtrlAnimationExpand(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_ANIMATION_EXPAND);

	m_pPropPanelName = NULL;
	m_pPropSjGroup = NULL;
	// �Ƿ��ڶ�����������ʾ�����е�����
	m_pPropIsShowPanel = NULL;
	// �����μ�ͷ����
	m_pPropUpSjImg = NULL;
	// �����μ�ͷMark����
	m_pPropUpSjMarkImg = NULL;
	// �����μ�ͷ����
	m_pPropDownSjImg = NULL;
	// �����μ�ͷMark����
	m_pPropDownSjMarkImg = NULL;
	// չ���ı߿�
	m_pPropFrameImg = NULL;
	// չ��������
	m_pPropFrameMidImg = NULL;
}

ICtrlAnimationExpand::~ICtrlAnimationExpand(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlAnimationExpand::CreateControlPropetry(bool bNeedSetDftProp)
{
	m_pPropPanelName = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "PanelName", "�����ؼ��а�����Panel�ؼ������֣�Panel�ؼ�Ϊһ������");
	m_pPropIsShowPanel = (IPropertyBool*)CreatePropetry(NULL, OTID_BOOL, "ShowPanelInAnmation", "�ڶ����Ĺ����У��Ƿ���ʾ�����пؼ���ͼ��");
	m_pPropSjGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "SjGroup", "��ͷͼ����");
	m_pPropUpSjImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "UpSjImage", "�������ϵ�������ͼƬ");
	m_pPropUpSjMarkImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "UpSjMarkImage", "�������ϵ������ε�Alpha����ͼƬ");
	m_pPropDownSjImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "DownSjImage", "�������µ�������ͼƬ");
	m_pPropDownSjMarkImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "DownSjMarkImage", "�������µ������ε�Alpha����ͼƬ");
	m_pPropFrameImg = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "ExpandFrame", "չ������ı߿�ͼƬ");
	m_pPropFrameMidImg = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "ExpandMidImage", "չ��������м�ͼƬ");

	return true;
}

// ��ʼ����
void ICtrlAnimationExpand::BeginAnimation()
{

}

// ȡ�����ڻ��Ʊ�����ͼƬDC
CDrawingBoard* ICtrlAnimationExpand::GetAnimationBackgroudMemDc()
{
	return &m_BkImageDc;
}

// ��ʼ���ؼ�
void ICtrlAnimationExpand::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlAnimationExpand::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlAnimationExpand::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlAnimationExpand::OnPaint(CDrawingBoard &DrawBoard)
{
//	if (m_pPropImage != NULL)
//		m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());
}
