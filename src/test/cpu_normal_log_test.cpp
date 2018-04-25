#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include "sparse_matrix.h"

using namespace std;

int main(int argc, char **argv)
{
    Matrix t1_a, t1_b;
    t1_a.rows = 8; t1_a.cols = 9;

    // init matrices
    rand(t1_a);
    
    cout << "------------Test 1 for Matrix log--------------" << endl;
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t1_a.rows << "x" << t1_a.cols << endl;
    // print matrix t1_a
    print(t1_a);

    cout << "Matrix log Result:" << endl;
    if (log(t1_a, t1_b))
    {
        cout << "Size: " << t1_b.rows << "x" << t1_b.cols << endl;
        print(t1_b); 
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }
    
    delete [] t1_a.data; 
    delete [] t1_b.data;
    
    cout << "------------Test 2 for Matrix log--------------" << endl;
    Matrix t2_a, t2_b;
    t2_a.rows = 8; t2_a.cols = 9;

    // init matrices
    zeros(t2_a);
    
    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t2_a.rows << "x" << t2_a.cols << endl;
    // print matrix t2_a
    print(t2_a);

    cout << "Matrix log Result:" << endl;
    if (log(t2_a, t2_b))
    {
        cout << "Size: " << t2_b.rows << "x" << t2_b.cols << endl;
        print(t2_b); 
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }
    
    delete [] t2_a.data; 
    delete [] t2_b.data;

    cout << "------------Test 3 for Matrix log--------------" << endl;
    Matrix t3_a, t3_b;
    t3_a.rows = 8; t3_a.cols = 9;

    // init matrices
    rand(t3_a);
    t3_a.data[5] = 0;
    
    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t3_a.rows << "x" << t3_a.cols << endl;
    // print matrix t3_a
    print(t3_a);

    cout << "Matrix log Result:" << endl;
    if (log(t3_a, t3_b))
    {
        cout << "Size: " << t3_b.rows << "x" << t3_b.cols << endl;
        print(t3_b); 
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }
    
    delete [] t3_a.data; 
    delete [] t3_b.data;
    return 0;
}
