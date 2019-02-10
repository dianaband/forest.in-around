// i2c
#include <Wire.h>
#include "hanger/i2c_protocol.h"

// my tasks
extern Task sing_task;

// room protocol
static int message = 0;
static char msg_cstr[MSG_LENGTH_MAX] = {0, };
extern Task reaction_task;
void gotChangedConnectionCallback() { // REQUIRED
}
void gotMessageCallback(uint32_t from, String & msg) { // REQUIRED
  Serial.println(msg);
  // is it for me?
  int receipent = msg.substring(1, 7).toInt();
  if (receipent == IDENTITY) {
    // what it says?
    message = msg.substring(8, 12).toInt();
    // i ve heard. reaction.
    reaction_task.restart();
    // so, what to do, then?
    switch (message)
    {
    case HANGER_WORD_SING:
      Serial.println("hanger: great. i sing for me!");
      sing_task.restartDelayed(500);
      break;
    default:
      ;
    }
  }
  //eavesdropping 'thunder' message
  if (receipent == ID_THUNDER || receipent == ID_EVERYONE) {
    // what it says?
    message = msg.substring(8, 12).toInt();
    // i ve heard. reaction.
    reaction_task.restart();
    // so, what to do, then?
    switch (message)
    {
    case THUNDER_WORD_RRRRR:
      Serial.println("hanger: oh, thunder is coming! let's hide!");
      //
      sprintf(cmdstr, "SXXXX@%04d", 10); // amplitude change == 0.01
      Wire.beginTransmission(I2C_ADDR);
      Wire.write(cmdstr, CMD_LENGTH);
      Wire.endTransmission();
      break;
    case THUNDER_WORD_LEFT:
      Serial.println("hanger: well, thunder is gone. now is safe.");
      //
      sprintf(cmdstr, "SXXXX@%04d", 300); // play song #1, with amplitude == 0.3
      Wire.beginTransmission(I2C_ADDR);
      Wire.write(cmdstr, CMD_LENGTH);
      Wire.endTransmission();
      break;
    default:
      ;
    }
  }
}

// some reaction for received msg.
void reaction() {
  static int mask = 0x8000;
  static int count = 0;
  if (reaction_task.isFirstIteration()) {
    mask = 0x8000;
    count = 0;
  }
  if ((message & mask) == 0) {
    ; // what to do?
  }
  else {
    ; // what to do?
  }
  mask = mask >> 1;
  count++;
}
Task reaction_task(10, 16, &reaction);

// saying hello
void greeting() {
  static String msg = "";
  sprintf(msg_cstr, "[%06d:%03d]", ID_EVERYONE, HANGER_WORD_HELLO); //"(ttut-ttu-ru-ttut-ttu)"
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

void sing() {

  // "P#SSS@AAAA" - P: P (play), SSS: song #, A: amp. (x 1000)
  // "SXXXXXXXXX" - S: S (stop)

  sprintf(cmdstr, "P#%03d@%04d", 1, 1000); // play song #1, with amplitude == 1.0
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(cmdstr, CMD_LENGTH);
  Wire.endTransmission();
}
Task sing_task(0, TASK_ONCE, &sing);

//setup_member
void setup_member() {
  //i2c master
  Wire.begin();

  //tasks
  runner.addTask(saying_greeting);
  saying_greeting.enable();
  runner.addTask(sing_task);
  runner.addTask(reaction_task);
}