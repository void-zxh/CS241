#ifndef HUFFMAN_EXERCISE_1_H
#define HUFFMAN_EXERCISE_1_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <string>
#include <map>
#include <queue>

bool cmp(int x,int y)
{
    return x<y;
}

class Huffman
{
private:
    int n;
    int mp[305];
    int cou[305];
public:
    Huffman()
    {
        n=0;
        memset(mp,0,sizeof(mp));
        memset(cou,0,sizeof(cou));
    }

    void init(const string& str)
    {
        int to,len=str.size();
        for(int i=0;i<len;i++)
            if(mp[str[i]])
            {
                to=mp[str[i]];
                cou[to]++;
            }
            else
            {
                mp[str[i]]=++n;
                to=n;
                cou[to]=1;
            }
    }

    void work()
    {
        if(n==1)
        {
            printf("%d\n",cou[1]);
            return ;
        }
        sort(cou+1,cou+n+1,cmp);
        priority_queue<int, vector<int>,greater<int> > q;
        for(int i=1;i<=n;i++)
            q.push(cou[i]);
        int xi1,xi2;
        long long ans=0;
        for(int i=1;i<n;i++)
        {
            xi1=q.top();
            q.pop();
            xi2=q.top();
            q.pop();
            ans+=xi1+xi2;
            q.push(xi1+xi2);
            //printf("%d %d\n",xi1,xi2);
        }
        printf("%lld\n",ans);
    }
};

#endif