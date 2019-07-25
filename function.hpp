//
//  function.h
//  my_first_try
//
//  Created by brian on 2019/7/25.
//  Copyright © 2019 brian. All rights reserved.
//

#ifndef function_hpp
#define function_hpp
#endif /* function_h */

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define ScreenWidth 1600
#define ScreenHeight 1200


typedef struct bullet{
    int damage;
    int x;
    int y;
    struct bullet *next;
};


void init(){
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_acodec_addon();
    al_init_primitives_addon();
    al_install_audio();
    al_install_keyboard();
    al_install_mouse();
}

ALLEGRO_DISPLAY* set_display(ALLEGRO_DISPLAY *display){
    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
    display = al_create_display(ScreenWidth,ScreenHeight);
    al_set_window_position(display,250,150);
    al_set_window_title(display,"Flight Game");
    
    if(!display){
        al_show_native_message_box(display, "Sample Title", "Display Settings", "Dispaly Window wasn't created successfully", NULL,ALLEGRO_MESSAGEBOX_QUESTION);
    }
    return display;
}

ALLEGRO_SAMPLE_INSTANCE* init_background_music(ALLEGRO_SAMPLE_INSTANCE* music_array[8]){
    al_reserve_samples(8);
    
    ALLEGRO_SAMPLE *song = al_load_sample("sound/menu.wav");
    ALLEGRO_SAMPLE *song1 = al_load_sample("sound/battle.wav");
    ALLEGRO_SAMPLE *song2 = al_load_sample("sound/lose.wav");
    ALLEGRO_SAMPLE *song3 = al_load_sample("sound/win.wav");
    ALLEGRO_SAMPLE *song4 = al_load_sample("sound/hurt.wav");
    ALLEGRO_SAMPLE *song5 = al_load_sample("sound/bird_dead.wav");
    ALLEGRO_SAMPLE *song6 = al_load_sample("sound/life.wav");
    ALLEGRO_SAMPLE *song7 = al_load_sample("sound/powerup.wav");
    ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(song);
    ALLEGRO_SAMPLE_INSTANCE *songInstance1 = al_create_sample_instance(song1);
    ALLEGRO_SAMPLE_INSTANCE *songInstance2 = al_create_sample_instance(song2);
    ALLEGRO_SAMPLE_INSTANCE *songInstance3 = al_create_sample_instance(song3);
    ALLEGRO_SAMPLE_INSTANCE *songInstance4 = al_create_sample_instance(song4);
    ALLEGRO_SAMPLE_INSTANCE *songInstance5 = al_create_sample_instance(song5);
    ALLEGRO_SAMPLE_INSTANCE *songInstance6 = al_create_sample_instance(song6);
    ALLEGRO_SAMPLE_INSTANCE *songInstance7 = al_create_sample_instance(song7);
    
    music_array[0]=songInstance;
    music_array[1]=songInstance1;
    music_array[2]=songInstance2;
    music_array[3]=songInstance3;
    music_array[4]=songInstance4;
    music_array[5]=songInstance5;
    music_array[6]=songInstance6;
    music_array[7]=songInstance7;
    
    return music_array[8];
}

void set_font(ALLEGRO_FONT* font[5]){
    
    font[0] = al_load_font("font/pirulen.ttf", 70, NULL);
    font[1] = al_load_font("font/ABC.otf", 60, NULL);
    font[2] = al_load_font("font/pirulen.ttf", 35, NULL);
    font[3] = al_load_font("font/ABC.otf", 40, NULL);
    font[4] = al_load_font("font/ABC.otf", 30, NULL);
    
}

void set_background_music(ALLEGRO_SAMPLE_INSTANCE* music_array[8]){
    for(int i=0;i<2;++i) al_set_sample_instance_playmode(music_array[i], ALLEGRO_PLAYMODE_LOOP);
    for(int i=2;i<8;++i) al_set_sample_instance_playmode(music_array[i], ALLEGRO_PLAYMODE_ONCE);
    for(int i=0;i<8;++i) al_attach_sample_instance_to_mixer(music_array[i], al_get_default_mixer());
}

void set_timer(ALLEGRO_TIMER* timer[6]){
    const float FPS0=4.0, FPS=60.0, FPS1=4.0, FPS2=100.0, FPS3=225.0, FPS4=150.0;
    timer[0] = al_create_timer(1.0/FPS);
    timer[1] = al_create_timer(1.0/FPS1);
    timer[2] = al_create_timer(1.0/FPS2);
    timer[3] = al_create_timer(1.0/FPS3);
    timer[4] = al_create_timer(1.0/FPS0);
    timer[5] = al_create_timer(1.0/FPS4);
}

void set_event_queue(ALLEGRO_TIMER* timer[6],ALLEGRO_DISPLAY* display ,ALLEGRO_EVENT_QUEUE *event_queue){
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer[0]));
    al_register_event_source(event_queue, al_get_timer_event_source(timer[1]));
    al_register_event_source(event_queue, al_get_timer_event_source(timer[2]));
    al_register_event_source(event_queue, al_get_timer_event_source(timer[3]));
    al_register_event_source(event_queue, al_get_timer_event_source(timer[4]));
    al_register_event_source(event_queue, al_get_timer_event_source(timer[5]));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
}

void destroy(ALLEGRO_TIMER* timer[6],ALLEGRO_DISPLAY* display ,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT* font[5],ALLEGRO_SAMPLE_INSTANCE* music_array[8]){
    for(int i=0;i<5;++i) al_destroy_font(font[i]);
    for(int i=0;i<8;++i) al_destroy_sample_instance(music_array[i]);
    for(int i=0;i<6;++i) al_destroy_timer(timer[i]);
    
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}

bool player_collision(int x, int y, int ex, int ey, int width, int height, int e_width, int e_height){
    if(x>ex+e_width||x+width<ex||y+height<ey||y>ey+e_height) return false;
    else return true;
    
}

bullet* createlist(bullet *head,int x,int y, int d){
    bullet *np;
    np = (bullet *)malloc(sizeof(bullet));
    if(head==NULL){
        head=np;
        np->x=x;
        np->y=y;
        np->damage=d;
        np->next=NULL;
    }
    else{
        np->x=x;
        np->y=y;
        np->damage=d;
        np->next=head;
        head=np;
    }
    
    return head;
}

bullet* xyupdate(bullet *head,int dist_x, int dist_y){
    
    if(head!=NULL){
        bullet *np;
        np=head;
        while(np!=NULL){
            np->x=np->x+dist_x;
            np->y=np->y+dist_y;
            np=np->next;
        }
    }
    
    return head;
}
