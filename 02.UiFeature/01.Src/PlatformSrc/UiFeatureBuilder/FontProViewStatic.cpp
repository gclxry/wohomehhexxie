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
	m_strText = "����������Ҹ棺���Щ�����������˱������Լ�����ĸ��࣬��������ȥ���������ϲ����ʫ�裻��Ҫ������������ÿ���£���Ҫ����������У���Ҫ��˯��þ�˯��ã����ۺ�ʱ˵���Ұ��㡱��������ʵ�⣻���ۺ�ʱ˵���Բ��𡱣��뿴�ŶԷ����۾�������һ�����飻��Զ��Ҫ���ӱ��˵����룻�������ҵذ���Ҳ��������ˣ�������ʹ����������Ψһ��������һ����ȷ�ķ���������飬��Ҫð������Զ��Ҫ��òȡ�ˣ�������˵����ҪѸ�ٵ��룻���������㲻��ش������ʱ��Ц��˵����Ϊʲô��֪��������";
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
