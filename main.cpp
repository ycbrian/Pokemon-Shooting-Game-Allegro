//
//  main.cpp
//  my_first_try
//
//  Created by brian on 2018/12/15.
//  Copyright © 2018 brian. All rights reserved.
//

#include "main.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "function.hpp"


int main(int argc, char *argv[])
{
    ALLEGRO_DISPLAY *display;
    
    enum Direction { UP, DOWN, LEFT, RIGHT};
    
    al_init();
    
    // init display
    display=set_display(display);
    
    // init features
    init();
    
    // set music
    ALLEGRO_SAMPLE_INSTANCE* music_array[8];
    init_background_music(music_array);
    set_background_music(music_array);
    
    // Set color
    ALLEGRO_COLOR BLACK = al_map_rgb(0,0,0);
    ALLEGRO_COLOR RED = al_map_rgb(255,0,0);
    
    // Set font
    ALLEGRO_FONT* font[5];
    set_font(font);
    
    // load image
    ALLEGRO_BITMAP *begin_back = al_load_bitmap("image/begin.png"),*game_back = al_load_bitmap("image/BG.png"), *X = al_load_bitmap("image/X.png"),*Z = al_load_bitmap("image/z.png"), *direction = al_load_bitmap("image/direction.png"), *bird = al_load_bitmap("image/pi1.png"),
        *bird1 = al_load_bitmap("image/pi2.png"), *bird2 = al_load_bitmap("image/pi3.png"), *game_bird = al_load_bitmap("image/game_pi.png"),
        *pika = al_load_bitmap("image/pikachu.png"), *turtle = al_load_bitmap("image/Squirtle.png"), *flight = al_load_bitmap("image/Fly.png"),
        *shoot = al_load_bitmap("image/Shoot.png"), *game_bird1 = al_load_bitmap("image/ho_oh.png"), *game_bird2 = al_load_bitmap("image/taillow.png"),*p_Bullet = al_load_bitmap("image/Bullet.png"), *fire = al_load_bitmap("image/fireball.png"), *wind = al_load_bitmap("image/wind.png"),*electric = al_load_bitmap("image/electric.png"), *life = al_load_bitmap("image/hp.png"), *power = al_load_bitmap("image/power.png"),*bomb = al_load_bitmap("image/bomb.png"), *sad = al_load_bitmap("image/sadchu.png");
    
    // var init
    bool done = false, done1 = false , done3 = false, done4 = false, done5=false;
    bool game_run=false;
    int x = 400, y = 400;
    int movespeed = 5;
    int a=100,b=500;
    int e1_x=1300,e2_x=1100,e3_x=1000;
    int e1_y=500,e2_y=100,e3_y=1000;
    bool e1=false,e2=false,e3=false, p_flag=false;
    bool e1_flag = false,e2_flag = false, e3_flag = false, shootnote=false , success=false, hp_appear=false ,power_appear=false, pu_flag=false;
    int e_time=0,e_time1=0,e_time2=0,e_hp=0, e_pu=0;
    int e4_x=rand()%1100, e4_y=rand()%1200;
    int e5_x=rand()%1100, e5_y=rand()%1200;
    bullet *head=NULL,*e1_head=NULL,*e2_head=NULL,*e3_head=NULL, *pu_head=NULL;
    int e1_hp=800,e2_hp=1000,e3_hp=500,p_hp=50;
    char p[10],hp1[10],hp2[10],hp3[10],grade[10];
    int score = 0,pu_interval=0;
    int hp_flag_x=rand()%2, hp_flag_y=rand()%2 ,power_flag_x=rand()%2 ,power_flag_y=rand()%2;
    
    
    ALLEGRO_KEYBOARD_STATE keystate;
    
    // init timer
    ALLEGRO_TIMER *timer[6];
    set_timer(timer);
    
    //set event queue
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    set_event_queue(timer,display,event_queue);
    
    
    // begin window
    while(!done1){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        
        al_play_sample_instance(music_array[0]);
        
        // event control
        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            done1 = true;
            done = true;
            done3 = true;
            done5 = true;
            game_run = true;
        }
        else if(events.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(events.keyboard.keycode)
            {
                case ALLEGRO_KEY_ENTER:
                    done1 = true;
                    break;
            }
        }
        else if(events.type == ALLEGRO_EVENT_MOUSE_AXES){
            x=events.mouse.x;
            y=events.mouse.y;
        }
        
        // draw map
        al_hide_mouse_cursor(display);
        al_draw_scaled_bitmap(begin_back,0,0,al_get_bitmap_width(begin_back),al_get_bitmap_height(begin_back),0,0,ScreenWidth,ScreenHeight,NULL);
        al_draw_scaled_bitmap(pika,0,0,al_get_bitmap_width(pika),al_get_bitmap_height(pika),1200,850,250,180,NULL);
        al_draw_scaled_bitmap(turtle,0,0,al_get_bitmap_width(turtle),al_get_bitmap_height(turtle),150,750,250,250,NULL);
        al_draw_text(font[0], BLACK, 210, ScreenHeight/4, ALLEGRO_ALIGN_LEFT, "Flight Shoooting Game");
        al_draw_text(font[1], BLACK, 450, 800, ALLEGRO_ALIGN_LEFT, "Press Enter to Begin");
        al_draw_scaled_bitmap(bird,0,0,al_get_bitmap_width(bird),al_get_bitmap_height(bird),x+20,y+20,200,200,NULL);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
    }
    
    // menu
    while(!done3){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        
        al_play_sample_instance(music_array[0]);
        
        done4 = false;
        
        // event control
        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            done3 = true;
            done = true;
            done5 = true;
            game_run = true;
        }
        else if(events.type == ALLEGRO_EVENT_MOUSE_AXES){
            x=events.mouse.x;
            y=events.mouse.y;
        }
        else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(events.mouse.button & 1){
                x=events.mouse.x;
                y=events.mouse.y;
                
                if(x>=410 && x<=850 && y>=ScreenHeight/4-30 && y<=ScreenHeight/4+110) done3 = true;
                else if(x>=410 && x<= 895 && y>= 2*ScreenHeight/4-30 && y<= 2*ScreenHeight/4+110){
                    
                    // Go to instruction page
                    while(!done4){
                        ALLEGRO_EVENT events1;
                        al_wait_for_event(event_queue, &events1);
                        
                        // event control
                        if(events1.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                            done4 = true;
                            done3 = true;
                            done = true;
                            done5 = true;
                            game_run = true;
                        }
                        else if(events1.type == ALLEGRO_EVENT_MOUSE_AXES){
                            x=events1.mouse.x;
                            y=events1.mouse.y;
                        }
                        else if(events1.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                            if(events1.mouse.button & 1){
                                x=events1.mouse.x;
                                y=events1.mouse.y;
                                if(x>=1210 && x<=1460 && y>= 3*ScreenHeight/4+70 && y<=  3*ScreenHeight/4+210) done4 = true;
                            }
                        }
                        
                        // draw map
                        al_hide_mouse_cursor(display);
                        al_draw_scaled_bitmap(game_back,0,0,al_get_bitmap_width(game_back),al_get_bitmap_height(game_back),0,0,ScreenWidth,ScreenHeight,NULL);
                        al_draw_scaled_bitmap(bird2,0,0,al_get_bitmap_width(bird2),al_get_bitmap_height(bird2),1200,350,300,300,NULL);
                        al_draw_text(font[1], BLACK, 1250, 3*ScreenHeight/4+100, ALLEGRO_ALIGN_LEFT, "BACK");
                        al_draw_text(font[2], BLACK, 600,1*ScreenHeight/4-75,ALLEGRO_ALIGN_LEFT, "Press direction to control flight");
                        al_draw_text(font[2], BLACK, 550,2*ScreenHeight/4-80,ALLEGRO_ALIGN_LEFT, "Press X to attack");
                        al_draw_text(font[2], BLACK, 550,3*ScreenHeight/4-160,ALLEGRO_ALIGN_LEFT, "Press Z to use strong weapon");
                         al_draw_text(font[2], BLACK, 650,3*ScreenHeight/4+55,ALLEGRO_ALIGN_LEFT, "->Get items");
                        al_draw_scaled_bitmap(direction,0,0,al_get_bitmap_width(direction),al_get_bitmap_height(direction),ScreenWidth/4-300,ScreenHeight/4-200,400,275,NULL);
                        al_draw_scaled_bitmap(X,0,0,al_get_bitmap_width(X),al_get_bitmap_height(X),ScreenWidth/4-145,2*ScreenHeight/4-110,125,125,NULL);
                        al_draw_scaled_bitmap(Z,0,0,al_get_bitmap_width(Z),al_get_bitmap_height(Z),ScreenWidth/4-145,3*ScreenHeight/4-200,125,125,NULL);
                        al_draw_scaled_bitmap(power,0,0,al_get_bitmap_width(power),al_get_bitmap_height(power),ScreenWidth/4+25,3*ScreenHeight/4+40,125,125,NULL);
                        al_draw_scaled_bitmap(life,0,0,al_get_bitmap_width(life),al_get_bitmap_height(life),ScreenWidth/4-200,3*ScreenHeight/4+30,150,150,NULL);
                        al_draw_rounded_rectangle(1210, 3*ScreenHeight/4+70, 1460, 3*ScreenHeight/4+210, 5, 5, BLACK, 3);
                        al_draw_scaled_bitmap(bird,0,0,al_get_bitmap_width(bird),al_get_bitmap_height(bird),x,y,100,100,NULL);
                        al_flip_display();
                        al_clear_to_color(al_map_rgb(0,0,0));
                    }
                }
                else if(x>=410 && x<= 635 && y>= 3*ScreenHeight/4-30 && y<= 110+3*ScreenHeight/4){
                    done3 = true;
                    done = true;
                    done5 = true;
                    game_run = true;
                }
            }
            else if(events.mouse.button & 2) continue;
        }
        
        // draw map
        al_hide_mouse_cursor(display);
        al_draw_scaled_bitmap(game_back,0,0,al_get_bitmap_width(game_back),al_get_bitmap_height(game_back),0,0,ScreenWidth,ScreenHeight,NULL);
        al_draw_scaled_bitmap(bird1,0,0,al_get_bitmap_width(bird1),al_get_bitmap_height(bird1),1100,600,400,400,NULL);
        al_draw_text(font[1], BLACK, 450, ScreenHeight/4, ALLEGRO_ALIGN_LEFT, "Start Game");
        al_draw_text(font[1], BLACK, 450, 2*ScreenHeight/4, ALLEGRO_ALIGN_LEFT, "How to Play");
        al_draw_text(font[1], BLACK, 450, 3*ScreenHeight/4, ALLEGRO_ALIGN_LEFT, "Exit");
        al_draw_rounded_rectangle(410, ScreenHeight/4-30, 850, ScreenHeight/4+110, 5, 5, BLACK, 3);
        al_draw_rounded_rectangle(410, 2*ScreenHeight/4-30, 895, 2*ScreenHeight/4+110, 5, 5, BLACK, 3);
        al_draw_rounded_rectangle(410, 3*ScreenHeight/4-30, 635, 3*ScreenHeight/4+110, 5, 5, BLACK, 3);
        al_draw_scaled_bitmap(bird,0,0,al_get_bitmap_width(bird),al_get_bitmap_height(bird),x,y,100,100,NULL);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
    }
    
    
    // start timer for starting main game
    al_start_timer(timer[0]);
    al_start_timer(timer[1]);
    al_start_timer(timer[2]);
    al_start_timer(timer[3]);
    al_start_timer(timer[4]);
    al_start_timer(timer[5]);
    
    // main game
    while(!done){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        al_stop_sample_instance(music_array[0]);
        al_play_sample_instance(music_array[1]);
        
        // event controller
        if(events.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(events.keyboard.keycode)
            {
                case ALLEGRO_KEY_SPACE:
                    done = true;
                    break;
            }
        }
        else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            done = true;
            done5 = true;
        }
        else if(events.type == ALLEGRO_EVENT_TIMER){
            // timer 1 (1.0/4.0)
            if(events.timer.source==timer[1]){
                e_time+=10;
                e_time1+=10;
                e_time2+=10;
                e_hp+=10;
                e_pu+=10;
                al_get_keyboard_state(&keystate);
                
                // press x shoot the small bullet, and create bullet linked list
                if(al_key_down(&keystate, ALLEGRO_KEY_X)){
                    shootnote = true;
                    head=createlist(head,a+150,b,1);
                }
                // press z shoot the large bullet, and create bullet linked list
                if(al_key_down(&keystate, ALLEGRO_KEY_Z)){
                    // if eat the power up, then insert bullet into bullet list
                    if(pu_flag==true) pu_head=createlist(pu_head,a+150,b,1);
                }
                
                // enemy attack bullet list, e_time for the time interval of bullets
                if(e_time==50){
                    e1_head=createlist(e1_head,e1_x,e1_y,1);
                    e_time=0;
                }
                if(e_time1==60){
                    e2_head=createlist(e2_head,e2_x,e2_y,1);
                    e_time1=0;
                }
                if(e_time2==40){
                    e3_head=createlist(e3_head,e3_x,e3_y,1);
                    e_time2=0;
                }
                
                // set hp tools appear time interval
                if(e_hp==500){
                    hp_appear=true;
                    e4_x=rand()%1100;
                    e4_y=rand()%1200;
                }
                else if(e_hp==800){
                    hp_appear=false;
                    e_hp=0;
                }
                
                // controlling hp tools flying direction
                if(hp_flag_x==false&&hp_flag_y==false){
                    e4_x+=50;
                    e4_y+=50;
                }
                else if(hp_flag_x==true&&hp_flag_y==false){
                    e4_x-=50;
                    e4_y+=50;
                }
                else if(hp_flag_x==false&&hp_flag_y==true){
                    e4_x+=50;
                    e4_y-=50;
                }
                else if(hp_flag_x==true&&hp_flag_y==true){
                    e4_x-=50;
                    e4_y-=50;
                }
                
                // give the flying regions of hp tools
                if(e4_x>=ScreenWidth-500) hp_flag_x=true;
                else if(e4_x<=50) hp_flag_x=false;
                
                if(e4_y>=ScreenHeight-100) hp_flag_y=true;
                else if(e4_y<=50) hp_flag_y=false;
                
                // set power up tools appear time interval
                if(e_pu==400){
                    power_appear=true;
                    // tools appear at random position on map
                    e5_x=rand()%1100;
                    e5_y=rand()%1200;
                }
                else if(e_pu==600){
                    power_appear=false;
                    e_pu=0;
                }
                
                // controlling power up tools flying direction
                if(power_flag_x==false&&power_flag_y==false){
                    e5_x+=50;
                    e5_y+=50;
                }
                else if(power_flag_x==true&&power_flag_y==false){
                    e5_x-=50;
                    e5_y+=50;
                }
                else if(power_flag_x==false&&power_flag_y==true){
                    e5_x+=50;
                    e5_y-=50;
                }
                else if(power_flag_x==true&&power_flag_y==true){
                    e5_x-=50;
                    e5_y-=50;
                }
                
                // give the flying regions of power up tools
                if(e5_x>=ScreenWidth-500) power_flag_x=true;
                else if(e5_x<=50) power_flag_x=false;
                
                if(e5_y>=ScreenHeight-100) power_flag_y=true;
                else if(e5_y<=50) power_flag_y=false;
                
                // if power up was eaten, tool effect remaining time begins to count down
                if(pu_flag==true){
                    pu_interval+=10;
                    if(pu_interval==300){
                        pu_flag=false;
                        pu_interval=0;
                    }
                }
                
            }
            // timer 1 (1.0/100.0)
            else if(events.timer.source==timer[2]){
                
                // setting enemy2 flying dircetions and regions
                if(e2_flag==false) e2_y+=movespeed;
                else if(e2_flag==true) e2_y-=movespeed;
            
                if(e2_y>=ScreenHeight-200) e2_flag=true;
                else if(e2_y<=100) e2_flag=false;
            }
            // timer 3 (1.0/225.0)
            else if(events.timer.source==timer[3]){
                
                // setting enemy3 flying dircetions and regions
                if(e3_flag==false) e3_y+=movespeed;
                else if(e3_flag==true) e3_y-=movespeed;
                
                if(e3_y>=ScreenHeight-200) e3_flag=true;
                else if(e3_y<=100) e3_flag=false;
            }
            // timer 0 (1.0/60.0)
            else if(events.timer.source==timer[0]){
                
                // setting player moving speed
                al_get_keyboard_state(&keystate);
                if(al_key_down(&keystate, ALLEGRO_KEY_DOWN)) b+=movespeed;
                else if(al_key_down(&keystate, ALLEGRO_KEY_UP)) b-=movespeed;
                else if(al_key_down(&keystate, ALLEGRO_KEY_RIGHT)) a+=movespeed;
                else if(al_key_down(&keystate, ALLEGRO_KEY_LEFT)) a-=movespeed;
                
            }
            // timer 5 (1.0/150.0)
            else if(events.timer.source==timer[5]){
                
                // setting enemy3 flying dircetions and regions
                if(e1_flag==false) e1_y+=movespeed;
                else if(e1_flag==true) e1_y-=movespeed;
                
                if(e1_y>=ScreenHeight-200) e1_flag=true;
                else if(e1_y<=100) e1_flag=false;
            }
            // timer 4 (1.0/4.0)
            else if(events.timer.source==timer[4]){
                // shootnote put here for the player shooting animation
                shootnote=false;
                // small bullet list position update
                head=xyupdate(head,70,0);
                // enemy bullet list position update
                e1_head=xyupdate(e1_head,-100,0);
                e2_head=xyupdate(e2_head,-100,0);
                e3_head=xyupdate(e3_head,-100,0);
                // large bullet list(power up) position update
                pu_head=xyupdate(pu_head,70,0);
            }
        }
        
        // if player hp<=0 , player lose;
        if(p_hp<=0) p_flag=true;
        
        // if enemy died, play sound effect once
        if(e1_hp<=0&&!e1){
            e1=true;
            al_play_sample_instance(music_array[5]);
        }
        if(e2_hp<=0&&!e2){
            e2=true;
            al_play_sample_instance(music_array[5]);
        }
        if(e3_hp<=0&&!e3){
            e3=true;
            al_play_sample_instance(music_array[5]);
        }
        
        // check if the small bullets collide with enemy
        bullet *np3,*np4;
        if(head!=NULL){
            np3=head;
            if(np3->next==NULL){
                if((player_collision(np3->x, np3->y, e1_x, e1_y, 30, 30,200,200)||np3->x>=ScreenWidth)&&!e1){
                    if(np3->x<ScreenWidth){
                        e1_hp--;
                        score++;
                    }
                    head = NULL;
                    delete np3;
                    np3 = NULL;
                }
                else if((player_collision(np3->x, np3->y, e2_x, e2_y, 30, 30,250,250)||np3->x>=ScreenWidth)&&!e2){
                    if(np3->x<ScreenWidth){
                        e2_hp--;
                        score++;
                    }
                    head = NULL;
                    delete np3;
                    np3 = NULL;
                }
                else if((player_collision(np3->x, np3->y, e3_x, e3_y, 30, 30,170,100)||np3->x>=ScreenWidth)&&!e3){
                    if(np3->x<ScreenWidth){
                        e3_hp--;
                        score++;
                    }
                    head = NULL;
                    delete np3;
                    np3 = NULL;
                }
                
            }
            else if(np3->next->next==NULL){
                np4=np3->next;
                if((player_collision(np4->x, np4->y, e1_x, e1_y, 30, 30,200,200)||np4->x>=ScreenWidth)&&!e1){
                    if(np4->x<ScreenWidth){
                        e1_hp--;
                        score++;
                    }
                    np3->next=NULL;
                    delete np4;
                    np4=NULL;
                }
                else if((player_collision(np4->x, np4->y, e2_x, e2_y, 30, 30,250,250)||np4->x>=ScreenWidth)&&!e2){
                    if(np4->x<ScreenWidth){
                        e2_hp--;
                        score++;
                    }
                    np3->next=NULL;
                    delete np4;
                    np4=NULL;
                }
                else if((player_collision(np4->x, np4->y, e3_x, e3_y, 30, 30,170,100)||np4->x>=ScreenWidth)&&!e3){
                    if(np4->x<ScreenWidth){
                        e3_hp--;
                        score++;
                    }
                    np3->next=NULL;
                    delete np4;
                    np4=NULL;
                }
                
            }
            else if(np3->next->next!=NULL){
                while(np3->next->next!=NULL) np3=np3->next;
                np4=np3->next;
                if((player_collision(np4->x, np4->y, e1_x, e1_y, 30, 30,200,200)||np4->x>=ScreenWidth)&&!e1){
                    if(np4->x<ScreenWidth){
                        e1_hp--;
                        score++;
                    }
                    np3->next=NULL;
                    delete np4;
                    np4=NULL;
                }
                else if((player_collision(np4->x, np4->y, e2_x, e2_y, 30, 30,250,250)||np4->x>=ScreenWidth)&&!e2){
                    if(np4->x<ScreenWidth){
                        e2_hp--;
                        score++;
                    }
                    np3->next=NULL;
                    delete np4;
                    np4=NULL;
                }
                else if((player_collision(np4->x, np4->y, e3_x, e3_y, 30, 30,170,100)||np4->x>=ScreenWidth)&&!e3){
                    if(np4->x<ScreenWidth){
                        e3_hp--;
                        score++;
                    }
                    np3->next=NULL;
                    delete np4;
                    np4=NULL;
                }
            }
        }
        
        // check if the power-up bullets collide with enemy
        bullet *np5,*np6;
        if(pu_head!=NULL){
            np5=pu_head;
            if(np5->next==NULL){
                if((player_collision(np5->x, np5->y, e1_x, e1_y, 30, 30,200,200)||np5->x>=ScreenWidth)&&!e1){
                    if(np5->x<ScreenWidth){
                        e1_hp=e1_hp-2;
                        score=score+2;
                    }
                    pu_head = NULL;
                    delete np5;
                    np5 = NULL;
                }
                else if((player_collision(np5->x, np5->y, e2_x, e2_y, 30, 30,250,250)||np5->x>=ScreenWidth)&&!e2){
                    if(np5->x<ScreenWidth){
                        e2_hp=e2_hp-2;
                        score=score+2;
                    }
                    pu_head = NULL;
                    delete np5;
                    np5 = NULL;
                }
                else if((player_collision(np5->x, np5->y, e3_x, e3_y, 30, 30,170,100)||np5->x>=ScreenWidth)&&!e3){
                    if(np5->x<ScreenWidth){
                        e3_hp=e3_hp-2;
                        score=score+2;
                    }
                    pu_head = NULL;
                    delete np5;
                    np5 = NULL;
                }
            
            }
            else if(np5->next->next==NULL){
                np6=np5->next;
                if((player_collision(np6->x, np6->y, e1_x, e1_y, 30, 30,200,200)||np6->x>=ScreenWidth)&&!e1){
                    if(np6->x<ScreenWidth){
                        e1_hp=e1_hp-2;
                        score=score+2;
                    }
                    np5->next=NULL;
                    delete np6;
                    np6=NULL;
                }
                else if((player_collision(np6->x, np6->y, e2_x, e2_y, 30, 30,250,250)||np6->x>=ScreenWidth)&&!e2){
                    if(np6->x<ScreenWidth){
                        e2_hp=e2_hp-2;
                        score=score+2;
                    }
                    np5->next=NULL;
                    delete np6;
                    np6=NULL;
                }
                else if((player_collision(np6->x, np6->y, e3_x, e3_y, 30, 30,170,100)||np6->x>=ScreenWidth)&&!e3){
                    if(np6->x<ScreenWidth){
                        e3_hp=e3_hp-2;
                        score=score+2;
                    }
                    np5->next=NULL;
                    delete np6;
                    np6=NULL;
                }
            
            }
            else if(np5->next->next!=NULL){
                while(np5->next->next!=NULL) np5=np5->next;
                
                np6=np5->next;
                if((player_collision(np6->x, np6->y, e1_x, e1_y, 30, 30,200,200)||np6->x>=ScreenWidth)&&!e1){
                    if(np6->x<ScreenWidth){
                        e1_hp=e1_hp-2;
                        score=score+2;
                    }
                    np5->next=NULL;
                    delete np6;
                    np6=NULL;
                }
                else if((player_collision(np6->x, np6->y, e2_x, e2_y, 30, 30,250,250)||np6->x>=ScreenWidth)&&!e2){
                    if(np6->x<ScreenWidth){
                        e2_hp=e2_hp-2;
                        score=score+2;
                    }
                    np5->next=NULL;
                    delete np6;
                    np6=NULL;
                }
                else if((player_collision(np6->x, np6->y, e3_x, e3_y, 30, 30,170,100)||np6->x>=ScreenWidth)&&!e3){
                    if(np6->x<ScreenWidth){
                        e2_hp=e2_hp-2;
                        score=score+2;
                    }
                    np5->next=NULL;
                    delete np6;
                    np6=NULL;
                }
            
            }
        }
        
        // check if the enemy-1 bullets collide with player
        if(e1_head!=NULL){
            np3=e1_head;
            if(np3->next==NULL){
                if((player_collision(np3->x, np3->y, a, b, 60, 60, 150, 125)||np3->x<=0)&&!p_flag &&!e1){
                    if(np3->x>0){
                       al_play_sample_instance(music_array[4]);
                       p_hp = p_hp - 3;
                    }
                    e1_head = NULL;
                    delete np3;
                    np3 = NULL;
                }
            }
            else if(np3->next->next==NULL){
                np4=np3->next;
                if((player_collision(np4->x, np4->y, a, b, 60, 60, 150, 125)||np4->x<=0)&&!p_flag&&!e1){
                    if(np4->x>0){
                        al_play_sample_instance(music_array[4]);
                        p_hp = p_hp - 3;
                    }
                    np3->next=NULL;
                    delete np4;
                    np4=NULL;
                }
            }
            else if(np3->next->next!=NULL){
                while(np3->next->next!=NULL) np3=np3->next;
                np4=np3->next;
                if((player_collision(np4->x, np4->y, a, b, 60, 60, 150, 125)||np4->x<=0)&&!p_flag&&!e1){
                    if(np4->x>0){
                        al_play_sample_instance(music_array[4]);
                        p_hp = p_hp-3;
                    }
                    np3->next=NULL;
                    delete np4;
                    np4=NULL;
                }
            }
        }
        
        // check if the enemy-2 bullets collide with player
        if(e2_head!=NULL){
            np3=e2_head;
            if(np3->next==NULL){
                if((player_collision(np3->x, np3->y, a, b, 100, 75, 150, 125)||np3->x<=0)&&!p_flag&&!e2){
                    if(np3->x>0){
                        al_play_sample_instance(music_array[4]);
                        p_hp = p_hp-5;
                    }
                    e2_head = NULL;
                    delete np3;
                    np3 = NULL;
                }
            }
            else if(np3->next->next==NULL){
                np4=np3->next;
                if((player_collision(np4->x, np4->y, a, b, 100, 75, 150, 125)||np4->x<=0)&&!p_flag&&!e2){
                    if(np4->x>0){
                        al_play_sample_instance(music_array[4]);
                        p_hp = p_hp-5;
                    }
                    np3->next=NULL;
                    delete np4;
                    np4=NULL;
                }
            }
            else if(np3->next->next!=NULL){
                while(np3->next->next!=NULL) np3=np3->next;
                np4=np3->next;
                if((player_collision(np4->x, np4->y, a, b, 100, 75, 150, 125)||np4->x<=0)&&!p_flag&&!e2){
                    if(np4->x>0){
                        al_play_sample_instance(music_array[4]);
                        p_hp = p_hp-5;
                    }
                    np3->next=NULL;
                    delete np4;
                    np4=NULL;
                }
            }
            
        }
        
        // check if the enemy-3 bullets collide with player
        if(e3_head!=NULL){
            np3=e3_head;
            if(np3->next==NULL){
                if((player_collision(np3->x, np3->y, a, b, 90, 60, 150, 125)||np3->x<=0)&&!p_flag&&!e3){
                    if(np3->x>0){
                        al_play_sample_instance(music_array[4]);
                        p_hp = p_hp-2;
                    }
                    e3_head = NULL;
                    delete np3;
                    np3 = NULL;
                }
            }
            else if(np3->next->next==NULL){
                np4=np3->next;
                if((player_collision(np4->x, np4->y, a, b, 90, 60, 150, 125)||np4->x<=0)&&!p_flag&&!e3){
                    if(np4->x>0){
                        al_play_sample_instance(music_array[4]);
                        p_hp = p_hp-2;
                    }
                    np3->next=NULL;
                    delete np4;
                    np4=NULL;
                }
            }
            else if(np3->next->next!=NULL){
                while(np3->next->next!=NULL) np3=np3->next;
                np4=np3->next;
                if((player_collision(np4->x, np4->y, a, b, 90, 60, 150, 125)||np4->x<=0)&&!p_flag&&!e3){
                    if(np4->x>0){
                        al_play_sample_instance(music_array[4]);
                        p_hp = p_hp-2;
                    }
                    np3->next=NULL;
                    delete np4;
                    np4=NULL;
                }
            }
            
        }
        
        // check if the player collide with hp tools
        if(player_collision(a,b,e4_x,e4_y,150,125,100,100)==true && hp_appear==true){
            al_play_sample_instance(music_array[6]);
            hp_appear=false;
            p_hp = p_hp + 3;
        }
        // check if the player collide with power up tools
        if(player_collision(a,b,e5_x,e5_y,150,125,80,80)==true && power_appear==true){
            al_play_sample_instance(music_array[7]);
            power_appear=false;
            pu_flag=true;
        }
        
        
        // checking the status if we can go to ending page
        // if player hp<=0 or all enemies are dead
        if(p_flag||(e1&&e2&&e3)){
            // Go to ending page
            done = true;
            if(p_flag==true) success=false;
            else success=true;
        }
        
        // convert int to string for showing on the screen
        sprintf(p,"%d",p_hp);
        sprintf(hp1,"%d",e1_hp);
        sprintf(hp2,"%d",e2_hp);
        sprintf(hp3,"%d",e3_hp);
        sprintf(grade,"%d",score);
        
        // draw map
        al_draw_scaled_bitmap(game_back,0,0,al_get_bitmap_width(game_back),al_get_bitmap_height(game_back),0,0,ScreenWidth,ScreenHeight,NULL);
        al_draw_text(font[4], BLACK, 1200, 1150, ALLEGRO_ALIGN_LEFT, "Press Space to Leave");
        al_draw_text(font[4], BLACK, 900, 1150, ALLEGRO_ALIGN_LEFT, "Score:");
        al_draw_text(font[4], BLACK, 1070, 1150, ALLEGRO_ALIGN_LEFT, grade);
        
        // if enemy-1 is still alive, then draw it
        if(!e1){
            al_draw_text(font[3], RED, e1_x, e1_y+210, ALLEGRO_ALIGN_LEFT, "hp:");
            al_draw_text(font[3], RED, e1_x+80, e1_y+210, ALLEGRO_ALIGN_LEFT, hp1);
            al_draw_scaled_bitmap(game_bird,0,0,al_get_bitmap_width(game_bird),al_get_bitmap_height(game_bird),e1_x ,e1_y,200,200,NULL);
        }
        // if enemy-2 is still alive, then draw it
        if(!e2){
            al_draw_text(font[3], RED, e2_x, e2_y+230, ALLEGRO_ALIGN_LEFT, "hp:");
            al_draw_text(font[3], RED, e2_x+80, e2_y+230, ALLEGRO_ALIGN_LEFT, hp2);
            al_draw_scaled_bitmap(game_bird1,0,0,al_get_bitmap_width(game_bird1),al_get_bitmap_height(game_bird1),e2_x ,e2_y,250,250,NULL);
        }
        // if enemy-3 is still alive, then draw it
        if(!e3){
            al_draw_text(font[3], RED, e3_x, e3_y+130, ALLEGRO_ALIGN_LEFT, "hp:");
            al_draw_text(font[3], RED, e3_x+80 , e3_y+130, ALLEGRO_ALIGN_LEFT, hp3);
            al_draw_scaled_bitmap(game_bird2,0,0,al_get_bitmap_width(game_bird2),al_get_bitmap_height(game_bird2),e3_x ,e3_y,170,100,NULL);
        }
        // if player is alive, then draw it
        if(!p_flag){
            al_draw_text(font[3], RED, a, b+150, ALLEGRO_ALIGN_LEFT, "hp:");
            al_draw_text(font[3], RED, a+80, b+150, ALLEGRO_ALIGN_LEFT, p);
            if(!shootnote) al_draw_scaled_bitmap(flight,0,0,al_get_bitmap_width(flight),al_get_bitmap_height(flight),a,b,150,125,NULL);
            else if(shootnote) al_draw_scaled_bitmap(shoot,0,0,al_get_bitmap_width(shoot),al_get_bitmap_height(shoot),a,b,150,125,NULL);
        }
        
        // if hp tools appear, then draw it
        if(hp_appear==true) al_draw_scaled_bitmap(life,0,0,al_get_bitmap_width(life),al_get_bitmap_height(life),e4_x ,e4_y,100,100,NULL);
        // if power up tools appear, then draw it
        if(power_appear==true) al_draw_scaled_bitmap(power,0,0,al_get_bitmap_width(power),al_get_bitmap_height(power),e5_x ,e5_y,80,80,NULL);
        
        
        bullet *np2;
        // draw the small bullet list on screen
        if(head!=NULL){
            np2=head;
            while(np2!=NULL){
                al_draw_scaled_bitmap(p_Bullet,0,0,al_get_bitmap_width(p_Bullet),al_get_bitmap_height(p_Bullet),np2->x ,np2->y+110,30,30,NULL);
                np2=np2->next;
            }
        }
        // draw the large bullet list on screen
        if(pu_head!=NULL){
            np2=pu_head;
            while(np2!=NULL){
                al_draw_scaled_bitmap(bomb,0,0,al_get_bitmap_width(bomb),al_get_bitmap_height(bomb),np2->x ,np2->y+50,70,70,NULL);
                np2=np2->next;
            }
        }
        // draw the enemy-1 bullet list on screen
        if(e1_head!=NULL&&!e1){
            np2=e1_head;
            while(np2!=NULL){
                al_draw_scaled_bitmap(electric,0,0,al_get_bitmap_width(electric),al_get_bitmap_height(electric),np2->x,np2->y,60,60,NULL);
                np2=np2->next;
            }
        }
        // draw the enemy-2 bullet list on screen
        if(e2_head!=NULL&&!e2){
            np2=e2_head;
            while(np2!=NULL){
                al_draw_scaled_bitmap(fire,0,0,al_get_bitmap_width(fire),al_get_bitmap_height(fire),np2->x,np2->y,100,75,NULL);
                np2=np2->next;
            }
        }
        // draw the enemy-3 bullet list on screen
        if(e3_head!=NULL&&!e3){
            np2=e3_head;
            while(np2!=NULL){
                al_draw_scaled_bitmap(wind,0,0,al_get_bitmap_width(wind),al_get_bitmap_height(wind),np2->x,np2->y,90,60,NULL);
                np2=np2->next;
            }
        }
        
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
    }
    
    // stop main game background music
    al_stop_sample_instance(music_array[1]);
    // play winning sound effects
    if(success) al_play_sample_instance(music_array[3]);
    // play losing sound effects
    else al_play_sample_instance(music_array[2]);
    
    // ending scene
    while(!done5){
        
        ALLEGRO_EVENT events1;
        al_wait_for_event(event_queue, &events1);
        
        //event control
        if(events1.type == ALLEGRO_EVENT_DISPLAY_CLOSE) done5 = true;
        else if(events1.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(events1.keyboard.keycode)
            {
                case ALLEGRO_KEY_ENTER:
                    done5 = true;
                    break;
            }
        }
        
        // convert int to string for showing on screen
        sprintf(grade,"%d",score);
        
        // render the scene by win or lose
        al_draw_scaled_bitmap(game_back,0,0,al_get_bitmap_width(game_back),al_get_bitmap_height(game_back),0,0,ScreenWidth,ScreenHeight,NULL);
        if(success==true){
            al_draw_text(font[0], BLACK, ScreenWidth/2-60, ScreenHeight/4, ALLEGRO_ALIGN_LEFT, "Win");
            al_draw_scaled_bitmap(turtle,0,0,al_get_bitmap_width(turtle),al_get_bitmap_height(turtle),1100,450,400,400,NULL);
        }
        else if(success==false){
            al_draw_text(font[0], BLACK, ScreenWidth/2-300, ScreenHeight/4, ALLEGRO_ALIGN_LEFT, "Game Over");
            al_draw_scaled_bitmap(sad,0,0,al_get_bitmap_width(sad),al_get_bitmap_height(sad),1100,450,400,400,NULL);
        }
        
        // draw map
        al_draw_text(font[1], BLACK, ScreenWidth/2-140, 2*ScreenHeight/4, ALLEGRO_ALIGN_LEFT, "Score:");
        al_draw_text(font[1], BLACK, ScreenWidth/2+90, 2*ScreenHeight/4, ALLEGRO_ALIGN_LEFT, grade);
        al_draw_text(font[1], BLACK, 450, 3*ScreenHeight/4, ALLEGRO_ALIGN_LEFT, "Press ENTER to Exit");
        al_draw_rounded_rectangle(400, 3*ScreenHeight/4-30, 1160, 3*ScreenHeight/4+110, 5, 5, BLACK, 3);
        
        
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
    
    }
    
    
    // destroy object
    al_destroy_bitmap(begin_back);
    al_destroy_bitmap(game_back);
    al_destroy_bitmap(direction);
    al_destroy_bitmap(bird);
    al_destroy_bitmap(bird1);
    al_destroy_bitmap(bird2);
    al_destroy_bitmap(game_bird);
    al_destroy_bitmap(game_bird1);
    al_destroy_bitmap(game_bird2);
    al_destroy_bitmap(p_Bullet);
    al_destroy_bitmap(shoot);
    al_destroy_bitmap(pika);
    al_destroy_bitmap(turtle);
    al_destroy_bitmap(flight);
    al_destroy_bitmap(fire);
    al_destroy_bitmap(wind);
    al_destroy_bitmap(electric);
    al_destroy_bitmap(bomb);
    al_destroy_bitmap(power);
    al_destroy_bitmap(life);
    al_destroy_bitmap(X);
    al_destroy_bitmap(Z);
    destroy(timer,display ,event_queue,font,music_array);
    
    
    return 0;
}

