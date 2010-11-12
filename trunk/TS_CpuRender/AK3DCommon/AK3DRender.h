//AK 3D ��Ⱦ����

#ifndef _AK3DRENDER_H_
#define _AK3DRENDER_H_

#include "../AKPicDrawCommon/AKPicDraw.h"
#include "../AK2DUICommon/AK2DUI.h"
#include "AK3DModelMgr.h"

class CAK3DRender
{
public:

	//������Ȼ���(ZValue���ӷ�Χ����Զ����Z����)
	void ResetZBuffer(float ZValue);

	//ѡ����ȾĿ��
	void SelectPicDraw(CAKPicDraw *pPicDraw);

	//���������Ƿ�ɼ�
	bool IsPolygonDisplay(struct AK3D_VERTEX *v1,struct AK3D_VERTEX *v2,struct AK3D_VERTEX *v3);

	//�������ι�ǿ��
	float GetPolygonPower(struct AK3D_VERTEX *v1,struct AK3D_VERTEX *v2,struct AK3D_VERTEX *v3);

	//��ȡˮƽɨ����y���߶�(xx1,yy1,zz1,xx2,yy2,zz2)�Ľ��㲢������(xx,yy,zz),���ڽ��㷵��true;�����ڷ���false;
	//�������˵㲻���ཻ
	bool GetIntersection1(
		float y,
		float x1,float y1,float z1,
		float x2,float y2,float z2,
		float &xx,float &yy,float &zz
		);

	//��ȡˮƽɨ����y���߶�(xx1,yy1,zz1,xx2,yy2,zz2)�Ľ��㲢������(xx,yy,zz),���ڽ��㷵��true;�����ڷ���false;
	//(���Ӽ���UV)
	//�������˵㲻���ཻ
	bool GetIntersection1(
		float y,
		float x1,float y1,float z1,float u1,float v1,
		float x2,float y2,float z2,float u2,float v2,
		float &xx,float &yy,float &zz,float &uu,float &vv
		);

	//��ȡ��ֱɨ����x���߶�(xx1,yy1,zz1,xx2,yy2,zz2)�Ľ��㲢������(xx,yy,zz),���ڽ��㷵��true;�����ڷ���false;
	//�������˵㲻���ཻ
	bool GetIntersection2(
		float x,
		float x1,float y1,float z1,
		float x2,float y2,float z2,
		float &xx,float &yy,float &zz
		);

	//��ȡ��ֱɨ����x���߶�(xx1,yy1,zz1,xx2,yy2,zz2)�Ľ��㲢������(xx,yy,zz),���ڽ��㷵��true;�����ڷ���false;
	//(���Ӽ���UV)
	//�������˵㲻���ཻ
	bool GetIntersection2(
		float x,
		float x1,float y1,float z1,float u1,float v1,
		float x2,float y2,float z2,float u2,float v2,
		float &xx,float &yy,float &zz,float &uu,float &vv
		);

	//�ü��߶�,�ɼ��򲿷ֿɼ�����true;��ɲ��ɼ�����false;�ü����������(xx1,yy1,zz1,xx2,yy2,zz2)
	bool CutOutLine(
		float x1,float y1,float z1,
		float x2,float y2,float z2,
		float &xx1,float &yy1,float &zz1,
		float &xx2,float &yy2,float &zz2
		);

	//�����߶�ɨ�轻�㼯
	void CreateIntersectionArray(
		float x1,float y1,float z1,
		float x2,float y2,float z2
		);

	//�����߶�ɨ�轻�㼯(���Ӽ���UV)
	void CreateIntersectionArray(
		float x1,float y1,float z1,
		float x2,float y2,float z2,
		float u1,float v1,
		float u2,float v2
		);

	//��Ⱦ������(��Ⱦ��ʽ1)
	void Draw1(
	struct AK3D_VERTEX *v1,//����1
	struct AK3D_VERTEX *v2,//����2
	struct AK3D_VERTEX *v3//����3
		);

	//��Ⱦ�ı���(��Ⱦ��ʽ1)
	void CAK3DRender::DrawRect1(
	struct AK3D_VERTEX *v1,//����1
	struct AK3D_VERTEX *v2,//����2
	struct AK3D_VERTEX *v3,//����3
	struct AK3D_VERTEX *v4//����4
		);

	//��Ⱦ������(��Ⱦ��ʽ2)
	void CAK3DRender::Draw2(
	struct AK3D_VERTEX *v1,//����1
	struct AK3D_VERTEX *v2,//����2
	struct AK3D_VERTEX *v3,//����3
		float *uv1,//����UV1
		float *uv2,//����UV2
		float *uv3,//����UV3
		bool bIsUseAlpha = false//�Ƿ�ʹ��alphaͨ��
		);

	//��Ⱦ�ı���(��Ⱦ��ʽ2)
	void DrawRect2(
	struct AK3D_VERTEX *v1,//����1
	struct AK3D_VERTEX *v2,//����2
	struct AK3D_VERTEX *v3,//����3
	struct AK3D_VERTEX *v4,//����4
		float *uv1,//����UV1
		float *uv2,//����UV2
		float *uv3,//����UV3
		float *uv4,//����UV4
		bool bIsUseAlpha = false//�Ƿ�ʹ��alpha
		);

	//��Ⱦģ��
	void DrawModel(
	struct AK3D_MODEL *pModel,//ģ��
		unsigned short uRenderStyle=1//��Ⱦ��ʽ:0=������ͼ��Ⱦ(���㷴���ǿ);1=������ͼ��Ⱦ(���㷴���ǿ);2=����ͼ��Ⱦ(���Է����ǿ);3=����ͼ��Ⱦ(���㷴���ǿ);
		);

	//����������
#define AK_3D_RENDER_MAX_COUNT 10

	//CAK3DRender����(uIDΪ������:0~AK_3D_RENDER_MAX_COUNT)
	static CAK3DRender *GetInst(unsigned short uID=0)
	{
		static CAK3DRender AK3DRenderList[AK_3D_RENDER_MAX_COUNT];

		if(uID<AK_3D_RENDER_MAX_COUNT)return &AK3DRenderList[uID];
		else return NULL;
	}

	CAK3DRender();

	~CAK3DRender();

protected:

	//��ȾĿ��
	CAKPicDraw *m_pPicDraw;

	//��Ļ���
	long m_ScrWidth,m_ScrHeight;

	//////////////////////////////////////////////////////////////////
	//�����������ɨ���߲����Ľ��㼯��
	float *m_XArray[2];
	float *m_ZArray[2];
	float *m_UArray[2];
	float *m_VArray[2];

	//������������(ָ��ÿ�еĽ�������:0~2)
	unsigned char *m_pIntersectionCountArray;

	//��Ȼ���
	float *m_pZBuffer;
	//////////////////////////////////////////////////////////////////
};

#endif