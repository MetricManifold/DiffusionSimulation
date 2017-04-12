#pragma once

#include <utility>
#include <iostream>

struct MatrixBase
{
public:
	/*
		Creates the 2 dimensional MatrixAbstract which stores values.

		@param number of columns
		@param number of rows
	*/
	MatrixBase(const int, const int);
	~MatrixBase();

	double *V;		// Values of the matrix.

	const int N;	// Width of MatrixAbstract.
	const int M;	// Height of MatrixAbstract.
};
