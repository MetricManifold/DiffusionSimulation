
#include "MatrixBase.h"

#include <iostream>

MatrixBase::MatrixBase(const int N, const int M) : N{ N }, M{ M }
{
	if (N == 0 || M == 0)
	{
		throw("Malformed Matrix, one or both dimensions are 0.");
	}

	V = new double[N * M];
	std::fill(V, V + N * M, 0);
}

MatrixBase::~MatrixBase()
{
	delete[] V;
}
