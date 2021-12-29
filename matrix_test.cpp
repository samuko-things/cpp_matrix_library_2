#include <iostream>
#include "matrixLab/matrixLab.h"

#include <stdio.h>
#include <errno.h>

using namespace std;


int main(){
    // Matrix A;
    // float a[2][4]{
    //     {2,3,5,1},
    //     {4,6,0,7},
    // };
    // A.copyArray(a);

    // Matrix B;
    // float b[4][1]{
    //     {3},
    //     {4},
    //     {2},
    //     {9},
    // };
    // B.copyArray(b);
    Matrix A;
    float a[3][3]{
        {1,2,3},
        {4,1,5},
        {6,0,2},
    };
    A.copyArray(a);

    Matrix B;
    float b[3][3]{
        {2,7,4},
        {3,1,6},
        {5,0,8},
    };
    B.copyArray(b);

    Matrix C = mat.dotProd(A, A.inverse());
    C = C.round(0);
    C.print();


    // float detA = A.det();
    // cout << "det of A = " << detA << endl;
  
    // A = A.inverse();
    // A.print();

    // float detB = B.det();
    // cout << "det of B = " << detB << endl;

    B = B.inverse();
    B.print();
    B = B.round(3);
    B.print();

    return 0;
}
