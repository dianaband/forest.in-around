// mood
int mood = MOOD_SLEEP;

// names for all the members
String names[NUM_OF_MEMBERS] = {
  "Bell",
  "Float",
  "Bag",
  "Look",
  "Windmill",
  "Glass",
  "Reel",
  "Arrow",
  "Thunder",
  "Fur",
  "Peak",
  "Keybed",
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
  // is it for me?
  int receipent = msg.substring(1, 7).toInt();
  if (1) {
    // always true
    //     ---> 'monitor' agent will simply listen to every messages == 'eavesdropping'
    // what it says?
    message = msg.substring(8, 12).toInt();
    // so, what to do, then?
    switch (message)
    {
    // we are interested in all those 'hello' messages.
    case BELL_WORD_HELLO:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_BELL) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 1; // it's awake.
        }
      }
      break;
    case BELL_WORD_SLEEPING:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_BELL) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 0; // it's sleeping
        }
      }
      break;
    case FLOAT_WORD_HELLO:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_FLOAT) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 1; // it's awake.
        }
      }
      break;
    case FLOAT_WORD_SLEEPING:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_FLOAT) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 0; // it's sleeping
        }
      }
      break;
    case BAG_WORD_HELLO:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_BAG) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 1; // it's awake.
        }
      }
      break;
    case BAG_WORD_SLEEPING:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_BAG) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 0; // it's sleeping
        }
      }
      break;
    case LOOK_WORD_HELLO:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_LOOK) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 1; // it's awake.
        }
      }
      break;
    case LOOK_WORD_SLEEPING:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_LOOK) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 0; // it's sleeping
        }
      }
      break;
    case WINDMILL_WORD_HELLO:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_WINDMILL) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 1; // it's awake.
        }
      }
      break;
    case WINDMILL_WORD_SLEEPING:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_WINDMILL) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 0; // it's sleeping
        }
      }
      break;
    case GLASS_WORD_HELLO:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_GLASS) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 1; // it's awake.
        }
      }
      break;
    case GLASS_WORD_SLEEPING:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_GLASS) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 0; // it's sleeping
        }
      }
      break;
    case REEL_WORD_HELLO:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_REEL) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 1; // it's awake.
        }
      }
      break;
    case REEL_WORD_SLEEPING:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_REEL) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 0; // it's sleeping
        }
      }
      break;
    case ARROW_WORD_HELLO:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_ARROW) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 1; // it's awake.
        }
      }
      break;
    case ARROW_WORD_SLEEPING:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_ARROW) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 0; // it's sleeping
        }
      }
      break;
    case THUNDER_WORD_HELLO:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_THUNDER) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 1; // it's awake.
        }
      }
      break;
    case THUNDER_WORD_SLEEPING:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_THUNDER) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 0; // it's sleeping
        }
      }
      break;
    case FUR_WORD_HELLO:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_FUR) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 1; // it's awake.
        }
      }
      break;
    case FUR_WORD_SLEEPING:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_FUR) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 0; // it's sleeping
        }
      }
      break;
    case PEAK_WORD_HELLO:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_PEAK) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 1; // it's awake.
        }
      }
      break;
    case PEAK_WORD_SLEEPING:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_PEAK) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 0; // it's sleeping
        }
      }
      break;
    case KEYBED_WORD_HELLO:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_KEYBED) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 1; // it's awake.
        }
      }
      break;
    case KEYBED_WORD_SLEEPING:
      for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
        if (memberList[idx] == ID_KEYBED) {
          presence[idx] = 10; // 1 greeting per every 10 seconds expected. (1 fps)
          awakeness[idx] = 0; // it's sleeping
        }
      }
      break;
    default:
      ;
    }
  }
}

// using Adafruit 3.5" TFT (HX8357) FeatherWing
//     ----> http://www.adafruit.com/products/3651
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include "Adafruit_STMPE610.h"

// #ifdef ESP32
#define STMPE_CS 32
#define TFT_CS   15
#define TFT_DC   33
#define SD_CS    14
// #endif

#define TFT_RST -1

// Init screen on hardware SPI, HX8357D type:
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 3800
#define TS_MAXX 100
#define TS_MINY 100
#define TS_MAXY 3750

//
const int boxsize = 10;
int wakeup_button_x = 80;
int wakeup_button_y = 340;
int wakeup_button_r = 60;
int sleep_button_x = 240;
int sleep_button_y = 410;
int sleep_button_r = 60;

//screen task
void loop_screen() {
  //
  // tft.fillScreen(HX8357_BLACK);
  //
  int color = HX8357_BLACK;
  for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
    // place markings
    tft.drawRect(idx * (boxsize + 2), idx * boxsize * 2, 100 + 2, boxsize + 2, HX8357_WHITE);
    // name
    tft.setCursor(idx * (boxsize + 2) + 100 + 2 + 5, idx * boxsize * 2);
    tft.setTextColor(HX8357_WHITE);
    tft.setTextSize(1);
    tft.print(names[idx]);
    // color coding..
    if (awakeness[idx] == 0) {
      color = HX8357_BLUE; // sleeping
    } else if (awakeness[idx] == 1) {
      color = HX8357_YELLOW; // awake
    } else if (awakeness[idx] == -1) {
      color = HX8357_BLACK; // unknown
    }
    // awakeness & presence markings
    tft.fillRect(idx * (boxsize + 2) + 1, idx * boxsize * 2 + 1, 100, boxsize, HX8357_BLACK);
    delay(2);
    tft.fillRect(idx * (boxsize + 2) + 1, idx * boxsize * 2 + 1, presence[idx] * 10, boxsize, color);
    // presence decrease
    if (presence[idx] > 0) {
      presence[idx] = presence[idx] - 1;
    }
  };
  // draw mode control buttons
  tft.fillCircle(wakeup_button_x, wakeup_button_y, wakeup_button_r, HX8357_YELLOW);
  tft.setTextColor(HX8357_WHITE);
  tft.setCursor(150, 290);
  tft.setTextSize(2);
  tft.print("Wake up!");
  tft.fillCircle(sleep_button_x, sleep_button_y, sleep_button_r, HX8357_BLUE);
  tft.setTextColor(HX8357_WHITE);
  tft.setCursor(70, 420);
  tft.setTextSize(2);
  tft.print("Good night~");
}
Task loop_screen_task(1000, TASK_FOREVER, &loop_screen); // fps : 1hz

//touch task
void loop_touch() {
  // Retrieve a point
  TS_Point p = ts.getPoint();

  // Serial.print("X = ");
  // Serial.print(p.x);
  // Serial.print("\tY = ");
  // Serial.print(p.y);
  // Serial.print("\tPressure = ");
  // Serial.println(p.z);

  // Scale from ~0->4000 to tft.width using the calibration #'s
  p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

  //
  float dist = 0.0;

  //
  dist = sqrt((p.x - wakeup_button_x) * (p.x - wakeup_button_x) + (p.y - wakeup_button_y) * (p.y - wakeup_button_y));
  if (dist < wakeup_button_r) {
    //wake up button touched! ---> send wake_up message to everyone.
    static String msg = "";
    sprintf(msg_cstr, "[%06d:%03d]", ID_EVERYONE, MONITOR_WORD_WAKEUP);
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
  }

  //
  dist = sqrt((p.x - sleep_button_x) * (p.x - sleep_button_x) + (p.y - sleep_button_y) * (p.y - sleep_button_y));
  if (dist < sleep_button_r) {
    //sleep button touched! ---> send sleep message to everyone.
    static String msg = "";
    sprintf(msg_cstr, "[%06d:%03d]", ID_EVERYONE, MONITOR_WORD_SLEEP);
    msg = String(msg_cstr);
    mesh.sendBroadcast(msg);
  }
}
Task loop_touch_task(100, TASK_FOREVER, &loop_touch); // touch sensing --> 0.1s

//
void setup_member() {

  //touchscreen
  if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }
  Serial.println("Touchscreen started");

  //tft screen
  tft.begin();
  tft.fillScreen(HX8357_BLACK);

  //array init.
  for (int idx = 0; idx < NUM_OF_MEMBERS; idx++) {
    presence[idx] = 0;
    awakeness[idx] = -1; // 1 : awake, 0 : sleeping, -1 : unknown
  }

  //
  runner.addTask(loop_screen_task);
  loop_screen_task.enable();
  runner.addTask(loop_touch_task);
  loop_touch_task.enable();
}
