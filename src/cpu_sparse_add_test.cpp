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

    SparseMatrix a, b, c;
//    a.rows = rand() % MAX_ROW + 1;
//    b.rows = rand() % MAX_ROW + 1;
//    a.cols = rand() % MAX_COL + 1;
//    b.cols = rand() % MAX_COL + 1;
//    c.table = NULL;
    a.rows = atoi(argv[1]);   a.cols = atoi(argv[2]);
    b.rows = atoi(argv[3]);   b.cols = atoi(argv[4]);

    // init matrices
    rand(a);
    sleep(1);
    rand(b); 

//    a.table[1].row = 0; a.table[1].col = 4; a.table[1].value = 0.34;
//    b.table[1].row = 0; b.table[1].col = 1; b.table[1].value = 0.45;
//    b.table[2].row = 0; b.table[2].col = 4; b.table[2].value = 0.23;
    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << a.rows << "x" << a.cols << endl;
    // print sparse matrix a
    print(a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << b.rows << "x" << b.cols << endl;
    // print sparse matrix b
    print(b);

    cout << "Addition Test Result:" << endl;
    if (add(a, b, c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << c.rows << "x" << c.cols << endl;
        print(c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }

    if (a.table)
        delete [] a.table; 
    if (b.table)
        delete [] b.table;
    if (c.table)
        delete [] c.table;

    return 0;
}
