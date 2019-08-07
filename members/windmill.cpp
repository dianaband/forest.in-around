//tasks
extern Task on_task;
extern Task off_task;

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
    case WINDMILL_WORD_BLOW:
      Serial.println("windmill: blow start ");
      on_task.restartDelayed(100);
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
  sprintf(msg_cstr, "[%06d:%03d]", memberList[random(NUM_OF_MEMBERS)], WINDMILL_WORD_HELLO); //"Que tal? Me llame Santa Claudius, mi amigo!"
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// bag_msg_sing
extern Task bag_msg_sing_task;
void bag_msg_sing() {
  static String msg = "";
  sprintf(msg_cstr, "[%06d:%03d]", ID_BAG, BAG_WORD_SING);
  msg = String(msg_cstr);
  //
  if (mood == MOOD_HIGH) {
    mesh.sendBroadcast(msg);
  } else if (mood == MOOD_LOW) {
    // do nothing.
  }
  //
  bag_msg_sing_task.restartDelayed(random(1000*60*3, 1000*60*4));
}
Task bag_msg_sing_task(0, TASK_ONCE, &bag_msg_sing);

// bag_msg_handle
extern Task bag_msg_handle_task;
void bag_msg_handle() {
  static String msg = "";
  static bool toggle = false;
  toggle = !toggle;
  sprintf(msg_cstr, "[%06d:%03d]", ID_BAG, (toggle ? BAG_WORD_HANDLE_UP : BAG_WORD_HANDLE_DOWN));
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  //
  bag_msg_handle_task.restartDelayed(random(1000*60*5, 1000*60*7));
}
Task bag_msg_handle_task(0, TASK_ONCE, &bag_msg_handle);

// switch 'on'
void on() {
  digitalWrite(D6, HIGH);
  Serial.print("pin D6 <= HIGH.");
  off_task.restartDelayed(20000);
}
Task on_task(0, TASK_ONCE, &on);
// off
void off() {
  digitalWrite(D6, LOW);
  Serial.print("pin D6 <= LOW.");
}
Task off_task(0, TASK_ONCE, &off);

//
void setup_member() {
  //random seed
  randomSeed(analogRead(0));

  //pwm out
  pinMode(D6, OUTPUT);

  runner.addTask(saying_greeting);
  saying_greeting.enable();
  runner.addTask(bag_msg_sing_task);
  bag_msg_sing_task.enable();
  runner.addTask(bag_msg_handle_task);
  bag_msg_handle_task.enable();

  runner.addTask(on_task);
  runner.addTask(off_task);
  runner.addTask(reaction_task);

  //off_task.restartDelayed(100);
  on_task.restartDelayed(100);
}
