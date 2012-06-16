
#pragma once
#include "..\..\Inc\Control\ICtrlTabBar.h"
#include "..\..\Inc\Control\ICtrlButton.h"
#include "..\..\Inc\IPropertyInt.h"


typedef vector<ICtrlButton*>	BUTTON_VEC;

class ICtrlTabBarImpl : public ICtrlTabBar, public IControlMessage
{
public:
	ICtrlTabBarImpl();
	virtual ~ICtrlTabBarImpl();

	// ���õ�ǰѡ����
	virtual void SetCheck(int nBtnNum);
	// ȡ��ָ����ľ���λ�ã��������������
	virtual RECT GetButtonWindowRect(int nBtnNum);

protected:
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);
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
	// �ƶ������ÿؼ�λ��
	virtual void OnSize();
	// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
	virtual void OnCreateSubControl(bool bIsCreate);
	// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
	virtual void OnBuilderRefreshProp(IPropertyBase* pPropBase);
	// ����ӿڻ��������Ի����ʼ����ɵ�ʱ�����
	// �ؼ�ͨ����������ӿڣ�����������ӿں�����ͨ�������ؼ�������ȡ�õ�ǰ�Ի�����������ؼ���
	virtual void OnWindowFinalCreate();

private:
	IPropertyInt* m_pPropTabButtonCtns;
	BUTTON_VEC m_ButtonVec;
};
