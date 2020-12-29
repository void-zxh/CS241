#ifndef QUESTION1_H
#define QUESTION1_H

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>


bool cmp(int x,int y)
{
    return x<y;
}

class Question1
{
private:
    int m,n;
    int a[505];
public:
    Question1()
    {
        m=0;n=0;
        memset(a,0,sizeof(a));
    }

    void solve()
    {
        int i,j;
        int on1=0;
        scanf("%d%d",&m,&n);
        for(i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]<=0)
                on1=2;
            if(a[i]>m&&on1==0)
                on1=1;
        }
        if(on1==2)
        {
            printf("error\n");
            return ;
        }
        else if(on1==1)
        {
            printf("out\n");
            return ;
        }
        sort(a+1,a+n+1,cmp);
        i=1,j=n;
        int cou=0;
        while(i<=j)
        {
            if(i!=j&&a[i]+a[j]<=m)
            {
                cou++;
                i++,j--;
            }
            else if(a[j]<=m)
            {
                j--;
                cou++;
            }
        }
        printf("%d\n",cou);
    }
};

#endif

