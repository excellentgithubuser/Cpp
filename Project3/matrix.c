#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

void createMatrix(int r, int c, struct Matrix * a)
{
    if(a==NULL)
    {
        exit(0);
    }
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
        a->elements = (float **)malloc(sizeof(float *)*r);
        for(int i = 0; i < r; i++)
        {
            a->elements[i] = (float *)malloc(sizeof(float)*c);
        }  

        printf("To create a matrix(%d, %d), please input elements:\n", r, c);
        printf("Note: Please enter elements from left to right and then top to bottom (Press 'Enter' between each two elements).\n");
        for(int i = 0; i < r; i++)
        {
            for(int j = 0; j < c; j++)
            {
                scanf("%f", &a->elements[i][j]);
            }
        }
    }
    printf("\n"); 
}

void deleteMatrix(struct Matrix * a)
{
    if(a==NULL)
    {
        exit(0);
    }
    for(int i = 0; i < a->rows; i++)
    {
        free(a->elements[i]);
        a->elements[i] = NULL;
    }
    free(a->elements);
    a->rows=0;
    a->columns=0;
    a->elements = NULL;
    printf("The matrix was successfully deleted!\n");
    printf("\n");
}

void printMatrix(const struct Matrix * a)
{
    if(a==NULL)
    {
        exit(0);
    }
    if(a->rows<1)
    {
        printf("Sorry! This is not a legal matrix or does not exist!\n");
    }
    else if(a->columns<=10)
    {
        printf("This is a %d by %d matrix!\n",a->rows,a->columns);
        for(int i = 0; i < a->rows; i++)
        {
            for(int j = 0; j < a->columns; j++)
            {
                printf("%f ", a->elements[i][j]);
            }
        printf("\n");
        }
    }
    else
    {
        printf("This is a %d by %d matrix!\n",a->rows,a->columns);
        for(int i = 0; i < a->rows; i++)
        {
            for(int j = 0; j < a->columns; j++)
            {
                printf("%f ", a->elements[i][j]);
            }
        printf(";\n");        //for matrix with large number of columns, use ';' to tell the different rows.
        }
    }
    printf("\n");
}

void copyMatrix(struct Matrix *b,const struct Matrix * a)  //get a new matrix b as the same as a
{
    if(a==NULL)
    {
        exit(0);
    }
    b->rows=a->rows;
    b->columns=a->columns;
    b->elements = (float **)malloc(sizeof(float *)*a->rows);
    for(int i = 0; i < a->rows; i++)
    {
        b->elements[i] = (float *)malloc(sizeof(float)*a->columns);
    } 
    for(int i=0;i<a->rows;i++)
    {
        for(int j=0;j<a->columns;j++)
        {
            b->elements[i][j]=a->elements[i][j];
        }
    }
    printf("The matrix was successfully copied!\n");
    printf("\n");
}

struct Matrix addMatrix(const struct Matrix * a, const struct Matrix * b)
{
    if(a==NULL||b==NULL)
    {
        exit(0);
    }
    if((a->rows!=b->rows)||(a->columns!=b->columns)||(a->columns==0)||(b->columns==0))
    {
        struct Matrix result;
        result.rows=0;
        result.columns=0;
        result.elements=NULL;
        return result;
    }
    else
    {
        struct Matrix result;
        result.rows=a->rows;
        result.columns=a->columns;
        result.elements = (float **)malloc(sizeof(float *)*result.rows);
        for(int i = 0; i < result.rows; i++)
        {
            result.elements[i] = (float *)malloc(sizeof(float)*result.columns);
        }
        for(int i = 0; i < result.rows; i++)
        {
            for(int j = 0; j < result.columns; j++)
            {
                result.elements[i][j] = a->elements[i][j] + b->elements[i][j]; 
            }
        }
        return result;
    }
}

struct Matrix subtractMatrix(const struct Matrix * a, const struct Matrix * b)
{
    if(a==NULL||b==NULL)
    {
        exit(0);
    }
    if((a->rows!=b->rows)||(a->columns!=b->columns)||(a->columns==0)||(b->columns==0))
    {
        struct Matrix result;
        result.rows=0;
        result.columns=0;
        result.elements=NULL;
        return result;
    }
    else
    {
        struct Matrix result;
        result.rows=a->rows;
        result.columns=a->columns;
        result.elements = (float **)malloc(sizeof(float *)*result.rows);
        for(int i = 0; i < result.rows; i++)
        {
            result.elements[i] = (float *)malloc(sizeof(float)*result.columns);
        }
        for(int i = 0; i < result.rows; i++)
        {
            for(int j = 0; j < result.columns; j++)
            {
                result.elements[i][j] = a->elements[i][j] - b->elements[i][j]; 
            }
        }
        return result;
    }
}

struct Matrix addScalarWithMatrix(const struct Matrix * a, float b)
{
    if(a==NULL)
    {
        exit(0);
    }
    if(a->columns==0||a->rows==0)
    {
        struct Matrix result;
        result.rows=0;
        result.columns=0;
        result.elements=NULL;
        return result;
    }
    else
    {
        struct Matrix result;
        result.rows=a->rows;
        result.columns=a->columns;
        result.elements = (float **)malloc(sizeof(float *)*result.rows);
        for(int i = 0; i < result.rows; i++)
        {
            result.elements[i] = (float *)malloc(sizeof(float)*result.columns);
        }
        for(int i = 0; i < result.rows; i++)
        {
            for(int j = 0; j < result.columns; j++)
            {
                result.elements[i][j] = a->elements[i][j] + b; 
            }
        }
        return result;
    }
}

struct Matrix subtractScalarWithMatrix(const struct Matrix * a, float b)
{
    if(a==NULL)
    {
        exit(0);
    }
    if(a->columns==0||a->rows==0)
    {
        struct Matrix result;
        result.rows=0;
        result.columns=0;
        result.elements=NULL;
        return result;
    }
    else
    {
        struct Matrix result;
        result.rows=a->rows;
        result.columns=a->columns;
        result.elements = (float **)malloc(sizeof(float *)*result.rows);
        for(int i = 0; i < result.rows; i++)
        {
            result.elements[i] = (float *)malloc(sizeof(float)*result.columns);
        }
        for(int i = 0; i < result.rows; i++)
        {
            for(int j = 0; j < result.columns; j++)
            {
                result.elements[i][j] = a->elements[i][j] - b; 
            }
        }
        return result;
    }
}

struct Matrix mulScalarWithMatrix(const struct Matrix * a, float b)
{
    if(a==NULL)
    {
        exit(0);
    }
    if(a->columns==0||a->rows==0)
    {
        struct Matrix result;
        result.rows=0;
        result.columns=0;
        result.elements=NULL;
        return result;
    }
    else
    {
        struct Matrix result;
        result.rows=a->rows;
        result.columns=a->columns;
        result.elements = (float **)malloc(sizeof(float *)*result.rows);
        for(int i = 0; i < result.rows; i++)
        {
            result.elements[i] = (float *)malloc(sizeof(float)*result.columns);
        }
        for(int i = 0; i < result.rows; i++)
        {
            for(int j = 0; j < result.columns; j++)
            {
                result.elements[i][j] = a->elements[i][j] * b; 
            }
        }
        return result;
    }
}

struct Matrix mulMatrix(const struct Matrix * a, const struct Matrix * b)
{
    if(a==NULL||b==NULL)
    {
        exit(0);
    }
    if(a->columns == b->rows && a->rows!=0 && b->rows!=0)
    {
        struct Matrix result;
        result.rows = a->rows;
        result.columns = b->columns;
        result.elements = (float **)malloc(sizeof(float *)*result.rows);
        for(int i = 0; i < result.rows; i++)
        {
            result.elements[i] = (float *)malloc(sizeof(float)*result.columns);
        }
        for(int i = 0; i < result.rows; i++)
        {
            for(int j = 0; j < result.columns; j++)
            {
                result.elements[i][j] = 0;
            }
        }
        for(int i = 0; i < result.rows; i++)
        {
            for(int j = 0; j < result.columns; j++)
            {
                for(int k = 0; k < a->columns; k++)
                {
                    result.elements[i][j] = result.elements[i][j] + a->elements[i][k] * b->elements[k][j];
                }
            }
        }
        return result;
    }
    else
    {
        struct Matrix result;
        result.rows=0;
        result.columns=0;
        result.elements=NULL;
        return result;
    }
}

float matrix_max(const struct Matrix * a)
{
    if(a==NULL)
    {
        exit(0);
    }
    if(a->rows==0)
    {
        return 0;
    }
    else
    {
        float max = a->elements[0][0];
        for(int r = 0; r < a->rows; r++)
        {
            for (int c = 0; c < a->columns; c++)
            {
                float val = a->elements[r][c];
                max = ( max > val ? max : val);
            }
        }
        return max;
    }
}

float matrix_min(const struct Matrix * a)
{
    if(a==NULL)
    {
        exit(0);
    }
    if(a->rows==0)
    {
        return 0;
    }
    else
    {
        float min = a->elements[0][0];
        for(int r = 0; r < a->rows; r++)
        {
            for (int c = 0; c < a->columns; c++)
            {
                float val = a->elements[r][c];
                min = ( min < val ? min : val);
            }
        }
        return min;
    }
}

void transpose(struct Matrix *b,const struct Matrix * a)  //transpose a and get b
{
    if(a==NULL||b==NULL)
    {
        exit(0);
    }
    b->rows=a->columns;
    b->columns=a->rows;
    b->elements = (float **)malloc(sizeof(float *)*b->rows);
    for(int i = 0; i < b->rows; i++)
    {
        b->elements[i] = (float *)malloc(sizeof(float)*b->columns);
    } 
    for(int i=0;i<b->rows;i++)
    {
        for(int j=0;j<b->columns;j++)
        {
            b->elements[i][j]=a->elements[j][i];
        }
    }
    printf("\n");
}

float det(struct Matrix a)
{
    if(a.rows==a.columns && a.rows!=0)
    {
        float result;
        if(a.rows==1)
        {
            result = a.elements[0][0];
        }
        else
        {
            result = 0;
            for(int i=0;i<a.rows;i++)
            {
                struct Matrix temp;
                temp.rows = a.rows - 1;
                temp.columns = a.columns - 1;
                temp.elements = (float **)malloc(sizeof(float *)*temp.rows);
                for(int j = 0; j < temp.rows; j++)
                {
                    temp.elements[j] = (float *)malloc(sizeof(float)*temp.columns);
                }
                for(int k=0;k<temp.rows;k++)
                {
                    for(int l=0;l < temp.columns;l++)
                    {
                        if(l<i)
                        {
                            temp.elements[k][l] = a.elements[k+1][l];
                        }
                        else
                        {
                            temp.elements[k][l] = a.elements[k+1][l+1];
                        }
                    }
                } 
                if((1+i+1)%2==0)
                {
                    result = result + a.elements[0][i] * det(temp);
                }
                else
                {
                    result = result - a.elements[0][i] * det(temp);
                }
                //free
                for(int ii = 0; ii < temp.rows; ii++)
                {
                    free(temp.elements[ii]);
                    temp.elements[ii] = NULL;
                }
                free(temp.elements);
                temp.elements = NULL;
            }
        }
    }
    else
    {
        return 0;
    }
}

struct Matrix inverse(struct Matrix a)
{
    if(a.rows==a.columns && a.rows>=2 && det(a)!=0)
    {
        struct Matrix result;
        result.rows = a.rows;
        result.columns = a.columns;
        result.elements = (float **)malloc(sizeof(float *)*result.rows);
        for(int j = 0; j < result.rows; j++)
        {
            result.elements[j] = (float *)malloc(sizeof(float)*result.columns);
        }
        for(int i=0;i<result.rows;i++)
        {
            for(int j=0;j<result.columns;j++)
            {
                struct Matrix temp;
                temp.rows = result.rows - 1;
                temp.columns = result.columns - 1;
                temp.elements = (float **)malloc(sizeof(float *)*temp.rows);
                for(int k = 0; k < temp.rows; k++)
                {
                    temp.elements[k] = (float *)malloc(sizeof(float)*temp.columns);
                }
                for(int ii=0;ii<temp.rows;ii++)
                {
                    for(int jj=0;jj < temp.columns;jj++)
                    {
                        if(ii<i&&jj<j)
                        {
                            temp.elements[ii][jj] = a.elements[ii][jj];
                        }
                        else if(ii<i&&jj>=j)
                        {
                            temp.elements[ii][jj] = a.elements[ii][jj+1];
                        }
                        else if(ii>=i&&jj<j)
                        {
                            temp.elements[ii][jj] = a.elements[ii+1][jj];
                        }
                        else
                        {
                            temp.elements[ii][jj] = a.elements[ii+1][jj+1];
                        }
                    }
                }
                if((i+1+j+1)%2==0)
                {
                    result.elements[j][i] = det(temp)/det(a);
                } 
                else
                {
                    result.elements[j][i] = - det(temp)/det(a);
                }
                //free 
                for(int h = 0; h < temp.rows; h++)
                {
                    free(temp.elements[h]);
                    temp.elements[h] = NULL;
                }
                free(temp.elements);
                temp.elements = NULL;
            }
        }
        return result;
    }
    else if(a.rows==1&&det(a)!=0)
    {
        struct Matrix result;
        result.rows=1;
        result.columns=1;
        result.elements = (float **)malloc(sizeof(float *)*result.rows);
        for(int j = 0; j < result.rows; j++)
        {
            result.elements[j] = (float *)malloc(sizeof(float)*result.columns);
        }
        result.elements[0][0]=1/a.elements[0][0];
        return result;
    }
    else
    {
        struct Matrix result;
        result.rows=0;
        result.columns=0;
        result.elements=NULL;
        return result;
    }
}