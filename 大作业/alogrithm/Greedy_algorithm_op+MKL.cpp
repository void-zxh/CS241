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

int n,m,cnt=1,mi,range=5;;
double ans=0x3f3f3f3f,dis;
int head[3005];
double vi[3005][3005],wi[3005][3005],hi[3005][3005];
int sub_root[3005],fa[3005],sz[3005]; 
int nodecou,epoch,item; 
priority_queue<val> q,vq,vq2;

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
	clear(vq);
	//memset(sub_root,0,sizeof(sub_root));
	memset(fa,0,sizeof(fa));
	memset(sz,0,sizeof(sz));
	memset(vi,0,sizeof(vi));
	memset(wi,0,sizeof(wi));
	//memset(hi,0,sizeof(hi));
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

void Muti_KL_work(int step)
{
	int i,j,x,tx,y,ty,ti,to;
	int on1=0,tcou=0;
	double nowans=dis;
	val xi;
	for(i=1;i<=n;i++)
		for(j=head[i];j;j=e[j].next)
			wi[i][fa[e[j].to]]+=e[j].w;
	for(i=1;i<=n;i++)
		for(j=1;j<=nodecou;j++)
			if(fa[i]!=j)
			{
				hi[i][j]=wi[i][j]-wi[i][fa[i]];
				vq.push(val(i,j,hi[i][j]));
			}
	//if(step==545)
	//	cout<<nowans<<endl;
	for(ti=1;ti<=item;ti++)
	//int itc=0;
	//while(1)
	{
		//itc++;
		while(1)
		{
			xi=vq.top();vq.pop();
			x=xi.x; y=xi.y;
			if(fa[x]==y) continue;
			if(hi[x][y]!=xi.w) continue;
			break;	
		}
		clear(vq2); 
		for(i=1;i<=n;i++)
			if(fa[i]==y)
				vq2.push(val(i,fa[x],hi[i][fa[x]]));
		xi=vq2.top();vq2.pop();
		tx=xi.x; ty=fa[x];
		//if(step==545)
		//	cout<<hi[x][y]<<" "<<hi[tx][ty]<<endl;
		nowans=nowans-(hi[x][y]+hi[tx][ty]);
		//if(step==545)
		//	cout<<nowans<<endl; 
		on1=0;
		for(i=head[x];i;i=e[i].next)
		{
			to=e[i].to;
			if(to==tx)
				nowans+=2*e[i].w; 
		}
		/*if(step==545)
		{
		cout<<x<<' '<<y<<' '<<endl;
		cout<<tx<<' '<<ty<<' '<<endl; 
		cout<<nowans<<endl;
		}*/
		if(nowans<dis)
		{
			dis=nowans;
		//	tcou=0;
		}
		/*else
		{
			tcou++;
			if(tcou>=20)
				break;
		} */
		for(i=head[x];i;i=e[i].next)
		{
			to=e[i].to;
			//cout<<to<<" "<<e[i].w<<endl; 
			if(to!=tx)
			{
				hi[to][ty]-=e[i].w;
				hi[to][y]+=e[i].w;
				if(fa[to]==y)
				{
					for(j=1;j<=nodecou;j++)
					{
						hi[to][j]-=e[i].w;
						if(fa[to]!=j)	
							vq.push(val(to,j,hi[to][j]));
					}
				}
				else if(fa[to]==ty)
				{
					for(j=1;j<=nodecou;j++)
					{
						hi[to][j]+=e[i].w;	
						if(fa[to]!=j)
							vq.push(val(to,j,hi[to][j]));
					}
				} 
				else
				{
					vq.push(val(to,ty,hi[to][ty]));
					vq.push(val(to,y,hi[to][y]));
				}
			}
		}
		for(i=head[tx];i;i=e[i].next)
		{
			to=e[i].to;
			if(to!=x)
			{
				hi[to][y]-=e[i].w;
				hi[to][ty]+=e[i].w;
				if(fa[to]==ty)
				{
					for(j=1;j<=nodecou;j++)
					{
						hi[to][j]-=e[i].w;	
						if(fa[to]!=j)
							vq.push(val(to,j,hi[to][j]));
					}
				}
				else if(fa[to]==y)
				{
					for(j=1;j<=nodecou;j++)
					{
						hi[to][j]+=e[i].w;	
						if(fa[to]!=j)
							vq.push(val(to,j,hi[to][j]));
					}
				} 
				else
				{
					vq.push(val(to,y,hi[to][y]));
					vq.push(val(to,ty,hi[to][ty]));
				}
			}
		} 
		fa[x]=y; fa[tx]=ty;
		for(i=1;i<=nodecou;i++)
		{
			hi[tx][i]=0;
			hi[x][i]=0;
		}
		for(i=head[x];i;i=e[i].next)
			hi[x][fa[e[i].to]]+=e[i].w;
		for(i=head[tx];i;i=e[i].next)
			hi[tx][fa[e[i].to]]+=e[i].w;
		for(i=1;i<=nodecou;i++)
		{
			if(i!=fa[x]) 
			{
				hi[x][i]-=hi[x][fa[x]];
				vq.push(val(x,i,hi[x][i])); 
			}
			if(i!=fa[tx])
			{
				hi[tx][i]-=hi[tx][fa[tx]];
				vq.push(val(tx,i,hi[tx][i]));	
			}
		}
	} 
	//printf("Work%d: %lf ",step,dis);
	//printf("Work%d(%d): %lf ",step,itc,dis);
	ans=min(ans,dis);
	//printf("Current loss: %lf\n",ans);
//	if(itc>=item)
//		system("pause"); 
}

void calc_out()
{
	double sum=0;
	for(int i=1;i<=m;i++)
		if(fa[fe[i].x]!=fa[fe[i].y])
			sum+=fe[i].w;
	dis=sum;
}

int main()
{
	//freopen("1.txt","r",stdin);
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
	epoch=400;item=50;
	for(ti=1;ti<=epoch;ti++)
	{
		rebuild(); 
		rand_sub();
		Greedy_work();
		calc_out();
		Muti_KL_work(ti);
	}
	//printf("Best: %lf\n",ans);
	printf("%lf\n",ans);
	return 0;
}

