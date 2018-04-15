#include <iostream>
#include <cstdlib>
#include "cpu_matlab.h"

using std::cout;
using std::endl;

/*------------- Normal Matrix --------------*/
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

/*------------- Special Matrix --------------*/
void add(const SparseMatrix a, const SparseMatrix b, SparseMatrix c)
{
    c.rows = a.rows;    c.cols = a.cols;
    // using a' term for the moment
    c.terms = a.terms;
    
    if (!c.table)
        c.table = new trituple[a.terms]; 

    unsigned index_a, index_b, count = 0;
    unsigned i = 0, j = 0, rows = a.rows, cols = a.cols;
    while (i < a.terms && j < b.terms)
    {
        index_a = a.cols * a.table[i].row + a.table[i].col;
        index_b = b.cols * b.table[i].row + b.table[i].col;
        // check terms of matrix c
        if (count >= (c.terms - 1))
        {
            unsigned new_terms = c.terms * 2;
            // realloc memory for matrix c
            trituple *p = new trituple[new_terms];
            for (unsigned t = 0; t < c.terms; ++t)
                p[i] = c.table[i];
            c.terms = new_terms;
            delete [] c.table;
            c.table = p;
        }
        if (index_a < index_b)
        {
            c.table[count] = a.table[i++]; 
        }
        else if (index_a > index_b)
        {
            c.table[count] = b.table[j++];
        }
        else
        {
            c.table[count] = a.table[i];
            c.table[count].value = a.table[i++].value + b.table[j++].value;
        }
        count++;
    }
    unsigned real_terms = count + a.terms - i + b.terms - j;
    if (count >= (c.terms - 1))
    {
        // realloc memory for matrix c
        trituple *p = new trituple[real_terms];
        for (unsigned t = 0; t < c.terms; ++t)
            p[i] = c.table[i];
        c.terms = real_terms;
        delete [] c.table;
        c.table = p;
    }    
    // copy remaining elements
    for (; i < a.terms; ++i)
        c.table[count++] = a.table[i]; 
    for (; j < b.terms; ++j)
        c.table[count++] = b.table[j];
}

void sub(const SparseMatrix a, const SparseMatrix b, SparseMatrix c)
{
    SparseMatrix d;
    mul(b, -1.0f, d);
    add(a, d, c);
}

void sub(const SparseMatrix a, const Matrix b, Matrix c)
{
    SparseMatrix new_b;
    Nor2Spa(b, new_b);        
    SparseMatrix temp_c;
    sub(a, new_b, temp_c);
    Spa2Nor(temp_c, c);
}


void mul(const SparseMatrix a, const SparseMatrix b, SparseMatrix c)
{

}


void mul(const SparseMatrix a, const Matrix b, SparseMatrix c)
{
    SparseMatrix new_b;
    Nor2Spa(b, new_b);
    mul(a, new_b, c);
}

void mul(const SparseMatrix a, const Matrix b, Matrix c)
{
    SparseMatrix new_b;
    Nor2Spa(b, new_b);
    SparseMatrix temp_c;
    mul(a, new_b, temp_c);
    Spa2Nor(temp_c, c);
}

void mul(const SparseMatrix a, const double b, SparseMatrix c)
{
    c.rows = a.rows;    c.cols = a.cols;
    c.terms = a.terms;
    if (!c.table)
        c.table = new trituple[c.terms];

    for (int i = 0; i < a.terms; ++i)
    {
        c.table[i] = a.table[i];
        c.table[i].value = a.table[i].value * b;
    }
}

void transpose(const SparseMatrix a, SparseMatrix b)
{

}

void Spa2Nor(const SparseMatrix a, Matrix b)
{

}

void Nor2Spa(const Matrix a, SparseMatrix b)
{

}
