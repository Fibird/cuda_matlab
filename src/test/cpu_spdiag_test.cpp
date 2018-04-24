#include <iostream>
#include "sparse_matrix.h"

using namespace std;

int main(int argc, char **argv)
{
    Matrix b;
    SparseMatrix a;
    int *d;
    int d_size, m, n;

    cout << "Please enter size of matrix B(height*width): " << endl;
    cin >> b.rows;
    cin >> b.cols;
    b.data = new double[b.rows * b.cols];
    cout << "Please enter elements of matrix B: " << endl;
    for (unsigned i = 0; i < b.rows * b.cols; ++i)
        cin >> b.data[i];
    
    cout << "Please enter size of vector D: " << endl;
    cin >> d_size;
    d = new int[d_size];
    cout << "Please enter element of vector D: " << endl;
    for (unsigned i = 0; i < d_size; ++i)
        cin >> d[i];
    
    cout << "Please enter size of result sparse matrix(height*widht): " << endl;
    cin >> m >> n;
    spdiag(b, d, d_size, m, n, a);

    Matrix m_a;
    Spa2Nor(a, m_a);
    print(m_a);
    
    if (m_a.data)
        delete [] m_a.data;
    if (b.data)
        delete [] b.data;
    if (a.table)
        delete [] a.table;
    delete [] d;

    return 0;
}
