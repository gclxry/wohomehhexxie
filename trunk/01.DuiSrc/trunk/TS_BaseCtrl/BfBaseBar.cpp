
#include "BfBaseBar.h"

CBfBaseBar::CBfBaseBar(void)
{
}

CBfBaseBar::~CBfBaseBar(void)
{
}

void CBfBaseBar::OnLButtonDown(CPoint point)
{
	// ������ͨ bar ����ȡ�ý���
	CDirectUiWindow::SetLButtonUp();
}
