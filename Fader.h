#pragma once

#include <stddef.h>
#include <Arduino.h>
#include <DmxSimple.h>
#include <BitBool.h>

#define SMOOTHING_SAMPLES 8
#define DMX_CHANNEL_BLOCK 16

class Fader
{
public:
	Fader();
	~Fader();
private:
	uint8_t faderPin;
	int faderValue;
	DmxSimpleClass* dmxUniverse;
	BitBool<DMX_CHANNEL_BLOCK> dmxMap;
	int inputValue[SMOOTHING_SAMPLES];
	uint16_t inputTotal;
	byte inputIndex;
public:
	void usePin(uint8_t);
	void setDmxUniverse(DmxSimpleClass*);
	void clearDmxMap();
	void setDmxMap(int, bool);
	void update();
private:
	int readInput();
};

