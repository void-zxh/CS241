#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
using namespace std;

inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
	return x*f;
}

struct edge
{
	int to,next,w;
}e[500005];

struct node
{
	int x,y,w;
	node(int xx=0,int yy=0,int ww=0)
	{
		x=xx; y=yy; w=ww;
	}
}fe[500005]; 

int n,m,cnt=1,mi,ans=0x3f3f3f3f;
int head[3005],vi[3005][3005];
int sub_root[3005],fa[3005],sz[3005]; 
int nodecou,epoch,id; 

void addedge(int x,int y,int w)
{
	e[++cnt].to=y;e[cnt].next=head[x];head[x]=cnt;e[cnt].w=w;
}

void rebuild()
{
	cnt=1; nodecou=0;
	memset(head,0,sizeof(head));	
	memset(sub_root,0,sizeof(sub_root));
	memset(fa,0,sizeof(fa));
	memset(sz,0,sizeof(sz));
	memset(vi,0,sizeof(vi));
	for(int i=1;i<=m;i++)
	{
		addedge(fe[i].x,fe[i].y,fe[i].w);
		addedge(fe[i].y,fe[i].x,fe[i].w);
	}
}

void rand_sub()
{
	int  i,x,basecou=n/mi;
	if(n%mi!=0) basecou++;
	nodecou=basecou;
	for(i=1;i<=nodecou;i++)
	{
		do
		{
			x=rand()%n+1;
		}while(fa[x]!=0);
		sub_root[i]=x;
		fa[x]=i;sz[i]=1; 
	}
}

void Greedy_work()
{
	int i,j,x,y;
	for(i=1;i<=m;i++)
	{
		x=fe[i].x; y=fe[i].y;
		if(fa[x]==0&&fa[y]!=0)
			vi[x][fa[y]]+=fe[i].w;
		if(fa[y]==0&&fa[x]!=0)
			vi[y][fa[x]]+=fe[i].w;
	}
	int to,ci,delta=n-nodecou;
	while(delta--)
	{
		x=0;y=0;ci=-1;
		if(delta==334)
			to=1;
		for(i=1;i<=n;i++)
			if(fa[i]==0)
			{
				for(j=1;j<=nodecou;j++)
					if(sz[j]<mi)
					{ 
						if(ci<vi[i][j])
						{
							ci=vi[i][j];
							x=i;y=j;
						}
					}
			}
		//printf("%d: %d %d\n",delta,x,y);
		fa[x]=y;sz[y]++;
		for(i=head[x];i;i=e[i].next)
		{
			to=e[i].to;
			vi[to][y]+=e[i].w;
		}
	}
}

void calc_out(int step)
{
	int sum=0;
	for(int i=1;i<=m;i++)
		if(fa[fe[i].x]!=fa[fe[i].y])
			sum+=fe[i].w;
	ans=min(sum,ans);
	printf("Work%d: %d\n",step,sum);
}

int main()
{
	freopen("1.txt","r",stdin);
	int i,j,k,x,y,w;
	n=read(); m=read(); mi=read();
	for(i=1;i<=m;i++)
	{
		x=read(); y=read(); w=read();
		fe[i]=node(x,y,w);		
	}
	int ti;
	epoch=20;
	for(ti=1;ti<=epoch;ti++)
	{
		rebuild(); 
		rand_sub();
		Greedy_work();
		calc_out(ti);
	}
	printf("Best: %d\n",ans);
	return 0;
}

