/*
 Name:		Fader.h
 Created:	7/14/2015
 Author:	Nathan Durnan
*/

#include "Fader.h"

/* constructor */
Fader::Fader()
{
	// Initialize members
	dmxUniverse = NULL;
	faderValue = 0;
	faderPin = 1;
	clearDmxMap();
	inputIndex = 0;
	for (int i = 0; i < SMOOTHING_SAMPLES; i++) inputValue[i] = 0;
	inputTotal = 0;
}

/* read analog input (with smoothing)
*/
int Fader::readInput()
{
	/* Apply smoothing algorithm to input value */
	// subtract the oldest reading from the total
	inputTotal -= inputValue[inputIndex];
	// read new value from the analog input
	inputValue[inputIndex] = analogRead(faderPin);
	// add the new reading to the total
	inputTotal += inputValue[inputIndex];
	// advance to the next position in the array
	inputIndex += 1;
	// wrap around the end of the array
	if (inputIndex >= SMOOTHING_SAMPLES) inputIndex = 0;
	return (inputTotal / SMOOTHING_SAMPLES);
}

/*-----------------------------------------------
	C++ wrapper (public methods)
-----------------------------------------------*/

/*	Set Analog Input Pin
	@param pin : Input Analog pin to use (1...NUM_ANALOG_INPUTS)
*/
void Fader::usePin(uint8_t pin)
{
	if ((pin >= 1) || (pin <= NUM_ANALOG_INPUTS))
		faderPin = pin;
}

/*  Set DMX Universe Pointer
	@param universe : Pointer to DmxSimpleClass object to use for output
*/
void Fader::setDmxUniverse(DmxSimpleClass* universe)
{
	dmxUniverse = universe;
}

/* Reset all DMX Channel mapping to false (OFF)
*/
void Fader::clearDmxMap()
{
	for (byte i = 0; i < DMX_CHANNEL_BLOCK; i++)
		dmxMap[i] = false;
}

/*	Set DMX Mapping for specified channel
	@param ch : DMX Channel to assign mapping (1...DMX_CHANNEL_BLOCK)
	@param map : Turn mapping ON/Off (true/false)
*/
void Fader::setDmxMap(int ch, bool map)
{
	if ((ch >= 1) && (ch <= DMX_CHANNEL_BLOCK))
		dmxMap[ch - 1] = map;
}

/* Update Fader input and output values
*/
void Fader::update()
{
	faderValue = readInput();
	// rescale analog input to DMX output range
	uint8_t dmxValue = map(faderValue, FADER_LO, FADER_HI, DMX_MIN, DMX_MAX);
	dmxValue = constrain(dmxValue, DMX_MIN, DMX_MAX);
	// only send output if channel is mapped to Fader
	for (byte i = 1; i <= DMX_CHANNEL_BLOCK; i++)
		if (dmxMap[i - 1]) dmxUniverse->write(i, dmxValue);
}
