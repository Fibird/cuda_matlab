#include <iostream>
#include "sparse_matrix.h"

using namespace std;

int main(int argc, char **argv)
{
    SparseMatrix t1_a, t1_b;
    Matrix t1_c;

    t1_a.rows = 9;  t1_a.cols = 9;
    rand(t1_a);

    t1_b.rows = 9;  t1_b.cols = 9;
    rand(t1_b);

    pow(t1_a, t1_b, t1_c);
    cout << "-------------Test 1 for Sparse Matrix Pow------------" << endl;
    cout << "Sparse Matrix a:" << endl;
    cout << "Size: " << t1_a.rows << "x" << t1_a.cols << endl;
    print(t1_a);

    cout << "Sparse Matrix b: " << endl;
    cout << "Size: " << t1_b.rows << "x" << t1_b.cols << endl;
    print(t1_b);

    cout << "Result Matrix c: " << endl;
    cout << "Size: " << t1_c.rows << "x" << t1_c.cols << endl;
    print(t1_c);

    if (t1_a.table)
        delete t1_a.table;
    if (t1_b.table)
        delete t1_b.table;
    if (t1_c.data)
        delete t1_c.data;

    SparseMatrix t2_a, t2_b;
    Matrix t2_c;

    t2_a.rows = 9;  t2_a.cols = 9;
    zeros(t2_a);

    t2_b.rows = 9;  t2_b.cols = 9;
    zeros(t2_b);

    pow(t2_a, t2_b, t2_c);
    cout << "-------------Test 2 for Sparse Matrix Pow------------" << endl;
    cout << "Sparse Matrix a:" << endl;
    cout << "Size: " << t2_a.rows << "x" << t2_a.cols << endl;
    print(t2_a);

    cout << "Sparse Matrix b: " << endl;
    cout << "Size: " << t2_b.rows << "x" << t2_b.cols << endl;
    print(t2_b);

    cout << "Result Matrix c: " << endl;
    cout << "Size: " << t2_c.rows << "x" << t2_c.cols << endl;
    print(t2_c);

    if (t2_a.table)
        delete t2_a.table;
    if (t2_b.table)
        delete t2_b.table;
    if (t2_c.data)
        delete t2_c.data;

    SparseMatrix t3_a, t3_b;
    Matrix t3_c;

    t3_a.rows = 9;  t3_a.cols = 9;
    zeros(t3_a);

    t3_b.rows = 9;  t3_b.cols = 9;
    rand(t3_b);

    pow(t3_a, t3_b, t3_c);
    cout << "-------------Test 3 for Sparse Matrix Pow------------" << endl;
    cout << "Sparse Matrix a:" << endl;
    cout << "Size: " << t3_a.rows << "x" << t3_a.cols << endl;
    print(t3_a);

    cout << "Sparse Matrix b: " << endl;
    cout << "Size: " << t3_b.rows << "x" << t3_b.cols << endl;
    print(t3_b);

    cout << "Result Matrix c: " << endl;
    cout << "Size: " << t3_c.rows << "x" << t3_c.cols << endl;
    print(t3_c);

    if (t3_a.table)
        delete t3_a.table;
    if (t3_b.table)
        delete t3_b.table;
    if (t3_c.data)
        delete t3_c.data;

    SparseMatrix t4_a, t4_b;
    Matrix t4_c;

    t4_a.rows = 9;  t4_a.cols = 9;
    rand(t4_a);

    t4_b.rows = 9;  t4_b.cols = 9;
    zeros(t4_b);

    pow(t4_a, t4_b, t4_c);
    cout << "-------------Test 3 for Sparse Matrix Pow------------" << endl;
    cout << "Sparse Matrix a:" << endl;
    cout << "Size: " << t4_a.rows << "x" << t4_a.cols << endl;
    print(t4_a);

    cout << "Sparse Matrix b: " << endl;
    cout << "Size: " << t4_b.rows << "x" << t4_b.cols << endl;
    print(t4_b);

    cout << "Result Matrix c: " << endl;
    cout << "Size: " << t4_c.rows << "x" << t4_c.cols << endl;
    print(t4_c);

    if (t4_a.table)
        delete t4_a.table;
    if (t4_b.table)
        delete t4_b.table;
    if (t4_c.data)
        delete t4_c.data;
    return 0;
}
