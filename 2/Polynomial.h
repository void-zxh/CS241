#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H 

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

class Polynomial
{
public:
    int len;
    double a[10005];
    Polynomial(){memset(a,0,sizeof(a));len=0;};
public:
    void out()
    {
        int i,on1=0;
        //printf("%lf\n",Fabs(a[len]));
        while(len>0&&Fabs(a[len])<1e-7)
            len--;
        //printf("%d\n",len);
        for(i=len;i>=1;i--)
            if(Fabs(a[i])>=1e-7)
            {
                if(a[i]>0&&on1==1)
                    printf("+");
                print(a[i]);
                printf("x");
                if(i>1)
                    printf("^%d",i);
                on1=1;
                //system("pause");
            }
        if(Fabs(a[0])>=1e-7)
        {
            if(a[0]>0&&on1==1)
                printf("+");
            print(a[0]);
            printf("\n");
        }
        else if(len==0)
            printf("0.0000\n");
        else
            printf("\n");
    }
    Polynomial d()
    {
        int i;
        Polynomial y;
        if(len==0)
        {
            y.len=0;
            y.a[0]=0;
            return y;
        }
        y.len=len-1;
        for(i=0;i<len;i++)
            y.a[i]=(i+1)*a[i+1];
        return y;
        //y.out();
    }
    double f(double x)
    {
        int i,j;
        double re=0,t;
        for(i=0;i<=len;i++)
        {
            t=a[i];
            for(j=1;j<=i;j++)
                t*=x;
            re+=t;
        }
        return re;
    }
};


int get_Polynomial(string str,Polynomial& xi)
{
    int i,fi=1,len=str.size();
    int dx,id;
    double index,dy;
    for(i=0;i<len;i++)
    {
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
                    if(i>=len||str[i]=='+'||str[i]=='-')
                    {
                    	xi.a[0]+=index*fi;
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
                xi.a[0]+=dx*fi;
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
        else if(str[i]=='x')
        {
            if(i==0||str[i-1]>'9'||str[i-1]<'0')
                index=1;
            i++;
            if(str[i]=='^')
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
                    xi.a[id]+=index*fi;
                    xi.len=max(xi.len,id);
                    if(i>=len)
                    	break;
                    if(str[i]=='+'||str[i]=='-')
                        i--;
                }
                else
                    return 0;
            }
            else if(str[i]=='+'||str[i]=='-')
            {
                id=1;
                xi.a[id]+=index*fi;
                xi.len=max(xi.len,1);
                i--;
            }
            else if(i>=len)
            {
                id=1;
                xi.a[id]+=index*fi;
                xi.len=max(xi.len,1);
                break;
            }
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
        else
            return 0;
    }
    return 1;
}

void divide(Polynomial& xi,Polynomial& yi)
{
    int i,j;
    Polynomial q,r=xi;
    double x;
    if(yi.len==0&&Fabs(yi.a[0])<1e-6)
    {
        printf("error\nerror\n");
        return ;
    }
    if(xi.len<yi.len)
    {
        q.out();
        r.out();
        return ;
    }
    q.len=r.len-yi.len;
    for(i=q.len;i>=0;i--)
    {
        q.a[i]=r.a[i+yi.len]/yi.a[yi.len];
        x=q.a[i];
        for(j=yi.len;j>=0;j--)
            r.a[i+j]-=x*yi.a[j];
    }
    q.out();
    r.out();
}
#endif
//x^4+x^3+3x^2+2x-78.4375 2.1 2.7
//1+6x-5x^2+3x+2x^2+3 3.1