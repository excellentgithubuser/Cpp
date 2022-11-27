#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "head.h"
#include <immintrin.h> 
#include <avx2intrin.h>
#include <omp.h>

Matrix * createMatrix(size_t r, size_t c)
{
    Matrix * a = (Matrix *)malloc(sizeof(Matrix));
    if(r<1||c<1)
    {
        a->rows=0;
        a->columns=0;
        a->elements=NULL;
    }
    else
    {
        a->rows=r;
        a->columns=c;
        // a->elements = (float *)malloc(r*c*sizeof(float));
        a->elements = (aligned_alloc(256, r*c*sizeof(float)));
        memset(a->elements, 0.0f, r*c* sizeof(float));
        //printf("Created successfully!\n\n");
    }
    return a;
}

void setValue(Matrix *a, float * t, size_t len_of_t)  
{
    if(a==NULL)
    {
        return;
    }
    if(a->elements==NULL)
    {
        return;
    }
    if(t==NULL)
    {
        return;
    } 
    if(len_of_t < a->columns * a->rows)
    {
        printf("Failed to set the value of the matrix since too few elements were provided!\n");
    }
    else if(len_of_t == a->columns * a->rows)
    {
        for(size_t i = 0 ; i<a->rows ; i++)
        {
            for(size_t j = 0 ; j<a->columns ; j++)
            {
                a->elements[i*a->columns + j] = t[i*a->columns + j];
            }
        }
        //printf("Succeeded to setting the values!\n");
    }
    else
    {
        for(size_t i = 0 ; i<a->rows ; i++)
        {
            for(size_t j = 0 ; j<a->columns ; j++)
            {
                a->elements[i*a->columns + j] = t[i*a->columns + j];
            }
        }
        printf("Succeeded to setting the values! But some data was not used due to the excessive amount of data provided.\n");
    }
    printf("\n");
}

void deleteMatrix(Matrix ** a)
{
    if(a==NULL)
    {
        return;
    }
    if(*a==NULL)
    {
        return;
    }
    if((*a)->elements==NULL)
    {
        return;
    }
    free((*a)->elements);
    (*a)->elements = NULL;
    free(*a);
    (*a) = NULL;
    // printf("Deleted successfully!\n");
    // printf("\n");
}

void printMatrix(const Matrix * a)
{
    if(a==NULL)
    {
        printf("This is an empty matrix!\n\n");
        return;
    }
    if(a->elements==NULL)
    {
        printf("This is an empty matrix!\n\n");
        return;
    }
    if(a->rows<1)
    {
        printf("Sorry! This is not a legal matrix or does not exist!\n");
    }
    else if(a->columns<=10)
    {
        printf("This is a %ld by %ld matrix!\n",a->rows,a->columns);
        for(int i = 0; i < a->rows; i++)
        {
            for(int j = 0; j < a->columns; j++)
            {
                printf("%f ", a->elements[a->columns*i+j]);
            }
        printf("\n");
        }
    }
    else
    {
        printf("This is a %ld by %ld matrix!\n",a->rows,a->columns);
        for(size_t i = 0; i < a->rows; i++)
        {
            for(size_t j = 0; j < a->columns; j++)
            {
                printf("%f ", a->elements[a->columns*i+j]);
            }
        printf(";\n");        //for matrix with large number of columns, use ';' to tell the different rows.
        }
    }
    printf("\n");
}


bool matmul_plain(const Matrix * a, const Matrix * b, Matrix * result)
{
    if(a==NULL||b==NULL||result==NULL)
    {
        return false;
    }
    if(a->elements==NULL||b->elements==NULL)
    {
        return false;
    }
    else if(a->columns == b->rows && a->rows == result->rows && b->columns == result->columns && a->rows!=0 && b->rows!=0)
    {
        for(size_t i = 0; i < result->rows; i++)
        {
            for(size_t j = 0; j < result->columns; j++)
            {
                for(size_t k = 0; k < a->columns; k++)
                {
                    result->elements[i*result->columns+j] = result->elements[i*result->columns+j] + a->elements[i*a->columns+k] * b->elements[k*b->columns+j];
                }
            }
        }
        return true;
    }
    else
    {
        printf("The dimensions of matrices are not consistent!\n");
        return false;
    }
}


bool matmul_improved(const Matrix * a, const Matrix * b,Matrix * result) 
{
    if(a==NULL||b==NULL||result==NULL)
    {
        return false;
    }
    if(a->elements==NULL||b->elements==NULL)
    {
        return false;
    }
    if(a->columns == b->rows && a->rows == result->rows && b->columns == result->columns && a->rows!=0 && b->rows!=0)
    {
        Matrix *b_tran = transpose(b);

        size_t mat_size = (a->rows) * (b->columns);
        if (result->rows * result->columns != mat_size)
        {
            free(result->elements);
            result->elements = (aligned_alloc(256, mat_size * sizeof(float)));
        }
        result->rows = a->rows;
        result->columns = b->columns;

        #pragma omp parallel for
        for (size_t i = 0; i < a->rows; i++)
        {
            for (size_t j = 0; j < b->columns; j++)
            {
                size_t k;

                for (k = 0; k < (a->columns / 8) * 8; k += 8)
                {
                    float sum[8] __attribute__((aligned(256))) = {0};
                    __m256 aa = _mm256_loadu_ps(a->elements + (i * (a->columns) + k));
                    __m256 bb = _mm256_loadu_ps(b_tran->elements + (j * (b_tran->columns) + k));
                    __m256 cc = _mm256_mul_ps(aa, bb);

                    _mm256_storeu_ps(sum, cc);
                    result->elements[i * (result->columns) + j] += (sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7]);
                }
                
                for(k = (a->columns / 8) * 8; k < a->columns; k++)
                {
                    result->elements[i * (result->columns) + j] += a->elements[i*(a->columns)+k] * b->elements[k*(b->columns)+j];
                }

            }
        }              

        deleteMatrix(&b_tran);
        return true;
    }
    else
    {
        printf("The dimensions of matrices are not consistent!\n");
        return false;
    }
}


Matrix *randMat(size_t rows, size_t cols, float min, float max)
{
    Matrix *result = createMatrix(rows, cols);
    for (size_t i = 0; i < rows * cols; i++)
    {
        result->elements[i] = min + 1.0 * (rand() % RAND_MAX) / RAND_MAX * (max - min);
    }
    return result;
}


Matrix *transpose(const Matrix *mat)
{
    if (mat == NULL)
    {
        return NULL;
    }
    if (mat->elements == NULL)
    {
        return NULL;
    }
    Matrix *result = createMatrix(mat->columns, mat->rows);
    for (size_t i = 0; i < mat->rows; i++)
    {
        for (size_t j = 0; j < mat->columns; j++)
        {
            result->elements[j * mat->rows + i] = mat->elements[i * (mat->columns) + j];
        }
    }
    return result;
}