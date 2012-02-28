// һ���ؼ�����ʵ�ֵ����нӿڣ�����ӿ��������ؼ�����ʵ�ֵģ�
// �Ǵ���ӿڰ��ո����ؼ�������Լ̳�ʵ��

#pragma once
#include "IControlBase.h"
#include "IWindowBase.h"

class ICtrlInterface : public IControlBase
{
public:
	ICtrlInterface();
	virtual ~ICtrlInterface();

protected:
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bNeedSetDftProp��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bNeedSetDftProp) = 0;
	// ��ʼ���ؼ�
	virtual void OnCreate() = 0;
	// ����Ƥ������ʼ�����
	virtual void OnFinalCreate() = 0;
	// ���ٿؼ�
	virtual void OnDestroy() = 0;
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard) = 0;
	// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
	virtual void OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam);
	// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
	virtual void OnBuilderRefreshProp();
	// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
	// �˺����ɶ�ʱ��������ÿ100���봥��һ��
	virtual bool OnDrawAnimation();
	// ��ʱ��
	virtual void OnTimer(UINT nTimerId);
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
