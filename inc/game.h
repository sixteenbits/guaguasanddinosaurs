#ifndef _GAME_H_
#define _GAME_H_
#include <genesis.h>
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
