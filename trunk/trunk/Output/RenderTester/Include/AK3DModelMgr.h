//AK3D ģ�͹�����
#ifndef _AK3DMODELMGR_H_
#define _AK3DMODELMGR_H_

#include "AK3DBonesMgr.h"
#include "AK2DUI.h"

//AK3D ����νṹ
struct AK3D_POLYGON
{
	//��������(3��4)
	unsigned char uVertexCount;

	//����ָ������
	struct AK3D_VERTEX *pVertexList[4];

	//����UV����
	float UVList[4][2];

	//�������ɫ
	unsigned char r,g,b;
};

//AK3D ģ�ͽṹ
struct AK3D_MODEL
{
	//ģ��ID
	unsigned long uID;

	//�����(ÿ��Ԫ�ذ���һ�� struct AK3D_VERTEX * ָ��)
	CAKList VertexList;

	//����α�(ÿ��Ԫ�ذ���һ�� struct AK3D_POLYGON * ָ��)
	CAKList PolygonList;

	//��ͼ
	struct AK_2D_UI_PIC *pUIPic;

	//��������(ģ�ͼ�ȥ������,���������ϵԭ��,���罫���㶨Ϊ�������λ��,����ȥ�˽����,����ȫ���Խ��ƶ�������ϵԭ��)
	float xFocus,yFocus,zFocus;

	//Ŀ��任����
	float DestMatrix[4*4];

	//�����������
	CAK3DBonesMgr BonesMgr;
};

class CAK3DModelMgr
{
public:

	//����ģ��Ŀ�����
	void SetModelMatrix(struct AK3D_MODEL *pModel,float *pMatrix);

	//ˢ��ģ����ʾ����(�����ڵ���SetModelMatrix����֮��,Ӧ�õ��ô˺���)
	void UpdateModel(struct AK3D_MODEL *pModel);

	//��������
	struct AK3D_VERTEX *CreateVertex(
	struct AK3D_MODEL *pModel,//ģ��
		float x,float y,float z//����
		);

	//���Ҷ����ַ(����λ�ڶ�����λ��,λ�ô�0��ʼ)
	struct AK3D_VERTEX *FindVertex(
	struct AK3D_MODEL *pModel,//ģ��
		unsigned long uPos//λ�ڶ�����λ��(>=0)
		);

	//���Ҷ���λ�õ�ֵ+1;0=û���ҵ�
	unsigned long GetVertexPos(
	struct AK3D_MODEL *pModel,//ģ��
	struct AK3D_VERTEX *pVertex//�����ַ
		);

	//���������
	struct AK3D_POLYGON *CreatePolygon(
	struct AK3D_MODEL *pModel,//ģ��
		unsigned char uCount,//��������(3��4)
		unsigned long uPos1,//����λ��1
		unsigned long uPos2,//����λ��2
		unsigned long uPos3,//����λ��3
		unsigned long uPos4=0//����λ��4
		);

	//����ģ��
	struct AK3D_MODEL *CreateModel(
		unsigned long uID//ģ��ID
		);
	
	//����ģ��
	struct AK3D_MODEL *FindModel(
		unsigned long uID//ģ��ID
		);

	//����޸�ģ�Ͷ���
	void RandomModifModelVertex(
	struct AK3D_MODEL *pModel,
		long dx,//X�����޸ķ�Χ
		long dy,//Y�����޸ķ�Χ
		long dz//Z�����޸ķ�Χ
		);

	//����������(����)
	struct AK3D_MODEL *CreateModel_Box(
		unsigned long uID,//ģ��ID
		float x,float y,float z,//���Ͻ�����
		float width,float length,float height//����
		);

	//����������(����)
	struct AK3D_MODEL *CreateModel_Gridding(
		unsigned long uID,//ģ��ID
		float x,float y,float z,//���Ͻ�����
		float width,float length,//��
		long rows,long cols//����������
		);

	CAK3DModelMgr();

	~CAK3DModelMgr();

	static CAK3DModelMgr & GetSingle()
	{
		static CAK3DModelMgr Single;
		return Single;
	}

protected:

	//ģ���б�(ÿ��Ԫ�ذ���һ�� struct AK3D_MODEL * ָ��)
	CAKList m_ModelList;
};

#endif