
#include "stdafx.h"
#include "AK3DRender.h"
#include <math.h>

#pragma warning(disable:4244)

CAK3DRender::CAK3DRender()
{
	m_pPicDraw=NULL;
	
	m_XArray[0]=NULL;
	m_XArray[1]=NULL;
	m_ZArray[0]=NULL;
	m_ZArray[1]=NULL;
	m_UArray[0]=NULL;
	m_UArray[1]=NULL;
	m_VArray[0]=NULL;
	m_VArray[1]=NULL;

	m_pZBuffer=NULL;
}

CAK3DRender::~CAK3DRender()
{
	if(m_pIntersectionCountArray)delete [] m_pIntersectionCountArray;
	if(m_XArray[0])delete [] m_XArray[0];
	if(m_ZArray[0])delete [] m_ZArray[0];
	if(m_UArray[0])delete [] m_UArray[0];
	if(m_VArray[0])delete [] m_VArray[0];
	if(m_XArray[1])delete [] m_XArray[1];
	if(m_ZArray[1])delete [] m_ZArray[1];
	if(m_UArray[1])delete [] m_UArray[1];
	if(m_VArray[1])delete [] m_VArray[1];
	if(m_pZBuffer)delete [] m_pZBuffer;
}

void CAK3DRender::SelectPicDraw(CAKPicDraw *pPicDraw)
{
	m_pPicDraw=pPicDraw;
	m_ScrWidth=pPicDraw->m_Width;
	m_ScrHeight=pPicDraw->m_Height;

	if(m_pIntersectionCountArray)delete [] m_pIntersectionCountArray;
	if(m_XArray[0])delete [] m_XArray[0];
	if(m_ZArray[0])delete [] m_ZArray[0];
	if(m_UArray[0])delete [] m_UArray[0];
	if(m_VArray[0])delete [] m_VArray[0];
	if(m_XArray[1])delete [] m_XArray[1];
	if(m_ZArray[1])delete [] m_ZArray[1];
	if(m_UArray[1])delete [] m_UArray[1];
	if(m_VArray[1])delete [] m_VArray[1];
	if(m_pZBuffer)delete [] m_pZBuffer;

	m_pIntersectionCountArray=new unsigned char[m_ScrHeight];
	m_XArray[0]=new float[m_ScrHeight];
	m_ZArray[0]=new float[m_ScrHeight];
	m_UArray[0]=new float[m_ScrHeight];
	m_VArray[0]=new float[m_ScrHeight];
	m_XArray[1]=new float[m_ScrHeight];
	m_ZArray[1]=new float[m_ScrHeight];
	m_UArray[1]=new float[m_ScrHeight];
	m_VArray[1]=new float[m_ScrHeight];
	m_pZBuffer=new float[m_ScrWidth*m_ScrHeight];
}

void CAK3DRender::ResetZBuffer(float ZValue)
{
	long l=m_ScrWidth*m_ScrHeight;

	long i;
	for(i=0;i<l;++i)
	{
		m_pZBuffer[i]=ZValue;
	}
}

bool CAK3DRender::IsPolygonDisplay(struct AK3D_VERTEX *v1,struct AK3D_VERTEX *v2,struct AK3D_VERTEX *v3)
{
	float x1=v1->xDest;
	float y1=v1->yDest;

	float x2=v2->xDest;
	float y2=v2->yDest;
	
	float x3=v3->xDest;
	float y3=v3->yDest;

	float ux=x1-x2;
	float uy=y1-y2;

	float vx=x1-x3;
	float vy=y1-y3;

	float c=ux*vy-uy*vx;

	if(c>0)return true;
	else return false;
}

float CAK3DRender::GetPolygonPower(struct AK3D_VERTEX *v1,struct AK3D_VERTEX *v2,struct AK3D_VERTEX *v3)
{
	float x1=v1->xDest;
	float y1=v1->yDest;
	float z1=v1->zDest;

	float x2=v2->xDest;
	float y2=v2->yDest;
	float z2=v2->zDest;
	
	float x3=v3->xDest;
	float y3=v3->yDest;
	float z3=v3->zDest;

	float ux,uy,uz;
	ux=x1-x2;
	uy=y1-y2;
	uz=z1-z2;

	float vx,vy,vz;
	vx=x1-x3;
	vy=y1-y3;
	vz=z1-z3;

	//��ƽ�淨����n=a*i+b*j+c*k;
	float a,b,c;
	a=uy*vz-uz*vy;
	b=ux*vz-uz*vx;
	c=ux*vy-uy*vx;
	if(a==0&&b==0&&c==0)return 0;
	double Power=c/sqrt(a*a+b*b+c*c);
	if(Power<0)Power/=-1;
	return(Power);//����ƽ��������֮��Ƕȵ�����ֵ�ľ���ֵ
}

bool CAK3DRender::GetIntersection1(
								   float y,
								   float x1,float y1,float z1,
								   float x2,float y2,float z2,
								   float &xx,float &yy,float &zz
								   )
{
	//�໥ƽ��,���ཻ
	float dy=y2-y1;
	if(dy==0)return false;

	//ɨ����y���߶��ཻ
	if((y>y1&&y<y2)||(y>y2&&y<y1))
	{
		float dx=x2-x1;
		if(dx==0)//�߶δ�ֱ��ˮƽɨ����y
		{
			xx=x1;
			yy=y;
		}
		else//����ֱ
		{
			float a=dy/dx;
			float b=y1-a*x1;
			xx=(y-b)/a;
			yy=y;
		}

		float percent=(y-y1)/dy;

		//���㽻��zֵ
		float dz=z2-z1;
		if(dz==0)zz=z1;
		else zz=percent*dz+z1;

		return true;
	}
	else return false;//���ཻ
}

bool CAK3DRender::GetIntersection1(
								   float y,
								   float x1,float y1,float z1,float u1,float v1,
								   float x2,float y2,float z2,float u2,float v2,
								   float &xx,float &yy,float &zz,float &uu,float &vv
								   )
{
	//�໥ƽ��,���ཻ
	float dy=y2-y1;
	if(dy==0)return false;

	//ɨ����y���߶��ཻ
	if((y>y1&&y<y2)||(y>y2&&y<y1))
	{
		float dx=x2-x1;
		if(dx==0)//�߶δ�ֱ��ˮƽɨ����y
		{
			xx=x1;
			yy=y;
		}
		else//����ֱ
		{
			float a=dy/dx;
			float b=y1-a*x1;
			xx=(y-b)/a;
			yy=y;
		}

		float percent=(y-y1)/dy;

		//���㽻��zֵ
		float dz=z2-z1;
		if(dz==0)zz=z1;
		else zz=percent*dz+z1;

		//���㽻��UV
		float du=u2-u1;
		float dv=v2-v1;
		if(du==0)uu=u1;
		else uu=percent*du+u1;
		if(dv==0)vv=v1;
		else vv=percent*dv+v1;

		return true;
	}
	else return false;//���ཻ
}

bool CAK3DRender::GetIntersection2(
								   float x,
								   float x1,float y1,float z1,
								   float x2,float y2,float z2,
								   float &xx,float &yy,float &zz
								   )
{
	//�໥ƽ��,���ཻ
	float dx=x2-x1;
	if(dx==0)return false;

	//ɨ����y���߶��ཻ
	if((x>x1&&x<x2)||(x>x2&&x<x1))
	{
		float dy=y2-y1;
		if(dy==0)//�߶δ�ֱ�ڴ�ֱɨ����x
		{
			xx=x;
			yy=y1;
		}
		else//����ֱ
		{
			float a=dy/dx;
			float b=y1-a*x1;
			xx=x;
			yy=a*x+b;
		}

		float percent=(x-x1)/dx;

		//���㽻��zֵ
		float dz=z2-z1;
		if(dz==0)zz=z1;
		else zz=percent*dz+z1;

		return true;
	}
	else return false;//���ཻ
}

bool CAK3DRender::GetIntersection2(
								   float x,
								   float x1,float y1,float z1,float u1,float v1,
								   float x2,float y2,float z2,float u2,float v2,
								   float &xx,float &yy,float &zz,float &uu,float &vv
								   )
{
	//�໥ƽ��,���ཻ
	float dx=x2-x1;
	if(dx==0)return false;

	//ɨ����y���߶��ཻ
	if((x>x1&&x<x2)||(x>x2&&x<x1))
	{
		float dy=y2-y1;
		if(dy==0)//�߶δ�ֱ�ڴ�ֱɨ����x
		{
			xx=x;
			yy=y1;
		}
		else//����ֱ
		{
			float a=dy/dx;
			float b=y1-a*x1;
			xx=x;
			yy=a*x+b;
		}

		float percent=(x-x1)/dx;

		//���㽻��zֵ
		float dz=z2-z1;
		if(dz==0)zz=z1;
		else zz=percent*dz+z1;

		//���㽻��UV
		float du=u2-u1;
		float dv=v2-v1;
		if(du==0)uu=u1;
		else uu=percent*du+u1;
		if(dv==0)vv=v1;
		else vv=percent*dv+v1;

		return true;
	}
	else return false;//���ཻ
}

bool CAK3DRender::CutOutLine(
							 float x1,float y1,float z1,
							 float x2,float y2,float z2,
							 float &xx1,float &yy1,float &zz1,
							 float &xx2,float &yy2,float &zz2
							 )
{
	//�߶�ȫ������Ļ��Χ��
	if(x1>=0&&x1<m_ScrWidth&&y1>=0&&y1<m_ScrHeight&&
		x2>=0&&x2<m_ScrWidth&&y2>=0&&y2<m_ScrHeight)
	{
		xx1=x1;
		yy1=y1;
		zz1=z1;
		xx2=x2;
		yy2=y2;
		zz2=z2;
		return true;
	}
	else
	{
		bool rt;
		int c=0;//����Ļ�Ľ�������
		float xx,yy,zz;//����

		//��Ļ�ϱ߽���
		rt=GetIntersection1(0,x1,y1,z1,x2,y2,z2,xx,yy,zz);
		if(rt)
		{
			if(y1!=0&&y2!=0)
			{
				if(y1<0)
				{
					x1=xx;
					y1=yy;
					z1=zz;
				}
				else
				{
					x2=xx;
					y2=yy;
					z2=zz;
				}
			}
		}

		//��Ļ�±߽���
		rt=GetIntersection1(m_ScrHeight-1,x1,y1,z1,x2,y2,z2,xx,yy,zz);
		if(rt)
		{
			if(y1!=(m_ScrHeight-1)&&y2!=(m_ScrHeight-1))
			{
				if(y1>(m_ScrHeight-1))
				{
					x1=xx;
					y1=yy;
					z1=zz;
				}
				else
				{
					x2=xx;
					y2=yy;
					z2=zz;
				}
			}
		}

		//��Ļ��߽���
		rt=GetIntersection2(0,x1,y1,z1,x2,y2,z2,xx,yy,zz);
		if(rt)
		{
			if(x1!=0&&x2!=0)
			{
				if(x1<0)
				{
					x1=xx;
					y1=yy;
					z1=zz;
				}
				else
				{
					x2=xx;
					y2=yy;
					z2=zz;
				}
			}
		}

		//��Ļ�ұ߽���
		rt=GetIntersection2(m_ScrWidth-1,x1,y1,z1,x2,y2,z2,xx,yy,zz);
		if(rt)
		{
			if(x1!=(m_ScrWidth-1)&&x2!=(m_ScrWidth-1))
			{
				if(x1>(m_ScrWidth-1))
				{
					x1=xx;
					y1=yy;
					z1=zz;
				}
				else
				{
					x2=xx;
					y2=yy;
					z2=zz;
				}
			}
		}

		xx1=x1;
		yy1=y1;
		zz1=z1;
		xx2=x2;
		yy2=y2;
		zz2=z2;

		if(x1>=0&&x1<m_ScrWidth&&y1>=0&&y1<m_ScrHeight&&
			x2>=0&&x2<m_ScrWidth&&y2>=0&&y2<m_ScrHeight)
		{
			return true;
		}
		else return false;
	}
}

void CAK3DRender::CreateIntersectionArray(
							 float x1,float y1,float z1,
							 float x2,float y2,float z2,
							 float u1,float v1,
							 float u2,float v2
							 )
{
	float dy=y2-y1;
	
	//�����ܲ���
	long StepCount;
	if(dy<0)StepCount=-dy;
	else StepCount=dy;

	if(StepCount<=0)return;
	
	float dx=x2-x1;
	float dz=z2-z1;
	float du=u2-u1;
	float dv=v2-v1;

	//���㲽��
	float XStep=dx/StepCount;
	long YStep=dy/StepCount;
	float ZStep=dz/StepCount;
	float UStep=du/StepCount;
	float VStep=dv/StepCount;

	long i;
	float xx=x1;
	long yy=y1;
	float zz=z1;
	float uu=u1;
	float vv=v1;
	for(i=0;i<=StepCount;++i)
	{
		switch(m_pIntersectionCountArray[yy])
		{
		case 0:
			{
				m_XArray[0][yy]=xx;
				m_ZArray[0][yy]=zz;
				m_UArray[0][yy]=uu;
				m_VArray[0][yy]=vv;
				++m_pIntersectionCountArray[yy];
				break;
			}
		case 1:
			{
				float t=xx-m_XArray[0][yy];
				if(t<0)t=-t;
				if(t>1)
				{
					++m_pIntersectionCountArray[yy];

					//������2��ʱ,��Ҫ����
					if(xx<m_XArray[0][yy])
					{
						m_XArray[1][yy]=m_XArray[0][yy];
						m_ZArray[1][yy]=m_ZArray[0][yy];
						m_XArray[0][yy]=xx;
						m_ZArray[0][yy]=zz;

						m_UArray[1][yy]=m_UArray[0][yy];
						m_VArray[1][yy]=m_VArray[0][yy];
						m_UArray[0][yy]=uu;
						m_VArray[0][yy]=vv;
					}
					else
					{
						m_XArray[1][yy]=xx;
						m_ZArray[1][yy]=zz;
						m_UArray[1][yy]=uu;
						m_VArray[1][yy]=vv;
					}
				}
				break;
			}
		case 2:
			{
				float t=m_XArray[1][yy]-m_XArray[0][yy];
				if(t<0)t=-t;
				if(t<2)//���ԭ�������������̫��
				{
					//��ɾ���ڶ�������
					--m_pIntersectionCountArray[yy];
				}

				//�����ǰ��������Ϊ1
				if(m_pIntersectionCountArray[yy]==1)
				{
					t=xx-m_XArray[0][yy];
					if(t<0)t=-t;
					if(t>1)
					{
						++m_pIntersectionCountArray[yy];

						//������2��ʱ,��Ҫ����
						if(xx<m_XArray[0][yy])
						{
							m_XArray[1][yy]=m_XArray[0][yy];
							m_ZArray[1][yy]=m_ZArray[0][yy];
							m_XArray[0][yy]=xx;
							m_ZArray[0][yy]=zz;

							m_UArray[1][yy]=m_UArray[0][yy];
							m_VArray[1][yy]=m_VArray[0][yy];
							m_UArray[0][yy]=uu;
							m_VArray[0][yy]=vv;
						}
						else
						{
							m_XArray[1][yy]=xx;
							m_ZArray[1][yy]=zz;
							m_UArray[1][yy]=uu;
							m_VArray[1][yy]=vv;
						}
					}
				}
				break;
			}
		}

		//����������
		xx+=XStep;
		yy+=YStep;
		zz+=ZStep;
		uu+=UStep;
		vv+=VStep;
	}

	//�޸�Y�������һ�����ܵ����յ���������
	xx=x2;
	yy=y2;
	zz=z2;
	switch(m_pIntersectionCountArray[yy])
	{
	case 0:
		{
			m_XArray[0][yy]=xx;
			m_ZArray[0][yy]=zz;
			m_UArray[0][yy]=uu;
			m_VArray[0][yy]=vv;
			++m_pIntersectionCountArray[yy];
			break;
		}
	case 1:
		{
			float t=xx-m_XArray[0][yy];
			if(t<0)t=-t;
			if(t>1)
			{
				++m_pIntersectionCountArray[yy];

				//������2��ʱ,��Ҫ����
				if(xx<m_XArray[0][yy])
				{
					m_XArray[1][yy]=m_XArray[0][yy];
					m_ZArray[1][yy]=m_ZArray[0][yy];
					m_XArray[0][yy]=xx;
					m_ZArray[0][yy]=zz;

					m_UArray[1][yy]=m_UArray[0][yy];
					m_VArray[1][yy]=m_VArray[0][yy];
					m_UArray[0][yy]=uu;
					m_VArray[0][yy]=vv;
				}
				else
				{
					m_XArray[1][yy]=xx;
					m_ZArray[1][yy]=zz;
					m_UArray[1][yy]=uu;
					m_VArray[1][yy]=vv;
				}
			}
			break;
		}
	case 2:
		{
			float t=m_XArray[1][yy]-m_XArray[0][yy];
			if(t<0)t=-t;
			if(t<2)//���ԭ�������������̫��
			{
				//��ɾ���ڶ�������
				--m_pIntersectionCountArray[yy];
			}

			//�����ǰ��������Ϊ1
			if(m_pIntersectionCountArray[yy]==1)
			{
				t=xx-m_XArray[0][yy];
				if(t<0)t=-t;
				if(t>1)
				{
					++m_pIntersectionCountArray[yy];

					//������2��ʱ,��Ҫ����
					if(xx<m_XArray[0][yy])
					{
						m_XArray[1][yy]=m_XArray[0][yy];
						m_ZArray[1][yy]=m_ZArray[0][yy];
						m_XArray[0][yy]=xx;
						m_ZArray[0][yy]=zz;

						m_UArray[1][yy]=m_UArray[0][yy];
						m_VArray[1][yy]=m_VArray[0][yy];
						m_UArray[0][yy]=uu;
						m_VArray[0][yy]=vv;
					}
					else
					{
						m_XArray[1][yy]=xx;
						m_ZArray[1][yy]=zz;
						m_UArray[1][yy]=uu;
						m_VArray[1][yy]=vv;
					}
				}
			}
			break;
		}
	}

}


void CAK3DRender::CreateIntersectionArray(
							 float x1,float y1,float z1,
							 float x2,float y2,float z2
							 )
{
	float dy=y2-y1;
	
	//�����ܲ���
	long StepCount;
	if(dy<0)StepCount=-dy;
	else StepCount=dy;

	if(StepCount<=0)return;
	
	float dx=x2-x1;
	float dz=z2-z1;

	//���㲽��
	float XStep=dx/StepCount;
	long YStep=dy/StepCount;
	float ZStep=dz/StepCount;

	long i;
	float xx=x1;
	long yy=y1;
	float zz=z1;
	for(i=0;i<=StepCount;++i)
	{
		switch(m_pIntersectionCountArray[yy])
		{
		case 0:
			{
				m_XArray[0][yy]=xx;
				m_ZArray[0][yy]=zz;
				++m_pIntersectionCountArray[yy];
				break;
			}
		case 1:
			{
				float t=xx-m_XArray[0][yy];
				if(t<0)t=-t;
				if(t>1)
				{
					++m_pIntersectionCountArray[yy];

					//������2��ʱ,��Ҫ����
					if(xx<m_XArray[0][yy])
					{
						m_XArray[1][yy]=m_XArray[0][yy];
						m_ZArray[1][yy]=m_ZArray[0][yy];
						m_XArray[0][yy]=xx;
						m_ZArray[0][yy]=zz;
					}
					else
					{
						m_XArray[1][yy]=xx;
						m_ZArray[1][yy]=zz;
					}
				}
				break;
			}
		case 2:
			{
				float t=m_XArray[1][yy]-m_XArray[0][yy];
				if(t<0)t=-t;
				if(t<2)//���ԭ�������������̫��
				{
					//��ɾ���ڶ�������
					--m_pIntersectionCountArray[yy];
				}

				//�����ǰ��������Ϊ1
				if(m_pIntersectionCountArray[yy]==1)
				{
					t=xx-m_XArray[0][yy];
					if(t<0)t=-t;
					if(t>1)
					{
						++m_pIntersectionCountArray[yy];

						//������2��ʱ,��Ҫ����
						if(xx<m_XArray[0][yy])
						{
							m_XArray[1][yy]=m_XArray[0][yy];
							m_ZArray[1][yy]=m_ZArray[0][yy];
							m_XArray[0][yy]=xx;
							m_ZArray[0][yy]=zz;
						}
						else
						{
							m_XArray[1][yy]=xx;
							m_ZArray[1][yy]=zz;
						}
					}
				}
				break;
			}
		}

		//����������
		xx+=XStep;
		yy+=YStep;
		zz+=ZStep;
	}

	//�޸�Y�������һ�����ܵ����յ���������
	xx=x2;
	yy=y2;
	zz=z2;
	switch(m_pIntersectionCountArray[yy])
	{
	case 0:
		{
			m_XArray[0][yy]=xx;
			m_ZArray[0][yy]=zz;
			++m_pIntersectionCountArray[yy];
			break;
		}
	case 1:
		{
			float t=xx-m_XArray[0][yy];
			if(t<0)t=-t;
			if(t>1)
			{
				++m_pIntersectionCountArray[yy];

				//������2��ʱ,��Ҫ����
				if(xx<m_XArray[0][yy])
				{
					m_XArray[1][yy]=m_XArray[0][yy];
					m_ZArray[1][yy]=m_ZArray[0][yy];
					m_XArray[0][yy]=xx;
					m_ZArray[0][yy]=zz;
				}
				else
				{
					m_XArray[1][yy]=xx;
					m_ZArray[1][yy]=zz;
				}
			}
			break;
		}
	case 2:
		{
			float t=m_XArray[1][yy]-m_XArray[0][yy];
			if(t<0)t=-t;
			if(t<2)//���ԭ�������������̫��
			{
				//��ɾ���ڶ�������
				--m_pIntersectionCountArray[yy];
			}

			//�����ǰ��������Ϊ1
			if(m_pIntersectionCountArray[yy]==1)
			{
				t=xx-m_XArray[0][yy];
				if(t<0)t=-t;
				if(t>1)
				{
					++m_pIntersectionCountArray[yy];

					//������2��ʱ,��Ҫ����
					if(xx<m_XArray[0][yy])
					{
						m_XArray[1][yy]=m_XArray[0][yy];
						m_ZArray[1][yy]=m_ZArray[0][yy];
						m_XArray[0][yy]=xx;
						m_ZArray[0][yy]=zz;
					}
					else
					{
						m_XArray[1][yy]=xx;
						m_ZArray[1][yy]=zz;
					}
				}
			}
			break;
		}
	}
}

void CAK3DRender::DrawModel(
struct AK3D_MODEL *pModel,
	unsigned short uRenderStyle
	)
{
	AK_POS_PTR pos=pModel->PolygonList.GetHeadPos();

	switch(uRenderStyle)
	{
	case 0://0=������ͼ��Ⱦ(���㷴���ǿ);
		{
			break;
		}
	case 1://1=������ͼ��Ⱦ(���㷴���ǿ);
		{
			while(pos)
			{
				struct AK3D_POLYGON *pPolygon=(struct AK3D_POLYGON *)pModel->PolygonList.GetValue(pos);

				//���������Ƿ�ɼ�
				bool rt=IsPolygonDisplay(pPolygon->pVertexList[0],pPolygon->pVertexList[1],pPolygon->pVertexList[2]);
				if(rt)
				{
					//�����ǿ��
					float power=GetPolygonPower(pPolygon->pVertexList[0],pPolygon->pVertexList[1],pPolygon->pVertexList[2]);

					m_pPicDraw->SetPenColor(pPolygon->r*power,pPolygon->g*power,pPolygon->b*power);

					switch(pPolygon->uVertexCount)
					{
					case 3:
						{
							Draw1(
								pPolygon->pVertexList[0],
								pPolygon->pVertexList[1],
								pPolygon->pVertexList[2]
								);
								break;
						}
					case 4:
						{
							DrawRect1(
								pPolygon->pVertexList[0],
								pPolygon->pVertexList[1],
								pPolygon->pVertexList[2],
								pPolygon->pVertexList[3]
								);
								break;
						}
					}
				}

				//��һ��
				pModel->PolygonList.Next(&pos);
			}

			break;
		}
	case 2://2=����ͼ��Ⱦ(���Է����ǿ);
		{
			//�����ͼ������,�������Ⱦ��ʽ1
			if(!pModel->pUIPic)
			{
				DrawModel(pModel,1);
				return;
			}

			//ѡ����ͼ׼����Ⱦ
			CAKPicDraw::GetInst(AK_PIC_DRAW_MAX_COUNT-1)->SelectPic(pModel->pUIPic->pData,pModel->pUIPic->uWidth,pModel->pUIPic->uHeight);

			while(pos)
			{
				struct AK3D_POLYGON *pPolygon=(struct AK3D_POLYGON *)pModel->PolygonList.GetValue(pos);

				//���������Ƿ�ɼ�
				bool rt=IsPolygonDisplay(pPolygon->pVertexList[0],pPolygon->pVertexList[1],pPolygon->pVertexList[2]);
				if(rt)
				{
					//�����ǿ��
					//float power=GetPolygonPower(pPolygon->pVertexList[0],pPolygon->pVertexList[1],pPolygon->pVertexList[2]);

					//m_pPicDraw->SetPenColor(pPolygon->r*power,pPolygon->g*power,pPolygon->b*power);

					switch(pPolygon->uVertexCount)
					{
					case 3:
						{
							Draw2(
								pPolygon->pVertexList[0],
								pPolygon->pVertexList[1],
								pPolygon->pVertexList[2],
								pPolygon->UVList[0],
								pPolygon->UVList[1],
								pPolygon->UVList[2]
								);
								break;
						}
					case 4:
						{
							DrawRect2(
								pPolygon->pVertexList[0],
								pPolygon->pVertexList[1],
								pPolygon->pVertexList[2],
								pPolygon->pVertexList[3],
								pPolygon->UVList[0],
								pPolygon->UVList[1],
								pPolygon->UVList[2],
								pPolygon->UVList[3]
								);
								break;
						}
					}
				}

				//��һ��
				pModel->PolygonList.Next(&pos);
			}

			break;
		}
	case 3://3=����ͼ��Ⱦ(���㷴���ǿ);
		{
			break;
		}
	}
}

void CAK3DRender::DrawRect1(
struct AK3D_VERTEX *v1,//����1
struct AK3D_VERTEX *v2,//����2
struct AK3D_VERTEX *v3,//����3
struct AK3D_VERTEX *v4//����4
	)
{
	Draw1(v1,v2,v3);
	Draw1(v1,v4,v3);
}

void CAK3DRender::DrawRect2(
struct AK3D_VERTEX *v1,//����1
struct AK3D_VERTEX *v2,//����2
struct AK3D_VERTEX *v3,//����3
struct AK3D_VERTEX *v4,//����4
	float *uv1,//����UV1
	float *uv2,//����UV2
	float *uv3,//����UV3
	float *uv4,//����UV4
	bool bIsUseAlpha//�Ƿ�ʹ��alpha
	)
{
	Draw2(v1,v2,v3,uv1,uv2,uv3,bIsUseAlpha);
	Draw2(v1,v4,v3,uv1,uv4,uv3,bIsUseAlpha);
}

void CAK3DRender::Draw1(
struct AK3D_VERTEX *v1,//����1
struct AK3D_VERTEX *v2,//����2
struct AK3D_VERTEX *v3//����3
	)
{
	//��������������0
	memset(m_pIntersectionCountArray,0,m_ScrHeight);

	float ymin,ymax;
	bool rt;
	bool IsBegin=false;

	float yy1;

	bool IsVertexList[9];//��־��ǰ�����Ƿ����
	float VertexList[9][3];//��������

	VertexList[0][0]=v1->xDest;
	VertexList[0][1]=v1->yDest;
	VertexList[0][2]=v1->zDest;
	VertexList[1][0]=v2->xDest;
	VertexList[1][1]=v2->yDest;
	VertexList[1][2]=v2->zDest;
	VertexList[2][0]=v3->xDest;
	VertexList[2][1]=v3->yDest;
	VertexList[2][2]=v3->zDest;
	IsVertexList[0]=true;
	IsVertexList[1]=true;
	IsVertexList[2]=true;
	IsVertexList[3]=false;
	IsVertexList[4]=false;
	IsVertexList[5]=false;
	IsVertexList[6]=false;
	IsVertexList[7]=false;
	IsVertexList[8]=false;

	short VertexCount=3;//��������
	float *pVertex1;
	float *pVertex2;
	long i,j;
	long index;
	float x,y,z;
	short c;
	short LineCount;

	//���㽻��
	LineCount=VertexCount;//�߶�����
	pVertex1=pVertex2=NULL;
	for(i=0,c=0;c<LineCount;++i)
	{
		index=i%VertexCount;

		//��ǰ�������
		if(IsVertexList[index])
		{
			if(!pVertex1)
			{
				pVertex1=VertexList[index];
			}
			else
			{
				pVertex2=VertexList[index];
			}
		}

		if(pVertex1&&pVertex2)
		{
			//�����߶�����
			++c;

			//�иǰ�߶�
			//��Ļ�ϱ߽���
			rt=GetIntersection1(0,pVertex1[0],pVertex1[1],pVertex1[2],pVertex2[0],pVertex2[1],pVertex2[2],x,y,z);
			if(rt)
			{
				//���Ų��һ����λ��
				for(j=VertexCount-1;j>=i;--j)
				{
					IsVertexList[j+1]=IsVertexList[j];
					VertexList[j+1][0]=VertexList[j][0];
					VertexList[j+1][1]=VertexList[j][1];
					VertexList[j+1][2]=VertexList[j][2];
				}

				//���뽻����Ϊ�µĶ���
				VertexList[i][0]=x;
				VertexList[i][1]=y;
				VertexList[i][2]=z;
				IsVertexList[i]=true;
				++VertexCount;

				++i;

				//������һ���߶εĵ�һ���˵�
				pVertex1=VertexList[index+1];
				pVertex2=NULL;
			}
			else
			{
				//������һ���߶εĵ�һ���˵�
				pVertex1=pVertex2;
				pVertex2=NULL;
			}
		}
	}


	//�޳����ɼ�����
	pVertex1=pVertex2=NULL;
	for(i=0;i<VertexCount;++i)
	{
		x=VertexList[i][0];
		y=VertexList[i][1];

		//�����ǰ���㲻�ɼ�
		if(y<0)
		{
			//ɾ����ǰ����:�Ѻ���Ķ���Ų����,���ǵ�ǰ����
			for(j=i+1;j<VertexCount;++j)
			{
				IsVertexList[j-1]=IsVertexList[j];
				VertexList[j-1][0]=VertexList[j][0];
				VertexList[j-1][1]=VertexList[j][1];
				VertexList[j-1][2]=VertexList[j][2];
			}

			//ԭ�������һ�������־Ϊ������
			IsVertexList[VertexCount-1]=false;
			--VertexCount;
			--i;
		}
	}

	//���㽻��
	LineCount=VertexCount;//�߶�����
	pVertex1=pVertex2=NULL;
	for(i=0,c=0;c<LineCount;++i)
	{
		index=i%VertexCount;

		//��ǰ�������
		if(IsVertexList[index])
		{
			if(!pVertex1)
			{
				pVertex1=VertexList[index];
			}
			else
			{
				pVertex2=VertexList[index];
			}
		}

		if(pVertex1&&pVertex2)
		{
			//�����߶�����
			++c;

			//�иǰ�߶�
			//��Ļ�±߽���
			rt=GetIntersection1(m_ScrHeight-1,pVertex1[0],pVertex1[1],pVertex1[2],pVertex2[0],pVertex2[1],pVertex2[2],x,y,z);
			if(rt)
			{
				//���Ų��һ����λ��
				for(j=VertexCount-1;j>=i;--j)
				{
					IsVertexList[j+1]=IsVertexList[j];
					VertexList[j+1][0]=VertexList[j][0];
					VertexList[j+1][1]=VertexList[j][1];
					VertexList[j+1][2]=VertexList[j][2];
				}

				//���뽻����Ϊ�µĶ���
				VertexList[i][0]=x;
				VertexList[i][1]=y;
				VertexList[i][2]=z;
				IsVertexList[i]=true;
				++VertexCount;

				++i;

				//������һ���߶εĵ�һ���˵�
				pVertex1=VertexList[index+1];
				pVertex2=NULL;
			}
			else
			{
				//������һ���߶εĵ�һ���˵�
				pVertex1=pVertex2;
				pVertex2=NULL;
			}
		}
	}


	//�޳����ɼ�����
	pVertex1=pVertex2=NULL;
	for(i=0;i<VertexCount;++i)
	{
		x=VertexList[i][0];
		y=VertexList[i][1];

		//�����ǰ���㲻�ɼ�
		if(y>=m_ScrHeight)
		{
			//ɾ����ǰ����:�Ѻ���Ķ���Ų����,���ǵ�ǰ����
			for(j=i+1;j<VertexCount;++j)
			{
				IsVertexList[j-1]=IsVertexList[j];
				VertexList[j-1][0]=VertexList[j][0];
				VertexList[j-1][1]=VertexList[j][1];
				VertexList[j-1][2]=VertexList[j][2];
			}

			//ԭ�������һ�������־Ϊ������
			IsVertexList[VertexCount-1]=false;
			--VertexCount;
			--i;
		}
	}

	//���㽻��
	LineCount=VertexCount;//�߶�����
	pVertex1=pVertex2=NULL;
	for(i=0,c=0;c<LineCount;++i)
	{
		index=i%VertexCount;

		//��ǰ�������
		if(IsVertexList[index])
		{
			if(!pVertex1)
			{
				pVertex1=VertexList[index];
			}
			else
			{
				pVertex2=VertexList[index];
			}
		}

		if(pVertex1&&pVertex2)
		{
			//�����߶�����
			++c;

			//�иǰ�߶�
			//��Ļ��߽���
			rt=GetIntersection2(0,pVertex1[0],pVertex1[1],pVertex1[2],pVertex2[0],pVertex2[1],pVertex2[2],x,y,z);
			if(rt)
			{
				//���Ų��һ����λ��
				for(j=VertexCount-1;j>=i;--j)
				{
					IsVertexList[j+1]=IsVertexList[j];
					VertexList[j+1][0]=VertexList[j][0];
					VertexList[j+1][1]=VertexList[j][1];
					VertexList[j+1][2]=VertexList[j][2];
				}

				//���뽻����Ϊ�µĶ���
				VertexList[i][0]=x;
				VertexList[i][1]=y;
				VertexList[i][2]=z;
				IsVertexList[i]=true;
				++VertexCount;

				++i;

				//������һ���߶εĵ�һ���˵�
				pVertex1=VertexList[index+1];
				pVertex2=NULL;
			}
			else
			{
				//������һ���߶εĵ�һ���˵�
				pVertex1=pVertex2;
				pVertex2=NULL;
			}
		}
	}


	//�޳����ɼ�����
	pVertex1=pVertex2=NULL;
	for(i=0;i<VertexCount;++i)
	{
		x=VertexList[i][0];
		y=VertexList[i][1];

		//�����ǰ���㲻�ɼ�
		if(x<0)
		{
			//ɾ����ǰ����:�Ѻ���Ķ���Ų����,���ǵ�ǰ����
			for(j=i+1;j<VertexCount;++j)
			{
				IsVertexList[j-1]=IsVertexList[j];
				VertexList[j-1][0]=VertexList[j][0];
				VertexList[j-1][1]=VertexList[j][1];
				VertexList[j-1][2]=VertexList[j][2];
			}

			//ԭ�������һ�������־Ϊ������
			IsVertexList[VertexCount-1]=false;
			--VertexCount;
			--i;
		}
	}

	//���㽻��
	LineCount=VertexCount;//�߶�����
	pVertex1=pVertex2=NULL;
	for(i=0,c=0;c<LineCount;++i)
	{
		index=i%VertexCount;

		//��ǰ�������
		if(IsVertexList[index])
		{
			if(!pVertex1)
			{
				pVertex1=VertexList[index];
			}
			else
			{
				pVertex2=VertexList[index];
			}
		}

		if(pVertex1&&pVertex2)
		{
			//�����߶�����
			++c;

			//�иǰ�߶�
			//��Ļ�ұ߽���
			rt=GetIntersection2(m_ScrWidth-1,pVertex1[0],pVertex1[1],pVertex1[2],pVertex2[0],pVertex2[1],pVertex2[2],x,y,z);
			if(rt)
			{
				//���Ų��һ����λ��
				for(j=VertexCount-1;j>=i;--j)
				{
					IsVertexList[j+1]=IsVertexList[j];
					VertexList[j+1][0]=VertexList[j][0];
					VertexList[j+1][1]=VertexList[j][1];
					VertexList[j+1][2]=VertexList[j][2];
				}

				//���뽻����Ϊ�µĶ���
				VertexList[i][0]=x;
				VertexList[i][1]=y;
				VertexList[i][2]=z;
				IsVertexList[i]=true;
				++VertexCount;

				++i;

				//������һ���߶εĵ�һ���˵�
				pVertex1=VertexList[index+1];
				pVertex2=NULL;
			}
			else
			{
				//������һ���߶εĵ�һ���˵�
				pVertex1=pVertex2;
				pVertex2=NULL;
			}
		}
	}


	//�޳����ɼ�����
	pVertex1=pVertex2=NULL;
	for(i=0;i<VertexCount;++i)
	{
		x=VertexList[i][0];
		y=VertexList[i][1];

		//�����ǰ���㲻�ɼ�
		if(x>=m_ScrWidth)
		{
			//ɾ����ǰ����:�Ѻ���Ķ���Ų����,���ǵ�ǰ����
			for(j=i+1;j<VertexCount;++j)
			{
				IsVertexList[j-1]=IsVertexList[j];
				VertexList[j-1][0]=VertexList[j][0];
				VertexList[j-1][1]=VertexList[j][1];
				VertexList[j-1][2]=VertexList[j][2];
			}

			//ԭ�������һ�������־Ϊ������
			IsVertexList[VertexCount-1]=false;
			--VertexCount;
			--i;
		}
	}


	if(VertexCount>=3)
	{
		c=0;//���ɨ�����:�ղŵ���VertexCount��ʾ���������ߵķ���

		//ɨ��ü���Ķ���ν���
		for(i=0;c<VertexCount;++i)
		{
			index=i%VertexCount;
			if(IsVertexList[index])
			{
				if(!pVertex1)
				{
					pVertex1=VertexList[index];
				}
				else
				{
					pVertex2=VertexList[index];
				}

				//����Yֵ�����ֵ����Сֵ
				if(IsBegin)
				{
					yy1=VertexList[index][1];
					if(yy1<ymin)ymin=yy1;
					if(yy1>ymax)ymax=yy1;
				}
				else
				{
					ymin=ymax=VertexList[index][1];
				}

				IsBegin=true;
			}

			//��ǰ�߶δ���
			if(pVertex1&&pVertex2)
			{
				//ɨ���߶ν���
				CreateIntersectionArray(pVertex1[0],pVertex1[1],pVertex1[2],pVertex2[0],pVertex2[1],pVertex2[2]);

				//��һ���߶�
				pVertex1=pVertex2;
				pVertex2=NULL;

				++c;
			}
		}

		//��Ⱦ
		if(ymin<0)ymin=0;
		if(ymax>=m_ScrWidth)ymax=m_ScrWidth-1;
		long yy;
		float zz;
		float ZStep;
		for(yy=ymin;yy<=ymax;++yy)
		{
			switch(m_pIntersectionCountArray[yy])//������
			{
			case 1:
				{
					i=m_XArray[0][yy];
					zz=m_ZArray[0][yy];

					index=yy*m_ScrWidth+i;
					if(zz>m_pZBuffer[index])
					{
						//��������
						memcpy(&m_pPicDraw->m_pData[index*4],&m_pPicDraw->m_uPenColorMark,sizeof(unsigned long));//m_pPicDraw->SetPixel(i,yy);
						m_pZBuffer[index]=zz;
					}
					break;
				}
			case 2:
				{
					zz=m_ZArray[0][yy];
					ZStep=(m_ZArray[1][yy]-m_ZArray[0][yy])/(m_XArray[1][yy]-m_XArray[0][yy]);

					for(i=m_XArray[0][yy];i<=m_XArray[1][yy];++i)
					{
						index=yy*m_ScrWidth+i;
						if(zz>m_pZBuffer[index])
						{
							//��������
							memcpy(&m_pPicDraw->m_pData[index*4],&m_pPicDraw->m_uPenColorMark,sizeof(unsigned long));//m_pPicDraw->SetPixel(i,yy);
							m_pZBuffer[index]=zz;
						}
						zz+=ZStep;
					}

					break;
				}
			}
		}
	}
}

void CAK3DRender::Draw2(
struct AK3D_VERTEX *v1,//����1
struct AK3D_VERTEX *v2,//����2
struct AK3D_VERTEX *v3,//����3
	float *uv1,//����UV1
	float *uv2,//����UV2
	float *uv3,//����UV3
	bool bIsUseAlpha//�Ƿ�ʹ��alpha
	)
{
	//��������������0
	memset(m_pIntersectionCountArray,0,m_ScrHeight);

	float ymin,ymax;
	bool rt;
	bool IsBegin=false;

	float yy1;

	bool IsVertexList[9];//��־��ǰ�����Ƿ����
	float VertexList[9][5];//��������+����UV����

	VertexList[0][3]=uv1[0];
	VertexList[0][4]=uv1[1];
	VertexList[1][3]=uv2[0];
	VertexList[1][4]=uv2[1];
	VertexList[2][3]=uv3[0];
	VertexList[2][4]=uv3[1];
	VertexList[0][0]=v1->xDest;
	VertexList[0][1]=v1->yDest;
	VertexList[0][2]=v1->zDest;
	VertexList[1][0]=v2->xDest;
	VertexList[1][1]=v2->yDest;
	VertexList[1][2]=v2->zDest;
	VertexList[2][0]=v3->xDest;
	VertexList[2][1]=v3->yDest;
	VertexList[2][2]=v3->zDest;
	IsVertexList[0]=true;
	IsVertexList[1]=true;
	IsVertexList[2]=true;
	IsVertexList[3]=false;
	IsVertexList[4]=false;
	IsVertexList[5]=false;
	IsVertexList[6]=false;
	IsVertexList[7]=false;
	IsVertexList[8]=false;

	short VertexCount=3;//��������
	float *pVertex1;
	float *pVertex2;
	long i,j;
	long index;
	float x,y,z;
	float u,v;
	short c;
	short LineCount;

	//���㽻��
	LineCount=VertexCount;//�߶�����
	pVertex1=pVertex2=NULL;
	for(i=0,c=0;c<LineCount;++i)
	{
		index=i%VertexCount;

		//��ǰ�������
		if(IsVertexList[index])
		{
			if(!pVertex1)
			{
				pVertex1=VertexList[index];
			}
			else
			{
				pVertex2=VertexList[index];
			}
		}

		if(pVertex1&&pVertex2)
		{
			//�����߶�����
			++c;

			//�иǰ�߶�
			//��Ļ�ϱ߽���
			rt=GetIntersection1(0,
				pVertex1[0],pVertex1[1],pVertex1[2],pVertex1[3],pVertex1[4],
				pVertex2[0],pVertex2[1],pVertex2[2],pVertex2[3],pVertex2[4],
				x,y,z,u,v
				);
			if(rt)
			{
				//���Ų��һ����λ��
				for(j=VertexCount-1;j>=i;--j)
				{
					IsVertexList[j+1]=IsVertexList[j];
					VertexList[j+1][0]=VertexList[j][0];
					VertexList[j+1][1]=VertexList[j][1];
					VertexList[j+1][2]=VertexList[j][2];
					VertexList[j+1][3]=VertexList[j][3];
					VertexList[j+1][4]=VertexList[j][4];
				}

				//���뽻����Ϊ�µĶ���
				VertexList[i][0]=x;
				VertexList[i][1]=y;
				VertexList[i][2]=z;
				VertexList[i][3]=u;
				VertexList[i][4]=v;
				IsVertexList[i]=true;
				++VertexCount;

				++i;

				//������һ���߶εĵ�һ���˵�
				pVertex1=VertexList[index+1];
				pVertex2=NULL;
			}
			else
			{
				//������һ���߶εĵ�һ���˵�
				pVertex1=pVertex2;
				pVertex2=NULL;
			}
		}
	}


	//�޳����ɼ�����
	pVertex1=pVertex2=NULL;
	for(i=0;i<VertexCount;++i)
	{
		x=VertexList[i][0];
		y=VertexList[i][1];

		//�����ǰ���㲻�ɼ�
		if(y<0)
		{
			//ɾ����ǰ����:�Ѻ���Ķ���Ų����,���ǵ�ǰ����
			for(j=i+1;j<VertexCount;++j)
			{
				IsVertexList[j-1]=IsVertexList[j];
				VertexList[j-1][0]=VertexList[j][0];
				VertexList[j-1][1]=VertexList[j][1];
				VertexList[j-1][2]=VertexList[j][2];
				VertexList[j-1][3]=VertexList[j][3];
				VertexList[j-1][4]=VertexList[j][4];
			}

			//ԭ�������һ�������־Ϊ������
			IsVertexList[VertexCount-1]=false;
			--VertexCount;
			--i;
		}
	}

	//���㽻��
	LineCount=VertexCount;//�߶�����
	pVertex1=pVertex2=NULL;
	for(i=0,c=0;c<LineCount;++i)
	{
		index=i%VertexCount;

		//��ǰ�������
		if(IsVertexList[index])
		{
			if(!pVertex1)
			{
				pVertex1=VertexList[index];
			}
			else
			{
				pVertex2=VertexList[index];
			}
		}

		if(pVertex1&&pVertex2)
		{
			//�����߶�����
			++c;

			//�иǰ�߶�
			//��Ļ�±߽���
			rt=GetIntersection1(m_ScrHeight-1,
				pVertex1[0],pVertex1[1],pVertex1[2],pVertex1[3],pVertex1[4],
				pVertex2[0],pVertex2[1],pVertex2[2],pVertex2[3],pVertex2[4],
				x,y,z,u,v
				);
			if(rt)
			{
				//���Ų��һ����λ��
				for(j=VertexCount-1;j>=i;--j)
				{
					IsVertexList[j+1]=IsVertexList[j];
					VertexList[j+1][0]=VertexList[j][0];
					VertexList[j+1][1]=VertexList[j][1];
					VertexList[j+1][2]=VertexList[j][2];
					VertexList[j+1][3]=VertexList[j][3];
					VertexList[j+1][4]=VertexList[j][4];
				}

				//���뽻����Ϊ�µĶ���
				VertexList[i][0]=x;
				VertexList[i][1]=y;
				VertexList[i][2]=z;
				VertexList[i][3]=u;
				VertexList[i][4]=v;
				IsVertexList[i]=true;
				++VertexCount;

				++i;

				//������һ���߶εĵ�һ���˵�
				pVertex1=VertexList[index+1];
				pVertex2=NULL;
			}
			else
			{
				//������һ���߶εĵ�һ���˵�
				pVertex1=pVertex2;
				pVertex2=NULL;
			}
		}
	}


	//�޳����ɼ�����
	pVertex1=pVertex2=NULL;
	for(i=0;i<VertexCount;++i)
	{
		x=VertexList[i][0];
		y=VertexList[i][1];

		//�����ǰ���㲻�ɼ�
		if(y>=m_ScrHeight)
		{
			//ɾ����ǰ����:�Ѻ���Ķ���Ų����,���ǵ�ǰ����
			for(j=i+1;j<VertexCount;++j)
			{
				IsVertexList[j-1]=IsVertexList[j];
				VertexList[j-1][0]=VertexList[j][0];
				VertexList[j-1][1]=VertexList[j][1];
				VertexList[j-1][2]=VertexList[j][2];
				VertexList[j-1][3]=VertexList[j][3];
				VertexList[j-1][4]=VertexList[j][4];
			}

			//ԭ�������һ�������־Ϊ������
			IsVertexList[VertexCount-1]=false;
			--VertexCount;
			--i;
		}
	}

	//���㽻��
	LineCount=VertexCount;//�߶�����
	pVertex1=pVertex2=NULL;
	for(i=0,c=0;c<LineCount;++i)
	{
		index=i%VertexCount;

		//��ǰ�������
		if(IsVertexList[index])
		{
			if(!pVertex1)
			{
				pVertex1=VertexList[index];
			}
			else
			{
				pVertex2=VertexList[index];
			}
		}

		if(pVertex1&&pVertex2)
		{
			//�����߶�����
			++c;

			//�иǰ�߶�
			//��Ļ��߽���
			rt=GetIntersection2(0,
				pVertex1[0],pVertex1[1],pVertex1[2],pVertex1[3],pVertex1[4],
				pVertex2[0],pVertex2[1],pVertex2[2],pVertex2[3],pVertex2[4],
				x,y,z,u,v
				);
			if(rt)
			{
				//���Ų��һ����λ��
				for(j=VertexCount-1;j>=i;--j)
				{
					IsVertexList[j+1]=IsVertexList[j];
					VertexList[j+1][0]=VertexList[j][0];
					VertexList[j+1][1]=VertexList[j][1];
					VertexList[j+1][2]=VertexList[j][2];
					VertexList[j+1][3]=VertexList[j][3];
					VertexList[j+1][4]=VertexList[j][4];
				}

				//���뽻����Ϊ�µĶ���
				VertexList[i][0]=x;
				VertexList[i][1]=y;
				VertexList[i][2]=z;
				VertexList[i][3]=u;
				VertexList[i][4]=v;
				IsVertexList[i]=true;
				++VertexCount;

				++i;

				//������һ���߶εĵ�һ���˵�
				pVertex1=VertexList[index+1];
				pVertex2=NULL;
			}
			else
			{
				//������һ���߶εĵ�һ���˵�
				pVertex1=pVertex2;
				pVertex2=NULL;
			}
		}
	}


	//�޳����ɼ�����
	pVertex1=pVertex2=NULL;
	for(i=0;i<VertexCount;++i)
	{
		x=VertexList[i][0];
		y=VertexList[i][1];

		//�����ǰ���㲻�ɼ�
		if(x<0)
		{
			//ɾ����ǰ����:�Ѻ���Ķ���Ų����,���ǵ�ǰ����
			for(j=i+1;j<VertexCount;++j)
			{
				IsVertexList[j-1]=IsVertexList[j];
				VertexList[j-1][0]=VertexList[j][0];
				VertexList[j-1][1]=VertexList[j][1];
				VertexList[j-1][2]=VertexList[j][2];
				VertexList[j-1][3]=VertexList[j][3];
				VertexList[j-1][4]=VertexList[j][4];
			}

			//ԭ�������һ�������־Ϊ������
			IsVertexList[VertexCount-1]=false;
			--VertexCount;
			--i;
		}
	}

	//���㽻��
	LineCount=VertexCount;//�߶�����
	pVertex1=pVertex2=NULL;
	for(i=0,c=0;c<LineCount;++i)
	{
		index=i%VertexCount;

		//��ǰ�������
		if(IsVertexList[index])
		{
			if(!pVertex1)
			{
				pVertex1=VertexList[index];
			}
			else
			{
				pVertex2=VertexList[index];
			}
		}

		if(pVertex1&&pVertex2)
		{
			//�����߶�����
			++c;

			//�иǰ�߶�
			//��Ļ�ұ߽���
			rt=GetIntersection2(m_ScrWidth-1,
				pVertex1[0],pVertex1[1],pVertex1[2],pVertex1[3],pVertex1[4],
				pVertex2[0],pVertex2[1],pVertex2[2],pVertex2[3],pVertex2[4],
				x,y,z,u,v
				);
			if(rt)
			{
				//���Ų��һ����λ��
				for(j=VertexCount-1;j>=i;--j)
				{
					IsVertexList[j+1]=IsVertexList[j];
					VertexList[j+1][0]=VertexList[j][0];
					VertexList[j+1][1]=VertexList[j][1];
					VertexList[j+1][2]=VertexList[j][2];
					VertexList[j+1][3]=VertexList[j][3];
					VertexList[j+1][4]=VertexList[j][4];
				}

				//���뽻����Ϊ�µĶ���
				VertexList[i][0]=x;
				VertexList[i][1]=y;
				VertexList[i][2]=z;
				VertexList[i][3]=u;
				VertexList[i][4]=v;
				IsVertexList[i]=true;
				++VertexCount;

				++i;

				//������һ���߶εĵ�һ���˵�
				pVertex1=VertexList[index+1];
				pVertex2=NULL;
			}
			else
			{
				//������һ���߶εĵ�һ���˵�
				pVertex1=pVertex2;
				pVertex2=NULL;
			}
		}
	}


	//�޳����ɼ�����
	pVertex1=pVertex2=NULL;
	for(i=0;i<VertexCount;++i)
	{
		x=VertexList[i][0];
		y=VertexList[i][1];

		//�����ǰ���㲻�ɼ�
		if(x>=m_ScrWidth)
		{
			//ɾ����ǰ����:�Ѻ���Ķ���Ų����,���ǵ�ǰ����
			for(j=i+1;j<VertexCount;++j)
			{
				IsVertexList[j-1]=IsVertexList[j];
				VertexList[j-1][0]=VertexList[j][0];
				VertexList[j-1][1]=VertexList[j][1];
				VertexList[j-1][2]=VertexList[j][2];
				VertexList[j-1][3]=VertexList[j][3];
				VertexList[j-1][4]=VertexList[j][4];
			}

			//ԭ�������һ�������־Ϊ������
			IsVertexList[VertexCount-1]=false;
			--VertexCount;
			--i;
		}
	}


	if(VertexCount>=3)
	{
		c=0;//���ɨ�����:�ղŵ���VertexCount��ʾ���������ߵķ���

		//ɨ��ü���Ķ���ν���
		for(i=0;c<VertexCount;++i)
		{
			index=i%VertexCount;
			if(IsVertexList[index])
			{
				if(!pVertex1)
				{
					pVertex1=VertexList[index];
				}
				else
				{
					pVertex2=VertexList[index];
				}

				//����Yֵ�����ֵ����Сֵ
				if(IsBegin)
				{
					yy1=VertexList[index][1];
					if(yy1<ymin)ymin=yy1;
					if(yy1>ymax)ymax=yy1;
				}
				else
				{
					ymin=ymax=VertexList[index][1];
				}

				IsBegin=true;
			}

			//��ǰ�߶δ���
			if(pVertex1&&pVertex2)
			{
				//ɨ���߶ν���
				CreateIntersectionArray(
					pVertex1[0],pVertex1[1],pVertex1[2],
					pVertex2[0],pVertex2[1],pVertex2[2],
					pVertex1[3],pVertex1[4],
					pVertex2[3],pVertex2[4]
					);

				//��һ���߶�
				pVertex1=pVertex2;
				pVertex2=NULL;

				++c;
			}
		}

		long w=CAKPicDraw::GetInst(AK_PIC_DRAW_MAX_COUNT-1)->m_Width;
		long h=CAKPicDraw::GetInst(AK_PIC_DRAW_MAX_COUNT-1)->m_Height;
		
		CAKPicDraw *pPicDraw2=CAKPicDraw::GetInst(AK_PIC_DRAW_MAX_COUNT-1);

		//��Ⱦ
		if(ymin<0)ymin=0;
		if(ymax>=m_ScrWidth)ymax=m_ScrWidth-1;
		long yy;
		float zz;
		float uu,vv;
		long u,v;
		float ZStep;
		float UStep,VStep;
		for(yy=ymin;yy<=ymax;++yy)
		{
			switch(m_pIntersectionCountArray[yy])//������
			{
			case 1:
				{
					i=m_XArray[0][yy];
					zz=m_ZArray[0][yy];
					uu=m_UArray[0][yy];
					vv=m_VArray[0][yy];

					//if(zz>=0&&zz<=1)
					//{
					index=yy*m_ScrWidth+i;
					if(zz>m_pZBuffer[index])
					{
						//��ʽ��UV
						u=uu;
						u%=w;
						v=vv;
						v%=h;
						if(u<0)u+=w;
						if(v<0)v+=h;

						//����ͼȡ��ɫ
						unsigned long uColor;
						long index2 = (v*w+u)*4;
						memcpy(&uColor, &pPicDraw2->m_pData[index2], 4);

						if (bIsUseAlpha)
						{
							// alpha ��� �����ɫ=Դ��ɫ*alpha+Ŀ����ɫ*(1-alpha);
							unsigned char *p = (unsigned char *)&uColor;
							BYTE byB = p[0];
							BYTE byG = p[1];
							BYTE byR = p[2];
							BYTE byA = p[3];
							float fA = byA / 255.0f;
							if (fA != 1.0f)
							{
								int i = 0;
							}

							unsigned char *p1 = (unsigned char *)&m_pPicDraw->m_pData[index*4];
							BYTE byB1 = p1[0];
							BYTE byG1 = p1[1];
							BYTE byR1 = p1[2];

							byB = (BYTE)(byB * fA + byB1 * (1 - fA));
							byG = (BYTE)(byG * fA + byG1 * (1 - fA));
							byR = (BYTE)(byR * fA + byR1 * (1 - fA));

							p[0] = byB;
							p[1] = byG;
							p[2] = byR;
						}
						
						//��������
						memcpy(&m_pPicDraw->m_pData[index*4], &uColor, sizeof(unsigned long));
						m_pZBuffer[index] = zz;
					}
					//}
					break;
				}
			case 2:
				{
					zz=m_ZArray[0][yy];
					uu=m_UArray[0][yy];
					vv=m_VArray[0][yy];
					
					float dx=m_XArray[1][yy]-m_XArray[0][yy];

					ZStep=(m_ZArray[1][yy]-m_ZArray[0][yy])/dx;
					UStep=(m_UArray[1][yy]-m_UArray[0][yy])/dx;
					VStep=(m_VArray[1][yy]-m_VArray[0][yy])/dx;

					index=yy*m_ScrWidth+m_XArray[0][yy];
					for(i=m_XArray[0][yy];i<=m_XArray[1][yy];++i)
					{
						//if(zz>=0&&zz<=1)
						//{
						if(zz>m_pZBuffer[index])
						{
							//��ʽ��UV
							u=uu;
							u%=w;
							v=vv;
							v%=h;
							if(u<0)u+=w;
							if(v<0)v+=h;

							//����ͼȡ��ɫ
							unsigned long uColor;
							long index2=(v*w+u)*4;
							memcpy(&uColor,&pPicDraw2->m_pData[index2],4);

							if (bIsUseAlpha)
							{
								// alpha ��� �����ɫ=Դ��ɫ*alpha+Ŀ����ɫ*(1-alpha);
								unsigned char *p = (unsigned char *)&uColor;
								BYTE byB = p[0];
								BYTE byG = p[1];
								BYTE byR = p[2];
								BYTE byA = p[3];
								float fA = byA / 255.0f;
								if (fA != 1.0f)
								{
									int i = 0;
								}

								unsigned char *p1 = (unsigned char *)&m_pPicDraw->m_pData[index*4];
								BYTE byB1 = p1[0];
								BYTE byG1 = p1[1];
								BYTE byR1 = p1[2];

								byB = (BYTE)(byB * fA + byB1 * (1 - fA));
								byG = (BYTE)(byG * fA + byG1 * (1 - fA));
								byR = (BYTE)(byR * fA + byR1 * (1 - fA));

								p[0] = byB;
								p[1] = byG;
								p[2] = byR;
							}

							//��������
							memcpy(&m_pPicDraw->m_pData[index*4],&uColor,sizeof(unsigned long));
							m_pZBuffer[index]=zz;
						}
						//}

						zz+=ZStep;
						uu+=UStep;
						vv+=VStep;

						++index;
					}

					break;
				}
			}
		}
	}
}
