#include <iostream>
#include <stdexcept>

class Matrix {
private:
    int rows;
    int cols;
    double **data; 

public:
    Matrix(int n); 
    Matrix(int m, int n, double fill_value = 0.0); 
    Matrix(const Matrix &other); 

    ~Matrix();

    Matrix& operator=(const Matrix &other);

    double get(int i, int j) const;
    void set(int i, int j, double value);
    int get_height() const;
    int get_width() const;

    void negate(); 
    void add_in_place(const Matrix &other);
    Matrix multiply(const Matrix &other) const; 

    void print() const;
};

Matrix matrix_power(Matrix base, int n);
int fibonacci(int n);
