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
	m_strText = "����������Ҹ棺���Щ�����������˱������Լ�����ĸ��࣬��������ȥ���������ϲ����ʫ�裻��Ҫ������������ÿ���£���Ҫ����������У���Ҫ��˯��þ�˯��ã����ۺ�ʱ˵���Ұ��㡱��������ʵ�⣻���ۺ�ʱ˵���Բ��𡱣��뿴�ŶԷ����۾���\0\0";
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
