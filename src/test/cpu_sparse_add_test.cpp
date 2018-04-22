#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include "sparse_matrix.h"

#define MAX_ROW 10
#define MAX_COL 10

using namespace std;

int main(int argc, char **argv)
{
    srand((unsigned) time(NULL));
    bool flag;
    int test_id = 0;
    
    //////// Test Case 1 ////////
    cout << "-------- Test " << test_id << "--------" << endl;
    SparseMatrix t1_a, t1_b, t1_c;
    test_id++;
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

    //////// Test Case 2 ////////
    cout << "-------- Test " << test_id << "--------" << endl;
    SparseMatrix t2_a, t2_b, t2_c;
    test_id++;
    t2_a.rows = 8;      t2_a.cols = 6;
    t2_b.rows = 8;      t2_b.cols = 6;
    // init matrices
    zeros(t2_a);
    sleep(1);
    zeros(t2_b); 

    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t2_a.rows << "x" << t2_a.cols << endl;
    // print sparse matrix a
    print(t2_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t2_b.rows << "x" << t2_b.cols << endl;
    // print sparse matrix b
    print(t2_b);

    cout << "Addition Test Result:" << endl;
    if (add(t2_a, t2_b, t2_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t2_c.rows << "x" << t2_c.cols << endl;
        print(t2_c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }

    if (t2_a.table)
        delete [] t2_a.table; 
    if (t2_b.table)
        delete [] t2_b.table;
    if (t2_c.table)
        delete [] t2_c.table;

    //////// Test Case 3 ////////
    cout << "-------- Test " << test_id << "--------" << endl;
    SparseMatrix t3_a, t3_b, t3_c;
    test_id++;
    t3_a.rows = 9;      t3_a.cols = 12;
    t3_b.rows = 9;      t3_b.cols = 12;
    // init matrices
    rand(t3_a);
    sleep(1);
    rand(t3_b); 

    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t3_a.rows << "x" << t3_a.cols << endl;
    // print sparse matrix a
    print(t3_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t3_b.rows << "x" << t3_b.cols << endl;
    // print sparse matrix b
    print(t3_b);

    cout << "Addition Test Result:" << endl;
    if (add(t3_a, t3_b, t3_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t3_c.rows << "x" << t3_c.cols << endl;
        print(t3_c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }

    if (t3_a.table)
        delete [] t3_a.table; 
    if (t3_b.table)
        delete [] t3_b.table;
    if (t3_c.table)
        delete [] t3_c.table;

    //////// Test Case 4 ////////
    cout << "-------- Test " << test_id << "--------" << endl;
    SparseMatrix t4_a, t4_b, t4_c;
    test_id++;
    t4_a.rows = 9;      t4_a.cols = 12;
    t4_b.rows = 9;      t4_b.cols = 12;
    // init matrices
    rand(t4_a);
    sleep(1);
    zeros(t4_b); 

    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t4_a.rows << "x" << t4_a.cols << endl;
    // print sparse matrix a
    print(t4_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t4_b.rows << "x" << t4_b.cols << endl;
    // print sparse matrix b
    print(t4_b);

    cout << "Addition Test Result:" << endl;
    if (add(t4_a, t4_b, t4_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t4_c.rows << "x" << t4_c.cols << endl;
        print(t4_c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }

    if (t4_a.table)
        delete [] t4_a.table; 
    if (t4_b.table)
        delete [] t4_b.table;
    if (t4_c.table)
        delete [] t4_c.table;

    //////// Test Case 5 ////////
    cout << "-------- Test " << test_id << "--------" << endl;
    SparseMatrix t5_a, t5_b, t5_c;
    test_id++;
    t5_a.rows = 9;      t5_a.cols = 12;
    t5_b.rows = 9;      t5_b.cols = 12;
    // init matrices
    zeros(t5_a);
    sleep(1);
    rand(t5_b); 

    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t5_a.rows << "x" << t5_a.cols << endl;
    // print sparse matrix a
    print(t5_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t5_b.rows << "x" << t5_b.cols << endl;
    // print sparse matrix b
    print(t5_b);

    cout << "Addition Test Result:" << endl;
    if (add(t5_a, t5_b, t5_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t5_c.rows << "x" << t5_c.cols << endl;
        print(t5_c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }

    if (t5_a.table)
        delete [] t5_a.table; 
    if (t5_b.table)
        delete [] t5_b.table;
    if (t5_c.table)
        delete [] t5_c.table;
    
    //////// Test Case 6 ////////
    cout << "-------- Test " << test_id << "--------" << endl;
    SparseMatrix t6_a, t6_b, t6_c;
    test_id++;
    t6_a.rows = 9;      t6_a.cols = 12;
    t6_b.rows = 9;      t6_b.cols = 12;
    // init matrices
    // don't init a
    sleep(1);
    rand(t6_b); 

    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t6_a.rows << "x" << t6_a.cols << endl;
    // print sparse matrix a
    print(t6_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t6_b.rows << "x" << t6_b.cols << endl;
    // print sparse matrix b
    print(t6_b);

    cout << "Addition Test Result:" << endl;
    if (add(t6_a, t6_b, t6_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t6_c.rows << "x" << t6_c.cols << endl;
        print(t6_c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }

    if (t6_a.table)
        delete [] t6_a.table; 
    if (t6_b.table)
        delete [] t6_b.table;
    if (t6_c.table)
        delete [] t6_c.table;

    return 0;
}
