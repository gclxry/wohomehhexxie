//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// ������ʾ��ʽ
enum FONT_SHOW_MODE
{
	// ������ʾ��������ʾ��Χĩβ����ʾ...
	FSM_ONE_ROW_NO_POINT	= 1,
	// ������ʾ��������ʾ��Χ��ʾ...
	FSM_ONE_ROW_POINT		= 2,
	// ������ʾ
	FSM_MULTI_ROW			= 3
};

// ����ģʽ
enum FONT_ALIGNING
{
	// ˮƽ����/��ֱ����
	FAL_LEFT_TOP		= 1,
	// ˮƽ����/��ֱ����
	FAL_RIGHT_BOTTOM	= 2,
	// ˮƽ����/��ֱ����
	FAL_MIDDLE		= 3
};

// ��������
struct FONT_PROP
{
	// ��������
	string strName;
	string strPropInfo;
	// ������Ϣ
	LOGFONTA Font;
	// ������ɫ
	COLORREF FontColor;
	// ��ֱͣ����Ϣ
	FONT_ALIGNING VAligning;
	// ˮƽͣ����Ϣ
	FONT_ALIGNING HAligning;
	// ��ʾ��ʽ
	FONT_SHOW_MODE ShowMode;
};

class IPropertyFont : public IPropertyBase
{
public:
	IPropertyFont();
	virtual ~IPropertyFont();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ȡ����������
	virtual PROP_TYPE GetPropType();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

	// ����������Ϣ
	void SetFontProp(FONT_PROP *pFontProp);
	FONT_PROP* GetFontProp();

private:
	FONT_PROP m_FontProp;
};
