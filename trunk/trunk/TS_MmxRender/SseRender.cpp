
#include "StdAfx.h"
#include "SseRender.h"

CSseRender::CSseRender(void)
{
	m_bIsSupportSse = m_CpuSupport.IsSSE();
}

CSseRender::~CSseRender(void)
{
}

// sse2 32位带透明值色块画刷
void CSseRender::ARGB32_SolidBrush(DWORD *pDstBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
{
	if (pDstBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0 || BrushRect.IsRectEmpty() || byA == 0)
		return;

	if (byA == 255)
	{
	}
	else
	{
		DWORD dwOvrColor[2] = { BGRA_MARK(byB,byG,byR,byA), BGRA_MARK(byB,byG,byR,50) };
		DWORD *pDwOvrColor = dwOvrColor;

		int nLoops = (BmpSize.cx * BmpSize.cy) / 2;
		__asm
		{
			pxor		xmm2, xmm2	// 把MM2清0
			mov			edx, pDstBmpData	// 取32bit像素地址到edx
			mov			eax, pDwOvrColor
			mov			ecx, nLoops
			dec			ecx

LOOP_S:
			movq		mm0, qword ptr [edx]	// 取2个像素值放入mm0，目标像素点
			movq		mm1, qword ptr [eax]	// 取2个像素值放入mm1，覆盖像素点

			movq2dq		xmm0, mm0	// 把2个像素值放入xmm0低64bit
			movq2dq		xmm1, mm1

			punpcklbw	xmm0, xmm2	// 扩展64位数据到128位，以64位为一个像素，以容纳计算结果
			punpcklbw	xmm1, xmm2

//			movdq2q		mm4, xmm0	// TTT 测试显示值
//			movdq2q		mm5, xmm1	// TTT 测试显示值

			movdqu		xmm3, xmm1	// 为了取得覆盖像素点的alpha值
			punpckhwd	xmm3, xmm3	// 高字移动到双字
			punpckhwd	xmm3, xmm3	// 高字移动到四字
			punpckhwd	xmm3, xmm3	// 双字移动到八字，可以分别计算每个颜色值的alpha的混合啦

//			movdq2q		mm4, xmm3	// TTT 测试显示值

			movdqu		xmm4, xmm0
			movdqu		xmm5, xmm1

			psubusw		xmm4, xmm1	// Source-Overlay,饱和减
			psubusw		xmm5, xmm0	// Overlay-Source,饱和减

			pmullw		xmm4, xmm3	// Alpha * (Source-Overlay)
			pmullw		xmm5, xmm3	// Alpha * (Overlay-Source)

			psrlw		xmm4, 8		// 除以256,now mm4 get the result,(Source-Overlay)<0 部分
			psrlw		xmm5, 8		// 除以256,now mm5 get the result,(Overlay-Source)>0 部分

			paddusw		xmm0, xmm5	// 饱和加到原图象D=Alpha*(O-S)+S,(Source-Overlay)<0 部分
			psubusw		xmm0, xmm4	// 饱和加到原图象D=S-Alpha*(S-O),(Overlay-Source)>0 部分
			packuswb	xmm0, xmm0	// 紧缩到低32bit

			movdq2q		mm0, xmm0	// 保存结果
			movq		[edx], mm0
			add			edx, 8

			loop		LOOP_S
			emms
		}

		if ((BmpSize.cx * BmpSize.cy) % 2 > 1)
		{
		}
	}
}

void CSseRender::BlendESS0(unsigned char* src1, unsigned char* src2, unsigned char* dst, unsigned int count)
{
	unsigned short* redMask =  (unsigned short*)_aligned_malloc(16,16);
	unsigned short rm[8] = {0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000};
	memcpy(redMask, rm, 16);

	unsigned short* greenMask =  (unsigned short*)_aligned_malloc(16,16);
	unsigned short gm[8] = {0xff00, 0x0000, 0xff00, 0x0000, 0xff00, 0x0000, 0xff00, 0x0000};
	memcpy(greenMask, gm, 16);

	unsigned short* blueMask =  (unsigned short*)_aligned_malloc(16,16);
	unsigned short bm[8] = {0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff};
	memcpy(blueMask, bm, 16);

	unsigned short* add0x80 =  (unsigned short*)_aligned_malloc(16,16);
	unsigned short a80[16] = {0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080};
	memcpy(add0x80, a80, 16);

	unsigned short* pm0xFF =  (unsigned short*)_aligned_malloc(16,16);
	unsigned short d[8] = {0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff};
	memcpy(pm0xFF, d, 16);

	unsigned short* pmHEven =  (unsigned short*)_aligned_malloc(16,16);
	unsigned short he[8] = {0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0xffff, 0x0000};
	memcpy(pmHEven, he, 16);

	unsigned short* pmLEven =  (unsigned short*)_aligned_malloc(16,16);
	unsigned short le[8] = {0xffff, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};
	memcpy(pmLEven, le, 16);

	unsigned short* pTemp =  (unsigned short*)_aligned_malloc(384,16);
	memset(pTemp, 0, 384);

	int v0xFF = 0xFF;
	int* p0xFF = &v0xFF;

	__asm
	{
		align        16
		pusha
		mov            esi, src1
		mov            edi, src2

		prefetcht0    [esi]
		prefetcht0    [edi]
		pxor        xmm0, xmm0 // = 0
		// =======================================================================================================
		// Load 4 pixels from source1: [(a4s1,b4s1,g4s1,r4s1)(a3s1,b3s1,g3s1,r3s1)(a2s1,b2s1,g2s1,r2s1)(a1s1,b1s1,g1s1,r1s1)]
		movdqu        xmm1, [esi]
		// Load 4 pixels from source2: [(a4s2,b4s2,g4s2,r4s2)(a3s2,b3s2,g3s2,r3s2)(a2s2,b2s2,g2s2,r2s2)(a1s2,b1s2,g1s2,r1s2)]
		movdqu        xmm2, [edi]
		// Load next 4 pixels from source1: [(a8s1,b8s1,g8s1,r8s1)(a7s1,b7s1,g7s1,r7s1)(a6s1,b6s1,g6s1,r6s1)(a5s1,b5s1,g5s1,r5s1)]
		movdqu        xmm3, [esi+16]
		// Load next 4 pixels from source2: [(a8s2,b8s2,g8s2,r8s2)(a7s2,b7s2,g7s2,r7s2)(a6s2,b6s2,g6s2,r6s2)(a5s2,b5s2,g5s2,r5s2)]
		movdqu        xmm4, [edi+16]
		// Isolate alpha values in first 4 pixels of source1: [(00,00,00,a4s1)(00,00,00,a3s1)(00,00,00,a2s1)(00,00,00,a1s1)]
		psrld        xmm1, 24
		// Isolate alpha values in first 4 pixels of source2: [(00,00,00,a4s2)(00,00,00,a3s2)(00,00,00,a2s2)(00,00,00,a1s2)]
		psrld        xmm2, 24
		// Isolate alpha values in second 4 pixels of source1: [(00,00,00,a8s1)(00,00,00,a7s1)(00,00,00,a6s1)(00,00,00,a5s1)]
		psrld        xmm3, 24
		// Isolate alpha values in second 4 pixels of source2: [(00,00,00,a8s2)(00,00,00,a7s2)(00,00,00,a6s2)(00,00,00,a5s2)]
		psrld        xmm4, 24
		// Pack alpha values in first 4 pixels of source1 into lo qword: [(00,00,00,00,00,00,00,00)(00,a4s1,00,a3s1,00,a2s1,00,a1s1)]
		packssdw    xmm1, xmm0
		// Pack alpha values in first 4 pixels of source2 into lo qword: [(00,00,00,00,00,00,00,00)(00,a4s2,00,a3s2,00,a2s2,00,a1s2)]
		packssdw    xmm2, xmm0
		// Pack alpha values in second 4 pixels of source1 into lo qword: [(00,00,00,00,00,00,00,00)(00,a8s1,00,a7s1,00,a6s1,00,a5s1)]
		packssdw    xmm3, xmm0
		// Pack alpha values in second 4 pixels of source2 into lo qword: [(00,00,00,00,00,00,00,00)(00,a8s2,00,a7s2,00,a6s2,00,a5s2)]
		packssdw    xmm4, xmm0
		// Combine all 8 alpha values of source1 in order: [(00,a8s1,00,a7s1,00,a6s1,00,a5s1)(00,a4s1,00,a3s1,00,a2s1,00,a1s1)]
		pshufd        xmm0, xmm3, 0x40
		movsd         xmm0, xmm1
		movdqa        xmm1, xmm0
		// Combine all 8 alpha values of source2 in order: [(00,a8s2,00,a7s2,00,a6s2,00,a5s2)(00,a4s2,00,a3s2,00,a2s2,00,a1s2)]
		pshufd        xmm0, xmm4, 0x40
		movsd         xmm0, xmm2
		movdqa        xmm2, xmm0
		// Make copy of 8 alpha values of source1
		movdqa        xmm3, xmm1
		// Make copy of 8 alpha values of source2
		movdqa        xmm4, xmm2
		// xN=aNs1+aNs2
		movdqa        xmm5, xmm3
		paddq        xmm5, xmm4
		// yN=(aNs1*aNs2)/255
		movdqa        xmm6, xmm3
		pmullw        xmm6, xmm4
		mov            eax, add0x80
		paddw        xmm6, [eax]
		movdqa        xmm7, xmm6
		psrlw        xmm6, 8
		paddw        xmm6, xmm7
		psrlw        xmm6, 8
		// aNf=xN-yN
		psubw        xmm5, xmm6
		movdqa        xmm6, xmm5
		// zN=aNs1*255
		mov            eax, pm0xFF
		pmullw        xmm3, [eax]
		// aNp1=zN/aNf
		pxor        xmm0, xmm0
		// Find any zero values
		pcmpeqw        xmm6, xmm0
		// And make them non-zero
		por            xmm5, xmm6
		// Duplicate zN and aNf
		movdqa        xmm6, xmm3 // zN
		movdqa        xmm7, xmm5 // aNf
		movdqa        xmm4, xmm5 // aNf
		// zN/aNf (lo qwordq)
		punpcklwd    xmm5, xmm0
		punpcklwd    xmm3, xmm0
		divps        xmm3, xmm5
		cvtps2dq    xmm3, xmm3
		// zN/aNf (hi qword)
		punpckhwd    xmm6, xmm0
		punpckhwd    xmm7, xmm0
		divps        xmm6, xmm7
		cvtps2dq    xmm6, xmm6
		// Combine hi and lo qwords into one
		packuswb    xmm3, xmm0
		packuswb    xmm6, xmm0
		movlhps        xmm3, xmm6 // aNp1
		// aNp2=255-aNp1
		mov            eax, pm0xFF
		movdqa        xmm0, [eax]
		psubd        xmm0, xmm3 // aNp2
		//--------        
		// xmm3=aNp1
		// xmm4=aNp2
		// xmm7=aNf
		//--------
		// Save aNp1, aNp2, aNf into memory to free some registers
		mov            ebx, pTemp
		movdqa        [ebx], xmm3
		movdqa        [ebx+128], xmm0
		movdqa        [ebx+256], xmm4
		// Load 4 pixels from source1: [(a4s1,b4s1,g4s1,r4s1)(a3s1,b3s1,g3s1,r3s1)(a2s1,b2s1,g2s1,r2s1)(a1s1,b1s1,g1s1,r1s1)]
		movdqu        xmm1, [esi]
		// Load 4 pixels from source2: [(a4s2,b4s2,g4s2,r4s2)(a3s2,b3s2,g3s2,r3s2)(a2s2,b2s2,g2s2,r2s2)(a1s2,b1s2,g1s2,r1s2)]
		movdqu        xmm2, [edi]
		// Load next 4 pixels from source1: [(a8s1,b8s1,g8s1,r8s1)(a7s1,b7s1,g7s1,r7s1)(a6s1,b6s1,g6s1,r6s1)(a5s1,b5s1,g5s1,r5s1)]
		movdqu        xmm3, [esi+16]
		// Load next 4 pixels from source2: [(a8s2,b8s2,g8s2,r8s2)(a7s2,b7s2,g7s2,r7s2)(a6s2,b6s2,g6s2,r6s2)(a5s2,b5s2,g5s2,r5s2)]
		movdqu        xmm4, [edi+16]
		// Mask out red channel
		mov            eax, redMask
		pand        xmm1, [eax]
		pand        xmm3, [eax]
		pand        xmm2, [eax]
		pand        xmm4, [eax]
		// Pack into lo qword
		packssdw    xmm1, xmm0
		packssdw    xmm3, xmm0
		packssdw    xmm2, xmm0
		packssdw    xmm4, xmm0
		// Combine all of source1: [(00,r8s1,00,r7s1,00,r6s1,00,r5s1)(00,r4s1,00,r3s1,00,r2s1,00,r1s1)]
		pshufd        xmm0, xmm3, 0x40
		movsd         xmm0, xmm1
		movdqa        xmm1, xmm0
		pxor        xmm0, xmm0
		// Combine all of source2: [(00,r8s2,00,r7s2,00,r6s2,00,r5s2)(00,r4s2,00,r3s2,00,r2s2,00,r1s2)]
		pshufd        xmm0, xmm4, 0x40
		movsd         xmm0, xmm2
		movdqa        xmm2, xmm0
		// rN1=rNs1*aNp1
		pmullw        xmm1, [ebx]
		// rN2=rNs2*aNp2
		pmullw        xmm2, [ebx+128]
		// rNt=rN1+rN2
		paddw        xmm1, xmm2
		movdqa        xmm5, xmm1
		// rN=rNt/255
		mov            eax, add0x80
		paddw        xmm5, [eax]
		movdqa        xmm7, xmm5
		psrlw        xmm5, 8
		paddw        xmm5, xmm7
		psrlw        xmm5, 8
		// xmm5=rN
		// -----------
		// Green channel
		pxor        xmm0, xmm0
		movdqu        xmm1, [esi]
		movdqu        xmm2, [edi]
		movdqu        xmm3, [esi+16]
		movdqu        xmm4, [edi+16]
		mov            eax, greenMask
		pand        xmm1, [eax]
		pand        xmm3, [eax]
		pand        xmm2, [eax]
		pand        xmm4, [eax]
		psrldq        xmm1, 1
		psrldq        xmm2, 1
		psrldq        xmm3, 1
		psrldq        xmm4, 1
		packssdw    xmm1, xmm0
		packssdw    xmm3, xmm0
		packssdw    xmm2, xmm0
		packssdw    xmm4, xmm0
		pshufd        xmm0, xmm3, 0x40
		movsd         xmm0, xmm1
		movdqa        xmm1, xmm0
		pxor        xmm0, xmm0
		pshufd        xmm0, xmm4, 0x40
		movsd         xmm0, xmm2
		movdqa        xmm2, xmm0
		pmullw        xmm1, [ebx]
		pmullw        xmm2, [ebx+128]
		paddw        xmm1, xmm2
		movdqa        xmm6, xmm1
		mov            eax, add0x80
		paddw        xmm6, [eax]
		movdqa        xmm7, xmm6
		psrlw        xmm6, 8
		paddw        xmm6, xmm7
		psrlw        xmm6, 8
		// xmm6=gN
		// -----------
		// Blue channel
		pxor        xmm0, xmm0
		movdqu        xmm1, [esi]
		movdqu        xmm2, [edi]
		movdqu        xmm3, [esi+16]
		movdqu        xmm4, [edi+16]
		mov            eax, blueMask
		pand        xmm1, [eax]
		pand        xmm3, [eax]
		pand        xmm2, [eax]
		pand        xmm4, [eax]
		psrldq        xmm1, 2
		psrldq        xmm2, 2
		psrldq        xmm3, 2
		psrldq        xmm4, 2
		packssdw    xmm1, xmm0
		packssdw    xmm3, xmm0
		packssdw    xmm2, xmm0
		packssdw    xmm4, xmm0
		pshufd        xmm0, xmm3, 0x40
		movsd         xmm0, xmm1
		movdqa        xmm1, xmm0
		pxor        xmm0, xmm0
		pshufd        xmm0, xmm4, 0x40
		movsd         xmm0, xmm2
		movdqa        xmm2, xmm0
		pmullw        xmm1, [ebx]
		pmullw        xmm2, [ebx+128]
		paddw        xmm1, xmm2
		movdqa        xmm7, xmm1
		mov            eax, add0x80
		paddw        xmm7, [eax]
		movdqa        xmm0, xmm7
		psrlw        xmm7, 8
		paddw        xmm7, xmm0
		psrlw        xmm7, 8
		// xmm7=bN
		movdqa        xmm4, [ebx+256] // aNf
		pxor        xmm0, xmm0
		// Process first 4 result red channel values
		movdqa        xmm1, xmm5
		punpcklwd    xmm1, xmm0
		// Process first 4 result green channel values
		movdqa        xmm2, xmm6
		punpcklwd    xmm2, xmm0
		pslldq        xmm2, 1
		// Process first 4 result blue channel values
		movdqa        xmm3, xmm7
		punpcklwd    xmm3, xmm0
		pslldq        xmm3, 2
		// Put them together
		por            xmm1, xmm2
		por            xmm1, xmm3
		// Process first 4 result alpha channel values
		movdqa        xmm3, xmm4
		punpcklwd    xmm3, xmm0
		pslldq        xmm3, 3
		// Put them into the colors
		por            xmm1, xmm3
		// Now we have xmm1 with first 4 final pixels: [(a4f,b4f,g4f,r4f)(a3f,b3f,g3f,r3f)(a2f,b2f,g2f,r2f)(a1f,b1f,g1f,r1f)]
		// Write them to destination memory
		mov            edx, dst
		movdqa        [edx], xmm1

		// Process second 4 result red channel values
		movdqa        xmm1, xmm5
		punpckhwd    xmm1, xmm0
		// Process second 4 result green channel values
		movdqa        xmm2, xmm6
		punpckhwd    xmm2, xmm0
		pslldq        xmm2, 1
		// Process second 4 result blue channel values
		movdqa        xmm3, xmm7
		punpckhwd    xmm3, xmm0
		pslldq        xmm3, 2
		// Put them together
		por            xmm1, xmm2
		por            xmm1, xmm3
		// Process second 4 result alpha channel values
		movdqa        xmm3, xmm4
		punpckhwd    xmm3, xmm0
		pslldq        xmm3, 3
		// Put them into the colors
		por            xmm1, xmm3
		// Now we have xmm1 with second 4 final pixels: [(a4f,b4f,g4f,r4f)(a3f,b3f,g3f,r3f)(a2f,b2f,g2f,r2f)(a1f,b1f,g1f,r1f)]
		// Write them to destination memory
		movdqa        [edx+16], xmm1
		popa
		emms
	}
}

void CSseRender::ARGB32_AlphaBlend(__inout BYTE *pbyDst, __in CSize DstSize, __in BYTE *pbyOvr, __in CSize OvrSize, __in CPoint BlendPoint)
{
	if (pbyDst == NULL || pbyOvr == NULL ||
		DstSize.cx == 0 || DstSize.cy == 0 ||
		OvrSize.cx == 0 || OvrSize.cy == 0 ||
		BlendPoint.x >= DstSize.cx ||
		BlendPoint.y >= DstSize.cy)
		return;

	CRect BlendRect(0, 0, 0, 0);
	BlendRect.left = BlendPoint.x;
	BlendRect.right = min((BlendRect.left + OvrSize.cx), DstSize.cx);
	BlendRect.top = BlendPoint.y;
	BlendRect.bottom = min((BlendRect.top + OvrSize.cy), DstSize.cy);

	for (int nLine = BlendRect.top; nLine < BlendRect.bottom; nLine++)
	{
		int nLineNum = nLine - BlendRect.top;
		BYTE *pbyLineDst = pbyDst + (DstSize.cx * nLine * 4) + (BlendRect.left * 4);
		BYTE *pbyLineOvr = pbyOvr + (OvrSize.cx * nLineNum * 4);

		int nLoops = BlendRect.Width() / 2;
		__asm
		{
			pxor		xmm2, xmm2	// 把MM2清0
			mov			edx, dword ptr [pbyLineDst]	// 取32bit像素地址到edx
			mov			eax, dword ptr [pbyLineOvr]
			mov			ecx, nLoops
			dec			ecx

		LOOP_S:
			movq		mm0, qword ptr [edx]	// 取2个像素值放入mm0，目标像素点
			movq		mm1, qword ptr [eax]	// 取2个像素值放入mm1，覆盖像素点

			movq2dq		xmm0, mm0	// 把2个像素值放入xmm0低64bit
			movq2dq		xmm1, mm1

			punpcklbw	xmm0, xmm2	// 扩展64位数据到128位，以64位为一个像素，以容纳计算结果
			punpcklbw	xmm1, xmm2

			//			movdq2q		mm4, xmm0	// TTT 测试显示值
			//			movdq2q		mm5, xmm1	// TTT 测试显示值

			movdqu		xmm3, xmm1	// 为了取得覆盖像素点的alpha值
			punpckhwd	xmm3, xmm3	// 高字移动到双字
			punpckhwd	xmm3, xmm3	// 高字移动到四字
			punpckhwd	xmm3, xmm3	// 双字移动到八字，可以分别计算每个颜色值的alpha的混合啦

			//			movdq2q		mm4, xmm3	// TTT 测试显示值

			movdqu		xmm4, xmm0
			movdqu		xmm5, xmm1

			psubusw		xmm4, xmm1	// Source-Overlay,饱和减
			psubusw		xmm5, xmm0	// Overlay-Source,饱和减

			pmullw		xmm4, xmm3	// Alpha * (Source-Overlay)
			pmullw		xmm5, xmm3	// Alpha * (Overlay-Source)

			psrlw		xmm4, 8		// 除以256,now mm4 get the result,(Source-Overlay)<0 部分
			psrlw		xmm5, 8		// 除以256,now mm5 get the result,(Overlay-Source)>0 部分

			paddusw		xmm0, xmm5	// 饱和加到原图象D=Alpha*(O-S)+S,(Source-Overlay)<0 部分
			psubusw		xmm0, xmm4	// 饱和加到原图象D=S-Alpha*(S-O),(Overlay-Source)>0 部分
			packuswb	xmm0, xmm0	// 紧缩到低32bit

			movdq2q		mm0, xmm0	// 保存结果
			movq		[edx], mm0
			add			edx, 8
			add			eax, 8

			loop		LOOP_S
			emms
		}

		if (BlendRect.Width() % 2 > 1)
		{
		}
	}
}
