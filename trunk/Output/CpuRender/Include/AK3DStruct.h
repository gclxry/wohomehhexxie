//AK3D ���ݽṹ

#define NAME_MAX_LEN 24

#include "AKList.h"

//AK3D ����ṹ
struct AK3D_VERTEX
{
	//��������
	float x,y,z;

	//�������ƶ���ṹ�б�(ÿһ��Ԫ�ذ���һ�� struct AK3D_BONES_CTRL * ָ��)
	CAKList BonesCtrlList;

	//Ŀ�궥������
	float xDest,yDest,zDest;
};

//AK3D �����ṹ
struct AK3D_BONES
{
	//����֡�б�(ÿһ��Ԫ�ذ���һ�� struct AK3D_BONES_FRAME * ָ��),�б�����ÿ��֡��Ӧ����һ����������汾
	CAKList FrameList;

	//��ǰ����֡��ַ
	struct AK3D_BONES_FRAME *pCurBonesFrame;

	//��ǰ����֡�汾��Ŀ�����(ֱ�����ڹ�����������任)
	float DestMatrix[4*4];

	//�������ṹ
	struct AK3D_BONES *pFather;

	//�ӹ����ṹ�б�(ÿһ��Ԫ�ذ���һ�� struct AK3D_BONES * ָ��)
	CAKList SonList;

	//����Ψһ����
	char Name[NAME_MAX_LEN+1];

	//����Ψһ���
	unsigned long uID;

	//����
	float xFocus,yFocus,zFocus;
};

//AK3D �������ƶ���ṹ
struct AK3D_BONES_CTRL
{
	//�����ܿ�Ȩֵ
	float Power;

	//����
	struct AK3D_BONES *pBones;
};

//AK3D ����֡�ṹ
struct AK3D_BONES_FRAME
{
	//��ʼ֡(>=0)
	unsigned long uStartFrame;

	//��������
	float Matrix[4*4];

	//Ŀ�����(ֱ�������ڶ���)
	float DestMatrix[4*4];

	//�ϼ�����֡�ṹ(��Ӧͬһ֡)
	struct AK3D_BONES_FRAME *pFrontFrame;
};
