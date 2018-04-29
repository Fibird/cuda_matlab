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
 
#ifndef MATRIX_H
#define MATRIX_H
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

// Matrix a multiplies a number by elements
// b - a number
// a - left matrix
// c - result matrix
bool mul(const double b, const Matrix a, Matrix &c);

// Get the natural logarithm ln(a) of each element
// a - input matrix
// b - result matrix
bool log(const Matrix a, Matrix &b);

// Element-wise power
// a - base matrix
// b - exponent matrix
// b - result matrix
bool pow(const Matrix a, const Matrix b, Matrix &c);

// Transpose matrix
// a - operated matrix
// b - result matrix
bool transpose(const Matrix a, Matrix &b);

// Calculate determinant of matrix
// a - input square matrix
// d - determinant of matrix
bool det(const Matrix a, double &d);

// Solve linear systems
// a - coefficient matrix
// b - constant terms
// set - solution set
bool lup(const Matrix a, const double *b, double *&set);

// Matrix inverse
// a - input matrix
// b - inverse of matrix a
bool inv(const Matrix a, Matrix &b);

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
#endif
