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
  if (message == GLASS_PLAYTIME) {
    Serial.println("glass: play start ");
    fastturn_task.restartDelayed(100);
  }
}

// saying hello
void greeting() {
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", GLASS_HELLO);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("TX : " + msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// arrow_msg
extern Task arrow_msg_task;
void arrow_msg() {
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", ARROW_CHANGE);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  //
  arrow_msg_task.restartDelayed(random(1000*20, 1000*60));
}
Task arrow_msg_task(0, TASK_ONCE, &arrow_msg);

// float_msg
extern Task float_msg_task;
void float_msg() {
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", FLOAT_FLY);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  //
  float_msg_task.restartDelayed(random(1000*60*2, 1000*60*3));
}
Task float_msg_task(0, TASK_ONCE, &float_msg);

// play sequences
// note_1
void fastturn() {
  int r = random(400, 600);
  analogWrite(D6,r);
  Serial.print("fast:");
  Serial.println(r);
  slowturn_task.restartDelayed(20000);
}
Task fastturn_task(0, TASK_ONCE, &fastturn);
// note_2
void slowturn() {
  int r = random(300, 400);
  Serial.print("slow:");
  Serial.println(r);
  analogWrite(D6,r);
  rest_task.restartDelayed(15000);
}
Task slowturn_task(0, TASK_ONCE, &slowturn);
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
  runner.addTask(arrow_msg_task);
  arrow_msg_task.enable();
  runner.addTask(float_msg_task);
  float_msg_task.enable();

  runner.addTask(fastturn_task);
  runner.addTask(slowturn_task);
  runner.addTask(rest_task);

  rest_task.restartDelayed(500);
}
