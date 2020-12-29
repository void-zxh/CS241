
#include "std_lib_facilities.h"
#include "Polynomial.h"


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
                    else
                        return 0;
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
//2x^2-5x-1 x-3
//3x^4-2x^3+7x+9 0
//x^8+2x^7+2x^6+2x^5+2x^4+2x^3+2x^2+2x+1 x^7+x^6+x^5+x^4+x^3+x^2+x+1
//x^3-3x^2-x-1 3x^2-2x+1

int main()
{
    //请打开文件目录修改Polynomial.h，Polynomial.cpp，和exercise_2.cpp
    /********** Begin **********/
    
    bool exercise1=1;
    if(exercise1)    
    {
    //第一关执行代码
        string str;
        Polynomial xi;
        double x;
        getline(cin,str); 
        scanf("%lf",&x);
        if(get_Polynomial(str,xi))
        {
            xi.out();
            xi.d();
            print(xi.f(x));
            printf("\n");
        }
        else
            printf("error\nerror\nerror\n");
    }   
    else     
    {
    //第二关执行代码
        string str1,str2;
        Polynomial xi,yi;
        getline(cin,str1);
        get_Polynomial(str1,xi);
        getline(cin,str2);
        get_Polynomial(str2,yi);
        divide(xi,yi);
    }
	/********** End **********/
  	return 0;
}

//x^8+x^7+2x^6+x^5+2x^4+2x^3+2x^2+2x+1