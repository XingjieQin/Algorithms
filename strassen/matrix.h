#ifndef MATRIX_H
#define MATRIX_H
/*
 *矩阵类模板
 *矩阵的输入、输出、矩阵乘法、加法、减法
 *2018/07/26 17:12
 **/
 #include <vector>
 #include <iostream>
 #include <cmath>
 struct Submatrix{
     int row_start, row_end;
     int col_start, col_end;
 };
template <typename T>
class Matrix{
private:
    const int row = 0, col = 0;
    int row_start, row_end, col_start, col_end;
    std::vector<std::vector<T>> data;
public:
    template <typename U>
    friend std::ostream& operator<<(std::ostream &out, const Matrix<U> &matrix);//重载输出运算符
    template <typename U>
    friend std::istream& operator>>(std::istream &in, Matrix<U> &matrix);//重载输入运算符
    template <typename U>
    friend Matrix<U> operator+(const Matrix<U> &matrix1, const Matrix<U> &matrix2);//重载加法运算符
    template <typename U>
    friend Matrix<U> operator-(const Matrix<U> &matrix1, const Matrix<U> &matrix2);
    template <typename U>
    friend Matrix<U> operator*(Matrix<U> &matrix1, Matrix<U> &matrix2);
    template <typename U>
    friend Matrix<U> matrix_add(const Matrix<U> &matrix, const Submatrix &submatrix1, const Submatrix &submatrix2);
    template <typename U>
    friend Matrix<U> matrix_sub(const Matrix<U> &matrix, const Submatrix &submatrix1, const Submatrix &submatrix2);
    Matrix(const int r, const int c): row(r), col(c), row_start(0), col_start(0), row_end(r), col_end(c) {
        std::vector<T> item(col, 0);
        for(int i = 0; i < row; ++i){
            data.push_back(item);
        }
    }
};
template <typename U>
std::ostream& operator<<(std::ostream &out, const Matrix<U> &matrix){
    for(int i = 0; i < matrix.row; ++i){
        for(int j = 0; j < matrix.col; ++j){
            out << matrix.data[i][j] <<" ";
        }
        out << std::endl;
    }
    return out;
}
template <typename U>
std::istream& operator>>(std::istream &in, Matrix<U> &matrix){
    for(int i = 0; i < matrix.row; ++i){
        for(int j = 0; j < matrix.col; ++j){
            in >> matrix.data[i][j];
        }
    }
    return in;
}
template <typename U>
Matrix<U> operator+(const Matrix<U> &matrix1, const Matrix<U> &matrix2){
    if(matrix1.row != matrix2.row || matrix1.col != matrix2.col){
        throw "Matrix dimention error! Can not add.";
    }
    Matrix<U> sum(matrix1.row, matrix1.col);
    for(int i = 0; i < sum.row; ++i){
        for(int j = 0; j < sum.col; ++j){
            sum.data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
        }
    }
    return sum;
}
template <typename U>
Matrix<U> operator-(const Matrix<U> &matrix1, const Matrix<U> &matrix2){
    if(matrix1.row != matrix2.row || matrix1.col != matrix2.col){
        throw "Matrix dimention error! Can not add.";
    }
    Matrix<U> diff(matrix1.row, matrix1.col);
    for(int i = 0; i < diff.row; ++i){
        for(int j = 0; j < diff.col; ++j){
            diff.data[i][j] = matrix1.data[i][j] - matrix2.data[i][j];
        }
    }
    return diff;
}
template <typename U>
Matrix<U> matrix_add(const Matrix<U> &matrix, const Submatrix &submatrix1, const Submatrix &submatrix2){
    Matrix<U> sum(submatrix1.row_end - submatrix1.row_start, submatrix1.col_end - submatrix1.col_start);
    for(int i = 0; i < sum.row && i + submatrix1.row_start < matrix.row; ++i){
        for(int j = 0; j < sum.col && j + submatrix1.col_start < matrix.col; ++j){
            sum.data[i][j] += matrix.data[i + submatrix1.row_start][j + submatrix1.col_start];
        }
    }
    for(int i = 0; i < sum.row && i + submatrix2.row_start < matrix.row; ++i){
        for(int j = 0; j < sum.col && j + submatrix2.col_start < matrix.col; ++j){
            sum.data[i][j] += matrix.data[i + submatrix2.row_start][j + submatrix2.col_start];
        }
    }
    return sum;
}
template <typename U>
Matrix<U> matrix_sub(const Matrix<U> &matrix, const Submatrix &submatrix1, const Submatrix &submatrix2){
    Matrix<U> diff(submatrix1.row_end - submatrix1.row_start, submatrix1.col_end - submatrix1.col_start);
    for(int i = 0; i < diff.row && i + submatrix1.row_start < matrix.row; ++i){
        for(int j = 0; j < diff.col && j + submatrix1.col_start < matrix.col; ++j){
            diff.data[i][j] += matrix.data[i + submatrix1.row_start][j + submatrix1.col_start];
        }
    }
    for(int i = 0; i < diff.row && i + submatrix2.row_start < matrix.row; ++i){
        for(int j = 0; j < diff.col && j + submatrix2.col_start < matrix.col; ++j){
            diff.data[i][j] -= matrix.data[i + submatrix2.row_start][j + submatrix2.col_start];
        }
    }
    return diff;
}
template <typename U>
Matrix<U> operator*(Matrix<U> &matrix1, Matrix<U> &matrix2){
    if(matrix1.col_end - matrix1.col_start != matrix2.row_end - matrix2.row_start){
        throw "Matrix dimention error! Can not multipy.";
    }
    Matrix<U> mul(matrix1.row_end - matrix1.row_start, matrix2.col_end - matrix2.col_start);
    int max_row = (matrix1.row_end - matrix1.row_start > matrix2.row_end - matrix2.row_end) ? (matrix1.row_end - matrix1.row_start) : (matrix2.row_end - matrix2.row_end);
    int max_col = (matrix1.col_end - matrix1.col_start > matrix2.col_end - matrix2.col_end) ? (matrix1.col_end - matrix1.col_start) : (matrix2.col_end - matrix2.col_end);
    if(!(std::ceil(std::log(max_row) / std::log(2)) == (std::log(max_row) / std::log(2)) && std::ceil(std::log(max_col) / std::log(2)) == std::log(max_col) / std::log(2))){
        matrix1.row_end = matrix2.row_end = (std::ceil(std::log(max_row) / std::log(2)) > (std::ceil(std::log(max_col) / std::log(2)))) ? (std::ceil(std::log(max_row) / std::log(2))) : (std::ceil(std::log(max_col) / std::log(2)));
        matrix1.row_end = matrix2.row_end = std::pow(2, matrix1.row_end);
        matrix1.col_end = matrix2.col_end = matrix1.row_end;
    }
    int m1rs = matrix1.row_start, m1re = matrix1.row_end, m1cs = matrix1.col_start, m1ce = matrix1.col_end;
    int m2rs = matrix2.row_start, m2re = matrix2.row_end, m2cs = matrix2.col_start, m2ce = matrix2.col_end;
    //Matrix<U> mul(matrix1.row_end - matrix1.row_start, matrix2.col_end - matrix2.col_start);
    if(matrix1.row_end == matrix1.row_start + 1 && matrix1.col_start + 1 == matrix1.col_end && matrix2.col_start + 1 == matrix2.col_end){
        if(matrix1.row_start >= matrix1.row || matrix1.col_start >= matrix1.col || matrix2.row_start >= matrix2.row || matrix2.col_start >= matrix2.col)return mul;
        mul.data[0][0] = matrix1.data[matrix1.row_start][matrix1.col_start] * matrix2.data[matrix2.row_start][matrix2.col_start];
    }else{
        int mid = (matrix1.row_end - matrix1.row_start) / 2;
        Matrix<U> s1 = matrix_sub(matrix2, {matrix2.row_start, matrix2.row_start + mid, matrix2.col_start + mid, matrix2.col_end}, {matrix2.row_start + mid, matrix2.row_end, matrix2.col_start + mid, matrix2.col_end});
        Matrix<U> s2 = matrix_add(matrix1, {matrix1.row_start, matrix1.row_start + mid, matrix1.col_start, matrix1.col_start + mid}, {matrix1.row_start, matrix1.row_start + mid, matrix1.col_start + mid, matrix1.col_end});
        Matrix<U> s3 = matrix_add(matrix1, {matrix1.row_start + mid, matrix1.row_end, matrix1.col_start, matrix1.col_start + mid}, {matrix1.row_start + mid, matrix1.row_end, matrix1.col_start + mid, matrix1.col_end});
        Matrix<U> s4 = matrix_sub(matrix2, {matrix2.row_start + mid, matrix2.row_end, matrix2.col_start, matrix2.col_start + mid}, {matrix2.row_start, matrix2.row_start + mid, matrix2.col_start, mid + matrix2.col_start});
        Matrix<U> s5 = matrix_add(matrix1, {matrix1.row_start, matrix1.row_start + mid, matrix1.col_start, matrix1.col_start + mid}, {matrix1.row_start + mid, matrix1.row_end, matrix1.col_start + mid, matrix1.col_end});
        Matrix<U> s6 = matrix_add(matrix2, {matrix2.row_start, matrix2.row_start + mid, matrix2.col_start, matrix2.col_start + mid}, {matrix2.row_start + mid, matrix2.row_end, matrix2.col_start + mid, matrix2.col_end});
        Matrix<U> s7 = matrix_sub(matrix1, {matrix1.row_start, matrix1.row_start + mid, matrix1.col_start + mid, matrix1.col_end}, {matrix1.row_start + mid, matrix1.row_end, matrix1.col_start + mid, matrix1.col_end});
        Matrix<U> s8 = matrix_add(matrix2, {matrix2.row_start + mid, matrix2.row_end, matrix2.col_start, matrix2.col_start + mid}, {matrix2.row_start + mid, matrix2.row_end, matrix2.col_start + mid, matrix2.col_end});
        Matrix<U> s9 = matrix_sub(matrix1, {matrix1.row_start, matrix1.row_start + mid, matrix1.col_start, matrix1.col_start + mid}, {matrix1.row_start + mid, matrix1.row_end, matrix1.col_start, matrix1.col_start + mid});
        Matrix<U> s10 = matrix_add(matrix2, {matrix2.row_start, matrix2.row_start + mid, matrix2.col_start, matrix2.col_start + mid}, {matrix2.row_start, matrix2.row_start + mid, matrix2.col_start + mid, matrix2.col_end});
        matrix1.row_start = m1rs;
        matrix1.col_start = m1cs;
        matrix1.row_end = matrix1.col_end = m1rs + mid;
        Matrix<U> p1 = matrix1 * s1;
        matrix2.row_end = m2re;
        matrix2.col_end = m2ce;
        matrix2.row_start = matrix2.col_start = m2rs + mid;
        Matrix<U> p2 = s2 * matrix2;
        matrix2.row_start = m2rs;
        matrix2.col_start = m2cs;
        matrix2.row_end = matrix2.col_end = m2rs + mid;
        Matrix<U> p3 = s3 * matrix2;
        matrix1.row_end = m1re;
        matrix1.col_end = m1ce;
        matrix1.row_start = matrix1.col_start = m1rs + mid;
        Matrix<U> p4 = matrix1 * s4;
        Matrix<U> p5 = s5 * s6;
        Matrix<U> p6 = s7 * s8;
        Matrix<U> p7 = s9 * s10;
        Matrix<U> c11 = p5 + p4 - p2 + p6;
        Matrix<U> c12 = p1 + p2;
        Matrix<U> c21 = p3 + p4;
        Matrix<U> c22 = p5 + p1 - p3 - p7;
        for(int i = 0; i < c11.row && i < mul.row; ++i){
            for(int j = 0; j < c11.col && j < mul.col; ++j){
                mul.data[i][j] = c11.data[i][j];
            }
        }
        for(int i = 0; i < c12.row && i < mul.row; ++i){
            for(int j = mid; j < mid + c12.col && j < mul.col; ++j){
                mul.data[i][j] = c12.data[i][j - mid];
            }
        }
        for(int i = mid; i < mid + c21.row && i < mul.row; ++i){
            for(int j = 0; j < c21.col && j < mul.col; ++j){
                mul.data[i][j] = c21.data[i - mid][j];
            }
        }
        for(int i = mid; i < mid + c22.row && i < mul.row; ++i){
            for(int j = mid; j < mid + c22.col && j < mul.col; ++j){
                mul.data[i][j] = c22.data[i - mid][j - mid];
            }
        }
        return mul;
    }
}
#endif // MATRIX_H
