// servo
#define SERVO_PIN D6
#include <Servo.h>
static Servo myservo;
extern Task servo_release_task;

// my tasks
extern Task scratch_task;
extern Task saying_greeting;

// room protocol
static char msg_cstr[MSG_LENGTH_MAX] = {0, };
void gotChangedConnectionCallback() { // REQUIRED
}
void gotMessageCallback(uint32_t from, String & msg) { // REQUIRED
  Serial.println(msg);
  int message = msg.substring(1, 6).toInt();
  if (message == DRUM_SCRATCH) {
    Serial.println("DRUM_SCRATCH");
    scratch_task.restartDelayed(100);
  }
}

// saying hello
void greeting() {
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", DRUM_HELLO);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
}
Task saying_greeting(10000, TASK_FOREVER, &greeting);

// scratch.
void scratch() {
  int angle = random(60, 140);
  //
  Serial.print("scratch go -> ");
  Serial.print(angle);
  Serial.println(" deg.");
  //
  myservo.attach(D6);
  myservo.write(angle);
  servo_release_task.restartDelayed(100);
}
Task scratch_task(0, TASK_ONCE, &scratch);

// servo release
void servo_release() {
  myservo.detach();
}
Task servo_release_task(0, TASK_ONCE, &servo_release);

//setup_member
void setup_member() {

  //servo
  // myservo.attach(D6);

  //tasks
  runner.addTask(saying_greeting);
  saying_greeting.enable();

  //
  runner.addTask(servo_release_task);

  //
  runner.addTask(scratch_task);
}
