#include <iostream>
#include <stdexcept>
#pragma once

class Matrix {
private:
    int rows;
    int cols;
    double **data; 

public:
    Matrix(int n); 
    Matrix(int m, int n, double fill_value = 0.0); 
    Matrix(const Matrix &other); 
    Matrix(Matrix&& other);

    ~Matrix();

    Matrix& operator=(const Matrix &other);
    Matrix& operator=(Matrix&& other);

    Matrix& operator+=(const Matrix &other);
    Matrix& operator-=(const Matrix &other);
    Matrix& operator*=(double n);
    Matrix& operator/=(double n);
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator*(double n) const;
    Matrix operator/(double n) const;

    double get(int i, int j) const;
    void set(int i, int j, double value);
    int get_height() const;
    int get_width() const;

    void negate(); 
    void add_in_place(const Matrix &other);
    Matrix multiply(const Matrix &other) const; 

    void print() const;
};

Matrix operator*(double n, const Matrix& m);
Matrix operator-(const Matrix& m);

Matrix matrix_power(Matrix base, int n);
int fibonacci(int n);
