#include "std_lib_facilities.h"
#include "NodeRecognition.h"
#include "TreeConstruct.h"

int main()
{
    bool exercise_1=true;
    if(exercise_1)
    {
        //第一关执行代码
        string str;          
        getline(cin,str);    
        NodeRecognition nr;
        nr.read(str);
        //nr.out();
        nr.work();
    }
    else
    {
        //第二关执行代码
        string str;          
        getline(cin,str);
        TreeConstruct tr1,tr2;
        tr1.read(str);
        getline(cin,str);
        tr2.read(str);  
        tr1.coding();
        tr2.coding();
        constructcmp(tr1,tr2);
    }
	/********** End **********/
    return 0;
}

