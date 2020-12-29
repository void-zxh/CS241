#include "std_lib_facilities.h"
#include "Token_Exercise_1.h"
#include "Code_Exercise_2.h"

int main()
{
    /********** Begin **********/
    
    bool exercise_1=false;
    if(exercise_1)
    {
    //第一关执行代码
		//Please fix Token_Exercise_1.h and Token_Exercise_1.cpp
        string str;   
        token_exercise te;
        getline(cin,str);    
        te.get_count(str);
        te.get_words();
        //cout<<str<<endl;
        }
    else
    {
    //第二关执行代码
    //Please fix Code_Exercise_2.h and Code_Exercise_2.cpp
        string str;
        code_exercise ce;
        while(getline(cin,str))
            ce.get_count(str);
        ce.out();
    }
	/********** End **********/
  	return 0;
}

