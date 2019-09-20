//tasks
extern Task fastturn_task;
extern Task slowturn_task;
extern Task rest_task;

// mood
int mood = EVERYONE_MOOD_LOW;

// room protocol
static int message = 0;
static char msg_cstr[MSG_LENGTH_MAX] = {0, };
void gotChangedConnectionCallback() { // REQUIRED
}
void gotMessageCallback(uint32_t from, String & msg) { // REQUIRED
  Serial.println(msg);
  message = msg.substring(1, 6).toInt();
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

void fastturn() {
  int r = random(400, 600);
  analogWrite(12,r);
  Serial.print("fast:");
  Serial.println(r);
  slowturn_task.restartDelayed(20000);
}
Task fastturn_task(0, TASK_ONCE, &fastturn);

void slowturn() {
  int r = random(200, 400);
  Serial.print("slow:");
  Serial.println(r);
  analogWrite(12,r);
  rest_task.restartDelayed(15000);
}
Task slowturn_task(0, TASK_ONCE, &slowturn);

void rest() {
  analogWrite(12,0);
  // fastturn_task.restartDelayed(100);
}
Task rest_task(0, TASK_ONCE, &rest);


void setup_member() {
  //random seed
  randomSeed(analogRead(0));

  //i2c master
  pinMode(12, OUTPUT);

  runner.addTask(saying_greeting);
  saying_greeting.enable();

  runner.addTask(fastturn_task);
  runner.addTask(slowturn_task);
  runner.addTask(rest_task);

  fastturn_task.restartDelayed(500);
}
