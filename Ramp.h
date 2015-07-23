/*
Name:		Ramp.h
Created:	7/22/2015
Author:	Nathan Durnan
*/
#pragma once

/*-----------------------------------------------
--> Delay in milliseconds between updates.
--> Increase this value for slower ramping.
-----------------------------------------------*/
#define RAMP_UPDATE_DELAY 10
/*-----------------------------------------------
--> Number of updates to ramp from minimum to maximum.
--> Increase this value for smoother ramping.
-----------------------------------------------*/
#define RAMP_UPDATE_STEPS 100
/*-----------------------------------------------
* NOTE:  10ms delay with 100 steps yields
*	approximately a 1sec fade time.
-----------------------------------------------*/

template <typename T> class Ramp
{
private:
	T value;	//* internal ramped value
	T rampRate;	//* size of change allowed for each update
public:
	/**	Reset the internal values to defaults.
	*/
	T reset(void)
	{
		rampRate = (sizeof(T) * 256 / RAMP_UPDATE_STEPS);
		value = 0;
		return value;
	}
	/**	Pre-load an internal value.
	*	@param _value : the value to pre-load into the Ramp.
	*	returns the new value of the Ramp.
	*/
	T setValue(T _value)
	{
		value = _value;
		return value;
	}
	/**	Set the Ramp Rate value.
	*	@param _rate : amount of change allowed for each update.
	*	NOTE: _rate must be positive and non-zero;
	*	returns the new value of the ramp rate.
	*/
	T setRampRate(T _rate)
	{
		if (_rate > 0)
		{
			rampRate = _rate;
		}
		return rampRate;
	}
	/**	Update the Ramp and step towards a new value.
	*	@param _newValue : the new target value.
	*	returns the updated Ramp value.
	*/
	T update(T _newValue)
	{
		if (_newValue > value)
		{
			value = min((value + rampRate), _newValue);
		}
		else if (_newValue < value)
		{
			value = max((value - rampRate), _newValue);
		}
		return value;
	}
	/**	Get the current value of the Ramp.
	*/
	T getValue(void)
	{
		return value;
	}

};