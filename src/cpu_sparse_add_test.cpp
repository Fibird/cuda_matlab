#include "cpu_matlab.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <iomanip>

#define MAX_ROW 10
#define MAX_COL 10

using namespace std;

int main(int argc, char **argv)
{
    srand((unsigned) time(NULL));
    bool flag;
    
    //////// Test Case 1 ////////
    SparseMatrix t1_a, t1_b, t1_c;
    t1_a.rows = 8;      t1_a.cols = 8;
    t1_b.rows = 9;      t1_b.cols = 5;
    // init matrices
    rand(t1_a);
    sleep(1);
    rand(t1_b); 

    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t1_a.rows << "x" << t1_a.cols << endl;
    // print sparse matrix a
    print(t1_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t1_b.rows << "x" << t1_b.cols << endl;
    // print sparse matrix b
    print(t1_b);

    cout << "Addition Test Result:" << endl;
    if (add(t1_a, t1_b, t1_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t1_c.rows << "x" << t1_c.cols << endl;
        print(t1_c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }

    if (t1_a.table)
        delete [] t1_a.table; 
    if (t1_b.table)
        delete [] t1_b.table;
    if (t1_c.table)
        delete [] t1_c.table;

    return 0;
}
