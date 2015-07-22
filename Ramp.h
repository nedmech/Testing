/*
Name:		Ramp.h
Created:	7/22/2015
Author:	Nathan Durnan
*/
#pragma once

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
		rampRate = (sizeof(T) * 256 / 32);
		value = 0;
		return value;
	}
	/**	Pre-load an internal value.
	*	@param _val : the value to pre-load into the Ramp.
	*	returns the new value of the Ramp.
	*/
	T setValue(T _val)
	{
		value = _val;
		return value;
	}
	/**	Set the Ramp Rate value.
	*	@param _val : amount of change allowed for each update.
	*	returns the new value of the ramp rate.
	*/
	T setRampRate(T _val)
	{
		rampRate = _val;
		return rampRate;
	}
	/**	Update the Ramp and step towards a new value.
	*	@param _val : the new target value.
	*	returns the updated Ramp value.
	*/
	T update(T _val)
	{
		if (_val > value)
		{
			value = min((value + rampRate), _val);
		}
		else if (_val < value)
		{
			value = max((value - rampRate), _val);
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