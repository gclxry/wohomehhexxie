#ifndef  IEFFECT_H
#define  IEFFECT_H

#ifndef _WINDEF_
#include <WinDef.h>
#endif

// ��������
struct AnimationParam
{
	// ����ID
	WPARAM				effectKey;			
	// ����ͼƬ��Դ
	HBITMAP				hBitmap;
	// ����ͼƬDC
	HDC					hdc;
	// ����ͼƬ�ߴ�
	SIZE				bmpSize;
	// ����ͼƬ�ڴ��ַ
	BYTE*				pBmpData;
	// ��������
	DWORD				animationEffect;
	// ����֡ʱ��
	DWORD				animationFrequency;
	// ����˳��
	BOOL				bShow;
};

class IUIEffectCallBack
{
public:
	// ÿһ �� ������ʼʱ�ص�
	virtual void OnUiEffectBegin(WPARAM effectKey, DWORD animaType) = 0;
	// ÿһ �� ��������ʱ�ص�
	virtual void OnUiEffectEnd(WPARAM effectKey, DWORD animaType) = 0;
	// ÿһ ֡ ��������ʱ�ص�
	virtual void OnUiEffectDraw() = 0;
};


class IUIEffect
{
public:
	// ����һ������
	virtual BOOL AppendAnimation(AnimationParam &aParam) = 0;
	// ɾ��һ������
	virtual BOOL DependAnimation(WPARAM effectKey) = 0;
	// ɾ�����ж���
	virtual BOOL ClearAllAnimation() = 0;
	// ִ�����ж���
	virtual BOOL Animation(IUIEffectCallBack *iDrawEffect,DWORD frameSpin) = 0;

};

	
	// ��������
	// ��ö�����ʵ��
	IUIEffect* GetAnimation(void);
	// ɾ��GetAnimation������õĶ�����ʵ��
	BOOL ReleaseAnimation(IUIEffect* &pUIEffect);
	// �����֧�ֵĶ������ͣ�\0Ϊ�ָ�����������������
	// �ַ����е�˳����Ƕ������������ֵ��1...N��
	DWORD GetSurportAnimationType(const char* &strType);

	typedef IUIEffect* (*GETANIMATION)();
	typedef BOOL (*RELEASEANIMATION)(IUIEffect* &);
	typedef DWORD (*GETSURPORTANIMATIONTYPE)(const char* &);

#endif