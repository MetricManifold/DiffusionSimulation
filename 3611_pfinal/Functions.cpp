#include "Functions.h"

std::default_random_engine *rand_gen::generator = new std::default_random_engine;


double func::zero(double, double)
{
	return 0;
}

double func::zero(double)
{
	return 0;
}

double func::problem1dist(double x)
{
	return 0.05 * exp(-5 * pow(x, 2));
}

double func::problem1R(double u)
{
	return u - pow(u, 2);
}

double func::problem2dist(double x, double y)
{
	return fabs(sin(x * y));
}

double func::problem2left(double y, double t)
{
	return 3 * fabs(y) * exp(-t);
}

double func::problem2right(double y, double t)
{
	return 3 * t * exp(-fabs(y) * t);
}

double func::problem2bottom(double x, double t)
{
	return t * pow(x, 2);
}

double func::problem2top(double x, double t)
{
	return 4.5 * pow(x, 2) * pow(t, 2);
}

double func::problem2R(double)
{
	return 0;
}

double func::problem3dist(double x, double y)
{
	std::normal_distribution<double> distribution(0.0, sqrt(0.1));
	return fabs(distribution(*rand_gen::getGen()));
}

double func::problem3left(double y, double t)
{
	std::normal_distribution<double> distribution(0.0, sqrt(0.5));
	return fabs(distribution(*rand_gen::getGen()));
}

double func::problem3right(double y, double t)
{
	std::normal_distribution<double> distribution(0.0, sqrt(0.01));
	return fabs(distribution(*rand_gen::getGen()));
}

double func::problem3bottom(double x, double t)
{
	std::normal_distribution<double> distribution(0.0, sqrt(0.2));
	return fabs(distribution(*rand_gen::getGen()));
}

double func::problem3top(double x, double t)
{
	std::normal_distribution<double> distribution(0.0, sqrt(0.001));
	return fabs(distribution(*rand_gen::getGen()));
}

double func::problem3R(double u)
{
	return u * (1 - u / 100.0);
}

double func::problem4dist(double r, double w)
{
	return r * pow(sin(w), 2);
}

double func::problem4inner(double w, double t)
{
	return 3 * w * exp(-t / 5);
}

double func::problem4outer(double w, double t)
{
	return 3 * w * t * fabs(sin(w));
}

double func::problem4left(double r, double t)
{
	return t * pow(r, 4) + r;
}

double func::problem4right(double r, double t)
{
	return 4.5 * r * pow(t, 2);
}

double func::problem4R(double u)
{
	return pow(u, 2) - pow(u, 3);
}
