#include "std_lib_facilities.h"
#include "Interpolation.h"
#include "SimpleLinearRegression.h"

//定义main函数
int main()
{
    /********** Begin **********/
    bool exercisel = false;
   	if (exercisel)
	{
    //第一关执行代码 完成 Interpolation.cpp与 Interpolation.h文件
		Interpolation itrp;
   		string str;          //测试输入数据存放变量
    	getline(cin,str);    //读取测试输入，并存入str
		if(!itrp.get_index(str))
		{
			printf("error1\n");
			return 0;
		}
		if(!itrp.get_xy())
		{
			printf("error2\n");
			return 0;
		}
		if(!itrp.Sort_init())
		{
			printf("error3\n");
			return 0;
		}
		//itrp.out();
		itrp.Newton_work();
    } 
	else
	{
   	//第二执行代码 完成 SimpleLinearRegression.cpp与 SimpleLinearRegression.h文件
		SimpleLinearRegression slr;
		string str;          //测试输入数据存放变量
    	getline(cin,str);    //读取测试输入，并存入str
		if(!slr.get_index(str))
		{
			printf("error\nerror\nerror\n");
			return 0;
		}
		if(!slr.get_xy())
		{
			printf("error\nerror\nerror\n");
			return 0;
		}
		//slr.out();
		slr.work();
    }
    
	/********** End **********/
  	return 0;
}

/*
-2.31
7.3 -18.6
5.2 -14.4
3.1 -10.2
1 -6
-1.1 -1.8
-3.2 2.4
*/