#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "matrix.h"

int main()
{
    struct Matrix a;
    createMatrix(2,3,&a);  //create a matrix

    //Another mmethod to create a matrix
    //struct Matrix * a1 = (struct Matrix *)malloc(sizeof(struct Matrix *));
    //create_matrix(2,3,a1);  

    struct Matrix b; 
    copyMatrix(&b,&a);  //copy matrix a to b
    printMatrix(&b);
    
    struct Matrix c;
    createMatrix(2,3,&c);

    struct Matrix d = addMatrix(&b,&c);  //add matrices
    printMatrix(&d);  

    struct Matrix e = subtractMatrix(&b,&c);  //subtract matrices
    printMatrix(&e);  

    struct Matrix f = addScalarWithMatrix(&b,2.222f);  //add a scalar to a matrix
    printMatrix(&f);  

    struct Matrix g = subtractScalarWithMatrix(&b,-2.222f);  //subtract a scalar to a matrix
    printMatrix(&g);

    struct Matrix h = mulScalarWithMatrix(&b,1.1f);  //mul a scalar to a matrix
    printMatrix(&h);

    struct Matrix i;
    createMatrix(3,2,&i);
    struct Matrix j = mulMatrix(&b,&i);  //mul two matrices
    printMatrix(&j);

    printf("%f\n",matrix_max(&b));
    printf("%f\n",matrix_min(&b));

    struct Matrix k;
    transpose(&k,&b);
    printMatrix(&k);

    struct Matrix l;
    createMatrix(4,4,&l);
    printf("%f\n\n",det(l));

    struct Matrix m = inverse(l);
    printMatrix(&m);


    deleteMatrix(&a);  //delete a matrix
    deleteMatrix(&b);  
    deleteMatrix(&c);
    deleteMatrix(&d);
    deleteMatrix(&e);
    deleteMatrix(&f);
    deleteMatrix(&g);
    deleteMatrix(&h);
    deleteMatrix(&i);
    deleteMatrix(&j);
    deleteMatrix(&k);
    deleteMatrix(&l);
    deleteMatrix(&m);

    printMatrix(&a);  //verify whther the matrices were deleted
    printMatrix(&b);
    printMatrix(&c);
    printMatrix(&d);
    printMatrix(&e);
    printMatrix(&f);
    printMatrix(&g);
    printMatrix(&h);
    printMatrix(&i);
    printMatrix(&j);
    printMatrix(&k);
    printMatrix(&l);
    printMatrix(&m);

}