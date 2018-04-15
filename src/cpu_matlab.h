/**
 * Author: Liu Chaoyang
 * E-mail: chaoyanglius@gmail.com
 * 
 * Some operations of Matrices using C++
 * Copyright (C) 2018 Liu Chaoyang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
/*---------------- Normal Matrix ----------------*/
struct Matrix
{
    unsigned rows;
    unsigned cols;
    double *data;
};

//  Addition Operation Declaration 
//      a - left matrix 
//      b - right matrix
//      c - result Matrix
void add(const Matrix a, const Matrix b, Matrix c);
//  Subtraction Operation Declaration
//      a - left matrix
//      b - right matrix
//      c - result matrix
void sub(const Matrix a, const Matrix b, Matrix c);
//  Multiplication Operation Declaration
//      a - left matrix
//      b - right matrix
//      c - result matrix
void mul(const Matrix a, const Matrix b, Matrix c);
//  Multiplication Operation Declaration
//      a - left matrix
//      b - right matrix
//      c - result matrix
void mul(const Matrix a, const double b, Matrix c);
//  Matrix Transpose Operation Declaration
//      a - operated matrix
//      b - result matrix
void transpose(const Matrix a, Matrix b);

/*---------------- Special Matrix ----------------*/
struct trituple
{
    unsigned row, col;
    double value;
};

struct SparseMatrix
{
    unsigned rows, cols;
    unsigned terms;
    trituple *table;
};

void add(const SparseMatrix a, const SparseMatrix b, SparseMatrix c);
void add(const SparseMatrix a, const Matrix b, Matrix c);
void sub(const SparseMatrix a, const SparseMatrix b, SparseMatrix c);
void sub(const SparseMatrix a, const Matrix b, Matrix c);
void mul(const SparseMatrix a, const SparseMatrix b, SparseMatrix c);
void mul(const SparseMatrix a, const Matrix b, SparseMatrix c);
void mul(const SparseMatrix a, const Matrix b, Matrix c);
void mul(const SparseMatrix a, const double b, SparseMatrix c);
void transpose(const SparseMatrix a, SparseMatrix b);
void Spa2Nor(const SparseMatrix a, Matrix b);
void Nor2Spa(const Matrix a, SparseMatrix b);
