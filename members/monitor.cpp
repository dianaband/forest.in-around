// mood
int mood = EVERYONE_MOOD_LOW;

// names for all the members
String names[NUM_OF_MEMBERS] = {
  "Gas",
  "Trunk",
  "Drum",
  "Reel",
  "Float",
  "Speak_A",
  "Speak_B",
  "Speak_C",
  "Speak_D",
  "Speak_E",
  "Speak_F",
  "Monitor"
};

// presence monitoring for all the members
int presence[NUM_OF_MEMBERS];

// awakeness monitoring for all the members
int awakeness[NUM_OF_MEMBERS]; // 1 : awake, 0 : sleeping, -1 : unknown

// room protocol
static int message = 0;
static char msg_cstr[MSG_LENGTH_MAX] = {0, };
void gotChangedConnectionCallback() { // REQUIRED
}
void gotMessageCallback(uint32_t from, String & msg) { // REQUIRED
  Serial.println(msg);
  message = msg.substring(1, 6).toInt();
  switch (message)
  {
  // we are interested in all those 'hello' messages.
  case GAS_HELLO:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_GAS) {
        presence[idx] = 10;   // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 1;   // it's awake.
      }
    }
    break;
  case GAS_SLEEPING:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_GAS) {
        presence[idx] = 10;   // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 0;   // it's sleeping
      }
    }
    break;
  case TRUNK_HELLO:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_TRUNK) {
        presence[idx] = 10;   // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 1;   // it's awake.
      }
    }
    break;
  case TRUNK_SLEEPING:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_TRUNK) {
        presence[idx] = 10;   // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 0;   // it's sleeping
      }
    }
    break;
  case DRUM_HELLO:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_DRUM) {
        presence[idx] = 10;   // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 1;   // it's awake.
      }
    }
    break;
  case DRUM_SLEEPING:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_DRUM) {
        presence[idx] = 10;   // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 0;   // it's sleeping
      }
    }
    break;
  case FLOAT_HELLO:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_FLOAT) {
        presence[idx] = 10;   // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 1;   // it's awake.
      }
    }
    break;
  case FLOAT_SLEEPING:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_FLOAT) {
        presence[idx] = 10;   // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 0;   // it's sleeping
      }
    }
    break;
  case REEL_HELLO:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_REEL) {
        presence[idx] = 10;   // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 1;   // it's awake.
      }
    }
    break;
  case REEL_SLEEPING:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_REEL) {
        presence[idx] = 10;   // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 0;   // it's sleeping
      }
    }
    break;
  case SPEAK_A_HELLO:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_SPEAK_A) {
        presence[idx] = 10;     // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 1;     // it's awake.
      }
    }
    break;
  case SPEAK_A_SLEEPING:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_SPEAK_A) {
        presence[idx] = 10;     // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 0;     // it's sleeping
      }
    }
    break;
  case SPEAK_B_HELLO:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_SPEAK_B) {
        presence[idx] = 10;       // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 1;       // it's awake.
      }
    }
    break;
  case SPEAK_B_SLEEPING:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_SPEAK_B) {
        presence[idx] = 10;       // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 0;       // it's sleeping
      }
    }
    break;
  case SPEAK_C_HELLO:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_SPEAK_C) {
        presence[idx] = 10;         // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 1;         // it's awake.
      }
    }
    break;
  case SPEAK_C_SLEEPING:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_SPEAK_C) {
        presence[idx] = 10;         // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 0;         // it's sleeping
      }
    }
    break;
  case SPEAK_D_HELLO:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_SPEAK_D) {
        presence[idx] = 10;           // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 1;           // it's awake.
      }
    }
    break;
  case SPEAK_D_SLEEPING:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_SPEAK_D) {
        presence[idx] = 10;           // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 0;           // it's sleeping
      }
    }
    break;
  case SPEAK_E_HELLO:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_SPEAK_E) {
        presence[idx] = 10;             // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 1;             // it's awake.
      }
    }
    break;
  case SPEAK_E_SLEEPING:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_SPEAK_E) {
        presence[idx] = 10;             // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 0;             // it's sleeping
      }
    }
    break;
  case SPEAK_F_HELLO:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_SPEAK_F) {
        presence[idx] = 10;               // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 1;               // it's awake.
      }
    }
    break;
  case SPEAK_F_SLEEPING:
    for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
      if (memberList[idx] == ID_SPEAK_F) {
        presence[idx] = 10;               // 1 greeting per every 10 seconds expected. (1 fps)
        awakeness[idx] = 0;               // it's sleeping
      }
    }
    break;
  default:
    ;
  }
}

// //screen task
// void loop_screen() {
//   //
//   // tft.fillScreen(HX8357_BLACK);
//   //
//   int color = HX8357_BLACK;
//   for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
//     // place markings
//     tft.drawRect(idx * (boxsize + 2), idx * boxsize * 2, 100 + 2, boxsize + 2, HX8357_WHITE);
//     // name
//     tft.setCursor(idx * (boxsize + 2) + 100 + 2 + 5, idx * boxsize * 2);
//     tft.setTextColor(HX8357_WHITE);
//     tft.setTextSize(1);
//     tft.print(names[idx]);
//     // color coding..
//     if (awakeness[idx] == 0) {
//       color = HX8357_BLUE; // sleeping
//     } else if (awakeness[idx] == 1) {
//       color = HX8357_YELLOW; // awake
//     } else if (awakeness[idx] == -1) {
//       color = HX8357_BLACK; // unknown
//     }
//     // awakeness & presence markings
//     tft.fillRect(idx * (boxsize + 2) + 1, idx * boxsize * 2 + 1, 100, boxsize, HX8357_BLACK);
//     delay(2);
//     tft.fillRect(idx * (boxsize + 2) + 1, idx * boxsize * 2 + 1, presence[idx] * 10, boxsize, color);
//     // presence decrease
//     if (presence[idx] > 0) {
//       presence[idx] = presence[idx] - 1;
//     }
//   };
//   // draw mode control buttons
//   tft.fillCircle(wakeup_button_x, wakeup_button_y, wakeup_button_r, HX8357_YELLOW);
//   tft.setTextColor(HX8357_WHITE);
//   tft.setCursor(150, 290);
//   tft.setTextSize(2);
//   tft.print("Wake up!");
//   tft.fillCircle(sleep_button_x, sleep_button_y, sleep_button_r, HX8357_BLUE);
//   tft.setTextColor(HX8357_WHITE);
//   tft.setCursor(70, 420);
//   tft.setTextSize(2);
//   tft.print("Good night~");
// }
// Task loop_screen_task(1000, TASK_FOREVER, &loop_screen); // fps : 1hz
//
// //touch task
// void loop_touch() {
//   // Retrieve a point
//   TS_Point p = ts.getPoint();
//
//   // Serial.print("X = ");
//   // Serial.print(p.x);
//   // Serial.print("\tY = ");
//   // Serial.print(p.y);
//   // Serial.print("\tPressure = ");
//   // Serial.println(p.z);
//
//   // Scale from ~0->4000 to tft.width using the calibration #'s
//   p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
//   p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
//
//   //
//   float dist = 0.0;
//
//   //
//   dist = sqrt((p.x - wakeup_button_x) * (p.x - wakeup_button_x) + (p.y - wakeup_button_y) * (p.y - wakeup_button_y));
//   if (dist < wakeup_button_r) {
//     //wake up button touched! ---> send wake_up message to everyone.
//     static String msg = "";
//     sprintf(msg_cstr, "[%06d:%03d]", ID_EVERYONE, MONITOR_WAKEUP);
//     msg = String(msg_cstr);
//     mesh.sendBroadcast(msg);
//   }
//
//   //
//   dist = sqrt((p.x - sleep_button_x) * (p.x - sleep_button_x) + (p.y - sleep_button_y) * (p.y - sleep_button_y));
//   if (dist < sleep_button_r) {
//     //sleep button touched! ---> send sleep message to everyone.
//     static String msg = "";
//     sprintf(msg_cstr, "[%06d:%03d]", ID_EVERYONE, MONITOR_SLEEP);
//     msg = String(msg_cstr);
//     mesh.sendBroadcast(msg);
//   }
// }
// Task loop_touch_task(100, TASK_FOREVER, &loop_touch); // touch sensing --> 0.1s

//msg_reel task
void loop_msg_reel() {
  //
  static String msg = "";
  sprintf(msg_cstr, "[%05d]", REEL_TURN);
  msg = String(msg_cstr);
  mesh.sendBroadcast(msg);
  Serial.println("TX : " + msg);
}
Task loop_msg_reel_task(10000, TASK_FOREVER, &loop_msg_reel); // touch sensing --> 0.1s

//
void setup_member() {

  //array init.
  for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
    presence[idx] = 0;
    awakeness[idx] = -1; // 1 : awake, 0 : sleeping, -1 : unknown
  }

  //
  // runner.addTask(loop_screen_task);
  // loop_screen_task.enable();
  // runner.addTask(loop_touch_task);
  // loop_touch_task.enable();

  //
  runner.addTask(loop_msg_reel_task);
  loop_msg_reel_task.enable();
}
