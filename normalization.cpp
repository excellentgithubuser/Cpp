#include <iostream>
#include <string>
#include "f.h"

using namespace std;

string normalization(string a)
{
    string a1="";  //before E/e
    string a2="";  //after E/e
    int lo=0;  //location of E/e
    string result="";  //store the result
    int flag=1;  //store whether the number is zero

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
        if(a1.size()==1)
        {
            if(std::stoi(a1)==0)
            {
                flag=0;
            }   
            result=a1+"E"+a2;
        }
        else
        {
            string temp=a1.insert(1,".");
            int e=std::stoi(a2)+a1.size()-2;
            result=temp+"E"+std::to_string(e);
        }    
    }


    else
    {
        string a1_="";
        int loc_of_dot=0;
        for(int i=0;i<a1.size();i++)
        {
            int t = (int)a1[i];
            if(t==46)
            {
                loc_of_dot=i;
            }
            else
            {
                a1_=a1_+a1[i];
            }
        }
        int e_of_a1_=-(a1.size()-loc_of_dot-1);

        if(a1_.size()==1)
        {
            result=a1_+"E"+std::to_string(e_of_a1_+std::stoi(a2));
        }
        else
        {
            string temp=a1_.insert(1,".");
            int e=e_of_a1_+std::stoi(a2)+a1_.size()-2; //
            result=temp+"E"+std::to_string(e);
        }    
    }

    if(flag==0)
    {
        return "0";
    }
    else{
        return result;
    }

}