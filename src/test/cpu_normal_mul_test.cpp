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

    t1_a.data = new double[t1_a.rows * t1_a.cols];
    t1_b.data = new double[t1_b.rows * t1_b.cols];
    // init matrices
    for (unsigned i = 0; i < t1_a.rows * t1_a.cols; ++i)
        t1_a.data[i] = (double)rand() / (double) RAND_MAX;

    for (unsigned i = 0; i < t1_b.rows * t1_b.cols; ++i)
        t1_b.data[i] = (double)rand() / (double) RAND_MAX;
    
    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << t1_a.rows << "x" << t1_a.cols << endl;

    for (unsigned i = 0; i < t1_a.rows; ++i)
    {
        for (unsigned j = 0; j < t1_a.cols; ++j)
            cout << setprecision(2) << t1_a.data[i * t1_a.cols +j] << " "; 
        cout << endl;
    }
    

    cout << "Test Matrix B:" << endl;
    cout << "Size: " << t1_b.rows << "x" << t1_b.cols << endl;
    for (unsigned i = 0; i < t1_b.rows; ++i)
    {
        for (unsigned j = 0; j < t1_b.cols; ++j)
            cout << setprecision(2) << t1_b.data[i * t1_b.cols +j] << " "; 
        cout << endl;
    }
    

    cout << "Vector Multiplication Test Result:" << endl;
    if (mul(t1_a, t1_b, t1_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t1_c.rows << "x" << t1_c.cols << endl;
        for (unsigned i = 0; i < t1_c.rows; ++i)
        {
            for (unsigned j = 0; j < t1_c.cols; ++j)
                cout << setprecision(2) << t1_c.data[i * t1_c.cols +j] << " "; 
            cout << endl;
        }
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }
    
    double test_num = (double) rand() / (double) RAND_MAX;
    cout << "Test Data B: " << test_num << endl;
    cout << "Scalar Multiplication Test Result:" << endl;
    if (mul(t1_a, test_num, t1_c))
    {
        cout << "Get result Matrix C:" << endl;
        cout << "Size: " << t1_c.rows << "x" << t1_c.cols << endl;
        for (unsigned i = 0; i < t1_c.rows; ++i)
        {
            for (unsigned j = 0; j < t1_c.cols; ++j)
                cout << setprecision(2) << t1_c.data[i * t1_c.cols +j] << " "; 
            cout << endl;
        }
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
