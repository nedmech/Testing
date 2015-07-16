/*
 Name:		Testing.ino
 Created:	7/14/2015
 Author:	Nathan Durnan
*/
#include <DmxSimple.h>
#include <BitBool.h>
#include "Fader.h"

/*------------------------------------------
	FADER CHANNEL DEFINITIONS
	--> Number must be between 0 to (NUM_ANALOG_INPUTS - 1)
	--> New faders can be added using the "#define {name} {value}" format.
	\/\/\/ EDIT BELOW \/\/\/
	------------------------------------------*/
#define FADER_HOUSE    0  // Main House Ceiling Lights
#define FADER_STAGE    1  // All Stage Ceiling Lights
#define FADER_ENTRY    2  // Entryway Ceiling Lights
#define FADER_OVERFLOW 3  // Overflow Seating Ceiling Lights
#define FADER_CHANNELS 4  // Maximum of (NUM_ANALOG_INPUTS - 1)
/*------------------------------------------
	END FADER CHANNEL DEFINITIONS
------------------------------------------*/

/*------------------------------------------
	DMX OUTPUT CHANNEL DEFINITIONS
	--> These can be edited based on the DMX Addressing of each zone/fixture
	--> Address number must be between 1 to DMX_CHANNEL_BLOCK (see Fader.h)
	--> New fixtures/zones can be added using the "#define {name} {value}" format.
	\/\/\/ EDIT BELOW \/\/\/
------------------------------------------*/
#define DMX_HOUSE      1 // Main House Ceiling Lights
#define DMX_STAGE_MAIN 2 // Stage Ceiling Lights - Center Zone
#define DMX_STAGE_SIDE 6 // Stage Ceiling Lights - Side Zone
#define DMX_OVERFLOW   7 // Overflow Seating Ceiling Lights
#define DMX_ENTRY      8 // Entryway Ceiling Lights
/*------------------------------------------
	END DMX OUTPUT CHANNEL DEFINITIONS
------------------------------------------*/

// Fader Channel Object
Fader Channel[FADER_CHANNELS];

// the setup function runs once when you press reset or power the board
void setup() {
	// Set up DMX Interface
	DmxSimple.usePin(3);
	DmxSimple.maxChannel(DMX_CHANNEL_BLOCK);
	// Assign channels input pins and DMX Output Universe
	for (byte i = 0; i < FADER_CHANNELS; i++)
	{
		Channel[i].usePin(i + 1);
		Channel[i].setDmxUniverse(&DmxSimple);
		Channel[i].clearDmxMap();
	}
	/*------------------------------------------
		CONFIGURE FADER CHANNEL MAPPING
		--> Edit the lines below to change which
			DMX channels are controlled by each Fader.
		--> One Fader can control multiple DMX channels.
		--> Do NOT map a DMX channel to multiple Faders!
			(The output will be unstable)
		\/\/\/ EDIT BELOW \/\/\/
	------------------------------------------*/
	Channel[FADER_HOUSE   ].setDmxMap(DMX_HOUSE     , true);
	Channel[FADER_STAGE   ].setDmxMap(DMX_STAGE_MAIN, true);
	Channel[FADER_STAGE   ].setDmxMap(DMX_STAGE_SIDE, true);
	Channel[FADER_ENTRY   ].setDmxMap(DMX_ENTRY     , true);
	Channel[FADER_OVERFLOW].setDmxMap(DMX_OVERFLOW  , true);
	/*------------------------------------------
		END FADER CHANNEL MAPPING
	------------------------------------------*/
}

// the loop function runs over and over again until power down or reset
void loop() {
	for (byte i = 0; i < FADER_CHANNELS; i++)
	{
		Channel[i].update();
	}
	delay(10);  // slow down the loop so fading is smoother
}
