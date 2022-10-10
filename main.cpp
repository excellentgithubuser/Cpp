#include <iostream>
#include <string>
#include <cstring>
#include "f.h"
using namespace std;

string calculator1(string str);  //without parentheses
string calculator(string str);  //allow parentheses

int main()
{
    cout<<"Please select the model you want!"<<endl;
    cout<<"1. Four fundamental operations;"<<endl;
    cout<<"2. Four fundamental operations with variables you can define;"<<endl;
    cout<<"3. Find the square root of a positive integer;"<<endl;
    cout<<"4. Compute the integer power of a positive integer."<<endl;

    string m;
    cin>>m;
    if(m=="1")
    {
        cout<<"Please enter the expression that you want to compute:"<<endl;
        cout<<"Notes: 1. Please use '+', '-', '*', '/' to express the sign of four fundamental operations;"<<endl;
        cout<<"       2. Please do not enter spaces;"<<endl;
        cout<<"       3. You can enter integers, decimals and numbers given by the scientific counting method;"<<endl;
        cout<<"       4. You can enter numbers which are beyond the range of int, or even of long int;"<<endl;
        cout<<"       5. In division, the result is accurate to four decimal places."<<endl;
        string a;
        cin>>a;
        int flag=0;
        for(int i=0;i<a.size();i++)
        {
            if((((int)a[i]>=40&&(int)a[i]<=43)||((int)a[i]>=45&&(int)a[i]<=57)||(int)a[i]==69||(int)a[i]==101)==false)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            cout<<"Sorry! This is illegal input!"<<endl;
        }
        else
        {
            cout<<"The result is: "<<calculator(a)<<endl;
        }    
    }
    else if(m=="2")
    {
        cout<<"Warning: 1. You cannot use 'e' or 'E' to define you variables since they are used in the scientific counting method;"<<endl;
        cout<<"         2. Your variables should have only one length;"<<endl;
        cout<<"         3. Numbers, '+', '-', '*', '/', '.','(', ')' are not allowed to be contained in the names of the variables."<<endl;
        cout<<"         4. Please do not enter spaces in the equations that define variables"<<endl;
        string b;
        char* s = new char[1024]; 

        cin.ignore();
        while (cin.getline(s, 1024))
        {
            int flag=0;
            for(int i=0;i<strlen(s);i++)
            {
                if((int)s[i]==61)  //=
                {
                    flag=1;
                    break;
                }
            }
            b += s;
            b += '\n';           
            if (flag == 0)           
            {
                break;
            }
        }
        delete[]s;

        int num_of_v=-1;
        for(int i=0;i<b.size();i++)
        {
            if(b[i]=='\n')
            {
                num_of_v=num_of_v+1;
            }
        }
        string variables[num_of_v];
        string equation;
        for(int i=0;i<num_of_v;i++)
        {
            variables[i]=b.substr(0,b.find('\n'));
            b.erase(0,b.find('\n')+1);
        }
        equation=b.substr(0,b.size()-1);
        
        string library="1234567890.+-*/()Ee";
        for(int i=0;i<equation.size();i++)
        {
            if(library.find(equation[i])==library.npos)
            {
                for(int j=0;j<num_of_v;j++)
                {
                    if((int)variables[j][0]==(int)equation[i])
                    {
                        equation=equation.replace(i,1,variables[j].substr(variables[j].find("=")+1,variables[j].size()));
                        break;
                    }
                }
            }
        }

        cout<<"The result is: "<<calculator(equation)<<endl;
    }
    else if(m=="3")
    {
        cout<<"Please enter the radicand:"<<endl;
        string c1;
        cin>>c1;
        cout<<"Please enter the times of iterations you want:"<<endl;
        cout<<"(To manage the number smaller than 10^20, we recommend between 20 and 40 times. The larger number need more times of iteration which will greatly extend the operation time!)"<<endl;
        string c2;
        cin>>c2;
        cout<<"The result is: "<<square_root(c1,c2)<<endl;  
        //The operations for determining whether c1 and c2 are valid have been written in squarert.cpp.
    }
    else if(m=="4")
    {
        cout<<"Please enter the base number: (you can enter an arbitrary non-negative integers)"<<endl;
        string d1;
        cin>>d1;
        cout<<"Please enter the exponent: (you can enter an arbitrary integers)"<<endl;
        string d2;
        cin>>d2;
        cout<<"The result is: "<<power(d1,d2)<<endl;
        //The operations for determining whether d1 and d2 are valid have been written in power.cpp.
    }
    else
    {
        cout<<"Sorry! This is illegal input!"<<endl;
    }

}


string calculator1(string str)  //without parentheses
{
	string result="";

    int loc_mul=str.size()+1;  //check * and / firstly
    int loc_div=str.size()+1;
    for(int i=0;i<str.size();i++)
    {
        if((int)str[i]==42)  //*
        {
            loc_mul=i;
            break;
        }
    }
    for(int i=0;i<str.size();i++)
    {
        if((int)str[i]==47)  // /
        {
            loc_div=i;
            break;
        }
    }

    if(loc_mul!=str.size()+1||loc_div!=str.size()+1)
    {
        if(loc_mul<loc_div)  //do mul 
        {
            int loc_mul_element1=0;
            for(int i=1;i<=loc_mul;i++)
            {
                if((int)str[loc_mul-i]==43||(int)str[loc_mul-i]==45||(int)str[loc_mul-i]==42||(int)str[loc_mul-i]==47)
                {
                    if((loc_mul-i==1)||((int)str[loc_mul-i-1]!=69&&(int)str[loc_mul-i-1]!=101))  //E e
                    {
                        loc_mul_element1=loc_mul-i+1;
                        break;
                    }
                }
            }
            if(loc_mul_element1>=2)
            {
                if((int)str[loc_mul_element1-2]==43||(int)str[loc_mul_element1-2]==45||(int)str[loc_mul_element1-2]==42||(int)str[loc_mul_element1-2]==47)
                {
                    loc_mul_element1=loc_mul_element1-1;  //manage the form like 3+-4*2
                }
            }
            if(loc_mul_element1==1&&(int)str[0]==45)  //in -3*4,we think that there is one * sign in it, and it is (-3)*4
            {
                loc_mul_element1=0;
            }
            int loc_mul_element2=str.size()-1;
            for(int i=2;i<=str.size()-loc_mul-1;i++)
            {
                if((int)str[loc_mul+i]==43||(int)str[loc_mul+i]==45||(int)str[loc_mul+i]==42||(int)str[loc_mul+i]==47)
                {
                    if((int)str[loc_mul+i-1]!=69&&(int)str[loc_mul+i-1]!=101)
                    {
                        loc_mul_element2=loc_mul+i-1;
                        break;
                    }   
                }
            }
            
            string mul1=str.substr(loc_mul_element1,loc_mul-loc_mul_element1);
            string mul2=str.substr(loc_mul+1,loc_mul_element2-loc_mul);
            string remaind1=str.substr(0,loc_mul_element1);
            string remaind2=str.substr(loc_mul_element2+1,str.size()-loc_mul_element2-1);
            string new_str=remaind1+mul(mul1,mul2)+remaind2;
            int flag=0;
            if((int)new_str[0]==45)
            {
                for(int i=1;i<new_str.size();i++)
                {
                    if((int)new_str[i]==42||(int)new_str[i]==43||(int)new_str[i]==45||(int)new_str[i]==47)
                    {
                        if((int)new_str[i-1]!=69&&(int)new_str[i-1]!=101)
                        {
                            flag=1;
                        }
                    }
                }
            }
            else
            {
                for(int i=0;i<new_str.size();i++)
                {
                    if((int)new_str[i]==42||(int)new_str[i]==43||(int)new_str[i]==45||(int)new_str[i]==47)
                    {
                        if((int)new_str[i-1]!=69&&(int)new_str[i-1]!=101)
                        {
                            flag=1;
                        }
                    }
                }
            }
            if(flag==1)
            {
                result=calculator1(new_str);
            }
            else
            {
                result=new_str;
            }
        }
        else  //do div 
        {
            int loc_div_element1=0;
            for(int i=1;i<=loc_div;i++)
            {
                if((int)str[loc_div-i]==43||(int)str[loc_div-i]==45||(int)str[loc_div-i]==42||(int)str[loc_div-i]==47)
                {
                    if((loc_div-i-1==0)||((int)str[loc_div-i-1]!=69&&(int)str[loc_div-i-1]!=101))
                    {
                        loc_div_element1=loc_div-i+1;
                        break;
                    }
                }
            }
            if(loc_div_element1>=2)
            {
                if((int)str[loc_div_element1-2]==43||(int)str[loc_div_element1-2]==45||(int)str[loc_div_element1-2]==42||(int)str[loc_div_element1-2]==47)
                {
                    loc_div_element1=loc_div_element1-1;
                }
            }
            if(loc_div_element1==1&&(int)str[0]==45)  //in -3/4,we think that there is one / sign in it, and it is (-3)/4
            {
                loc_div_element1=0;
            }
            int loc_div_element2=str.size()-1;
            for(int i=2;i<=str.size()-loc_div-1;i++)
            {
                if((int)str[loc_div+i]==43||(int)str[loc_div+i]==45||(int)str[loc_div+i]==42||(int)str[loc_div+i]==47)
                {
                    if((int)str[loc_div+i-1]!=69&&(int)str[loc_div+i-1]!=101)
                    {
                        loc_div_element2=loc_div+i-1;
                        break;
                    }
                }
            }
                
            string div1=str.substr(loc_div_element1,loc_div-loc_div_element1);
            string div2=str.substr(loc_div+1,loc_div_element2-loc_div);
            string remaind1=str.substr(0,loc_div_element1);
            string remaind2=str.substr(loc_div_element2+1,str.size()-loc_div_element2-1);
            string new_str=remaind1+div(div1,div2)+remaind2;
            int flag=0;
            if((int)new_str[0]==45)
            {
                for(int i=1;i<new_str.size();i++)
                {
                    if((int)new_str[i]==42||(int)new_str[i]==43||(int)new_str[i]==45||(int)new_str[i]==47)
                    {
                        if((int)new_str[i-1]!=69&&(int)new_str[i-1]!=101)
                        {
                            flag=1;
                        }
                    }
                }
            }
            else
            {
                for(int i=0;i<new_str.size();i++)
                {
                    if((int)new_str[i]==42||(int)new_str[i]==43||(int)new_str[i]==45||(int)new_str[i]==47)
                    {
                        if((int)new_str[i-1]!=69&&(int)new_str[i-1]!=101)
                        {
                            flag=1;
                        }
                    }
                }
            }
            if(flag==1)
            {
                result=calculator1(new_str);
            }
            else
            {
                result=new_str;
            }
        }
    }
    else
    {
        int loc_add=str.size()+1;  //check + and - secondly
        int loc_sub=str.size()+1;
        for(int i=0;i<str.size();i++)
        {
            if((int)str[i]==43)  //+
            {
                loc_add=i;
                break;
            }
        }
        for(int i=1;i<str.size();i++)  //in -3+4,we think that there is one + sign in it, and it is (-3)+4
        {
            if((int)str[i]==45&&(int)str[i-1]!=69&&(int)str[i-1]!=101)  //-  E  e
            {
                loc_sub=i;
                break;
            }
        }

        if(loc_add!=str.size()+1||loc_sub!=str.size()+1)
        {
            if(loc_add<loc_sub)  //do add
            {
                int loc_add_element1=0;
                for(int i=1;i<=loc_add;i++)
                {
                    if((int)str[loc_add-i]==43||(int)str[loc_add-i]==45||(int)str[loc_add-i]==42||(int)str[loc_add-i]==47)
                    {
                        if((loc_add-i-1==0)||((int)str[loc_add-i-1]!=69&&(int)str[loc_add-i-1]!=101))
                        {
                            loc_add_element1=loc_add-i+1;
                            break;
                        }
                    }
                }
                if(loc_add_element1>=2)
                {
                    if((int)str[loc_add_element1-2]==43||(int)str[loc_add_element1-2]==45||(int)str[loc_add_element1-2]==42||(int)str[loc_add_element1-2]==47)
                    {
                        loc_add_element1=loc_add_element1-1;
                    }
                }
                if(loc_add_element1==1&&(int)str[0]==45)  //in -3+4,we think that there is one + sign in it, and it is (-3)+4
                {
                    loc_add_element1=0;
                }
                int loc_add_element2=str.size()-1;
                for(int i=2;i<=str.size()-loc_add-1;i++)
                {
                    if((int)str[loc_add+i]==43||(int)str[loc_add+i]==45||(int)str[loc_add+i]==42||(int)str[loc_add+i]==47)
                    {
                        if((int)str[loc_add+i-1]!=69&&(int)str[loc_add+i-1]!=101)
                        {
                            loc_add_element2=loc_add+i-1;
                            break;
                        }
                    }
                }
                
                string add1=str.substr(loc_add_element1,loc_add-loc_add_element1);
                string add2=str.substr(loc_add+1,loc_add_element2-loc_add);
                string remaind1=str.substr(0,loc_add_element1);
                string remaind2=str.substr(loc_add_element2+1,str.size()-loc_add_element2-1);
                string new_str=remaind1+add(add1,add2)+remaind2;
                int flag=0;
                if((int)new_str[0]==45)
                {
                    for(int i=1;i<new_str.size();i++)
                    {
                        if((int)new_str[i]==42||(int)new_str[i]==43||(int)new_str[i]==45||(int)new_str[i]==47)
                        {
                            if((int)new_str[i-1]!=69&&(int)new_str[i-1]!=101)
                            {
                                flag=1;
                            }
                        }
                    }
                }
                else
                {
                    for(int i=0;i<new_str.size();i++)
                    {
                        if((int)new_str[i]==42||(int)new_str[i]==43||(int)new_str[i]==45||(int)new_str[i]==47)
                        {
                            if((int)new_str[i-1]!=69&&(int)new_str[i-1]!=101)
                            {
                                flag=1;
                            }
                        }
                    }
                }
                if(flag==1)
                {
                    result=calculator1(new_str);
                }
                else
                {
                    result=new_str;
                }
            }
            else  //do sub 
            {
                int loc_sub_element1=0;
                for(int i=1;i<=loc_sub;i++)
                {
                    if((int)str[loc_sub-i]==43||(int)str[loc_sub-i]==45||(int)str[loc_sub-i]==42||(int)str[loc_sub-i]==47)
                    {
                        if((loc_sub-i-1==0)||((int)str[loc_sub-i-1]!=69&&(int)str[loc_sub-i-1]!=101))
                        {
                            loc_sub_element1=loc_sub-i+1;
                            break;
                        }
                    }
                }
                if(loc_sub_element1>=2)
                {
                    if((int)str[loc_sub_element1-2]==43||(int)str[loc_sub_element1-2]==45||(int)str[loc_sub_element1-2]==42||(int)str[loc_sub_element1-2]==47)
                    {
                        loc_sub_element1=loc_sub_element1-1;
                    }
                }
                if(loc_sub_element1==1&&(int)str[0]==45)  //in -3-4,we think that there is one - sign in it, and it is (-3)-4
                {
                    loc_sub_element1=0;
                }
                int loc_sub_element2=str.size()-1;
                for(int i=2;i<=str.size()-loc_sub-1;i++)
                {
                    if((int)str[loc_sub+i]==43||(int)str[loc_sub+i]==45||(int)str[loc_sub+i]==42||(int)str[loc_sub+i]==47)
                    {
                        if((int)str[loc_sub+i-1]!=69&&(int)str[loc_sub+i-1]!=101)
                        {
                            loc_sub_element2=loc_sub+i-1;
                            break;
                        }
                    }
                }
                    
                string sub1=str.substr(loc_sub_element1,loc_sub-loc_sub_element1);
                string sub2=str.substr(loc_sub+1,loc_sub_element2-loc_sub);
                string remaind1=str.substr(0,loc_sub_element1);
                string remaind2=str.substr(loc_sub_element2+1,str.size()-loc_sub_element2-1);
                string new_str=remaind1+sub(sub1,sub2)+remaind2;
                int flag=0;
                if((int)new_str[0]==45)
                {
                    for(int i=1;i<new_str.size();i++)
                    {
                        if((int)new_str[i]==42||(int)new_str[i]==43||(int)new_str[i]==45||(int)new_str[i]==47)
                        {
                            if((int)new_str[i-1]!=69&&(int)new_str[i-1]!=101)
                            {
                                flag=1;
                            }
                        }
                    }
                }
                else
                {
                    for(int i=0;i<new_str.size();i++)
                    {
                        if((int)new_str[i]==42||(int)new_str[i]==43||(int)new_str[i]==45||(int)new_str[i]==47)
                        {
                            if((int)new_str[i-1]!=69&&(int)new_str[i-1]!=101)
                            {
                                flag=1;
                            }
                        }
                    }
                }
                if(flag==1)
                {
                    result=calculator1(new_str);
                }
                else
                {
                    result=new_str;
                }
            }
        }

    }

    string strr=str.c_str();
    if((int)str[0]==43||(int)str[0]==45)
    {
        str.erase(0,1);
    }

    if(isNum(str)==true||isDecimal(str)==true||isScientific_counting_method(str)==true)
    {
        return strr;  //for example, input is 9e-1, then output 9e-1
    }
    else if(result=="")
    {
        return "Sorry! This is illegal input!";
    }
    else
    {
        return result;
    }

}

string calculator(string str)  //allow parentheses
{
    int num_left_parentheses=0;
    int num_right_parentheses=0;
    for (int i=0;i<str.size();i++)
    {
        if((int)str[i]==40)
        {
            num_left_parentheses=num_left_parentheses+1;
        }
    }
    for (int i=0;i<str.size();i++)
    {
        if((int)str[i]==41)
        {
            num_right_parentheses=num_right_parentheses+1;
        }
    }

    if(num_left_parentheses==0&&num_right_parentheses==0)
    {
        return calculator1(str);
    }
    else if(num_left_parentheses==1&&num_right_parentheses==1&&(int)str[0]==40&&(int)str[str.size()-1]==41)
    {
        str.erase(0,1);
        str.erase(str.size()-1,1);
        return calculator1(str);
    }
    else if(num_left_parentheses!=num_right_parentheses)
    {
        return "Sorry! This is illegal input!";
    }
    else
    {
        int left_parentheses[num_left_parentheses];
        int right_parentheses[num_right_parentheses];
        left_parentheses[0]=str.find("(",0);
        for (int i=1;i<num_left_parentheses;i++)
        {                
            left_parentheses[i]=str.find("(",left_parentheses[i-1]+1);
                
        }
        right_parentheses[0]=str.find(")",0);
        for (int i=1;i<num_right_parentheses;i++)
        {                
            right_parentheses[i]=str.find(")",right_parentheses[i-1]+1);
                
        }
        int left;
        int right;
        for(int i=0;i<num_left_parentheses;i++)
        {
            for(int j=0;j<num_right_parentheses;j++)
            {
                int flag=0;
                for(int k=left_parentheses[i]+1;k<right_parentheses[j];k++)
                {
                    if((int)str[k]==40||(int)str[k]==41)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    left=left_parentheses[i];
                    right=right_parentheses[j];
                    goto here;
                }
            }
        }
        here:
        if(right+1<=str.size()-1)
        {
            return calculator(str.substr(0,left)+calculator1(str.substr(left+1,right-left-1))+str.substr(right+1,str.size()-right-1));
        }
        else
        {
            return calculator(str.substr(0,left)+calculator1(str.substr(left+1,right-left-1)));        
        }
    }

}