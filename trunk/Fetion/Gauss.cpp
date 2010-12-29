
#include "stdafx.h"
#include "Gauss.h"

// 模糊整个图像
// 32位bgra格式的数据
void CGaussBlur::ImageGaussBlur(BYTE *pbyData, int nWidth, int nHeight)
{
	if (m_pnWeightList == NULL)
		return;

	int nRadius = m_nRadius;
	// bgra 
	int bytes = 4;
	int nStride = nWidth*bytes;
	int templateLength = 2 * nRadius + 1;
	DWORD num = max(nWidth,nHeight)*bytes;
	BYTE *ptrTemp = new BYTE[num];
	memset(ptrTemp,0,num*sizeof(BYTE));	

	int *pnWeight = m_pnWeightList;

	int r,g,b,a,row,col;
	
	__asm
	{
		// col blur
		mov     eax, 0				//	for(col = 0; col < nWidth; col++)
		mov     col, eax 
		jmp     cColJudge 
	cColLoop:
		mov     eax,col 
		add     eax,1 
		mov     col,eax 
	cColJudge:
		mov     eax, nWidth
		cmp     col, eax 
		jge     cColLoopEnd 

		mov     eax, 0			//	for(row = 0; row < nHeight; row++)
		mov     row, eax 
		jmp     cPreAlphaJudge 
	cPreAlphaLoop:
		mov     edx,row 
		add     edx,1 
		mov     row,edx 
	cPreAlphaJudge:
		mov     eax, nHeight
		cmp     row, eax 
		jge     cPreAlphaLoopEnd 

		//pTT = (BYTE *)pbyData+row*nStride +col*bytes; // 预乘alpha
		mov         eax, row
		imul        eax, nStride
		add         eax, [pbyData] 
		mov         ecx, col
		imul        ecx, bytes 
		add         eax, ecx 

		mov			ebx, eax       // 指针放入ebx

	//	*pTT = (*pTT)*(*(pTT+3))/255;
		movzx       eax, [eax] 
		movzx       edx, [ebx+3] 
		imul        eax, edx 
		cdq              
		mov         ecx, 0FFh 
		idiv        ecx 
		mov         [ebx],al 

	//	*(pTT+1) = (*(pTT+1))*(*(pTT+3))/255;
		mov			eax,  ebx
		movzx       eax, [eax+1] 
		movzx       edx, [ebx+3] 
		imul        eax, edx 
		cdq              
		mov         ecx, 0FFh 
		idiv        ecx 
		mov         [ebx+1], al 

	//	*(pTT+2) = (*(pTT+2))*(*(pTT+3))/255;
		mov			eax,  ebx
		movzx       eax, [eax+2] 
		movzx       edx, [ebx+3] 
		imul        eax,edx 
		cdq              
		mov         ecx,0FFh 
		idiv        ecx 
		mov         byte ptr [ebx+2],al 

		jmp         cPreAlphaLoop
cPreAlphaLoopEnd:

		mov     eax, 0					//	for(row = ; row < nHeight; row++)
		mov     row, eax 
		jmp     cRowJudge 
	cRowLoop:
		mov     edx,row 
		add     edx,1 
		mov     row,edx 
	cRowJudge:
		mov     eax, nHeight
		cmp     row, eax 
		jge     cRowEnd 
		
		xor     ebx, ebx					// 清零
		mov     r,   ebx   
		mov     g,	 ebx 
		mov     b,   ebx   
		mov     a,   ebx 		
		
 		mov     eax, row 
 		imul    eax, nStride 
 		mov     edx, [pbyData]
 		add     edx, eax 
 		mov     eax, col 
 		imul    eax, bytes 
 		add     edx, eax					// 当前要进行模糊计算的像素	
					
		mov     esi, edx					// 运算涉及到的首个像素指针	
		mov		edi, pnWeight				// 模板
		
		mov     ecx, templateLength			// 模板长度放入ecx
		
		mov     eax, nRadius					// 计算模板偏移量像素扫描线偏移量
		cmp		eax, row
		jge		cOffset1
		mov		eax, nHeight
		sub		eax, nRadius
		dec		eax
		cmp		eax, row
		jl		cOffset2					//(ecx-nRadius+nHeight-row-1)
		jmp		cOffset3
	cOffset1:						
		add		ecx, row                    // 循环次数调整
		sub		ecx, eax
		sub     eax, row					// 模板偏移量
		imul    eax, 4							
		add		edi, eax
		mov		eax, nStride					// 数据偏移量
		imul	eax, row
		sub		esi, eax	
		jmp		cblurLoop
	cOffset2:
		add		ecx, eax					// 后边界只调整循环次数和源数据指针
		sub		ecx, row
	cOffset3:
		mov		eax, nRadius					// 中间部分只调整源数据指针
		imul	eax, nStride
		sub		esi, eax
	cblurLoop:								// 模糊循环
		movzx   eax, [esi]					// blue
		movzx   edx, [esi+1]				// green
		imul    eax, [edi]					// blue与模板相乘
		imul    edx, [edi]					// green与模板相乘
		add     b,   eax					// blue结果累加
		add     g,   edx					// green结果累加
		movzx   eax, [esi+2]				// red
		movzx   edx, [esi+3]				// alpha
		imul    eax, [edi]					// red与模板相乘
		imul    edx, [edi]					// alpha与模板相乘
		add     r,   eax					// red结果累加
		add     a,   edx					// alpha结果累加
		add     edi, 4						// 循环变量增加一，int型数据占4字节
		add     esi, nStride					// 下一行的同一列
		loop    cblurLoop					// goto cblurLoop


		mov     eax, row 
 		imul    eax, bytes 
 		add     eax, [ptrTemp]				// 临时数据指针
		mov     edi, eax				

		mov		eax, b
		shr		eax, 16
		mov		[edi], al
		mov		eax, g
		shr		eax, 16
		mov		[edi+1], al
		mov		eax, r
		shr		eax, 16
		mov		[edi+2], al
		mov		eax, a
		shr		eax, 16
		mov		[edi+3], al

		jmp     cRowLoop 
	cRowEnd:


		mov         eax, pbyData
		mov         ecx, col
		imul        ecx, bytes 
		add         eax, ecx 
		mov			edi, eax			// 图片数据指针放入esi

		mov         esi, ptrTemp		// 临时数据指针

		mov     eax, 0
		mov     row, eax 
		jmp     cRowCopyJudge 
	cRowCopyLoop:
		mov     edx,row 
		add     edx,1 
		mov     row,edx 
	cRowCopyJudge:
		mov     eax, nHeight
		cmp     row, eax 
		jge     cRowCopyLoopEnd 
		
		mov         dl, [esi]		// copy data
		mov         [edi], dl 
		mov         dl, [esi+1] 
		mov         [edi+1], dl 
		mov         dl, [esi+2] 
		mov         [edi+2], dl 
		mov         dl, [esi+3] 
		mov         [edi+3], dl 

		mov         eax, esi		// ptroffset
		add         eax, bytes
		mov         esi, eax 			
		mov         eax, edi		// ptroffset
		add         eax, nStride 
		mov         edi, eax 

		jmp         cRowCopyLoop
	cRowCopyLoopEnd:
		jmp		cColLoop

	cColLoopEnd:

	//// row blur

		mov     eax, 0						//		for(row = 0; row < nHeight; row++)
		mov     row, eax 
		jmp     rRowJudge 
	rRowLoop:
		mov     eax,row 
		add     eax,1 
		mov     row,eax 
	rRowJudge:
		mov     eax, nHeight
		cmp     row, eax 
		jge     rRowLoopEnd 

		mov     eax, 0					//	for(col = 0; col < nHeight; col++)
		mov     col, eax 
		jmp     rColJudge 
	rColLoop:
		mov     eax, col 
		add     eax, 1 
		mov     col, eax 
	rColJudge:
		mov     eax, nWidth 
		cmp     col, eax 
		jge     rColEnd 

		xor     ebx, ebx					// 清零
		mov     r,   ebx   
		mov     g,	 ebx 
		mov     b,   ebx   
		mov     a,   ebx 		
		
		mov     eax, row 
 		imul    eax, nStride 
 		mov     edx, [pbyData]
 		add     edx, eax 
 		mov     eax, col 
 		imul    eax, bytes 
 		add     edx, eax					// 当前要进行模糊计算的像素	
		
		mov     esi, edx					// 运算涉及到的首个像素指针	//
		mov		edi, pnWeight				// 模板
		
		mov     ecx, templateLength			// 模板长度放入ecx
		
		mov     eax, nRadius					// 计算模板偏移量像素扫描线偏移量
		cmp		eax, col
		jge		rOffset1
		mov		eax, nWidth
		sub		eax, nRadius
		dec		eax
		cmp		eax, col
		jl		rOffset2					//(ecx-nRadius+nWidth-col-1)
		jmp		rOffset3
	rOffset1:						
		add		ecx, col                    // 循环次数调整
		sub		ecx, eax
		sub     eax, col					// 模板偏移量
		imul    eax, 4							
		add		edi, eax
		mov		eax, bytes					// 数据偏移量
		imul	eax, col
		sub		esi, eax	
		jmp		rblurLoop
	rOffset2:
		add		ecx, eax					// 后边界只调整循环次数和源数据指针
		sub		ecx, col
	rOffset3:
		mov		eax, nRadius					// 中间部分只调整源数据指针
		imul	eax, bytes
		sub		esi, eax
	rblurLoop:								// 模糊循环
		movzx   eax, [esi]					// blue
		movzx   edx, [esi+1]				// green
		imul    eax, [edi]					// blue与模板相乘
		imul    edx, [edi]					// green与模板相乘
		add     b,   eax					// blue结果累加
		add     g,   edx					// green结果累加
		movzx   eax, [esi+2]				// red
		movzx   edx, [esi+3]				// alpha
		imul    eax, [edi]					// red与模板相乘
		imul    edx, [edi]					// alpha与模板相乘
		add     r,   eax					// red结果累加
		add     a,   edx					// alpha结果累加
		add     edi, 4						// 循环变量增加一，int型数据占4字节
		add     esi, bytes					// 下个像素
		loop    rblurLoop					// goto rblurLoop

		mov     eax, col 
 		imul    eax, bytes 
 		add     eax, [ptrTemp]				// 临时数据指针
		mov     edi, eax					
	
		mov		eax, b						// 模板左移16位放大过，此处缩小回去
		shr		eax, 16
		mov		[edi], al
		mov		eax, g
		shr		eax, 16
		mov		[edi+1], al
		mov		eax, r
		shr		eax, 16
		mov		[edi+2], al
		mov		eax, a
		shr		eax, 16
		mov		[edi+3], al

		jmp     rColLoop 
	rColEnd:

		mov         esi, ptrTemp					//	pTT = ptrTemp+nRadius*bytes;
		
		mov         eax, row						//	BYTE *ppp = (BYTE *)pbyData+row*nStride+nRadius*bytes;
		imul        eax, nStride
		add         eax, pbyData
		mov         edi, eax 
	
		mov     eax, 0								//for(col = 0; col < nWidth; col++)
		mov     col, eax 
		jmp     rSepAlphaJudge 
	rSepAlphaLoop:
		mov     eax,col 
		add     eax,1 
		mov     col,eax 
	rSepAlphaJudge:
		mov     eax, nWidth
		cmp     col, eax 
		jge     rSepAlphaEnd 
	

		movzx       ecx, [esi+3]					//	if(*(pTT+3) != 0 && *(pTT+3) != 255)
		test        ecx, ecx 
		je          rAlphaNullOrOpacity 
		cmp         ecx, 0FFh 
		je          rAlphaNullOrOpacity 
			
		
		movzx       eax, [esi]						//	*ppp = (*pTT)*255/(*(pTT+3));
		imul        eax, 0FFh 
		cdq              
		idiv        ecx 
		mov         [edi],al 


		movzx       eax, [esi+1]					//	*(ppp+1) = (*(pTT+1))*255/(*(pTT+3));
		imul        eax, 0FFh 
		cdq              
		idiv        ecx 
		mov         [edi+1],al 
		
		movzx       eax, [esi+2]					//	*(ppp+2) = (*(pTT+2))*255/(*(pTT+3));
		imul        eax, 0FFh 
		cdq              
		idiv        ecx 
		mov         [edi+2], al 
		jmp			rAlphaCopy
		
	rAlphaNullOrOpacity:
		mov         dl, [esi]						// alpha is 0 or 255,just copy r,g,b
		mov         [edi], dl 
		mov         dl, [esi+1] 
		mov         [edi+1], dl 
		mov         dl, [esi+2] 
		mov         [edi+2], dl 
	rAlphaCopy:										
		mov         dl, [esi+3]						//  *(ppp+3) = *(pTT+3);
		mov         [edi+3], dl 
		
		mov         eax, esi						//  pTT += bytes;
		add         eax, bytes
		mov         esi, eax 
		
		mov         eax, edi						//  ppp += bytes;
		add         eax, bytes 
		mov         edi, eax 

		jmp        rSepAlphaLoop

	rSepAlphaEnd:
		jmp			rRowLoop
	rRowLoopEnd:
	}

	delete []ptrTemp;
} 

// 根据方差dbQ与模糊半径nRadius生成 m_pnWeightList
void CGaussBlur::InitWeights(double dbQ, int nRadius)
{
	if (m_pnWeightList != NULL)
	{
		delete []m_pnWeightList;
		m_pnWeightList = NULL;
	}

	m_nRadius = nRadius;

	double fx = 0;
	int templateLength = nRadius*2 + 1;
	float *fweights = new float[templateLength];
	
	for(int i = 1; i <= nRadius; i++)
	{
		fx = i / dbQ;   
		fweights[nRadius + i] = (float)exp(-fx * fx / 2);   
		fweights[nRadius - i] = fweights[nRadius + i];
	}

	fweights[nRadius] = 1.0;

	fx = 0.0;   
	for(int i = 0; i < templateLength; i++)
	{
		fx = fx + fweights[i];  
	}

	m_pnWeightList = new int[templateLength];
	if (m_pnWeightList == NULL)
	{
		delete fweights;
		return;
	}

	// 归一化，整数化
	for(int i = 0; i < templateLength; i++)
	{
		m_pnWeightList[i] = int(fweights[i] / fx * 65536.0 + 0.5);  
	}
 
	delete fweights;
}

// 32位bgra格式，可以指定上下左右的模糊范围
void CGaussBlur::ImageGaussBlur(BYTE *pbyData, int nWidth, int nHeight, int nLeft, int nTop, int nRight, int nBottom)
{
	if (m_pnWeightList == NULL)
		return;
	
	int bytes = 4;
	int nStride = nWidth*bytes;
	DWORD num = max(nWidth,nHeight)*bytes;
	BYTE *ptrTemp = new BYTE[num];
	memset(ptrTemp,0,num*sizeof(BYTE));


	_ImageGaussiabBlur(pbyData,0,nWidth,0,nTop,nStride,ptrTemp);
	_ImageGaussiabBlur(pbyData,0,nWidth,nHeight-nBottom,nHeight,nStride,ptrTemp);
	_ImageGaussiabBlur(pbyData,0,nLeft,nTop,nHeight-nBottom,nStride,ptrTemp);
	_ImageGaussiabBlur(pbyData,nWidth-nRight,nWidth,nTop,nHeight-nBottom,nStride,ptrTemp);

	delete []ptrTemp;
}

// 局部模糊函数核心算法
void CGaussBlur::_ImageGaussiabBlur(BYTE *pbyData, int nWidthFrom, int nWidthTo, int nHeightFrom, int nHeightTo, int nStride, BYTE *ptrTemp)
{
	if (m_pnWeightList == NULL)
		return;

	int nRadius = m_nRadius;
	int r,g,b,a,row,col,bytes = 4;
	int templateLength = 2 * nRadius + 1;

	int *pnWeight = m_pnWeightList;

	__asm
	{
		// col blur
		mov     eax, nWidthFrom				//	for(col = 0; col < nWidth; col++)
		mov     col, eax 
		jmp     cColJudge 
	cColLoop:
		mov     eax,col 
		add     eax,1 
		mov     col,eax 
	cColJudge:
		mov     eax, nWidthTo
		cmp     col, eax 
		jge     cColLoopEnd 

		mov     eax, nHeightFrom			//	for(row = 0; row < nHeight; row++)
		mov     row, eax 
		jmp     cPreAlphaJudge 
	cPreAlphaLoop:
		mov     edx,row 
		add     edx,1 
		mov     row,edx 
	cPreAlphaJudge:
		mov     eax, nHeightTo
		cmp     row, eax 
		jge     cPreAlphaLoopEnd 

		//pTT = (BYTE *)pbyData+row*nStride +col*bytes; // 预乘alpha
		mov         eax, row
		imul        eax, nStride
		add         eax, [pbyData] 
		mov         ecx, col
		imul        ecx, bytes 
		add         eax, ecx 

		mov			ebx, eax       // 指针放入ebx

	//	*pTT = (*pTT)*(*(pTT+3))/255;
		movzx       eax, [eax] 
		movzx       edx, [ebx+3] 
		imul        eax, edx 
		cdq              
		mov         ecx, 0FFh 
		idiv        ecx 
		mov         [ebx],al 

	//	*(pTT+1) = (*(pTT+1))*(*(pTT+3))/255;
		mov			eax,  ebx
		movzx       eax, [eax+1] 
		movzx       edx, [ebx+3] 
		imul        eax, edx 
		cdq              
		mov         ecx, 0FFh 
		idiv        ecx 
		mov         [ebx+1], al 

	//	*(pTT+2) = (*(pTT+2))*(*(pTT+3))/255;
		mov			eax,  ebx
		movzx       eax, [eax+2] 
		movzx       edx, [ebx+3] 
		imul        eax,edx 
		cdq              
		mov         ecx,0FFh 
		idiv        ecx 
		mov         byte ptr [ebx+2],al 

		jmp         cPreAlphaLoop
cPreAlphaLoopEnd:

		mov     eax, nHeightFrom					//	for(row = 0; row < nHeight; row++)
		mov     row, eax 
		jmp     cRowJudge 
	cRowLoop:
		mov     edx,row 
		add     edx,1 
		mov     row,edx 
	cRowJudge:
		mov     eax, nHeightTo
		cmp     row, eax 
		jge     cRowEnd 
		
		xor     ebx, ebx					// 清零
		mov     r,   ebx   
		mov     g,	 ebx 
		mov     b,   ebx   
		mov     a,   ebx 		
		
 		mov     eax, row 
 		imul    eax, nStride 
 		//mov     ecx, pbyData 
 		mov     edx, [pbyData]
 		add     edx, eax 
 		mov     eax, col 
 		imul    eax, bytes 
 		add     edx, eax					// 当前要进行模糊计算的像素	
					
		mov     esi, edx					// 运算涉及到的首个像素指针	
		mov		edi, pnWeight				// 模板
		
		mov     ecx, templateLength			// 模板长度放入ecx
		
		mov     eax, nRadius					// 计算模板偏移量像素扫描线偏移量
		mov		ebx, row
		sub		ebx, nHeightFrom
		cmp		eax, ebx
		jge		cOffset1
		mov		eax, nHeightTo
		sub		eax, nRadius
		sub		eax, nHeightFrom
		dec		eax
		cmp		eax, ebx
		jl		cOffset2					//(ecx-nRadius+nHeight-row-1)
		jmp		cOffset3
	cOffset1:						
		add		ecx, ebx                    // 循环次数调整
		sub		ecx, eax
		sub     eax, ebx					// 模板偏移量
		imul    eax, 4							
		add		edi, eax
		mov		eax, nStride					// 数据偏移量
		imul	eax, ebx
		sub		esi, eax	
		jmp		cblurLoop
	cOffset2:
		add		ecx, eax					// 后边界只调整循环次数和源数据指针
		sub		ecx, ebx
	cOffset3:
		mov		eax, nRadius					// 中间部分只调整源数据指针
		imul	eax, nStride
		sub		esi, eax
	cblurLoop:								// 模糊循环
		movzx   eax, [esi]					// blue
		movzx   edx, [esi+1]				// green
		imul    eax, [edi]					// blue与模板相乘
		imul    edx, [edi]					// green与模板相乘
		add     b,   eax					// blue结果累加
		add     g,   edx					// green结果累加
		movzx   eax, [esi+2]				// red
		movzx   edx, [esi+3]				// alpha
		imul    eax, [edi]					// red与模板相乘
		imul    edx, [edi]					// alpha与模板相乘
		add     r,   eax					// red结果累加
		add     a,   edx					// alpha结果累加
		add     edi, 4						// 循环变量增加一，int型数据占4字节
		add     esi, nStride					// 下一行的同一列
		loop    cblurLoop					// goto cblurLoop


		mov     eax, row 
 		imul    eax, bytes 
 		add     eax, [ptrTemp]				// 临时数据指针
		mov     edi, eax				

		mov		eax, b
		shr		eax, 16
		mov		[edi], al
		mov		eax, g
		shr		eax, 16
		mov		[edi+1], al
		mov		eax, r
		shr		eax, 16
		mov		[edi+2], al
		mov		eax, a
		shr		eax, 16
		mov		[edi+3], al

		jmp     cRowLoop 
	cRowEnd:


		mov         eax, nHeightFrom
		imul        eax, nStride
		add         eax, [pbyData] 
		mov         ecx, col
		imul        ecx, bytes 
		add         eax, ecx 
		mov			edi, eax       // 图片数据指针放入esi

		mov         eax, nHeightFrom 
		imul        eax, bytes
		add         eax, ptrTemp
		mov         esi, eax		// 临时数据指针

		mov     eax, nHeightFrom
		mov     row, eax 
		jmp     cRowCopyJudge 
	cRowCopyLoop:
		mov     edx,row 
		add     edx,1 
		mov     row,edx 
	cRowCopyJudge:
		mov     eax, nHeightTo
		cmp     row, eax 
		jge     cRowCopyLoopEnd 
		
		mov         dl, [esi]		// copy data
		mov         [edi], dl 
		mov         dl, [esi+1] 
		mov         [edi+1], dl 
		mov         dl, [esi+2] 
		mov         [edi+2], dl 
		mov         dl, [esi+3] 
		mov         [edi+3], dl 

		mov         eax, esi		// ptroffset
		add         eax, bytes
		mov         esi, eax 			
		mov         eax, edi		// ptroffset
		add         eax, nStride 
		mov         edi, eax 

		jmp         cRowCopyLoop
	cRowCopyLoopEnd:
		jmp		cColLoop

	cColLoopEnd:

	//// row blur

		mov     eax, nHeightFrom						//		for(row = 0; row < nHeight; row++)
		mov     row, eax 
		jmp     rRowJudge 
	rRowLoop:
		mov     eax,row 
		add     eax,1 
		mov     row,eax 
	rRowJudge:
		mov     eax, nHeightTo
		cmp     row, eax 
		jge     rRowLoopEnd 

		mov     eax, nWidthFrom					//	for(col = 0; col < nHeight; col++)
		mov     col, eax 
		jmp     rColJudge 
	rColLoop:
		mov     eax, col 
		add     eax, 1 
		mov     col, eax 
	rColJudge:
		mov     eax, nWidthTo 
		cmp     col, eax 
		jge     rColEnd 

		xor     ebx, ebx					// 清零
		mov     r,   ebx   
		mov     g,	 ebx 
		mov     b,   ebx   
		mov     a,   ebx 		
		
		mov     eax, row 
 		imul    eax, nStride 
 		mov     edx, [pbyData]
 		add     edx, eax 
 		mov     eax, col 
 		imul    eax, bytes 
 		add     edx, eax					// 当前要进行模糊计算的像素	
		
		mov     esi, edx					// 运算涉及到的首个像素指针	//
		mov		edi, pnWeight				// 模板
		
		mov     ecx, templateLength			// 模板长度放入ecx
		
		mov     eax, nRadius					// 计算模板偏移量像素扫描线偏移量
		mov		ebx, col
		sub		ebx, nWidthFrom
		cmp		eax, ebx
		jge		rOffset1
		mov		eax, nWidthTo
		sub		eax, nRadius
		sub		eax, nWidthFrom
		dec		eax
		cmp		eax, ebx
		jl		rOffset2					//(ecx-nRadius+nWidth-col-1)
		jmp		rOffset3
	rOffset1:						
		add		ecx, ebx                    // 循环次数调整
		sub		ecx, eax
		sub     eax, ebx					// 模板偏移量
		imul    eax, 4							
		add		edi, eax
		mov		eax, bytes					// 数据偏移量
		imul	eax, ebx
		sub		esi, eax	
		jmp		rblurLoop
	rOffset2:
		add		ecx, eax					// 后边界只调整循环次数和源数据指针
		sub		ecx, ebx
	rOffset3:
		mov		eax, nRadius					// 中间部分只调整源数据指针
		imul	eax, bytes
		sub		esi, eax
	rblurLoop:								// 模糊循环
		movzx   eax, [esi]					// blue
		movzx   edx, [esi+1]				// green
		imul    eax, [edi]					// blue与模板相乘
		imul    edx, [edi]					// green与模板相乘
		add     b,   eax					// blue结果累加
		add     g,   edx					// green结果累加
		movzx   eax, [esi+2]				// red
		movzx   edx, [esi+3]				// alpha
		imul    eax, [edi]					// red与模板相乘
		imul    edx, [edi]					// alpha与模板相乘
		add     r,   eax					// red结果累加
		add     a,   edx					// alpha结果累加
		add     edi, 4						// 循环变量增加一，int型数据占4字节
		add     esi, bytes					// 下个像素
		loop    rblurLoop					// goto rblurLoop

		mov     eax, col 
 		imul    eax, bytes 
 		add     eax, [ptrTemp]				// 临时数据指针
		mov     edi, eax					
	
		mov		eax, b						// 模板左移16位放大过，此处缩小回去
		shr		eax, 16
		mov		[edi], al
		mov		eax, g
		shr		eax, 16
		mov		[edi+1], al
		mov		eax, r
		shr		eax, 16
		mov		[edi+2], al
		mov		eax, a
		shr		eax, 16
		mov		[edi+3], al

		jmp     rColLoop 
	rColEnd:

		mov         eax, nWidthFrom						//	pTT = ptrTemp+nRadius*bytes;
		imul        eax, bytes
		add         eax, ptrTemp
		mov         esi, eax 
		
		mov         eax, row						//	BYTE *ppp = (BYTE *)pbyData+row*nStride+nRadius*bytes;
		imul        eax, nStride
		add         eax, pbyData
		mov         ecx, nWidthFrom
		imul        ecx, bytes
		add         eax, ecx 
		mov         edi, eax 
	
		mov     eax, nWidthFrom								//for(col = 0; col < nWidth; col++)
		mov     col, eax 
		jmp     rSepAlphaJudge 
	rSepAlphaLoop:
		mov     eax,col 
		add     eax,1 
		mov     col,eax 
	rSepAlphaJudge:
		mov     eax, nWidthTo
		cmp     col, eax 
		jge     rSepAlphaEnd 
	

		movzx       ecx, [esi+3]					//	if(*(pTT+3) != 0 && *(pTT+3) != 255)
		test        ecx, ecx 
		je          rAlphaNullOrOpacity 
		cmp         ecx, 0FFh 
		je          rAlphaNullOrOpacity 
			
		
		movzx       eax, [esi]						//	*ppp = (*pTT)*255/(*(pTT+3));
		imul        eax, 0FFh 
		cdq              
		idiv        ecx 
		mov         [edi],al 


		movzx       eax, [esi+1]					//	*(ppp+1) = (*(pTT+1))*255/(*(pTT+3));
		imul        eax, 0FFh 
		cdq              
		idiv        ecx 
		mov         [edi+1],al 
		
		movzx       eax, [esi+2]					//	*(ppp+2) = (*(pTT+2))*255/(*(pTT+3));
		imul        eax, 0FFh 
		cdq              
		idiv        ecx 
		mov         [edi+2], al 
		jmp			rAlphaCopy
		
	rAlphaNullOrOpacity:
		mov         dl, [esi]						// alpha is 0 or 255,just copy r,g,b
		mov         [edi], dl 
		mov         dl, [esi+1] 
		mov         [edi+1], dl 
		mov         dl, [esi+2] 
		mov         [edi+2], dl 
	rAlphaCopy:										
		mov         dl, [esi+3]						//  *(ppp+3) = *(pTT+3);
		mov         [edi+3], dl 
		
		mov         eax, esi						//  pTT += bytes;
		add         eax, bytes
		mov         esi, eax 
		
		mov         eax, edi						//  ppp += bytes;
		add         eax, bytes 
		mov         edi, eax 

		jmp        rSepAlphaLoop

	rSepAlphaEnd:
		jmp			rRowLoop
	rRowLoopEnd:
	}
} 
