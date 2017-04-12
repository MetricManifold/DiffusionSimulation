#pragma once

#include "MatrixBase.h"
#include "Interval.h"
#include "ModelBase.h"
#include "Functions.h"

/*
	Contains all the necessary initial conditions for a 2
	dimensional problem.
*/
struct InitCondition2D : public MatrixBase
{
	friend struct Table2D;

private:
	typedef double(*funcarr)(double, double);

	Interval *intX, *intY;		// The two spacial intervals.
	funcarr *bounds;			// Functions defined on the boundaries.

public:
	/*
		Intial Condition constructor.

		@param step size in the x axis
		@param step size in the y direction
		@param initial displacement of x
		@param initial displacement of y
		@param array of 4 functions that serve as the top, right,
			bottom and left (in that order)
			The function takes one space dimension and a time dimension.
	*/
	InitCondition2D(Interval *, Interval *, double(*)(double, double) = &func::zero, funcarr[4] = NULL);
	~InitCondition2D();

	/*
		Returns the number of divisions in the dimension x.
	*/
	int getDivisionsX();

	/*
		Returns the number of divisions in the dimension y.
	*/
	int getDivisionsY();

	/*
		Returns the space step size of dimension X.
	*/
	double getIncrementX();

	/*
		Returns the space step size of dimension Y.
	*/
	double getIncrementY();

	/*
		Returns the offset in the dimension X.
	*/
	double getOffsetX();

	/*
		Returns the offset in the dimension Y.
	*/
	double getOffsetY();

	/*
		Returns the bounds array.
	*/
	funcarr * getBounds();
};

/*
	Space is the square Table2D that holds values that correspond to x
	and y coordinates. Columns are indexed by x, rows are indexed
	by y. An initial condition is given to set the values inside the table.
*/
struct Table2D : public MatrixBase
{
public:
	/*
		Creates the 2 dimensional space which holds all the values. Given
		the initial condition, it also sets the boundaries to the proper
		values.

		@param size of grid
		@param initial condition package
	*/
	Table2D(InitCondition2D *);

	/*
		Creates a copy of the current table with the same initial
		conditions and same inner values, then returns it.
	*/
	Table2D(Table2D *, InitCondition2D *);
};
