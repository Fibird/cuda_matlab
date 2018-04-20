#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cfloat>
#include <cmath>
#include "cpu_matlab.h"

using std::cout;
using std::endl;
using std::ios;
using std::setprecision;

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
    if (check(a))
    {
        cout << "Invalid matrix!" << endl;
        exit(EXIT_FAILURE);
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
        cout << "Row or column can not be zero!" << endl;
        return false;
    }
    if (!m.data)
    {
        cout << "Matrix data error!" << endl;
        return false;
    }

}
/*------------- Special Matrix --------------*/
bool add(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c)
{
    c.rows = a.rows;    c.cols = a.cols;
    c.table = NULL;

    // judge if matrices are compatible
    if (a.rows != b.rows || a.cols != b.cols)
        return false;
    // check validation of matrices
    check(a);   check(b); 
    // when matrix is all-zero matrix
    if (a.terms == 0)
    {
        c.terms = b.terms;
        c.table = new trituple[c.terms]; 
        for (unsigned i = 0; i < c.terms; ++i)
        {
            c.table[i].row = b.table[i].row;
            c.table[i].col = b.table[i].col;
            c.table[i].value = b.table[i].value;
        }
        return true;
    }
    else if (b.terms == 0)
    {
        c.terms = a.terms;
        c.table = new trituple[c.terms]; 
        for (unsigned i = 0; i < c.terms; ++i)
        {
            c.table[i].row = a.table[i].row;
            c.table[i].col = a.table[i].col;
            c.table[i].value = a.table[i].value;
        }
        return true;
    }
    // using a' term for the moment
    c.terms = a.terms;
    c.table = new trituple[a.terms]; 

    unsigned index_a, index_b, count = 0;
    unsigned i = 0, j = 0, rows = a.rows, cols = a.cols;
    while (i < a.terms && j < b.terms)
    {
        index_a = a.cols * a.table[i].row + a.table[i].col;
        index_b = b.cols * b.table[j].row + b.table[j].col;
        // check terms of matrix c
        if (count >= c.terms)
        {
            unsigned new_terms = c.terms * 2;
            // realloc memory for matrix c
            trituple *p = new trituple[new_terms];
            for (unsigned t = 0; t < c.terms; ++t)
                p[t] = c.table[t];
            c.terms = new_terms;
            delete [] c.table;
            c.table = p;
        }
        if (index_a < index_b)
        {
            c.table[count] = a.table[i]; 
            i++;
        }
        else if (index_a > index_b)
        {
            c.table[count] = b.table[j];
            j++;
        }
        else
        {
            c.table[count] = a.table[i];
            c.table[count].value = a.table[i].value + b.table[j].value;
            i++;    j++;
        }
        count++;
    }
    unsigned real_terms = count + a.terms - i + b.terms - j;
    // realloc memory for matrix c
    trituple *p = new trituple[real_terms];
    for (unsigned t = 0; t < count; ++t)
        p[t] = c.table[t];
    c.terms = real_terms;
    delete [] c.table;
    c.table = p;

    // copy remaining elements
    for (; i < a.terms; ++i)
        c.table[count++] = a.table[i]; 
    for (; j < b.terms; ++j)
        c.table[count++] = b.table[j];
    return true;
}

bool sub(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c)
{
    if (a.rows != b.rows || a.cols != b.cols)
        return false;
    // check validation of matrices
    check(a);   check(b);
    SparseMatrix d;
    if(!mul(b, -1.0f, d))
        return false;
    if (!add(a, d, c))
        return false;
    return true;
}

bool sub(const SparseMatrix a, const Matrix b, Matrix &c)
{
    if (a.rows != b.rows || a.cols != b.cols)
        return false;
    c.rows = a.rows;    c.cols = c.cols;
    c.data = NULL;
    // check validation of matrices
    check(a);   check(b);
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
    if (a.cols != b.rows)
        return false;
    c.rows = a.rows;    c.cols = b.cols;
    c.table = NULL;
    // check validation of matrices
    check(a);   check(b);
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
    if (a.cols != b.rows)
        return false;
    c.rows = a.rows;    c.cols = b.cols;
    c.table = NULL;
    // check validation of matrices
    check(a);   check(b);
    SparseMatrix new_b;
    if (!Nor2Spa(b, new_b))
        return false;
    if (!mul(a, new_b, c))
        return false;
    return true;
}

bool mul(const SparseMatrix a, const Matrix b, Matrix &c)
{
    if (a.cols != b.rows)
        return false;
    c.rows = a.rows;    c.cols = b.cols;
    c.data = NULL;
    // check validation of matrices
    check(a);   check(b);
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
    // check validation of matrix
    check(a);
    c.rows = a.rows;    c.cols = a.cols;
    c.table = NULL;
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
    // check validation of matrix
    check(a);
    b.rows = a.cols;    b.cols = a.rows;
    b.table = NULL;
    b.terms = a.terms;
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
    // check validation of matrix
    check(a);
    b.rows = a.rows;    b.cols = a.cols;
    b.table = NULL;
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
    // check validation of matrix
    check(a);
    // init matrix b
    b.cols = a.cols;    b.rows = a.rows;
    b.data = NULL;
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
    // check validation of matrix
    check(a);
    b.cols = a.cols;    b.rows = a.rows;
    b.table = NULL;
    // using rows  of a for the time
    b.terms = a.rows;
    b.table = new trituple[b.terms];
    
    unsigned count = 0;
    for (unsigned i = 0; i < a.rows; ++i)
    {
        for (unsigned j = 0; j < a.cols; ++j)
        {
            // extend memory space of matrix b
            if (count >= b.terms)
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

void rand(SparseMatrix &a)
{
    srand((unsigned) time(NULL));
    a.terms = rand() % (int)ceil(a.rows * a.cols * 0.05);
    if (a.terms == 0)
        a.table = NULL;
    else
        a.table = new trituple[a.terms];
    int t = a.terms;
    bool rows_cols[a.rows][a.cols] = {false};

    while (t > 0)
    {
        unsigned r = rand() % a.rows;
        unsigned c = rand() % a.cols;
        
        if (!rows_cols[r][c])
        {
            rows_cols[r][c] = true;
            t--;
        }
    }
    
    for (unsigned i = 0; i < a.rows; ++i)
    {
        for (unsigned j = 0; j < a.cols; ++j)
        {
            if (rows_cols[i][j])
            {
                a.table[t].row = i;
                a.table[t].col = j;
                a.table[t].value = (double)rand() / (double) RAND_MAX;
                t++;
            }
            if (t == a.terms)
                break;
        }
        if (t == a.terms)
            break;
    }
}

void print(const trituple t)
{
    cout << "(" << t.row << "," << t.col << ")" 
    << "\t" << t.value << endl;
}

void print(const SparseMatrix a)
{
    // check validation of matrix
    if (check(a))
    {
        cout << "Invalid matrix!" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "\n";
    if (a.terms == 0)
        cout << "All zero sparse: " << a.rows 
        << "-by-" << a.cols << endl;
    else
        for (unsigned i = 0; i < a.terms; ++i)
            print(a.table[i]);
    cout << "\n";
}

bool check(const SparseMatrix &sm)
{
    // check matrix row and column
    if (sm.rows == 0 || sm.cols == 0)
    {
        cout << "Row or column can not be zero!" << endl;
        return false;
    }
    // check matrix term
    if (sm.terms == 0 && sm.table != NULL ||
        sm.terms != 0 && sm.table == NULL)
    {
        cout << "Sparse matrix data error!" << endl;
        return false;
    }
}
