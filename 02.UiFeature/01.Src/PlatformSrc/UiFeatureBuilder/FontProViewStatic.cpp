// FontProViewStatic.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "FontProViewStatic.h"
#include "..\..\Inc\UiFeatureDefs.h"

#pragma warning(disable:4244)


// CFontProViewStatic

IMPLEMENT_DYNAMIC(CFontProViewStatic, CStatic)

CFontProViewStatic::CFontProViewStatic()
{
	m_pFontBaseProp = NULL;
	m_strText = "给你生活的忠告：多吃些粗粮，给别人比他们自己期许的更多，并且用心去做；熟记你喜欢的诗歌；不要轻信你听到的每件事；不要花光你的所有；不要想睡多久就睡多久；无论何时说“我爱你”，请真心实意；无论何时说“对不起”，请看着对方的眼睛。\0\0";
}

CFontProViewStatic::~CFontProViewStatic()
{
}


BEGIN_MESSAGE_MAP(CFontProViewStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CFontProViewStatic message handlers



void CFontProViewStatic::RedrawView(IPropertyFontBase* pFontBaseProp)
{
	m_pFontBaseProp = pFontBaseProp;
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CFontProViewStatic::OnPaint()
{
	CPaintDC dc(this);

	CRect CtrlRct(0, 0, 0, 0);
	this->GetClientRect(&CtrlRct);
	m_MemDc.Create(CtrlRct.Width(), CtrlRct.Height(), 0, false, true);

	Graphics DoGrap(m_MemDc.GetSafeHdc());

	SolidBrush BkSBrush(Color(255, 255, 255, 255));
	RectF ToRctF;
	ToRctF.X = CtrlRct.left;
	ToRctF.Y = CtrlRct.top;
	ToRctF.Width = RECT_WIDTH(CtrlRct);
	ToRctF.Height = RECT_HEIGHT(CtrlRct);
	DoGrap.FillRectangle(&BkSBrush, ToRctF);

	ToRctF.Width--;
	ToRctF.Height--;
	SolidBrush frameSBrush(Color(255, 255, 0, 0));
	Pen framePen(&frameSBrush);
	DoGrap.DrawRectangle(&framePen, ToRctF);

	if (m_pFontBaseProp != NULL)
		m_pFontBaseProp->DrawFontText(m_MemDc, (char*)m_strText.c_str(), CtrlRct);

	::BitBlt(dc.m_hDC, 0, 0, CtrlRct.Width(), CtrlRct.Height(), m_MemDc.GetSafeHdc(), 0, 0, SRCCOPY);
}
