// servo
#define SERVO_PIN D6
#include <Servo.h>
static Servo myservo;
// #define HITTING_ANGLE 87 // mild hit. + fails sometimes..
#define HITTING_ANGLE 89
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

// room protocol
static char msg_cstr[MSG_LENGTH_MAX] = {0, };
void gotChangedConnectionCallback() { // REQUIRED
}
void gotMessageCallback(uint32_t from, String & msg) { // REQUIRED
  Serial.println(msg);
  int message = msg.substring(1, 6).toInt();
  if (message == BELL_RING_RING_RING) {
    Serial.println("bell: ring ring.");
    hit_task.restartDelayed(100);
  }
}

// saying hello
void greeting() {
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", BELL_HELLO);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("TX : " + msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// // p2p_msg -> ARROW_CHANGE
// extern Task p2p_msg_task;
// void p2p_msg() {
//   static String msg = "";
//   sprintf(msg_cstr, "[%05d]", ARROW_CHANGE);
//   msg = String(msg_cstr);
//   mesh.sendBroadcast(msg);
//   //
//   p2p_msg_task.restartDelayed(random(1000*20, 1000*60));
// }
// Task p2p_msg_task(0, TASK_ONCE, &p2p_msg);

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
    pcontrol_task.restartDelayed(280);
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
  //random seed
  randomSeed(analogRead(0));

  //
  runner.addTask(saying_greeting);
  saying_greeting.enable();
  // runner.addTask(p2p_msg_task);
  // p2p_msg_task.enable();

  runner.addTask(hit_task);
  runner.addTask(pcontrol_task);
  runner.addTask(servo_release_task);

  //
  pcontrol_task.restart();
}
