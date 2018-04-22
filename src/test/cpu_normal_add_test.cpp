#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include "sparse_matrix.h"

#define MAX_ROW 10
#define MAX_COL 10

using namespace std;

int main(int argc, char **argv)
{
    srand((unsigned) time(NULL));
    unsigned t_id = 0;
    bool flag;

    Matrix t1_a, t1_b, t1_c;
    t1_a.rows = rand() % MAX_ROW + 1;
    t1_b.rows = rand() % MAX_ROW + 1;
    t1_a.cols = rand() % MAX_COL + 1;
    t1_b.cols = rand() % MAX_COL + 1;

    // init matrices
    rand(t1_a);
    rand(t1_b);
    
    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t1_a.rows << "x" << t1_a.cols << endl;

    // print matrix a
    print(t1_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t1_b.rows << "x" << t1_b.cols << endl;
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
    
    delete [] t1_a.data; 
    delete [] t1_b.data;
    delete [] t1_c.data;
    
    return 0;
}
