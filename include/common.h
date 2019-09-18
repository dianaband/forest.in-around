#pragma once

// member identity
#define ID_GAS           (0x1D00 + 0x20)
#define ID_FLOAT         (0x1D00 + 0x30)
#define ID_VOICE1        (0x1D00 + 0x40)
#define ID_LOOK          (0x1D00 + 0x50)
#define ID_VOICE2        (0x1D00 + 0x60)
#define ID_GLASS         (0x1D00 + 0x70)
#define ID_FALL2         (0x1D00 + 0x80)
#define ID_ARROW         (0x1D00 + 0x90)
#define ID_THUNDER       (0x1D00 + 0xA0)
#define ID_FALL1         (0x1D00 + 0xB0)
#define ID_VOICE3        (0x1D00 + 0xC0)
#define ID_KEYBED        (0x1D00 + 0xD0)
#define ID_ANI1          (0x1D00 + 0xE0)
#define ID_ANI2          (0x1D00 + 0xF0)
// (special agent)
#define ID_MONITOR        (0x1E00 + 0x10)
// (groups)
#define ID_EVERYONE      (0x1F00 + 0x00)
// (choice)
#define IDENTITY         ID_ANI1


#define NUM_OF_MEMBERS 15
int memberList[NUM_OF_MEMBERS] = {
  ID_GAS, // 1
  ID_FLOAT, // 2
  ID_VOICE1, // 3
  ID_LOOK, // 4
  ID_VOICE2, // 5
  ID_GLASS, // 6
  ID_FALL2, // 7
  ID_ARROW, // 8
  ID_THUNDER, // 9
  ID_FALL1, // 10
  ID_VOICE3, // 11
  ID_KEYBED, // 12
  ID_MONITOR, // 13
  ID_ANI1, // 14
  ID_ANI2 // 15
};

//
#define LONELY_TO_DIE    (30000)

//
#include <Arduino.h>

//
#include <painlessMesh.h>
extern painlessMesh mesh;

// mood
#define MOOD_LOW            (0x300D0001)
#define MOOD_HIGH           (0x300D0002)

// firmata connectivity
#define FIRMATA_ON          (0xF13A0001)
#define FIRMATA_OFF         (0xF13A0002)
#define FIRMATA_USE         FIRMATA_OFF
#if (IDENTITY == ID_KEYBED)
#undef FIRMATA_USE
#define FIRMATA_USE         FIRMATA_ON
#endif

//NOTE: disabling AP beacon for speaker accompanied devices!
#define NODE_TYPE_AP_STA    (0x40DE0001)
#define NODE_TYPE_STA_ONLY  (0x40DE0002)
#define NODE_TYPE           NODE_TYPE_STA_ONLY
#if (IDENTITY == ID_GAS || IDENTITY == ID_LOOK || IDENTITY == ID_MONITOR)
#undef NODE_TYPE
#define NODE_TYPE           NODE_TYPE_AP_STA
#endif

// board
#define BOARD_NODEMCU_ESP12E (0xBD00 + 1)
#define BOARD_NODEMCU_ESP12N (0xBD00 + 2)
#define BOARD_NODEMCU_ESP32  (0xBD00 + 3)
//(choice)
#define BOARD_SELECT BOARD_NODEMCU_ESP12E

// mesh
#define MESH_SSID "darker-than-the-navel"
#define MESH_PASSWORD "12*1000/128"
#define MESH_PORT 5555
#define MESH_CHANNEL 5
// #define MESH_ANCHOR

//
// LED status indication
//   operation modes
//     0 - booted. and running. no connection. scanning.
//     1 - + connected.
//   notifying patterns
//     0 - steady on
//     1 - slow blinking (syncronized)
//
#if (BOARD_SELECT == BOARD_NODEMCU_ESP12E)
#define LED_PIN 2 // nodemcuv2
#elif (BOARD_SELECT == BOARD_NODEMCU_ESP32)
#define LED_PIN 13 // featheresp32
#endif
#define LED_PERIOD (1000+(12*1000/128))
#define LED_ONTIME (12*1000/128)

// event handlers fo connection-related events
extern void gotMessageCallback(uint32_t from, String & msg); // REQUIRED
extern void gotChangedConnectionCallback();

// the system scheduler
extern Scheduler runner;

#include "words.h"
