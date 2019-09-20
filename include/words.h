#define MSG_LENGTH_MAX 256

//for group (everyone)
#define EVERYONE_MOOD_HIGH    (ID_EVERYONE + 1)
#define EVERYONE_MOOD_LOW     (ID_EVERYONE + 2)

//monitor & conductor
#define MONITOR_HELLO         (ID_MONITOR + 1)
#define MONITOR_WAKEUP        (ID_MONITOR + 2)
#define MONITOR_SLEEP         (ID_MONITOR + 3)

//actors
#define GAS_HELLO             (ID_GAS + 1)
#define GAS_SLEEPING          (ID_GAS + 2)
#define GAS_RING_RING_RING    (ID_GAS + 3)

#define TRUNK_HELLO           (ID_TRUNK + 1)
#define TRUNK_SLEEPING        (ID_TRUNK + 2)
#define TRUNK_SING            (ID_TRUNK + 3)

#define DRUM_HELLO            (ID_DRUM + 1)
#define DRUM_SLEEPING         (ID_DRUM + 2)
#define DRUM_TOMTOM           (ID_DRUM + 3)

#define FLOAT_HELLO           (ID_FLOAT + 1)
#define FLOAT_SLEEPING        (ID_FLOAT + 2)
#define FLOAT_FLY             (ID_FLOAT + 3)

#define REEL_HELLO            (ID_REEL + 1)
#define REEL_SLEEPING         (ID_REEL + 2)
#define REEL_TURN             (ID_REEL + 3)

#define SPEAK_A_HELLO         (ID_SPEAK_A + 1)
#define SPEAK_A_SLEEPING      (ID_SPEAK_A + 2)
#define SPEAK_A_TIC           (ID_SPEAK_A + 3)
#define SPEAK_A_TAC           (ID_SPEAK_A + 4)
#define SPEAK_A_TOE           (ID_SPEAK_A + 5)
#define SPEAK_A_PLAYMODE      (ID_SPEAK_A + 6) // + XX : 0: Individual random, 1: Directional Propagation
#define SPEAK_A_PARA_SPEED    (ID_SPEAK_A + 7) // + XX : speed of rhythm
#define SPEAK_A_PARA_SNDSET   (ID_SPEAK_A + 8) // + XX : sound set select

#define SPEAK_B_HELLO         (ID_SPEAK_B + 1)
#define SPEAK_B_SLEEPING      (ID_SPEAK_B + 2)
#define SPEAK_B_TIC           (ID_SPEAK_B + 3)
#define SPEAK_B_TAC           (ID_SPEAK_B + 4)
#define SPEAK_B_TOE           (ID_SPEAK_B + 5)
#define SPEAK_B_PLAYMODE      (ID_SPEAK_B + 6) // + XX : 0: Individual random, 1: Directional Propagation
#define SPEAK_B_PARA_SPEED    (ID_SPEAK_B + 7) // + XX : speed of rhythm
#define SPEAK_B_PARA_SNDSET   (ID_SPEAK_B + 8) // + XX : sound set select

#define SPEAK_C_HELLO         (ID_SPEAK_C + 1)
#define SPEAK_C_SLEEPING      (ID_SPEAK_C + 2)
#define SPEAK_C_TIC           (ID_SPEAK_C + 3)
#define SPEAK_C_TAC           (ID_SPEAK_C + 4)
#define SPEAK_C_TOE           (ID_SPEAK_C + 5)
#define SPEAK_C_PLAYMODE      (ID_SPEAK_C + 6) // + XX : 0: Individual random, 1: Directional Propagation
#define SPEAK_C_PARA_SPEED    (ID_SPEAK_C + 7) // + XX : speed of rhythm
#define SPEAK_C_PARA_SNDSET   (ID_SPEAK_C + 8) // + XX : sound set select

#define SPEAK_D_HELLO         (ID_SPEAK_D + 1)
#define SPEAK_D_SLEEPING      (ID_SPEAK_D + 2)
#define SPEAK_D_TIC           (ID_SPEAK_D + 3)
#define SPEAK_D_TAC           (ID_SPEAK_D + 4)
#define SPEAK_D_TOE           (ID_SPEAK_D + 5)
#define SPEAK_D_PLAYMODE      (ID_SPEAK_D + 6) // + XX : 0: Individual random, 1: Directional Propagation
#define SPEAK_D_PARA_SPEED    (ID_SPEAK_D + 7) // + XX : speed of rhythm
#define SPEAK_D_PARA_SNDSET   (ID_SPEAK_D + 8) // + XX : sound set select

#define SPEAK_E_HELLO         (ID_SPEAK_E + 1)
#define SPEAK_E_SLEEPING      (ID_SPEAK_E + 2)
#define SPEAK_E_TIC           (ID_SPEAK_E + 3)
#define SPEAK_E_TAC           (ID_SPEAK_E + 4)
#define SPEAK_E_TOE           (ID_SPEAK_E + 5)
#define SPEAK_E_PLAYMODE      (ID_SPEAK_E + 6) // + XX : 0: Individual random, 1: Directional Propagation
#define SPEAK_E_PARA_SPEED    (ID_SPEAK_E + 7) // + XX : speed of rhythm
#define SPEAK_E_PARA_SNDSET   (ID_SPEAK_E + 8) // + XX : sound set select

#define SPEAK_F_HELLO         (ID_SPEAK_F + 1)
#define SPEAK_F_SLEEPING      (ID_SPEAK_F + 2)
#define SPEAK_F_TIC           (ID_SPEAK_F + 3)
#define SPEAK_F_TAC           (ID_SPEAK_F + 4)
#define SPEAK_F_TOE           (ID_SPEAK_F + 5)
#define SPEAK_F_PLAYMODE      (ID_SPEAK_F + 6) // + XX : 0: Individual random, 1: Directional Propagation
#define SPEAK_F_PARA_SPEED    (ID_SPEAK_F + 7) // + XX : speed of rhythm
#define SPEAK_F_PARA_SNDSET   (ID_SPEAK_F + 8) // + XX : sound set select

//for group (all speakers)
#define SPEAKERS_HELLO        (ID_SPEAKERS + 1)
#define SPEAKERS_SLEEPING     (ID_SPEAKERS + 2)
#define SPEAKERS_TIC          (ID_SPEAKERS + 3)
#define SPEAKERS_TAC          (ID_SPEAKERS + 4)
#define SPEAKERS_TOE          (ID_SPEAKERS + 5)
#define SPEAKERS_PLAYMODE     (ID_SPEAKERS + 6) // + XX : 0: Individual random, 1: Directional Propagation
#define SPEAKERS_PARA_SPEED   (ID_SPEAKERS + 7) // + XX : speed of rhythm
#define SPEAKERS_PARA_SNDSET  (ID_SPEAKERS + 8) // + XX : sound set select
//status: leading (speakers)
#define SPEAKERS_LEADING      (ID_SPEAKERS + 80)
#define SPEAKERS_FOLLOWING    (ID_SPEAKERS + 81)
