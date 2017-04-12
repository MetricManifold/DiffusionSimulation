#pragma once

#include <cmath>
#include <random>

class rand_gen
{
private:
	static std::default_random_engine *generator;

	rand_gen() {}
	~rand_gen() {}
	
public:
	static std::default_random_engine * getGen() { return generator; }

};

namespace func
{
	double zero(double, double);
	double zero(double);
	
	// Problem 1
	double problem1dist(double);
	double problem1R(double);

	// Problem 2
	double problem2dist(double, double);
	double problem2left(double, double);
	double problem2right(double, double);
	double problem2bottom(double, double);
	double problem2top(double, double);
	double problem2R(double);

	//Problem 3
	double problem3dist(double, double);
	double problem3left(double, double);
	double problem3right(double, double);
	double problem3bottom(double, double);
	double problem3top(double, double);
	double problem3R(double);

	//Problem 4
	double problem4dist(double, double);
	double problem4inner(double, double);
	double problem4outer(double, double);
	double problem4left(double, double);
	double problem4right(double, double);
	double problem4R(double);
}
