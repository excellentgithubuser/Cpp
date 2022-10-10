#include <iostream>
#include <string>
using namespace std;

//check
bool isNum(string str);
bool isDecimal(string str);
bool isScientific_counting_method_by_E(string str);
bool isScientific_counting_method_by_e(string str);
bool isScientific_counting_method(string str);

//normalization
string normalization(string a);

//add
string add_positive_integers(string a,string b);
string add_positive(string a,string b);
string add(string a,string b);

//subtraction
string sub_positive_integers_1(string a,string b);
string sub_positive_integers(string a,string b);
string sub_positive(string a,string b);
string sub(string a,string b);

//mul
string mul_positive_integers(string a,string b);
string mul_positive(string a,string b);
string mul(string a,string b);

//divide
struct Division
{
    string quotient;
    string remainder; 
};
bool compare(string a,string b);
string next(string a);
Division ddiv_positive_integers_slow(string a,string b);
Division ddiv_positive_integers(string a,string b);
string div_positive_integers(string a,string b);
string div_positive(string a,string b);
string round(string a);
string div(string a,string b);

//squarert
string newton_iteration(string a,string a1,string a2,int times);
string square_root(string a,string times);

//power
string power(string a, string b);
string power_compute(string a, string b);