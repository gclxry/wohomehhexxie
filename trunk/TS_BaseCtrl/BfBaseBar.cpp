
#include "BfBaseBar.h"

CBfBaseBar::CBfBaseBar(void)
{
}

CBfBaseBar::~CBfBaseBar(void)
{
}

void CBfBaseBar::OnLButtonDown(CPoint point)
{
	// 不让普通 bar 窗口取得焦点
	CDirectUiWindow::SetLButtonUp();
}
