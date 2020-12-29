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
    void d()
    {
        int i;
        Polynomial y;
        if(len==0)
        {
            printf("0.0000\n");
            return ;
        }
        y.len=len-1;
        for(i=0;i<len;i++)
            y.a[i]=(i+1)*a[i+1];
        y.out();
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
#endif
//1+6x-5x^2+3x+2x^2+3 3.1