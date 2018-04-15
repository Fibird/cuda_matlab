struct Matrix
{
    unsigned rows;
    unsigned cols;
    double *data;
};

void add(const Matrix a, const Matrix b, Matrix c);
void sub(const Matrix a, const Matrix b, Matrix c);
void mul(const Matrix a, const Matrix b, Matrix c);
void mul(const Matrix a, const double b, Matrix c);
void transpose(const Matrix a, Matrix b);

