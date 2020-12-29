#ifndef SIMPLELINEARREGRESSION_H
#define SIMPLELINEARREGRESSION_H

#include "Interpolation.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <string>

class SimpleLinearRegression
{
private:
    int n;
    double index;
    double r,a,b;
    double x[105],y[105];

public:
    SimpleLinearRegression()
    {
        n=0;
        memset(x,0,sizeof(x));
        memset(y,0,sizeof(y));
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
        if(n<2)
            return 0;
        return 1;
    }
    
    void work()
    {
        int i;
        double sxx=0,sxy=0,xsum=0,ysum=0;
        double xp,yp;
        for(i=1;i<=n;i++)
        {
            sxx+=x[i]*x[i];
            sxy+=x[i]*y[i];
            xsum+=x[i]; ysum+=y[i];
        }
        xp=xsum/n; yp=ysum/n;
        double rxx=0,ryy=0,rxy=0;
        for(i=1;i<=n;i++)
        {
            rxy+=(x[i]-xp)*(y[i]-yp);
            rxx+=(x[i]-xp)*(x[i]-xp);
            ryy+=(y[i]-yp)*(y[i]-yp);
        }
        r=rxy/sqrt(rxx*ryy);
        if(Fabs(r)<0.75)
        {
            print(r);
            printf("\nerror\nerror\n");
            return ;
        }
        a=(sxy*n-xsum*ysum)/(n*sxx-xsum*xsum);
        b=ysum/n-a*xsum/n;
        print(r);
        printf("\n");
        printf("y=");
        print(a);
        printf("*x");
        if(b>0)
            printf("+");
        print(b);
        printf("\n");
        print(a*index+b);
        printf("\n");
    }
};

#endif