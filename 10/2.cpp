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
	for(i=1;i<=n;i++)
	{
		printf("%d %d\n",a[i].fi,a[i].st);
		for(int j=0;j<a[i].ti.size();j++)
			printf("%d ",a[i].ti[j]);
		printf("\n");
	}
	sort(a+1,a+n+1,cmp);
	int now1=1,now2=0,t=a[1].st,t1=a[1].st,t2=0,l=2,mx=0,to;
	q[++dep]=1;
	while(m>0)
	{
		if(now2==0||t1+a[now1].ti[wr[now1]]<t2+a[now2].ti[wr[now2]])
		{ 
			t=t1+a[now1].ti[wr[now1]];
			t1=t;
			wr[now1]++; m--;
			while(l<=n&&a[l].st<t)
			{
				q[++dep]=l;
				l++; 
			}
			for(i=1;i<=dep;i++) 
				if(i!=now1&&i!=now2&&vis[i]==0)
					a[i].fi=min(a[i].fi+1,10);
			a[now1].fi=max(a[now1].fi-1,1);
			if(now2==0)
			{
				now2=l;
				q[++dep]=l;
				l++;
				t2=a[now2].st;
			}
			to=0; mx=0;
			for(i=1;i<=dep;i++)
				if(i!=now1&&i!=now2&&vis[i]==0)
				{
					if(a[i].fi>mx)
					{
						mx=a[i].fi;
						to=i;
					}
				}
			if(wr[now1]==a[now1].ti.size())
			{
				vis[now1]=1;
				co[++cou]=a[now1].id;
				now1=to;
				if(now1==0&&l<=n)
				{
					now1=l;
					l++;
					q[++dep]=now1; 
					t1=a[now1].st;
				}
			}
			else if(to!=0&&a[to].fi>=a[now1].fi+2)
				now1=to;
		}
		else if(t2+a[now2].ti[wr[now2]]<t1+a[now1].ti[wr[now1]])
		{
			t=t2+a[now2].ti[wr[now2]];
			t2=t; 
			wr[now2]++; m--;
			while(l<=n&&a[l].st<t)
			{
				q[++dep]=l;
				l++; 
			}
			for(i=1;i<=dep;i++) 
				if(i!=now1&&i!=now2&&vis[i]==0)
					a[i].fi=min(a[i].fi+1,10);
			a[now2].fi=max(a[now2].fi-1,1);
			to=0; mx=0;
			for(i=1;i<=dep;i++)
				if(i!=now1&&i!=now2&&vis[i]==0)
				{
					if(a[i].fi>mx)
					{
						mx=a[i].fi;
						to=i;
					}
				}
			if(wr[now2]==a[now2].ti.size())
			{
				vis[now2]=1;
				co[++cou]=a[now2].id;
				now2=to;
				if(now2==0&&l<=n)
				{
					now2=l;
					l++;
					q[++dep]=now2; 
					t2=a[now2].st;
				}
			}
			else if(to!=0&&a[to].fi>=a[now1].fi+2)
				now2=to;
		}
		else
		{
			t=t1+a[now1].ti[wr[now1]];
			t1=t; t2=t;
			wr[now1]++; m--; wr[now2]++; m--;
			while(l<=n&&a[l].st<t)
			{
				q[++dep]=l;
				l++; 
			}
			for(i=1;i<=dep;i++) 
				if(i!=now1&&i!=now2&&vis[i]==0)
					a[i].fi=min(a[i].fi+2,10);
			a[now1].fi=max(a[now1].fi-1,1);
			a[now2].fi=max(a[now2].fi-1,1);
			to=0; mx=0;
			for(i=1;i<=dep;i++)
				if(i!=now1&&i!=now2&&vis[i]==0)
				{
					if(a[i].fi>mx)
					{
						mx=a[i].fi;
						to=i;
					}
				}
			if(wr[now1]==a[now1].ti.size()&&wr[now2]!=a[now2].ti.size())
			{
				vis[now1]=1;
				co[++cou]=a[now1].id;
				now1=to;
				if(now1==0&&l<=n)
				{
					now1=l;
					l++;
					q[++dep]=now1; 
					t1=a[now1].st;
				}
			}
			else if(wr[now2]==a[now2].ti.size()&&wr[now1]!=a[now1].ti.size())
			{
				vis[now2]=1;
				co[++cou]=a[now2].id;
				now2=to;
				if(now2==0&&l<=n)
				{
					now2=l;
					l++;
					q[++dep]=now2; 
					t2=a[now2].st;
				}
			}
			else if(wr[now2]==a[now2].ti.size()&&wr[now1]==a[now1].ti.size())
			{
				vis[now1]=1;
				co[++cou]=a[now1].id;
				now1=to;
				if(now1==0&&l<=n)
				{
					now1=l;
					l++;
					q[++dep]=now1; 
					t1=a[now1].st;
				}
				to=0; mx=0;
				for(i=1;i<=dep;i++)
					if(i!=now1&&i!=now2&&vis[i]==0)
					{
						if(a[i].fi>mx)
						{
							mx=a[i].fi;
							to=i;
						}
					}
				vis[now2]=1;
				co[++cou]=a[now2].id;
				now2=to;
				if(now2==0&&l<=n)
				{
					now2=l;
					l++;
					q[++dep]=now2; 
					t2=a[now2].st;
				}
			}
			else if(to!=0)
			{
				if(a[to].fi>=a[now1].fi+2&&a[to].fi>=a[now2].fi+2)
				{
					if(a[now1].fi<=a[now2].fi)
						now1=to;
					else
						now2=to;
				}
				else if(a[to].fi>=a[now1].fi+2)
					now1=to;
				else if(a[to].fi>=a[now2].fi+2)
					now2=to;
			}
		} 
	} 
	for(i=1;i<=cou;i++)
		printf("P%d ",co[i]);
	printf("\n");
	return 0;
}
