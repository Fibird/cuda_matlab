#include <iostream>
#include "sparse_matrix.h"

using namespace std;

int main(int argc, char **argv)
{
    Matrix a, b;

    cout << "Please enter size of matrix a: " << endl;
    cin >> a.rows >> a.cols;
    
    a.data = new double[a.rows * a.cols];

    cout << "Please enter elements of matrix a: " << endl;
    for (unsigned i = 0; i < a.rows * a.cols; ++i)
        cin >> a.data[i];

    if (inv(a, b))
    {
        cout << "The inverse matrix of a is :" << endl;
        print(b);
    }

    delete [] a.data;

    return 0;
}
