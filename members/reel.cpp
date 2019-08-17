//tasks
extern Task on_task;
extern Task off_task;

// mood
int mood = MOOD_SLEEP;

// room protocol
static int message = 0;
static char msg_cstr[MSG_LENGTH_MAX] = {0, };
extern Task reaction_task;
void gotChangedConnectionCallback() { // REQUIRED
}
void gotMessageCallback(uint32_t from, String & msg) { // REQUIRED
  Serial.println(msg);
  // am i awake?
  if (mood == MOOD_SLEEP) {
    // i am sleeping so, only 'wake-up!' message is meaningful to me.
    if (msg.substring(8, 12).toInt() == MONITOR_WORD_WAKEUP) {
      mood = MOOD_HIGH;
    }
  } else {
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
      case REEL_WORD_PLAYTIME:
        Serial.println("reel: play time! ");
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
        off_task.restartDelayed(100);
        break;
      case MONITOR_WORD_SLEEP:
        mood = MOOD_SLEEP;
        off_task.restartDelayed(100);
        break;
      default:
        ;
      }
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
  if (mood == MOOD_SLEEP) {
    sprintf(msg_cstr, "[%06d:%03d]", memberList[random(NUM_OF_MEMBERS)], REEL_WORD_SLEEPING); //"zzzzzzzz"
  } else {
    sprintf(msg_cstr, "[%06d:%03d]", memberList[random(NUM_OF_MEMBERS)], REEL_WORD_HELLO); //"reeeeeeeeeeeeeee::::::::::::"
  }
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// peak_msg_ppippi
extern Task peak_msg_ppippi_task;
void peak_msg_ppippi() {
  static String msg = "";
  sprintf(msg_cstr, "[%06d:%03d]", ID_PEAK, PEAK_WORD_PPI_PPI_PPI);
  msg = String(msg_cstr);
  //
  if (mood == MOOD_HIGH) {
    mesh.sendBroadcast(msg);
  } else {
    // do nothing
  }
  //
  peak_msg_ppippi_task.restartDelayed(random(1000*60*4, 1000*60*5));
}
Task peak_msg_ppippi_task(0, TASK_ONCE, &peak_msg_ppippi);

// switch 'on'
void on() {
  digitalWrite(D6, HIGH);
  Serial.print("pin D6 <= HIGH.");
  off_task.restartDelayed(1000*60*(1 + random(5) * 0.1));
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
  runner.addTask(peak_msg_ppippi_task);
  peak_msg_ppippi_task.enable();

  runner.addTask(on_task);
  runner.addTask(off_task);
  runner.addTask(reaction_task);

  off_task.restartDelayed(100);
}
