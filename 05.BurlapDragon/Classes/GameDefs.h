

#ifndef __GAME_DEFS_H__
#define __GAME_DEFS_H__

#ifndef IS_SAFE_HANDLE
#define IS_SAFE_HANDLE(hWnd)						(((hWnd)!=NULL)&&((hWnd)!=INVALID_HANDLE_VALUE))
#endif

#ifndef IS_INVALID_HANDLE
#define IS_INVALID_HANDLE(hWnd)						(((hWnd)==NULL)||((hWnd)==INVALID_HANDLE_VALUE))
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(pMem)							{if((pMem)!=NULL){delete((pMem));(pMem)=NULL;}};
#endif

#ifndef SAFE_DELETE_LIST
#define SAFE_DELETE_LIST(pMem)						{if((pMem)!= NULL) {delete[]((pMem));(pMem)=NULL;}};
#endif

// 初始化点
#define INIT_POINT(pt)								((pt).x=(pt).y=0)
// 得到矩形宽度
#define RECT_WIDTH(GetRct)							((GetRct).right-(GetRct).left)
// 得到矩形宽度
#define RECT_HEIGHT(GetRct)							((GetRct).bottom-(GetRct).top)
// 初始化矩形为空
#define INIT_RECT(SetEmRect)						((SetEmRect).left=(SetEmRect).right=(SetEmRect).top=(SetEmRect).bottom=0)
// 设置矩形
#define SET_RECT(SetRct,nL,nT,nR,nB)				((SetRct).left=(nL),(SetRct).top=(nT),(SetRct).right=(nR),(SetRct).bottom=(nB))
#define SET_RECT_WH(SetRct,nL,nT,nWidth,nHeight)	((SetRct).left=(nL),(SetRct).top=(nT),(SetRct).right=(nL)+(nWidth),(SetRct).bottom=(nT)+(nHeight))
// 判断矩形是否不为空
#define IS_RECT_NOT_EMPTY(CheckRect)				((RECT_WIDTH(CheckRect)>0)&&((RECT_HEIGHT(CheckRect)>0)))
// 判断矩形是否为空
#define IS_RECT_EMPTY(CheckRect)					((RECT_WIDTH(CheckRect)<=0)||(RECT_HEIGHT(CheckRect)<=0))

#endif // __GAME_DEFS_H__