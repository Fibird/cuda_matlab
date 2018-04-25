#include "matrix.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    Matrix t1_a, t1_b, t1_c;

    t1_a.rows = 10; t1_a.cols = 9;
    rand(t1_a);
    t1_b.rows = 10; t1_b.cols = 9;
    rand(t1_b);

    pow(t1_a, t1_b, t1_c);

    cout << "-------------Test 1 for Matrix pow-------------" << endl;
    cout << "Matrix a: " << endl;
    cout << "Size: " << t1_a.rows << "x" << t1_a.cols << endl;
    print(t1_a);

    cout << "Matrix b: " << endl;
    cout << "Size: " << t1_b.rows << "x" << t1_b.cols << endl;
    print(t1_b);

    cout << "Result Matrix c: " << endl;
    cout << "Size: " << t1_c.rows << "x" << t1_c.cols << endl;
    print(t1_c);

    // free memory
    if (t1_a.data)
        delete t1_a.data;
    if (t1_b.data)
        delete t1_b.data;
    if (t1_c.data)
        delete t1_c.data;


    Matrix t2_a, t2_b, t2_c;

    t2_a.rows = 10; t2_a.cols = 9;
    rand(t2_a);
    t2_b.rows = 10; t2_b.cols = 9;
    zeros(t2_b);

    pow(t2_a, t2_b, t2_c);

    cout << "-------------Test 2 for Matrix pow-------------" << endl;
    cout << "Matrix a: " << endl;
    cout << "Size: " << t2_a.rows << "x" << t2_a.cols << endl;
    print(t2_a);

    cout << "Matrix b: " << endl;
    cout << "Size: " << t2_b.rows << "x" << t2_b.cols << endl;
    print(t2_b);

    cout << "Result Matrix c: " << endl;
    cout << "Size: " << t2_c.rows << "x" << t2_c.cols << endl;
    print(t2_c);

    // free memory
    if (t2_a.data)
        delete t2_a.data;
    if (t2_b.data)
        delete t2_b.data;
    if (t2_c.data)
        delete t2_c.data;
    
    Matrix t3_a, t3_b, t3_c;

    t3_a.rows = 10; t3_a.cols = 9;
    zeros(t3_a);
    t3_b.rows = 10; t3_b.cols = 9;
    rand(t3_b);

    pow(t3_a, t3_b, t3_c);
    cout << "-------------Test 3 for Matrix pow-------------" << endl;
    cout << "Matrix a: " << endl;
    cout << "Size: " << t3_a.rows << "x" << t3_a.cols << endl;
    print(t3_a);

    cout << "Matrix b: " << endl;
    cout << "Size: " << t3_b.rows << "x" << t3_b.cols << endl;
    print(t3_b);

    cout << "Result Matrix c: " << endl;
    cout << "Size: " << t3_c.rows << "x" << t3_c.cols << endl;
    print(t3_c);

    // free memory
    if (t3_a.data)
        delete t3_a.data;
    if (t3_b.data)
        delete t3_b.data;
    if (t3_c.data)
        delete t3_c.data;

    Matrix t4_a, t4_b, t4_c;

    t4_a.rows = 10; t4_a.cols = 9;
    zeros(t4_a);
    t4_b.rows = 10; t4_b.cols = 9;
    zeros(t4_b);

    pow(t4_a, t4_b, t4_c);
    cout << "-------------Test 4 for Matrix pow-------------" << endl;
    cout << "Matrix a: " << endl;
    cout << "Size: " << t4_a.rows << "x" << t4_a.cols << endl;
    print(t4_a);

    cout << "Matrix b: " << endl;
    cout << "Size: " << t4_b.rows << "x" << t4_b.cols << endl;
    print(t4_b);

    cout << "Result Matrix c: " << endl;
    cout << "Size: " << t4_c.rows << "x" << t4_c.cols << endl;
    print(t4_c);

    // free memory
    if (t4_a.data)
        delete t4_a.data;
    if (t4_b.data)
        delete t4_b.data;
    if (t4_c.data)
        delete t4_c.data;
    return 0;
}
