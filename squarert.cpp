#include <iostream>
#include <string>
#include "f.h"

using namespace std;

string square_root(string a,string times)  //compute the aquare root of a positive integers
{
    string step="1e"+std::to_string(a.size()-1);
    if(isNum(times)==false||isNum(a)==false)
    {  
        return "Sorry! This is illegal input!";
    }
    else
    {
        string result;
        //a^0.5 is the positive zero of the function f(x)=x^2-a, then we can gain this by the Newton's iteration method
        string flag="0";
        while(true)
        {   
            string a1=sub(mul(flag,flag),a);
            string a2=sub(mul(add(flag,step),add(flag,step)),a);
            if(sub(a1,"0")=="0")
            {   
                result=flag;
                break;
            }
            else if(sub(a2,"0")=="0")
            {   
                result=add(flag,step);
                break;
            }
            else
            {
                if((int)sub(a1,"0")[0]==45&&(int)sub(a2,"0")[0]!=45)  //a1<0&&a2>0
                {   
                    result=newton_iteration(a,flag,add(flag,step),std::stoi(times));
                    break;
                }
                else
                {
                    flag=add(flag,step);
                }
            }
        }
    
        return result;

    }
    
    
}

string newton_iteration(string a,string a1,string a2,int times)  //find the zero of f(x)=x^2-a within [a1,a2]
{
    string p0=div(add(a1,a2),"2");  //initial point
    int N=times;  //iteration times
    string p;
    for(int i=0;i<N;i++)
    {
        p=sub(p0,div(sub(mul(p0,p0),a),mul("2",p0)));
        p0=p;
    }
    return p;
}