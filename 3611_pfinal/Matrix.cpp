#include "Matrix.h"

inline Matrix::Matrix(const int N, const int M, bool identity = false) : MatrixBase(N, M)
{
	if (identity && N == M)
	{
		for (int i = 0; i < N * N; i += N + 1)
		{
			*(V + i) = 1;
		}
	}
}

Matrix &Matrix::operator=(const Matrix &m)
{
	// Must check for self-assignment due to memory allocation.
	if (this == &m)
	{
		return *this;
	}

	// Assign all values for the new object.
	for (int i = 0; i < N * M; i++)
	{
		*(this->V + i) = m.V[i];
	}

	return *this;
}

Matrix &Matrix::operator+=(const Matrix &m)
{
	for (int i = 0; i < N * M; i++)
	{
		*(this->V + i) += m.V[i];
	}

	return *this;
}

Matrix &Matrix::operator+(const Matrix &m)
{
	return Matrix(*this) += m;
}

Matrix &Matrix::operator-=(const Matrix &m)
{
	for (int i = 0; i < N * M; i++)
	{
		*(this->V + i) -= m.V[i];
	}

	return *this;
}

Matrix &Matrix::operator-(const Matrix &m)
{
	return Matrix(*this) -= m;
}

Matrix &Matrix::operator*=(const Matrix &m)
{
	if (this->N != m.M)
	{
		throw("Matrices not compatible for multiplication");
	}

	for (int o = 0; o < N * M; o++)
	{
		double dot = 0;

		for (int i = 0; i < this->N; i++)
		{
			dot += *(this->V + i) * m.V[i];
		}

		*(this->V + o) = dot;
	}
	
	

	return *this;
}

Matrix &Matrix::operator*(const Matrix &m)
{
	return Matrix(*this) *= m;
}

bool Matrix::operator==(const Matrix &m)
{
	// Checks whether both instances of numbers are the same.
	for (int i = 0; i < N * M; i++)
	{
		if (*(this->V + i) != m.V[i])
			return false;
	}
	
	return true;
}

bool Matrix::operator!=(const Matrix &m)
{
	return !(*this == m);
}
