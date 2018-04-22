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
    if (mul(t1_a, t1_b, t1_c))
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
    t2_b.rows = 6;      t2_b.cols = 8;
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
    if (mul(t2_a, t2_b, t2_c))
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
    t3_b.rows = 12;      t3_b.cols = 12;
    // init matrices
    ///////////////// Matrix a /////////////////
    //          10 0 5 7
    //          2 1 0 0
    //          3 0 4 0
    //----------- Sparse format
    //          (0, 0)  10
    //          (0, 2)  5
    //          (0, 3)  7
    //          (1, 0)  2
    //          (1, 1)  1
    //          (2. 0)  3
    //          (2, 2)  4
    t3_a.terms = 7;
    t3_a.table = new trituple[t3_a.terms];
    t3_a.table[0].row = 0;  t3_a.table[0].col = 0;
    t3_a.table[0].value = 10;
    t3_a.table[1].row = 0;  t3_a.table[1].col = 2;
    t3_a.table[1].value = 5;
    t3_a.table[2].row = 0;  t3_a.table[2].col = 3;
    t3_a.table[2].value = 7;
    t3_a.table[3].row = 1;  t3_a.table[3].col = 0;
    t3_a.table[3].value = 2;
    t3_a.table[4].row = 1;  t3_a.table[4].col = 1;
    t3_a.table[4].value = 1;
    t3_a.table[5].row = 2;  t3_a.table[5].col = 0;
    t3_a.table[5].value = 3;
    t3_a.table[6].row = 2;  t3_a.table[6].col = 2;
    t3_a.table[6].value = 4;

    ////////////// Matrix b /////////////
    //          2 0
    //          4 8
    //          0 14
    //          3 5
    //----------- Sparse format
    //          (0, 0)  2
    //          (1, 0)  4
    //          (1, 1)  8
    //          (2, 1)  14
    //          (3, 0)  3
    //          (3, 1)  5
    t3_b.terms = 6;
    t3_b.table = new trituple[t3_b.terms];
    t3_b.table[0].row = 0;  t3_b.table[0].col = 0;
    t3_b.table[0].value = 2;
    t3_b.table[1].row = 1;  t3_b.table[1].col = 0;
    t3_b.table[1].value = 4;
    t3_b.table[2].row = 1;  t3_b.table[2].col = 1;
    t3_b.table[2].value = 8;
    t3_b.table[3].row = 2;  t3_b.table[3].col = 1;
    t3_b.table[3].value = 14;
    t3_b.table[4].row = 3;  t3_b.table[4].col = 0;
    t3_b.table[4].value = 3;
    t3_b.table[5].row = 3;  t3_b.table[5].col = 1;
    t3_b.table[5].value = 5;

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
    if (mul(t3_a, t3_b, t3_c))
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
    t4_b.rows = 12;      t4_b.cols = 12;
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
    if (mul(t4_a, t4_b, t4_c))
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
    t5_b.rows = 12;      t5_b.cols = 12;
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
    if (mul(t5_a, t5_b, t5_c))
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
    t6_b.rows = 12;      t6_b.cols = 12;
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
    if (mul(t6_a, t6_b, t6_c))
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

    //////// Test Case 7 ////////
    cout << "-------- Test " << test_id << "--------" << endl;
    SparseMatrix t7_a, t7_b, t7_c;
    test_id++;
    t7_a.rows = 9;      t7_a.cols = 12;
    t7_b.rows = 12;      t7_b.cols = 12;
    // init matrices
    ///////////////// Matrix a /////////////////
    //          -1 0 -1 0
    //          -1 0 1 0
    //          -1 0 1 0
    //----------- Sparse format
    //          (0, 0)  -1
    //          (0, 2)  -1
    //          (1, 0)  -1
    //          (1, 2)  1
    //          (2, 0)  -1
    //          (2, 2)  1
    t7_a.terms = 6;
    t7_a.table = new trituple[t7_a.terms];
    t7_a.table[0].row = 0;  t7_a.table[0].col = 0;
    t7_a.table[0].value = -1;
    t7_a.table[1].row = 0;  t7_a.table[1].col = 2;
    t7_a.table[1].value = -1;
    t7_a.table[2].row = 1;  t7_a.table[2].col = 0;
    t7_a.table[2].value = -1;
    t7_a.table[3].row = 1;  t7_a.table[3].col = 2;
    t7_a.table[3].value = 1;
    t7_a.table[4].row = 2;  t7_a.table[4].col = 0;
    t7_a.table[4].value = -1;
    t7_a.table[5].row = 2;  t7_a.table[5].col = 2;
    t7_a.table[5].value = 1;
    
    ////////////// Matrix b /////////////
    //          1 1
    //          0 0
    //         -1 -1
    //          0 0
    //----------- Sparse format
    //          (0, 0)  1
    //          (0, 1)  1
    //          (2, 0)  -1
    //          (2, 1)  -1
    t7_b.terms = 4;
    t7_b.table = new trituple[t7_b.terms];
    t7_b.table[0].row = 0;  t7_b.table[0].col = 0;
    t7_b.table[0].value = -1;
    t7_b.table[1].row = 0;  t7_b.table[1].col = 1;
    t7_b.table[1].value = -1;
    t7_b.table[2].row = 2;  t7_b.table[2].col = 0;
    t7_b.table[2].value = -1;
    t7_b.table[3].row = 2;  t7_b.table[3].col = 1;
    t7_b.table[3].value = -1;

    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t7_a.rows << "x" << t7_a.cols << endl;
    // print sparse matrix a
    print(t7_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t7_b.rows << "x" << t7_b.cols << endl;
    // print sparse matrix b
    print(t7_b);

    cout << "Addition Test Result:" << endl;
    if (mul(t7_a, t7_b, t7_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t7_c.rows << "x" << t7_c.cols << endl;
        print(t7_c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }

    if (t7_a.table)
        delete [] t7_a.table; 
    if (t7_b.table)
        delete [] t7_b.table;
    if (t7_c.table)
        delete [] t7_c.table;

    //////// Test Case 8 ////////
    cout << "-------- Test " << test_id << "--------" << endl;
    SparseMatrix t8_a, t8_b, t8_c;
    test_id++;
    t8_a.rows = 9;      t8_a.cols = 12;
    t8_b.rows = 12;      t8_b.cols = 12;
    // init matrices
    ///////////////// Matrix a /////////////////
    //          -1 0 1 0
    //          -1 0 1 0
    //          -1 0 1 0
    //----------- Sparse format
    //          (0, 0)  -1
    //          (0, 2)  1
    //          (1, 0)  -1
    //          (1, 2)  1
    //          (2, 0)  -1
    //          (2, 2)  1
    t8_a.terms = 6;
    t8_a.table = new trituple[t8_a.terms];
    t8_a.table[0].row = 0;  t8_a.table[0].col = 0;
    t8_a.table[0].value = -1;
    t8_a.table[1].row = 0;  t8_a.table[1].col = 2;
    t8_a.table[1].value = 1;
    t8_a.table[2].row = 1;  t8_a.table[2].col = 0;
    t8_a.table[2].value = -1;
    t8_a.table[3].row = 1;  t8_a.table[3].col = 2;
    t8_a.table[3].value = 1;
    t8_a.table[4].row = 2;  t8_a.table[4].col = 0;
    t8_a.table[4].value = -1;
    t8_a.table[5].row = 2;  t8_a.table[5].col = 2;
    t8_a.table[5].value = 1;
    
    ////////////// Matrix b /////////////
    //          1 1
    //          0 0
    //         -1 -1
    //          0 0
    //----------- Sparse format
    //          (0, 0)  1
    //          (0, 1)  1
    //          (2, 0)  -1
    //          (2, 1)  -1
    t8_b.terms = 4;
    t8_b.table = new trituple[t8_b.terms];
    t8_b.table[0].row = 0;  t8_b.table[0].col = 0;
    t8_b.table[0].value = -1;
    t8_b.table[1].row = 0;  t8_b.table[1].col = 1;
    t8_b.table[1].value = -1;
    t8_b.table[2].row = 2;  t8_b.table[2].col = 0;
    t8_b.table[2].value = -1;
    t8_b.table[3].row = 2;  t8_b.table[3].col = 1;
    t8_b.table[3].value = -1;

    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t8_a.rows << "x" << t8_a.cols << endl;
    // print sparse matrix a
    print(t8_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t8_b.rows << "x" << t8_b.cols << endl;
    // print sparse matrix b
    print(t8_b);

    cout << "Addition Test Result:" << endl;
    if (mul(t8_a, t8_b, t8_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t8_c.rows << "x" << t8_c.cols << endl;
        print(t8_c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }

    if (t8_a.table)
        delete [] t8_a.table; 
    if (t8_b.table)
        delete [] t8_b.table;
    if (t8_c.table)
        delete [] t8_c.table;

 
    return 0;
}
