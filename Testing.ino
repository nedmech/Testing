/*
 Name:		Testing.ino
 Created:	7/14/2015 1:54:15 PM
 Author:	Nathan Durnan
*/

#include <DmxSimple.h>
#include <BitBool.h>
#include "Fader.h"

// Fader Channel Definitions
#define FADER_HOUSE    0
#define FADER_STAGE    1
#define FADER_ENTRY    2
#define FADER_OVERFLOW 3
#define FADER_CHANNELS 4

Fader Channel[FADER_CHANNELS];

// DMX Output Channel Definitions
#define DMX_HOUSE      1
#define DMX_STAGE_MAIN 2
#define DMX_STAGE_SIDE 6
#define DMX_OVERFLOW   7
#define DMX_ENTRY      8

// the setup function runs once when you press reset or power the board
void setup() {
	// Set up DMX Interface
	DmxSimple.usePin(3);
	DmxSimple.maxChannel(DMX_CHANNEL_BLOCK);
	// First Fader Channel
	Channel[FADER_HOUSE].usePin(1);
	Channel[FADER_HOUSE].setDmxUniverse(&DmxSimple);
	Channel[FADER_HOUSE].setDmxMap(DMX_HOUSE, true);
	// Second Fader Channel
	Channel[FADER_STAGE].usePin(2);
	Channel[FADER_STAGE].setDmxUniverse(&DmxSimple);
	Channel[FADER_STAGE].setDmxMap(DMX_STAGE_MAIN, true);
	Channel[FADER_STAGE].setDmxMap(DMX_STAGE_SIDE, true);
	// Third Fader Channel
	Channel[FADER_ENTRY].usePin(3);
	Channel[FADER_ENTRY].setDmxUniverse(&DmxSimple);
	Channel[FADER_ENTRY].setDmxMap(DMX_ENTRY, true);
	// Fourth Fader Channel
	Channel[FADER_OVERFLOW].usePin(4);
	Channel[FADER_OVERFLOW].setDmxUniverse(&DmxSimple);
	Channel[FADER_OVERFLOW].setDmxMap(DMX_OVERFLOW, true);

}

// the loop function runs over and over again until power down or reset
void loop() {
	for (byte i = 0; i < FADER_CHANNELS; i++)
	{
		Channel[i].update();
	}
	delay(10);  // slow down the loop so fading is smoother
}
