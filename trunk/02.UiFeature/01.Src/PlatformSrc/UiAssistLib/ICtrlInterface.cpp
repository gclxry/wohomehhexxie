// һ���ؼ�����ʵ�ֵ����нӿ�

#include "stdafx.h"
#include "..\..\Inc\ICtrlInterface.h"

ICtrlInterface::ICtrlInterface()
{
}

ICtrlInterface::~ICtrlInterface()
{
}

// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
void ICtrlInterface::OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam)
{
}

// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
void ICtrlInterface::OnBuilderRefreshProp()
{
}

// ������
void ICtrlInterface::OnMouseEnter(POINT pt)
{
}

// ����Ƴ�
void ICtrlInterface::OnMouseLeave()
{
}

// ����ƶ�
void ICtrlInterface::OnMouseMove(POINT pt)
{
}

// ���������
void ICtrlInterface::OnLButtonDown(POINT pt)
{
}

// ������̧��
void ICtrlInterface::OnLButtonUp(POINT pt)
{
}

// ������˫��
void ICtrlInterface::OnLButtonDbClick(POINT pt)
{
}

// ����ڿؼ��ڲ�������²��ƶ����
void ICtrlInterface::OnMouseDragInCtrl(POINT pt)
{
}

// ����Ҽ����
void ICtrlInterface::OnRButtonDown(POINT pt)
{
}

// �ƶ������ÿؼ�λ��
void ICtrlInterface::OnSize()
{
}

// �ƶ����ڿ�ʼ
void ICtrlInterface::OnEnterSizeMove()
{
}

// �ƶ����ڽ���
void ICtrlInterface::OnExitSizeMove()
{
}

// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
void ICtrlInterface::OnSetFocus()
{
}

// �ؼ�ʧȥ����
void ICtrlInterface::OnKillFocus()
{
}

// �ؼ�ȡ�ü���������Ϣ
void ICtrlInterface::OnChar(WPARAM wParam, LPARAM lParam)
{
}

// �ؼ�ȡ�ü���������Ϣ
void ICtrlInterface::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
}

// �ؼ�ȡ�ü���������Ϣ
void ICtrlInterface::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
}

// ���ܵ�Ĭ�ϻس�����ִ�пؼ�����
void ICtrlInterface::OnDefaultEnterCtrl()
{
}

// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
// �˺����ɶ�ʱ��������ÿ100���봥��һ��
bool ICtrlInterface::OnDrawAnimation()
{
	return false;
}
// ��ʱ��
void ICtrlInterface::OnTimer(UINT nTimerId)
{
}