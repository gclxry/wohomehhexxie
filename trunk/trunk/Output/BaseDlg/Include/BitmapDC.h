
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

	CSize GetDcSize();
	void Delete();
	void Create(int nWidth, int nHeight);

	HDC GetSafeHdc();
	HBITMAP GetBmpHandle();
	DWORD* GetBits();

private:
	HBITMAP m_hBmp;
	HDC m_hDC;
	BYTE* m_pBits;
	CSize m_DcSize;
};
