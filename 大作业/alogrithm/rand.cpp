#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <time.h>
using namespace std;

inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,m,mi;
int fa[10005];
int ei[3005][3005];

int find(int x)
{
	int t=fa[x];
	if(x==fa[x])
		return fa[x];
	fa[x]=find(t);
	return fa[x];
}

void join(int x,int y)
{
	int fx=find(x),fy=find(y);
	if(fx!=fy)
		fa[fx]=fy;
}

int main()
{
	freopen("1.txt","w",stdout);
	srand((unsigned)time(NULL));
	int i,x,y,w;
	n=10; m=10; mi=3;
	printf("%d %d %d\n",n,m,mi);
	for(i=1;i<=n;i++)
		fa[i]=i;
	for(i=1;i<n;i++)
	{
		do
		{
			x=rand()%n+1;
			y=rand()%n+1;
		}while(find(x)==find(y));
		w=rand()%20+1;
		ei[x][y]=1;ei[y][x]=1;
		join(x,y);
		printf("%d %d %d\n",x,y,w); 
	}
	for(i=1;i<=m-n+1;i++)
	{
		do
		{
			x=rand()%n+1;
			y=rand()%n+1;
		}while(ei[x][y]!=0||x==y); 
		w=rand()%20+1;
		printf("%d %d %d\n",x,y,w);
	}
	return 0;
}

