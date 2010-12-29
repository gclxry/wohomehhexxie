
#include "stdafx.h"
#include "Gauss.h"

// ģ������ͼ��
// 32λbgra��ʽ������
void CGaussBlur::ImageGaussBlur(BYTE *Data,int width, int height)
{		
	int radius = m_nRadius;
	// bgra 
	int bytes = 4;
	int stride = width*bytes;
	int templateLength = 2 * radius + 1;
	DWORD num = max(width,height)*bytes;
	BYTE *ptrTemp = new BYTE[num];
	memset(ptrTemp,0,num*sizeof(BYTE));	

	int *pnWeight = m_pnWeightList;

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

		mov     eax, 0			//	for(row = 0; row < height; row++)
		mov     row, eax 
		jmp     cPreAlphaJudge 
	cPreAlphaLoop:
		mov     edx,row 
		add     edx,1 
		mov     row,edx 
	cPreAlphaJudge:
		mov     eax, height
		cmp     row, eax 
		jge     cPreAlphaLoopEnd 

		//pTT = (BYTE *)Data+row*stride +col*bytes; // Ԥ��alpha
		mov         eax, row
		imul        eax, stride
		add         eax, [Data] 
		mov         ecx, col
		imul        ecx, bytes 
		add         eax, ecx 

		mov			ebx, eax       // ָ�����ebx

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

		mov     eax, 0					//	for(row = ; row < height; row++)
		mov     row, eax 
		jmp     cRowJudge 
	cRowLoop:
		mov     edx,row 
		add     edx,1 
		mov     row,edx 
	cRowJudge:
		mov     eax, height
		cmp     row, eax 
		jge     cRowEnd 
		
		xor     ebx, ebx					// ����
		mov     r,   ebx   
		mov     g,	 ebx 
		mov     b,   ebx   
		mov     a,   ebx 		
		
 		mov     eax, row 
 		imul    eax, stride 
 		mov     edx, [Data]
 		add     edx, eax 
 		mov     eax, col 
 		imul    eax, bytes 
 		add     edx, eax					// ��ǰҪ����ģ�����������	
					
		mov     esi, edx					// �����漰�����׸�����ָ��	
		mov		edi, pnWeight				// ģ��
		
		mov     ecx, templateLength			// ģ�峤�ȷ���ecx
		
		mov     eax, radius					// ����ģ��ƫ��������ɨ����ƫ����
		cmp		eax, row
		jge		cOffset1
		mov		eax, height
		sub		eax, radius
		dec		eax
		cmp		eax, row
		jl		cOffset2					//(ecx-radius+height-row-1)
		jmp		cOffset3
	cOffset1:						
		add		ecx, row                    // ѭ����������
		sub		ecx, eax
		sub     eax, row					// ģ��ƫ����
		imul    eax, 4							
		add		edi, eax
		mov		eax, stride					// ����ƫ����
		imul	eax, row
		sub		esi, eax	
		jmp		cblurLoop
	cOffset2:
		add		ecx, eax					// ��߽�ֻ����ѭ��������Դ����ָ��
		sub		ecx, row
	cOffset3:
		mov		eax, radius					// �м䲿��ֻ����Դ����ָ��
		imul	eax, stride
		sub		esi, eax
	cblurLoop:								// ģ��ѭ��
		movzx   eax, [esi]					// blue
		movzx   edx, [esi+1]				// green
		imul    eax, [edi]					// blue��ģ�����
		imul    edx, [edi]					// green��ģ�����
		add     b,   eax					// blue����ۼ�
		add     g,   edx					// green����ۼ�
		movzx   eax, [esi+2]				// red
		movzx   edx, [esi+3]				// alpha
		imul    eax, [edi]					// red��ģ�����
		imul    edx, [edi]					// alpha��ģ�����
		add     r,   eax					// red����ۼ�
		add     a,   edx					// alpha����ۼ�
		add     edi, 4						// ѭ����������һ��int������ռ4�ֽ�
		add     esi, stride					// ��һ�е�ͬһ��
		loop    cblurLoop					// goto cblurLoop


		mov     eax, row 
 		imul    eax, bytes 
 		add     eax, [ptrTemp]				// ��ʱ����ָ��
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


		mov         eax, Data
		mov         ecx, col
		imul        ecx, bytes 
		add         eax, ecx 
		mov			edi, eax			// ͼƬ����ָ�����esi

		mov         esi, ptrTemp		// ��ʱ����ָ��

		mov     eax, 0
		mov     row, eax 
		jmp     cRowCopyJudge 
	cRowCopyLoop:
		mov     edx,row 
		add     edx,1 
		mov     row,edx 
	cRowCopyJudge:
		mov     eax, height
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

	//// row blur

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

		mov     eax, 0					//	for(col = 0; col < height; col++)
		mov     col, eax 
		jmp     rColJudge 
	rColLoop:
		mov     eax, col 
		add     eax, 1 
		mov     col, eax 
	rColJudge:
		mov     eax, width 
		cmp     col, eax 
		jge     rColEnd 

		xor     ebx, ebx					// ����
		mov     r,   ebx   
		mov     g,	 ebx 
		mov     b,   ebx   
		mov     a,   ebx 		
		
		mov     eax, row 
 		imul    eax, stride 
 		mov     edx, [Data]
 		add     edx, eax 
 		mov     eax, col 
 		imul    eax, bytes 
 		add     edx, eax					// ��ǰҪ����ģ�����������	
		
		mov     esi, edx					// �����漰�����׸�����ָ��	//
		mov		edi, pnWeight				// ģ��
		
		mov     ecx, templateLength			// ģ�峤�ȷ���ecx
		
		mov     eax, radius					// ����ģ��ƫ��������ɨ����ƫ����
		cmp		eax, col
		jge		rOffset1
		mov		eax, width
		sub		eax, radius
		dec		eax
		cmp		eax, col
		jl		rOffset2					//(ecx-radius+width-col-1)
		jmp		rOffset3
	rOffset1:						
		add		ecx, col                    // ѭ����������
		sub		ecx, eax
		sub     eax, col					// ģ��ƫ����
		imul    eax, 4							
		add		edi, eax
		mov		eax, bytes					// ����ƫ����
		imul	eax, col
		sub		esi, eax	
		jmp		rblurLoop
	rOffset2:
		add		ecx, eax					// ��߽�ֻ����ѭ��������Դ����ָ��
		sub		ecx, col
	rOffset3:
		mov		eax, radius					// �м䲿��ֻ����Դ����ָ��
		imul	eax, bytes
		sub		esi, eax
	rblurLoop:								// ģ��ѭ��
		movzx   eax, [esi]					// blue
		movzx   edx, [esi+1]				// green
		imul    eax, [edi]					// blue��ģ�����
		imul    edx, [edi]					// green��ģ�����
		add     b,   eax					// blue����ۼ�
		add     g,   edx					// green����ۼ�
		movzx   eax, [esi+2]				// red
		movzx   edx, [esi+3]				// alpha
		imul    eax, [edi]					// red��ģ�����
		imul    edx, [edi]					// alpha��ģ�����
		add     r,   eax					// red����ۼ�
		add     a,   edx					// alpha����ۼ�
		add     edi, 4						// ѭ����������һ��int������ռ4�ֽ�
		add     esi, bytes					// �¸�����
		loop    rblurLoop					// goto rblurLoop

		mov     eax, col 
 		imul    eax, bytes 
 		add     eax, [ptrTemp]				// ��ʱ����ָ��
		mov     edi, eax					
	
		mov		eax, b						// ģ������16λ�Ŵ�����˴���С��ȥ
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

		mov         esi, ptrTemp					//	pTT = ptrTemp+radius*bytes;
		
		mov         eax, row						//	BYTE *ppp = (BYTE *)Data+row*stride+radius*bytes;
		imul        eax, stride
		add         eax, Data
		mov         edi, eax 
	
		mov     eax, 0								//for(col = 0; col < width; col++)
		mov     col, eax 
		jmp     rSepAlphaJudge 
	rSepAlphaLoop:
		mov     eax,col 
		add     eax,1 
		mov     col,eax 
	rSepAlphaJudge:
		mov     eax, width
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

// ���ݷ���Q��ģ���뾶radius���� m_pnWeightList
void CGaussBlur::InitWeights(double Q, int radius)
{
	m_nRadius = radius;

	double fx = 0;
	int templateLength = radius*2 + 1;
	float *fweights = new float[templateLength];
	
	for(int i = 1; i <= radius; i++)
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

	m_pnWeightList = new int[templateLength];

	// ��һ����������
	for(int i = 0; i < templateLength; i++)
	{
		m_pnWeightList[i] = int(fweights[i] / fx * 65536.0 + 0.5);  
	}
 
	delete fweights;
}
// 32λbgra��ʽ������ָ���������ҵ�ģ����Χ
void CGaussBlur::ImageGaussBlur(BYTE *Data,int width, int height,int left,int top,int right,int bottom)
{
	if (m_pnWeightList == NULL)
		return;
	
	int bytes = 4;
	int stride = width*bytes;
	DWORD num = max(width,height)*bytes;
	BYTE *ptrTemp = new BYTE[num];
	memset(ptrTemp,0,num*sizeof(BYTE));


	_ImageGaussiabBlur(Data,0,width,0,top,stride,ptrTemp);
	_ImageGaussiabBlur(Data,0,width,height-bottom,height,stride,ptrTemp);
	_ImageGaussiabBlur(Data,0,left,top,height-bottom,stride,ptrTemp);
	_ImageGaussiabBlur(Data,width-right,width,top,height-bottom,stride,ptrTemp);

	delete []ptrTemp;
}

// �ֲ�ģ�����������㷨
void CGaussBlur::_ImageGaussiabBlur(BYTE *Data,int widthFrom,int widthTo,int heightFrom,int heightTo,int stride,BYTE *ptrTemp)
{
	int radius = m_nRadius;
	int r,g,b,a,row,col,bytes = 4;
	int templateLength = 2 * radius + 1;

	int *pnWeight = m_pnWeightList;

	__asm
	{
		// col blur
		mov     eax, widthFrom				//	for(col = 0; col < width; col++)
		mov     col, eax 
		jmp     cColJudge 
	cColLoop:
		mov     eax,col 
		add     eax,1 
		mov     col,eax 
	cColJudge:
		mov     eax, widthTo
		cmp     col, eax 
		jge     cColLoopEnd 

		mov     eax, heightFrom			//	for(row = 0; row < height; row++)
		mov     row, eax 
		jmp     cPreAlphaJudge 
	cPreAlphaLoop:
		mov     edx,row 
		add     edx,1 
		mov     row,edx 
	cPreAlphaJudge:
		mov     eax, heightTo
		cmp     row, eax 
		jge     cPreAlphaLoopEnd 

		//pTT = (BYTE *)Data+row*stride +col*bytes; // Ԥ��alpha
		mov         eax, row
		imul        eax, stride
		add         eax, [Data] 
		mov         ecx, col
		imul        ecx, bytes 
		add         eax, ecx 

		mov			ebx, eax       // ָ�����ebx

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

		mov     eax, heightFrom					//	for(row = 0; row < height; row++)
		mov     row, eax 
		jmp     cRowJudge 
	cRowLoop:
		mov     edx,row 
		add     edx,1 
		mov     row,edx 
	cRowJudge:
		mov     eax, heightTo
		cmp     row, eax 
		jge     cRowEnd 
		
		xor     ebx, ebx					// ����
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
 		add     edx, eax					// ��ǰҪ����ģ�����������	
					
		mov     esi, edx					// �����漰�����׸�����ָ��	
		mov		edi, pnWeight				// ģ��
		
		mov     ecx, templateLength			// ģ�峤�ȷ���ecx
		
		mov     eax, radius					// ����ģ��ƫ��������ɨ����ƫ����
		mov		ebx, row
		sub		ebx, heightFrom
		cmp		eax, ebx
		jge		cOffset1
		mov		eax, heightTo
		sub		eax, radius
		sub		eax, heightFrom
		dec		eax
		cmp		eax, ebx
		jl		cOffset2					//(ecx-radius+height-row-1)
		jmp		cOffset3
	cOffset1:						
		add		ecx, ebx                    // ѭ����������
		sub		ecx, eax
		sub     eax, ebx					// ģ��ƫ����
		imul    eax, 4							
		add		edi, eax
		mov		eax, stride					// ����ƫ����
		imul	eax, ebx
		sub		esi, eax	
		jmp		cblurLoop
	cOffset2:
		add		ecx, eax					// ��߽�ֻ����ѭ��������Դ����ָ��
		sub		ecx, ebx
	cOffset3:
		mov		eax, radius					// �м䲿��ֻ����Դ����ָ��
		imul	eax, stride
		sub		esi, eax
	cblurLoop:								// ģ��ѭ��
		movzx   eax, [esi]					// blue
		movzx   edx, [esi+1]				// green
		imul    eax, [edi]					// blue��ģ�����
		imul    edx, [edi]					// green��ģ�����
		add     b,   eax					// blue����ۼ�
		add     g,   edx					// green����ۼ�
		movzx   eax, [esi+2]				// red
		movzx   edx, [esi+3]				// alpha
		imul    eax, [edi]					// red��ģ�����
		imul    edx, [edi]					// alpha��ģ�����
		add     r,   eax					// red����ۼ�
		add     a,   edx					// alpha����ۼ�
		add     edi, 4						// ѭ����������һ��int������ռ4�ֽ�
		add     esi, stride					// ��һ�е�ͬһ��
		loop    cblurLoop					// goto cblurLoop


		mov     eax, row 
 		imul    eax, bytes 
 		add     eax, [ptrTemp]				// ��ʱ����ָ��
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


		mov         eax, heightFrom
		imul        eax, stride
		add         eax, [Data] 
		mov         ecx, col
		imul        ecx, bytes 
		add         eax, ecx 
		mov			edi, eax       // ͼƬ����ָ�����esi

		mov         eax, heightFrom 
		imul        eax, bytes
		add         eax, ptrTemp
		mov         esi, eax		// ��ʱ����ָ��

		mov     eax, heightFrom
		mov     row, eax 
		jmp     cRowCopyJudge 
	cRowCopyLoop:
		mov     edx,row 
		add     edx,1 
		mov     row,edx 
	cRowCopyJudge:
		mov     eax, heightTo
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

	//// row blur

		mov     eax, heightFrom						//		for(row = 0; row < height; row++)
		mov     row, eax 
		jmp     rRowJudge 
	rRowLoop:
		mov     eax,row 
		add     eax,1 
		mov     row,eax 
	rRowJudge:
		mov     eax, heightTo
		cmp     row, eax 
		jge     rRowLoopEnd 

		mov     eax, widthFrom					//	for(col = 0; col < height; col++)
		mov     col, eax 
		jmp     rColJudge 
	rColLoop:
		mov     eax, col 
		add     eax, 1 
		mov     col, eax 
	rColJudge:
		mov     eax, widthTo 
		cmp     col, eax 
		jge     rColEnd 

		xor     ebx, ebx					// ����
		mov     r,   ebx   
		mov     g,	 ebx 
		mov     b,   ebx   
		mov     a,   ebx 		
		
		mov     eax, row 
 		imul    eax, stride 
 		mov     edx, [Data]
 		add     edx, eax 
 		mov     eax, col 
 		imul    eax, bytes 
 		add     edx, eax					// ��ǰҪ����ģ�����������	
		
		mov     esi, edx					// �����漰�����׸�����ָ��	//
		mov		edi, pnWeight				// ģ��
		
		mov     ecx, templateLength			// ģ�峤�ȷ���ecx
		
		mov     eax, radius					// ����ģ��ƫ��������ɨ����ƫ����
		mov		ebx, col
		sub		ebx, widthFrom
		cmp		eax, ebx
		jge		rOffset1
		mov		eax, widthTo
		sub		eax, radius
		sub		eax, widthFrom
		dec		eax
		cmp		eax, ebx
		jl		rOffset2					//(ecx-radius+width-col-1)
		jmp		rOffset3
	rOffset1:						
		add		ecx, ebx                    // ѭ����������
		sub		ecx, eax
		sub     eax, ebx					// ģ��ƫ����
		imul    eax, 4							
		add		edi, eax
		mov		eax, bytes					// ����ƫ����
		imul	eax, ebx
		sub		esi, eax	
		jmp		rblurLoop
	rOffset2:
		add		ecx, eax					// ��߽�ֻ����ѭ��������Դ����ָ��
		sub		ecx, ebx
	rOffset3:
		mov		eax, radius					// �м䲿��ֻ����Դ����ָ��
		imul	eax, bytes
		sub		esi, eax
	rblurLoop:								// ģ��ѭ��
		movzx   eax, [esi]					// blue
		movzx   edx, [esi+1]				// green
		imul    eax, [edi]					// blue��ģ�����
		imul    edx, [edi]					// green��ģ�����
		add     b,   eax					// blue����ۼ�
		add     g,   edx					// green����ۼ�
		movzx   eax, [esi+2]				// red
		movzx   edx, [esi+3]				// alpha
		imul    eax, [edi]					// red��ģ�����
		imul    edx, [edi]					// alpha��ģ�����
		add     r,   eax					// red����ۼ�
		add     a,   edx					// alpha����ۼ�
		add     edi, 4						// ѭ����������һ��int������ռ4�ֽ�
		add     esi, bytes					// �¸�����
		loop    rblurLoop					// goto rblurLoop

		mov     eax, col 
 		imul    eax, bytes 
 		add     eax, [ptrTemp]				// ��ʱ����ָ��
		mov     edi, eax					
	
		mov		eax, b						// ģ������16λ�Ŵ�����˴���С��ȥ
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

		mov         eax, widthFrom						//	pTT = ptrTemp+radius*bytes;
		imul        eax, bytes
		add         eax, ptrTemp
		mov         esi, eax 
		
		mov         eax, row						//	BYTE *ppp = (BYTE *)Data+row*stride+radius*bytes;
		imul        eax, stride
		add         eax, Data
		mov         ecx, widthFrom
		imul        ecx, bytes
		add         eax, ecx 
		mov         edi, eax 
	
		mov     eax, widthFrom								//for(col = 0; col < width; col++)
		mov     col, eax 
		jmp     rSepAlphaJudge 
	rSepAlphaLoop:
		mov     eax,col 
		add     eax,1 
		mov     col,eax 
	rSepAlphaJudge:
		mov     eax, widthTo
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
