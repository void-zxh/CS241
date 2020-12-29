#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <map>
#include <queue>
#include <utility>
using namespace std;
#define ll long long
#define fs first
#define sc second
#define pi pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,m,cnt; 
int head[100005],vis[100005];
double dis[100005];

struct edge
{
	int to,next;
	double v;
}e[600005];

void addedge(int xi,int yi,double wi)
{
	e[++cnt].to=yi;e[cnt].next=head[xi];head[xi]=cnt;e[cnt].v=wi;
}

void dij(int s)
{
	int i,x,v;
	for(i=1;i<=n;i++)
		dis[i]=0x3f3f3f3f;
	dis[s]=0;
	priority_queue<pi,vector<pi >,greater<pi > > q;
	q.push(pi(0,s));
	while(!q.empty())
	{
		pi xi=q.top();q.pop();
		x=xi.sc;
		if(vis[x]) continue; 
		vis[x]=1;
		for(i=head[x];i!=-1;i=e[i].next)
		{
			v=e[i].to;
			if(dis[v]>xi.fs+e[i].v)
			{
				dis[v]=xi.fs+e[i].v;
				q.push(pi(dis[v],v));
			}
		}
	}
}

int main()
{
	int i,s,x,y;
	double w;
	freopen("1.txt","r",stdin);
	n=read(),m=read(),s=read();
	cout<<n<<' '<<m<<' '<<s<<endl;
	for(i=1;i<=n;i++)
		head[i]=-1; 
	for(i=1;i<=m;i++)
	{
		scanf("<%d %d %lf>\n",&x,&y,&w);
		//cout<<x<<' '<<y<<' '<<w<<endl;
		addedge(x,y,w); 
	} 
	dij(s);
	printf("%lf\n",dis[1]); 
	return 0;
}

