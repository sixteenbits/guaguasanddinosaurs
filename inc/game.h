#ifndef _GAME_H_
#define _GAME_H_
#include <genesis.h>

#define INITIAL_STATE 0
#define LOGO_STATE 1
#define TITLE_STATE 2
#define STAGE1_STATE 3
#define STAGE2_STATE 4
#define GAMEOVER_STATE 5

//Stage atributes

#define STAGE1_LEN 1023
#define STAGE2_LEN 1023

//player actions

#define RUN 1
#define JUMP 2
#define JUMP_T 20
#define DOWN 0
#define DOWN_T 20

//player animations

#define JUMP_A 0
#define DOWN_A 2

//player powerups

#define POWER_1 1
#define POWER_2 2
#define POWER_3 4

//pyshics constants

#define DELTAY 1.2

#define SND_VARA 1
#define SND_JUMP 2


#define CALCULATE_TICS(TICS) TICS << 5

// Player struct
typedef struct{
    // Player lives
    u8 lives;
    // Player sprite
    Sprite * sprite;
    u8 state;
    // Player pos X
    u16 x;
    // Player pos Y
    u16 y;
    // Jump Speed
    u16 vy;
    // Player coins
    u16 varacoins;
    u8 action_s;
    u8 action_t;
}Player;

// Game data
struct{
    Player player;
    u8 current_state;
    u8 initiated;
    u16 tics;
    u16 ind;
    u16 offset;
    s16 column_update;
    u8 cuenta_pixel;
}game;

#endif

void initGame();
void initState();
void updatePhisycs();
void update();
void handleSincInput();
void handleAsyncInput(u16, u16, u16);
void jump();
void down();
void updateCamera();
