#ifndef NODERECOGNITION_H
#define NODERECOGNITION_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <string>
#include <map>
#include <queue>

using namespace std;

struct edge
{
    int to,next;
};

struct node
{
    int cl,v,sz;
};

bool cmp(node x,node y)
{
    if(x.cl<y.cl)
        return 1;
    else if(x.cl>y.cl)
        return 0;
    else
    {
        if(x.sz==1&&y.sz==1)
            return x.v<y.v;
        else if(x.sz==1)
            return 1;
        else if(y.sz==1)
            return 0;
        else
            return x.v==y.v?x.sz<y.sz:x.v<y.v;
    }
}

class NodeRecognition
{
private:
    int n,cnt,cli,m,to,on1;
    edge e[10005];
    map<int,int>mp;
    int wi[505];
    int indeg[505];
    int head[505];
    int vis[505];
    node ty[505];
    int dep,q[10005];

    void addedge(int x,int y)
    {
        e[++cnt].to=y;e[cnt].next=head[x];head[x]=cnt;
    }

    void dfs(int x)
    {
        int i,y,cou=0;
        q[++dep]=x;
        vis[x]=to;
        for(i=head[x];i!=0;i=e[i].next)
        {
            y=e[i].to;
            cou++;
            if(indeg[y]>1)
                cli=3;
            if(vis[y]!=0)
            {
                cli=3;
                to=min(to,vis[y]);
                continue;
            }
            dfs(y);
        }
        if(cou>2&&cli!=3)
            cli=2;
    }
public:
    NodeRecognition()
    {
        n=0;cnt=0;cli=0;to=0;m=0;on1=1;
        dep=0; memset(q,0,sizeof(q));
        mp.clear();
        memset(e,0,sizeof(e));
        memset(wi,0,sizeof(wi));
        memset(head,0,sizeof(head));
        memset(indeg,0,sizeof(indeg));
        memset(vis,0,sizeof(vis));
        memset(ty,0,sizeof(ty));
    }
    void read(const string& str)
    {
        int len=str.size(),i,x,y;
        for(i=0;i<len;i++)
            if(str[i]=='<')
            {
                i++; x=0;
                if(i==len||!(str[i]>='0'&&str[i]<='9'))
                {
                    on1=0;
                    break;
                }
                while(i<len&&str[i]>='0'&&str[i]<='9')
                {
                    x=x*10+str[i]-48;
                    i++;
                }
                if(mp.find(x)==mp.end())
                {
                    mp[x]=++n;
                    wi[n]=x;
                    x=n;
                }
                else
                    x=mp[x];
                if(str[i]=='>')
                    continue;
                else
                {
                    if(i==len)
                    {
                        on1=0;
                        break;
                    }
                    i++; y=0;
                    if(!(str[i]>='0'&&str[i]<='9'))
                    {
                        on1=0;
                        break;
                    }
                    while(i<len&&str[i]>='0'&&str[i]<='9')
                    {
                        y=y*10+str[i]-48;
                        i++;
                    }
                    if(mp.find(y)==mp.end())
                    {
                        mp[y]=++n;
                        wi[n]=y;
                        y=n;
                    }
                    else
                        y=mp[y];
                    addedge(y,x);
                    //printf("%d %d\n",wi[y],wi[x]);
                    indeg[x]++;
                    if(i==len||str[i]!='>')
                    {
                        on1=0;
                        break;
                    }
                }
                if(i==len)
                    break;
            }
    }
    void out()
    {
        printf("%d\n",n);
        for(int i=1;i<=n;i++)
        {
            printf("wi:%d indeg: %d\n",wi[i],indeg[i]);
            for(int j=head[i];j!=0;j=e[j].next)
            {
                int x=e[j].to;
                printf("<%d %d> ",wi[i],wi[x]);
            }
            printf("\n");
        }
    }
    void work()
    {
        if(!on1)
        {
            printf("We have recognized 0 graph.");
            return ;
        }
        int i,x;
        for(i=1;i<=n;i++)
            if(indeg[i]==0)
            {
                //printf("%d\n",wi[i]);
                dep=0;
                cli=1;to=m+1;
                dfs(i);
                if(to==m+1)
                    m++;
                ty[to].cl=cli;
                //printf("%d %d %d %d\n",wi[i],m,cli,dep);
                while(dep>0)
                {
                    x=q[dep--];
                    ty[to].sz++;
                    ty[to].v+=wi[x];
                    vis[x]=to;
                }
            }
        //for(i=1;i<=m;i++)
        //    printf("%d %d %d\n",ty[i].cl,ty[i].v,ty[i].sz);
        for(i=1;i<=n;i++)
            if(vis[i]==0)
            {
                dep=0;cli=3;to=m+1;
                dfs(i);
                if(to==m+1)
                    m++;
                ty[to].cl=cli;
                while(dep>0)
                {
                    x=q[dep--];
                    ty[to].sz++;
                    ty[to].v+=wi[x];
                    vis[x]=to;
                }
            }
        sort(ty+1,ty+m+1,cmp);
        printf("We have recognized %d graph",m);
        if(m>1)
            printf("s");
        printf(".\n");
        for(i=1;i<=m;i++)
        {
            if(ty[i].cl==1)
            {
                if(ty[i].sz==1)
                    printf("--Node. Weight: %d. Size: 1.\n",ty[i].v);
                else
                    printf("--Binary tree. Weight: %d. Size: %d.\n",ty[i].v,ty[i].sz);
            }
            else if(ty[i].cl==2)
                printf("--Tree. Weight: %d. Size: %d.\n",ty[i].v,ty[i].sz);
            else
                printf("--Graph. Weight: %d. Size: %d.\n",ty[i].v,ty[i].sz);
        }
    }
};

#endif
//<2 6> <3 1> <1 6> <4 6> <7 1> <8 1> <0 2> <9 4> <11> <9 0>
//We have recognized 2 graphs.
//--Node. Weight: 11. Size: 1.
//--Graph. Weight: 40. Size: 9.