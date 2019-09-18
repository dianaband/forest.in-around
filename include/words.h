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
#define CONDUCTOR_WORD_HELLO         (ID_MONITOR + 0x00)

//actors
#define GAS_WORD_HELLO             (ID_GAS + 0x00)
#define GAS_WORD_SLEEPING          (ID_GAS + 0x01)
#define GAS_WORD_RING_RING_RING    (ID_GAS + 0x02)

#define VOICE1_WORD_HELLO          (ID_VOICE1 + 0x00)
#define VOICE1_WORD_SLEEPING       (ID_VOICE1 + 0x01)
#define VOICE1_WORD_SING           (ID_VOICE1 + 0x02)

#define VOICE2_WORD_HELLO          (ID_VOICE2 + 0x00)
#define VOICE2_WORD_SLEEPING       (ID_VOICE2 + 0x01)
#define VOICE2_WORD_SING           (ID_VOICE2 + 0x02)

#define VOICE3_WORD_HELLO          (ID_VOICE3 + 0x00)
#define VOICE3_WORD_SLEEPING       (ID_VOICE3 + 0x01)
#define VOICE3_WORD_SING           (ID_VOICE3 + 0x02)

#define FALL1_WORD_HELLO           (ID_FALL1 + 0x00)
#define FALL1_WORD_SLEEPING        (ID_FALL1 + 0x01)
#define FALL1_WORD_SING            (ID_FALL1 + 0x02)

#define FALL2_WORD_HELLO           (ID_FALL2 + 0x00)
#define FALL2_WORD_SLEEPING        (ID_FALL2 + 0x01)
#define FALL2_WORD_SING            (ID_FALL2 + 0x02)

#define ANI1_WORD_HELLO            (ID_ANI1 + 0x00)
#define ANI1_WORD_SLEEPING         (ID_ANI1 + 0x01)
#define ANI1_WORD_SING             (ID_ANI1 + 0x02)

#define ANI2_WORD_HELLO            (ID_ANI2 + 0x00)
#define ANI2_WORD_SLEEPING         (ID_ANI2 + 0x01)
#define ANI2_WORD_SING             (ID_ANI2 + 0x02)
