#include <iostream>
#include <string>
#include "f.h"

using namespace std;

bool compare(string a,string b)  //compare two positive integers;a>b is true,others are false
{
    if(a.size()>b.size())
    {
        return true;
    }
    else if(a.size()==b.size())
    {
        return a>b;
    }
    else
    {
        return false;
    }
}

string next(string a)
{
    return add_positive_integers(a,"1");
}

Division ddiv_positive_integers_slow(string a,string b)  //compute the division of two positive integers (may be large numbers)
{
    Division result;
    result.quotient="0";
    result.remainder="";

    if(sub_positive_integers(b,"0")=="0")
    {
        result.quotient="Sorry! This is illegal input!";
        result.remainder="Sorry! This is illegal input!";
    }
    else if(sub_positive_integers(a,"0")=="0")
    {
        result.quotient="0";
        result.remainder="0";
    }
    else
    {
        for(string i="0";;i=next(i))
        {
            if(compare(mul_positive_integers(b,i),a)==0&&compare(mul_positive_integers(b,next(i)),a)==1)
            {
                result.quotient=i;
                result.remainder=sub_positive_integers(a,mul_positive_integers(b,i));
                break;
            }
        }
    }
    

    return result;

}

Division ddiv_positive_integers(string a,string b)  //compute the division of two positive integers (may be large numbers)
{
    if(a.size()-b.size()<5)
    {
        return ddiv_positive_integers_slow(a,b);
    }
    else  //when a>>b, the method using above is very slow
    {
        Division result;
        result.quotient="0";
        result.remainder="0";
        while(true)
        {
            //divide the first b.size()+1 bits of a by b, the result is larger than 1
            Division temp=ddiv_positive_integers_slow(a.substr(0,b.size()+1),b);  
            if(temp.quotient=="Sorry! This is illegal input!")
            {
                result=temp;
                break;
            }
            a.erase(0,b.size()+1);
            for(int j=0;j<a.size();j++)
            {
                temp.quotient=temp.quotient.append("0");
                temp.remainder=temp.remainder.append("0");
            }
            result.quotient=add_positive_integers(result.quotient,temp.quotient);
            a=add_positive_integers(a,temp.remainder);  //new dividend
            if(compare(b,a)==1)
            {
                result.remainder=a;
                break;
            }
        }
        return result;
    }
}

string div_positive_integers(string a,string b)  //compute the division of two positive integers by accurating to >=n decimal places
{
    int n=10;
    if(sub_positive_integers(b,"0")=="0")
    {
        return "Sorry! This is illegal input!";
    }
    else if(sub_positive_integers(a,"0")=="0")
    {
        return "0";
    }
    else
    {
        Division result1=ddiv_positive_integers(a,b);
        for(int i=0;i<n+b.size();i++)
        {
            result1.remainder.append("0");
        }
        Division result2=ddiv_positive_integers(result1.remainder,b);
        string result=add(result1.quotient,result2.quotient+"e-"+std::to_string(n+b.size()));
        return result;
    }
}

string div_positive(string a,string b)  //compute the division of two positive numbers which have normal/decimal/SCM formal
{
    int n=10;
    string aa="";
    string bb="";
    string e_of_a="";
    string e_of_b="";

    if(n==0)
    {
        n=1;  
    }
    if(isNum(a)==true)
    {
        aa=a;
        e_of_a="0";
    }

    if(isDecimal(a)==true)
    {
        int loc_of_dot=0;
        for(int i=0;i<a.size();i++)
        {
            int t = (int)a[i];
            if(t==46)
            {
                loc_of_dot=i;
            }
            else
            {
                aa=aa+a[i];
            }
        }
        e_of_a="-"+std::to_string(a.size()-loc_of_dot-1);
    }

    if(isScientific_counting_method(a)==true)
    {
        string a1="";  //before E/e
        string a2="";  //after E/e
        int loc_of_e=0;
        for(int i=0;i<a.size();i++)
        {
            int t = (int)a[i];
            if(t!=69 and t!=101)
            {
                a1=a1+a[i];
            }
            else
            {
                loc_of_e=i;
                break;
            }
        }

        for(int i=loc_of_e+1;i<a.size();i++)
        {
            a2=a2+a[i];
        }

        if(isNum(a1)==true)
        {
            aa=a1;
            e_of_a=a2;
        }

        if(isDecimal(a1)==true)
        {
            int loc_of_dot__=0;
            string aa__="";
            for(int i=0;i<a1.size();i++)
            {
                int t = (int)a1[i];
                if(t==46)
                {
                    loc_of_dot__=i;
                }
                else
                {
                    aa__=aa__+a1[i];
                }
            }
            string e_of_a1="-"+std::to_string(a1.size()-loc_of_dot__-1);
            aa=aa__;
            e_of_a=std::to_string(std::stoi(e_of_a1)+std::stoi(a2));
        }
    }

    if(isNum(b)==true)
    {
        bb=b;
        e_of_b="0";
    }

    if(isDecimal(b)==true)
    {
        int loc_of_dot=0;
        for(int i=0;i<b.size();i++)
        {
            int t = (int)b[i];
            if(t==46)
            {
                loc_of_dot=i;
            }
            else
            {
                bb=bb+b[i];
            }
        }
        e_of_b="-"+std::to_string(b.size()-loc_of_dot-1);
    }

    if(isScientific_counting_method(b)==true)
    {
        string b1="";  //before E/e
        string b2="";  //after E/e
        int loc_of_e=0;
        for(int i=0;i<b.size();i++)
        {
            int t = (int)b[i];
            if(t!=69 and t!=101)
            {
                b1=b1+b[i];
            }
            else
            {
                loc_of_e=i;
                break;
            }
        }

        for(int i=loc_of_e+1;i<b.size();i++)
        {
            b2=b2+b[i];
        }

        if(isNum(b1)==true)
        {
            bb=b1;
            e_of_b=b2;
        }

        if(isDecimal(b1)==true)
        {
            int loc_of_dot__=0;
            string bb__="";
            for(int i=0;i<b1.size();i++)
            {
                int t = (int)b1[i];
                if(t==46)
                {
                    loc_of_dot__=i;
                }
                else
                {
                    bb__=bb__+b1[i];
                }
            }
            string e_of_b1="-"+std::to_string(b1.size()-loc_of_dot__-1);
            bb=bb__;
            e_of_b=std::to_string(std::stoi(b2)+std::stoi(e_of_b1));
        }
    }

    if ((isNum(a)==1 or isDecimal(a)==1 or isScientific_counting_method(a)==1)&&(isNum(b)==1 or isDecimal(b)==1 or isScientific_counting_method(b)==1))
    {
        string ans1=div_positive_integers(aa,bb);
        string ans2=std::to_string(std::stoi(e_of_a)-std::stoi(e_of_b));
            
        return mul(ans1,"1E"+ans2);
    }
    else 
    {
        return "Sorry! This is illegal input!";
    }
}

string round(string a)  //a is the output of normalization(a positive number with standard scientific counting form)
{
    int n=8;
    string a1="";  //before E/e
    string a2="";  //after E/e
    int lo=0;  //location of E/e
    string result="";  //store the result

    for(int i=0;i<a.size();i++)
    {
        int t = (int)a[i];
        if(t!=69 and t!=101)
        {
            a1=a1+a[i];
        }
        else
        {
            lo=i;
            break;
        }
    }
    for(int i=lo+1;i<a.size();i++)
    {
        a2=a2+a[i];
    }

    if(isNum(a1)==true)
    {
        result=a;
    }
    else
    {
        string a1_1="";
        string a1_2="";
        int loc_of_dot=0;
        for(int i=0;i<a1.size();i++)
        {
            int t = (int)a1[i];
            if(t==46)
            {
                loc_of_dot=i;
                break;
            }
            else
            {
                a1_1=a1_1+a1[i];
            }
        }
        for(int i=loc_of_dot+1;i<a1.size();i++)
        {
            a1_2=a1_2+a1[i];
        }
        if(a1_2.size()<=n)
        {
            result=a;
        }
        else
        {
            if((int)a1_2[n]<=52)
            {
                a1=add(a1_1,mul(a1_2.substr(0,n),"1e-"+std::to_string(n)));
            }
            else
            {
                a1=add(a1_1,mul(add(a1_2.substr(0,n),"1"),"1e-"+std::to_string(n)));
            }
        }
        result=mul(a1,"1E"+a2);
    }

    return result;
}

string div(string a,string b)  //compute the division of two numbers which have normal/decimal/SCM formal
{
    int sign_a=1;
    int sign_b=1;

    string aa=a.c_str();
    string bb=b.c_str();

    if((int)a[0]==43)  //"+"
    {
        a.erase(0, 1);
    }
    if((int)a[0]==45)  //"-"
    {
        a.erase(0, 1);
        sign_a=-1;
    }
    if((int)b[0]==43)  //"+"
    {
        b.erase(0, 1);
    }
    if((int)b[0]==45)  //"-"
    {
        b.erase(0, 1);
        sign_b=-1;
    }

    int sign=sign_a*sign_b;
    string word=div_positive(a,b); 

    if((int)word[0]==83)  //S
    {
        return word;
    }
    else
    {
        if(sign==1)
        {
            return round(word);
        }
        else
        {
            return "-"+round(word);
        }
    }
    
}