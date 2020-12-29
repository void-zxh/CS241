#pragma GCC optimize(2)
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <queue>
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
	int to,next;
	double w;
}e[500005];

struct node
{
	int x,y;
	double w;
	node(int xx=0,int yy=0,double ww=0)
	{
		x=xx; y=yy; w=ww;
	}
}fe[500005]; 

struct val
{
	int x,y;
	double w;
	val(int xx=0,int yy=0,double ww=0)
	{
		x=xx;y=yy;w=ww;
	}
	bool operator<(val x)const
	{
		return w<x.w;
	}
};

int n,m,cnt=1,mi,range=5;
int head[3005];
double vi[3005][3005],ans=0x3f3f3f3f;
int sub_root[3005],fa[3005],sz[3005]; 
int nodecou,epoch; 
priority_queue<val> q;

void clear(priority_queue<val>& q) 
{
	priority_queue<val> empty;
	swap(empty, q);
}

void addedge(int x,int y,double w)
{
	e[++cnt].to=y;e[cnt].next=head[x];head[x]=cnt;e[cnt].w=w;
}

void rebuild()
{
	nodecou=0; 
	clear(q);
	//memset(sub_root,0,sizeof(sub_root));
	memset(fa,0,sizeof(fa));
	memset(sz,0,sizeof(sz));
	memset(vi,0,sizeof(vi));
}

void rand_sub()
{
	int  i,x,basecou=n/mi;
	if(n%mi!=0) basecou++;
	nodecou=basecou+rand()%range;
	for(i=1;i<=nodecou;i++)
	{
		do
		{
			x=rand()%n+1;
		}while(fa[x]!=0);
		//sub_root[i]=x;
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
	for(i=1;i<=n;i++)
		if(fa[i]==0)
			for(j=1;j<=nodecou;j++)	
				q.push(val(i,j,vi[i][j])); 
	int to,ci,delta=n-nodecou;
	val xi;
	while(delta--)
	{
		x=0;y=0;
		while(1)
		{
			xi=q.top();q.pop(); 
			x=xi.x; y=xi.y;
			if(fa[x]) continue;
			if(sz[y]==mi) continue; 
			if(vi[x][y]!=xi.w) continue;
			break;
		}
		fa[x]=y;sz[y]++;
		for(i=head[x];i;i=e[i].next)
		{
			to=e[i].to;
			vi[to][y]+=e[i].w;
			q.push(val(to,y,vi[to][y]));
		}
	}
}

void calc_out(int step)
{
	double sum=0;
	for(int i=1;i<=m;i++)
		if(fa[fe[i].x]!=fa[fe[i].y])
			sum+=fe[i].w;
	ans=min(sum,ans);
	printf("Work%d: %.0lf ",step,sum);
	printf("Current loss: %lf\n",ans);
}

int main()
{
	freopen("1.txt","r",stdin);
	//freopen("2.out","w",stdout);
	int i,j,k,x,y;
	double w;
	n=read(); m=read(); mi=read();
	range=max(range,n/100);
	for(i=1;i<=m;i++)
	{
		x=read(); y=read();
		scanf("%lf",&w);
		fe[i]=node(x,y,w);		
		addedge(x,y,w);addedge(y,x,w);
	}
	int ti;
	epoch=8000;
	for(ti=1;ti<=epoch;ti++)
	{
		rebuild(); 
		rand_sub();
		Greedy_work();
		calc_out(ti);
	}
	printf("Best: %.0lf\n",ans);
	//printf("%d\n",ans);
	return 0;
}

