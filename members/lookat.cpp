// servo
#define SERVO_PIN D6
#include <Servo.h>
static Servo myservo;
extern Task servo_release_task;

// my tasks
extern Task lookat_task;
extern Task saying_greeting;

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
      case LOOK_WORD_LOOK_AROUND:
        Serial.println("look: me to looking around?? well, but where?");
        lookat_task.restart();
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
      case MONITOR_WORD_SLEEP:
        mood = MOOD_SLEEP;
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
    tone(D7, 800 + count * 50);
  }
  else {
    noTone(D7);
  }
  if (reaction_task.isLastIteration()) {
    noTone(D7);
  }
  mask = mask >> 1;
  count++;
}
Task reaction_task(10, 17, &reaction);

// saying hello
void greeting() {
  static String msg = "";
  if (mood == MOOD_SLEEP) {
    sprintf(msg_cstr, "[%06d:%03d]", memberList[random(NUM_OF_MEMBERS)], LOOK_WORD_SLEEPING); //"zzzzzzzz"
  } else {
    sprintf(msg_cstr, "[%06d:%03d]", memberList[random(NUM_OF_MEMBERS)], LOOK_WORD_HELLO); //"Me? I do look at you!"
  }
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// routine
extern Task routine_task;
void routine() {
  static String msg = "";
  sprintf(msg_cstr, "[%06d:%03d]", ID_BELL, BELL_WORD_RING_RING_RING);
  msg = String(msg_cstr);

  //
  if (mood == MOOD_HIGH) {
    mesh.sendBroadcast(msg);
    routine_task.restartDelayed(random(1000*60*3, 1000*60*5));
  } else if (mood == MOOD_LOW) {
    mesh.sendBroadcast(msg);
    routine_task.restartDelayed(1000*60*5);
  } else if (mood == MOOD_SLEEP) {
    // do nothing
    routine_task.restartDelayed(1000*60*1);
  }
}
Task routine_task(0, TASK_ONCE, &routine);

// looking around once.
void lookat() {
  int angle = random(40, 140);
  //
  Serial.print("i will look at now @ ");
  Serial.print(angle);
  Serial.println(" deg.");
  //
  myservo.attach(D6);
  myservo.write(angle);
  servo_release_task.restartDelayed(100);
}
Task lookat_task(0, TASK_ONCE, &lookat);

// servo release
void servo_release() {
  myservo.detach();
}
Task servo_release_task(0, TASK_ONCE, &servo_release);

//setup_member
void setup_member() {

  //servo
  // myservo.attach(D6);

  //tone
  pinMode(D7, OUTPUT);

  //tasks
  runner.addTask(saying_greeting);
  saying_greeting.enable();
  runner.addTask(routine_task);
  routine_task.enable();

  runner.addTask(routine_task);
  routine_task.enable();
  //
  runner.addTask(lookat_task);
  //
  runner.addTask(servo_release_task);
  runner.addTask(reaction_task);
}
