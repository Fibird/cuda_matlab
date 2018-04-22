#include "cpu_matlab.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    unsigned t_id = 0;
    
    /////// Test Case 1 //////// 
    Matrix t1_a,  t1_c;
    t1_a.rows = 6;  t1_a.cols = 7;
    SparseMatrix t1_b;
    t1_b.rows = 6;  t1_b.cols = 7;

    // init matrices
    rand(t1_a);
    rand(t1_b);
    t_id++;
    cout << "-------------Test " << t_id << "-------------" << endl;
    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t1_a.rows << "x" << t1_a.cols << endl;
    // print matrix a
    print(t1_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t1_b.rows << "x" << t1_b.cols << endl;
    // print matrix b
    print(t1_b);

    cout << "Addition Test Result:" << endl;
    if (add(t1_b, t1_a, t1_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t1_c.rows << "x" << t1_c.cols << endl;
        // print matrix c
        print(t1_c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }
    
     
    if (t1_a.data) 
        delete [] t1_a.data; 
    if (t1_b.table)
        delete [] t1_b.table;
    if (t1_c.data)
        delete [] t1_c.data;

    Matrix t2_a,  t2_c;
    t2_a.rows = 6;  t2_a.cols = 7;
    SparseMatrix t2_b;
    t2_b.rows = 6;  t2_b.cols = 7;

    // init matrices
    zeros(t2_a);
    zeros(t2_b);

    t_id++; 
    cout << "-------------Test " << t_id << "-------------" << endl;
    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t2_a.rows << "x" << t2_a.cols << endl;
    // print matrix a
    print(t2_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t2_b.rows << "x" << t2_b.cols << endl;
    // print matrix b
    print(t2_b);

    cout << "Addition Test Result:" << endl;
    if (add(t2_b, t2_a, t2_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t2_c.rows << "x" << t2_c.cols << endl;
        // print matrix c
        print(t2_c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }
    
     
    if (t2_a.data) 
        delete [] t2_a.data; 
    if (t2_b.table)
        delete [] t2_b.table;
    if (t2_c.data)
        delete [] t2_c.data;
    
    Matrix t3_a,  t3_c;
    t3_a.rows = 6;  t3_a.cols = 7;
    SparseMatrix t3_b;
    t3_b.rows = 6;  t3_b.cols = 7;

    // init matrices
    zeros(t3_a);
    rand(t3_b);
    
    t_id++; 
    cout << "-------------Test " << t_id << "-------------" << endl;
    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t3_a.rows << "x" << t3_a.cols << endl;
    // print matrix a
    print(t3_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t3_b.rows << "x" << t3_b.cols << endl;
    // print matrix b
    print(t3_b);

    cout << "Addition Test Result:" << endl;
    if (add(t3_b, t3_a, t3_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t3_c.rows << "x" << t3_c.cols << endl;
        // print matrix c
        print(t3_c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }
    
     
    if (t3_a.data) 
        delete [] t3_a.data; 
    if (t3_b.table)
        delete [] t3_b.table;
    if (t3_c.data)
        delete [] t3_c.data;

    Matrix t4_a,  t4_c;
    t4_a.rows = 6;  t4_a.cols = 7;
    SparseMatrix t4_b;
    t4_b.rows = 6;  t4_b.cols = 7;

    // init matrices
    rand(t4_a);
    zeros(t4_b);
    
    t_id++; 
    cout << "-------------Test " << t_id << "-------------" << endl;
    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t4_a.rows << "x" << t4_a.cols << endl;
    // print matrix a
    print(t4_a);

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t4_b.rows << "x" << t4_b.cols << endl;
    // print matrix b
    print(t4_b);

    cout << "Addition Test Result:" << endl;
    if (add(t4_b, t4_a, t4_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t4_c.rows << "x" << t4_c.cols << endl;
        // print matrix c
        print(t4_c);
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }
    
     
    if (t4_a.data) 
        delete [] t4_a.data; 
    if (t4_b.table)
        delete [] t4_b.table;
    if (t4_c.data)
        delete [] t4_c.data;

    return 0;
}
