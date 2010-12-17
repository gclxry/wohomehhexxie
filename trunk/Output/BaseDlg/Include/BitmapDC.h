
                        /*�q�Шr��~ �衡 �q�Шr �q�Шr
                        �q�Шq�Шr�q�Шr���q�Шr���,�����
                        ,�����,''��~~ ,''~��ᡡ ,''


                                  ("`-''-/").___..--''"`-._
                                   `6_ 6  )   `-.  (     ).`-.__.`)
                                   (_Y_.)'  ._   )  `._ `. ``-..-'
                                 _..`--'_..-_/  /--'_.' ,'
                                (il),-'   (li),'  ((!.-'*/

#pragma once
#include "BaseDlgDefs.h"

class CBitmapDC
{
public:

    CBitmapDC();
    virtual ~CBitmapDC();

	CSize GetDcSize() { return m_DcSize; };
	void Delete();
	void Create(int nWidth, int nHeight, bool bIsAlign = true);

	HDC GetSafeHdc(void) { return m_hDC; };
	HBITMAP GetBmpHandle(void) { return m_hBmp; };
	DWORD* GetBits(void) { return (DWORD *)m_pBits; };

protected:

	HBITMAP m_hBmp;
	HDC m_hDC;
	unsigned char* m_pBits;
	CSize m_DcSize;
};
