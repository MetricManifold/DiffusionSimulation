#include "Space1D.h"

InitCondition1D::InitCondition1D(Interval *interval, double(*dist)(double), funcarr bounds[2]) :
	MatrixBase(interval->getDivisions(), 1)
{
	this->bounds = (bounds == NULL) ? NULL : new funcarr[2];
	this->interval = new Interval(interval->getLeft(), interval->getRight());

	/*
		Sets the inner and boundary values of this problem.
	*/
	for (int i = 0; dist != NULL && i < N; i++)		*(V + i) = dist(interval->getIncrement() * i + interval->getLeft());
	for (int i = 0; bounds != NULL && i < 2; i++)	*(this->bounds + i) = *(bounds + i);
}

int InitCondition1D::getDivisions()
{
	return interval->getDivisions();
}

double InitCondition1D::getIncrement()
{
	return interval->getIncrement();
}

double InitCondition1D::getOffset()
{
	return interval->getLeft();
}

InitCondition1D::funcarr * InitCondition1D::getBounds()
{
	return bounds;
}

InitCondition1D::~InitCondition1D()
{
	delete[] bounds;
	delete interval;
}

/*
	TABLE OBJECT
	***************************************
*/

Table1D::Table1D(InitCondition1D *IC) : MatrixBase(IC->N, 1)
{
	/*
		Copies all values from the initial conditions.
	*/
	for (int i = 0; i < N * M; i++)
	{
		*(V + i) = *(IC->V + i);
	}
	
	/*
		Sets the boundaries of the problem.
	*/
	if (IC->bounds != NULL)
	{
		*V = (*IC->bounds)(Time::getTime());
		*(V + N) = (*(IC->bounds + 1))(Time::getTime());
	}
}

Table1D::Table1D(Table1D *table, InitCondition1D *IC) : Table1D(IC)
{
	// Throw an error if the size of the table is incompatible with the initial conditions.
	if (IC->N != table->N)
	{
		throw("Table initialized with table and initial condition of incompatible sizes!");
	}

	/*
		Copies all values from previous table minus boundary conditions.
	*/
	for (int i = 1; i < N - 1; i++)
	{
		*(V + i) = *(table->V + i);
	}

}