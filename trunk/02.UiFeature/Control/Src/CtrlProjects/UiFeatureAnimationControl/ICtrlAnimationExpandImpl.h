
#pragma once
#include "..\..\Inc\Control\ICtrlAnimationExpand.h"
#include "..\..\Inc\CHighAccuracyTimer.h"

class ICtrlAnimationExpandImpl : public ICtrlAnimationExpand
{
public:
	ICtrlAnimationExpandImpl();
	virtual ~ICtrlAnimationExpandImpl();

	// ��ʼ����
	virtual void BeginAnimation();
	// ȡ�����ڻ��Ʊ�����ͼƬDC
	virtual CDrawingImage* GetAnimationBackgroudMemDc();
	// ������Ҫ������ͼƬ��λ��
	virtual void SetIconPostion(RECT iconRct);
	// ���ü�ͷ����true�����ϣ�false������
	virtual void SetUpMode(bool bIsUpMode);

protected:
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bNeedSetDftProp��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bNeedSetDftProp);
	// ��ʼ���ؼ�
	virtual void OnCreate();
	// �ؼ���ʼ�����
	virtual void OnFinalCreate();
	// ���ٿؼ�
	virtual void OnDestroy();
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard);
	// ��ʱ��
	virtual void OnTimer(UINT nTimerId);

private:
	int m_nAnimationTime;
	RECT m_DstExpandRct;
	RECT m_NowExpandRct;
	CHighAccuracyTimer m_HTimer;
	int m_nHighTimerId;
	// ������Ҫ������ͼƬ��λ��
	RECT m_IconRect;
	// ���ü�ͷ����true�����ϣ�false������
	bool m_bIsUpMode;
	// ����ͼ���ڴ�DC
	CDrawingImage m_BkImageDc;
	// ��������
	IPropertyString* m_pPropPanelName;
	// �Ƿ��ڶ�����������ʾ�����е�����
	IPropertyBool* m_pPropIsShowPanel;
	IPropertyGroup* m_pPropSjGroup;
	// �����μ�ͷ����
	IPropertyInt* m_pPropSjWidth;
	// �����μ�ͷ����
	IPropertyInt* m_pPropSjHeight;
	// �����μ�ͷ����
	IPropertyImage* m_pPropUpSjImg;
	// �����μ�ͷMark����
	IPropertyImage* m_pPropUpSjMarkImg;
	// �����μ�ͷ����
	IPropertyImage* m_pPropDownSjImg;
	// �����μ�ͷMark����
	IPropertyImage* m_pPropDownSjMarkImg;
	// չ���ı߿�
	IPropertyImage* m_pPropFrameImg;
	// չ��������
	IPropertyImage* m_pPropFrameMidImg;
	// �����ϱ߽�
	IPropertyInt* m_pPropAnimationTopBound;
	// �����±߽�
	IPropertyInt* m_pPropAnimationBottomBound;

};
