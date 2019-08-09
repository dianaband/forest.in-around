#pragma once

// member identity
#define ID_BELL          (0x1D00 + 0x20)
#define ID_FLOAT         (0x1D00 + 0x30)
#define ID_BAG           (0x1D00 + 0x40)
#define ID_LOOK          (0x1D00 + 0x50)
#define ID_WINDMILL      (0x1D00 + 0x60)
#define ID_GLASS         (0x1D00 + 0x70)
#define ID_REEL          (0x1D00 + 0x80)
#define ID_ARROW         (0x1D00 + 0x90)
#define ID_THUNDER       (0x1D00 + 0xA0)
#define ID_FUR           (0x1D00 + 0xB0)
#define ID_PEAK          (0x1D00 + 0xC0)
#define ID_KEYBED        (0x1D00 + 0xD0)
// (special agent)
#define ID_CONDUCTOR     (0x1E00 + 0x10)
// (groups)
#define ID_EVERYONE      (0x1F00 + 0x00)
// (choice)
#define IDENTITY         ID_FLOAT

#define NUM_OF_MEMBERS 13
int memberList[NUM_OF_MEMBERS] = {
  ID_BELL, // 1
  ID_FLOAT, // 2
  ID_BAG, // 3
  ID_LOOK, // 4
  ID_WINDMILL, // 5
  ID_GLASS, // 6
  ID_REEL, // 7
  ID_ARROW, // 8
  ID_THUNDER, // 9
  ID_FUR, // 10
  ID_PEAK, // 11
  ID_KEYBED, // 12
  ID_CONDUCTOR // 13
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
#define NODE_TYPE           NODE_TYPE_AP_STA
#if (IDENTITY == ID_THUNDER || IDENTITY == ID_GPS)
#undef NODE_TYPE
#define NODE_TYPE           NODE_TYPE_STA_ONLY
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
