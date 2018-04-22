#include <iostream>
#include "sparse_matrix.h"

using namespace std;

int main()
{
    ///////// Test Case 1 /////////
    Matrix t1_a;    SparseMatrix t1_b;

    t1_a.cols = 4; t1_a.rows = 5;
    rand(t1_a);
    cout << "------------- Test 1 --------------" << endl;
    
    cout << "Matrix a:" << endl;
    cout << "Size:" << t1_a.rows << "x" << t1_a.cols << endl;
    print(t1_a);

    if (Nor2Spa(t1_a, t1_b))
    {
        cout << "Transfomed Matrix b:" << endl;
        cout << "Size:" << t1_b.rows << "x" << t1_b.cols << endl;
        print(t1_b);
    }
    else
        cout << "Error" << endl;
    
    if (t1_a.data)
        delete [] t1_a.data;
    if (t1_b.table)
        delete [] t1_b.table;

    ///////// Test Case 2 /////////
    Matrix t2_a; SparseMatrix t2_b;

    t2_a.rows = 4;  t2_a.cols = 5;
    zeros(t2_a);

    cout << "------------- Test 2 --------------" << endl;
    cout << "Matrix a:" << endl;
    cout << "Size:" << t2_a.rows << "x" << t2_a.cols << endl;
    print(t2_a);

    if (Nor2Spa(t2_a, t2_b))
    {
        cout << "Transfomed Matrix b:" << endl;
        cout << "Size:" << t2_b.rows << "x" << t2_b.cols << endl;
        print(t2_b);
    }
    else
        cout << "Error" << endl;
    
    if (t2_a.data)
        delete [] t2_a.data;
    if (t2_b.table)
        delete [] t2_b.table;

    /////// Test Case 3 ///////////
    SparseMatrix t3_a; Matrix t3_b;

    t3_a.rows = 4;  t3_a.cols = 5;
    zeros(t3_a);

    cout << "------------- Test 2 --------------" << endl;
    cout << "Matrix a:" << endl;
    cout << "Size:" << t3_a.rows << "x" << t3_a.cols << endl;
    print(t3_a);

    if (Spa2Nor(t3_a, t3_b))
    {
        cout << "Transfomed Matrix b:" << endl;
        cout << "Size:" << t3_b.rows << "x" << t3_b.cols << endl;
        print(t3_b);
    }
    else
        cout << "Error" << endl;
    
    if (t3_a.table)
        delete [] t3_b.data;
    if (t3_b.data)
        delete [] t3_a.table;


    return 0;
}
