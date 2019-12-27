#pragma once

// member identity
// objects
#define ID_FLOAT         (10100)
#define ID_GLASS         (10200)
#define ID_ARROW         (10300)
#define ID_BELL          (10400)
// (special agent)
#define ID_MONITOR       (20100) // TBD
#define ID_CONDUCTOR     (20200) // TBD
// (groups)
#define ID_EVERYONE      (90100)
#define ID_SPEAKERS      (90200) // TBD
// (choice)
#define IDENTITY         ID_GLASS

#define NUM_OF_MEMBERS 5
int memberList[NUM_OF_MEMBERS] = {
  ID_FLOAT, // 1
  ID_GLASS, // 2
  ID_ARROW, // 3
  ID_BELL, // 4
  ID_MONITOR // 5
};

//
#define LONELY_TO_DIE    (30000)

//
#include <Arduino.h>

//
#include <painlessMesh.h>
extern painlessMesh mesh;

// firmata connectivity
#define FIRMATA_ON          (0xF13A0001)
#define FIRMATA_OFF         (0xF13A0002)
#define FIRMATA_USE         FIRMATA_OFF
#if (IDENTITY == ID_NOBODY)
#undef FIRMATA_USE
#define FIRMATA_USE         FIRMATA_ON
#endif

//NOTE: disabling AP beacon for speaker accompanied devices!
#define NODE_TYPE_AP_STA    (0x40DE0001)
#define NODE_TYPE_STA_ONLY  (0x40DE0002)
//by-default : STA_ONLY
#define NODE_TYPE           NODE_TYPE_AP_STA
//guys w/ speakers : AP_STA
#if (IDENTITY == ID_NOBODY)
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
#define MESH_SSID "forest.in-around"
#define MESH_PASSWORD "1*around/inner"
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
#define LED_PERIOD (1111)
#define LED_ONTIME (1)

// event handlers fo connection-related events
extern void gotMessageCallback(uint32_t from, String & msg); // REQUIRED
extern void gotChangedConnectionCallback();

// the system scheduler
extern Scheduler runner;

#include "words.h"
