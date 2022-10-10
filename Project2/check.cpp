#include <iostream>
#include <string>
#include "f.h"

using namespace std;

bool isNum(string str)  //check whether the string is an non-negative integer
{  
    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if (t >= 48 && t <= 57)
        {
            continue;
        }
        else
        {
            return false;
        }
    } 
    return true;
} 

bool isDecimal(string str)  //check whether the string is a decimal
{
    bool condition1=false;
    bool condition2=false;
    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if (t==46 or (t>=48&&t<=57))
        {
            condition1=true;
        }
        else
        {
            condition1=false;
            break;
        }
    } 
    
    int flag=0;
    int loc_of_dot=0;
    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if (t==46)
        {
            flag=flag+1;
            loc_of_dot=i;
        }
    }

    if (flag==1&&loc_of_dot<str.size()-1)
    {
        condition2=true;
    }
    else
    {
        condition2=false;
    }
    
    return condition1&&condition2;
}

bool isScientific_counting_method_by_E(string str)  //check whether the string is given by the scientific counting method
{
    bool condition1=false; 
    bool condition2=false;

    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if ((t==69) or (t==46) or (t==45) or (t==43) or (t>=48&&t<=57))
        {
            condition1=true;
        }
        else
        {
            condition1=false;
            break;
        }
    } 
    
    int flag1=0;
    int loc_of_dot=0;
    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if (t==46)
        {
            flag1=flag1+1;
            loc_of_dot=i;
        }
    }

    int flag2=0;
    int loc_of_E=0;
    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if (t==69)
        {
            flag2=flag2+1;
            loc_of_E=i;
        }
    }

    int flag3=0;
    int loc_of_negative=0;
    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if (t==45)
        {
            flag3=flag3+1;
            loc_of_negative=i;
        }
    }

    int flag4=0;
    int loc_of_positive=0;
    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if (t==43)
        {
            flag4=flag4+1;
            loc_of_positive=i;
        }
    }
    
    if((flag3==1&&flag4==0&&loc_of_negative==loc_of_E+1) or (flag4==1&&flag3==0&&loc_of_positive==loc_of_E+1) or (flag3==0&&flag4==0))
    {
        if(flag1==0&&flag2==1&&loc_of_E>0&&loc_of_E<str.size()-1)
        {
            condition2=true;
        }
        else if(flag1==1&&flag2==1&&loc_of_dot<loc_of_E-1&&loc_of_E>0&&loc_of_E<str.size()-1)
        {
            condition2=true;
        }
        else
        {
            condition2=false;
        }
    }
    
    return condition1&&condition2;
}

bool isScientific_counting_method_by_e(string str)  //check whether the string is given by the scientific counting method
{
    bool condition1=false; 
    bool condition2=false;

    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if ((t==101) or (t==46) or (t==45) or (t==43) or (t>=48&&t<=57))
        {
            condition1=true;
        }
        else
        {
            condition1=false;
            break;
        }
    } 
    
    int flag1=0;
    int loc_of_dot=0;
    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if (t==46)
        {
            flag1=flag1+1;
            loc_of_dot=i;
        }
    }

    int flag2=0;
    int loc_of_E=0;
    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if (t==101)
        {
            flag2=flag2+1;
            loc_of_E=i;
        }
    }

    int flag3=0;
    int loc_of_negative=0;
    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if (t==45)
        {
            flag3=flag3+1;
            loc_of_negative=i;
        }
    }

    int flag4=0;
    int loc_of_positive=0;
    for (int i = 0; i < str.size(); i++)
    {
        int t = (int)str[i];
        if (t==43)
        {
            flag4=flag4+1;
            loc_of_positive=i;
        }
    }
    
    if((flag3==1&&flag4==0&&loc_of_negative==loc_of_E+1) or (flag4==1&&flag3==0&&loc_of_positive==loc_of_E+1) or (flag3==0&&flag4==0))
    {
        if(flag1==0&&flag2==1&&loc_of_E>0&&loc_of_E<str.size()-1)
        {
            condition2=true;
        }
        else if(flag1==1&&flag2==1&&loc_of_dot<loc_of_E-1&&loc_of_E>0&&loc_of_E<str.size()-1)
        {
            condition2=true;
        }
        else
        {
            condition2=false;
        }
    }
    
    return condition1&&condition2;
}

bool isScientific_counting_method(string str)  //check whether the string is given by the scientific counting method
{
    if(isScientific_counting_method_by_E(str)==true or isScientific_counting_method_by_e(str)==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}