#pragma once

#include "ModelBase.h"

/*
	Overload of the 1 dimensional template.
*/
class Model1D : public ModelBase<Table1D, InitCondition1D>
{
public:
	Model1D(const double dT, const double Dceof, InitCondition1D *IC, double(*R)(double)) :
		ModelBase(dT, Dceof, IC, R) {}

	void pickCoord(COORD) { throw("Cannot select coordinate for 1d problem."); }
};

/*
	Overload of the 2 dimensional template.
*/
class Model2D : public ModelBase<Table2D, InitCondition2D>
{
public:
	Model2D(const double dT, const double Dcoef, InitCondition2D *IC, double(*R)(double)) :
		ModelBase(dT, Dcoef, IC, R) {}
};
