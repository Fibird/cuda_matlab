#include <iostream>
#include <cstdlib>
#include <cfloat>
#include "cpu_matlab.h"

using std::cout;
using std::endl;

/*------------- Normal Matrix --------------*/
bool add(const Matrix a, const Matrix b, Matrix &c)
{
    if (a.rows != b.rows || a.cols != b.cols
        || !a.data || !b.data)
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
    if (a.rows != b.rows || a.cols != b.cols
        || !a.data || !b.data)   
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
    if (a.cols != b.rows || !a.data || !b.data)
        return false;
    c.rows = a.rows;
    c.cols = b.cols;
    c.data = new double[c.rows * c.cols];

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
    return true;
}

bool mul(const Matrix a, const double b, Matrix &c)
{
    if (!a.data)
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

bool transpose(const Matrix a, Matrix &b)
{
    if (!a.data)
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

/*------------- Special Matrix --------------*/
bool add(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c)
{
    if (a.rows != b.rows || a.cols != b.cols
        || !a.table || !b.table)
        return false;
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
    return true;
}

bool sub(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c)
{
    if (a.rows != b.rows || a.cols != b.cols
        || !a.table || !b.table)
        return false;
    SparseMatrix d;
    if(!mul(b, -1.0f, d))
        return false;
    if (!add(a, d, c))
        return false;
    return true;
}

bool sub(const SparseMatrix a, const Matrix b, Matrix &c)
{
    if (a.rows != b.rows || a.cols != b.cols
        || !a.table || !b.data)
        return false;
    SparseMatrix new_b;
    if (!Nor2Spa(b, new_b))
        return false;
    SparseMatrix temp_c;
    if (!sub(a, new_b, temp_c))
        return false;
    if (!Spa2Nor(temp_c, c))
        return false;
    return true;
}

bool mul(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c)
{
    if (a.cols != b.rows || !a.table || !b.table)
        return false;
    c.rows = a.rows;    c.cols = b.cols;
    // using a' term for the time
    c.terms = a.terms;
    c.table = new trituple[c.terms];
    for (unsigned i = 0; i < c.terms; ++i)
        c.table[i].value = 0.0f;

    unsigned *nonzeros = new unsigned[b.rows];
    unsigned *term_starts = new unsigned[b.rows + 1];

    // count the number of non-zero elements every row
    for (unsigned i = 0; i < b.rows; ++i)
        nonzeros[i] = 0;
    for (unsigned i = 0; i < b.terms; ++i)
        nonzeros[b.table[i].row]++;

    // get the start positon of non-zero elements in every row
    term_starts[0] = 0;
    for (unsigned i = 1; i <= b.rows; ++i)
        term_starts[i] = term_starts[i - 1] + nonzeros[i - 1];
    
    unsigned cur = 0, prev = -1;
    double *temp = new double[b.cols];  // save results temporarily
    unsigned count = 0;
    while (cur < a.terms)
    {
        unsigned a_cur_row = a.table[cur].row;
        for (unsigned i = 0; i < b.cols; ++i)
            temp[i] = 0.0f;
        while (cur < a.terms && a.table[cur].row == a_cur_row)
        {
            unsigned a_cur_col = a.table[cur].col;
            for (unsigned i = term_starts[a_cur_col]; i < term_starts[a_cur_col + 1]; ++i)
                temp[b.table[i].col] += a.table[cur].value * b.table[i].value;
            cur++;
        }
        for (unsigned i = 0; i < b.cols; ++i)
        {
            // extend memory space of matrix c
            if (count >= c.terms - 1)
            {
                unsigned new_terms = c.terms * 2;
                trituple *p = new trituple[new_terms];
                for (unsigned t = 0; t < c.terms; ++t)
                    p[t] = c.table[t];
                c.terms = new_terms;
                delete [] c.table;
                c.table = p;
            }
            if (temp[i] != 0)
            {
                c.table[count].row = a_cur_row;
                c.table[count].col = i;
                c.table[count].value = temp[i];
                count++;
            }
        }
    }
    // remove excessive memory space
    if (c.terms > count)
    {
        // realloc memory for matrix c
        trituple *p = new trituple[count];
        for (unsigned t = 0; t < count; ++t)
            p[t] = c.table[t];
        c.terms = count;
        delete [] c.table;
        c.table = p;
    }
    delete [] nonzeros; delete [] term_starts;
    c.terms = count;
    return true;
}


bool mul(const SparseMatrix a, const Matrix b, SparseMatrix &c)
{
    if (a.cols != b.rows || !a.table || !b.data)
        return false;
    SparseMatrix new_b;
    if (!Nor2Spa(b, new_b))
        return false;
    if (!mul(a, new_b, c))
        return false;
    return true;
}

bool mul(const SparseMatrix a, const Matrix b, Matrix &c)
{
    if (a.cols != b.rows || !a.table || !b.data)
        return false;
    SparseMatrix new_b;
    if (!Nor2Spa(b, new_b))
        return false;
    SparseMatrix temp_c;
    if (!mul(a, new_b, temp_c))
        return false;
    if (!Spa2Nor(temp_c, c))
        return false;
    return true;
}

bool mul(const SparseMatrix a, const double b, SparseMatrix &c)
{
    if (!a.table)
        return false;
    c.rows = a.rows;    c.cols = a.cols;
    c.terms = a.terms;
    if (!c.table)
        c.table = new trituple[c.terms];

    for (int i = 0; i < a.terms; ++i)
    {
        c.table[i] = a.table[i];
        c.table[i].value = a.table[i].value * b;
    }
    return true;
}

bool transpose(const SparseMatrix a, SparseMatrix &b)
{
    if (!a.table)
        return false;
    b.rows = a.cols;    b.cols = a.rows;
    b.terms = a.terms;
    if (!b.table)
        b.table = new trituple[b.terms];

    unsigned count = 0;
    for (unsigned i = 0; i < a.cols; ++i)
    {
        for (unsigned j = 0; j < a.terms; ++j)
        {
            if (a.table[j].col == i)
            {
                b.table[count].row = a.table[j].col;
                b.table[count].col = a.table[j].row;
                b.table[count].value = a.table[j].value;
                count++;
            }
        }
    }
    return true;
}

bool fastTranspose(const SparseMatrix a, SparseMatrix &b)
{
    if (!a.table)
        return false;
    b.rows = a.rows;    b.cols = a.cols;
    b.terms = a.terms;
    b.table = new trituple[b.terms];

    unsigned *nonzeros = new unsigned[a.cols];
    unsigned *term_starts = new unsigned[a.cols];

    // count the number of non-zero elements every row 
    for (int i = 0; i < a.cols; ++i) 
        nonzeros[i] = 0;
    for (int i = 0; i < a.terms; ++i)
        nonzeros[a.table[i].col]++;
    
    // get the start positon of non-zero elements in every row
    term_starts[0];
    for (int i = 1; i < a.cols; ++i)
        term_starts[i] = term_starts[i - 1] + nonzeros[i - 1];
        
    // compute transpose matrix
    unsigned pos = 0;
    for (int i = 0; i < a.terms; ++i)
    {
        pos = term_starts[a.table[i].col];
        b.table[pos].row = a.table[i].col;
        b.table[pos].col = a.table[i].row;
        b.table[pos].value = a.table[i].value;
        term_starts[a.table[i].col]++;
    }
    delete [] nonzeros; delete [] term_starts;
    
    return true;
}

bool Spa2Nor(const SparseMatrix a, Matrix &b)
{
    if (!a.table)
        return false;
    // init matrix b
    b.cols = a.cols;    b.rows = a.rows;
    b.data = new double[b.cols * b.rows];

    unsigned count = 0;
    for (unsigned i = 0; i < b.rows; ++i)
    {
        for (unsigned j = 0; j < b.cols; ++j)
        {
            if (i == a.table[count].row && j == a.table[count].col)
            {
                b.data[i * b.cols + j] = a.table[count].value;
                count++;
            }
            else
            {
                b.data[i * b.cols + j] = 0.0f;
            }
        }
    }
    return true;
}

bool Nor2Spa(const Matrix a, SparseMatrix &b)
{
    if (!a.data)
        return false;
    b.cols = a.cols;    b.rows = a.rows;
    // using rows  of a for the time
    b.terms = a.rows;
    b.table = new trituple[b.terms];
    
    unsigned count = 0;
    for (unsigned i = 0; i < a.rows; ++i)
    {
        for (unsigned j = 0; j < a.cols; ++j)
        {
            // extend memory space of matrix b
            if (count >= b.terms - 1)
            {
                unsigned new_terms = b.terms * 2;
                // realloc memory for matrix b
                trituple *p = new trituple[new_terms];
                for (unsigned t = 0; t < b.terms; ++t)
                    p[t] = b.table[t];
                b.terms = new_terms;
                delete [] b.table;
                b.table = p;
            }
            if (a.data[i * a.cols + j] > DBL_EPSILON)
            {
                b.table[count].row = i;
                b.table[count].col = j;
                b.table[count].value = a.data[i * a.cols + j];
                count++;
            }
        }
    }
    // remove remaining memory space
    if (b.terms > count)
    {
        // realloc memory for matrix b
        trituple *p = new trituple[count];
        for (unsigned t = 0; t < count; ++t)
            p[t] = b.table[t];
        b.terms = count;
        delete [] b.table;
        b.table = p;
    }
    return true;
}
