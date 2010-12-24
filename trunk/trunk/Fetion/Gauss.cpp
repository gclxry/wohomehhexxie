
#include "stdafx.h"
#include "Gauss.h"

void CGaussBlur::ImageGaussiabBlur(BYTE *Data,int width, int height,double Q, int radius)
{		
	double fx = 0;
	int templateLength = radius*2 + 1;
	float *fweights = new float[templateLength];

	for(int i = 1; i <=  radius; i++)
	{
		fx = i / Q;   
		fweights[radius + i] = (float)exp(-fx * fx / 2);   
		fweights[radius - i] = fweights[radius + i];
	}

	fweights[radius] = 1.0;

	fx = 0.0;   
	for(int i = 0; i < templateLength; i++)
	{
		fx = fx + fweights[i];  
	}

	int *weights = new int[templateLength];

	// 归一化，整数化
	for(int i = 0; i < templateLength; i++)
	{
		weights[i] = int(fweights[i] / fx * 65536.0 + 0.5);  
	}

	delete fweights;

	// bgra 
	int bytes = 4;

	DWORD num = max(width,height)*bytes;
	BYTE *ptrTemp = new BYTE[num];
	memset(ptrTemp,0,num*sizeof(BYTE));

	int stride = width*bytes;
	int offSetColRadius = radius*stride;
	int offSetRowRadius = radius*bytes;

	int r,g,b,a,row,col;

	__asm
	{	
		// col blur
		mov     eax, 0				//	for(col = 0; col < width; col++)
			mov     col, eax 
			jmp     cColJudge 
cColLoop:
		mov     eax,col 
			add     eax,1 
			mov     col,eax 
cColJudge:
		mov     eax, width
			cmp     col, eax 
			jge     cColLoopEnd 

			mov     eax, radius			//	for(row = radius; row < height-radius; row++)
			mov     row, eax 
			jmp     cPreAlphaJudge 
cPreAlphaLoop:
		mov     eax,row 
			add     eax,1 
			mov     row,eax 
cPreAlphaJudge:
		mov     eax, height
			sub     eax, radius
			cmp     row, eax 
			jge     cPreAlphaLoopEnd 

			//pTT = (BYTE *)Data+row*stride +col*bytes; // 预乘alpha
			mov         eax, row
			imul        eax, stride
			add         eax, [Data] 
		mov         ecx, col
			imul        ecx, bytes 
			add         eax, ecx 

			mov			ebx, eax       // 指针放入ebx

			//	*pTT = (*pTT)*(*(pTT+3))/255;
			movzx       eax, [eax] 
		//	mov         ecx, [ebx] 
		movzx       edx, [ebx+3] 
		imul        eax, edx 
			cdq              
			mov         ecx, 0FFh 
			idiv        ecx 
			mov         [ebx],al 

			//	*(pTT+1) = (*(pTT+1))*(*(pTT+3))/255;
			mov			eax,  ebx
			movzx       eax, [eax+1] 
		//mov         ecx, [ebx] 
		movzx       edx, [ebx+3] 
		imul        eax, edx 
			cdq              
			mov         ecx, 0FFh 
			idiv        ecx 
			mov         [ebx+1], al 

			//	*(pTT+2) = (*(pTT+2))*(*(pTT+3))/255;
			mov			eax,  ebx
			movzx       eax, [eax+2] 
		//mov         ecx, [ebx] 
		movzx       edx, [ebx+3] 
		imul        eax,edx 
			cdq              
			mov         ecx,0FFh 
			idiv        ecx 
			mov         byte ptr [ebx+2],al 

			jmp         cPreAlphaLoop
cPreAlphaLoopEnd:

		mov     eax, radius					//	for(row = radius; row < height-radius; row++)
			mov     row, eax 
			jmp     cRowJudge 
cRowLoop:
		mov     eax,row 
			add     eax,1 
			mov     row,eax 
cRowJudge:
		mov     eax, height
			sub     eax, radius
			cmp     row, eax 
			jge     cRowEnd 

			xor     ebx, ebx					// 清零
			mov     r,   ebx   
			mov     g,	 ebx 
			mov     b,   ebx   
			mov     a,   ebx 		

			mov     eax, row 
			imul    eax, stride 
			//mov     ecx, Data 
			mov     edx, [Data]
		add     edx, eax 
			mov     eax, col 
			imul    eax, bytes 
			add     edx, eax					// 当前要进行模糊计算的像素	

			mov     esi, edx					// 运算涉及到的首个像素指针
			sub		esi, offSetColRadius		//
			mov		edi, weights				// 模板

			mov     ecx, templateLength			// 模板长度放入ecx
			dec		ecx							// 减一
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
			add     esi, stride					// 下一行的同一列
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


		mov         eax, radius
			imul        eax, stride
			add         eax, [Data] 
		mov         ecx, col
			imul        ecx, bytes 
			add         eax, ecx 
			mov			edi, eax       // 图片数据指针放入esi

			mov         eax, radius 
			imul        eax, bytes
			add         eax, ptrTemp
			mov         esi, eax		// 临时数据指针

			mov     eax, radius
			mov     row, eax 
			jmp     cRowCopyJudge 
cRowCopyLoop:
		mov     eax,row 
			add     eax,1 
			mov     row,eax 
cRowCopyJudge:
		mov     eax, height
			sub     eax, radius
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
			add         eax, stride 
			mov         edi, eax 

			jmp         cRowCopyLoop
cRowCopyLoopEnd:
		jmp		cColLoop

cColLoopEnd:

		// row blur

		mov     eax, 0						//		for(row = 0; row < height; row++)
			mov     row, eax 
			jmp     rRowJudge 
rRowLoop:
		mov     eax,row 
			add     eax,1 
			mov     row,eax 
rRowJudge:
		mov     eax, height
			cmp     row, eax 
			jge     rRowLoopEnd 

			mov     eax, radius					//	for(col = radius; col < height-radius; col++)
			mov     col, eax 
			jmp     rColJudge 
rColLoop:
		mov     eax, col 
			add     eax, 1 
			mov     col, eax 
rColJudge:
		mov     eax, width 
			sub     eax, radius
			cmp     col, eax 
			jge     rColEnd 

			xor     ebx, ebx					// 清零
			mov     r,   ebx   
			mov     g,	 ebx 
			mov     b,   ebx   
			mov     a,   ebx 		

			mov     eax, row 
			imul    eax, stride 
			//mov     ecx, Data 
			mov     edx, [Data]
		add     edx, eax 
			mov     eax, col 
			imul    eax, bytes 
			add     edx, eax					// 当前要进行模糊计算的像素	

			mov     esi, edx					// 运算涉及到的首个像素指针
			sub		esi, offSetRowRadius		//
			mov		edi, weights				// 模板

			mov     ecx, templateLength			// 模板长度放入ecx
			dec		ecx							// 减一
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


		mov         eax, radius						//	pTT = ptrTemp+radius*bytes;
			imul        eax, bytes
			add         eax, ptrTemp
			mov         esi, eax 

			mov         eax, row						//	BYTE *ppp = (BYTE *)Data+row*stride+radius*bytes;
			imul        eax, stride
			add         eax, Data
			mov         ecx, radius
			imul        ecx, bytes
			add         eax, ecx 
			mov         edi, eax 

			mov     eax, radius							//for(col = radius; col < width-radius; col++)
			mov     col, eax 
			jmp     rSepAlphaJudge 
rSepAlphaLoop:
		mov     eax,col 
			add     eax,1 
			mov     col,eax 
rSepAlphaJudge:
		mov     eax, width
			sub     eax, radius
			cmp     col, eax 
			jge     rSepAlphaEnd 



			movzx       ecx, [esi+3]					//	if(*(pTT+3) != 0 && *(pTT+3) != 255)
		test        ecx, ecx 
			je          rAlphaNullOrOpacity 
			//movzx       ecx, [esi+3] 
			cmp         ecx, 0FFh 
			je          rAlphaNullOrOpacity 


			movzx       eax, [esi]						//	*ppp = (*pTT)*255/(*(pTT+3));
		imul        eax, 0FFh 
			//movzx       ecx, [esi+3] 
			cdq              
			idiv        ecx 
			mov         [edi],al 


			movzx       eax, [esi+1]					//	*(ppp+1) = (*(pTT+1))*255/(*(pTT+3));
		imul        eax, 0FFh 
			//movzx       ecx, [esi+3] 
			cdq              
			idiv        ecx 
			mov         [edi+1],al 

			movzx       eax, [esi+2]					//	*(ppp+2) = (*(pTT+2))*255/(*(pTT+3));
		imul        eax, 0FFh 
			//movzx       ecx, [esi+3] 
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
	delete []weights;
} 