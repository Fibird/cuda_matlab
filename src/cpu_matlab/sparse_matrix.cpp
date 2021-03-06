#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cfloat>
#include <cmath>
#include <cstring>
#include "sparse_matrix.h"

using std::cout;
using std::endl;
using std::ios;
using std::setprecision;

bool add(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c)
{
    c.table = NULL;

    // judge if matrices are compatible
    if (a.rows != b.rows || a.cols != b.cols)
        return false;
    // check validation of matrices
    if (!check(a))
        return false;
    if (!check(b))
        return false; 

    c.rows = a.rows;    c.cols = a.cols;

    // when matrix is all-zero matrix
    if (a.terms == 0 && b.terms == 0)
    {
        c.terms = 0;
        c.table = NULL;
        return true;
    }
    else if (a.terms == 0)
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
    
    // when sparse matrices not all-zeros
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
            memcpy(p, c.table, c.terms * sizeof(trituple));
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
            double temp = a.table[i].value + b.table[j].value;
            i++;    j++;
            // judge if is zero
            if (temp <= DBL_EPSILON)
                continue;
            c.table[count] = a.table[i];
            c.table[count].value = temp;
        }
        count++;
    }
    unsigned real_terms = count + a.terms - i + b.terms - j;
    if (count > 0)
    {
        trituple *p = new trituple[real_terms];
        memcpy(p, c.table, count * sizeof(trituple));
        c.terms = real_terms;
        delete [] c.table;
        c.table = p;
    }

    // copy remaining elements
    for (; i < a.terms; ++i)
        c.table[count++] = a.table[i]; 
    for (; j < b.terms; ++j)
        c.table[count++] = b.table[j];
    if (count == 0)
    {
        delete [] c.table;
        c.table = NULL;
        c.terms = 0;
    }
    return true;
}

bool add(const SparseMatrix a, const Matrix b, Matrix &c)
{
    c.data = NULL;

    if (a.rows != b.rows || a.cols != b.cols)
        return false;

    c.rows = a.rows;    c.cols = c.cols;

    // check validation of matrices
    if (!check(a))
        return false;
    if (!check(b))
        return false; 

    SparseMatrix new_b;
    if (!Nor2Spa(b, new_b))
        return false;

    SparseMatrix temp_c;
    if (!add(a, new_b, temp_c))
        return false;

    // free memory of temporary variable
    if (new_b.table)
        delete [] new_b.table;

    if (!Spa2Nor(temp_c, c))
        return false;

    // free memory of temporary variable
    if (temp_c.table)
        delete [] temp_c.table;

    return true;
}

bool add(const Matrix a, const SparseMatrix b, Matrix &c)
{
    return add(b, a, c);
}

bool sub(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c)
{
    c.table = NULL;

    if (a.rows != b.rows || a.cols != b.cols)
        return false;

    // check validation of matrices
    if (!check(a))
        return false;
    if (!check(b))
        return false; 

    SparseMatrix d;
    if(!mul(b, -1.0f, d))
        return false;

    if (!add(a, d, c))
        return false;
    if (d.table)
        delete [] d.table;

    return true;
}

bool sub(const SparseMatrix a, const Matrix b, Matrix &c)
{
    c.data = NULL;

    if (a.rows != b.rows || a.cols != b.cols)
        return false;

    c.rows = a.rows;    c.cols = c.cols;

    // check validation of matrices
    if (!check(a))
        return false;
    if (!check(b))
        return false; 

    SparseMatrix new_b;
    if (!Nor2Spa(b, new_b))
        return false;

    SparseMatrix temp_c;
    if (!sub(a, new_b, temp_c))
        return false;

    // free memory of temporary variable
    if (new_b.table)
        delete [] new_b.table;

    if (!Spa2Nor(temp_c, c))
        return false;

    // free memory of temporary variable
    if (temp_c.table)
        delete [] temp_c.table;

    return true;
}

bool sub(const Matrix a, const SparseMatrix b, Matrix &c)
{
    return sub(b, a, c);
}

bool mul(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c)
{
    c.table = NULL;

    if (a.cols != b.rows)
        return false;
    // check validation of matrices
    if (!check(a))
        return false;
    if (!check(b))
        return false; 
 
    c.rows = a.rows;    c.cols = b.cols;

    // when sparse matrices all-zeros
    if (a.terms == 0 || b.terms == 0)
    {
        c.terms = 0;
        return true;
    }

    // when sparse matrices not all-zeros
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
                memcpy(p, c.table, c.terms * sizeof(trituple));
                c.terms = new_terms;
                delete [] c.table;
                c.table = p;
            }
            // judge if is zero
            if (temp[i] > DBL_EPSILON)
            {
                c.table[count].row = a_cur_row;
                c.table[count].col = i;
                c.table[count].value = temp[i];
                count++;
            }
        }
    }

    // remove excessive memory space
    if (count == 0)
    {
        delete [] c.table;
        c.table = NULL;
        c.terms = 0;
    }
    else if (c.terms > count)
    {
        // realloc memory for matrix c
        trituple *p = new trituple[count];
        memcpy(p, c.table, count * sizeof(trituple));
        c.terms = count;
        delete [] c.table;
        c.table = p;
    }
    delete [] nonzeros; delete [] term_starts;
    return true;
}


bool mul(const SparseMatrix a, const Matrix b, SparseMatrix &c)
{
    c.table = NULL;

    if (a.cols != b.rows)
        return false;

    c.rows = a.rows;    c.cols = b.cols;

    // check validation of matrices
    if (!check(a))
        return false;
    if (!check(b))
        return false; 

    SparseMatrix new_b;
    if (!Nor2Spa(b, new_b))
        return false;

    if (!mul(a, new_b, c))
        return false;
    if (new_b.table)
        delete [] new_b.table;

    return true;
}

bool mul(const SparseMatrix a, const Matrix b, Matrix &c)
{
    c.data = NULL;

    if (a.cols != b.rows)
        return false;
        
    c.rows = a.rows;    c.cols = b.cols;

    // check validation of matrices
    if (!check(a))
        return false;
    if (!check(b))
        return false; 

    SparseMatrix new_b;
    if (!Nor2Spa(b, new_b))
        return false;

    SparseMatrix temp_c;
    if (!mul(a, new_b, temp_c))
        return false;
    if (new_b.table)
        delete [] new_b.table;

    if (!Spa2Nor(temp_c, c))
        return false;
    if (temp_c.table)
        delete [] temp_c.table;

    return true;
}

bool mul(const SparseMatrix a, const double b, SparseMatrix &c)
{
    c.table = NULL;

    // check validation of matrix
    if (!check(a))
        return false;

    c.rows = a.rows;    c.cols = a.cols;
    c.terms = a.terms;

    // when a is all-zeros sparse matrix
    if (c.terms == 0)
        return true;

    // when a is not all-zeros sparse matrix
    c.table = new trituple[c.terms];
    for (int i = 0; i < a.terms; ++i)
    {
        c.table[i] = a.table[i];
        c.table[i].value = a.table[i].value * b;
    }
    return true;
}

bool mul(const double b, const SparseMatrix a, SparseMatrix &c)
{
    return mul(a, b, c);
}

bool pow(const SparseMatrix a, const SparseMatrix b, Matrix &c)
{
    c.data = NULL;

    // check validation of matrix
    if (!check(a) || !check(b))
        return false;

    if (a.rows != b.rows || a.cols != b.rows)
        return false;
    
    c.rows = a.rows;    c.cols = a.cols;
    c.data = new double[c.rows * c.cols];

    // when a or b is all-zeros matrices
    if (b.terms == 0)
    {
        for (unsigned i = 0; i < c.rows * c.cols; ++i)
            c.data[i] = 1.0;
        return true;
    }
    else if (a.terms == 0)
    {
        unsigned t_id = 0;
        for (unsigned i = 0; i < c.rows; ++i)
        {
            for (unsigned j = 0; j < c.cols; ++j)
            {
                c.data[i * c.cols + j] = 1.0;
                if (b.table[t_id].row == i &&
                    b.table[t_id].col == j)         
                {
                     c.data[i * c.cols + j] =
                     pow(0.0, b.table[t_id].value);    
                     t_id++;
                }
            }
        }
        return true; 
    }

    // when a or b is not all-zeros matrices
    unsigned t_id = 0;
    for (unsigned i = 0; i < c.rows; ++i)
    {
        for (unsigned j = 0; j < c.cols; ++j)
        {
            c.data[i * c.cols + j] = 1.0f;
            if (a.table[t_id].row == i &&
                a.table[t_id].col == j)         
            {
                c.data[i * c.cols + j] =
                pow(a.table[t_id].value, b.table[t_id].value);    
                t_id++;
            }
        }
    }
    return true;
}

bool transpose(const SparseMatrix a, SparseMatrix &b)
{
    b.table = NULL;

    // check validation of matrix
    if (!check(a))
        return false;

    b.rows = a.cols;    b.cols = a.rows;
    b.terms = a.terms;

    // when a is all-zeros sparse matrix
    if (b.terms == 0)
        return true;
    
    // when a is not all-zeros sparse matrix
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
    b.table = NULL;

    // check validation of matrix
    if (!check(a))
        return false;

    b.rows = a.cols;    b.cols = a.rows;
    b.terms = a.terms;

    // when a is all-zeros sparse matrix
    if (b.terms == 0)
        return true;

    // when a is not all-zeros sparse matrix
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
    b.data = NULL;

    // check validation of matrix
    if (!check(a))
        return false;
    // init matrix b
    b.cols = a.cols;    b.rows = a.rows;
    
    // when a is all-zeros sparse matrix
    if (a.terms == 0)
    {
        zeros(b);
        return true;
    }

    // when a is not all-zeros sparse matrix
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
    b.table = NULL;

    // check validation of matrix
    if (!check(a))
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
            if (count >= b.terms)
            {
                unsigned new_terms = b.terms * 2;
                // realloc memory for matrix b
                trituple *p = new trituple[new_terms];
                memcpy(p, b.table, b.terms * sizeof(trituple));
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
    if (count == 0)
    {
        delete [] b.table;
        b.table = NULL;
        b.terms = 0;
    }
    else if (b.terms > count)
    {
        // realloc memory for matrix b
        trituple *p = new trituple[count];
        memcpy(p, b.table, count * sizeof(trituple));
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

void zeros(SparseMatrix &sm)
{
    sm.terms = 0;
    sm.table = NULL;
}

void print(const trituple t)
{
    cout.setf(ios::fixed);
    cout << "(" << t.row << "," << t.col << ")" 
    << "\t" << setprecision(3) << t.value << endl;
}

void mergeTable(trituple *&table, unsigned cols, unsigned mid, unsigned right)
{
    trituple temp[right];
    unsigned i = 0;   unsigned j = mid;    unsigned k = 0;

    // find smaller row * cols + col to put into temp
    while (i < mid && j < right)
    {
        unsigned v1 = table[i].row * cols + table[i].col;
        unsigned v2 = table[j].row * cols + table[j].col;
        if (v1 <= v2)
            temp[k++] = table[i++];
        else
            temp[k++] = table[j++];
    }

    // copy remaining elements
    while (i < mid)
        temp[k++] = table[i++];
    while (j < right)
        temp[k++] = table[j++];

    // copy ordered elements to previous table
    for (unsigned i = 0; i < right; ++i)
        table[i] = temp[i];
}

bool spdiags(const Matrix b, int *d, unsigned d_size, unsigned m, unsigned n, SparseMatrix &a)
{
    a.table = NULL;

    if (!check(b))
        return false;

    a.rows = m; a.cols = n;
    // compute terms of sparse matrix a
    unsigned max = m > n ? m : n;
    unsigned min = m > n ? n : m;
    unsigned upper = m > n ? min : max;
    unsigned lower = m > n ? max : min;
    unsigned a_t = 0;
    unsigned cumlens[d_size]; // accumulative lengths of diagonals

    // compute length of sparse matrix a
    for (unsigned i = 0; i < d_size; ++i)
    {
        // compute accumulative lengths of diagonals
        if (d[i] < 0)
            a_t += lower + d[i];
        if (d[i] > 0)
            a_t += upper - d[i];
        if (d[i] == 0)
            a_t += min;

        cumlens[i] = a_t;
    }

    a.terms = a_t;
    a.table = new trituple[a.terms];
    
    // get sparse matrix a
    unsigned count = 0;
    for (unsigned i = 0; i < d_size; ++i) 
    {
         unsigned a_r, a_c;
         unsigned b_r, b_c = i;
         if (m >= n)
         {
            b_r = a_c = d[i] <= 0 ? 0 : d[i];
            a_r = d[i] <= 0 ? -d[i] : 0;
         }
         else
         {
            b_r = a_r = d[i] <= 0 ? -d[i] : 0;
            a_c = d[i] <= 0 ? 0 : d[i];
         }
         while (a_r < a.rows && a_c < a.cols)
         {
            a.table[count].row = a_r;
            a.table[count].col = a_c;
            a.table[count].value = b.data[b_r * b.cols + b_c];
            count++;    b_r++;
            a_r++;  a_c++;
         }
    }
    // sort terms of sparse matrix
    // using merge sort
    for (unsigned i = 0; i < d_size - 1; ++i)
        mergeTable(a.table, a.cols, cumlens[i], cumlens[i + 1]);

    return true;
}

void print(const SparseMatrix a)
{
    // check validation of matrix
    if (!check(a))
    {
        cout << "Invalid matrix!" << endl;
        //exit(EXIT_FAILURE);
        return;
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
        cout << "Row or column of sparse matrix can not be zero!" << endl;
        return false;
    }
    // check matrix term
    if (sm.terms == 0 && sm.table != NULL ||
        sm.terms != 0 && sm.table == NULL)
    {
        cout << "Sparse matrix data error!" << endl;
        return false;
    }
    return true;
}


bool pcg(const SparseMatrix a, double *b, double tol, unsigned maxit, double *&set)
{
    // validation check
    if (!check(a))
        return false;

    if (a.rows != a.cols)
    {
        cout << "Matrix a is not square matrix!" << endl;
        return false;
    }
    
    //set = new double[a.rows];
    //for (unsigned i = 0; i < a.rows; ++i)
     //   set[i] = 0.0;
    
    Matrix x;
    x.rows = a.rows;    x.cols = 1;
    //x.data = set;
    x.data = new double[x.rows];
    for (unsigned i = 0; i < x.rows; ++i)
        x.data[i] = 0.0;
    // init r
    double *r = new double[a.rows];
    memcpy(r, b, sizeof(double) * a.rows);
    
    // preconditioning matrix
    SparseMatrix c;
    c.rows = a.rows;    c.cols = a.cols;
    // c is a diagonal matrix
    c.terms = a.rows; 
    c.table = new trituple[c.terms];
    // init c with diagonal of a
    unsigned count = 0;
    for (unsigned i = 0; i < a.terms; ++i)
    {
        if (a.table[i].row == a.table[i].col)
        {
            c.table[count].row = count; c.table[count].col = count;
            c.table[count].value = 1 / a.table[i].value;
            count++;
        }
    }

    Matrix w, R;
    // init vector R: r=b-Ax
    R.rows = a.rows;    R.cols = 1;
    R.data = r;
    // init vector w: w=Cr
    mul(c, R, w);
    
    // init vector v: v=Ctw
    SparseMatrix c_t;
    fastTranspose(c, c_t);
    SparseMatrix temp;
    mul(c_t, w, temp);
    Matrix v;
    Spa2Nor(temp, v);
    delete [] temp.table;

    // alpha=||w||2^2
    double alpha = 0.0;
    for (unsigned i = 0; i < a.rows; ++i)
        alpha += w.data[i] * w.data[i];
    
    // iterations
    unsigned k = 0;
    while (k <= maxit)
    {
        double norm = 0.0;
        // compute norm of v
        for (unsigned i = 0; i < a.rows; ++i)
            norm += fabs(v.data[i]);
        // judge if get to tol
        if (norm < tol)
            break;

        // compute u: u=Av
        Matrix u;
        mul(a, v, u);

        // compute t:t=alpha/(v,u)
        double t = 0.0;
        for (unsigned i = 0; i < a.rows; ++i)
            t += v.data[i] * u.data[i];
        t = alpha / t;

        // compute x: x=x+tv
        Matrix tv;
        mul(t, v, tv);
        add(x, tv, x);

        // compute r: r=r-tu
        Matrix tu;
        mul(t, u, tu);
        sub(R, tu, R);
        // compute w: w=cr
        mul(c, R, w);

        // compute beta: beta=||w||2^2
        double beta = 0.0, garma = 0.0;
        for (unsigned i = 0; i < a.rows; ++i)
        {
            garma += fabs(r[i]);
            beta += w.data[i] * w.data[i]; 
        }
        if (beta < tol && garma < tol)
            break;

        // compute s: s=beta/alpha
        double s = beta / alpha;
        // compute v: v=ctw+sv
        mul(c_t, w, v);
        Matrix sv;
        mul(s, v, sv);
        add(v, sv, v);

        alpha = beta;
        k++;
    }

    if (k > maxit)
        cout << "The maximum number of iterations was exceeded." << endl;
    set = x.data;

    return true;
}
