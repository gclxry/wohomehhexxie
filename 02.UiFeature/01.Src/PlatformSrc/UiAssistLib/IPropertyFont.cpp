
#include "stdafx.h"
#include "..\..\Inc\IPropertyFont.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyFont::IPropertyFont()
{
	m_FontProp.strName = "";
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
	strcpy_s(m_FontProp.Font.lfFaceName, 32, "ËÎÌå");

	m_FontProp.HAligning = FAL_LEFT_TOP;
	m_FontProp.VAligning = FAL_MIDDLE;
	m_FontProp.ShowMode = FSM_ONE_ROW_NO_POINT;
}

IPropertyFont::~IPropertyFont()
{

}

bool IPropertyFont::IsRightData()
{
	return true;
}

FONT_PROP* IPropertyFont::GetFontProp()
{
	return &m_FontProp;
}

void IPropertyFont::SetFontProp(FONT_PROP *pFontProp)
{
	if (pFontProp == NULL)
		return;

	m_FontProp = *pFontProp;
}

// É¾³ý×ÔÉí
PROP_TYPE IPropertyFont::GetPropType()
{
	return PT_FONT;
}

bool IPropertyFont::ReadResourceXmlProperty(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	char* psz_name = JabberXmlGetAttrValue(pXmlNode, SKIN_PROP_NAME);
	if (psz_name == NULL)
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

	if (psz_lfPitchAndFamily == NULL || psz_color == NULL || psz_lfFaceName == NULL || psz_lfHeight == NULL || psz_lfWidth == NULL || 
		psz_lfEscapement == NULL || psz_lfOrientation == NULL || psz_lfWeight == NULL || psz_lfItalic == NULL || psz_lfUnderline == NULL || 
		psz_lfStrikeOut == NULL || psz_lfCharSet == NULL || psz_lfOutPrecision == NULL || psz_lfClipPrecision == NULL || psz_lfQuality == NULL ||
		psz_VAligning == NULL || psz_HAligning == NULL || psz_ShowMode == NULL)
		return false;

	m_FontProp.strName = psz_name;

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

	return true;
}
