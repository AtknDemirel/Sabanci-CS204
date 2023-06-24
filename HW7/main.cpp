//
//  main.cpp
//  atakan.demirel_Demirel_Atakan_7
//
//  Created by Atakan Demirel on 1.01.2023.
//


#include "SparseMatrix.h"

int main(){
    // reads the matrix stored in m1.txt
    SparseMatrix lhs("m3.txt");
    // reads the matrix stored in m2.txt
    SparseMatrix rhs("m4.txt");
    // Stores in the SparseMatrix "result" the result of the following operation
    // lhs * rhs
    SparseMatrix result = lhs.mat_mul(rhs);
    return 0;
}
