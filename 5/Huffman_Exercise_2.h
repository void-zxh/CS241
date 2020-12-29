#ifndef HUFFMAN_EXERCISE_2_H
#define HUFFMAN_EXERCISE_2_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <string>
#include <map>
#include <queue>


class Huffmanword
{
private:
    int n,ans;
    map<string,int> mp;
    int cou[305];
public:
    Huffmanword()
    {
        n=0;ans=0;
        mp.clear();
        memset(cou,0,sizeof(cou));
    }

    void init(const string& str)
    {
        int to,len=str.size();
        string si="";
        for(int i=0;i<len;i++)
            if((str[i]<='z'&&str[i]>='a')||(str[i]<='Z'&&str[i]>='A'))
                si=si+str[i];
            else
            {
                ans+=8;
                if(si=="") continue;
                if(mp.find(si)==mp.end())
                {
                    mp[si]=++n;
                    cou[n]=1;
                }
                else
                {
                    to=mp[si];
                    cou[to]++;
                }
                si="";
            }
        if(si!="")
        {
            if(mp.find(si)==mp.end())
            {
                mp[si]=++n;
                cou[n]=1;
            }
            else
            {
                to=mp[si];
                cou[to]++;
            }
        }
    }

    void work()
    {
        if(n==1)
        {
            printf("%d\n",cou[1]+ans);
            return ;
        }
        //printf("%d %d\n",ans,n);
        sort(cou+1,cou+n+1,cmp);
        priority_queue<int, vector<int>,greater<int> > q;
        for(int i=1;i<=n;i++)
            q.push(cou[i]);
        int xi1,xi2;
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
        printf("%d\n",ans);
    }
};

#endif