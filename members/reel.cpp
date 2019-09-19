//tasks
extern Task on_task;
extern Task off_task;

// // mood
// int mood = MOOD_SLEEP;

// room protocol
static int message = 0;
static char msg_cstr[MSG_LENGTH_MAX] = {0, };
void gotChangedConnectionCallback() { // REQUIRED
}
void gotMessageCallback(uint32_t from, String & msg) { // REQUIRED
  Serial.println(msg);
  message = msg.substring(1, 6).toInt();
  // speakers event
  if (message == REEL_TURN) {
    Serial.println("REEL_TURN");
    on_task.restartDelayed(100);
  }
  // // everyone event
  // if (message == EVERYONE_MOOD_HIGH) {
  //   mood = EVERYONE_MOOD_HIGH;
  // }
  // if (message == EVERYONE_MOOD_LOW) {
  //   mood = EVERYONE_MOOD_LOW;
  // }
}

// saying hello
void greeting() {
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", REEL_HELLO);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("TX : " + msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// switch 'on'
void on() {
  digitalWrite(D6, LOW);
  Serial.println("pin D6 <= LOW(ON)");
  off_task.restartDelayed(1000*60*(1 + random(5) * 0.1));
  // off_task.restartDelayed(1000*(1 + random(5)));
}
Task on_task(0, TASK_ONCE, &on);
// off
void off() {
  digitalWrite(D6, HIGH);
  Serial.println("pin D6 <= HIGH(OFF)");
}
Task off_task(0, TASK_ONCE, &off);

//
void setup_member() {
  //random seed
  randomSeed(analogRead(0));

  //pwm out
  pinMode(D6, OUTPUT);

  //
  runner.addTask(saying_greeting);
  saying_greeting.enable();

  //
  runner.addTask(on_task);
  runner.addTask(off_task);

  //
  off_task.restartDelayed(100);
}
