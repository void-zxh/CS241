#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <map>
#include <queue>
using namespace std;
#define ll long long
 
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,m;
int wr[1005],q[10005],dep;
int vis[1005],co[1005],cou;
struct node
{
	int fi,st,id;
	vector<int> ti;
}a[1005];

bool cmp(node xi,node yi)
{
	return xi.st==yi.st?xi.fi>yi.fi:xi.st<yi.st;
}

int main()
{
	int i,x,y; 
	string str="",st;
	while(getline(cin,st))
		str=str+st; 
	int len=str.size();
	for(i=0;i<len;i++)
		if(str[i]=='[')
		{
			i++;
			if(str[i]!='P')
			{
				printf("error\n");
				return 0;
			} 
			i++;
			if(i==len)
			{
				printf("error\n");
				return 0;
			} 
			a[++n].id=0;
			while(i<len&&(str[i]<='9'&&str[i]>='0'))
			{
				a[n].id=a[n].id*10+str[i]-48;
				i++;
			}
			if(str[i]!=' ')
			{
				printf("error\n");
				return 0;
			}
			if(i==len)
			{
				printf("error\n");
				return 0;
			}
			i++; a[n].fi=0;
			while(i<len&&(str[i]<='9'&&str[i]>='0'))
			{
				a[n].fi=a[n].fi*10+str[i]-48;
				i++;
			}
			if(i==len||str[i]!=' ')
			{
				printf("error\n");
				return 0; 
			}
			i++; a[n].st=0;
			while(i<len&&(str[i]<='9'&&str[i]>='0'))
			{
				a[n].st=a[n].st*10+str[i]-48;
				i++;
			}
			if(i==len||str[i]!=' ')
			{
				printf("error\n");
				return 0; 
			}
			while(str[i]==' ')
			{
				i++; y=0;
				while(i<len&&(str[i]<='9'&&str[i]>='0'))
				{
					y=y*10+str[i]-48;
					i++;
				}
				a[n].ti.push_back(y);
				if(i==len||(str[i]!=' '&&str[i]!=']'))
				{
					printf("error\n");
					return 0;
				}
			}
			m+=a[n].ti.size();
		}
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++)
	{
		printf("%d %d\n",a[i].fi,a[i].st);
		for(int j=0;j<a[i].ti.size();j++)
			printf("%d ",a[i].ti[j]);
		printf("\n");
	}
	int now=1,t=a[1].st,l=2,mx=0,to;
	wr[1]=0; 
	q[++dep]=1;
	while(m>0)
	{
		t+=a[now].ti[wr[now]];
		wr[now]++; m--;
		while(l<=n&&a[l].st<t)
		{
			q[++dep]=l;
			l++; 
		}
		for(i=1;i<=dep;i++) 
			if(i!=now&&vis[i]==0)
				a[i].fi=min(a[i].fi+1,10);
		a[now].fi=max(a[now].fi-1,1);
		/*while(l<=n&&a[l].st<=t+1)
		{
			q[++dep]=l;
			l++; 
		}*/
		to=0; mx=0;
		for(i=1;i<=dep;i++)
			if(i!=now&&vis[i]==0)
			{
				if(a[i].fi>mx)
				{
					mx=a[i].fi;
					to=i;
				}
			}
		if(wr[now]==a[now].ti.size())
		{
			vis[now]=1;
			co[++cou]=a[now].id;
			now=to;
			if(now==0&&l<=n)
			{
				now=l;
				l++;
				q[++dep]=now; 
				t=a[now].st;
			}
		}
		else if(to!=0&&a[to].fi>=a[now].fi+2)
			now=to;
	} 
	for(i=1;i<=cou;i++)
		printf("P%d ",co[i]);
	printf("\n");
	return 0;
}
