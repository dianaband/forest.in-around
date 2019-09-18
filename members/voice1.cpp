// i2c
#include <Wire.h>
#include "voice2/i2c_protocol.h"

// servo
#include <Servo.h>

extern Task signal_task;

// mood
int mood = MOOD_LOW;

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
    if (reaction_task.getRunCounter() == 0)
      reaction_task.restart();
    // so, what to do, then?
    switch (message)
    {
    case VOICE1_WORD_SING:
      Serial.println("voice1: ah ah ah");
      signal_task.restartDelayed(500);
      break;
    default:
      ;
    }
  }
  //
  if (receipent == ID_EVERYONE) {
    // what it says?
    message = msg.substring(8, 12).toInt();
    // so, what to do, then?
    switch (message)
    {
    case KEYBED_WORD_FREE:
      mood = MOOD_HIGH;
      break;
    case KEYBED_WORD_ACTIVE:
      mood = MOOD_LOW;
      // "SXXXXXXXXX" - S: S (stop)
      sprintf(cmdstr, "SXXXXXXXXX"); // stop!
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
  if (reaction_task.isLastIteration()) {
    //
  }
  mask = mask >> 1;
  count++;
}
Task reaction_task(10, 17, &reaction);

// saying hello
void greeting() {
  static String msg = "";
  sprintf(msg_cstr, "[%06d:%03d]", memberList[random(NUM_OF_MEMBERS)], VOICE1_WORD_HELLO); //"Duncan. Living in the triangularities."
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

extern Task routine_task;
void routine() {
  static String msg = "";
  sprintf(msg_cstr, "[%06d:%03d]", ID_VOICE2, VOICE2_WORD_SING);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("to voice2");
  //
  routine_task.restartDelayed(random(3000));
}
Task routine_task(0, TASK_ONCE, &routine);
// sing!
void signal() {

  // "P#SSS@AAAA" - P: P (play), SSS: song #, A: amp. (x 1000)
  // "SXXXXXXXXX" - S: S (stop)

  sprintf(cmdstr, "P#%03d@%04d", random(1, 7), 800); // play song #1, with amplitude == 1.0
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(cmdstr, CMD_LENGTH);
  Wire.endTransmission();
}
Task signal_task(0, TASK_ONCE, &signal);

//setup_member
void setup_member() {
  //i2c master
  Wire.begin();

  //tasks
  runner.addTask(saying_greeting);
  saying_greeting.enable();
  runner.addTask(routine_task);
  routine_task.enable();

  runner.addTask(signal_task);
  runner.addTask(reaction_task);

}
