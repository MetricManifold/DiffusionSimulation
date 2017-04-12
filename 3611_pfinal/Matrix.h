#pragma once

#include <exception>

#include "MatrixBase.h"

/*
	This matrix class mimics the basic functionality of any
	usual 1 or 2 dimensional matrix. It was added in case such
	functionality was needed for this project.
*/
class Matrix : public MatrixBase
{ 
public:
	Matrix(const int, const int, bool);

	// Matrix operator overloads.

	Matrix &operator=(const Matrix &);

	Matrix &operator+=(const Matrix &);
	Matrix &operator+(const Matrix &);
	Matrix &operator-=(const Matrix &);
	Matrix &operator-(const Matrix &);
	Matrix &operator*=(const Matrix &);
	Matrix &operator*(const Matrix &);

	bool operator==(const Matrix &);
	bool operator!=(const Matrix &);
};