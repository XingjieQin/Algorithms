/*
 *Strassen算法
 *2018/07/26 17:12
 **/
#include <iostream>
#include "matrix.h"
using namespace std;
int main(){
    Matrix<int> matrix1(2, 2), matrix2(2, 2);
    cin >> matrix1 >> matrix2;
    cout << matrix1 << matrix2;
    try{
        Matrix<int> matrix_product = matrix1 * matrix2;
        cout << matrix_product;
    }catch(const char *e){
        cout << e << endl;
    }
    return 0;
}
