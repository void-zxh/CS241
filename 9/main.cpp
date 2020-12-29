#include "std_lib_facilities.h"
#include "Question_1.h"
#include "Question_2.h"
#include "Question_3.h"
int main()
{
    /********** Begin **********/
    int exercise = 3;
    
    if (exercise == 1)
    {
        Question1 q1;
        q1.solve();
    }
    else if(exercise == 2)
    {
        Question2 q2;
        q2.solve();
    }
    else if(exercise == 3)
    {
        Question3 q3;
        string str;
        getline(cin,str);
        q3.solve(str);
    }
    else
	    cout<<"error";
    return 0;
}

