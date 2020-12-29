#ifndef TREECONSTRUCT_H
#define TREECONSTRUCT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <string>
#include <map>
#include <queue>

bool cmp2(string x,string y)
{
    return x>y;
}

class TreeConstruct
{
    friend void constructcmp(const TreeConstruct& tr1,const TreeConstruct& tr2);
private:
    int n,cnt,root,layer;
    edge e[10005];
    map<string,int>mp;
    int indeg[505];
    int head[505];
    string cd;
    void addedge(int x,int y)
    {
        e[++cnt].to=y;e[cnt].next=head[x];head[x]=cnt;
    }

    string dfs(int x,int dep)
    {
        string res[105],re;
        int i,y,cou=0;
        layer=max(dep,layer);
        for(i=head[x];i!=0;i=e[i].next)
        {
            y=e[i].to;
            res[++cou]=dfs(y,dep+1);
        }
        if(cou==0)
            return string("10");
        else if(cou==1)
        {
            re='1'+res[1]+'0';
            return re;
        }
        else
        {
            re="1";
            sort(res+1,res+cou+1,cmp2);
            for(i=1;i<=cou;i++)
                re=re+res[i];
            re=re+'0';
            return re;
        }
        
    }
public:
    TreeConstruct()
    {
        n=0;cnt=0;root=0;layer=0;
        mp.clear();
        cd="";
        memset(e,0,sizeof(e));
        memset(head,0,sizeof(head));
        memset(indeg,0,sizeof(indeg));
    }
    void read(const string& str)
    {
        int len=str.size(),i,tx,ty;
        string x,y;
        for(i=0;i<len;i++)
            if(str[i]=='<')
            {
                i++; x="";
                while(i<len&&(str[i]>='A'&&str[i]<='Z'||str[i]>='a'&&str[i]<='z'))
                {
                    x=x+str[i];
                    i++;
                }
                if(mp.find(x)==mp.end())
                {
                    mp[x]=++n;
                    tx=n;
                }
                else
                    tx=mp[x];
                if(str[i]=='>')
                    continue;
                else
                {
                    i++; y="";
                    while(i<len&&(str[i]>='A'&&str[i]<='Z'||str[i]>='a'&&str[i]<='z'))
                    {
                        y=y+str[i];
                        i++;
                    }
                    if(mp.find(y)==mp.end())
                    {
                        mp[y]=++n;
                        ty=n;
                    }
                    else
                        ty=mp[y];
                    addedge(ty,tx);
                    //cout<<x<<' '<<y<<endl;
                    indeg[tx]++;
                }
                if(i==len)
                    break;
            }
    }
    void coding()
    {
        int i;
        for(i=1;i<=n;i++)
            if(indeg[i]==0)
            {
                root=i;
                break;
            }
        //cout<<root<<endl;
        cd=dfs(root,1);
    }
};


void constructcmp(const TreeConstruct& tr1,const TreeConstruct& tr2)
{
    printf("%d %d\n",tr1.layer,tr2.layer);
    cout<<tr1.cd<<' '<<tr2.cd<<'\n';
    if(tr1.cd==tr2.cd)
        printf("Yes\n");
    else
        printf("No");
}

#endif