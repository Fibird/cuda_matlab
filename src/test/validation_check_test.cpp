#include <iostream>
#include "sparse_matrix.h"

using namespace std;

int main()
{
    int test_id = 0;

    Matrix a;
    test_id++;
    a.rows = 0;
    a.cols = 3;
    a.data = new double[a.rows * a.cols];
    cout << "-----------Result of Test " << test_id << "-----------" << endl;
    if (check(a))
        cout << "valid matrix." << endl;

    Matrix b;
    test_id++;
    b.rows = 3;
    b.cols = 4;
    b.data = NULL;
    cout << "-----------Result of Test " << test_id << "-----------" << endl;
    if (check(b))
        cout << "valid matrix." << endl;

    Matrix c;
    test_id++;
    c.rows = 3;
    c.cols = 0;
    c.data = new double[c.rows * c.cols];
    cout << "-----------Result of Test " << test_id << "-----------" << endl;
    if (check(c))
        cout << "valid matrix." << endl;

    Matrix d;
    test_id++;
    d.rows = 0;
    d.cols = 0;
    d.data = new double[d.rows * d.cols];
    cout << "-----------Result of Test " << test_id << "-----------" << endl;
    if (check(d))
        cout << "valid matrix." << endl;
    
    Matrix td;
    test_id++;
    td.rows = 5;
    td.cols = 7;
    td.data = new double[td.rows * td.cols];
    cout << "-----------Result of Test " << test_id << "-----------" << endl;
    if (check(td))
        cout << "valid matrix." << endl;


    SparseMatrix e;
    test_id++;
    e.rows = 0;
    e.cols = 0;
    e.terms = 0;
    e.table = new trituple[e.terms];
    cout << "-----------Result of Test " << test_id << "-----------" << endl;
    if (check(e))
        cout << "valid sparse matrix." << endl;
    
    SparseMatrix f;
    test_id++;
    f.rows = 0;
    f.cols = 3;
    f.terms = 0;
    f.table = new trituple[f.terms];
    cout << "-----------Result of Test " << test_id << "-----------" << endl;
    if (check(f))
        cout << "valid sparse matrix." << endl;


    SparseMatrix g;
    test_id++;
    g.rows = 3;
    g.cols = 0;
    g.terms = 0;
    g.table = new trituple[g.terms];
    cout << "-----------Result of Test " << test_id << "-----------" << endl;
    if (check(g))
        cout << "valid sparse matrix." << endl;

    SparseMatrix h;
    test_id++;
    h.rows = 4;
    h.cols = 6;
    h.terms = 0;
    h.table = new trituple[h.terms];
    cout << "-----------Result of Test " << test_id << "-----------" << endl;
    if (check(h))
        cout << "valid sparse matrix." << endl;

    SparseMatrix i;
    test_id++;
    i.rows = 5;
    i.cols = 6;
    i.terms = 4;
    i.table = NULL;
    cout << "-----------Result of Test " << test_id << "-----------" << endl;
    if (check(i))
        cout << "valid sparse matrix." << endl;

    SparseMatrix j;
    test_id++;
    j.rows = 7;
    j.cols = 9;
    j.terms = 5;
    j.table = new trituple[j.terms];
    cout << "-----------Result of Test " << test_id << "-----------" << endl;
    if (check(j))
        cout << "valid sparse matrix." << endl;

    return 0;
}
