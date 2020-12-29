#ifndef GRAPH_DATALOADER_H
#define GRAPH_DATALOADER_H

#include "Tool.h"
#include "Graph_Basic.h"
#include "Graph_Divided.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <vector>
#define debug printf("in c.cpp line %d\n",__LINE__);
using namespace std;

class Graph_Dataloader
{
private:
    int n,sub_n;
    char addr[1005];
    char subaddr[1005];
    int mp[node_data_size];
    int back[node_data_size];
    int subto[node_data_size];
    vector<int> vp[node_data_size];

    int map_addId(int x)
    {
        if(mp[x])
            return mp[x];
        mp[x]=++n;
        back[n]=x;
        return n;
    }

    int subto_addId(int x)
    {
        if(subto[x])
            return subto[x];
        subto[x]=++sub_n;
        vp[sub_n].clear();
        return sub_n;
    }

    int split(string str,int& x,int& y,double& w)
    {
        int len=str.length(),i=0,cou=0,on1;
        string st[5];
        while(i<len)
        {
            while(i<len&&(str[i]>'9'||str[i]<'0')) i++;
            if(i==len) break;
            cou++;
            if(cou==3)
            {
                on1=0;
                while(i<len&&((str[i]<='9'&&str[i]>='0')||(on1==0&&str[i]=='.')))
                {
                    if(str[i]=='.') on1++;
                    st[cou]+=str[i];
                    i++;
                }
                if(on1>1||st[cou][st[cou].size()-1]=='.')
                {
                    cerr<<"error"<<endl;
                    exit(0);
                }
            }
            else
            {
                while(i<len&&str[i]<='9'&&str[i]>='0')
                {
                    st[cou]+=str[i];
                    i++;
                }
            }
        }
        if(cou==1)
        {
            x=atoi(st[1].c_str());
            return 0;
        }
        else if(cou==3)
        {
            x=atoi(st[1].c_str()); y=atoi(st[2].c_str());
            w=atof(st[3].c_str());
            return 1;
        }
        else
        {
            cerr<<"error"<<endl;
            exit(0);
        }
    }   

    void check_datawrite(const int out_fa[])
    {
        ofstream infile("subgraphcheck.txt");
        int x;
        sub_n=0;
        memset(subto,0,sizeof(subto));
        /*for(int i=1;i<=n;i++)
            cout<<out_fa[i]<<' ';
        cout<<endl;
        for(int i=1;i<=n;i++)
            cout<<mp[i]<<' ';
        cout<<endl;
        for(int i=1;i<=n;i++)
            cout<<back[i]<<' ';
        cout<<endl;*/
        for(int i=1;i<=n;i++)
        {
            x=subto_addId(out_fa[i]);
            vp[x].push_back(back[i]);
        }
        for(int i=1;i<=sub_n;i++)
        {
            for(int j=0;j<vp[i].size();j++)
                infile<<vp[i][j]<<' ';
            infile<<'\n';
        }
        infile.close();
    }

public:
    Graph_Dataloader()
    {
        memset(mp,0,sizeof(mp));
        memset(back,0,sizeof(back));
    }

    void Mout(Graph_Basic& Mg)
    {
        for(int i=1;i<=n;i++)  
        {
            cout<<back[i]<<": ";
            for(int j=Mg.head[i];j;j=Mg.e[j].next)
                cout<<"->("<<back[Mg.e[j].to]<<','<<Mg.e[j].w<<") ";
            cout<<endl;
        }
    }

    void Dout(Graph_Divided& Dg)
    {
        for(int i=1;i<=n;i++)  
        {
            cout<<back[i]<<": ";
            for(int j=Dg.head[i];j;j=Dg.e[j].next)
                cout<<"->("<<back[Dg.e[j].to]<<','<<Dg.e[j].w<<") ";
            cout<<endl;
        }
    }

    void dataload(Graph_Basic& Mg)
    {
        printf("Input the address of the data:");
        scanf("%s",&addr);
        string str;
        int i,x,y;
        double w;
        ifstream infile(addr);
        while(getline(infile,str))
        {
            if(split(str,x,y,w))
            {
                //cout<<x<<' '<<y<<' '<<w<<endl;
                x=map_addId(x);
                y=map_addId(y);
                Mg.addedge(x,y,w);
            }
            else
                x=map_addId(x);
        }
        Mg.setn(n);
        infile.close();
    }

    void check_datawrite(Graph_Basic& Ug)
    {
        check_datawrite(Ug.segmation_out());     
    }

    void subgraph_datawrite(Graph_Divided& Dg)
    {
        printf("Input the address of directory for the output(subgraphs): ");
        scanf("%s",subaddr);
        int i,j,k,x,y;
        string str(subaddr);
        ofstream outfile;
        //cout<<Dg.n<<endl;
        for(i=1;i<=sub_n;i++)
        {
            outfile.open(str+'/'+to_string(i)+".txt");
            for(j=0;j<vp[i].size();j++)
            {
                x=vp[i][j];
                outfile<<'<'<<x<<">\n";
                for(k=Dg.head[mp[x]];k;k=Dg.e[k].next)
                {
                    y=Dg.e[k].to;
                    if(y>Dg.n)
                        outfile<<'<'<<x<<" *"<<y<<' '<<back[Dg.e[k].ty]<<' '<<Dg.e[k].w<<">\n";
                    else
                        outfile<<'<'<<x<<' '<<back[y]<<' '<<Dg.e[k].w<<">\n";
                }
            }
            outfile.close();
        }
    }

    void shortest_path(Graph_Divided& Dg)
    {
        int i,st;
        printf("Input the start node:");
        scanf("%d",&st);
        Dg.Dijkstra(mp[st]);
        printf("Distance: from %d\n",st);
        for(i=1;i<=n;i++)
        {
            if(Dg.dis[i]==inf)
                printf("-> node: %d , dis: inf\n",back[i]);
            else
                printf("-> node: %d , dis: %lf\n",back[i],Dg.dis[i]);
        }
    }
};

#endif