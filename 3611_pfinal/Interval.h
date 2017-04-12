#pragma once

#include <utility>
#include <cmath>

struct Interval
{
private:
	int divisions;							// The number of divisions of the interval.
	std::pair<double, double> * interval;	// The limits of the interval.

public:
	Interval(double, double);
	Interval(Interval *);
	~Interval();

	/*
		Changes the limits of the interval.
	*/
	void setLimits(double, double);

	/*
		Sets the number of divisions making up the interval.
	*/
	void setDivisions(int);

	/*
		Returns the number of divisions making up the interval.
	*/
	int getDivisions();

	/*
		Returns the increment of the interval.
	*/
	double getIncrement();

	/*
		Returns the left limit.
	*/
	double getLeft();

	/*
		Returns the right limit.
	*/
	double getRight();
};