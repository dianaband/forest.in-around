//tasks
extern Task fastturn_task;
extern Task slowturn_task;
extern Task rest_task;

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
    case GLASS_WORD_PLAYTIME:
      Serial.println("glass: play start ");
      fastturn_task.restartDelayed(100);
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
  sprintf(msg_cstr, "[%06d:%03d]", memberList[random(NUM_OF_MEMBERS)], GLASS_WORD_HELLO); //"(criririririri)"
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// arrow_msg
extern Task arrow_msg_task;
void arrow_msg() {
  static String msg = "";
  sprintf(msg_cstr, "[%06d:%03d]", ID_ARROW, ARROW_WORD_CHANGE);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  //
  arrow_msg_task.restartDelayed(random(1000*20, 1000*60));
}
Task arrow_msg_task(0, TASK_ONCE, &arrow_msg);

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

  runner.addTask(fastturn_task);
  runner.addTask(slowturn_task);
  runner.addTask(reaction_task);
  runner.addTask(rest_task);

  rest_task.restartDelayed(500);
}
