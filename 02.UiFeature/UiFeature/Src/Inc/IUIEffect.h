#ifndef  IEFFECT_H
#define  IEFFECT_H

#ifndef _WINDEF_
#include <WinDef.h>
#endif

// 动画参数
struct AnimationParam
{
	// 动画ID
	WPARAM				effectKey;			
	// 动画图片资源
	HBITMAP				hBitmap;
	// 动画图片DC
	HDC					hdc;
	// 动画图片尺寸
	SIZE				bmpSize;
	// 动画图片内存地址
	BYTE*				pBmpData;
	// 动画种类
	DWORD				animationEffect;
	// 动画帧时间
	DWORD				animationFrequency;
	// 动画顺序
	BOOL				bShow;
};

class IUIEffectCallBack
{
public:
	// 每一 个 动画开始时回调
	virtual void OnUiEffectBegin(WPARAM effectKey, DWORD animaType) = 0;
	// 每一 个 动画结束时回调
	virtual void OnUiEffectEnd(WPARAM effectKey, DWORD animaType) = 0;
	// 每一 帧 动画绘制时回调
	virtual void OnUiEffectDraw() = 0;
};


class IUIEffect
{
public:
	// 加入一个动画
	virtual BOOL AppendAnimation(AnimationParam &aParam) = 0;
	// 删除一个动画
	virtual BOOL DependAnimation(WPARAM effectKey) = 0;
	// 删除所有动画
	virtual BOOL ClearAllAnimation() = 0;
	// 执行所有动画
	virtual BOOL Animation(IUIEffectCallBack *iDrawEffect,DWORD frameSpin) = 0;

};

	
	// 导出函数
	// 获得动画类实例
	IUIEffect* GetAnimation(void);
	// 删除GetAnimation函数获得的动画类实例
	BOOL ReleaseAnimation(IUIEffect* &pUIEffect);
	// 获得所支持的动画类型（\0为分隔符），动画名称在
	// 字符串中的顺序就是动画种类的输入值（1...N）
	DWORD GetSurportAnimationType(const char* &strType);

	typedef IUIEffect* (*GETANIMATION)();
	typedef BOOL (*RELEASEANIMATION)(IUIEffect* &);
	typedef DWORD (*GETSURPORTANIMATIONTYPE)(const char* &);

#endif