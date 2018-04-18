#include <iostream>
#include <cstdlib>
#include <ctime>
#include "cpu_matlab.h"

using namespace std;

#define MAX_ROW 30
#define MAX_COL 30

int main(int argc, char **argv)
{
    Matrix a, b, c;
    SparseMatrix d;
    srand((unsigned) time(NULL));
    a.rows = rand() % MAX_ROW + 1;
    a.cols = rand() % MAX_COL + 1;
    b.rows = rand() % MAX_ROW + 1;
    b.cols = rand() % MAX_COL + 1;
    c.rows = rand() % MAX_ROW + 1;
    c.cols = rand() % MAX_COL + 1;
    d.rows = rand() % MAX_ROW + 1;
    d.cols = rand() % MAX_COL + 1;
    
    // test for ones function
    ones(a);
    cout << "Matrix a = " << endl;
    print(a);
    // test for zeros function
    zeros(b);
    cout << "Matrix b = " << endl;
    print(b);
    // test for rand function(normal matrix)
    rand(c);
    cout << "Matrix c = " << endl;
    print(c);

    // test for rand function(sparse matrix)
    rand(d);
    cout << "Sparse Matrix d = " << endl;
    print(d);

    return 0;
}
