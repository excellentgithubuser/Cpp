#include <iostream>
#include "matrix.hpp"
#include <math.h>
#include <string.h>
#include <cstring>

#include <immintrin.h>
#include <omp.h>

using namespace std;

//g++ -fopenmp -mavx2 test2.cpp -o test2
int main()
{
    ROI_of_Matrix<int> r_m1(4,4,1,1,2,2);
    r_m1.random_generation(-10,10);
    cout<<"r_m1: "<<endl;
    r_m1.showROI();

    ROI_of_Matrix<float> r_m2(4,4,0,0,2,1);
    r_m2.random_generation(-10,10);
    cout<<"r_m2: "<<endl;
    r_m2.showROI();

    ROI_of_Matrix<double> r_m3(4,4,0,1,0,2);
    r_m3.random_generation(-10,10);
    cout<<"r_m3: "<<endl;
    r_m3.showROI();

    ROI_of_Matrix<double> r_m4(4,4,2,1,3,1);
    r_m4.random_generation(-10,10);
    cout<<"r_m4: "<<endl;
    r_m4.showROI();

    Matrix<double> m5 = r_m4.turn_to_matrix();
    cout<<"r_m4: "<<endl;
    r_m4.showROI();
    cout<<"r_m4.turn_to_matrix() = "<<m5<<endl;  //case 3 of 'turn_to_matrix'

    ROI_of_Matrix<double> r_m6(4,4);
    r_m6.random_generation(-10,10);
    Matrix<double> m7 = r_m6.turn_to_matrix();
    cout<<"r_m6: "<<endl;
    r_m6.showROI();
    cout<<"r_m6.turn_to_matrix() = "<<m7<<endl;  //case 2 of 'turn_to_matrix'

    ROI_of_Matrix<double> r_m8;
    Matrix<double> m9 = r_m8.turn_to_matrix();
    cout<<"r_m8: "<<endl;
    r_m8.showROI();
    cout<<"r_m8.turn_to_matrix() = "<<m9<<endl;  //case 1 of 'turn_to_matrix'

    ROI_of_Matrix<float> r_m10;
    Matrix<float> m11(4,4,1);
    m11.random_generation(-10,10);
    r_m10.turned_from_matrix(m11,1,1,2,2);
    cout<<"Matrix m11 is: "<<m11<<endl;
    cout<<"ROI_Matirx turned from m11 with ROI from (1,1) to (2,2) is: "<<endl;
    r_m10.showROI();
    cout<<"To show that m11 and r_m10 shared a same pointer elements, please see their getcount():"<<endl;
    cout<<"r_m10.getcount() = "<<r_m10.getCount()<<endl;
    cout<<"m11.getcount() = "<<m11.getCount()<<endl;
    

}