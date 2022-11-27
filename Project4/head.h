#ifndef _HEAD_H
#define _HEAD_H

#include<stdio.h>
#include<stdbool.h>
#pragma once

typedef struct Matrix
{
    size_t rows;
    size_t columns;
    float * elements;
}Matrix;


Matrix * createMatrix(size_t r, size_t c);
void setValue(Matrix *a, float *t, size_t len_of_t);
void deleteMatrix(Matrix ** a);
void printMatrix(const Matrix * a);
bool matmul_plain(const Matrix * a, const Matrix * b, Matrix * result);
bool matmul_improved(const Matrix * a, const Matrix * b, Matrix * result);
Matrix *randMat(size_t rows, size_t cols, float min, float max);
Matrix *transpose(const Matrix *mat);

#endif