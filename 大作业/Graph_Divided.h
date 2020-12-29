#ifndef GRAPH_DIVIDED_H
#define GRAPH_DIVIDED_H

#include "Tool.h"
#include "Graph_Basic.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <map>
#include <vector>
#include <queue>
#define fs first
#define sc second
#define debug printf("in c.cpp line %d\n",__LINE__);
using namespace std;

class Graph_Divided
{
    friend class Graph_Dataloader;
private:
    v_edge e[max_edge_size];
    int head[max_node_size];
    int virnode[max_node_size];
    int n,cnt;
    int sub_n;
    int inq[max_node_size];
    double dis[max_node_size];

    void addedge(int x,int y,double w,int nd=0)
    {
        e[++cnt].to=y;e[cnt].next=head[x];head[x]=cnt;e[cnt].w=w;e[cnt].ty=nd;
    }

    int vir_addId(int x)
    {
        if(virnode[x])
            return virnode[x];
        virnode[x]=++sub_n;
        return sub_n;
    }

public:
    Graph_Divided()
    {
        n=0;cnt=1;sub_n=0;
        memset(head,0,sizeof(head));
    }

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

    void build(Graph_Basic& Mg,const int fa[])
    {
        int i,j,x,y;
        n=Mg.n;//n+1~n+sub_n is for vir_node
        cout<<n<<endl;
        ofstream outfile("2.txt");
        for(i=1;i<=n;i++)
            for(j=Mg.head[i];j;j=Mg.e[j].next)
            {
                y=Mg.e[j].to;
                if(fa[i]==fa[y])
                {
                    addedge(i,y,Mg.e[j].w);
                    outfile<<i<<' '<<y<<' '<<Mg.e[j].w<<endl;
                }
                else
                {
                    x=vir_addId(fa[i]);
                    addedge(i,n+x,Mg.e[j].w,y);
                    outfile<<i<<' '<<y<<' '<<Mg.e[j].w<<endl;
                }
            }
        outfile.close();
    }

    void Dijkstra(int st)
    {
        int i,x,y;
        for(i=1;i<=n;i++)
            dis[i]=inf,inq[i]=0;
        dis[st]=0;
        pair<double,int> xi;
        priority_queue<pair<double,int>,vector<pair<double,int> >,greater<pair<double,int> > > q;
        q.push(pair<double,int>(0,st));
        while(!q.empty())
	    {
		    xi=q.top();q.pop();
		    x=xi.sc;
            if(inq[x]) continue;
		    inq[x]=1;
		    for(i=head[x];i;i=e[i].next)
		    {
		    	y=e[i].to;
                if(y>n) y=e[i].ty;
		    	if(dis[y]>xi.fs+e[i].w)
		        {
		    		dis[y]=xi.fs+e[i].w;
                    //cout<<y<<' '<<dis[y]<<endl;
                    q.push(pair<double,int>(dis[y],y));
                }
		    }   
    	}
    }
};

#endif