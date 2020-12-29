#ifndef CODE_EXERCISE_H
#define CODE_EXERCISE_H

#include "Token_Exercise_1.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <string>
#include <map>

std :: string sgn[] = {
    "alignas", "alignof", "and", "and_eq",
    "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept",
    "auto", "bitand", "bitor", "bool",
    "break", "case", "catch", "char",
    "char8_t", "char16_t", "char32_t", "class",
    "compl", "concept", "const", "consteval",
    "constexpr", "constinit", "const_cast", "continue",
    "co_await", "co_return", "co_yield", "decltype",
    "default", "define", "defined", "delete",
    "do", "double", "dynamic_cast", "elif",
    "else", "error", "endif", "enum",
    "explicit", "export", "extern", "false",
    "final", "float", "for", "friend",
    "goto", "if", "ifdef", "ifndef",
    "import", "include", "inline", "int",
    "line", "long", "module", "mutable",
    "namespace", "new", "noexcept", "not",
    "not_eq", "nullptr", "operator", "or",
    "or_eq", "override", "pragma", "private",
    "protected", "public", "reflexpr", "register",
    "reinterpret_cast", "requires", "return", "short",
    "signed", "sizeof", "static", "static_assert",
    "static_cast", "struct", "switch", "synchronized",
    "template", "this", "thread_local", "throw",
    "xor_eq", "true", "try", "typedef",
    "typeid", "typename", "undef", "union",
    "unsigned", "using", "virtual", "void",
    "volatile", "wchar_t", "while", "xor"
};

const int sign_cou=112;

class code_exercise
{
    friend int checkout(const string& str);
    friend void small_change(string& str);
private:
    std::map<string,int> mp_token;
    std::map<string,int> sign_code;
    int off;
public:
    code_exercise()
    {
        mp_token.clear();
        sign_code.clear();
        for(int i=0;i<112;i++)
            sign_code[sgn[i]]=1;
        off=0;
    }

    void get_count(const string& str)
    {
        int i,len=str.size(),chr=0;
        string in="";
        for(i=0;i<len;i++)
            if(off==0)
            {
                if((str[i]>='0'&&str[i]<='9')||(str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')||str[i]=='_')
                {
                    if(!(str[i]>='0'&&str[i]<='9'))
                        chr=1;
                    if(chr)
                        in+=str[i];
                    else
                        continue;
                }
                else if(i+1<len&&str[i]=='/'&&str[i+1]=='/')
                    return;
                else if(i+1<len&&str[i]=='/'&&str[i+1]=='*')
                {
                    off=1;
                    if(checkout(in))
                    {
                        if(sign_code.find(in)==sign_code.end())
                        {
                            //cout<<in<<endl;
                            if(mp_token.find(in)==mp_token.end())
                                mp_token[in]=1;
                            else
                                mp_token[in]++;
                        }
                        in="";
                        chr=0;
                    }
                    else
                        in="";
                }
                else
                {
                    //cout<<in<<endl;
                    if(str[i]=='\\')
                        i++;
                    if(checkout(in))
                    {
                        //small_change(in);
                        if(sign_code.find(in)==sign_code.end())
                        {
                            //cout<<in<<endl;
                            if(mp_token.find(in)==mp_token.end())
                                mp_token[in]=1;
                            else
                                mp_token[in]++;
                        }
                        in="";
                    }
                    else
                    {
                        in="";
                        continue;
                    }
                    chr=0;
                }
            }
            else if(i+1<len&&str[i]=='*'&&str[i+1]=='/')
                off=0;
        if(checkout(in))
        {
            if(sign_code.find(in)==sign_code.end())
            {
                //cout<<in<<endl;
                if(mp_token.find(in)==mp_token.end())
                    mp_token[in]=1;
                else
                    mp_token[in]++;
            }
            in="";
            chr=0;
        }
    }

    void out()
    {
        map<string,int>::iterator it;
        for(it=mp_token.begin();it!=mp_token.end();it++)
            cout<<it->first<<endl;
    }
};

#endif