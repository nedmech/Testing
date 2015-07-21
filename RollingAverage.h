/*
Name:		RollingAverage.h
Created:	7/17/2015
Author:	Nathan Durnan
*/
#pragma once

#define SAMPLES 32 // Number of samples to average over
template <typename T> class RollingAverage
{
private:
	T sample[SAMPLES];
	T avg;  // internal average value
	byte index;
public:
	/** Clears out the samples buffer
	*/
	void reset()
	{
		for (index = 0; index < SAMPLES; index++)
			sample[index] = 0;
		index = 0;
		avg = 0;
	}
	/** Add a new value to the samples buffer
	*	Returns updated rolling average value
	*	@param value : new sample value to be added
	*/
	T newSample(T value)
	{
		avg -= (sample[index] / SAMPLES);
		sample[index] = value;
		avg += (sample[index] / SAMPLES);
		index += 1;
		if (index >= SAMPLES) index = 0;
		return avg;
	}
	/** Reports the current rolling average value
	*/
	T average() { return avg; }
};

