#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <typeinfo>
#include <sstream>
#include <fstream>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> // graph
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h> // communicate windows
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h> // draw line

#define ROW 9
#define COL 8
#define CANDY_H 40
#define CANDY_W 40
#define WINDOWS_H 640
#define WINDOWS_W 360
#define FPS 60
#define POINT 10
#define SWAP_SPEED 4
#define SWAP_TIMES 100
#define DROP_SPEED 4

using namespace std;

typedef struct Mouse
{
    int previousX;
    int previousY;
    int x;
    int y;
    int candyX; // row of matrix
    int candyY; // col of matrix
} Mouse;

typedef struct Candy
{
    int initialX;
    int initialY;
    int x;
    int y;

} Candy;

typedef struct Player
{
    char mame[5];
    int score;
} Player;

typedef struct Object
{
    ALLEGRO_EVENT events;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_KEYBOARD_STATE keyboardState;
    ALLEGRO_TIMER *timer;

    ALLEGRO_BITMAP *candy;
    ALLEGRO_BITMAP *candy66;
    ALLEGRO_BITMAP *candy33;
    ALLEGRO_BITMAP *play_mark;
    ALLEGRO_BITMAP *cover;
    ALLEGRO_BITMAP *coverPlay;
    ALLEGRO_BITMAP *ranks;
    ALLEGRO_BITMAP *coverRank;
    ALLEGRO_BITMAP *exit;
    ALLEGRO_BITMAP *hide;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font_24;

    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *instance;
    ALLEGRO_MIXER *mixer;
    ALLEGRO_VOICE *voice;
    ALLEGRO_SAMPLE *sample2;
    ALLEGRO_SAMPLE_INSTANCE *instance2;
    ALLEGRO_MIXER *mixer2;
    ALLEGRO_VOICE *voice2;

    int state;
    int score;
    char name[5];
    int name_length;
    bool finish;
    int swap_times;
    int candy_move; // deriction of move
    bool can_swap;
    int run_times; // the times of cange
    int crush_run_times;
    Mouse mouse;
    Player *player;

    time_t startTime, endTime;

} Object;

typedef enum
{
    START,
    GAME,
    RANK,
    FINISH,
    SWAP,
    CRUSH,
    DROP,
    OVER
} State;

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Move;

#endif

