// i2c
#include <Wire.h>
#include "speakers/i2c_protocol.h"

// tasks
extern Task sing_task;

// // mood
// int mood = EVERYONE_MOOD_LOW;

// // leading or following
// int leadfollow = SPEAKERS_FOLLOWING;

// room protocol
static int message = 0;
static char msg_cstr[MSG_LENGTH_MAX] = {0, };
void gotChangedConnectionCallback() { // REQUIRED
}
void gotMessageCallback(uint32_t from, String & msg) { // REQUIRED
  Serial.println(msg);
  message = msg.substring(1, 6).toInt();
  // speakers event
  if (message == SPEAKERS_TIC) {
    Serial.println("SPEAKERS_TIC");
    sing_task.restartDelayed(10);
  }
  // // everyone event
  // if (message == EVERYONE_MOOD_HIGH) {
  //   mood = EVERYONE_MOOD_HIGH;
  // }
  // if (message == EVERYONE_MOOD_LOW) {
  //   mood = EVERYONE_MOOD_LOW;
  //   // "SXXXXXXXXX" - S: S (stop)
  //   sprintf(cmdstr, "SXXXXXXXXX");   // stop!
  //   Wire.beginTransmission(I2C_ADDR);
  //   Wire.write(cmdstr, CMD_LENGTH);
  //   Wire.endTransmission();
  // }
}

// saying hello
void greeting() {
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", SPEAK_F_HELLO);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("TX : " + msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// extern Task routine_task;
// void routine() {
//   static String msg = "";
//   sprintf(msg_cstr, "[%06d:%03d]", ID_VOICE2, VOICE2_WORD_SING);
//   msg = String(msg_cstr);
//   mesh.sendBroadcast(msg);
//   Serial.println("to voice2");
//   //
//   routine_task.restartDelayed(random(3000));
// }
// Task routine_task(0, TASK_ONCE, &routine);

// // the timing in my mind
// extern Task timing_task;
// void timing() {
//   Serial.println("to voice2");
//   //
//   timing_task.restartDelayed(random(3000));
// }
// Task timing_task(0, TASK_ONCE, &timing);

// sing!
void sing() {
  // "P#SSS@AAAA" - P: P (play), SSS: song #, A: amp. (x 1000)
  // "SXXXXXXXXX" - S: S (stop)
  sprintf(cmdstr, "P#%03d@%04d", (int)random(1, 7), 800); // play song #1, with amplitude
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

  // runner.addTask(timing_task);
  // timing_task.enable();

  runner.addTask(sing_task);
}
