//tasks
extern Task turn_task;
extern Task rest_task; // not used, yet

//global
int speed = 300;

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
    case ARROW_WORD_CHANGE:
      Serial.println("arrow: speed change! ");
      //turn_task.restartDelayed(100);
      speed = random(20, 300);
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
  sprintf(msg_cstr, "[%06d:%03d]", memberList[random(NUM_OF_MEMBERS)], ARROW_WORD_HELLO); //"which direction is you?"
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// routine
extern Task routine_task;
void routine() {
  static String msg = "";
  sprintf(msg_cstr, "[%06d:%03d]", ID_GLASS, GLASS_WORD_PLAYTIME);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  //
  routine_task.restartDelayed(random(1000*60*3, 1000*60*5));
}
Task routine_task(0, TASK_ONCE, &routine);

// play sequences
// note_1
void turn() {
  analogWrite(D6,speed);
  Serial.print("arrow_speed:");
  Serial.println(speed);
  turn_task.restartDelayed(1000); // speed updates every 1 sec.
}
Task turn_task(0, TASK_ONCE, &turn);
// fin
void rest() {
  analogWrite(D6,0);
}
Task rest_task(0, TASK_ONCE, &rest);

//
void setup_member() {
  //random seed
  randomSeed(analogRead(0));

  //pwm out
  pinMode(D6, OUTPUT);

  runner.addTask(saying_greeting);
  saying_greeting.enable();
  runner.addTask(routine_task);
  routine_task.enable();

  runner.addTask(turn_task);
  runner.addTask(reaction_task);
  runner.addTask(rest_task);

  turn_task.restartDelayed(100); // for TEST
}
