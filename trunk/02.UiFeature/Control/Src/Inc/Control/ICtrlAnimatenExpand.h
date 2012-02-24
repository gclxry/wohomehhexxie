
#pragma once
#include "ICtrlInterface.h"

class ICtrlAnimatenExpand : public ICtrlInterface
{
public:
	ICtrlAnimatenExpand();
	virtual ~ICtrlAnimatenExpand();

	// ��ʼ����
	void BeginAnimation();
	// ȡ�����ڻ��Ʊ�����ͼƬDC
	CDrawingBoard* GetAnimationBackgroudMemDc();

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

private:
	// ����ͼ���ڴ�DC
	CDrawingBoard m_BkImageDc;
	// ��������
	IPropertyString* m_pPropPanelName;
	// �Ƿ��ڶ�����������ʾ�����е�����
	IPropertyBool* m_pPropIsShowPanel;
	IPropertyGroup* m_pPropSjGroup;
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
};
