
#include "stdafx.h"
#include "..\..\Inc\IPropertyFontBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"
#include <atlconv.h>
using namespace ATL;

#pragma warning(disable:4244)

IPropertyFontBase::IPropertyFontBase()
{
	SetObjectType(PROP_TYPE_FONT_BASE_NAME);
	SetObjectName("Ĭ�����壺���壬12");

	m_FontProp.bIsPicText = false;
	m_FontProp.FontColor = 0;

	memset(&m_FontProp.Font, 0, sizeof(LOGFONTA));
	m_FontProp.Font.lfHeight = 12;
	m_FontProp.Font.lfWidth = 0;
	m_FontProp.Font.lfEscapement = 0;
	m_FontProp.Font.lfOrientation = 0;
	m_FontProp.Font.lfWeight = FW_NORMAL;
	m_FontProp.Font.lfItalic = 0;
	m_FontProp.Font.lfUnderline = 0;
	m_FontProp.Font.lfStrikeOut = 0;
	m_FontProp.Font.lfCharSet = DEFAULT_CHARSET;
	m_FontProp.Font.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_FontProp.Font.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_FontProp.Font.lfQuality = PROOF_QUALITY;
	m_FontProp.Font.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	strcpy_s(m_FontProp.Font.lfFaceName, 32, "����");

	m_FontProp.HAligning = FAL_LEFT_TOP;
	m_FontProp.VAligning = FAL_MIDDLE;
	m_FontProp.ShowMode = FSM_ONE_ROW_NO_POINT;
	m_FontProp.FontEffect = FE_NONE;
}

IPropertyFontBase::~IPropertyFontBase()
{

}

bool IPropertyFontBase::IsRightData()
{
	return true;
}

FONT_PROP* IPropertyFontBase::GetFontProp()
{
	return &m_FontProp;
}

void IPropertyFontBase::SetFontProp(FONT_PROP *pFontProp)
{
	if (pFontProp == NULL)
		return;

	m_FontProp = *pFontProp;
}

bool IPropertyFontBase::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	if (psz_id == NULL || psz_name == NULL)
		return false;

	XmlNode* pLogfont = JabberXmlGetChild(pXmlNode, "logfont");
	XmlNode* pMode = JabberXmlGetChild(pXmlNode, "mode");
	if (pLogfont == NULL || pMode == NULL)
		return false;

	// logfont
	char* psz_lfFaceName = JabberXmlGetAttrValue(pLogfont, "lfFaceName");
	char* psz_lfHeight = JabberXmlGetAttrValue(pLogfont, "lfHeight");
	char* psz_lfWidth = JabberXmlGetAttrValue(pLogfont, "lfWidth");
	char* psz_lfEscapement = JabberXmlGetAttrValue(pLogfont, "lfEscapement");
	char* psz_lfOrientation = JabberXmlGetAttrValue(pLogfont, "lfOrientation");
	char* psz_lfWeight = JabberXmlGetAttrValue(pLogfont, "lfWeight");
	char* psz_lfItalic = JabberXmlGetAttrValue(pLogfont, "lfItalic");
	char* psz_lfUnderline = JabberXmlGetAttrValue(pLogfont, "lfUnderline");
	char* psz_lfStrikeOut = JabberXmlGetAttrValue(pLogfont, "lfStrikeOut");
	char* psz_lfCharSet = JabberXmlGetAttrValue(pLogfont, "lfCharSet");
	char* psz_lfOutPrecision = JabberXmlGetAttrValue(pLogfont, "lfOutPrecision");
	char* psz_lfClipPrecision = JabberXmlGetAttrValue(pLogfont, "lfClipPrecision");
	char* psz_lfQuality = JabberXmlGetAttrValue(pLogfont, "lfQuality");
	char* psz_lfPitchAndFamily = JabberXmlGetAttrValue(pLogfont, "lfPitchAndFamily");

	// mode
	char* psz_color = JabberXmlGetAttrValue(pMode, "color");
	char* psz_VAligning = JabberXmlGetAttrValue(pMode, "VAligning");
	char* psz_HAligning = JabberXmlGetAttrValue(pMode, "HAligning");
	char* psz_ShowMode = JabberXmlGetAttrValue(pMode, "ShowMode");
	char* psz_Effect = JabberXmlGetAttrValue(pMode, "Effect");

	if (psz_lfPitchAndFamily == NULL || psz_color == NULL || psz_lfFaceName == NULL || psz_lfHeight == NULL || psz_lfWidth == NULL || 
		psz_lfEscapement == NULL || psz_lfOrientation == NULL || psz_lfWeight == NULL || psz_lfItalic == NULL || psz_lfUnderline == NULL || 
		psz_lfStrikeOut == NULL || psz_lfCharSet == NULL || psz_lfOutPrecision == NULL || psz_lfClipPrecision == NULL || psz_lfQuality == NULL ||
		psz_VAligning == NULL || psz_HAligning == NULL || psz_ShowMode == NULL || psz_Effect == NULL)
		return false;

	SetObjectId((const char *)psz_id);
	SetObjectName((const char *)psz_name);

	// logfont
	strcpy_s(m_FontProp.Font.lfFaceName, 32, psz_lfFaceName);
	m_FontProp.Font.lfHeight = atoi(psz_lfHeight);
	m_FontProp.Font.lfWidth = atoi(psz_lfWidth);
	m_FontProp.Font.lfEscapement = atoi(psz_lfEscapement);
	m_FontProp.Font.lfOrientation = atoi(psz_lfOrientation);
	m_FontProp.Font.lfWeight = atoi(psz_lfWeight);
	m_FontProp.Font.lfItalic = atoi(psz_lfItalic);
	m_FontProp.Font.lfUnderline = atoi(psz_lfUnderline);
	m_FontProp.Font.lfStrikeOut = atoi(psz_lfStrikeOut);
	m_FontProp.Font.lfCharSet = atoi(psz_lfCharSet);
	m_FontProp.Font.lfOutPrecision = atoi(psz_lfOutPrecision);
	m_FontProp.Font.lfClipPrecision = atoi(psz_lfClipPrecision);
	m_FontProp.Font.lfQuality = atoi(psz_lfQuality);
	m_FontProp.Font.lfPitchAndFamily = atoi(psz_lfPitchAndFamily);

	// mode
	m_FontProp.FontColor = atoi(psz_color);
	m_FontProp.HAligning = (FONT_ALIGNING)atoi(psz_HAligning);
	m_FontProp.VAligning = (FONT_ALIGNING)atoi(psz_VAligning);
	m_FontProp.ShowMode = (FONT_SHOW_MODE)atoi(psz_ShowMode);
	m_FontProp.FontEffect = atoi(psz_Effect);

	return true;
}

// д��xml
bool IPropertyFontBase::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
{
	// �������Ч���ԣ���д��XML
	if (!GetActivePropetry())
		return true;

	if (pParentXmlNode == NULL)
		return false;

	CUiXmlWriteNode* pPropNode = XmlStrObj.CreateNode(pParentXmlNode, "item");
	if (pPropNode == NULL)
		return false;

	pPropNode->AddAttribute(SKIN_OBJECT_ID, GetObjectId());
	pPropNode->AddAttribute("name", GetObjectName());

	CUiXmlWriteNode* pNode_logfont = XmlStrObj.CreateNode(pPropNode, "logfont");
	if (pNode_logfont == NULL)
		return false;

	pNode_logfont->AddAttribute("lfFaceName", m_FontProp.Font.lfFaceName);
	AddIntAttrToNode(pNode_logfont, "lfHeight", m_FontProp.Font.lfHeight);
	AddIntAttrToNode(pNode_logfont, "lfWidth", m_FontProp.Font.lfWidth);
	AddIntAttrToNode(pNode_logfont, "lfEscapement", m_FontProp.Font.lfEscapement);
	AddIntAttrToNode(pNode_logfont, "lfOrientation", m_FontProp.Font.lfOrientation);
	AddIntAttrToNode(pNode_logfont, "lfWeight", m_FontProp.Font.lfWeight);
	AddIntAttrToNode(pNode_logfont, "lfItalic", m_FontProp.Font.lfItalic);
	AddIntAttrToNode(pNode_logfont, "lfUnderline", m_FontProp.Font.lfUnderline);
	AddIntAttrToNode(pNode_logfont, "lfStrikeOut", m_FontProp.Font.lfStrikeOut);
	AddIntAttrToNode(pNode_logfont, "lfCharSet", m_FontProp.Font.lfCharSet);
	AddIntAttrToNode(pNode_logfont, "lfOutPrecision", m_FontProp.Font.lfOutPrecision);
	AddIntAttrToNode(pNode_logfont, "lfClipPrecision", m_FontProp.Font.lfClipPrecision);
	AddIntAttrToNode(pNode_logfont, "lfQuality", m_FontProp.Font.lfQuality);
	AddIntAttrToNode(pNode_logfont, "lfPitchAndFamily", m_FontProp.Font.lfPitchAndFamily);

	CUiXmlWriteNode* pNode_mode = XmlStrObj.CreateNode(pPropNode, "mode");
	if (pNode_mode == NULL)
		return false;

	AddIntAttrToNode(pNode_mode, "color", m_FontProp.FontColor);
	AddIntAttrToNode(pNode_mode, "VAligning", m_FontProp.VAligning);
	AddIntAttrToNode(pNode_mode, "HAligning", m_FontProp.HAligning);
	AddIntAttrToNode(pNode_mode, "ShowMode", m_FontProp.ShowMode);
	AddIntAttrToNode(pNode_mode, "Effect", m_FontProp.FontEffect);

	return true;
}

// �Ƿ���ָ����Ч
bool IPropertyFontBase::GetEffectState(FONT_EFFECT FontEffect)
{
	UINT nSet = (m_FontProp.FontEffect & FontEffect);
	return (nSet != 0);
}

void IPropertyFontBase::SetEffect(FONT_EFFECT FontEffect, bool bSet)
{
	if (bSet)
		m_FontProp.FontEffect |= FontEffect;
	else
		m_FontProp.FontEffect &= (~FontEffect);
}

// ��������
bool IPropertyFontBase::DrawFontText(CDrawingBoard &DstDc, char *pszOutText, RECT DstRct)
{
	return DrawToBoard(DstDc, pszOutText, DstRct);
}

// ���Ƶ�ָ���ڴ�DC��
bool IPropertyFontBase::DrawToBoard(CDrawingBoard &DstDc, char *pszOutText, RECT DstRct)
{
	USES_CONVERSION;
	if (pszOutText == NULL || strlen(pszOutText) <= 0 || IS_RECT_EMPTY(DstRct) || DstDc.GetSafeHdc() == NULL)
		return false;

	Graphics DoGrap(DstDc.GetSafeHdc());

	// ����
	Gdiplus::Font TextFont(DstDc.GetSafeHdc(), &(m_FontProp.Font));
	// ������ɫ
	SolidBrush textBrush(Color(MAX_ALPHA, GetRValue(m_FontProp.FontColor), GetGValue(m_FontProp.FontColor), GetBValue(m_FontProp.FontColor)));

	Gdiplus::StringFormat strFormat;
	// ������� & ����»�������
	strFormat.SetHotkeyPrefix(HotkeyPrefixNone);
	// ������ʾЧ������������ʾ��Χ�ڣ�����µ�һ�����ֻ�������ϰ벿�֣���һ�н����ᱻ��ʾ
	strFormat.SetFormatFlags(StringFormatFlagsLineLimit);

	// ���ô�ֱ����ģʽ
	if (m_FontProp.VAligning == FAL_RIGHT_BOTTOM)
	{
		// ��ֱ����
		strFormat.SetLineAlignment(StringAlignmentFar);
	}
	else if (m_FontProp.VAligning == FAL_MIDDLE)
	{
		// ��ֱ����
		strFormat.SetLineAlignment(StringAlignmentCenter);
	}
	else
	{
		// ��ֱ����
		strFormat.SetLineAlignment(StringAlignmentNear);
	}

	// ����ˮƽ����
	if (m_FontProp.HAligning == FAL_RIGHT_BOTTOM)
	{
		// ˮƽ����
		strFormat.SetAlignment(StringAlignmentFar);
	}
	else if (m_FontProp.HAligning == FAL_MIDDLE)
	{
		// ˮƽ����
		strFormat.SetAlignment(StringAlignmentCenter);
	}
	else
	{
		// ˮƽ����
		strFormat.SetAlignment(StringAlignmentNear);
	}

	// GDI+Ĭ��������ʾ��ĩβ����...
	if (m_FontProp.ShowMode != FSM_MULTI_ROW)
	{
		// ��������ʾ
		strFormat.SetFormatFlags(StringFormatFlagsNoWrap);
		// ��������ʾ��Ĭ��ĩβ����...
		if (m_FontProp.ShowMode == FSM_ONE_ROW_POINT)
		{
			// ������ʾ��������ʾ��Χ��ʾ...
			strFormat.SetTrimming(StringTrimmingEllipsisCharacter);
		}
	}

	if (GetEffectState(FE_SHADOW))
	{
		// ��Ӱ����
	}

	if (GetEffectState(FE_OBSCURE))
	{
		// ģ������
	}

	RectF OutFct;
	OutFct.X = DstRct.left;
	OutFct.Y = DstRct.top;
	OutFct.Width = RECT_WIDTH(DstRct);
	OutFct.Height = RECT_HEIGHT(DstRct);
	int nLen = strlen(pszOutText);
	DoGrap.DrawString(A2W(pszOutText), nLen, &TextFont, OutFct, &strFormat, &textBrush);
	return true;
}
