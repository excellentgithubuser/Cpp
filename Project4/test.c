#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "head.h"
#include <time.h>
#include <omp.h>
#include <immintrin.h> 
#include "cblas.h"

//gcc -mavx2 -fopenmp source.c test.c -o test -I /opt/OpenBLAS/include/ -L /opt/OpenBLAS/lib/ -lopenblas -lpthread
//gcc -mavx2 -fopenmp source.c test.c -O3 -I /opt/OpenBLAS/include/ -L /opt/OpenBLAS/lib/ -lopenblas -lpthread
int main()
{
    float value4 [16*16] = {0.0f};
    for(int i=0;i<16*16;i++)
    {
        value4[i] = 2.1f*i-20.0f;
    }
    float value5 [16*16] = {0.0f};
    for(int i=0;i<16*16;i++)
    {
        value5[i] = i-30.0f;
    }

    Matrix * a16 = createMatrix(16,16);
    setValue(a16,value4,sizeof(value4)/sizeof(value4[0]));
    Matrix * b16 = createMatrix(16,16);
    setValue(b16,value5,sizeof(value5)/sizeof(value5[0]));

    Matrix * t16 = createMatrix(16,16);
    bool boolb16 = matmul_plain(a16,b16,t16);  
    deleteMatrix(&t16);
    Matrix * tt16 = createMatrix(16,16);
    bool boolbb16 = matmul_improved(a16,b16,tt16);  
    deleteMatrix(&tt16);



    double dtime;

    Matrix * c16_1 = createMatrix(16,16);
    dtime = omp_get_wtime();
    bool b16_1 = matmul_plain(a16,b16,c16_1);
    dtime = omp_get_wtime() - dtime;
    printf("normal time of multiplication of 16 by 16 matrices = %f\n\n",dtime);
    
    Matrix * c16_2 = createMatrix(16,16);
    dtime = omp_get_wtime();
    bool b16_2 = matmul_improved(a16,b16,c16_2);
    dtime = omp_get_wtime() - dtime;
    printf("improved time of multiplication of 16 by 16 matrices = %f\n\n",dtime);

    deleteMatrix(&a16);
    deleteMatrix(&b16);
    deleteMatrix(&c16_1);
    deleteMatrix(&c16_2);
    

    float value6[128*128];
    for(int i=0;i<128*128;i++)
    {
        value6[i] = 2.1f*i-200.0f;
    }
    float value7 [128*128];
    for(int i=0;i<128*128;i++)
    {
        value7[i] = i-300.0f;
    }

    Matrix * a128 = createMatrix(128,128);
    setValue(a128,value6,sizeof(value6)/sizeof(value6[0]));
    Matrix * b128 = createMatrix(128,128);
    setValue(b128,value7,sizeof(value7)/sizeof(value7[0]));

    Matrix * c128_1 = createMatrix(128,128);
    dtime = omp_get_wtime();
    bool b128_1 = matmul_plain(a128,b128,c128_1);
    dtime = omp_get_wtime() - dtime;
    printf("normal time of multiplication of 128 by 128 matrices = %f\n\n",dtime);

    Matrix * c128_2 = createMatrix(128,128);
    dtime = omp_get_wtime();
    bool b128_2 = matmul_improved(a128,b128,c128_2);
    dtime = omp_get_wtime() - dtime;
    printf("improved time of multiplication of 128 by 128 matrices = %f\n\n",dtime);

    deleteMatrix(&a128);
    deleteMatrix(&b128);
    deleteMatrix(&c128_1);
    deleteMatrix(&c128_2);



    Matrix * a1k = randMat(1000,1000,0,1);
    Matrix * b1k = randMat(1000,1000,0,1);

    Matrix * c1k_1 = createMatrix(1000,1000);
    dtime = omp_get_wtime();
    bool b1k_1 = matmul_plain(a1k,b1k,c1k_1);
    dtime = omp_get_wtime() - dtime;
    printf("normal time of multiplication of 1k by 1k matrices = %f\n\n",dtime);

    Matrix * c1k_2 = createMatrix(1000,1000);
    dtime = omp_get_wtime();
    bool b1k_2 = matmul_improved(a1k,b1k,c1k_2);
    dtime = omp_get_wtime() - dtime;
    printf("improved time of multiplication of 1k by 1k matrices = %f\n\n",dtime);

    deleteMatrix(&a1k);
    deleteMatrix(&b1k);
    deleteMatrix(&c1k_1);
    deleteMatrix(&c1k_2);


    Matrix * a2k = randMat(2000,2000,0,1);
    Matrix * b2k = randMat(2000,2000,0,1);

    Matrix * c2k_1 = createMatrix(2000,2000);
    dtime = omp_get_wtime();
    bool b2k_1 = matmul_plain(a2k,b2k,c2k_1);
    dtime = omp_get_wtime() - dtime;
    printf("normal time of multiplication of 2k by 2k matrices = %f\n\n",dtime);

    Matrix * c2k_2 = createMatrix(2000,2000);
    dtime = omp_get_wtime();
    bool b2k_2 = matmul_improved(a2k,b2k,c2k_2);
    dtime = omp_get_wtime() - dtime;
    printf("improved time of multiplication of 2k by 2k matrices = %f\n\n",dtime);

    deleteMatrix(&a2k);
    deleteMatrix(&b2k);
    deleteMatrix(&c2k_1);
    deleteMatrix(&c2k_2);


    Matrix * a4k = randMat(4000,4000,0,1);
    Matrix * b4k = randMat(4000,4000,0,1);

    Matrix * c4k_1 = createMatrix(4000,4000);
    dtime = omp_get_wtime();
    bool b4k_1 = matmul_plain(a4k,b4k,c4k_1);
    dtime = omp_get_wtime() - dtime;
    printf("normal time of multiplication of 4k by 4k matrices = %f\n\n",dtime);

    Matrix * c4k_2 = createMatrix(4000,4000);
    dtime = omp_get_wtime();
    bool b4k_2 = matmul_improved(a4k,b4k,c4k_2);
    dtime = omp_get_wtime() - dtime;
    printf("improved time of multiplication of 4k by 4k matrices = %f\n\n",dtime);

    deleteMatrix(&a4k);
    deleteMatrix(&b4k);
    deleteMatrix(&c4k_1);
    deleteMatrix(&c4k_2);


    Matrix * a8k = randMat(8000,8000,0,1);
    Matrix * b8k = randMat(8000,8000,0,1);

    // Matrix * c8k_1 = createMatrix(8000,8000);
    // dtime = omp_get_wtime();
    // bool b8k_1 = matmul_plain(a8k,b8k,c8k_1);
    // dtime = omp_get_wtime() - dtime;
    // printf("normal time of multiplication of 8k by 8k matrices = %f\n\n",dtime);

    Matrix * c8k_2 = createMatrix(8000,8000);
    dtime = omp_get_wtime();
    bool b8k_2 = matmul_improved(a8k,b8k,c8k_2);
    dtime = omp_get_wtime() - dtime;
    printf("improved time of multiplication of 8k by 8k matrices = %f\n\n",dtime);

    deleteMatrix(&a8k);
    deleteMatrix(&b8k);
    //deleteMatrix(&c8k_1);
    deleteMatrix(&c8k_2);


    //test for my method with OpenBLAS
    int i, j; 
    float min = -1;
    float max = 1;
    float a[11*13]={0.0f}; //11*13
    float b[13*12]={0.0f}; //13*12
    for(size_t temp = 0; temp < 11 * 13; temp++)
    {
        a[temp] = min + 1.0 * (rand() % RAND_MAX) / RAND_MAX * (max - min);
    }
    for(size_t temp = 0; temp < 13 * 12; temp++)
    {
        b[temp] = min + 1.0 * (rand() % RAND_MAX) / RAND_MAX * (max - min);
    }
    float c[11*12]={0.0f};
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 11, 12, 13, 1.0, a, 13, b, 12, 0.0, c, 12);  //c = a * b
    printf("The result given by OpenBLAS is: \n");
    for(i = 0; i < 11; ++i)
    {
        for(j = 0; j < 12; ++j)
        {
            printf("%f ", c[i*12+j]);
        }
        printf("\n");
    }
    printf("\n");
    Matrix * my_a = createMatrix(11,13);
    setValue(my_a, a, 143);
    Matrix * my_b = createMatrix(13,12);
    setValue(my_b, b, 156);
    Matrix * my_c_1 = createMatrix(11,12);
    bool b_my_1 = matmul_plain(my_a,my_b,my_c_1);
    Matrix * my_c_2 = createMatrix(11,12);
    bool b_my_2 = matmul_improved(my_a,my_b,my_c_2);
    printf("The result given by my first method is: \n");
    printMatrix(my_c_1);
    printf("The result given by my second method is: \n");
    printMatrix(my_c_2);
    deleteMatrix(&my_c_1);
    deleteMatrix(&my_c_2);
    

    Matrix * a_500 = randMat(500,500,-1,1);
    Matrix * b_500 = randMat(500,500,-1,1);

    //double dtime;

    Matrix * c_500_1 = createMatrix(500,500);
    dtime = omp_get_wtime();
    bool b_500_1 = matmul_plain(a_500,b_500,c_500_1);
    dtime = omp_get_wtime() - dtime;
    printf("normal time of multiplication of 500 by 500 matrices = %f\n\n",dtime);

    Matrix * c_500_2 = createMatrix(500,500);
    dtime = omp_get_wtime();
    bool b_500_2 = matmul_improved(a_500,b_500,c_500_2);
    dtime = omp_get_wtime() - dtime;
    printf("improved time of multiplication of 500 by 500 matrices = %f\n\n",dtime);

    float a_500_5[500*500];
    float b_500_5[500*500];
    float c_500_5[500*500];
    for(size_t i = 0; i < 500*500; i++)
    {
        a_500_5[i] = a_500->elements[i];
        b_500_5[i] = b_500->elements[i];
        c_500_5[i] = 0;
    }
    dtime = omp_get_wtime();
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 500, 500, 500, 1.0, a_500_5, 500, b_500_5, 500, 0.0, c_500_5, 500);
    dtime = omp_get_wtime() - dtime;
    printf("time of multiplication using OpenBLAS of 500 by 500 matrices = %f\n\n",dtime);

    deleteMatrix(&a_500);
    deleteMatrix(&b_500);
    deleteMatrix(&c_500_1);
    deleteMatrix(&c_500_2);






}

