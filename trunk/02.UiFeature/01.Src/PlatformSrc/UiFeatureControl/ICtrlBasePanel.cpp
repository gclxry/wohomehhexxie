
#include "StdAfx.h"
#include "..\..\Inc\ICtrlBasePanel.h"
#include "..\..\Inc\IControlManager.h"

ICtrlBasePanel::ICtrlBasePanel(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_BASE_PANEL);
}

ICtrlBasePanel::~ICtrlBasePanel(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlBasePanel::CreateControlPropetry()
{
	return true;
}

// ��ʼ���ؼ�
void ICtrlBasePanel::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlBasePanel::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlBasePanel::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlBasePanel::OnPaint()
{

}
