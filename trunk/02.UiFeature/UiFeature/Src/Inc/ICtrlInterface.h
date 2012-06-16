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
	// bIsNewCtrl��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bIsNewCtrl) = 0;
	// �ؼ���ʼ��������
	virtual void OnCreate() = 0;
	// �ؼ���ʼ�����
	virtual void OnFinalCreate() = 0;
	// ���ٿؼ�
	virtual void OnDestroy() = 0;
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard) = 0;
	// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
	virtual void OnCreateSubControl(bool bIsCreate);
	// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
	virtual void OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam);
	// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
	virtual void OnBuilderRefreshProp(IPropertyBase* pPropBase);
	// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
	// �˺����ɶ�ʱ��������ÿ100���봥��һ��
	virtual bool OnDrawAnimation();
	// ��ʱ��
	virtual void OnTimer(UINT nTimerId);
	// ������
	virtual void OnMouseEnter(POINT pt);
	// ����Ƴ�
	virtual void OnMouseLeave(POINT pt);
	// ����ƶ�
	virtual void OnMouseMove(POINT pt);
	// ���������
	virtual void OnLButtonDown(POINT pt);
	// ������̧��
	virtual void OnLButtonUp(POINT pt);
	// ������˫��
	virtual void OnLButtonDbClick(POINT pt);
	// ����ڿؼ��ڲ��϶��ؼ��������Ϣ�����Դ���ؼ��ڲ���ק�Ķ�����Ҳ���Դ���ͬ�ؼ�֮����קʵ�����ݴ���
	virtual void OnMouseDragging(POINT pt);
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
	// ��������Ϣ
	virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam);
	// ���ܵ�Ĭ�ϻس�����ִ�пؼ�����
	virtual void OnDefaultEnterCtrl();
	// �ؼ�ȡ�ü���������Ϣ
	virtual void OnChar(WPARAM wParam, LPARAM lParam);
	// ��������
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual void OnKeyUp(WPARAM wParam, LPARAM lParam);
	// ��������Ϣ
	virtual void OnVScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar);
	// ����Ƿ������˿ؼ�ָ����RGN����Ĭ�Ϸ���true�������ؼ�����RGN����
	virtual bool OnCheckMouseInRgn(POINT pt);
	// ����ӿڻ��������Ի����ʼ����ɵ�ʱ�����
	// �ؼ�ͨ����������ӿڣ�����������ӿں�����ͨ�������ؼ�������ȡ�õ�ǰ�Ի�����������ؼ���
	virtual void OnWindowFinalCreate();
	// �����Ի��򼴽��ر�
	virtual void OnWindowClose();
	// ���ÿؼ����
	virtual IPropertyCursor* OnSetCursor(POINT pt);
	// �յ���Ҫ��ջ��ƻ������Ϣ
	virtual void OnClearDrawMemoryDc();

//////////////////////////////////////////////////////////////////////////
	// �û��Զ���ǿ������ʼ
	virtual void OnUserDefHighAnimationBegin();
	// �û��Զ���ǿ�������ƽӿڣ�hWndDc���ؼ����ڵĴ���DC
	virtual void OnUserDefHighAnimationDraw(HDC hWndDc);
	// �û��Զ���ǿ��������
	virtual void OnUserDefHighAnimationEnd();
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
	// �ؼ�֮����ק��ʵ�����ݴ��䣬һ���ؼ� OnMouseDragging �����󣬻������̧��ʱ�����Ŀؼ����� OnDragStop ��Ϣ��
	// ������ OnMouseDragging �Ŀؼ��ֻ��յ� OnGetDragParam ��Ϣ��Ҫ��ȡ����ק�Ĳ�����

	// ����϶�����������̧����ꡣ
	// pDragCtrl����ק��Դ�ؼ�����קԴ�ؼ������޷��յ�����Ϣ��ֻ��ͨ�� OnLButtonUp ��Ϣ������
	virtual void OnDragStop(IControlBase* pDragCtrl, POINT pt, WPARAM wParam, LPARAM lParam);
	// ȡ�ÿؼ�֮����ק�����ݲ������ڴ����� OnDragStop ��Ϣǰ�ᱻ����
	// WPARAM& wParam, LPARAM& lParam ���������ز���
	virtual void OnGetDragParam(WPARAM& wParam, LPARAM& lParam);
//////////////////////////////////////////////////////////////////////////
};
