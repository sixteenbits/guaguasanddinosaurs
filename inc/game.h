#ifndef _GAME_H_
#define _GAME_H_
#include <genesis.h>

#define INITIAL_STATE 0
#define LOGO_STATE 1
#define TITLE_STATE 2
#define STAGE1_STATE 3
#define STAGE2_STATE 4
#define GAMEOVER_STATE 5


//player powerups

#define POWER_1 1
#define POWER_2 2
#define POWER_3 4

//pyshics constants

#define DELTAY 1.2


#define CALCULATE_TICS(TICS) TICS << 5

typedef struct{
    u8 lives;
    Sprite * sprite;
    u8 state;
    u16 x;
    u16 y;
    u16 varacoins;
}Player;

struct{
    Player player;
    u8 current_state;
    u8 initiated;
    u16 tics;
    u16 ind;
}game;

#endif

void initGame();
void initState();
void updatePhisycs();
void update();
void handleSincInput();
void handleAsyncInput(u16, u16, u16);