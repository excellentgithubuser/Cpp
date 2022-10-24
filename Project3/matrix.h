#include<stdio.h>

struct Matrix
{
    int rows;
    int columns;
    float ** elements;
};
void createMatrix(int r, int c, struct Matrix * a);
void deleteMatrix(struct Matrix * a);
void printMatrix(const struct Matrix * a);
void copyMatrix(struct Matrix *b,const struct Matrix * a);
struct Matrix addMatrix(const struct Matrix * a, const struct Matrix * b);
struct Matrix subtractMatrix(const struct Matrix * a, const struct Matrix * b);
struct Matrix addScalarWithMatrix(const struct Matrix * a, float b);
struct Matrix subtractScalarWithMatrix(const struct Matrix * a, float b);
struct Matrix mulScalarWithMatrix(const struct Matrix * a, float b);
struct Matrix mulMatrix(const struct Matrix * a, const struct Matrix * b);
float matrix_max(const struct Matrix * a);
float matrix_min(const struct Matrix * a);
void transpose(struct Matrix *b,const struct Matrix * a);
float det(struct Matrix a);
struct Matrix inverse(struct Matrix a);