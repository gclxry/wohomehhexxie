
#include "StdAfx.h"
#include "ICtrlAnimationExpandImpl.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\UiFeatureDefs.h"

ICtrlAnimationExpandImpl::ICtrlAnimationExpandImpl(void)
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

ICtrlAnimationExpandImpl::~ICtrlAnimationExpandImpl(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlAnimationExpandImpl::CreateControlPropetry(bool bNeedSetDftProp)
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
void ICtrlAnimationExpandImpl::BeginAnimation()
{

}

// ȡ�����ڻ��Ʊ�����ͼƬDC
CDrawingImage* ICtrlAnimationExpandImpl::GetAnimationBackgroudMemDc()
{
	return &m_BkImageDc;
}

// ��ʼ���ؼ�
void ICtrlAnimationExpandImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlAnimationExpandImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlAnimationExpandImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlAnimationExpandImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (!IS_SAFE_HANDLE(m_BkImageDc.GetBmpHandle()))
		return;

	RECT ctrlRct = this->GetClientRect();
	RECT FromRct = ctrlRct;
	ctrlRct.bottom -= 100;
	m_BkImageDc.BitBltTo(DrawBoard, ctrlRct, FromRct);
}
