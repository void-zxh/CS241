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
}fe[500005]; 

int n,m,cnt=1,summ,mi;
int head[3005],fa[3005],sz[3005];
int wei[3005],vi[3005];
int vis[3005]; 

void addedge(int x,int y,int w)
{
	e[++cnt].to=y;e[cnt].next=head[x];head[x]=cnt;e[cnt].w=w;
}

void join(int x,int y)
{
	vis[y]=1;
	int fx=fa[x],fy=fa[y];
	sz[fy]--;
	sz[fx]++;
	for(int i=head[y];i;i=e[i].next)
		if(fa[e[i].to]==fa[x])
			vi[fa[x]]+=2*e[i].w;
		else if(fa[e[i].to]==fy)
			vi[fy]-=2*e[i].w;
	fa[y]=fa[x]; 
}

void join2(int x,int y)
{
	int fx=fa[x],fy=fa[y];
	sz[fy]--;
	sz[fx]++;
	for(int i=head[y];i;i=e[i].next)
		if(fa[e[i].to]==fa[x])
			vi[fa[x]]+=2*e[i].w;
		else if(fa[e[i].to]==fy)
			vi[fy]-=2*e[i].w;
	fa[y]=fa[x]; 
}

int main()
{
	freopen("1.txt","r",stdin);
	freopen("2.out","w",stdout);
	int i,j,k,kiin,cio,x,y,w;
	n=read(); m=read(); mi=read();
	for(i=1;i<=m;i++)
	{
		x=read(); y=read(); w=read();
		summ+=w;
		addedge(x,y,w);
		addedge(y,x,w);
		//cout<<x<<' '<<y<<' '<<w<<endl;  
		fe[i].x=x; fe[i].y=y; fe[i].w=w;
		wei[x]+=w; wei[y]+=w;
	}
	for(i=1;i<=n;i++)
	{
		fa[i]=i;
		sz[i]=1;
		vi[i]=0;
	}
	double deltaq,ansq;
	int sx,sy,fx,fy;
	while(1)
	{
		ansq=-0x3f3f3f3f; sx=0; sy=0;
		for(i=1;i<=n;i++)
			for(j=head[i];j;j=e[j].next)
			{
				y=e[j].to;
				if(vis[i]==0&&fa[i]!=fa[y]&&sz[fa[y]]+1<=mi)
				{
					kiin=0;
					for(k=head[i];k;k=e[k].next)
						if(fa[e[k].to]==fa[y])
							kiin+=2*e[k].w;
					deltaq=1.0000/(2*summ)*(kiin-vi[fa[i]]*wei[i]*1.0000/summ);
					if(ansq<deltaq)
					{
						ansq=deltaq;
						sx=y; sy=i;
					}
				}
			}
		if(!(ansq>0))
			break;
		join(sx,sy);
		//cout<<ansq<<endl;
	}
	int ans=0;
	for(i=1;i<=m;i++)
		if(fa[fe[i].x]!=fa[fe[i].y])
			ans+=fe[i].w;
	/*for(i=1;i<=n;i++)
		printf("%d ",fa[i]);
	printf("\n");*/ 
	//printf("%d\n",ans);
	double T=10000;
	double p=0.995,li=10,laq;
	int sans;
	while(1)
	{
		ansq=-0x3f3f3f3f; sx=0; sy=0;
		for(i=1;i<=n;i++)
			for(j=head[i];j;j=e[j].next)
			{
				y=e[j].to; 
				if(fa[i]!=fa[y]&&sz[fa[y]]+1<=mi)
				{
					kiin=0; cio=0;
					for(k=head[i];k;k=e[k].next)
						if(fa[e[k].to]==fa[y])
							kiin+=2*e[k].w;
						else if(fa[e[k].to]==fa[i])
							cio+=2*e[k].w;
					deltaq=kiin-cio;
					if(deltaq!=-laq&&ansq<deltaq)
					{
						ansq=deltaq;
						sx=y; sy=i;
					}
				}
			}
		if(!(ansq>0))
		{
			if(T*p>=li)
				T*=p;
			else
				break;
		}
		join2(sx,sy);
		laq=ansq;
		sans=0;
		for(i=1;i<=m;i++)
			if(fa[fe[i].x]!=fa[fe[i].y])
				sans+=fe[i].w;
		ans=min(ans,sans);
		//cout<<ansq<<endl;
	}
	cout<<ans<<endl;
	/*T=10000; li=10; p=0.995;
	while(1)
	{
		ansq=-0x3f3f3f3f; sx=0; sy=0;
		for(i=1;i<=n;i++)
			for(j=i+1;j<=n;j++)
			{
				y=j; 
				if(fa[i]!=fa[y]&&sz[fa[y]]+1<=mi)
				{
					kiin=0;
					for(k=head[i];k;k=e[k].next)
						if(fa[e[k].to]==fa[y])
							kiin+=2*e[k].w;
					deltaq=1.0000/(2*summ)*(kiin-vi[fa[i]]*wei[i]*1.0000/summ);
					if(deltaq!=-laq&&ansq<deltaq)
					{
						ansq=deltaq;
						sx=y; sy=i;
					}
				}
			}
		if(!(ansq>0))
		{
			if(T*p>=li)
				T*=p;
			else
				break;
		}
		join2(sx,sy);
		laq=ansq;
		sans=0;
		for(i=1;i<=m;i++)
			if(fa[fe[i].x]!=fa[fe[i].y])
				sans+=fe[i].w;
		ans=min(ans,sans);
		cout<<ansq<<endl;
	}*/
	/*ans=0;
	for(i=1;i<=m;i++)
		if(fa[fe[i].x]!=fa[fe[i].y])
			ans+=fe[i].w;*/
	/*for(i=1;i<=n;i++)
		printf("%d ",fa[i]);
	printf("\n");*/ 
	return 0;
}

