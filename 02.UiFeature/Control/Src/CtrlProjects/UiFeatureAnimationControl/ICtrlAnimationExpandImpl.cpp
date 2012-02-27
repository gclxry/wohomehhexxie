
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
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
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
	m_HTimer.KillTimer();
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlAnimationExpandImpl::CreateControlPropetry(bool bNeedSetDftProp)
{
	m_pPropPanelName = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "PanelName", "�����ؼ��а�����Panel�ؼ������֣�Panel�ؼ�Ϊһ������");
	m_pPropIsShowPanel = (IPropertyBool*)CreatePropetry(NULL, OTID_BOOL, "ShowPanelInAnmation", "�ڶ����Ĺ����У��Ƿ���ʾ�����пؼ���ͼ��");
	m_pPropAnimationTopBound = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "TopBound", "�������ϱ߽磬��λ������");
	m_pPropAnimationBottomBound = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "BottomBound", "�������±߽磬��λ������");
	m_pPropSjGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "SjGroup", "��ͷͼ����");
	m_pPropUpSjImg = (IPropertyImage*)CreatePropetry(m_pPropSjGroup, OTID_IMAGE, "UpSjImage", "�������ϵ�������ͼƬ");
	m_pPropSjWidth = (IPropertyInt*)CreatePropetry(m_pPropSjGroup, OTID_INT, "ImageWidth", "������ͼƬ�Ŀ�ȣ���λ������");
	m_pPropSjHeight = (IPropertyInt*)CreatePropetry(m_pPropSjGroup, OTID_INT, "ImageHeight", "������ͼƬ�ĸ߶ȣ���λ������");
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
//	// ����߳����ȼ�
//	HANDLE hThreadMe = GetCurrentThread();
//	INT priority = GetThreadPriority(hThreadMe);
//	SetThreadPriority( hThreadMe,THREAD_PRIORITY_HIGHEST );

	m_DstExpandRct = this->GetClientRect();
	m_DstExpandRct.top = 100;
	m_DstExpandRct.bottom -= 100;

	m_nHighTimerId = m_HTimer.SetTimer(this->GetOwnerWindow(), EXPAND_ANIMATION_TIME);
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
	RECT UpRct = ctrlRct;
	RECT DownRct = ctrlRct;
	UpRct.bottom = m_NowExpandRct.top;
	DownRct.top = m_NowExpandRct.bottom;

	m_BkImageDc.BitBltTo(DrawBoard, UpRct, ctrlRct);
	m_BkImageDc.BitBltTo(DrawBoard, DownRct, m_NowExpandRct);

	m_pPropUpSjImg->DrawImage(DrawBoard, ctrlRct);
}

// ������Ҫ������ͼƬ��λ��
void ICtrlAnimationExpandImpl::SetIconPostion(RECT iconRct)
{
	m_IconRect = iconRct;
}

// ���ü�ͷ����true������
void ICtrlAnimationExpandImpl::SetUpMode(bool bIsUpMode)
{
	m_bIsUpMode = bIsUpMode;
}

// ��ʱ��
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
