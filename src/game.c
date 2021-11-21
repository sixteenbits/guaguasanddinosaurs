#include "game.h"
#include "gfx.h"
#include "sprt.h"
#include "snd.h"
#include "music.h"



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
    SND_setPCM_XGM(SND_JUMP,jump_snd,sizeof(jump_snd));
    SYS_enableInts();
    
    Player player = {0,NULL,POWER_1,16,FIX16(Y_INIT),0,0,FIX16(0),16};
    game.player=player;
    game.offset = 0;
    game.column_update = 0;
    game.cuenta_pixel = 0;
    game.x_obstaculo = 0;
    JOY_setEventHandler(handleAsyncInput);

}
void initState(){
    if(game.initiated==0){
        switch(game.current_state){
            case LOGO_STATE:
            SYS_disableInts();
            VDP_drawImageEx(BG_B,&logo,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,game.ind),0,0,TRUE,CPU);
            VDP_setPalette(PAL2,tiovara_sprite.palette->data);
            game.player.sprite= SPR_addSprite(&tiovara_sprite,160,160,TILE_ATTR(PAL2,TRUE,FALSE,FALSE));
            SPR_setAnim(game.player.sprite,4);
            SYS_enableInts();
            SND_startPlayPCM_XGM(SND_VARA,0, SOUND_PCM_CH4);
            break;
            case TITLE_STATE:
            SYS_disableInts();
            game.ind=TILE_USERINDEX;
            VDP_drawImageEx(BG_B,&title,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,game.ind),0,0,TRUE,CPU);
            SND_startPlay_XGM(main_theme);
            SYS_enableInts();
            break;
            case STAGE1_STATE:
            game.player.lives=3;
            game.player.state=POWER_1;
            game.player.varacoins=0;
            game.player.action_s = RUN;
            game.player.vel_y = FIX16(0);
            SYS_disableInts();
            game.tics=0;
            game.ind += logo.tileset->numTile;
            VDP_drawImageEx(BG_A, &fondoa, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, game.ind), 0, 0, TRUE, CPU);
            VDP_setPalette(PAL3,objects.palette->data);
            VDP_setPalette(PAL2,player_sprite.palette->data);
            game.player.sprite = SPR_addSprite(&player_sprite, X_INIT, Y_INIT, TILE_ATTR(PAL2, FALSE,FALSE,FALSE));
            game.curr_obj=0;
            Sprite *lives=SPR_addSprite(&objects,5,4,TILE_ATTR(PAL3,FALSE,FALSE,FALSE));
            SPR_setAnim(lives,3);
            char strlives[5];
            sprintf(strlives,"x%d",game.player.lives);
            VDP_drawTextBG(BG_B,strlives,7,4);
            SPR_setAnim(game.player.sprite, RUN_A);
            VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
            SND_startPlay_XGM(stage);
            SYS_enableInts();
            Sprite *spr=SPR_addSprite(&objects,145,Y_INIT,TILE_ATTR(PAL3,FALSE,FALSE,FALSE));
            Object ob ={spr,145,Y_INIT+15};
            u16 anim=random();
            SPR_setAnim(ob.sprt,anim&3);
            game.objs[game.curr_obj]=ob;
            game.curr_obj++;
            game.curr_obj&=MAX_OBJS;
            break;
        }
        game.initiated=1;

    }
}
void update(){

    switch(game.current_state){
        case LOGO_STATE:
            if(game.tics>CALCULATE_TICS(4)){
                game.current_state=TITLE_STATE;
                game.initiated=0;
                game.tics=0;
                SPR_releaseSprite(game.player.sprite);
            }
        break;

        case STAGE1_STATE:
        case STAGE2_STATE:
                /*if(game.tics%200 == 0){
                    Sprite *spr=SPR_addSprite(&objects,145,Y_INIT,TILE_ATTR(PAL3,FALSE,FALSE,FALSE));
                    Object ob ={spr,145,Y_INIT};
                    u16 anim=random();
                    SPR_setAnim(ob.sprt,anim&3);
                    game.objs[game.curr_obj]=ob;
                    game.curr_obj++;
                    game.curr_obj&=MAX_OBJS;
                }*/
            
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
        case STAGE1_STATE:
            if(value & BUTTON_DOWN){
                down();
            }else if (game.player.action_s == DOWN){
                game.player.action_s = RUN;
                SPR_setAnim(game.player.sprite, RUN_A);
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
        break;
    }
}

void updatePhisycs(){
    if(game.current_state == STAGE1_STATE || game.current_state == STAGE2_STATE){
        game.offset+=game.player.state;
        game.x_obstaculo+=game.player.state<<1;
        game.player.y = fix16Add(game.player.y, game.player.vel_y);
        SPR_setPosition(game.player.sprite, X_INIT, fix16ToInt(game.player.y));
        if(game.player.action_s == JUMP) game.player.vel_y = fix16Add(game.player.vel_y,GRAVITY);
        
        if(game.player.action_s == JUMP && fix16ToInt(game.player.y)+game.player.height >= Y_INIT){
            game.player.action_s = RUN;
            game.player.vel_y = FIX16(0);
            game.player.y = FIX16(Y_INIT);
            SPR_setAnim(game.player.sprite,RUN_A);
        }



        game.cuenta_pixel++;
        if(game.cuenta_pixel >7) game.cuenta_pixel = 0;
        updateCamera();
    }
}

void jump(){
    if(game.player.action_s == RUN){
        game.player.action_s = JUMP;
        game.player.vel_y= FIX16(-5);
        SPR_setAnim(game.player.sprite, JUMP_A);
    }
}

void down(){
    if (game.player.action_s == RUN || game.player.action_s == DOWN)
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
    case STAGE2_STATE:
        if(game.offset > STAGE1_LEN) game.offset=0;
        if(game.cuenta_pixel == 0){
            game.column_update=(((game.offset+320)>>3)&127);
            VDP_setMapEx(BG_A, fondoa.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, game.ind), game.column_update, 0, game.column_update, 0, 1, 28);
        }
        VDP_setHorizontalScroll(BG_A, -game.offset);
        
        Object ob =game.objs[0];

        SPR_setPosition(ob.sprt,320-(game.x_obstaculo%380),ob.y);
        if(game.x_obstaculo > 380){
            u16 r_sprite = random()%3;
            u16 i= 1;
            if(r_sprite == i)
                game.objs[0].y = Y_INIT -32;
            else
                game.objs[0].y = Y_INIT+15;
            SPR_setAnim(ob.sprt,r_sprite);
            game.x_obstaculo = 0;

        } 
        break;
    
    }
}