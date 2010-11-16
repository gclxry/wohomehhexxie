
#pragma once
#include "BfButton.h"

struct DRAW_BTN_COLOR
{
	Color Text;
	Color OutR;
	Color UpBegin;
	Color UpEnd;
	Color DownBegin;
	Color DownEnd;
	Color BRColor;
	Color SRColor;
	COLORREF PtColor;
};

class CBfDrawButton : public CBfButton
{
public:
	CBfDrawButton(void);
	virtual ~CBfDrawButton(void);

private:

protected:
	virtual void OnPaint();

private:
	void CBfDrawButton::DrawButton(Color OutR, Color UpBegin, Color UpEnd, Color DownBegin, Color DownEnd, Color BRColor, Color SRColor, COLORREF PtColor);
	void CBfDrawButton::DrawFocus();
	void CBfDrawButton::DrawBtnText();
	void CBfDrawButton::Draw4Corner(Color BRColor, Color SRColor, COLORREF PtColor);
};
