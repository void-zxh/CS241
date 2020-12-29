#include "std_lib_facilities.h"
#include "Huffman_Exercise_1.h"
#include "Huffman_Exercise_2.h"

int main()
{
    /********** Begin **********/
    bool exercise_1 = false;
    if (exercise_1)
    {
        //第一关执行代码
        //Please fix Huffman_Exercise_1.h and Huffman_Exercise_1.cpp
        string str="",st;          
        while(getline(cin,st))
        {
            if(str!="") 
                str+='\n';
            str=str+st;
            printf("%d\n",str.size());
        }
        Huffman hf;
        hf.init(str);
        hf.work();
    }
    else
    {
        //Please fix Huffman_Exercise_2.h and Huffman_Exercise_2.cpp  
        string str="",st;          
        while(getline(cin,st))
        {
            if(str!="") 
                str+='\n';
            str=str+st;
        }
        Huffmanword hf;
        hf.init(str);
        hf.work();
    }
    /********** End **********/
  	return 0;
}

