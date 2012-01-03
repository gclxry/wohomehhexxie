// һ���ؼ�����ʵ�ֵ����нӿڣ�����ӿ��������ؼ�����ʵ�ֵģ�
// �Ǵ���ӿڰ��ո����ؼ�������Լ̳�ʵ��

#pragma once
#include "IControlBase.h"

class ICtrlInterface : public IControlBase
{
public:
	ICtrlInterface();
	virtual ~ICtrlInterface();

protected:
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	virtual bool CreateControlPropetry() = 0;
	// ��ʼ���ؼ�
	virtual void OnCreate() = 0;
	// ����Ƥ������ʼ�����
	virtual void OnFinalCreate() = 0;
	// ���ٿؼ�
	virtual void OnDestroy() = 0;
	// ���ƿؼ�
	virtual void OnPaint() = 0;
	// �����ؼ������������Ϣ
	virtual void OnCtrlMessage(int nMsgId, WPARAM wParam, LPARAM lParam);
	// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
	virtual void OnBuilderRefreshProp();
	// ������
	virtual void OnMouseEnter(POINT pt);
	// ����Ƴ�
	virtual void OnMouseLeave();
	// ����ƶ�
	virtual void OnMouseMove(POINT pt);
	// ���������
	virtual void OnLButtonDown(POINT pt);
	// ������̧��
	virtual void OnLButtonUp(POINT pt);
	// ������˫��
	virtual void OnLButtonDbClick(POINT pt);
	// ����ڿؼ��ڲ�������²��ƶ����
	virtual void OnMouseDragInCtrl(POINT pt);
	// ����Ҽ����
	virtual void OnRButtonDown(POINT pt);
	// �ƶ������ÿؼ�λ��
	virtual void OnSize();
	// �ƶ����ڿ�ʼ
	virtual void OnEnterSizeMove();
	// �ƶ����ڽ���
	virtual void OnExitSizeMove();
	// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
	virtual void OnSetFocus();
	// �ؼ�ʧȥ����
	virtual void OnKillFocus();
	// ���ܵ�Ĭ�ϻس�����ִ�пؼ�����
	virtual void OnDefaultEnterCtrl();
	// �ؼ�ȡ�ü���������Ϣ
	virtual void OnChar(WPARAM wParam, LPARAM lParam);
	// ��������
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual void OnKeyUp(WPARAM wParam, LPARAM lParam);
};
