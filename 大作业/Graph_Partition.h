#ifndef GRAPH_PARTITION_H
#define GRAPH_PARTITION_H

#include "Tool.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
#define debug printf("in c.cpp line %d\n",__LINE__);
using namespace std;

class Graph_Partition
{
private:
    SEG_ALGORITHM seg_state;
    edge e[max_edge_size];
    int head[max_node_size];
    int mp[max_node_size];
    int back[max_node_size];
    int n,cnt,cut_size;
    int out_fa[max_node_size];
    double ans;
    
    // BruteForce_Algorithm variate
    int bf_vis[max_node_size];
    int bf_cou;

    // LouvainSA_Algorithm variate
    double LSA_summ;
    double LSA_wei[max_node_size],LSA_vi[max_node_size];
    int LSA_fa[max_node_size],LSA_sz[max_node_size],LSA_vis[max_node_size]; 

    // Greedy_Algorithm variate
    int Gd_epoch,Gd_nodecou,Gd_range;
    int fa[max_node_size],Gd_sz[max_node_size];
    double Gd_vi[max_node_size][max_node_size];
    priority_queue<val> Gdq;

    // GreedyMKL_Algorithm variate
    int Gd_item;
    double Gd_wi[max_node_size][max_node_size];
    double Gd_hi[max_node_size][max_node_size];
    priority_queue<val> Gdvq,Gdvq2;
    int MKL_fa[max_node_size];
    double Gd_dis;

    void addedge(int x,int y,double w)
    {
        e[++cnt].to=y;e[cnt].next=head[x];head[x]=cnt;e[cnt].w=w;
    }

    int map_addId(int x)
    {
        if(mp[x])
            return mp[x];
        mp[x]=++n;
        back[n]=x;
        return n;
    }
    
    // BruteForce_Algorithm
    /* 
    *  use
    *  int n,cnt=1,cut_size;
    *  int head[3005],vis[3005],out_fa[3005];
    *  int cou;
    *  double ans=0x3f3f3f3f;
    */
    void BruteForce_dfs(int x,int dep,int sz)
    {
        int i;
        if(dep==n)
        {
            double sum=0;
            for(i=1;i<=n;i++)
                for(int j=head[i];j;j=e[j].next)
                    if(bf_vis[i]!=bf_vis[e[j].to])
                        sum+=e[j].w;
            sum/=2;
            if(sum<ans)
            {
                ans=sum;
                for(i=1;i<=n;i++)
                    out_fa[i]=bf_vis[i];
            }
            return ;
        }
        if(sz<cut_size)
        {
            sz++; 
            bf_vis[x]=bf_cou;
            if(dep==n-1)
                BruteForce_dfs(i,dep+1,sz);
            else
            {
                for(i=1;i<=n;i++)
                {
                    if(bf_vis[i]) continue;
                    BruteForce_dfs(i,dep+1,sz); 
                }
            }
            sz=1;
            bf_vis[x]=++bf_cou;
            if(dep==n-1)
                BruteForce_dfs(i,dep+1,sz);
            else
            {
                for(i=1;i<=n;i++)
                {
                    if(bf_vis[i]) continue;
                    BruteForce_dfs(i,dep+1,sz);
                } 
            }
            bf_cou--;
            bf_vis[x]=0;
        }
        else
        {
            sz=1;
            bf_vis[x]=++bf_cou;
            if(dep==n-1)
                BruteForce_dfs(i,dep+1,sz);
            else
            {
                for(i=1;i<=n;i++)
                {
                    if(bf_vis[i]) continue;
                    BruteForce_dfs(i,dep+1,sz); 
                }
            }
            bf_vis[x]=0;
            bf_cou--;
        }
    }

    void BruteForce_Partition()
    {
        if(n<=cut_size) 
        {
            ans=0;
            for(int i=1;i<=n;i++)
                out_fa[i]=1;
            return ;
        }
        ans=inf;bf_cou=0;
        memset(bf_vis,0,sizeof(bf_vis));
        memset(out_fa,0,sizeof(out_fa));
        bf_cou++;
        BruteForce_dfs(1,0,0);
        printf("BruteForce_Partition: %lf\n",ans);
    }

    // LouvainSA_Algorithm
    /* 
     *  use 
     *  int n,m,cnt=1,summ,mi;
     *  int head[3005],fa[3005],sz[3005];
     *  double wei[3005],vi[3005];
     *  int vis[3005]; 
    */

    void LSA_build()
    {
        memset(LSA_vis,0,sizeof(LSA_vis));
        for(int i=1;i<=n;i++)
        {
            LSA_fa[i]=i; LSA_sz[i]=1;
            LSA_vi[i]=0; LSA_wei[i]=0;
        }
        LSA_summ=0;
        for(int i=1;i<=n;i++)
            for(int j=head[i];j;j=e[j].next)
            {
                LSA_summ+=e[j].w;
                LSA_wei[i]+=e[j].w;
            }
        LSA_summ/=2;
    }

    void Louvain_join(int x,int y)
    {
        LSA_vis[y]=1;
        int fx=LSA_fa[x],fy=LSA_fa[y];
        LSA_sz[fy]--;
        LSA_sz[fx]++;
        for(int i=head[y];i;i=e[i].next)
            if(LSA_fa[e[i].to]==LSA_fa[x])
                LSA_vi[LSA_fa[x]]+=2*e[i].w;
            else if(LSA_fa[e[i].to]==fy)
                LSA_vi[fy]-=2*e[i].w;
        LSA_fa[y]=LSA_fa[x]; 
    }

    void SA_join(int x,int y)
    {
        int fx=LSA_fa[x],fy=LSA_fa[y];
        LSA_sz[fy]--;
        LSA_sz[fx]++;
        for(int i=head[y];i;i=e[i].next)
            if(LSA_fa[e[i].to]==LSA_fa[x])
                LSA_vi[LSA_fa[x]]+=2*e[i].w;
            else if(LSA_fa[e[i].to]==fy)
                LSA_vi[fy]-=2*e[i].w;
        LSA_fa[y]=LSA_fa[x]; 
    }

    void Louvain_work()
    {
        double kiin,deltaq,ansq;
        int i,j,k,y;
        int sx,sy,fx,fy;
        while(1)
        {
            ansq=-inf; sx=0; sy=0;
            for(i=1;i<=n;i++)
                for(j=head[i];j;j=e[j].next)
                {
                    y=e[j].to;
                    if(LSA_vis[i]==0&&LSA_fa[i]!=LSA_fa[y]&&LSA_sz[LSA_fa[y]]+1<=cut_size)
                    {
                        kiin=0;
                        for(k=head[i];k;k=e[k].next)
                            if(LSA_fa[e[k].to]==LSA_fa[y])
                                kiin+=2*e[k].w;
                        deltaq=1.0000/(2*LSA_summ)*(kiin-LSA_vi[fa[i]]*LSA_wei[i]*1.0000/LSA_summ);
                        if(ansq<deltaq)
                        {
                            ansq=deltaq;
                            sx=y; sy=i;
                        }
                    }
                }
            if(!(ansq>0))
                break;
            Louvain_join(sx,sy);
            //cout<<ansq<<endl;
        }
    }

    double LSA_calc_out()
    {
        double sum=0;
        for(int i=1;i<=n;i++)
            for(int j=head[i];j;j=e[j].next)
                if(LSA_fa[i]!=LSA_fa[e[j].to])
                    sum+=e[j].w;
        sum/=2;
        return sum;
    }

    void SA_work()
    {
        double T=10000;
        double p=0.995,li=10,laq;
        double deltaq,ansq,cio,kiin;
        int i,j,k,y;
        int sx,sy,fx,fy;
        double sans;
        for(i=1;i<=n;i++)
            out_fa[i]=LSA_fa[i];
        while(1)
        {
            ansq=-inf; sx=0; sy=0;
            for(i=1;i<=n;i++)
                for(j=head[i];j;j=e[j].next)
                {
                    y=e[j].to; 
                    if(LSA_fa[i]!=LSA_fa[y]&&LSA_sz[LSA_fa[y]]+1<=cut_size)
                    {
                        kiin=0; cio=0;
                        for(k=head[i];k;k=e[k].next)
                            if(LSA_fa[e[k].to]==LSA_fa[y])
                                kiin+=2*e[k].w;
                            else if(LSA_fa[e[k].to]==LSA_fa[i])
                                cio+=2*e[k].w;
                        deltaq=kiin-cio;
                        if(deltaq!=-laq&&ansq<deltaq)
                        {
                            ansq=deltaq;
                            sx=y; sy=i;
                        }
                    }
                }
            if(!(ansq>0))
            {
                if(T*p>=li)
                    T*=p;
                else
                    break;
            }
            SA_join(sx,sy);
            laq=ansq;
            sans=LSA_calc_out();
            if(sans<ans)
            {
                ans=sans;
                for(i=1;i<=n;i++)
                    out_fa[i]=LSA_fa[i];
            }
            //cout<<ansq<<endl;
        }
    }

    void LouvainSA_Partition()
    {
        if(n<=cut_size) 
        {
            ans=0;
            for(int i=1;i<=n;i++)
                out_fa[i]=1;
            return ;
        }
        LSA_build();
        Louvain_work();
        ans=LSA_calc_out();
        SA_work();
    }

    // Greedy_Algorithm
    /* 
     *  use
     *  int n,m,cnt=1,mi,range=5;
     *  int head[3005];
     *  double vi[3005][3005],ans=0x3f3f3f3f;
     *  int sub_root[3005],fa[3005],sz[3005]; 
     *  int nodecou,epoch; 
     *  priority_queue<val> q;
    */
    void Greedy_clear(priority_queue<val>& q) 
    {
    	priority_queue<val> empty;
    	swap(empty, q);
    }

    void Greedy_rebuild()
    {
        Gd_nodecou=0; 
        Greedy_clear(Gdq);
        //memset(sub_root,0,sizeof(sub_root));
        memset(fa,0,sizeof(fa));
        memset(Gd_sz,0,sizeof(Gd_sz));
        memset(Gd_vi,0,sizeof(Gd_vi));
    }

    void Greedy_rand_sub()
    {
        int  i,x,basecou=n/cut_size;
        if(n%cut_size!=0) basecou++;
        Gd_nodecou=min(basecou+(rand()%Gd_range),n);
        for(i=1;i<=Gd_nodecou;i++)
        {
            do
            {
                x=rand()%n+1;
            }while(fa[x]!=0);
            //sub_root[i]=x;
            fa[x]=i;Gd_sz[i]=1; 
        }
    }

    void Greedy_work()
    {
        int i,j,x,y;
        //for(i=1;i<=n;i++)
        //    cout<<fa[i]<<' ';
        //cout<<endl;
        for(i=1;i<=n;i++)
            for(j=head[i];j;j=e[j].next)
            {
                y=e[j].to;
                //cout<<i<<' '<<y<<' '<<e[j].w<<endl;
                if(fa[i]==0&&fa[y]!=0)
                    Gd_vi[i][fa[y]]+=e[j].w;
            }
        for(i=1;i<=n;i++)
            if(fa[i]==0)
                for(j=1;j<=Gd_nodecou;j++)	
                    Gdq.push(val(i,j,Gd_vi[i][j])); 
        int to,ci,delta=n-Gd_nodecou;
        val xi;
        while(delta--)
        {
            x=0;y=0;
            if(Gdq.empty()) break;
            while(1)
            {
                xi=Gdq.top();Gdq.pop(); 
                x=xi.x; y=xi.y;
                if(fa[x]) continue;
                if(Gd_sz[y]==cut_size) continue; 
                if(Gd_vi[x][y]!=xi.w) continue;
                break;
            }
            fa[x]=y;Gd_sz[y]++;
            for(i=head[x];i;i=e[i].next)
            {
                to=e[i].to;
                Gd_vi[to][y]+=e[i].w;
                Gdq.push(val(to,y,Gd_vi[to][y]));
            }
        }
    }

    void Greedy_calc_out(int step)
    {
        double sum=0;
        /*for(int i=1;i<=m;i++)
            if(fa[fe[i].x]!=fa[fe[i].y])
                sum+=fe[i].w;*/
        for(int i=1;i<=n;i++)
            for(int j=head[i];j;j=e[j].next)
                if(fa[i]!=fa[e[j].to])
                    sum+=e[j].w;
        sum/=2;
        if(sum<ans)
        {
            ans=sum;
            for(int i=1;i<=n;i++)
                out_fa[i]=fa[i];
        }
        printf("Work%d: %lf ",step,sum);
        printf("Current loss: %lf\n",ans);
    }

    void Greedy_Partition()
    {
        if(n<=cut_size) 
        {
            ans=0;
            for(int i=1;i<=n;i++)
                out_fa[i]=1;
            return ;
        }
        int ti;
        ans=inf;
        Gd_epoch=500;Gd_range=max(5,n/10);
        for(ti=1;ti<=Gd_epoch;ti++)
        {
            Greedy_rebuild(); 
            Greedy_rand_sub();
            Greedy_work();
            Greedy_calc_out(ti);
        }
        //printf("Best: %lf\n",ans);
    }

    // GreedyMKL_Algorithm
    /* 
     *  use
     *  int n,m,cnt=1,mi,range=5;;
     *  double ans=0x3f3f3f3f,dis;
     *  int head[3005];
     *  double vi[3005][3005],wi[3005][3005],hi[3005][3005];
     *  int sub_root[3005],fa[3005],sz[3005]; 
     *  int nodecou,epoch,item; 
     *  priority_queue<val> q,vq,vq2;
    */
    void GreedyMKL_rebuild()
    {
        Gd_nodecou=0;
        Greedy_clear(Gdq);
        Greedy_clear(Gdvq);
	    //memset(sub_root,0,sizeof(sub_root));
	    memset(fa,0,sizeof(fa));
	    memset(Gd_sz,0,sizeof(Gd_sz));
	    memset(Gd_vi,0,sizeof(Gd_vi));
	    memset(Gd_wi,0,sizeof(Gd_wi));
    }

    void Fs_calc_out()
    {
        Gd_dis=0;
        /*for(int i=1;i<=m;i++)
            if(fa[fe[i].x]!=fa[fe[i].y])
                sum+=fe[i].w;*/
        for(int i=1;i<=n;i++)
            for(int j=head[i];j;j=e[j].next)
                if(fa[i]!=fa[e[j].to])
                    Gd_dis+=e[j].w;
        Gd_dis/=2;
        for(int i=1;i<=n;i++)
            MKL_fa[i]=fa[i];
    }

    void Muti_KL_work(int step)
    {
        int i,j,x,tx,y,ty,ti,to;
        int on1=0,tcou=0;
        double nowans=Gd_dis,vx;
        val xi;
        for(i=1;i<=n;i++)
            for(j=head[i];j;j=e[j].next)
                Gd_wi[i][fa[e[j].to]]+=e[j].w;
        for(i=1;i<=n;i++)
            for(j=1;j<=Gd_nodecou;j++)
                if(fa[i]!=j)
                {
                    Gd_hi[i][j]=Gd_wi[i][j]-Gd_wi[i][fa[i]];
                    Gdvq.push(val(i,j,Gd_hi[i][j]));
                }
        //if(step==545)
        //	cout<<nowans<<endl;
        for(ti=1;ti<=Gd_item;ti++)
        //int itc=0;
        //while(1)
        {
            //itc++;
            if(Gdvq.empty()) break;
            while(1)
            {
                xi=Gdvq.top();Gdvq.pop();
                x=xi.x; y=xi.y;
                if(fa[x]==y) continue;
                if(Gd_hi[x][y]!=xi.w) continue;
                break;	
            }
            Greedy_clear(Gdvq2); 
            for(i=1;i<=n;i++)
                if(fa[i]==y)
                    Gdvq2.push(val(i,fa[x],Gd_hi[i][fa[x]]));
            xi=Gdvq2.top();Gdvq2.pop();
            tx=xi.x; ty=fa[x];
            //if(step==545)
            //	cout<<hi[x][y]<<" "<<hi[tx][ty]<<endl;
            nowans=nowans-(Gd_hi[x][y]+Gd_hi[tx][ty]);
            //if(step==545)
            //	cout<<nowans<<endl; 
            on1=0;
            for(i=head[x];i;i=e[i].next)
            {
                to=e[i].to;
                if(to==tx)
                    nowans+=2*e[i].w; 
            }
            /*if(step==545)
            {
            cout<<x<<' '<<y<<' '<<endl;
            cout<<tx<<' '<<ty<<' '<<endl; 
            cout<<nowans<<endl;
            }*/
            if(nowans<Gd_dis)
            {
                Gd_dis=nowans;
                on1=1;
            //	tcou=0;
            }
            /*else
            {
                tcou++;
                if(tcou>=20)
                    break;
            } */
            for(i=head[x];i;i=e[i].next)
            {
                to=e[i].to;
                //cout<<to<<" "<<e[i].w<<endl; 
                if(to!=tx)
                {
                    Gd_hi[to][ty]-=e[i].w;
                    Gd_hi[to][y]+=e[i].w;
                    if(fa[to]==y)
                    {
                        for(j=1;j<=Gd_nodecou;j++)
                        {
                            Gd_hi[to][j]-=e[i].w;
                            if(fa[to]!=j)	
                                Gdvq.push(val(to,j,Gd_hi[to][j]));
                        }
                    }
                    else if(fa[to]==ty)
                    {
                        for(j=1;j<=Gd_nodecou;j++)
                        {
                            Gd_hi[to][j]+=e[i].w;	
                            if(fa[to]!=j)
                                Gdvq.push(val(to,j,Gd_hi[to][j]));
                        }
                    } 
                    else
                    {
                        Gdvq.push(val(to,ty,Gd_hi[to][ty]));
                        Gdvq.push(val(to,y,Gd_hi[to][y]));
                    }
                }
            }
            for(i=head[tx];i;i=e[i].next)
            {
                to=e[i].to;
                if(to!=x)
                {
                    Gd_hi[to][y]-=e[i].w;
                    Gd_hi[to][ty]+=e[i].w;
                    if(fa[to]==ty)
                    {
                        for(j=1;j<=Gd_nodecou;j++)
                        {
                            Gd_hi[to][j]-=e[i].w;	
                            if(fa[to]!=j)
                                Gdvq.push(val(to,j,Gd_hi[to][j]));
                        }
                    }
                    else if(fa[to]==y)
                    {
                        for(j=1;j<=Gd_nodecou;j++)
                        {
                            Gd_hi[to][j]+=e[i].w;	
                            if(fa[to]!=j)
                                Gdvq.push(val(to,j,Gd_hi[to][j]));
                        }
                    } 
                    else
                    {
                        Gdvq.push(val(to,y,Gd_hi[to][y]));
                        Gdvq.push(val(to,ty,Gd_hi[to][ty]));
                    }
                }
            } 
            fa[x]=y; fa[tx]=ty;
            if(on1)
            {
                for(i=1;i<=n;i++)
                    MKL_fa[i]=fa[i];
            }
            /*vx=0;
            for(int i=1;i<=n;i++)
                for(int j=head[i];j;j=e[j].next)
                    if(fa[i]!=fa[e[j].to])
                        vx+=e[j].w;
            //printf("%lf %lf\n",vx/2,nowans);
            if(fabs(vx/2-nowans)>1e-6)
            {printf("%lf %lf\n",vx/2,nowans);getchar(); getchar();}*/
            for(i=1;i<=Gd_nodecou;i++)
            {
                Gd_hi[tx][i]=0;
                Gd_hi[x][i]=0;
            }
            for(i=head[x];i;i=e[i].next)
                Gd_hi[x][fa[e[i].to]]+=e[i].w;
            for(i=head[tx];i;i=e[i].next)
                Gd_hi[tx][fa[e[i].to]]+=e[i].w;
            for(i=1;i<=Gd_nodecou;i++)
            {
                if(i!=fa[x]) 
                {
                    Gd_hi[x][i]-=Gd_hi[x][fa[x]];
                    Gdvq.push(val(x,i,Gd_hi[x][i])); 
                }
                if(i!=fa[tx])
                {
                    Gd_hi[tx][i]-=Gd_hi[tx][fa[tx]];
                    Gdvq.push(val(tx,i,Gd_hi[tx][i]));	
                }
            }
        } 
        //printf("Work%d: %lf ",step,Gd_dis);
        //printf("Work%d(%d): %lf ",step,itc,dis);
        //ans=min(ans,Gd_dis);
        if(Gd_dis<ans)
        {
            ans=Gd_dis;
            for(i=1;i<=n;i++)
                out_fa[i]=MKL_fa[i];
        }
        //printf("Current loss: %lf\n",ans);
    //	if(itc>=item)
    //		system("pause"); 
    }

    void GreedyMKL_Partition()
    {
        if(n<=cut_size) 
        {
            ans=0;
            for(int i=1;i<=n;i++)
                out_fa[i]=1;
            return ;
        }
        int ti;
        ans=inf;
        Gd_epoch=2000;Gd_item=20;Gd_range=max(5,n/20);
        for(ti=1;ti<=Gd_epoch;ti++)
        {
            GreedyMKL_rebuild(); 
            Greedy_rand_sub();
            Greedy_work();
            Fs_calc_out();
            Muti_KL_work(ti);
        }
    }

public:
    Graph_Partition(){}

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

    void setState(SEG_ALGORITHM segs)
    {
        seg_state=segs;seg_state=segs;
    }

    void pre_build()
    {
        int seg_mode;
        printf("Input the maximum of the subgraph:");
        scanf("%d",&cut_size);
        printf("Choose the algorithm mode(1: BruteForce_MODE,2: Louvain_MODE,3: Greedy_MODE,4: GreedyMKL_MODE):");
        scanf("%d",&seg_mode);
        setState(SEG_ALGORITHM(seg_mode));
    }

    void build(const vector<int>& vnode,const edge ei[],const int last[])
    {
        n=0;cnt=1;
        memset(mp,0,sizeof(mp));
        memset(head,0,sizeof(head));
        memset(back,0,sizeof(back));
        memset(out_fa,0,sizeof(out_fa));
        int i,j,x,y;
        for(i=0;i<vnode.size();i++)
            map_addId(vnode[i]);
        cout<<"Blocksize: "<<n<<'\n';
        for(i=0;i<vnode.size();i++)
            for(j=last[vnode[i]];j;j=ei[j].next)
            {
                x=mp[vnode[i]];
                y=mp[ei[j].to];
                addedge(x,y,ei[j].w);
            }
    }

    double segmation(int fi[],int work_step)
    {
        switch(seg_state)
        {
            case BruteForce_MODE:BruteForce_Partition();break;
            case LouvainSA_MODE:LouvainSA_Partition();break;
            case Greedy_MODE:Greedy_Partition();break;
            case GreedyMKL_MODE:GreedyMKL_Partition();break;
        }
        for(int i=1;i<=n;i++)
            fi[back[i]]=work_step+out_fa[i];
        return ans;
    }
};


#endif