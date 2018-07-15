#include <ctime>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "sparse_matrix.h"

#define MAX_ROW 30
#define MAX_COL 30

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    srand((unsigned) time(NULL));
    unsigned t_id = 0;
    bool flag;

    SparseMatrix a, b;
    a.rows = rand() % MAX_ROW + 1;
    a.cols = rand() % MAX_COL+ 1;

    // init matrices
    rand(a);
    
    cout.setf(ios::fixed);
    cout << "Test Matrix A:" << endl;
    cout << "Size: " << a.rows << "x" << a.cols << endl;
    // print matrix a
    print(a);

    cout << "Matrix Transpose Result:" << endl;
    if (transpose(a, b))
    {
        cout << "Size: " << b.rows << "x" << b.cols << endl;
        print(b); 
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }

    cout << "Matrix Transpose Result(fast):" << endl;
    if (fastTranspose(a, b))
    {
        cout << "Size: " << b.rows << "x" << b.cols << endl;
        print(b); 
    }
    else
    {
        cout << "Incompatible Matrices!" << endl;
    }
    
    if (a.table)
        delete [] a.table; 
    if (b.table)
        delete [] b.table;
    
    // OpenCV Test
    Mat t1(512, 512, CV_64FC1);
    //Mat rst1(t1.size().height, t1.size().width, CV_64FC1);
    rectangle(t1, Point(100, 0), Point(200, 512), Scalar(255, 0, 0));
    imwrite("t1.jpg", t1);
    
    Matrix m_t1, m_rst1;
    m_t1.rows = t1.size().height;    m_t1.cols = t1.size().width;
    m_t1.data = (double*)t1.data;

    SparseMatrix sm_t1, sm_rst1;
    Nor2Spa(m_t1, sm_t1);
    fastTranspose(sm_t1, sm_rst1);
    Spa2Nor(sm_rst1, m_rst1); 
    Mat rst1(t1.size().height, t1.size().width, CV_64FC1, m_rst1.data);
    imwrite("rst1.jpg", rst1);

    return 0;
}
