// Pathplan.cpp: implementation of the Pathplan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RobotView.h"
#include "Pathplan.h"
#include "RobotViewView.h"
#include "MainFrm.h"
#include "Route.h"
#include<iostream>
#include<stdio.h>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Pathplan::Pathplan()
{

}

Pathplan::~Pathplan()
{

}

///////////////////////////////////////////////////////////////

path Pathplan:: GetPath()
{
	return m_resultpath;
}

void Pathplan::GetVmap(int map[MH][NW])
{
	for(int i=0;i<MH;i++)
		for(int j=0;j<NW;j++)
			map[i][j]=m_VMap[i][j];
}
void Pathplan::removeOfItem(int i)//m_removeItem[]�д��Ҫ��8·����S��ɾ����·��������
{
	int j,flag=0;
	for(j=0;j<m_removeNum;j++){
		if(m_removeItem[j]==i){
			flag=1;
			break;
		}
	}
	if(flag==0){
		m_removeItem[m_removeNum]=i;
		m_removeNum++;
	}
}

int Pathplan::pathEqual(path p,path q)// �ж�����·���Ƿ���ͬ�����p��q��ͬ���򷵻�1�����򣬷���0
{
	int i;
	if(p.pathlength!=q.pathlength)
		return 0;
	else{
		for(i=0;i<p.pathlength;i++){
			if(!(p.pos[i].x==q.pos[i].x&&p.pos[i].y==q.pos[i].y))
				return 0;
		}
		return 1;
	}
}

//���ô�ͼ�⴫����ָ�룬�ѵ�ͼ���е������Ϣ����m_VMap��m_VMap�о͵õ��˳�ʼ�ĵ�ͼ��	
void Pathplan::plan(int map[MH][NW])
{
	int i,j;
	for(i=0;i<MH;i++)
	{
		for(j=0;j<NW;j++){
			m_VMap[i][j]=map[i][j];//pinitmap->getEachRouteMap(i,j);
		}
	}
}

//���ó�ʼ��ͼ�������ϰ����λ�ã�����һ�����У������ϰ���ĸ�������m_onum
void Pathplan::setOposition()
{
	int i,j;
	m_onum=0;
	for(i=0;i<MH;i++)
	{
		for(j=0;j<NW;j++)
		{
			if(m_VMap[i][j]==1)
			{
				m_Oposition[m_onum].x=i;
				m_Oposition[m_onum].y=j;
				m_Oposition[m_onum].height=1;
				m_onum++;
			}
		}
	}
}




//////////////////////////////////////////////////////////////////////////////

//�ѳ�ʼ��ͼת��Ϊ��������߶ȵ������ͼ
void Pathplan::setVmap(float Kg, float r, int onum, position Oposition[NW*MH])
{
	int Kobs=20;
	int i,j,k;
	int Mid[MAX],temp;

 	for(i=0;i<MH;i++)
	{
		for(j=0;j<NW;j++)
		{
			Mid[0]=Kg*(sqrt((m_aimpos.x-i)*(m_aimpos.x-i))+sqrt((m_aimpos.y-j)*(m_aimpos.y-j)));//Ŀ����դ���Ӱ��
			for(k=1;k<=onum;k++)//�����ϰ����դ���Ӱ��
			{
				Mid[k]=r*(80-(sqrt((m_aimpos.x-Oposition[k-1].x)*(m_aimpos.x-Oposition[k-1].x))+sqrt((m_aimpos.y-Oposition[k-1].y)*(m_aimpos.y-Oposition[k-1].y))))/(sqrt((Oposition[k-1].x-i)*(Oposition[k-1].x-i))+sqrt((Oposition[k-1].y-j)*(Oposition[k-1].y-j)));
			}
			if(m_onum==0)
				temp=0;
			else
				temp=Mid[1];
			for(int l=1;l<=onum;l++){
				if(temp<Mid[l])
					temp=Mid[l];
			}
			m_VMap[i][j]=temp+Mid[0];//ȡ���ֵ��Ŀ�ĵ��դ���Ӱ��Ϊդ�������߶�
		}
	}
	for(i=0;i<onum;i++){
		Oposition[i].height=80;
		m_VMap[Oposition[i].x][Oposition[i].y]=80;
	}

}
///////////////////////////////////////////////////////////////////////////




//�������ͼ�еõ�Σ���ٽ�ֵ
int Pathplan::getKVH(position Oposition[MH*NW])
{
	int i;
	int temp= Oposition[0].height;
	for(i=0;i<m_onum;i++)
	{
		if(Oposition[i].height<temp)//���ϰ����դ������С������߶�
		{
			temp=Oposition[i].height;
		}
	}
     m_Kvh=temp;
	return m_Kvh ;
}

//���û�����Ŀǰ��λ�ã����ݶ�λģ��õ��Ľӿ�
void Pathplan::setRobotPos(int x,int y)
{ 
	m_robotpos.x=x;
	m_robotpos.y=y;
	m_robotpos.height=m_VMap[x][y];
}

//��һ��·������·������
void Pathplan::pathIntoPlist(path S[MAX], path p,int &num)
{
	S[num]=p;
	num++;
}

//�õ�һ��դ����Χ��դ�񼰸���
void Pathplan::getAround(position u)
{
	if(u.x==0&&u.y==0)
	{
		 m_pos[0].x=1;
		 m_pos[0].y=0;
		 m_pos[0].height=m_VMap[1][0];
		 m_pos[1].x=1;
		 m_pos[1].y=1;
		 m_pos[1].height=m_VMap[1][1];
		 m_pos[2].x=0;
		 m_pos[2].y=1;
		 m_pos[2].height=m_VMap[0][1];
		 m_posnum=3;  //uΪ���½�դ��ʱ
	}
	else if(u.x==0&&u.y==NW-1)
	{
		m_pos[0].x=0;
		 m_pos[0].y=NW-2;
		 m_pos[0].height=m_VMap[0][NW-2];
		 m_pos[1].x=1;
		 m_pos[1].y=NW-2;
		 m_pos[1].height=m_VMap[1][NW-2];
		 m_pos[2].x=1;
		 m_pos[2].y=NW-1;
		 m_pos[2].height=m_VMap[1][NW-1];
		 m_posnum=3;  //uΪ���½�դ��ʱ
	}else if(u.x==MH-1&&u.y==NW-1)
	{
		m_pos[0].x=MH-1;
		 m_pos[0].y=NW-2;
		 m_pos[0].height=m_VMap[MH-1][NW-2];
		 m_pos[1].x=MH-2;
		 m_pos[1].y=NW-2;
		 m_pos[1].height=m_VMap[MH-2][NW-2];
		 m_pos[2].x=MH-2;
		 m_pos[2].y=NW-1;
		 m_pos[2].height=m_VMap[MH-2][NW-1];
		 m_posnum=3;  //uΪ���Ͻ�դ��ʱ
	}else if(u.x==MH-1&&u.y==0)
	{
		m_pos[0].x=MH-1;
		 m_pos[0].y=1;
		 m_pos[0].height=m_VMap[MH-1][1];
		 m_pos[1].x=MH-2;
		 m_pos[1].y=1;
		 m_pos[1].height=m_VMap[MH-2][1];
		 m_pos[2].x=MH-2;
		 m_pos[2].y=0;
		 m_pos[2].height=m_VMap[MH-2][0];
		 m_posnum=3;  //uΪ���Ͻ�դ��ʱ
	}
	else if(u.x==0)
	{
		 m_pos[0].x=0;
		 m_pos[0].y=u.y-1;
		 m_pos[0].height=m_VMap[0][u.y-1];
		 m_pos[1].x=1;
		 m_pos[1].y=u.y-1;
		 m_pos[1].height=m_VMap[1][u.y-1];
		 m_pos[2].x=1;
		 m_pos[2].y=u.y;
		 m_pos[2].height=m_VMap[1][u.y];
		 m_pos[3].x=1;
		 m_pos[3].y=u.y+1;
		 m_pos[3].height=m_VMap[1][u.y+1];
		 m_pos[4].x=0;
		 m_pos[4].y=u.y+1;
		 m_pos[4].height=m_VMap[0][u.y+1];
		 m_posnum=5;  //uΪ������դ��ʱ
	}else if(u.y==0)
	{
		 m_pos[0].x=u.x-1;
		 m_pos[0].y=0;
		 m_pos[0].height=m_VMap[u.x-1][0];
		 m_pos[1].x=u.x-1;
		 m_pos[1].y=1;
		 m_pos[1].height=m_VMap[u.x-1][1];
		 m_pos[2].x=u.x;
		 m_pos[2].y=1;
		 m_pos[2].height=m_VMap[u.x][1];
		 m_pos[3].x=u.x+1;
		 m_pos[3].y=1;
		 m_pos[3].height=m_VMap[u.x+1][1];
		 m_pos[4].x=u.x+1;
		 m_pos[4].y=0;
		 m_pos[4].height=m_VMap[u.x+1][0];
		 m_posnum=5;  //uΪ������դ��ʱ
	}else if(u.x==MH-1)
	{
		 m_pos[0].x=MH-1;
		 m_pos[0].y=u.y-1;
		 m_pos[0].height=m_VMap[MH-1][u.y-1];
		 m_pos[1].x=MH-2;
		 m_pos[1].y=u.y-1;
		 m_pos[1].height=m_VMap[MH-2][u.y-1];
		 m_pos[2].x=MH-2;
		 m_pos[2].y=u.y;
		 m_pos[2].height=m_VMap[MH-2][u.y];
		 m_pos[3].x=MH-2;
		 m_pos[3].y=u.y+1;
		 m_pos[3].height=m_VMap[MH-2][u.y+1];
		 m_pos[4].x=MH-1;
		 m_pos[4].y=u.y+1;
		 m_pos[4].height=m_VMap[MH-1][u.y+1];
		 m_posnum=5;  //uΪ������դ��ʱ
	}else if(u.y==NW-1)
	{
		 m_pos[0].x=u.x-1;
		 m_pos[0].y=NW-1;
		 m_pos[0].height=m_VMap[u.x-1][NW-1];
		 m_pos[1].x=u.x-1;
		 m_pos[1].y=NW-2;
		 m_pos[1].height=m_VMap[u.x-1][NW-2];
		 m_pos[2].x=u.x;
		 m_pos[2].y=NW-2;
		 m_pos[2].height=m_VMap[u.x][NW-2];
		 m_pos[3].x=u.x+1;
		 m_pos[3].y=NW-2;
		 m_pos[3].height=m_VMap[u.x+1][NW-2];
		 m_pos[4].x=u.x+1;
		 m_pos[4].y=NW-1;
		 m_pos[4].height=m_VMap[u.x+1][NW-1];
		 m_posnum=5;  //uΪ������դ��ʱ
	}
	else
	{
		 m_pos[0].x=u.x;
		 m_pos[0].y=u.y-1;
		 m_pos[0].height=m_VMap[u.x][u.y-1];
		 m_pos[1].x=u.x+1;
		 m_pos[1].y=u.y-1;
		 m_pos[1].height=m_VMap[u.x+1][u.y-1];
		 m_pos[2].x=u.x+1;
		 m_pos[2].y=u.y;
		 m_pos[2].height=m_VMap[u.x+1][u.y];
		 m_pos[3].x=u.x+1;
		 m_pos[3].y=u.y+1;
		 m_pos[3].height=m_VMap[u.x+1][u.y+1];
		 m_pos[4].x=u.x;
		 m_pos[4].y=u.y+1;
		 m_pos[4].height=m_VMap[u.x][u.y+1];
		 m_pos[5].x=u.x-1;
		 m_pos[5].y=u.y+1;
		 m_pos[5].height=m_VMap[u.x-1][u.y+1];
		 m_pos[6].x=u.x-1;
		 m_pos[6].y=u.y;
		 m_pos[6].height=m_VMap[u.x-1][u.y];
		 m_pos[7].x=u.x-1;
		 m_pos[7].y=u.y-1;
		 m_pos[7].height=m_VMap[u.x-1][u.y-1];
		 m_posnum=8;  //���м��դ�����Ĳ���
	}
}

//�õ�һ��դ����Χդ�����С����߶�
int Pathplan::getMinHeight(position u)
{
	getAround(u);
	int i=0;
	int heig;
	heig=m_pos[0].height;
	
	for(i=0;i<m_posnum;i++)
	{
		if (m_pos[i].height<heig)
		{
			heig=m_pos[i].height;
		}
	}
	return heig;
}

//��һդ����д�ˮ����
void Pathplan::reserveWater(position &u, int  min)
{
	while(u.height<= min)
	{
		u.height=u.height+1;//����Ϊ1
	}
	m_VMap[u.x][u.y]=u.height;
}

//�õ�һդ��u��Χ��ĳЩդ����Щդ������������ʣ�����߶�С��m_Kvh��ҲС��u������߶ȣ�������midpos[]�У�����������midnum��
void Pathplan::setMidPos(position u)
{
	int i;
	m_midnum=0;
	for(i=0;i<m_posnum;i++)
	{ 
		if(m_pos[i].height<u.height&&m_pos[i].height<m_Kvh)
		{
			m_Midpos[m_midnum]=m_pos[i];
			m_midnum++;
		}
	}
}

//����һ��դ���Ƿ���һ��·����
int Pathplan::testPosInPath(position u,path l)
{
	int i;
	for(i=l.pathlength-1;i>=0;i--)
	//for(i=0;i<l.pathlength;i++)
	{
		if(l.pos[i].x==u.x&&l.pos[i].y==u.y)
		{
			return 1;
		}
	}
    return 0;
}

//�õ�������ĸ�·��
void  Pathplan::getMidPath(path p, position pos[MAX])
{
	int i;
	for(i=0;i<m_midnum;i++)
	{
		m_midpath[i]=p;
		m_midpath[i].pos[p.pathlength]=pos[i];
		m_midpath[i].pathlength=p.pathlength+1;
	}
}

//�õ��������·��
void Pathplan::getIntoPath(path p, path q, position s)
{
	int i,j,pm;
	m_intopath.pathlength=0;
	for(i=0;i<p.pathlength;i++)
	{
		if(p.pos[i].x==s.x&&p.pos[i].y==s.y)
		{
			pm=i;
			break;
		}
	}
	if(pm<=q.pathlength-1)
	{
		m_intopath=p;
	}
	else
	{
		for(i=0;i<q.pathlength;i++)
		{
			m_intopath.pos[i]=q.pos[i];
			m_intopath.pathlength++;
		}
		for(j=pm+1;j<p.pathlength;j++)
		{
			m_intopath.pos[m_intopath.pathlength]=p.pos[j];
			m_intopath.pathlength++;
		}
	}
}

//�ѵ�n��·����·������ɾ��
void Pathplan::removePath(int  n, path  s[MAX],int &num)
{
	int i;
	for(i=n;i<num;i++)
	{
		s[i-1]=s[i];
	}
	num--;
}

//������������
void Pathplan::removeCircle(path &p)
{
	int i,j,k;
	for(i=0;i<p.pathlength;i++)
	{
		for(j=i+1;j<p.pathlength;j++)
		{
			if(p.pos[i].x==p.pos[j].x&&p.pos[i].y==p.pos[j].y)
			{
				for(k=0;k<p.pathlength-j-1;k++)
				{
					p.pos[i+k]=p.pos[j+k];
				}
				p.pathlength=p.pathlength-j+i;
			}
			//
		}
	}
}

//�õ����·��
void Pathplan::getShortest(path s[MAX],int num)
{
	int i;
	m_resultpath=s[0];
	for(i=0;i<num;i++)
	{
		if(s[i].pathlength<m_resultpath.pathlength)
		{
			m_resultpath=s[i];
		}
	}
}

//���û�������һ��Ҫ�����λ��
void Pathplan::setNextStep(path  p)
{
	m_nextstep=p.pos[1];
}

//�������ϵķ������ý���·���滮,����xΪĿ�������꣬yΪĿ���������
void Pathplan::pathPlanAll(/*mapBase *pmap,dataBase *pdata,*/int aimx,int aimy)
{
	int i; 
	int j;
	int k;


	m_Kvh=59;
    m_kg=1;
    m_r=0.4;

    m_Spathnum=0; //·����S��ʼ��Ϊ�ձ�
    m_Mpathnum=0; //·����MI��ʼ��Ϊ�ձ�

	m_aimpos.x=aimx; //Ŀ�������� 
	m_aimpos.y=aimy; //Ŀ���������
	m_aimpos.height=m_VMap[m_aimpos.x][m_aimpos.y];


//    plan(/*pmapbase*/);//ͨ����ͼ�⴫����ָ�룬���ñ��ص�ͼ��Ϣ

    setOposition( );//����ϰ����λ�ú���Ŀ��������m_Oposition[]��m_onum��



    setVmap(m_kg,  m_r,  m_onum, m_Oposition);//�ѵ�ͼ��Ϣת���������ͼ��Ϣ
/*	CRobotViewApp* myapp=(CRobotViewApp*)AfxGetApp();
    CMainFrame* mainframe=(CMainFrame*)myapp->m_pMainWnd;
	GetVmap(mainframe->VirtualMap);
	Route* route=(Route*)mainframe->m_wndSplitter_Horizontal.GetPane(1,0);
	route->DrawRoute();*/


	for(i=0;i<40;i++){
		for(j=0;j<20;j++){
			if(m_VMap[i][j]<10)
				printf("  %d   ",m_VMap[i][j]);
			else if(m_VMap[i][j]!=100)
				printf(" %d   ",m_VMap[i][j]);
			else
				printf("%d   ",m_VMap[i][j]);
		}
		//printf("\n");
	}

    if(m_onum==0)
	{
		m_Kvh=59;
	}
	else
	{
		;//	m_Kvh=getKVH(m_Oposition);//�õ�Σ���ٽ�ֵ
	}

 //   setRobotPos(/*pdatabase*/);//�õ�������Ŀǰ��λ��

	if(m_aimpos.x==m_robotpos.x&&m_aimpos.y==m_robotpos.y)
	{
		;//���Ŀ���ͻ�����λ����ͬ���򲻶������򣬽���·���滮�㷨
	}
	else
	{
		path us;
		us.pos[0]=m_robotpos;
		us.pathlength=1;
		pathIntoPlist(m_S, us,m_Spathnum);//�ѻ����˳�ʼλ�÷ŵ�·����m_S��

		m_Fpathnum=0;//��FΪ��

		int flag=1;//�ж�m_S���Ƿ���ڷ���������·���ı�־��Ϊ1ʱ����ʾ���ڣ�����ѭ��

		while(flag!=0)
		{
			flag=0;
			
			if(m_Spathnum==0)
				break; //���m_S��û��·�����ڣ������ѭ������������û�п���·��
			else
			{
				m_Mpathnum=0; 
				path L=m_S[0];//ȡm_S�ĵ�һ��·��
				removePath(1,m_S,m_Spathnum); //�ѵ�һ��·����·����m_S��ȡ��Ȼ��ɾ��

				
				if(L.pos[L.pathlength-1].x==m_aimpos.x&&L.pos[L.pathlength-1].y==m_aimpos.y)
				{
					pathIntoPlist(m_F, L,m_Fpathnum);//��·��������һ������·������Ѵ�·���ŵ�·����F��

					for(i=0;i<m_Spathnum;i++)//�����Ƿ�ɼ���ѭ��
					{
						if(!(m_S[i].pos[m_S[i].pathlength-1].x==m_aimpos.x&&m_S[i].pos[m_S[i].pathlength-1].y==m_aimpos.y))
							flag=1;
					}
					continue;
				}
				else//��·���յ㲻��Ŀ���
				{
					int exist=0;//Ϊ0ʱ����ʾ����߶ȶ�����m_Kvh
					int  high=getMinHeight(L.pos[L.pathlength-1]);

					for(i=0;i<m_posnum;i++)
					{
						if(m_pos[i].height<m_Kvh)
						{
							exist=1;
							break;
						}
					}
					if(exist==0)
					{
						for(i=0;i<m_Spathnum;i++)//�����Ƿ�ɼ���ѭ��
						{
							if(!(m_S[i].pos[m_S[i].pathlength-1].x==m_aimpos.x&&m_S[i].pos[m_S[i].pathlength-1].y==m_aimpos.y))
								flag=1;
						}
						continue;
					}
					else{
						int allmax=0;//Ϊ0ʱ����ʾ����߶ȶ�����Lĩ��դ�������߶�
						
						for(i=0;i<m_posnum;i++)
						{
							if(m_pos[i].height<L.pos[L.pathlength-1].height)
							{
								allmax=1;
								break;
							}
						}
						if(allmax==0)
						{
							reserveWater(L.pos[L.pathlength-1], high);
						}

						setMidPos(L.pos[L.pathlength-1]);

						position temp;

						for(i=0;i<m_midnum;i++)//��midpos[]�и�Ԫ�ؽ�������
						{
							for(j=0;j<m_midnum-i;j++)
							{
								if(m_Midpos[i].height<m_Midpos[j].height)
								{
									temp=m_Midpos[i];
									m_Midpos[i]=m_Midpos[j];
									m_Midpos[j]=temp;
								}
							}
						}

						getMidPath(L, m_Midpos); //��������

						int inflag=0;//��־·���Ƿ����ֱ�ӷŵ�M,0�ʺ�
      ////////////////////////////////////////////////////////////////////////////
						m_removeNum=0;
						for(i=0;i<m_midnum;i++)
						{
							inflag=0;
							for(j=0;j<m_Spathnum;j++)
							{
								if(testPosInPath(m_Midpos[i],m_S[j]))
								{
									removeOfItem(j);
									inflag=1;
									getIntoPath(m_S[j],m_midpath[i],m_Midpos[i]);//��������


									int equalflag=0;//������������MI�е�ĳ��·����ͬ���򲻰����ŵ�MI��
									for(int g=0;g<m_Mpathnum;g++){
										if(pathEqual(m_intopath,m_MI[g])==1)
											equalflag=1;
									}
									if(equalflag==0)



										pathIntoPlist(m_MI,m_intopath,m_Mpathnum);//�ѻ����������·����M��

								}
							}
							if(inflag==0)
								pathIntoPlist(m_MI,m_midpath[i],m_Mpathnum);
						}


						//��m_removeItem[]�е�Ԫ�ؽ�������������ǰ�棬�Ա��m_S��ɾ��ʱ����Ų����
						int temp1;
						for(i=0;i<m_removeNum;i++){
							for(j=i+1;j<m_removeNum;j++){
								if(m_removeItem[i]<m_removeItem[j]){
									temp1=m_removeItem[i];
									m_removeItem[i]=m_removeItem[j];
									m_removeItem[j]=temp1;
								}
							}
						}

						for(int in=0;in<m_removeNum;in++){
							for(int ou=0;ou<m_Spathnum;ou++){
								if(m_removeItem[in]==ou)
									removePath(ou+1,m_S,m_Spathnum);
							}
						}


						if(m_Mpathnum!=0){
							for(i=0;i<m_Mpathnum;i++){
								removeCircle(m_MI[i]);
								pathIntoPlist(m_S,m_MI[i],m_Spathnum);
							}
						}
					}
				}
			}
			for(i=0;i<m_Spathnum;i++)
			{
				if(!(m_S[i].pos[m_S[i].pathlength-1].x==m_aimpos.x&&m_S[i].pos[m_S[i].pathlength-1].y==m_aimpos.y))
					flag=1;
			}
		}
		for(i=0;i<m_Spathnum;i++){
			pathIntoPlist(m_F,m_S[i],m_Fpathnum);
		}
		if(m_Fpathnum!=0)
		{
			for(i=0;i<m_Fpathnum;i++){
				removeCircle(m_F[i]);//��ÿ��·��������������
			}
			
			getShortest(m_F, m_Fpathnum);//�õ���̿���·��
			setNextStep(m_resultpath);//������һ��Ҫ�����λ��
			
		}
		else
		{
			;//�Ҳ�������·��
		}
	}
}
//	main(){
	//dataBase *data1;
	//mapBase *map1;
//	Pathplan npath;
//	npath.pathPlanAll(/*map1,data1,*/3,7);
//	}
