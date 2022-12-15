#include <iostream>
#include "matrix.hpp"
#include <math.h>
#include <string.h>
#include <cstring>

#include <immintrin.h>
#include <omp.h>

using namespace std;

//g++ -fopenmp -mavx2 test1.cpp -o test1
int main()
{
    Matrix<float> m1;  //testing for constructor 1
    Matrix<float> m2(3,3);  //testing for constructor 2
    Matrix<float> m3(3,3,2);  //testing for constructor 3

    float * m2_data = new float[9]{-1.0f,2.0f,-3.0f,4.0f,0.0f,1.0f,2.0f,-3.0f,-4.0f};
    m1.setData(m2_data,9);  //testing for function setData()
    m2.setData(m2_data,9);  //testing for function setData()

    float * m3_data = new float[18]{-1.0f,2.0f,-3.0f,4.0f,0.0f,1.0f,2.0f,-3.0f,-4.0f,1.0f,2.0f,-3.0f,-4.0f,1.1f,-1.0f,2.0f,-3.0f,4.0f};
    m3.setData(m3_data,18);  //testing for function setData()

    Matrix<float> m4 = m3;  //testing for copy constructor
    Matrix<float> m5;  
    m5 = m3;  //testing for overloading operator =
    Matrix<float> m6(1,11,1);
    m6 = m3;  //testing for overloading operator =

    cout<< "m1 : " << m1 << endl;  //testing for overloading operator <<
    cout<< "m2 : " << m2 << endl;  //testing for overloading operator <<
    cout<< "m3 : " << m3 << endl;  //testing for overloading operator <<
    cout<< "m4 : " << m4 << endl;  //testing for overloading operator <<
    cout<< "m5 : " << m5 << endl;  //testing for overloading operator <<
    cout<< "m6 : " << m6 << endl;  //testing for overloading operator <<
    cout<<"m1.getCount() = "<<m1.getCount()<<endl;  //testing for function getCount() and member count 
    cout<<"m2.getCount() = "<<m2.getCount()<<endl;  //testing for function getCount() and member count
    cout<<"m3.getCount() = "<<m3.getCount()<<endl;  //testing for function getCount() and member count
    cout<<"m4.getCount() = "<<m4.getCount()<<endl;  //testing for function getCount() and member count
    cout<<"m5.getCount() = "<<m5.getCount()<<endl;  //testing for function getCount() and member count
    cout<<"m6.getCount() = "<<m6.getCount()<<endl;  //testing for function getCount() and member count

    m4.change_one_entry(1,1,1,0.1);  //testing for function change_one_entry()

    cout<< "m1 : " << m1 << endl;  //testing for overloading operator <<
    cout<< "m2 : " << m2 << endl;  //testing for overloading operator <<
    cout<< "m3 : " << m3 << endl;  //testing for overloading operator <<
    cout<< "m4 : " << m4 << endl;  //testing for overloading operator <<
    cout<< "m5 : " << m5 << endl;  //testing for overloading operator <<
    cout<< "m6 : " << m6 << endl;  //testing for overloading operator <<
    cout<<"m1.getCount() = "<<m1.getCount()<<endl;  //testing for function getCount() and member count 
    cout<<"m2.getCount() = "<<m2.getCount()<<endl;  //testing for function getCount() and member count
    cout<<"m3.getCount() = "<<m3.getCount()<<endl;  //testing for function getCount() and member count
    cout<<"m4.getCount() = "<<m4.getCount()<<endl;  //testing for function getCount() and member count
    cout<<"m5.getCount() = "<<m5.getCount()<<endl;  //testing for function getCount() and member count
    cout<<"m6.getCount() = "<<m6.getCount()<<endl;  //testing for function getCount() and member count

    cin>>m2;  //testing for overloading operator >>
    cin>>m1;  //testing for overloading operator >>
    cout<<m1;  //testing for overloading operator <<

    Matrix<int> m7(2,2,2);
    Matrix<float> m8(4,4,2);
    Matrix<double> m9(2,2,2);
    m7.random_generation(-10,10);  //testing for function random_generation()
    m8.random_generation(-10.0f,10.0f);  //testing for function random_generation()
    m9.random_generation(-10.0,10.0);  //testing for function random_generation()
    cout<<"m7 :"<<m7<<endl<<"m8 :"<<m8<<endl<<"m9 :"<<m9<<endl;

    Matrix<float> m10(4,4,2);
    m10.random_generation(-1.0f,1.0f);
    Matrix<float> m11;
    m11 = m8 + m10;  //equivalently, "Matrix<float> k = h + j;" is also acceptable
    cout<<"m8 : "<<m8<<endl;  
    cout<<"m10 : "<<m10<<endl;
    cout<<"m11 = m8 + m10 : "<<m11<<endl;  //testing for overloading operator +
    Matrix<float> m12 = m8 - m10;
    cout<<"m12 = m8 - m10 : "<<m12<<endl;  //testing for overloading operator -
    Matrix<float> m13 = m8 * m10;
    cout<<"m13 = m8 * m10 : "<<m13<<endl;  //testing for overloading operator *
    bool b1 = m8 == m10;
    cout<<"b1 = (m8 == m10) : "<<b1<<endl;  //testing for overloading operator ==
    bool b2 = m8 == m8;
    cout<<"b2 = (m8 == m8) : "<<b2<<endl;  //testing for overloading operator ==

    Matrix<double> m14 = m10.inverse();
    cout<<"the channel-wise inversr of matrix m10 : "<<m14<<endl;  //testing for function inverse


    delete []m2_data;
    delete []m3_data;
}