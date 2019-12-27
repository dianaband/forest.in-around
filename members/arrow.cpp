//tasks
extern Task turn_task;
extern Task rest_task;

//global
int speed = 300;

// room protocol
static char msg_cstr[MSG_LENGTH_MAX] = {0, };
void gotChangedConnectionCallback() { // REQUIRED
}
void gotMessageCallback(uint32_t from, String & msg) { // REQUIRED
  Serial.println(msg);
  int message = msg.substring(1, 6).toInt();
  if (message == ARROW_CHANGE) {
    Serial.println("arrow: speed change! ");
    //turn_task.restartDelayed(100);
    speed = random(20, 300);
  }
}

// saying hello
void greeting() {
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", ARROW_HELLO);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("TX : " + msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// glass_msg
extern Task glass_msg_task;
void glass_msg() {
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", GLASS_PLAYTIME);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  //
  glass_msg_task.restartDelayed(random(1000*60*1, 1000*60*2)); // TEST
  // glass_msg_task.restartDelayed(random(1000*60*3, 1000*60*5));
}
Task glass_msg_task(0, TASK_ONCE, &glass_msg);

// bell_msg
extern Task bell_msg_task;
void bell_msg() {
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", BELL_RING_RING_RING);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  //
  bell_msg_task.restartDelayed(random(1000*60*3, 1000*60*5));
}
Task bell_msg_task(0, TASK_ONCE, &bell_msg);

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
  runner.addTask(glass_msg_task);
  glass_msg_task.enable();
  runner.addTask(bell_msg_task);
  bell_msg_task.enable();

  runner.addTask(turn_task);
  runner.addTask(rest_task);

  //
  turn_task.restartDelayed(100);
}
