#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cfloat>
#include <cmath>
#include <cstring>
#include "matrix.h"

using std::cout;
using std::endl;
using std::ios;
using std::setprecision;

bool add(const Matrix a, const Matrix b, Matrix &c)
{
    c.data = NULL;

    if (!check(a) || !check(b))
        return false;
    if (a.rows != b.rows || a.cols != b.cols)
        return false;

    int n = a.rows * a.cols;
    c.rows = a.rows;    c.cols = a.cols;
    c.data = new double[c.rows * c.cols];
    for (int i = 0; i < n; ++i)
    {
        c.data[i] = a.data[i] + b.data[i];
    }
    return true;
}

bool sub(const Matrix a, const Matrix b, Matrix &c)
{
    c.data = NULL;

    if (!check(a) || !check(b))
        return false;
    if (a.rows != b.rows || a.cols != b.cols)
        return false;

    int n = a.rows * a.cols;
    c.rows = a.rows;    c.cols = a.cols;
    c.data = new double[c.rows * c.cols];

    for (int i = 0; i < n; ++i)
    {
        c.data[i] = a.data[i] - b.data[i];
    }
    return true;
}

bool mul(const Matrix a, const Matrix b, Matrix &c)
{
    c.data = NULL;

    if (!check(a) || !check(b))
        return false;
    if (a.cols != b.rows)
        return false;

    c.rows = a.rows;
    c.cols = b.cols;
    c.data = new double[c.rows * c.cols];

    for (int i = 0; i < a.rows; ++i)
    {
        for (int j = 0; j < b.cols; ++j)
        {
            double temp = 0.0f;
            for (int t = 0; t < a.cols; ++t)
                temp += a.data[i * a.cols + t] * b.data[t * b.cols + j];
            c.data[i * c.cols + j] = temp;
        }
    }
    return true;
}

bool mul(const Matrix a, const double b, Matrix &c)
{
    c.data = NULL;

    if (!check(a))
        return false;

    c.rows = a.rows;
    c.cols = a.cols;
    c.data = new double[c.rows * c.cols];
    
    int n = a.rows * a.cols;
    for (int i = 0; i < n; ++i)
    {
        c.data[i] = a.data[i] * b;
    }
    return true;
}

bool log(const Matrix a, Matrix &b)
{
    b.data = NULL;
    if (!check(a))
        return false;
    b.rows = a.rows;    b.cols = a.cols;
    b.data = new double[b.rows * b.cols];
    
    for (unsigned i = 0; i < a.rows * a.cols; ++i)
        b.data[i] = log(a.data[i]);    

    return true;
}

bool pow(const Matrix a, const Matrix b, Matrix &c)
{
    c.data = NULL;

    // check validation of matrix
    if (!check(a) || !check(b))
        return false;

    if (a.rows != b.rows || a.cols != b.cols)
        return false;

    c.rows = a.rows;    c.cols = a.cols;
    c.data = new double[c.rows * c.cols];

    for (unsigned i = 0; i < a.rows * a.cols; ++i)
        c.data[i] = pow(a.data[i], b.data[i]);

    return true;
}

bool transpose(const Matrix a, Matrix &b)
{
    b.data = NULL;

    if (!check(a))
        return false;

    b.rows = a.cols;
    b.cols = a.rows;
    b.data = new double[b.rows * b.cols];
    
    for (int i = 0; i < a.rows; ++i)
    {
        for (int j = 0; j < a.cols; ++j)
        {
            b.data[j * b.cols + i] = a.data[i * a.cols + j];
        }
    }
    return true;
}

void zeros(Matrix &a)
{
    a.data = new double[a.rows * a.cols];
    for (unsigned i = 0; i < a.rows * a.cols; ++i)
        a.data[i] = 0.0f;
}

void ones(Matrix &a)
{
    a.data = new double[a.rows * a.cols];
    for (unsigned i = 0; i < a.rows * a.cols; ++i)
        a.data[i] = 1.0f;
}

void rand(Matrix &a)
{
    srand((unsigned) time(NULL));
    a.data = new double[a.rows * a.cols];
    for (unsigned i = 0; i < a.rows * a.cols; ++i)
        a.data[i] = (double)rand() / (double)RAND_MAX;
}

void print(const Matrix a)
{
    if (!check(a))
    {
        cout << "Invalid matrix!" << endl;
//        exit(EXIT_FAILURE);
        return;
    }
    cout.setf(ios::fixed);
    cout << "\n";
    for (unsigned i = 0; i < a.rows; ++i)
    {
        for (unsigned j = 0; j < a.cols; ++j)
            cout << setprecision(3) << a.data[i * a.cols + j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

bool check(const Matrix &m)
{
    // check matrix row and column
    if (m.rows == 0 || m.cols == 0)
    {
        cout << "Row or column of matrix can not be zero!" << endl;
        return false;
    }
    if (!m.data)
    {
        cout << "Matrix data error!" << endl;
        return false;
    }
    return true;
}
