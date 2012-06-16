
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_STATICBOX						("StaticBox")

class ICtrlStaticBox : public ICtrlInterface
{
public:
	// ���ÿؼ����ı�
	virtual bool SetText(char* pszText) = 0;
	virtual bool SetBackgroundImage(CDrawingImage* pBkImg) = 0;
};
