#include"ALGraph.h"
#include"iostream"
#include<stdlib.h>
#include<stdio.h>
FILE*fp;
using namespace std;
void CreateGraph(ALGraph &G)
{
	int i,j,k;
	WeightType weight;
	VertexType vi,vj;
	ArcNode *p;
	cout<<"�����붥����������������"<<endl;
	cin>>G.vexnum;
	cin>>G.arcnum;
	cin>>G.kind;
	for(i=0;i<G.vexnum;i++)
	{
		printf("����%d:",i+1);
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc=NULL;
	}
	for(k=0;k<G.arcnum;k++)
	{
		printf("��%d:",k+1);
		cin>>vi;
		cin>>vj;
		printf("��%d��Ȩֵ:",k+1);
		cin>>weight;
		i=LocateVex(G,vi);
		j=LocateVex(G,vj);
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j;
		p->weight=weight;
		p->nextarc=G.vertices[i].firstarc;
		G.vertices[i].firstarc=p;
		if(G.kind==2)
		{
			p=(ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex=i;
			p->weight=weight;
			p->nextarc=G.vertices[j].firstarc;
			G.vertices[j].firstarc=p;
		}
	}
 }
 void SaveGraph(ALGraph &G)
 {
 	int i;
 	ArcNode *p;
 	if((fp=fopen("ALGraph.txt","wb"))==NULL){
		cout<<"�޷����ļ�\"hfmTree.txt\""<<endl;
		system("pause");
		exit(0);
	}
	fwrite(&G,sizeof(ALGraph),1,fp);
	for(i=0;i<G.vexnum;i++)
	{
		if(p=G.vertices[i].firstarc)
		while(p)
		{
			fwrite(p,sizeof(ArcNode),1,fp);
			p=p->nextarc;
		}
	}
	fclose(fp);
 }
 void CreateGraph_F(ALGraph &G)
 {
 	int i;
 	ArcNode *p,*q;
 	if((fp=fopen("ALGraph.txt","rb"))==NULL){
		cout<<"�޷����ļ�\"hfmTree.txt\""<<endl;
		system("pause");
		exit(0);
	}
	fread(&G,sizeof(G),1,fp);
	for(i=0;i<G.vexnum;i++)
	if(G.vertices[i].firstarc)
	{
		p=(ArcNode*)malloc(sizeof(ArcNode));
		fread(p,sizeof(ArcNode),1,fp);
		G.vertices[i].firstarc=q=p;
		p=p->nextarc;
		while(p!=NULL)
		{
			p=(ArcNode*)malloc(sizeof(ArcNode));
			fread(p,sizeof(ArcNode),1,fp);
			q->nextarc=p;
			q=q->nextarc;
			p=p->nextarc;
		}
	}
	fclose(fp);
 }
 int LocateVex(ALGraph G,VertexType v)
 {
 	int i;
 	for(i=0;i<G.vexnum;i++)
 	if(G.vertices[i].data==v)return i;
 	return -1;
 }
void InsertArc(ALGraph &G,int i,int j,WeightType weight)
{
	ArcNode *p;
	if(i!=-1&&j!=-1)
	{
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j;
		p->weight=weight;
		p->nextarc=G.vertices[i].firstarc;
		G.vertices[i].firstarc=p;
		if(G.kind==3)
		{
			p=(ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex=i;
			p->weight=weight;
			p->nextarc=G.vertices[j].firstarc;
			G.vertices[j].firstarc=p;
		}
	}
}
void Prim(ALGraph &G,ALGraph &T)
{
	int i,j;
	int a[MAX_VERTEX_NUM],b[2]={0,0};
	WeightType weight;
	ArcNode *p;
	T=G;
	for(i=0;i<G.vexnum;i++)
	{
		a[i]=0;
		T.vertices[i].firstarc=NULL;
	}
	a[0]=1;
	printf("��С�������ıߣ�\n");
	for(i=1;i<G.vexnum;i++)
	{
		weight=MAX_WEIGHT;
		for(j=1;j<G.vexnum;j++)
		if(a[j]==0)
		for(p=G.vertices[j].firstarc;p;p=p->nextarc)
		if(p->weight<weight&&a[p->adjvex])
		{
			weight=p->weight;
			b[0]=j;
			b[1]=p->adjvex;
		}
		a[b[0]]=1;
		printf("(%d,%d)	",b[0],b[1]);
		InsertArc(T,b[0],b[1],weight);
	}
	printf("\n");
}
void PrintGraph(ALGraph G)
{
	int i;
	ArcNode *p;
	printf("vexnum:%d	arcnum:%d	kind:%d\n",G.vexnum,G.arcnum,G.kind);
	for(i=0;i<G.vexnum;i++)
	{
		cout<<G.vertices[i].data;
		p=G.vertices[i].firstarc;
		while(p)
		{
			printf("-->(%.1f)%c",p->weight,G.vertices[p->adjvex].data);
			p=p->nextarc;
		}
		printf("\n");
	}
}
int main()
{
	int i;
	ALGraph G,T;
	cout<<"������ͼ��1.�ֶ�����	2.���ļ���ȡ"<<endl;
	cin>>i;
	if(i==1)
	{
		cout<<"�Ƿ�����ļ���	1.��	2.��"<<endl;
		cin>>i;
		if(i==1)
		{
			CreateGraph(G);
			SaveGraph(G);
		}
		else
		CreateGraph(G);
	}
	else
	CreateGraph_F(G);
	cout<<"�ܵ�����"<<endl;
	PrintGraph(G);
	Prim(G,T);
	cout<<"��С������(��)��"<<endl;
	PrintGraph(T);
	return 0;
}
