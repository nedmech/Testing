/*
 Name:		Fader.h
 Created:	7/14/2015
 Author:	Nathan Durnan
*/

#include "Fader.h"
//#define DEBUG_ // un-comment this line for serial debug output

/* constructor */
Fader::Fader()
{
	// Initialize members
	dmxUniverse = NULL;
	faderValue = 0;
	faderPin = 1;
	off_LED_Pin = 6;
	on_LED_Pin = 9;
	clearDmxMap();
	inputValue.reset();
}

/*-----------------------------------------------
	C++ wrapper (public methods)
-----------------------------------------------*/

/**	Set Analog Input Pin
*	@param pin : Input Analog pin to use (1...NUM_ANALOG_INPUTS)
*/
void Fader::setFaderPin(uint8_t pin)
{
	if ((pin >= 1) || (pin <= NUM_ANALOG_INPUTS))
		faderPin = pin;
}

/**	Set Digital Output Pin for OFF state indication
*	@param pin : Output Digital pin to use (1...NUM_DIGITAL_PINS)
*/
void Fader::setOffPin(uint8_t pin)
{
	if ((pin >= 1) || (pin <= NUM_DIGITAL_PINS))
		off_LED_Pin = pin;
	pinMode(off_LED_Pin, OUTPUT);
}

/**	Set PWM Output Pin for ON state indication
*	@param pin : Output PWM pin to use (1...NUM_DIGITAL_PINS)
*/
void Fader::setOnPin(uint8_t pin)
{
	if ((pin >= 1) || (pin <= NUM_DIGITAL_PINS))
		on_LED_Pin = pin;
	pinMode(on_LED_Pin, OUTPUT);
}

/**  Set DMX Universe Pointer
*	@param universe : Pointer to DmxSimpleClass object to use for output
*/
void Fader::setDmxUniverse(DmxSimpleClass* universe)
{
	dmxUniverse = universe;
}

/** Reset all DMX Channel mapping to false (OFF)
*/
void Fader::clearDmxMap()
{
	for (byte i = 0; i < DMX_CHANNEL_BLOCK; i++)
		dmxMap[i] = false;
}

/**	Set DMX Mapping for specified channel
*	@param ch : DMX Channel to assign mapping (1...DMX_CHANNEL_BLOCK)
*	@param map : Turn mapping ON/Off (true/false)
*/
void Fader::setDmxMap(int ch, bool map)
{
	if ((ch >= 1) && (ch <= DMX_CHANNEL_BLOCK))
		dmxMap[ch - 1] = map;
}

/** Update Fader input and output values
*/
void Fader::update()
{
#ifdef DEBUG_
	Serial.print("FADER: ");
	Serial.print(faderPin);
	Serial.print("\tIN: ");
	Serial.print(analogRead(faderPin));
#endif
	inputValue.newSample(analogRead(faderPin));
	this->update(inputValue.average());
}
/** Update Fader scaled output value
*	@param value : Input value (0-1023) to be rescaled and output
*/
void Fader::update(int value)
{
	faderValue = constrain(value, 0, 1023);
	// rescale analog input to DMX output range
	uint8_t dmxValue = constrain(
		map(faderValue, FADER_LO, FADER_HI, DMX_MIN, DMX_MAX)
		, DMX_MIN
		, DMX_MAX
		);
#ifdef DEBUG_
	Serial.print("\tDMX: ");
	Serial.println(dmxValue);
#endif
	// only send output if channel is mapped to Fader
	for (byte i = 1; i <= DMX_CHANNEL_BLOCK; i++)
		if (dmxMap[i - 1]) dmxUniverse->write(i, dmxValue);
	if (dmxValue == 0)
	{
		digitalWrite(off_LED_Pin, HIGH);
		digitalWrite(on_LED_Pin, LOW);
	}
	else
	{
		digitalWrite(off_LED_Pin, LOW);
		analogWrite(on_LED_Pin, dmxValue);
	}
}
