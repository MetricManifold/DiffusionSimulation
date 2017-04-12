#include "ModelBase.h"

double Time::TIME = 0;			// Define the time variable.

template<>
void ModelBase<Table1D, InitCondition1D>::formNextTimeStep()
{
	for (int i = 1, size = current_frame->N - 1; i < size; i++)
	{
		double
			u_prev = *(frames.back()->V + i - 1),
			u_next = *(frames.back()->V + i + 1),
			u_curr = *(frames.back()->V + i);

		// Sets a new value at the index.
		*(current_frame->V + i) =
			u_curr + dT * Dcoef * ((u_next - 2 * u_curr + u_prev) / pow(IC->getIncrement(), 2) + R(u_curr));
	}

	frames.push_back(current_frame);
	current_frame = new Table1D(frames.back(), IC);
}

template<>
void ModelBase<Table2D, InitCondition2D>::formNextTimeStep()
{
	for (int i = current_frame->N + 1, size = current_frame->N * (current_frame->M - 1) - 1; i < size; i++)
	{
		if ((i + 1) % current_frame->N == 0) i += 2;

		double
			u_prev = *(frames.back()->V + i - 1),
			u_next = *(frames.back()->V + i + 1),
			u_curr = *(frames.back()->V + i),
			u_abov = *(frames.back()->V + i + current_frame->N),
			u_belo = *(frames.back()->V + i - current_frame->N);

		// Sets a new value at the index.
		*(current_frame->V + i) =
			u_curr + dT * (
				Dcoef * (u_next - 2 * u_curr + u_prev) / pow(IC->getIncrementX(), 2) +
				Dcoef * (u_abov - 2 * u_curr + u_belo) / pow(IC->getIncrementY(), 2)
				+ R(u_curr));

		double ans = u_curr + dT * (
			Dcoef * (u_next - 2 * u_curr + u_prev) / pow(IC->getIncrementX(), 2) +
			Dcoef * (u_abov - 2 * u_curr + u_belo) / pow(IC->getIncrementY(), 2)
			+ R(u_curr));
	}

	frames.push_back(current_frame);
	current_frame = new Table2D(frames.back(), IC);
}

template<>
void ModelBase<Table2D, InitCondition2D>::formNextTimeStepPolar()
{
	for (int i = current_frame->N + 1, size = current_frame->N * (current_frame->M - 1) - 1; i < size; i++)
	{
		if ((i + 1) % current_frame->N == 0) i += 2;

		double	/* values from previous table */
			u_prev = *(frames.back()->V + i - 1),
			u_next = *(frames.back()->V + i + 1),
			u_curr = *(frames.back()->V + i),
			u_abov = *(frames.back()->V + i + current_frame->N),
			u_belo = *(frames.back()->V + i - current_frame->N);
		double	/* r values */
			r_curr = IC->getIncrementY() * i,
			r_next = IC->getIncrementY() * i + IC->getIncrementY() / 2,
			r_prev = IC->getIncrementY() * i - IC->getIncrementY() / 2;

		// Sets a new value at the index.
		*(current_frame->V + i) =
			u_curr + dT * (
				Dcoef * (r_next * u_next - (r_prev + r_next) * u_curr + r_prev * u_prev) / (r_curr * pow(IC->getIncrementY(), 2)) +
				Dcoef * (u_abov - 2 * u_curr + u_belo) / (pow(r_curr, 2) * pow(IC->getIncrementX(), 2))
				+ R(u_curr));
	}

	frames.push_back(current_frame);
	current_frame = new Table2D(frames.back(), IC);
}
