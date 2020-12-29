#ifndef LINEAREQUARIONS_H
#define LINEAREQUATIONS_H 

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <string>

struct node
{
    int id;
    double ou;
    node(int i=0,double o=0){id=i;ou=o;}
};

bool cmp(node x,node y)
{
    return x.id<y.id;
}

class LinearEquations
{
    friend int get_LinearEquations(LinearEquations& li);
private:
    int n,m,io;
    double a[105][105],b[105];
    int to[105],bac[105],ans[105],vis[105];
    node outi[105];
public:
    LinearEquations()
    {
        n=0;m=0;io=0;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(to,0,sizeof(to));
        memset(bac,0,sizeof(bac));
        memset(ans,0,sizeof(ans));
        memset(vis,0,sizeof(vis));
        memset(outi,0,sizeof(outi));
    }
    void out()
    {
        int i,j;
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
                printf("%lf ",a[i][j]);
            printf(" -> %lf\n",b[i]);
        }
    }
    void solve()
    {
        int i,j,k,l;
        if(m>n)
        {
            printf("error\n");
            return ;
        }
        for(i=1;i<=m;i++)
        {
            k=0;
            for(j=1;j<=n;j++)
                if(vis[j]==0&&Fabs(a[j][i])>=1e-7)
                {
                    k=j;
                    break;
                }
            if(k==0)
            {
                printf("error\n");
                return ;
            }
            for(j=i+1;j<=m;j++)
                a[k][j]/=a[k][i];
            b[k]/=a[k][i];
            a[k][i]=1;
            for(j=1;j<=n;j++)
                if(j!=k)
                {
                    for(l=i+1;l<=m;l++)
                        a[j][l]-=a[k][l]*a[j][i];
                    b[j]-=b[k]*a[j][i];
                    a[j][i]=0;
                }
            ans[i]=k;
            vis[k]=i;
        }
        for(i=1;i<=n;i++)
            if(vis[i]==0&&Fabs(b[i])>=1e-7)
            {
                printf("error\n");
                return;
            }
        for(i=1;i<=m;i++)
            outi[++io]=node(bac[i],b[ans[i]]);
        sort(outi+1,outi+io+1,cmp);
        for(i=1;i<=io;i++)
        {
            print(outi[i].ou);
            printf(" ");
        }
        printf("\n");
    }
};

int get_LinearEquations(LinearEquations& li)
{
    string str;
    int len,i,lo=0,cou=0;
    int dx,fi=1,id=0;
    double index,dy;
    while(getline(cin,str))
    {
        cou++;
        lo=0;fi=1;
        len=str.size();
        for(i=0;i<len;i++)
            if(str[i]=='=')
            {
                lo=i;
                break;
            }
        //printf("%d\n",lo);
        if(lo==0||lo==len-1)
            return 0;
        for(i=0;i<lo;i++)
        {
            if(str[i]=='x')
            {
                if(i==0||str[i-1]>'9'||str[i-1]<'0')
                    index=1;
                i++;
                if(str[i]=='_')
                {
                    i++;
                    if(str[i]<='9'&&str[i]>='0')
                    {
                        id=0;
                        while(i<lo&&str[i]>='0'&&str[i]<='9')
                        {
                            id=id*10+str[i]-48;
                            i++;
                        }
                        if(li.to[id]==0)
                        {
                            li.to[id]=++li.m;
                            li.bac[li.m]=id;
                        }
                        li.a[cou][li.to[id]]+=index*fi;
                        if(i>=lo)
                            break;
                        if(str[i]=='+'||str[i]=='-')
                            i--;
                        else
                            return 0;
                    }
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else if(str[i]=='+')
            {
                fi=1;
                if(str[i+1]>'9'||str[i+1]<'0')
                {
                    if(str[i+1]!='x')
                        return 0;
                }
            }
            else if(str[i]=='-')
            {
                fi=-1;
                if(str[i+1]>'9'||str[i+1]<'0')
                {
                    if(str[i+1]!='x')
                        return 0;
                }
            }
            else if(str[i]<='9'&&str[i]>='0')
            {
                dx=0;
                while(i<lo&&str[i]<='9'&&str[i]>='0')
                {
                    dx=dx*10+str[i]-48;
                    i++;
                }
                if(str[i]=='.')
                {
                    i++;
                    if(str[i]<='9'&&str[i]>='0')
                    {
                        dy=0.1;
                        index=dx;
                        while(i<lo&&str[i]<='9'&&str[i]>='0')
                        {
                            dx=str[i]-48;
                            index+=dy*dx;
                            dy/=10;
                            i++;
                        }
                        if(i>=lo||str[i]=='+'||str[i]=='-')
                        {
                            li.b[cou]-=index*fi;
                            if(i>=lo)
                                break;
                        }
                        if(str[i]=='x'||str[i]=='+'||str[i]=='-')
                            i--;
                    }
                    else
                        return 0;
                }
                else if(i>=lo||str[i]=='+'||str[i]=='-')
                {
                    li.b[cou]-=dx*fi;
                    if(i>=lo)
                        break;
                    i--;
                }
                else if(str[i]=='x')
                {
                    index=dx;
                    i--;
                }
                else
                    return 0;
            }
            else
                return 0;
        }
        fi=1;id=0;
        for(i=lo+1;i<len;i++)
        {
            if(str[i]=='x')
            {
                if(i==0||str[i-1]>'9'||str[i-1]<'0')
                    index=1;
                i++;
                if(str[i]=='_')
                {
                    i++;
                    if(str[i]<='9'&&str[i]>='0')
                    {
                        id=0;
                        while(i<len&&str[i]>='0'&&str[i]<='9')
                        {
                            id=id*10+str[i]-48;
                            i++;
                        }
                        if(li.to[id]==0)
                        {
                            li.to[id]=++li.m;
                            li.bac[li.m]=id;
                        }
                        li.a[cou][li.to[id]]-=index*fi;
                        if(i>=len)
                            break;
                        if(str[i]=='+'||str[i]=='-')
                            i--;
                        else
                            return 0;
                    }
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else if(str[i]=='+')
            {
                fi=1;
                if(str[i+1]>'9'||str[i+1]<'0')
                {
                    if(str[i+1]!='x')
                        return 0;
                }
            }
            else if(str[i]=='-')
            {
                fi=-1;
                if(str[i+1]>'9'||str[i+1]<'0')
                {
                    if(str[i+1]!='x')
                        return 0;
                }
            }
            else if(str[i]<='9'&&str[i]>='0')
            {
                dx=0;
                while(i<len&&str[i]<='9'&&str[i]>='0')
                {
                    dx=dx*10+str[i]-48;
                    i++;
                }
                if(str[i]=='.')
                {
                    i++;
                    if(str[i]<='9'&&str[i]>='0')
                    {
                        dy=0.1;
                        index=dx;
                        while(i<len&&str[i]<='9'&&str[i]>='0')
                        {
                            dx=str[i]-48;
                            index+=dy*dx;
                            dy/=10;
                            i++;
                        }
                        if(i>=len||str[i]=='+'||str[i]=='-')
                        {
                            li.b[cou]+=index*fi;
                            if(i>=len)
                                break;
                        }
                        if(str[i]=='x'||str[i]=='+'||str[i]=='-')
                            i--;
                    }
                    else
                        return 0;
                }
                else if(i>=len||str[i]=='+'||str[i]=='-')
                {
                    li.b[cou]+=dx*fi;
                    if(i>=len)
                        break;
                    i--;
                }
                else if(str[i]=='x')
                {
                    index=dx;
                    i--;
                }
                else
                    return 0;
            }
            else
                return 0;
        }
    }
    li.n=cou;
    return 1;
}

#endif
//x_1-x_2=0 
//x_2-x_3=0 
//x_1+x_1+x_3=4.677
//x_1+3?9=2
//X_1+X_2+X_3+X_4=9.38 X_1-X_2+X_3-X_4=3.36 X_1+X_2+X_3-X_4=8.82 2X_3+2X_1-2X_2-2X_4=6.82