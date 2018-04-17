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
bool add(const Matrix a, const Matrix b, Matrix &c);
//  Subtraction Operation Declaration
//      a - left matrix
//      b - right matrix
//      c - result matrix
bool sub(const Matrix a, const Matrix b, Matrix &c);
//  Multiplication Operation Declaration
//      a - left matrix
//      b - right matrix
//      c - result matrix
bool mul(const Matrix a, const Matrix b, Matrix &c);
//  Multiplication Operation Declaration
//      a - left matrix
//      b - right matrix
//      c - result matrix
bool mul(const Matrix a, const double b, Matrix &c);
//  Matrix Transpose Operation Declaration
//      a - operated matrix
//      b - result matrix
bool transpose(const Matrix a, Matrix &b);

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

bool add(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c);
bool add(const SparseMatrix a, const Matrix b, Matrix &c);
bool sub(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c);
bool sub(const SparseMatrix a, const Matrix b, Matrix &c);
bool mul(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c);
bool mul(const SparseMatrix a, const Matrix b, SparseMatrix &c);
bool mul(const SparseMatrix a, const Matrix b, Matrix &c);
bool mul(const SparseMatrix a, const double b, SparseMatrix &c);
bool transpose(const SparseMatrix a, SparseMatrix &b);
bool fastTranspose(const SparseMatrix a, SparseMatrix &b);
bool Spa2Nor(const SparseMatrix a, Matrix &b);
bool Nor2Spa(const Matrix a, SparseMatrix &b);
