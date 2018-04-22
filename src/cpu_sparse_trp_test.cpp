#include "cpu_matlab.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

#define MAX_ROW 30
#define MAX_COL 30

using namespace std;

int main(int argc, char **argv)
{
    srand((unsigned) time(NULL));
    unsigned t_id = 0;
    bool flag;

    SparseMatrix a, b;
    a.rows = rand() % MAX_ROW + 1;
    a.cols = rand() % MAX_COL+ 1;

    // init matrices
    rand(a);
    
    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << a.rows << "x" << a.cols << endl;
    // print matrix a
    print(a);

    cout << "Matrix Transpose Result:" << endl;
    if (transpose(a, b))
    {
        cout << "Size: " << b.rows << "x" << b.cols << endl;
        print(b); 
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }

    cout << "Matrix Transpose Result(fast):" << endl;
    if (fastTranspose(a, b))
    {
        cout << "Size: " << b.rows << "x" << b.cols << endl;
        print(b); 
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }
    
    if (a.table)
        delete [] a.table; 
    if (b.table)
        delete [] b.table;
    
    return 0;
}
