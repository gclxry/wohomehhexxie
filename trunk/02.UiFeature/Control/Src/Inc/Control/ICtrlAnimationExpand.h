
#pragma once
#include "..\ICtrlInterface.h"
#include "..\CDrawingBoard.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_ANIMATION_EXPAND					("AnimationExpand")

class ICtrlAnimationExpand : public ICtrlInterface
{
public:
	// ��ʼ����
	virtual void BeginAnimation() = 0;
	// ȡ�����ڻ��Ʊ�����ͼƬDC
	virtual CDrawingBoard* GetAnimationBackgroudMemDc() = 0;
};
