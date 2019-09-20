// room protocol
static int message = 0;
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
  theme++; if (theme > N_THEMES) theme = 0;
  //

  //
  if (theme == 0) {
    //
    // indep_random + soundset 01~10
    //

    //
    Serial.println("THEME => 0");
    //
    sprintf(msg_cstr, "[%05d:%02d]", SPEAKERS_PLAYMODE, SPEAKERS_PLAYMODE_INDEP);
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
    Serial.println("TX : SPEAKERS_PLAYMODE == SPEAKERS_PLAYMODE_INDEP");
    //
    speaker_a_tick_task.disable();
    //
    // start a vspeed changer..
    //
  } else if (theme == 1) {
    ;
  } else if (theme == 2) {
    ;
  } else if (theme == 3) {
    ;
  }
}
Task playloop_task(1000*6, TASK_FOREVER, &playloop); // every 6 min. play theme changes.

//
void setup_member() {

  //
  runner.addTask(speaker_a_tick_task);
  runner.addTask(playloop_task);
  playloop_task.enable();
  playloop_task.restartDelayed(100);
}
