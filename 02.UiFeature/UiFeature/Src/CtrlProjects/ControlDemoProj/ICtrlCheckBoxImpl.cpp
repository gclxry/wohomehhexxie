
#include "StdAfx.h"
#include "ICtrlCheckBoxImpl.h"
#include "..\..\Inc\IControlManager.h"

ICtrlCheckBoxImpl::ICtrlCheckBoxImpl(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_CHECK_BOX);

}

ICtrlCheckBoxImpl::~ICtrlCheckBoxImpl(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlCheckBoxImpl::CreateControlPropetry(bool bNeedSetDftProp)
{
	return true;
}

// ��ʼ���ؼ�
void ICtrlCheckBoxImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlCheckBoxImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlCheckBoxImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlCheckBoxImpl::OnPaint(CDrawingBoard &DrawBoard)
{
}
