// firmata -> wireless mesh

// this ID uses firmata to get commands from PD.
//  --> common.h
//
// #if (IDENTITY == ID_KEYBED)
// #undef FIRMATA_USE
// #define FIRMATA_USE         FIRMATA_ON
// #endif
//

//tasks

// room protocol
static int message = 0;
static char msg_cstr[MSG_LENGTH_MAX] = {0, };
// extern Task reaction_task;
void gotChangedConnectionCallback() { // REQUIRED
}
void gotMessageCallback(uint32_t from, String & msg) { // REQUIRED
}

//firmata
void analogWriteCallback(byte pin, int value){
  //
  static String msg = "";
  //
  if (pin == 10) {
    //DEBUG
    //sprintf(cmdstr, "p:%d,v:%d", pin, value);

    //COMMAND
    if (value == 0) { // 0 - FREE
      sprintf(msg_cstr, "[%06d:%03d]", ID_EVERYONE, KEYBED_WORD_FREE);
      msg = String(msg_cstr);
      mesh.sendBroadcast(msg);
      //
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, HIGH);
    } else { // non-0 - ACTIVE
      sprintf(msg_cstr, "[%06d:%03d]", ID_EVERYONE, KEYBED_WORD_ACTIVE);
      msg = String(msg_cstr);
      mesh.sendBroadcast(msg);
      //
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}

// // some reaction for received msg.
// void reaction() {
// }
// Task reaction_task(10, 17, &reaction);

// saying hello
void greeting() {
  static String msg = "";
  sprintf(msg_cstr, "[%06d:%03d]", memberList[random(NUM_OF_MEMBERS)], KEYBED_WORD_HELLO); //"alien's terminal is me. ::)"
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

//
void setup_member() {

  //tasks
  runner.addTask(saying_greeting);
  saying_greeting.enable();
  // runner.addTask(reaction_task);

}
