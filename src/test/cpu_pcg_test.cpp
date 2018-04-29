#include <iostream>
#include "sparse_matrix.h"

using namespace std;

int main(int argc, char **argv)
{
    SparseMatrix a;
    double tol;
    unsigned maxit;
    double *x;

    cout << "Please enter size of matrix a: " << endl;
    cin >> a.rows >> a.cols;
    cout << "Please enter terms of matrix a: " << endl;
    cin >> a.terms;
    a.table = new trituple[a.terms];

    cout << "Please enter vectors of sparse matrix a: " << endl;
    unsigned *rs = new unsigned[a.terms];
    unsigned *cs = new unsigned[a.terms];
    double *vs = new double[a.terms];

    for (unsigned i = 0; i < a.terms; ++i)
        cin >> rs[i];
    for (unsigned i = 0; i < a.terms; ++i)
        cin >> cs[i];
    for (unsigned i = 0; i < a.terms; ++i)
        cin >> vs[i];
    
    for (unsigned i = 0; i < a.terms; ++i)
    {
        a.table[i].row = rs[i] - 1;
        a.table[i].col = cs[i] - 1;
        a.table[i].value = vs[i];
    }
    cout << "Please enter the constant terms b: " << endl;
    double *b = new double[a.rows];
    for (unsigned i = 0; i < a.rows; ++i)
        cin >> b[i];

    cout << "Please enter the maximum numbers of iteration: " << endl;
    cin >> maxit;
    cout << "Please enter the tolerance: " << endl;
    cin >> tol;
    x = new double[a.rows];
    if (pcg(a, b, tol, maxit, x))
    {
        cout << "The solution is :" << endl;
        for (unsigned i = 0; i < a.rows; ++i)
            cout << x[i] << endl;
    }

    return 0;
}
