#include "game.h"
#include "gfx.h"
#include "sprt.h"



void initGame(){

    //game.player=player;
    game.current_state=LOGO_STATE;
    game.initiated=0;
    game.tics=0;
    VDP_setScreenWidth320();
    SPR_init();
    
    
    Player player = {0,NULL,16,16,0,0,0};
    game.player=player;
}
void initState(){
    if(game.initiated==0){
        switch(game.current_state){
            case LOGO_STATE:
            VDP_drawImageEx(BG_B,&logo,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,game.ind),0,0,TRUE,CPU);
            VDP_setPalette(PAL2,tiovara_sprite.palette->data);
            game.player.sprite= SPR_addSprite(&tiovara_sprite,160,160,TILE_ATTR(PAL2,TRUE,FALSE,FALSE));
            SPR_setAnim(game.player.sprite,4);
            break;
            case TITLE_STATE:
            VDP_drawImageEx(BG_B,&title,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,game.ind),0,0,TRUE,CPU);
            break;
            case STAGE1_STATE:
            game.player.lives=3;
            
            VDP_drawImageEx(BG_B,&stage1,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,game.ind),0,0,TRUE,CPU);
            break;
        }
        game.initiated=1;

    }
}
void update(){

    switch(game.current_state){
        case LOGO_STATE:
            if(game.tics>CALCULATE_TICS(3)){
                game.current_state=TITLE_STATE;
                game.initiated=0;
                game.tics=0;
                SPR_releaseSprite(game.player.sprite);
            }
        break;

    }
    game.tics++;
    SPR_update();
}

void handleSincInput(){
    int value = JOY_readJoypad(JOY_1);

    switch(game.current_state){
        case TITLE_STATE:
            if(value & BUTTON_START){
                game.current_state=STAGE1_STATE;
                game.tics=0;
                game.initiated=0;
            }
        break;
    }
    

    
}

void updatePhisycs(){

}
