#ifndef _GAME_H_
#define _GAME_H_
#include <genesis.h>
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