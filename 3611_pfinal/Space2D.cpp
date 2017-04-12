#include "Space2D.h"

InitCondition2D::InitCondition2D(Interval *intX, Interval *intY, double(*dist)(double, double), funcarr bounds[4]) :
	MatrixBase(intX->getDivisions(), intY->getDivisions())
{
	double
		sx = intX->getIncrement(),
		sy = intY->getIncrement(),
		ix = intX->getLeft(),
		iy = intY->getLeft();

	this->bounds = (bounds == NULL) ? NULL : new funcarr[4];
	this->intX = new Interval(intX);
	this->intY = new Interval(intY);

	/*
		Sets the boundaries and inner values of this problem.
	*/
	for (int i = 0; bounds != NULL && i < 4; i++)		*(this->bounds + i) = *(bounds + i);
	for (int i = 0; dist != NULL && i < N * M; i++)		*(V + i) = dist(sx * (i % N) + ix, sy * (i / N) + iy);
}

int InitCondition2D::getDivisionsX()
{
	return intX->getDivisions();
}

int InitCondition2D::getDivisionsY()
{
	return intY->getDivisions();
}

double InitCondition2D::getIncrementX()
{
	return intX->getIncrement();
}

double InitCondition2D::getIncrementY()
{
	return intY->getIncrement();
}

double InitCondition2D::getOffsetX()
{
	return intX->getLeft();
}

double InitCondition2D::getOffsetY()
{
	return intY->getLeft();
}

InitCondition2D::funcarr * InitCondition2D::getBounds()
{
	return bounds;
}

InitCondition2D::~InitCondition2D()
{
	delete[] bounds;
	delete intX;
	delete intY;
}

/*
	TABLE OBJECT
	***************************************
*/

Table2D::Table2D(InitCondition2D *IC) : MatrixBase(IC->N, IC->M)
{
	// Helper variables.
	double
		sx = IC->intX->getIncrement(),
		sy = IC->intY->getIncrement(),
		ix = IC->intX->getLeft(),
		iy = IC->intY->getLeft();

	/*
		Copies values from the initial conditions.
	*/
	for (int i = 0; i < N * M; i++)
	{
		*(V + i) = *(IC->V + i);
	}

	/*
		Updates all the bounds.
	*/
	if (IC->bounds != NULL)
	{
		// Top
		for (int i = 0; i < N; i++)
		{
			*(V + N * (M - 1) + i) = (*(IC->bounds))(i * sx + ix, Time::getTime());
		}

		// Bottom
		for (int i = 0; i < N; i++)
		{
			*(V + i) = (*(IC->bounds + 2))(i * sx + ix, Time::getTime());
		}

		// Right
		for (int j = 0; j < M; j++)
		{
			*(V + N * (j + 1) - 1) = (*(IC->bounds + 1))(j * sx + ix, Time::getTime());
		}

		// Left
		for (int j = 0; j < M; j++)
		{
			*(V + N * j) = (*(IC->bounds + 3))(j * sx + ix, Time::getTime());
		}
	}
}

Table2D::Table2D(Table2D *table, InitCondition2D *IC) : Table2D(IC)
{
	// Throw an error if the size of the table is incompatible with the initial conditions.
	if (IC->N != table->N || IC->M != table->M)
	{
		throw("Table initialized with table and initial condition of incompatible sizes!");
	}

	/*
		Copies all values from previous table, minus initial conditions.
	*/
	for (int i = N; i < N * (M - 1); i++)
	{
		if ((i + 1) % N == 0) i += 2;
		*(V + i) = *(table->V + i);
	}

}
