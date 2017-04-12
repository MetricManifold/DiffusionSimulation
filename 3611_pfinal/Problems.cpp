#include "Problems.h"

double problems::PI = 4.0 * atan(1.0);

problems::problems() {}

problems::~problems()
{
	delete INTERVALX;				// Interval of x.
	delete INTERVALY;				// Interval of y.
	delete IC1;						// Initial conditions of a 1d system.
	delete IC2;						// Initial conditions of a 2d system.
	delete[] &BOUNDS;				// Boundary conditions of a 1d system.
	delete[] &BOUNDSF;				// Boundary conditions of a 2d system.
}

void problems::problem1()
{
	/*
		FIRST PROBLEM
		**********************************************
	*/

	fout.open("problem1.txt", std::ofstream::trunc);
	Time::resetTime();						// Initial time is 0.

	/*		Set up the parameters.	*/
	INTERVALX = new Interval(-50.0, 50.0);	// Interval of the problem.
	DT = 0.05;								// The time increment.
	TSTEPS = 800;							// The number of total steps to be made.
	DCOEF = 1.0;							// Diffusion coefficient.

	/*		Create the initial conditions and the model.	*/
	IC1 = new InitCondition1D(INTERVALX, &func::problem1dist);
	Model1D *m = new Model1D(DT, DCOEF, IC1, &func::problem1R);

	/*		Run the model and print the results.		*/
	m->runModel(TSTEPS);					// Run the model.
	m->printFrames(fout);					// Prints out the frames into a file.

	/*		Free the memory used in this problem.		*/
	delete INTERVALX, IC1, m;

	/*		Close the file		*/
	fout.close();
}

void problems::problem2()
{
	/*
	SECOND PROBLEM
	**********************************************
	*/

	fout.open("problem2.txt", std::ofstream::trunc);
	Time::resetTime();						// Initial time is 0.

	/*		Set up the parameters.	*/
	BOUNDSF[0] = &func::problem2top;
	BOUNDSF[1] = &func::problem2right;
	BOUNDSF[2] = &func::problem2bottom;
	BOUNDSF[3] = &func::problem2left;

	INTERVALX = new Interval(-30.0, 30.0);	// Interval of the problem.
	INTERVALY = new Interval(-30.0, 30.0);	// Interval of the problem.
	DT = 0.001;								// The time increment.
	TSTEPS = 250;							// The number of total steps to be made.
	DCOEF = 1.5;							// Diffusion coefficient.

	INTERVALX->setDivisions(150);			// Set the number of divisions to 150 instead of default 200.
	INTERVALY->setDivisions(150);			// Set the number of divisions to 150 instead of default 200.

	/*		Create the initial conditions and the model.	*/
	IC2 = new InitCondition2D(INTERVALX, INTERVALY, &func::problem2dist, BOUNDSF);
	Model2D *m = new Model2D(DT, DCOEF, IC2, &func::problem2R);

	/*		Run the model and print the results.		*/
	m->runModel(TSTEPS);					// Run the model.
	m->printFrames(fout);					// Prints out the frames into a file.

	/*		Free the memory used in this problem.		*/
	delete INTERVALX, INTERVALY, IC1, m;

	/*		Close the file		*/
	fout.close();
}


void problems::problem3()
{
	/*
	THIRD PROBLEM
	**********************************************
	*/

	fout.open("problem3.txt", std::ofstream::trunc);
	Time::resetTime();						// Initial time is 0.

	/*		Set up the parameters.	*/
	BOUNDSF[0] = &func::problem3top;
	BOUNDSF[1] = &func::problem3right;
	BOUNDSF[2] = &func::problem3bottom;
	BOUNDSF[3] = &func::problem3left;

	INTERVALX = new Interval(-50.0, 50.0);	// Interval of the problem.
	INTERVALY = new Interval(-50.0, 50.0);	// Interval of the problem.
	DT = 0.001;								// The time increment.
	TSTEPS = 200;							// The number of total steps to be made.
	DCOEF = 10.0;							// Diffusion coefficient.

	/*		Create the initial conditions and the model.	*/
	IC2 = new InitCondition2D(INTERVALX, INTERVALY, &func::problem3dist, BOUNDSF);
	Model2D *m = new Model2D(DT, DCOEF, IC2, &func::problem3R);

	/*		Run the model and print the results.		*/
	m->runModel(TSTEPS);					// Run the model.
	m->printFrames(fout);					// Prints out the frames into a file.

	/*		Free the memory used in this problem.		*/
	delete INTERVALX, INTERVALY, IC1, m;

	/*		Close the file		*/
	fout.close();
}

void problems::problem4()
{
	/*
	FOURTH PROBLEM
	**********************************************
	*/

	fout.open("problem4.txt", std::ofstream::trunc);
	Time::resetTime();						// Initial time is 0.

	/*		Set up the parameters.	*/
	BOUNDSF[0] = &func::problem4outer;
	BOUNDSF[1] = &func::problem4right;
	BOUNDSF[2] = &func::problem4inner;
	BOUNDSF[3] = &func::problem4left;

	INTERVALX = new Interval(1.0, 7.0);		// Interval of the problem.
	INTERVALY = new Interval(0.0, 2 * PI);	// Interval of the problem.
	DT = 0.00001;							// The time increment.
	TSTEPS = 200;							// The number of total steps to be made.
	DCOEF = 12.0;							// Diffusion coefficient.

	/*		Create the initial conditions and the model.	*/
	IC2 = new InitCondition2D(INTERVALX, INTERVALY, &func::problem4dist, BOUNDSF);
	Model2D *m = new Model2D(DT, DCOEF, IC2, &func::problem4R);
	m->pickCoord(Model2D::polar);

	/*		Run the model and print the results.		*/
	m->runModel(TSTEPS);					// Run the model.
	m->printFrames(fout);					// Prints out the frames into a file.

	/*		Free the memory used in this problem.		*/
	delete INTERVALX, INTERVALY, IC1, m;

	/*		Close the file		*/
	fout.close();
}

