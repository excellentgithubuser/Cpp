#include <iostream>
#include <string>
#include "f.h"

using namespace std;

string power(string a, string b)  //a>=0, a and b are both integers
{//if you want to conpute the case which a is negative, you just need to tell the sign of abs(a)^b which can gained by my code
    int sign_b=1;
    if((int)b[0]==45)  //"-"
    {
        b.erase(0, 1);
        sign_b=-1;
    }
    if(isNum(a)==0||isNum(b)==0)
    {
        return "Sorry! This is illegal input!";    
    }
    else if(sub(a,"0")=="0"&&sub(b,"0")=="0")
    {
        return "Sorry! This is illegal input!";    
    }
    else if(sub(a,"0")!="0"&&sub(b,"0")=="0")
    {
        return "1";
    }
    else if(sub(a,"0")=="0"&&sub(b,"0")!="0")
    {
        return "0";
    }
    else if(sign_b==1)
    {
        return power_compute(a,b);
    }
    else
    {
        return div("1",power_compute(a,b));
    }
}

string power_compute(string a,string b)  //here a and b are both positive integers
{
    string result="1";
    if(b.size()<=2)
    {
        for(int i=0;i<std::stoi(b);i++)
        {
            result=mul_positive_integers(result,a);
        }
    }
    else
    {
        if(ddiv_positive_integers(b,"2").remainder=="0")
        {
            result=power_compute(mul_positive_integers(a,a),ddiv_positive_integers(b,"2").quotient);
        }
        else
        {
            result=mul_positive_integers(a,power_compute(mul_positive_integers(a,a),ddiv_positive_integers(b,"2").quotient));
        }
    }
    return result;
}