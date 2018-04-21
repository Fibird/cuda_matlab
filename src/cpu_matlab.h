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

// Add two matrices and returns matrix c
// a - left matrix 
// b - right matrix
// c - result Matrix
bool add(const Matrix a, const Matrix b, Matrix &c);
// Subtracts matrix b from matrix a and return matrix c
// a - left matrix
// b - right matrix
// c - result matrix
bool sub(const Matrix a, const Matrix b, Matrix &c);
// Matrix a multiplies matrix b and returns matrix c
// a - left matrix
// b - right matrix
// c - result matrix
bool mul(const Matrix a, const Matrix b, Matrix &c);
// Matrix a multiplies a number by elements
// a - left matrix
// b - a number
// c - result matrix
bool mul(const Matrix a, const double b, Matrix &c);
// Transpose matrix
// a - operated matrix
// b - result matrix
bool transpose(const Matrix a, Matrix &b);
// Initialize matrix with zeros
// a - matrix a
void zeros(Matrix &a);
// Initialize matrix with ones
// a - matrix a
void ones(Matrix &a);
// Initialize matrix with random numbers
// a - matrix a
void rand(Matrix &a);
// Print matrix a
// a - matrix a
void print(const Matrix a);

// Check validation of matrix
// m - Matrix
bool check(const Matrix &m);
/*---------------- Special Matrix ----------------*/
struct trituple
{
    unsigned row, col;
    double value;
};

// print trituple
// t - trituple
void print(const trituple t);

struct SparseMatrix
{
    unsigned rows, cols;
    unsigned terms;
    trituple *table;
};
// Add two sparse matrices and returns sparse matrix
// a - left sparse matrix
// b - right sparse matrix 
// c - result sparse matrix 
bool add(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c);
// Add sparse matrix and normal matrix and returns matrix
// a - left sparse matrix
// b - right matrix
// c - result matrix
bool add(const SparseMatrix a, const Matrix b, Matrix &c);
// Subtracts sparse matrix b from sparse matrix a and returns sparse matrix c
// a - left sparse matrix
// b - right sparse matrix
// c - result sparse matrix
bool sub(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c);
// Subtracts matrix b from sparse matrix a and returns matrix c
// a - left sparse matrix
// b - right matrix b
// c - result matrix
bool sub(const SparseMatrix a, const Matrix b, Matrix &c);
// Sparse matrix a multiplies sparse matrix b and returns sparse matrix c
// a - left sparse matrix
// b - right sparse matrix
// c - result sparse matrix
bool mul(const SparseMatrix a, const SparseMatrix b, SparseMatrix &c);
// Sparse matrix multiplies matrix b and returns sparse matrix c
// a - left sparse matrix
// b - right matrix 
// c - result sparse matrix
bool mul(const SparseMatrix a, const Matrix b, SparseMatrix &c);
// Sparse matrix a multiplies matrix b and returns matrix c
// a - left sparse matrix
// b - right matrix
// c - result matrix
bool mul(const SparseMatrix a, const Matrix b, Matrix &c);
// Sparse matrix a multiplies a number by element
// a - left sparse matrix
// b - a number
// c - result sparse matrix
bool mul(const SparseMatrix a, const double b, SparseMatrix &c);
// Transpose sparse matrix
// a - sparse matrix
// b - result matrix
bool transpose(const SparseMatrix a, SparseMatrix &b);
// A fast way transposing sparse matrix
// a - sparse matrix
// b - result matrix
bool fastTranspose(const SparseMatrix a, SparseMatrix &b);
// Transform sparse matrix to normal matrix
// a - sparse matrix
// b - normal matrix
bool Spa2Nor(const SparseMatrix a, Matrix &b);
// Transform normal matrix to sparse matrix
// a - normal matrix 
// b - sparse matrix
bool Nor2Spa(const Matrix a, SparseMatrix &b);
// Initialize sparse matrix with random term and random numbers
// a - sparse matrix a
void rand(SparseMatrix &a);
// Initialize sparse matrix with zeros
// a - sparse matrix
void zeros(SparseMatrix &a);
// Print sparse matrix
// a - sparse matrix
void print(const SparseMatrix a);
// Check validation of sparse matrix
// sm - Sparse matrix
bool check(const SparseMatrix &sm);
