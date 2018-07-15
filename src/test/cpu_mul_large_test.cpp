#include <ctime>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "sparse_matrix.h"

#define MAX_ROW 10
#define MAX_COL 10

using namespace std;
using namespace cv; 
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " height " << "width" << endl;
        return -1;
    }
    unsigned w = atoi(argv[2]), h = atoi(argv[1]);
    Mat t1(h, w, CV_64FC1), t2(h, w, CV_64FC1);
    //Mat rst1(t1.size().height, t1.size().width, CV_64FC1);
    //rectangle(t1, Point(100, 0), Point(200, 512), Scalar(255, 0, 0));
    line(t1, Point(0, h / 2), Point(w, h / 2), Scalar(10, 0, 0), 100);
    rectangle(t2, Point(0, 0), Point(w, h), Scalar(30, 0, 0), -1);

    imwrite("t1.jpg", t1);
    imwrite("t2.jpg", t2);

    Matrix m_t1, m_t2, m_rst1;
    m_t1.rows = t1.size().height;    m_t1.cols = t1.size().width;
    m_t1.data = (double*)t1.data;
    m_t2.rows = t2.size().height;    m_t2.cols = t2.size().width;
    m_t2.data = (double*)t2.data;

    SparseMatrix sm_t1, sm_t2, sm_rst1;

    Nor2Spa(m_t1, sm_t1);
    Nor2Spa(m_t2, sm_t2);
    clock_t start = clock();
    mul(sm_t1, sm_t2, sm_rst1);
    clock_t stop = clock();
    Spa2Nor(sm_rst1, m_rst1);
    Mat rst1(m_rst1.rows, m_rst1.cols, CV_64FC1, m_rst1.data);
    imwrite("rst1.jpg", rst1); 
    cout << "elapsed time: " << (double)(stop - start) / CLOCKS_PER_SEC << "secs" << endl;

    return 0;
}
