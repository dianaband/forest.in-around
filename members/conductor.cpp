// room protocol
static char msg_cstr[MSG_LENGTH_MAX] = {0, };
void gotChangedConnectionCallback() { // REQUIRED
}
void gotMessageCallback(uint32_t from, String & msg) { // REQUIRED
}

// sound theme
#define N_THEMES 4
int theme = 0;

// vspeed
int vspeed = 0;

// soundset
int soundset = 0;

//speakers soundset changer
// // speakers mode changer
// // //speakers tic task
// // speakers speed changer

extern Task speaker_a_tick_task;
void speaker_a_tick() {
  //
  int base_speed = 1000 + (vspeed * 10);
  int random_portion = base_speed * 0.1;
  //
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", SPEAK_A_TIC);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("TX : " + msg);
  //
  speaker_a_tick_task.restartDelayed(base_speed + random(random_portion));
}
Task speaker_a_tick_task(0, TASK_ONCE, &speaker_a_tick);

extern Task playloop_task;
void playloop() {
  static String msg = "";

  //
  // theme : 0 ~ (N_THEMES - 1)
  theme++; if (theme >= N_THEMES) theme = 0;
  //

  //
  Serial.print("THEME => ");
  Serial.println(theme);
  //

  if (theme == 0) {
    //
    // directional propagation + soundset 01~10 + vspeed 20
    //
    //
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PLAYMODE, SPEAKERS_PLAYMODE_PROPA);
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.println("TX : SPEAKERS_PLAYMODE == SPEAKERS_PLAYMODE_PROPA");
    //
    soundset = 1; // soundset ==> 1 ~ 99
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PARA_SNDSET, soundset); // soundset ==> give starting sound #..
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.print("TX : SPEAKERS_PARA_SNDSET == ");
    Serial.println(soundset);
    Serial.println(msg);
    //
    vspeed = 99; // vspeed ==> 0 ~ 99
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PARA_SPEED, vspeed);
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.print("TX : SPEAKERS_PARA_SPEED == ");
    Serial.println(vspeed);
    Serial.println(msg);
    //
    speaker_a_tick_task.restartDelayed(1000);
    //
    // start a vspeed changer..
    //
  } else if (theme == 1) {
    //
    // indep_random + soundset 01~10
    //
    //
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PLAYMODE, SPEAKERS_PLAYMODE_INDEP);
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.println("TX : SPEAKERS_PLAYMODE == SPEAKERS_PLAYMODE_INDEP");
    //
    soundset = 1; // soundset ==> 1 ~ 99
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PARA_SNDSET, soundset); // soundset ==> give starting sound #..
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.print("TX : SPEAKERS_PARA_SNDSET == ");
    Serial.println(soundset);
    Serial.println(msg);
    //
    vspeed = 99; // vspeed ==> 0 ~ 99
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PARA_SPEED, vspeed);
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.print("TX : SPEAKERS_PARA_SPEED == ");
    Serial.println(vspeed);
    Serial.println(msg);
    //
    speaker_a_tick_task.disable();
    //
    // start a vspeed changer..
    //
  } else if (theme == 2) {
    //
    // directional propagation + soundset 01~10 + vspeed 0
    //
    //
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PLAYMODE, SPEAKERS_PLAYMODE_PROPA);
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.println("TX : SPEAKERS_PLAYMODE == SPEAKERS_PLAYMODE_PROPA");
    //
    soundset = 11; // soundset ==> 1 ~ 99
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PARA_SNDSET, soundset); // soundset ==> give starting sound #..
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.print("TX : SPEAKERS_PARA_SNDSET == ");
    Serial.println(soundset);
    Serial.println(msg);
    //
    vspeed = 99; // vspeed ==> 0 ~ 99
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PARA_SPEED, vspeed);
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.print("TX : SPEAKERS_PARA_SPEED == ");
    Serial.println(vspeed);
    Serial.println(msg);
    //
    speaker_a_tick_task.restartDelayed(1000);
    //
    // start a vspeed changer..
    //
  } else if (theme == 3) {
    //
    // indep_random + soundset 01~10
    //
    //
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PLAYMODE, SPEAKERS_PLAYMODE_INDEP);
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.println("TX : SPEAKERS_PLAYMODE == SPEAKERS_PLAYMODE_INDEP");
    //
    soundset = 11; // soundset ==> 1 ~ 99
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PARA_SNDSET, soundset); // soundset ==> give starting sound #..
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.print("TX : SPEAKERS_PARA_SNDSET == ");
    Serial.println(soundset);
    Serial.println(msg);
    //
    vspeed = 99; // vspeed ==> 0 ~ 99
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PARA_SPEED, vspeed);
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.print("TX : SPEAKERS_PARA_SPEED == ");
    Serial.println(vspeed);
    Serial.println(msg);
    //
    speaker_a_tick_task.disable();
    //
    // start a vspeed changer..
    //
  }
}
// Task playloop_task(1000*60*3, TASK_FOREVER, &playloop); // every 6 min. play theme changes.
Task playloop_task(1000*60*1.5, TASK_FOREVER, &playloop); // every 6 min. play theme changes.
// Task playloop_task(1000*20, TASK_FOREVER, &playloop); // every 6 min. play theme changes.

//msg_reel task
extern Task loop_msg_reel_task;
void loop_msg_reel() {
  //
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", REEL_TURN);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("TX : " + msg);
  //
  loop_msg_reel_task.restartDelayed(random(1000*60*1.5, 1000*60*2));
}
Task loop_msg_reel_task(0, TASK_ONCE, &loop_msg_reel);

//msg_float task
extern Task loop_msg_float_task;
void loop_msg_float() {
  //
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", FLOAT_FLY);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("TX : " + msg);
  //
  loop_msg_float_task.restartDelayed(random(1000*60*2, 1000*60*2.5));
}
Task loop_msg_float_task(0, TASK_ONCE, &loop_msg_float);

//msg_gas task
extern Task loop_msg_gas_task;
void loop_msg_gas() {
  //
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", GAS_RING_RING_RING);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("TX : " + msg);
  //
  loop_msg_gas_task.restartDelayed(random(800, 3000));
}
Task loop_msg_gas_task(0, TASK_ONCE, &loop_msg_gas);

//msg_drum task
extern Task loop_msg_drum_task;
void loop_msg_drum() {
  //
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", DRUM_SCRATCH);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("TX : " + msg);
  //
  loop_msg_drum_task.restartDelayed(random(800, 3000));
}
Task loop_msg_drum_task(0, TASK_ONCE, &loop_msg_drum);

//
void setup_member() {

  //
  runner.addTask(loop_msg_reel_task);
  loop_msg_reel_task.enable();
  loop_msg_reel_task.restartDelayed(100);

  //
  runner.addTask(loop_msg_float_task);
  loop_msg_float_task.enable();
  loop_msg_float_task.restartDelayed(100);

  //
  runner.addTask(loop_msg_gas_task);
  loop_msg_gas_task.enable();
  loop_msg_gas_task.restartDelayed(100);

  //
  runner.addTask(loop_msg_drum_task);
  loop_msg_drum_task.enable();
  loop_msg_drum_task.restartDelayed(100);

  //
  runner.addTask(speaker_a_tick_task);
  runner.addTask(playloop_task);
  playloop_task.enable();
  playloop_task.restartDelayed(100);
}
