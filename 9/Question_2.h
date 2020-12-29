#ifndef QUESTION2_H
#define QUESTION2_H

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>

class Question2
{
private:
    int n;
    int a[200005];
public:
    Question2()
    {
        n=0;
        memset(a,0,sizeof(a));
    }

    void solve()
    {
        int i=0,on1=0,x;
        scanf("%d",&n);
        while(scanf("%d",&x)!=EOF)
        {
            a[++i]=x;
            if(a[i]>1000||a[i]<-1000)
                on1=1;
        }
        if(on1==1||i>100000||i!=n)
        {
            printf("error\n");
            return ;
        }
        int l=0,r=0,ans=-0x3f3f3f3f,sum=0,la=0,id=0;
        n=i;
        for(i=1;i<=n;i++)
        {
            sum+=a[i];
            if(sum-la>ans)
            {
                ans=sum-la;
                l=id+1;
                r=i;
            }
            if(sum<la)
            {
                la=sum;
                id=i;
            }
        }
        printf("%d %d %d\n",ans,l,r);
    }
};

#endif

