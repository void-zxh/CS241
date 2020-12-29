//#ifndef QUESTION3_H
//#define QUESTION3_H

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string>
using namespace std;

int dp[1005][1005];

class Question3
{
private:
    int n;
    int vis[2005];
public:
    Question3()
    {
        n=0;
        memset(dp,0,sizeof(dp));
        memset(vis,0,sizeof(vis));
    }

    void solve(const string& str)
    {
        n=str.size();
        //cout<<n<<endl;
        int i,j,l,r,ans=0;
        for(l=2;l<=n;l++)
            for(i=1;i<=n;i++)
            {
                j=i+l-1;
                if(str[i-1]==str[j-1])
                    dp[i][j]=dp[i+1][j-1]+2;
                else
                    dp[i][j]=max(dp[i+1][j],dp[i][j-1]);
            }
        for(i=1;i<=n;i++)
            for(j=i+1;j<=n;j++)
                if(dp[i][j]>=ans)
                {
                    ans=dp[i][j];
                    l=i;
                    r=j;
                }
        //printf("%d\n",ans);
        while(ans>0)
        {
            //cout<<l<<' '<<r<<endl;
            if(dp[l][r]==dp[l+1][r])
                l++; 
            else if(str[l-1]==str[r-1])
            {
                vis[l]=1;vis[r]=1;
                l++;r--;ans-=2;
            }
            else if(dp[l][r]==dp[l][r-1])
                r--;
        }
        for(i=1;i<=n;i++)
            if(vis[i])
                printf("%c",str[i-1]);
        printf("\n");
    }
};

//#endif
//void PrintLPS(unsigned char **pDir, const char *s, int i, int j, ostream &os)
