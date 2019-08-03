#define MSG_LENGTH_MAX 256

//room events

// #1 ==> 369
#define ROOM_EVT369_ID               (ID_EVERYONE + 0x10)
//
#define ROOM_EVT369_CALL             (ROOM_EVT369_ID + 0x01) // wanna play 369?
#define ROOM_EVT369_RESPONSE_Y       (ROOM_EVT369_ID + 0x02) // good. i'm in.
#define ROOM_EVT369_RESPONSE_N       (ROOM_EVT369_ID + 0x03) // no, pass. i'm out.
//only for those did say gonna do this.
#define ROOM_EVT369_FASTER           (ROOM_EVT369_ID + 0x04) // let's make it faster
#define ROOM_EVT369_SLOWER           (ROOM_EVT369_ID + 0x05) // let's slow down, no?
#define ROOM_EVT369_DIED             (ROOM_EVT369_ID + 0x06) // oh. i'm dead. game over. well. was boring, again.

// #2 ==> baseball guess
#define ROOM_EVTBBG_ID               (ID_EVERYONE + 0x20)
//
#define ROOM_EVTBBG_CALL                 (ROOM_EVTBBG_ID + 0x01) // wanna play baseball guess?
#define ROOM_EVTBBG_RESPONSE_Y           (ROOM_EVTBBG_ID + 0x02) // good. i'm in.
#define ROOM_EVTBBG_RESPONSE_N           (ROOM_EVTBBG_ID + 0x03) // no, pass. i'm out.
//only for those did say gonna do this.
#define ROOM_EVTBBG_DECLARE_PROB_GIVER   (ROOM_EVTBBG_ID + 0x04) // i wanna do prob. giver.
#define ROOM_EVTBBG_DECLARE_PROB_SOLVER  (ROOM_EVTBBG_ID + 0x05) // i wanna do prob. solver.
#define ROOM_EVTBBG_THE_SOLUTION         (ROOM_EVTBBG_ID + 0x06) // i will try to solve! the answer is...
#define ROOM_EVTBBG_CORRECT              (ROOM_EVTBBG_ID + 0x07) // wow that was fast.
#define ROOM_EVTBBG_INCORRECT            (ROOM_EVTBBG_ID + 0x08) // sorry, but that is not the right one. ;)

// #3 ==> room escape game



//individual events

//announcements
#define CONDUCTOR_WORD_HELLO         (ID_CONDUCTOR + 0x00)

//actors
#define BELL_WORD_HELLO              (ID_BELL + 0x00)
#define BELL_WORD_RING_RING_RING     (ID_BELL + 0x01)

#define FLOAT_WORD_HELLO             (ID_FLOAT + 0x00)
#define FLOAT_WORD_TURN_TURN         (ID_FLOAT + 0x01)

#define BAG_WORD_HELLO               (ID_BAG + 0x00)
#define BAG_WORD_HANDLE_UP           (ID_BAG + 0x01)
#define BAG_WORD_HANDLE_DOWN         (ID_BAG + 0x02)
#define BAG_WORD_SING                (ID_BAG + 0x03)

#define LOOK_WORD_HELLO              (ID_LOOK + 0x00)
#define LOOK_WORD_LOOK_AROUND        (ID_LOOK + 0x01)

#define WINDMILL_WORD_HELLO          (ID_WINDMILL + 0x00)
#define WINDMILL_WORD_BLOW           (ID_WINDMILL + 0x01)

#define GLASS_WORD_HELLO             (ID_GLASS + 0x00)
#define GLASS_WORD_PLAYTIME          (ID_GLASS + 0x01)

#define REEL_WORD_HELLO              (ID_REEL + 0x00)
#define REEL_WORD_PLAYTIME           (ID_REEL + 0x01)

#define ARROW_WORD_HELLO             (ID_ARROW + 0x00)
#define ARROW_WORD_CHANGE  (ID_ARROW + 0x01)

#define THUNDER_WORD_HELLO           (ID_THUNDER + 0x00)
#define THUNDER_WORD_RRRRR           (ID_THUNDER + 0x01)
#define THUNDER_WORD_LEFT            (ID_THUNDER + 0x02)

#define FUR_WORD_HELLO               (ID_FUR + 0x00)
#define FUR_WORD_SING                (ID_FUR + 0x01)

#define PEAK_WORD_HELLO              (ID_PEAK + 0x00)
#define PEAK_WORD_PPI_PPI_PPI        (ID_PEAK + 0x01)

#define KEYBED_WORD_HELLO            (ID_KEYBED + 0x00)
