//adafruit HUZZAH esp8266

//tasks
extern Task fastturn_task;
extern Task slowturn_task;
extern Task rest_task;

// room protocol
static char msg_cstr[MSG_LENGTH_MAX] = {0, };
void gotChangedConnectionCallback() { // REQUIRED
}
void gotMessageCallback(uint32_t from, String & msg) { // REQUIRED
  Serial.println(msg);
  int message = msg.substring(1, 6).toInt();
  if (message == FLOAT_FLY) {
    Serial.println("FLOAT_FLY");
    fastturn_task.restartDelayed(100);
  }
}

// saying hello
void greeting() {
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", FLOAT_HELLO);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("TX : " + msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// // p2p_msg --> GLASS_PLAYTIME
// extern Task p2p_msg_task;
// void p2p_msg() {
//   static String msg = "";
//   sprintf(msg_cstr, "[%05d]", GLASS_PLAYTIME);
//   msg = String(msg_cstr);
//   mesh.sendBroadcast(msg);
//   //
//   //p2p_msg_task.restartDelayed(random(1000*60*3, 1000*60*5));
//   p2p_msg_task.restartDelayed(random(1000*20, 1000*60));
// }
// Task p2p_msg_task(0, TASK_ONCE, &p2p_msg);

// play sequences
// note_1
void fastturn() {
  int r = random(400, 600);
  analogWrite(12,r);
  Serial.print("fast:");
  Serial.println(r);
  slowturn_task.restartDelayed(20000);
}
Task fastturn_task(0, TASK_ONCE, &fastturn);
// note_2
void slowturn() {
  int r = random(200, 400);
  Serial.print("slow:");
  Serial.println(r);
  analogWrite(12,r);
  rest_task.restartDelayed(15000);
}
Task slowturn_task(0, TASK_ONCE, &slowturn);
// fin
void rest() {
  analogWrite(12,0);
}
Task rest_task(0, TASK_ONCE, &rest);

//
void setup_member() {
  //random seed
  randomSeed(analogRead(0));

  //i2c master
  pinMode(12, OUTPUT);

  runner.addTask(saying_greeting);
  saying_greeting.enable();
  // runner.addTask(p2p_msg_task);
  // p2p_msg_task.enable();

  runner.addTask(fastturn_task);
  runner.addTask(slowturn_task);
  runner.addTask(rest_task);

  rest_task.restartDelayed(500);
}
