#include "game.h"
#include "gfx.h"
#include "sprt.h"

#define INITIAL_STATE=0
#define LOGO_STATE 1
#define TITLE_STATE 2
#define STAGE1_STATE 3
#define STAGE2_STATE 4
#define GAMEOVER_STATE 5


void initGame(){

    //game.player=player;
    game.current_state=LOGO_STATE;
    game.initiated=0;
    SPR_init();
    
    
    Player player = {0,NULL,16,16,0,0};
    
}
void initState(){
    if(game.initiated==0){
        switch(game.current_state){
            case LOGO_STATE:
            VDP_drawImageEx(BG_B,&logo,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,game.ind),0,0,TRUE,CPU);
            VDP_setPalette(PAL2,tiovara_sprite.palette->data);
            Sprite * tiovara = SPR_addSprite(&tiovara_sprite,160,160,TILE_ATTR(PAL2,TRUE,FALSE,FALSE));
            SPR_setAnim(tiovara,4);
            game.initiated=1;
            break;
        }
    }
}
void update(){

    switch(game.current_state){
        case LOGO_STATE:

        break;
        
    }
    SPR_update();
}

void updatePhisycs(){

}
