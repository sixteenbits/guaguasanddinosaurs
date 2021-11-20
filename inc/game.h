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

//Init position

#define X_INIT 10
#define Y_INIT 155

//player actions

#define RUN 1
#define JUMP 2
#define JUMP_T 89
#define DOWN 0
#define DOWN_T 90

//player animations

#define JUMP_A 0
#define DOWN_A 2

//player powerups

#define POWER_1 1
#define POWER_2 2
#define POWER_3 4

//pyshics constants

#define DELTAY FIX16(18)
#define GRAVITY FIX16(0.2)

#define CALCULATE_TICS(TICS) TICS << 5
#define CALCULATE_SECS(SECS) SECS >> 5

typedef struct{
    u8 lives;
    Sprite * sprite;
    u16 x;
    fix16 y;
    u16 varacoins;
    u8 action_s;
    u8 action_t;
    fix16 vel_y;
    int height;
}Player;

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