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
	int x,y,w;
}e[50005];

int n,m,cnt=1,mi;
int head[3005],vis[3005],ci[3005];
int cou,ans=0x3f3f3f3f;

/*void addedge(int x,int y,int w)
{
	e[++cnt].to=y;e[cnt].next=head[x];head[x]=cnt;e[cnt].w=w;
}*/

void dfs(int x,int dep,int sz)
{
	int i;
	if(dep==n)
	{
		int sum=0;
		for(i=1;i<=m;i++)
			if(vis[e[i].x]!=vis[e[i].y])
				sum+=e[i].w;
		if(sum<ans)
		{
			ans=sum;
			for(i=1;i<=n;i++)
				ci[i]=vis[i];
		}
		return ;
	}
	if(sz<mi)
	{
		sz++; 
		vis[x]=cou;
		if(dep==n-1)
			dfs(i,dep+1,sz);
		else
		{
			for(i=1;i<=n;i++)
			{
				if(vis[i]) continue;
				dfs(i,dep+1,sz); 
			}
		}
		sz=1;
		vis[x]=++cou;
		if(dep==n-1)
			dfs(i,dep+1,sz);
		else
		{
			for(i=1;i<=n;i++)
			{
				if(vis[i]) continue;
				dfs(i,dep+1,sz);
			} 
		}
		cou--;
		vis[x]=0;
	}
	else
	{
		sz=1;
		vis[x]=++cou;
		if(dep==n-1)
			dfs(i,dep+1,sz);
		else
		{
			for(i=1;i<=n;i++)
			{
				if(vis[i]) continue;
				dfs(i,dep+1,sz); 
			}
		}
		vis[x]=0;
		cou--;
	}
}

int main()
{
	freopen("1.txt","r",stdin);
	freopen("1.out","w",stdout);
	int i,x,y,w; 
	n=read(),m=read(); mi=read();
	for(i=1;i<=m;i++)
	{
		e[i].x=read(); 
		e[i].y=read(); 
		e[i].w=read();
	}
	cou++;
	dfs(1,0,0);
	printf("%lf\n",double(ans));
	/*for(i=1;i<=n;i++)
		printf("%d ",ci[i]);
	printf("\n");*/
	return 0;
}

