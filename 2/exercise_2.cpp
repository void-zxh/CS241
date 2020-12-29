#include "std_lib_facilities.h"
#include "Polynomial.h"
#include "LinearEquations.h"

void Newton_work(Polynomial& p,Polynomial& q,double b)
{
    double x=b,y;
    while(1)
    {
        if(Fabs(q.f(x))<=1e-7) break;
        if(Fabs(p.f(x))<=1e-7) break;
        y=x-p.f(x)/q.f(x);
        if(Fabs(y-x)<=1e-5) break;
        x=y;
    }
    print(x);
    printf("\n");
}

int main()
{
    //请打开文件目录修改Polynomial.h，Polynomial.cpp，和exercise_2.cpp
    /********** Begin **********/
    
    bool exercise1=0;
    if(exercise1)    
    {
        //第一关执行代码
        //Please fix Polynomial.h and Polynomial.cpp
        string str;          
        Polynomial p,q,r;
        double fa,fb,a,b,x;
        getline(cin,str);    
        scanf("%lf %lf",&a,&b);
        if(a>b)
        {
            printf("error\n");
            return 0;
        }
        if(get_Polynomial(str,p))
        {
            //p.out();
            fa=p.f(a); fb=p.f(b);
            //printf("%lf %lf %lf\n",fa,fb,fa*fb);
            if(fa*fb>=0)
            {
                printf("error\n");
                return 0;
            }
            q=p.d(); r=q.d();
            for(double i=a;i<=b;i+=0.1)
            {
                x=q.f(i);
                if(Fabs(x)<=1e-7)
                {
                    printf("error\n");
                    return 0;
                }
            }
            x=r.f((a+b)/2);
            for(double i=a;i<=b;i+=0.1)
                if(r.f(i)*x<0)
                {
                    printf("error\n");
                    return 0;
                }
            Newton_work(p,q,b);
        }
        else
            printf("error\n");
    }   
    else     
    {
        //第二关执行代码
        //Please fix LinearEquations.h and LinearEquations.cpp
        LinearEquations li;
        if(get_LinearEquations(li))
        {
            //li.out();
            li.solve();
        }
        else
            printf("error\n");
        
    }
	/********** End **********/
  	return 0;
}
//x_1+2x_3=5 
//x_1+x_2=1
//x^8+x^7+2x^6+x^5+2x^4+2x^3+2x^2+2x+1
//4x^2+8x-6 -4 -1.5