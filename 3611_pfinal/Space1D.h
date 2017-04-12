#pragma once

#include "MatrixBase.h"
#include "Interval.h"
#include "ModelBase.h"
#include "Functions.h"

/*
	Contains all the necessary initial conditions for a 1
	dimensional problem.
*/

struct InitCondition1D : public MatrixBase
{
	friend struct Table1D;

private:
	typedef double(*funcarr)(double);

	Interval *interval;			// Interval of the problem.
	funcarr *bounds;			// Functions defined on the boundaries.

public:
	/*
		Initial Condition constructor.

		@param step size
		@param initial displacement
		@param array of 2 values that serve as the left and
		right boundaries.
	*/
	InitCondition1D(Interval *, double(*)(double) = &func::zero, funcarr[2] = NULL);
	~InitCondition1D();

	/*
		Returns the number of divisions in the dimension x.
	*/
	int getDivisions();

	/*
		Returns the step size.
	*/
	double getIncrement();

	/*
		Returns the displacement.
	*/
	double getOffset();

	/*
		Returns the bounds of the problem.
	*/
	funcarr * getBounds();

};

/*
	Space is the square Table that holds values that correspond to x
	and y coordinates. Columns are indexed by x, rows are indexed
	by y. An initial condition is given to set the values inside the table.
*/
struct Table1D : public MatrixBase
{
public:
	/*
		Creates the 2 dimensional space which holds all the values. Given
		the initial condition, it also sets the boundaries to the proper
		values.

		@param size of grid
		@param initial condition package
	*/
	Table1D(InitCondition1D *IC);

	/*
		Creates a copy of the current table with the same initial
		conditions and same inner values, then returns it.
	*/
	Table1D(Table1D *, InitCondition1D *IC);
};