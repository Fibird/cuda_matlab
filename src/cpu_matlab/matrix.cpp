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
    {
        if (a.data[i] <= DBL_EPSILON)
        {
            cout << "Log Error: element should not be zero or negative!" << endl;
            return false;
        }
        b.data[i] = log(a.data[i]);    
    }

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

// using LUP-decomposition method
bool det(const Matrix a, double &d)
{
    // validation check
    if (!check(a))
        return false;
    // check if a is square matrix
    if (a.rows != a.cols)
    {
        cout << "Matrix a is not square matrix!" << endl;
        return false;
    }

    unsigned rows = a.rows;
    unsigned cols = a.cols;
    double *A = new double[rows * cols];
    memcpy(A, a.data, sizeof(double) * rows * cols);

    // row vector for record line-swap
    // also called permutation matrix
    unsigned *p = new unsigned[rows];
    for (unsigned i = 0; i < rows; ++i)
        p[i] = i;

    unsigned count = 0; // record the times of swap-line
    
    // LUP decomposition method
    for (unsigned i = 0; i < cols; ++i)
    {
        // select leading row for reduction
        unsigned t = i;
        for (unsigned x = i + 1; x < rows; ++x)
        {
            if (fabs(A[p[t] * cols + i]) < fabs(A[p[x] * cols + i]))
            {
                count++;
                unsigned temp = p[t];
                p[t] = p[x];
                p[x] = temp;
            }
        }
        // check if cofactor is equal to zero
        double pivot = A[p[i] * cols + i];
        if (fabs(pivot) <= DBL_EPSILON)
        {
            d = 0.0; 
            return true;
        }
        // operate elimination 
        for (int k = i + 1; k < rows; ++k)
        {
            double m = A[p[k] * cols + i] / pivot;
            for (int j = i + 1; j < cols; ++j)
                A[p[k] * cols + j] = A[p[k] * cols + j] - m * A[p[i] * cols + j];        
        }
    }
    // compute value of determinant using elements of main diagonal
    d = 1.0;
    for (int i = 0; i < rows; ++i)
        d *= A[p[i] * rows + i];
    // get the sign of determinant
    d = (count % 2) ? -d : d;

    // free memory
    delete [] p;
    delete [] A;

    return true;
}

bool lup(const Matrix a, const double *b, double *&set)
{
    // validation check
    if (!check(a))
        return false;
    // check if a is square matrix
    if (a.rows != a.cols)
    {
        cout << "Matrix a is not square matrix!" << endl;
        return false;
    }

    unsigned rows = a.rows;
    unsigned cols = a.cols;
    // create copy of a data
    double *A = new double[a.rows * a.cols];
    memcpy(A, a.data, sizeof(double) * a.rows * a.cols);

    // row vector for record line-swap
    // also called permutation matrix
    unsigned *p = new unsigned[rows];
    for (unsigned i = 0; i < rows; ++i)
        p[i] = i;

    unsigned count = 0; // record the times of swap-line
    
    // LUP decomposition method
    for (unsigned i = 0; i < cols; ++i)
    {
        // select leading row for reduction
        unsigned t = i;
        for (unsigned x = i + 1; x < rows; ++x)
        {
            if (fabs(A[p[t] * cols + i]) < fabs(A[p[x] * cols + i]))
            {
                count++;
                unsigned temp = p[t];
                p[t] = p[x];
                p[x] = temp;
            }
        }
        // check if cofactor is equal to zero
        double pivot = A[p[i] * cols + i];
        if (fabs(pivot) <= DBL_EPSILON)
        {
            cout << "Error: a is a singular matrix!" << endl;
            return false;
        }
        // operate elimination 
        for (int k = i + 1; k < rows; ++k)
        {
            double m = A[p[k] * cols + i] / pivot;
            // create L matrix
            A[p[k] * cols + i] = m;
            // create U matrix
            for (int j = i + 1; j < cols; ++j)
                A[p[k] * cols + j] = A[p[k] * cols + j] - m * A[p[i] * cols + j];        
        }
    }
    
    // forward substitution
    double *y = new double[rows];
    for (int i = 0; i < cols; ++i)
    {
        double temp = 0.0;
        for (int j = 0; j < i; ++j)
            temp += A[p[i] * cols + j] * y[j]; 
        y[i] = b[p[i]] - temp;
    }

    // back substitution
    for (int i = cols - 1; i >= 0; --i)
    {
        double temp = 0.0;
        for (int j = i + 1; j < cols; ++j)
            temp += A[p[i] * cols + j] * set[j];
        set[i] = (y[i] - temp) / A[p[i] * cols + i];
    }
    
    // free memory
    delete [] A;
    delete [] p;
    delete [] y;

    return true;
}

bool inv(const Matrix a, Matrix &b)
{
    // validation check
    if (!check(a))
        return false;

    // check if a is square matrix
    if (a.rows != a.cols)
    {
        cout << "Matrix a is not square matrix!" << endl;
        return false;
    }

    b.rows = a.rows;    b.cols = a.cols;
    b.data = new double[b.rows * b.cols];
    
    double *I = new double[a.rows];
    for (unsigned i = 0; i < a.rows; ++i)
        I[i] = 0.0;

    double *x = new double[a.rows];
    for (unsigned i = 0; i < a.cols; ++i)
    {
        I[i] = 1.0;
        if (!lup(a, I, x))
            return false;
        I[i] = 0.0;
        for (unsigned j = 0; j < a.rows; ++j)
        {
            b.data[j * b.cols + i] = x[j];
        }
    }
    
    // free memory 
    delete [] x;
    delete [] I;
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
