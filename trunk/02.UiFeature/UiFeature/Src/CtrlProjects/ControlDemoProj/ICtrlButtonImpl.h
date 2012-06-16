
#pragma once
#include "..\..\Inc\Control\ICtrlButton.h"
#include "..\..\Inc\IControlBase.h"

enum BUTTON_TYPE
{
	// ��ͨ��ť
	BT_NORMAL_BUTTON = 0,
	// rgn ��ť
	BT_RGN_BUTTON,
	// tab�ð�ť
	BT_CHECK_BUTTON
};

class ICtrlButtonImpl : public ICtrlButton
{
public:
	ICtrlButtonImpl();
	virtual ~ICtrlButtonImpl();

	//����Button����
	virtual	void SetButtonText(const char* pszText);
	//��ȡButton����
	virtual	const char* GetButtonText();

	// check button ģʽ��
	virtual void SetCheck(bool bIsCheck, bool bRedraw);
	virtual bool IsCheck();

	virtual IControlBase* GetCheckPanel();

protected:
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bIsNewCtrl��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bIsNewCtrl);
	// ��ʼ���ؼ�
	virtual void OnCreate();
	// �ؼ���ʼ�����
	virtual void OnFinalCreate();
	// ���ٿؼ�
	virtual void OnDestroy();
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard);
	// ������
	virtual void OnMouseEnter(POINT pt);
	// ����Ƴ�
	virtual void OnMouseLeave(POINT pt);
	// ���������
	virtual void OnLButtonDown(POINT pt);
	// ������˫��
	virtual void OnLButtonDbClick(POINT pt);
	// ������̧��
	virtual void OnLButtonUp(POINT pt);
	// ����Ҽ����
	virtual void OnRButtonDown(POINT pt);
	// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
	virtual void OnSetFocus();
	// �ؼ�ʧȥ����
	virtual void OnKillFocus();
	// ����Ƿ������˿ؼ�ָ����RGN����Ĭ�Ϸ���true�������ؼ�����RGN����
	virtual bool OnCheckMouseInRgn(POINT pt);
	// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
	virtual void OnBuilderRefreshProp(IPropertyBase* pPropBase);
	// ����ӿڻ��������Ի����ʼ����ɵ�ʱ�����
	// �ؼ�ͨ����������ӿڣ�����������ӿں�����ͨ�������ؼ�������ȡ�õ�ǰ�Ի�����������ؼ���
	virtual void OnWindowFinalCreate();

private:
	// ���ݸ���ͼƬ����RGN
	bool SetRgn();

private:
	typedef enum enumBtnState
	{
		BtnStateInvalid = -1,
		BtnStateNormal,
		BtnStateHover,
		BtnStateDown,
		BtnStateFocus,
		BtnStateDisable,
		//�ڴ�֮ǰ����Button��״̬
		BtnStateNum
	}BTNSTATE;

private:
	void ChangeButtonStyle(BTNSTATE state);

private:
	// check button ģʽ�£���¼�Ƿ�check��
	bool				m_bIsCheck;
	IPropertyComboBox*	m_pPropButtonTypeCombo;

	IPropertyImage*		m_pPropImages[BtnStateNum];
	IPropertyFont*		m_pPropFonts[BtnStateNum];
	IPropertyString*	m_pPropText; 

	IPropertyGroup*		m_pPropRgnGroup;
	IPropertyImage*		m_pPropRgnMaskImage;
	HRGN				m_hRgn;

	IPropertyGroup*		m_pPropCheckBtnGroup;
	IPropertyString*	m_pPropShowPanelName;

	BTNSTATE			m_enumBtnState;
	ULONG				m_mouseFlag;

	IControlBase*		m_pCheckPanel;
};
