#include <iostream>
#include "sparse_matrix.h"

using namespace std;

int main(int argc, char **argv)
{
    Matrix a;
    unsigned len = 0;
    double *b, *x;

    cout << "Please enter size of matrix a: " << endl;
    cin >> a.rows >> a.cols;
    
    a.data = new double[a.rows * a.cols];

    cout << "Please enter elements of matrix a: " << endl;
    for (unsigned i = 0; i < a.rows * a.cols; ++i)
        cin >> a.data[i];

    len = a.rows;

    b = new double[len];
    x = new double[len];

    cout << "Please enter elements of b: " << endl;
    for (unsigned i = 0; i < len; ++i)
        cin >> b[i];

    if (lup(a, b, x))
    {
        cout << "The solution set is :" << endl;
        for (unsigned i = 0; i < len; ++i)
            cout << "X" << i << " = " << x[i] << endl;
    }

    delete [] a.data;
    delete [] b;
    delete [] x;

    return 0;
}
