
#pragma once
#include "..\ICtrlInterface.h"

// 添加控件，步骤1：编写一个控件名称宏。注意，控件名称不能相同
#define CTRL_NAME_STATICBOX						("StaticBox")

class ICtrlStaticBox : public ICtrlInterface
{
public:
	// 设置控件的文本
	virtual bool SetText(char* pszText) = 0;
	virtual bool SetBackgroundImage(CDrawingImage* pBkImg) = 0;
};
