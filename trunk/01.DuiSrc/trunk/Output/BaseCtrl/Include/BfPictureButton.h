//////////////////////////////////////////////////////////////////////////
// 图片按钮

#pragma once
#include "BfButton.h"

// 一张图片上按钮的状态个数
enum BTN_STA_CTNS
{
	BSC_THREE	= 3,
	BSC_FOUR	= 4
};

class CBfPictureButton : public CBfButton
{
public:
	CBfPictureButton(void);
	virtual ~CBfPictureButton(void);

	void SetBtnPicStas(BTN_STA_CTNS nStas) { m_nPicStas = nStas; };

protected:
	virtual void OnPaint();

private:
	BTN_STA_CTNS m_nPicStas;
};
