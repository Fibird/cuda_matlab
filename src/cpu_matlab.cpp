#include <iostream>
#include <cstdlib>
#include "cpu_matlab.h"

using namespace std;

void add(const Matrix a, const Matrix b, Matrix c)
{
    int n = a.rows * a.cols;
    if (!c.data)
    {
        c.rows = a.rows;
        c.cols = c.cols;
        c.data = new double[c.rows * c.cols];
    }
    for (int i = 0; i < n; ++i)
    {
        c.data[i] = a.data[i] + b.data[i];
    }
}

void sub(const Matrix a, const Matrix b, Matrix c)
{
    int n = a.rows * a.cols;
    if (!c.data)
    {
        c.rows = a.rows;
        c.cols = a.cols;
        c.data = new double[c.rows * c.cols];
    }

    for (int i = 0; i < n; ++i)
    {
        c.data[i] = a.data[i] - b.data[i];
    }
}

void mul(const Matrix a, const Matrix b, Matrix c)
{
    if (a.cols != b.rows)
    {
        cout << "Matrices inner dimension is not identical!" << endl;
        exit(EXIT_FAILURE);
    }
    if (!c.data)
    {
        c.rows = a.rows;
        c.cols = b.cols;
        c.data = new double[c.rows * c.cols];
    }
    for (int i = 0; i < a.rows; ++i)
    {
        double temp = 0.0f;
        for (int j = 0; j < b.cols; ++j)
        {
            for (int t = 0; t < a.cols; ++t)
            {
                temp += a.data[i * a.cols + t] * b.data[t * b.cols + j];
            }
            c.data[i * c.cols + j] = temp;
        }
    }
}

void mul(const Matrix a, const double b, Matrix c)
{
    if (!c.data)
    {
        c.rows = a.rows;
        c.cols = a.cols;
        c.data = new double[c.rows * c.cols];
    }
    int n = a.rows * a.cols;
    for (int i = 0; i < n; ++i)
    {
        c.data[i] = a.data[i] * b;
    }
}

void transpose(const Matrix a, Matrix b)
{
    if (!b.data)
    {
        b.rows = a.cols;
        b.cols = a.rows;
        b.data = new double[b.rows * b.cols];
    }
    for (int i = 0; i < a.rows; ++i)
    {
        for (int j = 0; j < a.cols; ++j)
        {
            b.data[j * b.cols + i] = a.data[i * a.cols + j];
        }
    }
}

