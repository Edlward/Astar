// Pathplan.h: interface for the Pathplan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATHPLAN_H__BFAEA81F_F76C_4EF5_AE02_9520E82CCD59__INCLUDED_)
#define AFX_PATHPLAN_H__BFAEA81F_F76C_4EF5_AE02_9520E82CCD59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include<math.h>
//using namespace move;

#define MAX  200
#define MH    12
#define NW    20





//////////////////////////////////////////////////////////////////////////////////////////
/*��ͼ�е�λ�û�����Ϣ��xΪդ������ĺ����꣬yΪդ������������꣬height��ʾ��λ�õĸ߶�*/
//////////////////////////////////////////////////////////////////////////////////////////
struct position{
    int    x ;
    int    y ;
    int    height;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
/*·���ṹ��pos[]Ϊ·����������դ����ϣ���λ�������ʾ��pathlength��ʾ·����������դ���������·�����ȡ�*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////
struct path{
    position  pos[100];
    int       pathlength;
};

class Pathplan{

private:
	//mapBase *pmapbase;  //��ŵ�ͼָ��
	//dataBase *pdatabase; //������ݿ�ָ��
	int m_VMap[MH][NW];                 //���������ͼ
	position m_aimpos;                //Ŀ��λ��
	position m_Oposition[MH*NW];        //����������ϰ����դ��
	int m_onum;                       //���ϰ����դ��ĸ���
	int m_Kvh;                        //Σ���ٽ�ֵ
	float m_kg;                         //Ϊһ��������������������߶�ʱ�õ�
	float m_r;                          //Ϊһ��������������������߶�ʱ�õ�
	position m_robotpos;              //�����˵ĳ�ʼλ��
	path m_S[MAX];                    //·����
	path m_F[MAX];                    //·����
	path m_MI[MAX];                    //·����
	int m_Spathnum;                   //S����·��������
	int m_Fpathnum;                   //F����·��������
	int m_Mpathnum;                   //M����·��������
	position m_pos[MAX];              //һ��դ����Χ��դ������
	int m_posnum;                     //һ��դ����Χ��դ�����
	position m_Midpos[MAX];           //���Ϸ���������դ��λ��
	int m_midnum;                     //���Ϸ���������դ�����
	path m_midpath[MAX];              //��������Ľ��
	path m_intopath;                  //����������
	path m_resultpath;                //���յõ�������·��
	position m_nextstep;              //��һ��������Ҫ�����λ��
	int m_removeItem[MAX];
	int m_removeNum;

public:
    //�����ݿ���ָ�봫���Լ������ָ����ȥ
	//void setDatabase(dataBase *pdata);
	path GetPath();
	//��ͼ���е�ָ�봫���Լ������ָ����ȥ
	//void setMapbase(mapBase *pmap);
	void GetVmap(int map[MH][NW]);
	//���ô�ͼ�⴫����ָ�룬�ѵ�ͼ���е������Ϣ����m_VMap��m_VMap�о͵õ��˳�ʼ�ĵ�ͼ��
	void plan(int map[MH][NW]);

    //���ó�ʼ��ͼ�������ϰ����λ�ã�����һ�����У������ϰ���ĸ�������m_onum
	void setOposition(/*int map[MH][NW]*/);

	//�ѳ�ʼ��ͼת��Ϊ��������߶ȵ������ͼ
	void setVmap(float Kg, float r, int onum, position Oposition[NW*MH]);

	//�������ͼ�еõ�Σ���ٽ�ֵ
	int getKVH(position Oposition[MH*NW]); 

	//���û�����Ŀǰ��λ�ã����ݶ�λģ��õ��Ľӿ�
	void setRobotPos(int x,int y); 

	//��һ��·������·������
	void pathIntoPlist(path S[MAX], path p ,int &num);

	//�õ�һ��դ����Χ��դ�񼰸���
	void getAround(position u);

	//�õ�һ��դ����Χդ�����С����߶�
	int getMinHeight(position u);

	//��һդ����д�ˮ����
	void reserveWater(position &u, int  min);

	//�õ�һդ��u��Χ��ĳЩդ����Щդ������������ʣ�����߶�С��m_Kvh��ҲС��u������߶ȣ�������midpos[]�У�����������midnum��
	void setMidPos(position u);

	//����һ��դ���Ƿ���һ��·����
	int testPosInPath(position u,path l);

	//�õ�������ĸ�·��
	void  getMidPath(path p, position pos[MAX]);

	//�õ��������·��
	void getIntoPath(path p, path q, position s);

	//��һ��·����·������ɾ��
	void removePath(int  n, path  s[MAX],int &num);

	//������������
	void removeCircle(path &p);

	//�õ����·��
	void getShortest(path s[MAX],int num);

	//���û�������һ��Ҫ�����λ��
	void setNextStep(path  p);

	//�������ϵķ������ý���·���滮
	void pathPlanAll(/*mapBase *pmap,dataBase *pdata,*/int aimx,int aimy);
	void removeOfItem(int i);//���m_removeItem��û��Ԫ����i��ȣ����i�ŵ�����������
	int pathEqual(path p,path q);//����p��q����·���Ƿ���ͬ
public:
	Pathplan();
	virtual ~Pathplan();
};

#endif // !defined(AFX_PATHPLAN_H__BFAEA81F_F76C_4EF5_AE02_9520E82CCD59__INCLUDED_)