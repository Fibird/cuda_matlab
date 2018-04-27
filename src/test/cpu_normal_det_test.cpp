#include <iostream>
#include "sparse_matrix.h"

using namespace std;

int main(int argc, char **argv)
{
    Matrix t1_a;
    double d;

    cout << "Please enter size of matrix a: " << endl;
    cin >> t1_a.rows >> t1_a.cols;
    
    t1_a.data = new double[t1_a.rows * t1_a.cols];

    cout << "Please enter elements of matrix a: " << endl;
    for (unsigned i = 0; i < t1_a.rows * t1_a.cols; ++i)
        cin >> t1_a.data[i];

    if (det(t1_a, d))
    {
        cout << "The determinant of a is : " << d << endl;
    }

    delete [] t1_a.data;
    return 0;
}
