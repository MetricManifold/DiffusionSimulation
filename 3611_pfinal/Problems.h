#pragma once

#include <iomanip>
#include <fstream>

#include "Space1D.h"
#include "Space2D.h"
#include "Model.h"
#include "Interval.h"
#include "Functions.h"

class problems
{
	typedef double(*funcarr)(double, double);

	/*
		PARAMETERS
		**********************************************
	*/
private:
	Interval *INTERVALX;				// Interval of x.
	Interval *INTERVALY;				// Interval of y.
	InitCondition1D *IC1;				// Initial conditions of a 1d system.
	InitCondition2D *IC2;				// Initial conditions of a 2d system.
	double DT, TSTEPS, DCOEF;			// The time step, number of steps, and diffusion coefficient.
	funcarr BOUNDS[2];					// Boundary conditions of a 1d problem.
	funcarr BOUNDSF[4];					// Boundary conditions of a 2d problem.

	static double PI;

	std::ofstream fout;					// Output stream.
	
public:

	problems();
	~problems();

	void problem1();		// Conditions and execution of problem 1,
	void problem2();		// ... problem 2,
	void problem3();		// ... problem 3,
	void problem4();		// ... problem 4.
};