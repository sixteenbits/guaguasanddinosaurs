#include "game.h"
#include "gfx.h"
#include "sprt.h"
#include "snd.h"



void initGame(){

    //game.player=player;
    game.current_state=LOGO_STATE;
    game.initiated=0;
    game.tics=0;
    SYS_disableInts();
    VDP_setScreenWidth320();
    VDP_setScreenHeight224();
    JOY_init();
    JOY_setEventHandler(handleAsyncInput);
    SPR_init();

    //sound initialization
    SND_setPCM_XGM(SND_VARA,vaaraaa,sizeof(vaaraaa));
    SND_setPCM_XGM(SND_JUMP,jump,sizeof(jump));
    SYS_enableInts();
    
    Player player = {0,NULL,POWER_1,16,16,0};

    game.player=player;
    game.offset = 0;
    game.column_update = 0;
    game.cuenta_pixel = 0;

    JOY_setEventHandler(handleAsyncInput);

}
void initState(){
    if(game.initiated==0){
        switch(game.current_state){
            case LOGO_STATE:
            VDP_drawImageEx(BG_B,&logo,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,game.ind),0,0,TRUE,CPU);
            VDP_setPalette(PAL2,tiovara_sprite.palette->data);
            game.player.sprite= SPR_addSprite(&tiovara_sprite,160,160,TILE_ATTR(PAL2,TRUE,FALSE,FALSE));
            SPR_setAnim(game.player.sprite,4);
            SND_startPlayPCM_XGM(SND_VARA,0, SOUND_PCM_CH4);
            break;
            case TITLE_STATE:
            VDP_drawImageEx(BG_B,&title,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,game.ind),0,0,TRUE,CPU);
            break;
            case STAGE1_STATE:
            game.player.lives=3;
            game.player.state=POWER_1;
            game.player.varacoins=0;
            game.player.x=160;
            game.player.y=160;
             SYS_disableInts();
            game.ind += logo.tileset->numTile;
            VDP_drawImageEx(BG_A, &fondoa, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, game.ind), 0, 0, TRUE, CPU);
            VDP_setPalette(PAL2, &player_sprite.palette->data);
            game.player.sprite = SPR_addSprite(&player_sprite, 160,155, TILE_ATTR(PAL2, FALSE,FALSE,FALSE));
            SPR_setAnim(game.player.sprite, RUN);
            VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
            SYS_enableInts();
           
            break;
        }
        game.initiated=1;

    }
}
void update(){

    switch(game.current_state){
        case LOGO_STATE:
            if(game.tics>CALCULATE_TICS(4)){
                game.current_state=STAGE1_STATE;
                game.initiated=0;
                game.tics=0;
                SPR_releaseSprite(game.player.sprite);
            }
        break;

        case STAGE1_STATE:
            
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


void handleAsyncInput(u16 joy, u16 changed, u16 state){
    switch (game.current_state)
    {
    case STAGE1_STATE:
        /* code */
        if (changed & state & (BUTTON_A|BUTTON_B|BUTTON_C)){ 
            jump();
                        SND_startPlayPCM_XGM(SND_JUMP,0, SOUND_PCM_CH2);
        }
        else if(changed & state & BUTTON_DOWN) down();
        break;
    }
}

void updatePhisycs(){
    if(game.current_state == STAGE1_STATE || game.current_state == STAGE2_STATE){
        game.offset++;
        if(game.player.action_t > 0) game.player.action_t--;
        else{
            game.player.action_s = 0;
            SPR_setAnim(game.player.sprite, RUN);
        }
        game.cuenta_pixel++;
        if(game.cuenta_pixel >7) game.cuenta_pixel = 0;
        updateCamera();
    }
}

void jump(){
    if(!game.player.action_s){
        SPR_setAnim(game.player.sprite, JUMP_A);
        game.player.action_s = JUMP;
        game.player.action_t = JUMP_T;
    }
}

void down(){
    if (!game.player.action_s)
    {
        SPR_setAnim(game.player.sprite, DOWN_A);
        game.player.action_s = DOWN;
        game.player.action_t = DOWN_T;
    }
    
}

void updateCamera(){
    switch (game.current_state)
    {
    case STAGE1_STATE:
        if(game.offset > STAGE1_LEN) game.offset=0;
        if(game.cuenta_pixel == 0){
            game.column_update=(((game.offset+320)>>3)&127);
            VDP_setMapEx(BG_A, fondoa.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, game.ind), game.column_update, 0, game.column_update, 0, 1, 28);
        }
        VDP_setHorizontalScroll(BG_A, -game.offset);
        break;
    
    case STAGE2_STATE:

        break;
    }
}