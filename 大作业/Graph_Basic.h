#ifndef GRAPH_BASIC_H
#define GRAPH_BASIC_H

#include "Graph_Partition.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <map>
#include <vector>
#define debug printf("in c.cpp line %d\n",__LINE__);
using namespace std;

class Graph_Basic
{  
    friend class Graph_Divided;
    friend class Graph_Generator;
    friend class Graph_Dataloader;
    friend class Graph_Partition;
private:
    edge e[max_edge_size];
    int head[max_node_size];
    int fa[max_node_size];
    int vis[max_node_size];
    int n,cnt;
    vector<double> mp[max_node_size];
    vector<int> vnode;
    double ans_loss;
    int work_n;

    void addedge(int x,int y,double w)
    {
        e[++cnt].to=y;e[cnt].next=head[x];head[x]=cnt;e[cnt].w=w;
    }

    void dfs(int x,int fi)
    {
        int i,y;
        vis[x]=1;
        vnode.push_back(x);
        for(i=head[x];i;i=e[i].next)
        {
            y=e[i].to;
            if(y==fi) continue;
            if(vis[y]) continue;
            dfs(y,x);
        }
    }

public:
    Graph_Basic()
    {
        cnt=1; n=0;
        memset(head,0,sizeof(head));
        memset(vis,0,sizeof(vis));
    }
    
    void setn(int x){ n=x; }

    void out()
    {
        for(int i=1;i<=n;i++)  
        {
            cout<<i<<": ";
            for(int j=head[i];j;j=e[j].next)
                cout<<"->("<<e[j].to<<','<<e[j].w<<") ";
            cout<<endl;
        }
    }

    int* segmation_out(){return fa;}

    void Undirected_build(const Graph_Basic& Mg)
    {
        int i,j,x;
        n=Mg.n;
        for(i=1;i<=n;i++)
            for(j=1;j<=n+1;j++)
                mp[i].push_back(0);
        for(i=1;i<=n;i++)
            for(j=Mg.head[i];j;j=Mg.e[j].next)
            {
                mp[i][Mg.e[j].to]+=Mg.e[j].w;
                mp[Mg.e[j].to][i]+=Mg.e[j].w;
            }
        for(i=1;i<=n;i++)
            for(j=i+1;j<=n;j++)
                if(mp[i][j]!=0)
                {
                    addedge(i,j,mp[i][j]);
                    addedge(j,i,mp[i][j]);
                }
    }
    
    void Dfs_seg(Graph_Partition& gp)
    {
        ans_loss=0;work_n=0;
        for(int i=1;i<=n;i++)
            if(!vis[i])
            {
                vnode.clear();
                dfs(i,0);
                gp.build(vnode,e,head);
                //gp.out();
                ans_loss+=gp.segmation(fa,work_n);
                work_n+=vnode.size();
            }
        printf("Final loss: %lf\n",ans_loss);
        /*for(int i=1;i<=n;i++)
            cout<<fa[i]<<' ';
        cout<<endl;*/
    }
};

#endif