#pragma once

#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

#include "Space1D.h"
#include "Space2D.h"

/*
	Global time controller.
*/
struct Time
{
private:
	static double TIME;				// time variable.

	Time() {}						// Prevent the object from being created.
	~Time() {}

public:
	static double getTime() { return TIME; }
	static void addTime(double dT) { TIME += dT; }
	static void resetTime() { TIME = 0; }
};


/*
	Models either the 1 dimensional or 2 dimensional diffusion problem.
	The templates can either be Table1D and InitCondition1D OR
	Table2D and InitCondition2D.
*/
template<class Table, class InitCondition>
class ModelBase
{
protected:
	const double
		dT,							// Time step length.
		Dcoef;						// Diffusion coefficient.

	std::vector<Table *> frames;	// Vector of each time frame in the series.
	Table *current_frame;			// Current time frame being processed.
	InitCondition *IC;				// Initial conditions of the problem.
	double(*R)(double);				// Function of additional parameters.

	void(ModelBase<Table, InitCondition>::*solve)();	// Selects which type of solution is used.

	/*
		Model sets up the simulation.

		@param Initial conditions for the problem
		@param The time increment
		@param The additional function
	*/
	ModelBase(
		const double dT, const double Dcoef, InitCondition *IC, double(*R)(double)
		) : dT{ dT }, Dcoef{ Dcoef }, IC{ IC }, R{ R }
	{
		solve = &ModelBase<Table, InitCondition>::formNextTimeStep;
		frames.emplace_back(new Table(IC));	// The frame of the original state.
		current_frame = new Table(IC);		// Creates a new time frame to work with.
	}
	~ModelBase();

	/*
		Updates the current frame and pushes it to the stack.
	*/
	void formNextTimeStep();			// In cartesian coordinates.
	void formNextTimeStepPolar();		// In polar coordinates.

public:
	enum COORD { cartesian, polar };	// To pick the type of coordinates.

	/*
		Solves all the frames up to the maximum time.
	*/
	virtual void runModel(double);

	/*
		Returns the pointer to the first frame in the series.
	*/
	virtual std::vector<Table*> * getFrames();

	/*
		Prints all the frames to the specified output.
	*/
	virtual void printFrames(std::ostream &);

	/*
		Selects the working coordinates.
	*/
	virtual void pickCoord(COORD);
};

template<class Table, class InitCondition>
std::vector<Table *> * ModelBase<Table, InitCondition>::getFrames()
{
	return &frames;
}

template<class Table, class InitCondition>
void ModelBase<Table, InitCondition>::runModel(double steps)
{
	for (int i = 0; i < steps; i++)
	{
		std::cout << "Time:	" << std::setprecision(4) << Time::getTime() + dT << ", ";			// Current time index.
		std::cout << "Frame: " << i + 1 << ", ";												// Current frame.
		std::cout << "TOTAL PROGRESS: ";														// Total progress.

		std::cout << std::setfill('0') << std::fixed << std::setprecision(0) << std::setw(3)	// Formats the output.
			<< ((double)i / steps) * 100 << "%" << "\r";										// Prints the progress.

		Time::addTime(dT);
		(this->*solve)();
	}

	std::cout << std::endl << std::defaultfloat;												// Reset the console output.
	std::cout << "Simulation complete!\t\t\t\t\t\t" << std::endl;
}

template<class Table, class InitCondition>
void ModelBase<Table, InitCondition>::printFrames(std::ostream &fout)
{
	int count = 0;
	for (Table *f : frames)
	{
		std::cout << "Printing to file... ";
		std::cout << std::setfill('0') << std::fixed << std::setprecision(0) << std::setw(3)	// Formats the output.
			<< (double)count++ / (frames.size()) * 100 << "%" << "\r";							// Prints the progress.

		for (int j = f->M; j > 0; j--)
		{
			for (int i = 0; i < f->N; i++)
			{
				fout << std::setprecision(3) << std::setw(10) << *(f->V + i + (j - 1) * f->N) << " ";
			}
			fout << std::endl;
		}
		fout << std::endl;
	}

	std::cout << "\rFrames have been printed!" << std::endl;
}

template<class Table, class InitCondition>
void ModelBase<Table, InitCondition>::pickCoord(COORD c)
{
	switch (c)
	{
	case cartesian:
		solve = &ModelBase<Table, InitCondition>::formNextTimeStep;
		break;
	case polar:
		solve = &ModelBase<Table, InitCondition>::formNextTimeStepPolar;
		break;
	default:
		throw("Incorrect coordinates supplied");
		break;
	}

}

template<class Table, class InitCondition>
ModelBase<Table, InitCondition>::~ModelBase()
{
	for (Table *t : frames)
	{
		delete t;
	}
}