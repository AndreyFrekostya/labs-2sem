#include "matrix.hpp"

double** fill_data(int m, int n, double fill_value = 0.0) {
    double **arr = new double*[m];

    for (int i = 0; i < m; i++) {
        arr[i] = new double[n];

        for (int j = 0; j < n; j++) arr[i][j] = fill_value;
    }

    return arr;
}


Matrix::Matrix(int n) {
    rows = n;
    cols = n;

    data = fill_data(rows, cols, 0.0);

    for (int i = 0; i < n; i++)
        data[i][i] = 1.0; //единичная матрица
}

Matrix::Matrix(int m, int n, double fill_value) {
    rows = m;
    cols = n;

    data = fill_data(rows, cols, fill_value);
}

Matrix::Matrix(const Matrix &other) {
    rows = other.rows;
    cols = other.cols;

    data = fill_data(rows, cols);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) delete[] data[i];

    delete[] data;
}

//перегрузка оператора = для умножения
Matrix& Matrix::operator=(const Matrix &other) {
    if (this == &other) return *this; 

    for (int i = 0; i < rows; i++) delete[] data[i];

    delete[] data;

    rows = other.rows;
    cols = other.cols;

    data = fill_data(rows, cols);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}

double Matrix::get(int i, int j) const {
    if (i < 0 || i >= rows || j < 0 || j >= cols) throw;
    return data[i][j];
}

void Matrix::set(int i, int j, double value) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) throw;
    data[i][j] = value;
}

int Matrix::get_height() const { return rows; }
int Matrix::get_width() const { return cols; }

void Matrix::negate() {
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] = -data[i][j];
        }
    }
}

void Matrix::add_in_place(const Matrix &other) {
    if (rows != other.rows || cols != other.cols) throw;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] += other.data[i][j];
        }
    }
}

Matrix Matrix::multiply(const Matrix &other) const {
    if (cols != other.rows) throw;

    Matrix result(rows, other.cols, 0.0);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < other.cols; j++){
            for (int k = 0; k < cols; k++){
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }

    return result;
}

void Matrix::print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            std::cout << data[i][j] << " ";
        std::cout << "\n";
    }
}


// Функции для фибоначчи
Matrix matrix_power(Matrix base, int n) {
    Matrix result(base.get_height()); 

    while (n > 0) {
        if (n % 2 == 1) result = result.multiply(base);
        base = base.multiply(base);
        n /= 2;
    }

    return result;
}

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    Matrix fib_mat(2, 2, 0.0);
    fib_mat.set(0, 0, 1);
    fib_mat.set(0, 1, 1);
    fib_mat.set(1, 0, 1);
    fib_mat.set(1, 1, 0);

    Matrix res = matrix_power(fib_mat, n-1);

    return static_cast<int>(res.get(0, 0));
}