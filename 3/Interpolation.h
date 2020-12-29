#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <string>

double Fabs(double x)
{
    return x>0?x:-x;
}

void print(double x)
{
    if(Fabs(x)<1e-7)
    {
        printf("0.0000");
        return;
    }
    string xi=to_string(x);
    int id=0,sum=4;
    while(xi[id]!='.')
        printf("%c",xi[id++]);
    printf("%c",xi[id++]);
    while(sum--)
        printf("%c",xi[id++]);
}

struct node
{
    double x,y;
    node(double xx=0,double yy=0){x=xx;y=yy;}
}ai[105];

bool cmp(node xi,node yi)
{
    return xi.x<yi.x;
}

class Interpolation
{
private:
    int n;
    double index;
    double x[105],y[105];
    double t[105][105];
public:
    Interpolation()
    {
        n=0;
        memset(x,0,sizeof(x));
        memset(y,0,sizeof(y));
        memset(t,0,sizeof(t));
    }
    void out()
    {
        printf("%d\n",n);
        printf("%lf\n",index);
        for(int i=1;i<=n;i++)
            printf("%lf %lf\n",x[i],y[i]);
    }

    int get_index(string str)
    {
        int i=0;
        int dx,fi=1;
        double dy;
        int len=str.size();
        if(str[i]=='-')
        {
            fi=-1;
            i++;
        }
        if(str[i]<='9'&&str[i]>='0')
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
                    index*=fi;
                    if(i>=len)
                        return 1;
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else if(i>=len)
            {
                index=dx*fi;
                return 1;
            }
            else
                return 0;
        }
        else
            return 0;
    }

    int get_xy()
    {
        string str;
        int i,cou=0;
        int dx,fi=1;
        double dy;
        int len;
        while(getline(cin,str))
        {
            cou++;
            len=str.size();
            i=0;fi=1;
            //first
            if(str[i]=='-')
            {
                fi=-1;
                i++;
            }
            if(str[i]<='9'&&str[i]>='0')
            {
                dx=0;
                while(str[i]!=' '&&str[i]<='9'&&str[i]>='0')
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
                        x[cou]=dx;
                        while(str[i]!=' '&&str[i]<='9'&&str[i]>='0')
                        {
                            dx=str[i]-48;
                            x[cou]+=dy*dx;
                            dy/=10;
                            i++;
                        }
                        x[cou]*=fi;
                        if(str[i]==' ')
                            goto sec;
                        else
                            return 0;
                    }
                    else
                        return 0;
                }
                else if(str[i]==' ')
                {
                    x[cou]=dx*fi;
                sec:
                    i++; fi=1;
                    if(str[i]=='-')
                    {
                        fi=-1;
                        i++;
                    }
                    if(str[i]<='9'&&str[i]>='0')
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
                                y[cou]=dx;
                                while(str[i]!=' '&&str[i]<='9'&&str[i]>='0')
                                {
                                    dx=str[i]-48;
                                    y[cou]+=dy*dx;
                                    dy/=10;
                                    i++;
                                }
                                y[cou]*=fi;
                                if(i>=len)
                                    continue;
                                else
                                    return 0;
                            }
                            else
                                return 0;
                        }
                        else if(i>=len)
                        {
                            y[cou]=dx*fi;
                            continue;
                        }
                        else
                            return 0;
                    }
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else
                return 0;
        }
        n=cou;
        return 1;
    }

    int Sort_init()
    {
        for(int i=1;i<=n;i++)
        {
            ai[i].x=x[i];
            ai[i].y=y[i];
        }
        sort(ai+1,ai+n+1,cmp);
        for(int i=2;i<n;i++)
            if(Fabs(Fabs(ai[i+1].x-ai[i].x)-
                        Fabs(ai[2].x-ai[1].x))>1e-7)
                return 0;
        return 1;
    }
    void Newton_work()
    {
        int i,j;
        double re=0,ti;
        for(i=1;i<=n;i++)
            t[0][i]=y[i];
        for(i=1;i<n;i++)
            for(j=i+1;j<=n;j++)
                t[i][j]=(t[i-1][j]-t[i-1][j-1])/(x[j]-x[j-i]);
        for(i=0;i<n;i++)
        {
            ti=t[i][i+1];
            //printf("%lf\n",ti);
            for(j=1;j<=i;j++)
                ti*=(index-x[j]);
            //printf("%lf\n",ti);
            re+=ti;
        }
        print(re);
        printf("\n");
    }
};


#endif
/*
0.4235
0.1 0.3894
0.2 0.4794
0.5 0.472
*/