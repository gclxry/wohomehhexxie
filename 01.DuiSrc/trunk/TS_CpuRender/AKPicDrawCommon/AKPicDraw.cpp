#include "stdafx.h"

#include "AKPicDraw.h"

#include "AKFile.h"

CAKPicDraw::CAKPicDraw()
{
	m_pData=NULL;

	m_Width=m_Height=0;

	memset(&m_uPenColorMark,255,sizeof(unsigned long));

	m_fAlpha=1.0;

	m_pASC16_Data=NULL;
	m_pHZK16_Data=NULL;

	SetFontHeight(16);
}

CAKPicDraw::~CAKPicDraw()
{
	if(m_pASC16_Data)delete [] m_pASC16_Data;
	if(m_pHZK16_Data)delete [] m_pHZK16_Data;
}

void CAKPicDraw::SetFontHeight(int FontHeight,int RowSpace,int WordSpace)
{
	if(FontHeight<6)m_FontHeight=6;
	else m_FontHeight=FontHeight;

	m_RowSpace=RowSpace;
	m_WordSpace=WordSpace;

	m_CharWidth=m_FontHeight/2;

	m_ChineseWidth=m_FontHeight;
}

bool CAKPicDraw::LoadDefaultFont(char *pASC16_FilePathName,char *pHZK16_FilePathName)
{
	if(m_pASC16_Data)delete [] m_pASC16_Data;
	if(m_pHZK16_Data)delete [] m_pHZK16_Data;

	m_pASC16_Data=NULL;
	m_pHZK16_Data=NULL;

	bool rt;

	CAKFile ASC16_File;
	rt=ASC16_File.Open(pASC16_FilePathName,"rb");
	if(!rt)return false;
	m_pASC16_Data=new unsigned char [4096];
	if(!m_pASC16_Data)return false;
	ASC16_File.Read(m_pASC16_Data,4096);
	ASC16_File.Close();

	CAKFile HZK16_File;
	rt=HZK16_File.Open(pHZK16_FilePathName,"rb");
	if(!rt)return false;
	m_pHZK16_Data=new unsigned char [267616];
	if(!m_pHZK16_Data)return false;
	HZK16_File.Read(m_pHZK16_Data,267616);
	HZK16_File.Close();

	return true;
}

void CAKPicDraw::SelectPic(unsigned char *pData, long Width, long Height)
{
	m_pData=pData;

	m_Width=Width;

	m_Height=Height;
}

void CAKPicDraw::SetAlpha(unsigned char uAlpha)
{
	m_fAlpha=uAlpha;

	m_fAlpha/=255;
}

void CAKPicDraw::SetPixel(long x, long y)
{
	if(x>=0&&x<m_Width&&
		y>=0&&y<m_Height)
	{
		unsigned long index=(y*m_Width+x)*4*sizeof(unsigned char);

		memcpy(&m_pData[index],&m_uPenColorMark,sizeof(unsigned long));
	}
}

void CAKPicDraw::SetPixelEX(long x, long y)
{
	if(m_fAlpha==1.0)SetPixel(x,y);

	if(x>=0&&x<m_Width&&
		y>=0&&y<m_Height)
	{
		unsigned long index=(y*m_Width+x)*4*sizeof(unsigned char);
		unsigned char *pColorMark=(unsigned char *)&m_uPenColorMark;

		m_pData[index]=(unsigned char)(m_pData[index]*(1-m_fAlpha));
		m_pData[index]=(unsigned char)(m_pData[index]+pColorMark[0]*m_fAlpha);

		m_pData[index+1]=(unsigned char)(m_pData[index+1]*(1-m_fAlpha));
		m_pData[index+1]=(unsigned char)(m_pData[index+1]+pColorMark[1]*m_fAlpha);

		m_pData[index+2]=(unsigned char)(m_pData[index+2]*(1-m_fAlpha));
		m_pData[index+2]=(unsigned char)(m_pData[index+2]+pColorMark[2]*m_fAlpha);
	}
}

void CAKPicDraw::Line(long x1, long y1, long x2, long y2)
{
	float dx,dy;
	float lx,ly;
	float x_step,y_step;
	float x,y;
	long i,step_total;

	dx=(float)x2-x1;
	dy=(float)y2-y1;

	if(dx<0)lx=-dx;
	else lx=dx;

	if(dy<0)ly=-dy;
	else ly=dy;

	if(lx>ly)step_total=(long)lx;
	else step_total=(long)ly;

	x_step=dx/step_total;
	y_step=dy/step_total;

	x=(float)x1;
	y=(float)y1;

	for(i=0;i<step_total;++i)
	{
		SetPixel((long)x,(long)y);

		x+=x_step;
		y+=y_step;
	}
}

void CAKPicDraw::SetPenColor(unsigned long uColor)
{
	int r=uColor&0xff;
	int g=uColor>>8&0xff;
	int b=uColor>>16&0xff;

	unsigned char *p=(unsigned char *)&m_uPenColorMark;

	p[0]=b;
	p[1]=g;
	p[2]=r;
	p[3]=0;
}

void CAKPicDraw::SetPenColor(unsigned char r,unsigned char g,unsigned char b)
{
	unsigned char *p=(unsigned char *)&m_uPenColorMark;

	p[0]=b;
	p[1]=g;
	p[2]=r;
	p[3]=0;
}

void CAKPicDraw::FillRect(long x1,long y1,long x2,long y2)
{
	long t;
	if(x1>x2)
	{
		t=x1;
		x1=x2;
		x2=t;
	}
	if(y1>y2)
	{
		t=y1;
		y1=y2;
		y2=t;
	}
	for(;y1<=y2;++y1)
	{
		for(t=x1;t<=x2;++t)
		{
			SetPixel(t,y1);
		}
	}
}

void CAKPicDraw::FillRectEX(long x1,long y1,long x2,long y2)
{
	if(m_fAlpha==1.0)
	{
		FillRect(x1,y1,x2,y2);
		return;
	}

	long t;
	if(x1>x2)
	{
		t=x1;
		x1=x2;
		x2=t;
	}
	if(y1>y2)
	{
		t=y1;
		y1=y2;
		y2=t;
	}
	for(;y1<=y2;++y1)
	{
		for(t=x1;t<=x2;++t)
		{
			SetPixelEX(t,y1);
		}
	}
}

void CAKPicDraw::Fill(long x, long y, unsigned long uBakcColor)
{
	if(x>=0&&x<m_Width&&
		y>=0&&y<m_Height)
	{
		long *pPixel;

		pPixel=new long[2];
		pPixel[0]=x;
		pPixel[1]=y;

		//入栈
		m_PixelList.AddTail(pPixel);

		AK_POS_PTR pos2;

		AK_POS_PTR pos=m_PixelList.GetHeadPos();

		long xx,yy;
		
		unsigned long index;

		while(pos)
		{
			pos2=pos;

			//获取一个点
			pPixel=(long *)m_PixelList.GetValue(pos);
			xx=pPixel[0];
			yy=pPixel[1];
			
			//如果点在范围内
			if(xx>=0&&xx<m_Width&&
				yy>=0&&yy<m_Height)
			{
				index=(yy*m_Width+xx)*4*sizeof(unsigned char);

				if((!ColorCmp((unsigned char *)&uBakcColor,
					(unsigned char *)&m_uPenColorMark))&&//如果填充色和底色不相同
					ColorCmp((unsigned char *)&uBakcColor,
					&m_pData[index]))//如果填充底色和(x,y)起始处原来的颜色相同
				{
					//画点
					SetPixel(xx,yy);
					
					pPixel=new long[2];
					pPixel[0]=xx+1;
					pPixel[1]=yy;
					
					//入栈
					m_PixelList.AddTail(pPixel);

					pPixel=new long[2];
					pPixel[0]=xx-1;
					pPixel[1]=yy;
					
					//入栈
					m_PixelList.AddTail(pPixel);

					pPixel=new long[2];
					pPixel[0]=xx;
					pPixel[1]=yy+1;
					
					//入栈
					m_PixelList.AddTail(pPixel);

					pPixel=new long[2];
					pPixel[0]=xx;
					pPixel[1]=yy-1;
					
					//入栈
					m_PixelList.AddTail(pPixel);
				}
			}
			
			//下一个
			m_PixelList.Next(&pos);
			
			//删除这个点
			m_PixelList.Remove(pos2);
		}
	}
}

bool CAKPicDraw::ColorCmp(unsigned char *pColor1, unsigned char *pColor2)
{
	if(pColor1[0]==pColor2[0]&&
		pColor1[1]==pColor2[1]&&
		pColor1[2]==pColor2[2])
	{
		return true;
	}
	else
	{
		return false;
	}
}

unsigned long CAKPicDraw::GetPixel(long x, long y)
{
	if(x>=0&&x<m_Width&&
		y>=0&&y<m_Height)
	{
		unsigned long index=(y*m_Width+x)*4*sizeof(unsigned char);

		unsigned long *pColor=(unsigned long *)&m_pData[index];

		return (*pColor);
	}
	else
		return 0;
}

unsigned long CAKPicDraw::GetColorRefPixel(long x, long y)
{
	if(x>=0&&x<m_Width&&
		y>=0&&y<m_Height)
	{
		unsigned long index=(y*m_Width+x)*4*sizeof(unsigned char);

		unsigned long ColorRef;

		unsigned char *pColor=(unsigned char *)&ColorRef;

		pColor[0]=m_pData[index+2];//b
		pColor[1]=m_pData[index+1];//g
		pColor[2]=m_pData[index];//r
		pColor[3]=0;

		return ColorRef;
	}
	else
		return 0;
}

void CAKPicDraw::FillEasy(long x, long y)
{
	Fill(x,y,GetPixel(x,y));
}

void CAKPicDraw::DrawBmp(long x,long y,
						 unsigned char *pData,long w,long h,unsigned long uBackColor)
{
	int r=uBackColor&0xff;
	int g=uBackColor>>8&0xff;
	int b=uBackColor>>16&0xff;

	//将uBackColor转换为内存格式
	unsigned char *p=(unsigned char *)&uBackColor;

	p[0]=b;
	p[1]=g;
	p[2]=r;
	p[3]=0;

	//
	long xx;
	long xb=x;
	if(xb<0)xb=0;
	if(xb>=m_Width)xb=m_Width-1;

	long xm=x+w;
	if(xm<0)xm=0;
	if(xm>=m_Width)xm=m_Width-1;

	long yy=y;
	if(yy<0)yy=0;
	if(yy>=m_Height)yy=m_Height-1;

	long ym=y+h;
	if(ym<0)ym=0;
	if(ym>=m_Height)ym=m_Height-1;

	if(xb==xm)return;
	if(yy==ym)return;

	long index1,index2;

	unsigned long *puCurColor;

	unsigned char *pData1,*pData2;

	for(;yy<ym;++yy)
	{
		//画板
		index1=(yy*m_Width+xb)*4*sizeof(unsigned char);
		pData1=&m_pData[index1];
		
		//位图
		index2=((yy-y)*w+(xb-x))*4*sizeof(unsigned char);
		pData2=&pData[index2];

		for(xx=xb;xx<xm;++xx)
		{
			//取位图当前点颜色(内存格式)
			puCurColor=(unsigned long *)pData2;

			//如果是透明色
			if((*puCurColor)==uBackColor)
			{
			}
			else//如果不是透明色
			{
				memcpy(pData1,pData2,4*sizeof(unsigned char));
			}

			pData1+=4;
			pData2+=4;
		}
	}
}


void CAKPicDraw::DrawBmp(long x,long y,
						 unsigned char *pData,long w,long h)
{
	long xb=x;
	if(xb<0)xb=0;
	if(xb>=m_Width)xb=m_Width-1;

	long xm=x+w;
	if(xm<0)xm=0;
	if(xm>=m_Width)xm=m_Width-1;

	long yy=y;
	if(yy<0)yy=0;
	if(yy>=m_Height)yy=m_Height-1;

	long ym=y+h;
	if(ym<0)ym=0;
	if(ym>=m_Height)ym=m_Height-1;

	if(xb==xm)return;
	if(yy==ym)return;

	long index1,index2;

	unsigned char *pData1,*pData2;

	for(;yy<ym;++yy)
	{
		//画板
		index1=(yy*m_Width+xb)*4*sizeof(unsigned char);
		pData1=&m_pData[index1];
		
		//位图
		index2=((yy-y)*w+(xb-x))*4*sizeof(unsigned char);
		pData2=&pData[index2];

		memcpy(pData1,pData2,4*(xm-xb)*sizeof(unsigned char));
	}
}

void CAKPicDraw::DrawBmpAlpha(long x,long y,
						 unsigned char *pData,long w,long h,
						 unsigned char uAlpha)
{
	long xb=x;
	if(xb<0)xb=0;
	if(xb>=m_Width)xb=m_Width-1;

	long xm=x+w;
	if(xm<0)xm=0;
	if(xm>=m_Width)xm=m_Width-1;

	long yy=y;
	if(yy<0)yy=0;
	if(yy>=m_Height)yy=m_Height-1;

	long ym=y+h;
	if(ym<0)ym=0;
	if(ym>=m_Height)ym=m_Height-1;

	if(xb==xm)return;
	if(yy==ym)return;

	long index1,index2;

	unsigned char *pData1,*pData2;

	unsigned long i;
	unsigned long j=xm-xb;

	int r1,g1,b1;
	int r2,g2,b2;

	float fAlpha=uAlpha;
	fAlpha/=255.0;

	for(;yy<ym;++yy)
	{
		//画板
		index1=(yy*m_Width+xb)*4*sizeof(unsigned char);
		pData1=&m_pData[index1];
		
		//位图
		index2=((yy-y)*w+(xb-x))*4*sizeof(unsigned char);
		pData2=&pData[index2];

		if(fAlpha>=1)
		{
			memcpy(pData1,pData2,4*(xm-xb)*sizeof(unsigned char));
		}
		else
		{
			for(i=0;i<j;++i)
			{
				r1=(int)(pData1[2]*(1-fAlpha));
				g1=(int)(pData1[1]*(1-fAlpha));
				b1=(int)(pData1[0]*(1-fAlpha));

				r2=(int)(pData2[2]*fAlpha);
				g2=(int)(pData2[1]*fAlpha);
				b2=(int)(pData2[0]*fAlpha);

				pData1[2]=(r1+r2);
				pData1[1]=(g1+g2);
				pData1[0]=(b1+b2);

				//
				pData2+=4;
				pData1+=4;
			}
		}

	}
}

void CAKPicDraw::DrawBmpEX(long x,long y,
                           unsigned char *pData,long w,long h,unsigned long uBackColor,
                           bool IsXReverse,//动作是否按X轴反向显示
                           bool IsYReverse//动作是否按Y轴反向显示
                           )
{
	int r=uBackColor&0xff;
	int g=uBackColor>>8&0xff;
	int b=uBackColor>>16&0xff;

	//将uBackColor转换为内存格式
	unsigned char *p=(unsigned char *)&uBackColor;

	p[0]=b;
	p[1]=g;
	p[2]=r;
	p[3]=0;

	//
	long xx;
	long xb=x;
	if(xb<0)xb=0;
	if(xb>=m_Width)xb=m_Width-1;

	long xm=x+w;
	if(xm<0)xm=0;
	if(xm>=m_Width)xm=m_Width-1;

	long yy=y;
	if(yy<0)yy=0;
	if(yy>=m_Height)yy=m_Height-1;

	long ym=y+h;
	if(ym<0)ym=0;
	if(ym>=m_Height)ym=m_Height-1;

	if(xb==xm)return;
	if(yy==ym)return;

	long index1,index2;

	unsigned long *puCurColor;

	unsigned char *pData1,*pData2;

	for(;yy<ym;++yy)
	{
		//画板
        index1=(yy*m_Width+xb)*4*sizeof(unsigned char);

		pData1=&m_pData[index1];

        if(!IsXReverse)//X正
        {

            //位图
            if(!IsYReverse)//Y正
            {
                index2=((yy-y)*w+(xb-x))*4*sizeof(unsigned char);
            }
            else//Y反
            {
                index2=((h-(yy-y)-1)*w+(xb-x))*4*sizeof(unsigned char);
            }
            pData2=&pData[index2];

            for(xx=xb;xx<xm;++xx)
            {
                //取位图当前点颜色(内存格式)
                puCurColor=(unsigned long *)pData2;

                //如果是透明色
                if((*puCurColor)==uBackColor)
                {
                }
                else//如果不是透明色
                {
                    memcpy(pData1,pData2,4*sizeof(unsigned char));
                }


                pData1+=4;

                pData2+=4;
            }

        }
        else//X反
        {

            //位图
            if(!IsYReverse)//Y正
            {
                index2=((yy-y)*w+((w-1)-(xb-x)))*4*sizeof(unsigned char);
            }
            else//Y反
            {
                //调试
                index2=((h-(yy-y)-1)*w+(xb-x)+w-1)*4*sizeof(unsigned char);
            }
            pData2=&pData[index2];

            for(xx=xm-1;xx>=xb;--xx)
            {
                //取位图当前点颜色(内存格式)
                puCurColor=(unsigned long *)pData2;

                //如果是透明色
                if((*puCurColor)==uBackColor)
                {
                }
                else//如果不是透明色
                {
                    memcpy(pData1,pData2,4*sizeof(unsigned char));
                }


                pData1+=4;
                
                pData2-=4;

            }

        }

    }
}

void CAKPicDraw::DrawBmpEXAlpha(long x,long y,
                           unsigned char *pData,long w,long h,unsigned long uBackColor,
                           bool IsXReverse,//动作是否按X轴反向显示
                           bool IsYReverse//动作是否按Y轴反向显示
                           )
{
	if(m_fAlpha==1.0)
	{
		DrawBmpEX(x,y,pData,w,h,uBackColor,IsXReverse,IsYReverse);

		return;
	}

	int r=uBackColor&0xff;
	int g=uBackColor>>8&0xff;
	int b=uBackColor>>16&0xff;

	//将uBackColor转换为内存格式
	unsigned char *p=(unsigned char *)&uBackColor;

	p[0]=b;
	p[1]=g;
	p[2]=r;
	p[3]=0;

	long xb=x;
	if(xb<0)xb=0;
	if(xb>=m_Width)xb=m_Width-1;
	long xx=xb;

	long xm=x+w;
	if(xm<0)xm=0;
	if(xm>=m_Width)xm=m_Width-1;

	long yy=y;
	if(yy<0)yy=0;
	if(yy>=m_Height)yy=m_Height-1;
	//long yb=yy;

	long ym=y+h;
	if(ym<0)ym=0;
	if(ym>=m_Height)ym=m_Height-1;

	if(xb==xm)return;
	if(yy==ym)return;

	long index1,index2;

	unsigned long *puCurColor;

	unsigned char *pData1,*pData2;

	for(;yy<ym;++yy)
	{
		//画板
        index1=(yy*m_Width+xb)*4*sizeof(unsigned char);

		pData1=&m_pData[index1];

        if(!IsXReverse)//X正
        {

            //位图
            if(!IsYReverse)//Y正
            {
                index2=((yy-y)*w+(xb-x))*4*sizeof(unsigned char);
            }
            else//Y反
            {
                index2=((h-(yy-y)-1)*w+(xb-x))*4*sizeof(unsigned char);
            }
            pData2=&pData[index2];

            for(xx=xb;xx<xm;++xx)
            {
                //取位图当前点颜色(内存格式)
                puCurColor=(unsigned long *)pData2;

                //如果是透明色
                if((*puCurColor)==uBackColor)
                {
                }
                else//如果不是透明色
                {
                    //memcpy(pData1,pData2,4*sizeof(unsigned char));

					unsigned long index=(y*m_Width+x)*4*sizeof(unsigned char);
					unsigned char *pColorMark=pData2;

					pData1[0]=(unsigned char)(pData1[0]*(1-m_fAlpha));
					pData1[0]=(unsigned char)(pData1[0]+pColorMark[0]*m_fAlpha);

					pData1[1]=(unsigned char)(pData1[1]*(1-m_fAlpha));
					pData1[1]=(unsigned char)(pData1[1]+pColorMark[1]*m_fAlpha);

					pData1[2]=(unsigned char)(pData1[2]*(1-m_fAlpha));
					pData1[2]=(unsigned char)(pData1[2]+pColorMark[2]*m_fAlpha);
                }


                pData1+=4;

                pData2+=4;
            }

        }
        else//X反
        {
            //位图
            if(!IsYReverse)//Y正
            {
                index2=((yy-y)*w+(w-1)-(xb-x))*4*sizeof(unsigned char);
            }
            else//Y反
            {
                //调试
                index2=((h-(yy-y)-1)*w+(xb-x)+w-1)*4*sizeof(unsigned char);
            }
            pData2=&pData[index2];

            for(xx=xm-1;xx>=xb;--xx)
            {
                
                
                //取位图当前点颜色(内存格式)
                puCurColor=(unsigned long *)pData2;

				//如果是透明色
				if((*puCurColor)==uBackColor)
				{
				}
				else//如果不是透明色
				{
					//memcpy(pData1,pData2,4*sizeof(unsigned char));

					unsigned long index=(y*m_Width+x)*4*sizeof(unsigned char);
					unsigned char *pColorMark=pData2;

					pData1[0]=(unsigned char)(pData1[0]*(1-m_fAlpha));
					pData1[0]=(unsigned char)(pData1[0]+pColorMark[0]*m_fAlpha);

					pData1[1]=(unsigned char)(pData1[1]*(1-m_fAlpha));
					pData1[1]=(unsigned char)(pData1[1]+pColorMark[1]*m_fAlpha);

					pData1[2]=(unsigned char)(pData1[2]*(1-m_fAlpha));
					pData1[2]=(unsigned char)(pData1[2]+pColorMark[2]*m_fAlpha);
				}


                pData1+=4;
                
                pData2-=4;

            }

        }

    }
}

void CAKPicDraw::MoveTo(long x,long y)
{
	m_CurX=x;

	m_CurY=y;
}

void CAKPicDraw::LineTo(long x,long y)
{
	Line(m_CurX,m_CurY,x,y);
	
	MoveTo(x,y);
}

void CAKPicDraw::GetPixel4Dir(long x,long y,unsigned char *pColor)
{
    unsigned long uColorList[4];
    uColorList[0]=GetPixel(x-1,y);
    uColorList[1]=GetPixel(x+1,y);
    uColorList[2]=GetPixel(x,y-1);
    uColorList[3]=GetPixel(x,y+1);

    unsigned long uColor=GetColorListAverage(uColorList,4);

    memcpy(pColor,&uColor,sizeof(unsigned long));
}

unsigned long CAKPicDraw::GetColorListAverage(unsigned long *pColorList,unsigned long uCount)
{
    unsigned long a=0;
    unsigned long r=0;
    unsigned long g=0;
    unsigned long b=0;

    unsigned char *pColor;
    unsigned long uColor;
    
    unsigned long i;

    for(i=0;i<uCount;++i)
    {
        pColor=(unsigned char *)&pColorList[i];

        b+=pColor[0];
        g+=pColor[1];
        r+=pColor[2];
        a+=pColor[3];
    }

    pColor=(unsigned char *)&uColor;

    pColor[0]=(unsigned char)(b/uCount);
    pColor[1]=(unsigned char)(g/uCount);
    pColor[2]=(unsigned char)(r/uCount);
    pColor[3]=(unsigned char)(a/uCount);

    return uColor;

}

void CAKPicDraw::Line(long x1, long y1, long x2, long y2,int LineWidth)
{
	if(LineWidth<=0)LineWidth=1;

	float dx,dy;
	float lx,ly;
	float x_step,y_step;
	float x,y;
	long i,step_total;

	dx=(float)x2-x1;
	dy=(float)y2-y1;

	if(dx<0)lx=-dx;
	else lx=dx;

	if(dy<0)ly=-dy;
	else ly=dy;

	if(lx>ly)step_total=(long)lx;
	else step_total=(long)ly;

	x_step=dx/step_total;
	y_step=dy/step_total;

	int j;

	if(LineWidth>2)
	{
		LineWidth-=2;

		int n=(LineWidth)/2;
		for(j=0;j<LineWidth;++j)
		{
			x=(float)x1;
			y=(float)y1;

			x+=y_step*(j-n);
			y-=x_step*(j-n);
			for(i=0;i<step_total;++i)
			{
				SetPixel((long)x,(long)y);

				//在周围补上4个像素,避免线体像素漏画的现象,但这样会导致线宽增加2,所以一开始就把LineWidth减去2
				SetPixel((long)(x+0.5),(long)y);
				SetPixel((long)(x-0.5),(long)y);
				SetPixel((long)x,(long)(y+0.5));
				SetPixel((long)x,(long)(y-0.5));
				x+=x_step;
				y+=y_step;
			}

		}
	}
	else
	{
		x=(float)x1;
		y=(float)y1;

		if(LineWidth==1)
		{
			for(j=0;j<LineWidth;++j)
			{
				for(i=0;i<step_total;++i)
				{
					SetPixel((long)x,(long)y);
					x+=x_step;
					y+=y_step;
				}

			}
		}
		else
		{
			float a=x_step;
			if(a<0)a=-a;
			float b=y_step;
			if(b<0)b=-b;

			if(a>b)
			{
				b=1;
				a=0;
			}
			else
			{
				a=1;
				b=0;
			}

			for(i=0;i<step_total;++i)
			{
				SetPixel((long)x,(long)y);
				SetPixel((long)(x+a),(long)(y+b));
				x+=x_step;
				y+=y_step;
			}
		}
	}


}

void CAKPicDraw::LineEX(long x1, long y1, long x2, long y2,int LineWidth)
{
	if(LineWidth<=0)LineWidth=1;

	float dx,dy;
	float lx,ly;
	float x_step,y_step;
	float x,y;
	long i,step_total;

	dx=(float)x2-x1;
	dy=(float)y2-y1;

	if(dx<0)lx=-dx;
	else lx=dx;

	if(dy<0)ly=-dy;
	else ly=dy;

	if(lx>ly)step_total=(long)lx;
	else step_total=(long)ly;

	x_step=dx/step_total;
	y_step=dy/step_total;

	int j;

	if(LineWidth>2)
	{
		LineWidth-=2;

		int n=(LineWidth)/2;
		for(j=0;j<LineWidth;++j)
		{
			x=(float)x1;
			y=(float)y1;

			x+=y_step*(j-n);
			y-=x_step*(j-n);
			for(i=0;i<step_total;++i)
			{
				SetPixelEX((long)x,(long)y);

				//在周围补上4个像素,避免线体像素漏画的现象,但这样会导致线宽增加2,所以一开始就把LineWidth减去2
				SetPixelEX((long)(x+0.5),(long)y);
				SetPixelEX((long)(x-0.5),(long)y);
				SetPixelEX((long)x,(long)(y+0.5));
				SetPixelEX((long)x,(long)(y-0.5));
				x+=x_step;
				y+=y_step;
			}

		}
	}
	else
	{
		x=(float)x1;
		y=(float)y1;

		if(LineWidth==1)
		{
			for(j=0;j<LineWidth;++j)
			{
				for(i=0;i<step_total;++i)
				{
					SetPixelEX((long)x,(long)y);
					x+=x_step;
					y+=y_step;
				}

			}
		}
		else
		{
			float a=x_step;
			if(a<0)a=-a;
			float b=y_step;
			if(b<0)b=-b;

			if(a>b)
			{
				b=1;
				a=0;
			}
			else
			{
				a=1;
				b=0;
			}

			for(i=0;i<step_total;++i)
			{
				SetPixelEX((long)x,(long)y);
				SetPixelEX((long)(x+a),(long)(y+b));
				x+=x_step;
				y+=y_step;
			}
		}
	}


}

void CAKPicDraw::LineTo(long x,long y,int LineWidth)
{
	Line(m_CurX,m_CurY,x,y,LineWidth);
	
	MoveTo(x,y);
}

void CAKPicDraw::LineToEX(long x,long y,int LineWidth)
{
	LineEX(m_CurX,m_CurY,x,y,LineWidth);
	
	MoveTo(x,y);
}

void CAKPicDraw::CharOut(long x,long y,char ch)
{
	if(!m_pASC16_Data)return;

	if(m_FontHeight<16)//按小比例输出
	{
		unsigned char ch2=ch;
		long i,j;
		unsigned char mark;
		long off=((long)(ch2))*((long)16);

		float ii,jj;
		float m=((float)m_CharWidth)/8;
		float n=((float)m_FontHeight)/16;

		for(j=0,jj=0;j<16;++j,jj+=n)
		{
			//取行字模
			mark=m_pASC16_Data[off];

			for(i=0,ii=(float)m_CharWidth-1;i<8;++i,ii-=n)
			{
				if(((mark>>i)&0x1)==1)
				{
					SetPixel(x+(long)ii,y+(long)jj);
				}
			}

			++off;
		}
	}
	if(m_FontHeight==16)//原大输出
	{
		unsigned char ch2=ch;
		long i,j;
		unsigned char mark;
		long off=((long)(ch2))*((long)16);

		for(j=0;j<16;++j)
		{
			//取行字模
			mark=m_pASC16_Data[off];

			for(i=0;i<8;++i)
			{
				if(((mark>>i)&0x1)==1)
				{
					SetPixel(x+7-i,y+j);
				}
			}

			++off;
		}
	}
	if(m_FontHeight>16)//按大比例输出
	{
		unsigned char ch2=ch;
		long i,j;
		float ii;
		unsigned char mark;
		float off=((float)(ch2))*((float)16);

		float Dh=16/((float)m_FontHeight);
		float Dw=8/((float)m_CharWidth);

		for(j=0;j<m_FontHeight;++j)
		{
			//取行字模
			mark=m_pASC16_Data[(long)off];

			for(i=0,ii=0;i<m_CharWidth;++i)
			{
				if(((mark>>((long)ii))&0x1)==1)
				{
					SetPixel(x+m_CharWidth-1-i,y+j);
				}

				ii+=Dw;
			}

			off+=Dh;
		}
	}

}
void CAKPicDraw::CharOutEX(long x,long y,char ch)
{
	if(m_fAlpha==1.0)
	{
		CharOut(x,y,ch);
		return;
	}

	if(!m_pASC16_Data)return;

	if(m_FontHeight<16)//按小比例输出
	{
		unsigned char ch2=ch;
		long i,j;
		unsigned char mark;
		long off=((long)(ch2))*((long)16);

		float ii,jj;
		float m=((float)m_CharWidth)/8;
		float n=((float)m_FontHeight)/16;

		for(j=0,jj=0;j<16;++j,jj+=n)
		{
			//取行字模
			mark=m_pASC16_Data[off];

			for(i=0,ii=(float)m_CharWidth-1;i<8;++i,ii-=n)
			{
				if(((mark>>i)&0x1)==1)
				{
					SetPixelEX(x+(long)ii,y+(long)jj);
				}
			}

			++off;
		}
	}
	if(m_FontHeight==16)//原大输出
	{
		unsigned char ch2=ch;
		long i,j;
		unsigned char mark;
		long off=((long)(ch2))*((long)16);

		for(j=0;j<16;++j)
		{
			//取行字模
			mark=m_pASC16_Data[off];

			for(i=0;i<8;++i)
			{
				if(((mark>>i)&0x1)==1)
				{
					SetPixelEX(x+7-i,y+j);
				}
			}

			++off;
		}
	}
	if(m_FontHeight>16)//按大比例输出
	{
		unsigned char ch2=ch;
		long i,j;
		float ii;
		unsigned char mark;
		float off=((float)(ch2))*((float)16);

		float Dh=16/((float)m_FontHeight);
		float Dw=8/((float)m_CharWidth);

		for(j=0;j<m_FontHeight;++j)
		{
			//取行字模
			mark=m_pASC16_Data[(long)off];

			for(i=0,ii=0;i<m_CharWidth;++i)
			{
				if(((mark>>((long)ii))&0x1)==1)
				{
					SetPixelEX(x+m_CharWidth-1-i,y+j);
				}

				ii+=Dw;
			}

			off+=Dh;
		}
	}

}

void CAKPicDraw::ChineseOut(long x,long y,char *pChinese)
{
	if(!m_pHZK16_Data)return;

	unsigned char *pChinese2=(unsigned char *)pChinese;

	if(m_FontHeight<16)//按小比例输出
	{
		long i,j;
		unsigned char mark[2];
		long off=((((long)pChinese2[0])-161L)*94L+((long)pChinese2[1])-161L)*32L;

		float n=((float)m_FontHeight)/16;
		float ii;
		float jj;

		for(j=0,jj=0;j<16;++j,jj+=n)
		{
			//取行字模
			memcpy(mark,&m_pHZK16_Data[off],2);
			
			for(i=0,ii=(float)m_ChineseWidth-1;i<8;++i,ii-=n)
			{
				if(((mark[1]>>i)&0x1)==1)
				{
					SetPixel(x+(long)ii,y+(long)jj);
				}
			}
			
			for(i=0;i<8;++i,ii-=n)
			{
				if(((mark[0]>>i)&0x1)==1)
				{
					SetPixel(x+(long)ii,y+(long)jj);
				}
			}

			off+=2;
		}
	}
	if(m_FontHeight==16)//原大输出
	{
		long i,ii,j;
		unsigned char mark[2];
		long off=((((long)pChinese2[0])-161L)*94L+((long)pChinese2[1])-161L)*32L;

		for(j=0;j<16;++j)
		{
			//取行字模
			memcpy(mark,&m_pHZK16_Data[off],2);
			
			for(i=0,ii=8-1;i<8;++i,--ii)
			{
				if(((mark[0]>>i)&0x1)==1)
				{
					SetPixel(x+ii,y+j);
				}
			}

			for(i=0,ii=16-1;i<8;++i,--ii)
			{
				if(((mark[1]>>i)&0x1)==1)
				{
					SetPixel(x+ii,y+j);
				}
			}
			
			off+=2;
		}
	}
	if(m_FontHeight>16)//按大比例输出
	{
		long i,ii,j;
		unsigned char mark[2];
		long off=((((long)pChinese2[0])-161L)*94L+((long)pChinese2[1])-161L)*32L;

		int n=m_ChineseWidth/2;
		float iii;

		float Dh=16/((float)m_FontHeight);
		float Dw=16/((float)m_ChineseWidth);

		float t=0;

		for(j=0;j<m_FontHeight;++j)
		{
			//取行字模
			memcpy(mark,&m_pHZK16_Data[off+((long)t)+((long)t)],2);

			iii=0;
			for(i=0,ii=n-1;i<n;++i,--ii)
			{
				if(((mark[0]>>((long)iii))&0x1)==1)
				{
					SetPixel(x+ii,y+j);
				}

				iii+=Dw;
			}

			iii=0;
			for(i=0,ii=m_ChineseWidth-1;i<n;++i,--ii)
			{
				if(((mark[1]>>((long)iii))&0x1)==1)
				{
					SetPixel(x+ii,y+j);
				}
				
				iii+=Dw;
			}
			
			t+=Dh;
		}
	}

}

void CAKPicDraw::ChineseOutEX(long x,long y,char *pChinese)
{
	if(m_fAlpha==1.0)
	{
		ChineseOut(x,y,pChinese);
		return;
	}

	if(!m_pHZK16_Data)return;

	unsigned char *pChinese2=(unsigned char *)pChinese;

	if(m_FontHeight<16)//按小比例输出
	{
		long i,j;
		unsigned char mark[2];
		long off=((((long)pChinese2[0])-161L)*94L+((long)pChinese2[1])-161L)*32L;

		float n=((float)m_FontHeight)/16;
		float ii;
		float jj;

		for(j=0,jj=0;j<16;++j,jj+=n)
		{
			//取行字模
			memcpy(mark,&m_pHZK16_Data[off],2);
			
			for(i=0,ii=(float)m_ChineseWidth-1;i<8;++i,ii-=n)
			{
				if(((mark[1]>>i)&0x1)==1)
				{
					SetPixelEX(x+(long)ii,y+(long)jj);
				}
			}
			
			for(i=0;i<8;++i,ii-=n)
			{
				if(((mark[0]>>i)&0x1)==1)
				{
					SetPixelEX(x+(long)ii,y+(long)jj);
				}
			}

			off+=2;
		}
	}
	if(m_FontHeight==16)//原大输出
	{
		long i,ii,j;
		unsigned char mark[2];
		long off=((((long)pChinese2[0])-161L)*94L+((long)pChinese2[1])-161L)*32L;

		for(j=0;j<16;++j)
		{
			//取行字模
			memcpy(mark,&m_pHZK16_Data[off],2);
			
			for(i=0,ii=8-1;i<8;++i,--ii)
			{
				if(((mark[0]>>i)&0x1)==1)
				{
					SetPixelEX(x+ii,y+j);
				}
			}

			for(i=0,ii=16-1;i<8;++i,--ii)
			{
				if(((mark[1]>>i)&0x1)==1)
				{
					SetPixelEX(x+ii,y+j);
				}
			}
			
			off+=2;
		}
	}
	if(m_FontHeight>16)//按大比例输出
	{
		long i,ii,j;
		unsigned char mark[2];
		long off=((((long)pChinese2[0])-161L)*94L+((long)pChinese2[1])-161L)*32L;

		int n=m_ChineseWidth/2;
		float iii;

		float Dh=16/((float)m_FontHeight);
		float Dw=16/((float)m_ChineseWidth);

		float t=0;

		for(j=0;j<m_FontHeight;++j)
		{
			//取行字模
			memcpy(mark,&m_pHZK16_Data[off+((long)t)+((long)t)],2);

			iii=0;
			for(i=0,ii=n-1;i<n;++i,--ii)
			{
				if(((mark[0]>>((long)iii))&0x1)==1)
				{
					SetPixelEX(x+ii,y+j);
				}

				iii+=Dw;
			}

			iii=0;
			for(i=0,ii=m_ChineseWidth-1;i<n;++i,--ii)
			{
				if(((mark[1]>>((long)iii))&0x1)==1)
				{
					SetPixelEX(x+ii,y+j);
				}
				
				iii+=Dw;
			}
			
			t+=Dh;
		}
	}

}

void CAKPicDraw::TextOut(long x,long y,char *pStr)
{
	unsigned char *str=(unsigned char *)pStr;

	long i;

	if(m_fAlpha==1.0)
	{
		for(i=0;str[i]!='\0';++i)
		{
			if(str[i]>=161&&str[i+1]>=161)/*显示汉字*/
			{
				ChineseOut(x,y,(char *)&str[i]);
				x+=m_ChineseWidth+m_WordSpace;
				++i;
			}
			else//显示ASCII字符
			{
				CharOut(x,y,str[i]);
				x+=m_CharWidth+m_WordSpace;
			}
		}
	}
	else
	{
		for(i=0;str[i]!='\0';++i)
		{
			if(str[i]>=161&&str[i+1]>=161)/*显示汉字*/
			{
				ChineseOutEX(x,y,(char *)&str[i]);
				x+=m_ChineseWidth+m_WordSpace;
				++i;
			}
			else//显示ASCII字符
			{
				CharOutEX(x,y,str[i]);
				x+=m_CharWidth+m_WordSpace;
			}
		}
	}
}

void CAKPicDraw::TextOut(long x,long y,char *pStr,long RectWidth)
{
	//如果显示区域宽比显示汉字的宽还要小,就不能显示了
	if(RectWidth<m_ChineseWidth)return;

	//当前占用行宽度
	long CurWidth=0;

	long x_base=x;

	unsigned char *str=(unsigned char *)pStr;

	long i;

	if(m_fAlpha==1.0)
	{
		for(i=0;str[i]!='\0';++i)
		{
			if(str[i]>=161&&str[i+1]>=161)/*显示汉字*/
			{
				//超出最大行宽,自动换行
				if((CurWidth+m_ChineseWidth)>RectWidth)
				{
					x=x_base;
					y+=m_FontHeight+m_RowSpace;
					CurWidth=0;
				}

				ChineseOut(x,y,(char *)&str[i]);
				x+=m_ChineseWidth+m_WordSpace;
				++i;

				//占用行宽递增
				CurWidth+=m_ChineseWidth+m_WordSpace;
			}
			else//显示ASCII字符
			{
				switch(str[i])
				{
				case '\r'://换行
					{
						y+=m_FontHeight+m_RowSpace;
						CurWidth=0;
						break;
					}
				case '\n'://回车
					{
						x=x_base;
						CurWidth=0;
						break;
					}
				default:
					{
						//超出最大行宽,自动换行
						if((CurWidth+m_CharWidth)>RectWidth)
						{
							x=x_base;
							y+=m_FontHeight+m_RowSpace;
							CurWidth=0;
						}

						CharOut(x,y,str[i]);
						x+=m_CharWidth+m_WordSpace;

						//占用行宽递增
						CurWidth+=m_CharWidth+m_WordSpace;

						break;
					}
				}
			}

		}
	}
	else
	{
		for(i=0;str[i]!='\0';++i)
		{
			if(str[i]>=161&&str[i+1]>=161)/*显示汉字*/
			{
				//超出最大行宽,自动换行
				if((CurWidth+m_ChineseWidth)>RectWidth)
				{
					x=x_base;
					y+=m_FontHeight+m_RowSpace;
					CurWidth=0;
				}

				ChineseOutEX(x,y,(char *)&str[i]);
				x+=m_ChineseWidth+m_WordSpace;
				++i;

				//占用行宽递增
				CurWidth+=m_ChineseWidth+m_WordSpace;
			}
			else//显示ASCII字符
			{
				switch(str[i])
				{
				case '\r'://换行
					{
						y+=m_FontHeight+m_RowSpace;
						CurWidth=0;
						break;
					}
				case '\n'://回车
					{
						x=x_base;
						CurWidth=0;
						break;
					}
				default:
					{
						//超出最大行宽,自动换行
						if((CurWidth+m_CharWidth)>RectWidth)
						{
							x=x_base;
							y+=m_FontHeight+m_RowSpace;
							CurWidth=0;
						}

						CharOutEX(x,y,str[i]);
						x+=m_CharWidth+m_WordSpace;

						//占用行宽递增
						CurWidth+=m_CharWidth+m_WordSpace;

						break;
					}
				}
			}

		}
	}
}
