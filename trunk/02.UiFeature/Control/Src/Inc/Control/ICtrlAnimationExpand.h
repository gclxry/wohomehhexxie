
#pragma once
#include "..\ICtrlInterface.h"
#include "..\CDrawingImage.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_ANIMATION_EXPAND					("AnimationExpand")

class ICtrlAnimationExpand : public ICtrlInterface
{
public:
	// ��ʼ����
	virtual void BeginAnimation() = 0;
	// ȡ�����ڻ��Ʊ�����ͼƬDC
	virtual CDrawingImage* GetAnimationBackgroudMemDc() = 0;
	// ������Ҫ������ͼƬ��λ��
	virtual void SetIconPostion(RECT iconRct) = 0;
	// ���ü�ͷ����true������
	virtual void SetUpMode(bool bIsUpMode) = 0;
};
