#include "Interval.h"

Interval::Interval(double n, double m)
{
	interval = new std::pair<double, double>(n, m);
	
	// Assign variables.
	divisions = 200;
}

Interval::Interval(Interval *i)
{
	interval = new std::pair<double, double>(i->interval->first, i->interval->second);
	setDivisions(i->divisions);
}

void Interval::setLimits(double n, double m)
{
	delete interval;
	interval = new std::pair<double, double>(m, n);
}

void Interval::setDivisions(int divisions)
{
	this->divisions = divisions;
}

double Interval::getLeft()
{
	return interval->first;
}

double Interval::getRight()
{
	return interval->second;
}

int Interval::getDivisions()
{
	return divisions;
}

double Interval::getIncrement()
{
	return fabs(interval->first - interval->second) / divisions;
}

Interval::~Interval()
{
	delete interval;
}