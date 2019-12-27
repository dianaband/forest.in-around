// servo
#define SERVO_PIN D6
#include <Servo.h>
static Servo myservo;
#define HITTING_ANGLE 87
#define RELEASE_ANGLE 60
#define STABILIZE_ANGLE 53

//
extern Task hit_task;

//
extern Task pcontrol_task;
bool pcontrol_new = false;
int pcontrol_start = 0;
int pcontrol_target = 0;
int control_count = 0;

//
extern Task servo_release_task;

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
      message = msg.substring(8, 12).toInt();
      if (reaction_task.getRunCounter() == 0)
        reaction_task.restart();
      switch (message) {
      case BELL_WORD_RING_RING_RING:
        Serial.println("bell: ring ring.");
        hit_task.restartDelayed(100);
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
        if (mood != MOOD_SLEEP) mood = MOOD_HIGH;
        break;
      case KEYBED_WORD_ACTIVE:
        if (mood != MOOD_SLEEP) mood = MOOD_LOW;
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
    sprintf(msg_cstr, "[%06d:%03d]", memberList[random(NUM_OF_MEMBERS)], BELL_WORD_SLEEPING); //"zzzzzzzz"
  } else {
    sprintf(msg_cstr, "[%06d:%03d]", memberList[random(NUM_OF_MEMBERS)], BELL_WORD_HELLO); //"signal out~ take my signal~~ to every~~"
  }
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// routine
extern Task routine_task;
void routine() {
  static String msg = "";
  sprintf(msg_cstr, "[%06d:%03d] To look: look around now!", ID_LOOK, LOOK_WORD_LOOK_AROUND);
  msg = String(msg_cstr);
  //
  if (mood == MOOD_HIGH) {
    mesh.sendBroadcast(msg);
    routine_task.restartDelayed(random(1500, 5000));
  } else if (mood == MOOD_LOW) {
    mesh.sendBroadcast(msg);
    routine_task.restartDelayed(random(5000, 20000));
  } else if (mood == MOOD_SLEEP) {
    //do nothing
    routine_task.restartDelayed(1000*60*1);
  }
}
Task routine_task(0, TASK_ONCE, &routine);

// hit!
void hit() {
  static int count = 0;
  if (hit_task.isFirstIteration()) {
    count = 0;
    Serial.println("hit! start.");
  }
  if (count % 3 == 0) {
    //
    myservo.attach(SERVO_PIN);
    myservo.write(RELEASE_ANGLE);
    // servo_release_task.restartDelayed(200);
    //
  } else if (count % 3 == 1) {
    //
    myservo.attach(SERVO_PIN);
    myservo.write(HITTING_ANGLE);
    // servo_release_task.restartDelayed(200);
    //
    Serial.print("bell, bell, bell! : ");
    Serial.print(HITTING_ANGLE);
    Serial.println(" deg.");
    //
  } else {
    //
    myservo.attach(SERVO_PIN);
    myservo.write(RELEASE_ANGLE);
    servo_release_task.restartDelayed(200);
    //
    Serial.print("release to .. : ");
    Serial.print(RELEASE_ANGLE);
    Serial.println(" deg.");
    // start stablizing..
    pcontrol_new = true;
    pcontrol_start = RELEASE_ANGLE;
    pcontrol_target = STABILIZE_ANGLE;
    pcontrol_task.restartDelayed(80);
    //
    control_count = 0;
  }
  //
  count++;
}
Task hit_task(100, 3, &hit);

// pcontrol
void pcontrol() {
  static int angle;
  if (pcontrol_new == true) {
    pcontrol_new = false;
    angle = pcontrol_start;
  }
  int error = pcontrol_target - angle;
  int sign = (error >= 0 ? 1 : -1);
  //
  Serial.print("step-by-step to.. : ");
  Serial.println(sign);
  //
  if (error != 0) {
    angle = angle + sign; // most gentle move : 1 step each time.
    //
    Serial.print("stablizing in action ==> next angle : ");
    Serial.print(angle);
    Serial.println(" deg.");
    //
    myservo.attach(SERVO_PIN);
    myservo.write(angle);
    servo_release_task.restartDelayed(50);
    pcontrol_task.restartDelayed(400);
  }
  else {
    // stand-by processes
    if (control_count % 2 == 0) {
      pcontrol_new = true;
      pcontrol_start = STABILIZE_ANGLE;
      pcontrol_target = RELEASE_ANGLE;
      pcontrol_task.restartDelayed(300);
    } else if (control_count % 2 == 1) {
      pcontrol_new = true;
      pcontrol_start = RELEASE_ANGLE;
      pcontrol_target = STABILIZE_ANGLE;
      pcontrol_task.restartDelayed(300);
    }
    //
    control_count++;
  }
}
Task pcontrol_task(0, TASK_ONCE, &pcontrol); // hit -> 100ms -> step back -> 50ms -> slowly move to rest pos.

// pcontrol release
void servo_release() {
  myservo.detach();
}
Task servo_release_task(0, TASK_ONCE, &servo_release);

//
void setup_member() {
  //servo
  // myservo.attach(D6);

  //
  runner.addTask(saying_greeting);
  saying_greeting.enable();
  runner.addTask(routine_task);
  routine_task.restart();

  runner.addTask(reaction_task);
  runner.addTask(hit_task);
  runner.addTask(pcontrol_task);

  runner.addTask(servo_release_task);

  // hit_task.restart();
}
