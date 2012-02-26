// FontProViewStatic.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "FontProViewStatic.h"


// CFontProViewStatic

IMPLEMENT_DYNAMIC(CFontProViewStatic, CStatic)

CFontProViewStatic::CFontProViewStatic()
{
	m_pFontBaseProp = NULL;
	m_strText = "给你生活的忠告：多吃些粗粮，给别人比他们自己期许的更多，并且用心去做；熟记你喜欢的诗歌；不要轻信你听到的每件事；不要花光你的所有；不要想睡多久就睡多久；无论何时说“我爱你”，请真心实意；无论何时说“对不起”，请看着对方的眼睛；相信一见钟情；永远不要忽视别人的梦想；深情热烈地爱，也许你会受伤，但这是使人生完整的唯一方法；用一种明确的方法解决争议，不要冒犯；永远不要以貌取人；慢慢地说，但要迅速地想；当别人问你不想回答的问题时，笑着说“你为什么想知道？”。";
}

CFontProViewStatic::~CFontProViewStatic()
{
}


BEGIN_MESSAGE_MAP(CFontProViewStatic, CStatic)
END_MESSAGE_MAP()



// CFontProViewStatic message handlers



void CFontProViewStatic::RedrawView(IPropertyFontBase* pFontBaseProp)
{
	m_pFontBaseProp = pFontBaseProp;
}

void CFontProViewStatic::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
//	if (lpDrawItemStruct == NULL)
//		return;
//
////	if (m_pFontBaseProp == NULL)
//	{
//		CStatic::DrawItem(lpDrawItemStruct);
//		return;
//	}
//
//	CRect CtrlRct(0, 0, 0, 0);
//	this->GetClientRect(&CtrlRct);
//	m_MemDc.Create(CtrlRct.Width(), CtrlRct.Height(), 0, false, true)
//
//	m_pFontBaseProp->DrawText()

}
