#include "Game.h"
#include "function.h"

void EventCheck(Object *object, int **data, Candy **candy)
{
    printf("===================");
    if (!al_is_event_queue_empty(object->event_queue))
    {
        while (al_get_next_event(object->event_queue, &object->events))
        {
            switch (object->events.type)
            {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                switch (object->state)
                {
                case GAME:
                    object->state = START;
                    al_set_sample_instance_playing(object->instance2, false); // close game music
                    break;

                default:
                    object->finish = true;
                    break;
                }

            case ALLEGRO_EVENT_KEY_DOWN:
                if (object->events.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    printf("=======================\n");
                    object->finish = true;
                }
                CheckKeyboardDown( object );
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                printf("=======================mouse\n");
                if (object->events.mouse.button == 1)
                {
                    switch (object->state)
                    {
                    case START:

                        break;

                    case GAME:
                        object->mouse.previousX = object->events.mouse.x;
                        object->mouse.previousY = object->events.mouse.y;
                        object->mouse.candyY = (int)floor((object->mouse.previousX - 24) / 40);
                        object->mouse.candyX = (int)floor((object->mouse.previousY - 24) / 40);
                        break;

                    case RANK:

                        break;
                    }
                }

                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if (object->events.mouse.button == 1)
                {
                    switch (object->state)
                    {
                    case START:
                        if (115 < object->events.mouse.x && object->events.mouse.x < 231 && 298 < object->events.mouse.y && object->events.mouse.y < 335)
                        {
                            object->state = GAME;
                            object->startTime = time(NULL);
                            al_set_sample_instance_playing(object->instance, false);
                            al_set_sample_instance_playing(object->instance2, true);
                        }
                        else if (150 < object->events.mouse.x && object->events.mouse.x < 210 && 360 < object->events.mouse.y && object->events.mouse.y < 420)
                            object->state = RANK;

                        else if (150 < object->events.mouse.x && object->events.mouse.x < 210 && 440 < object->events.mouse.y && object->events.mouse.y < 500)
                            object->finish = true;
                        break;

                    case GAME:
                        if (60 < object->events.mouse.x && object->events.mouse.x < 300 && 60 < object->events.mouse.y && object->events.mouse.y < 333)
                        {
                            object->mouse.x = object->events.mouse.x;
                            object->mouse.y = object->events.mouse.y;
                            object = SwapDirection(object);
                            object->state = SWAP;
                        }
                        break;

                    case RANK:

                        break;
                    }
                }

                break;

            case ALLEGRO_EVENT_TIMER:
                switch ((object)->state)
                {
                case START:
                    al_set_sample_instance_playing(object->instance, true);
                    al_draw_bitmap(object->cover, 0, 0, 0);
                    al_draw_bitmap(object->play_mark, 115, 290, 0);
                    al_draw_bitmap(object->ranks, 150, 360, 0);
                    al_draw_bitmap(object->exit, 150, 440, 0);
                    break;

                case GAME:
                    al_draw_bitmap(object->coverPlay, 0, 0, 0); // Print
                    PrintInitCandy(object, data);               // All
                    al_draw_bitmap(object->hide, 0, 0, 0);      // Candy
                    al_draw_textf(object->font_24, al_map_rgb(128, 42, 42), 50, 500, 0, "SCORE = %d", object->score);
                    object->endTime = time(NULL);
                    if ( (object->endTime - object->startTime) > 60 )
                    {
                        object->state = OVER;
                        al_set_sample_instance_playing(object->instance2, false);
                    }
                    break;

                case SWAP:
                    al_draw_bitmap(object->coverPlay, 0, 0, 0); // Print
                    object = SwapState(object, data);
                    al_draw_bitmap(object->hide, 0, 0, 0); // Candy
                    al_draw_textf(object->font_24, al_map_rgb(128, 42, 42), 50, 500, 0, "SCORE = %d", object->score);
                    if (object->state == CRUSH)
                        data = CandyChange(object, data);
                    break;

                case CRUSH:
                    al_draw_bitmap(object->coverPlay, 0, 0, 0); // Print
                    object = CrushState(object, data);
                    al_draw_bitmap(object->hide, 0, 0, 0); // Candy
                    al_draw_textf(object->font_24, al_map_rgb(128, 42, 42), 50, 500, 0, "SCORE = %d", object->score);
                    if (object->crush_run_times == 0)
                    {
                        object->state = DROP;
                        data = CrushCheck(ROW, COL, data);
                        object->score = object->score + CountScore(data);
                        candy = SetInitialLocation(candy, data);
                        data = DropCandy(data); // after drop
                        data = RandomCandy(data);
                        object->crush_run_times = 10;
                        object->swap_times = 0;
                        object->can_swap = true; // first swap move
                        printf("\n==========crush is over \n");
                    }
                    break;

                case DROP:
                    candy = DropMove(candy);
                    al_draw_bitmap(object->coverPlay, 0, 0, 0); // Print
                    PrintdropCandy(object, data, candy);
                    al_draw_bitmap(object->hide, 0, 0, 0); // Candy
                    al_draw_textf(object->font_24, al_map_rgb(128, 42, 42), 50, 500, 0, "SCORE = %d", object->score);
                    object = DropFinishCheck(object, data, candy);
                    break;

                case RANK:
                    al_draw_bitmap(object->coverRank, 0, 0, 0);
                    al_draw_textf(object->font_24, al_map_rgb(204, 0, 102), 160, 300, 1, "TOP V");
                    for (int i = 0; i < 5; i++)
                    {
                        al_draw_textf(object->font_24, al_map_rgb(204, 0, 102), 160, 340 + 40*i, 1, "%s : %d", object->player[i].mame, object->player[i].score);
                    }
                    break;

                case OVER:
                    al_draw_bitmap(object->cover, 0, 0, 0);
                    al_draw_textf(object->font_24, al_map_rgb(204, 0, 102), 160, 300, 1, "Type in your name");
                    al_draw_textf(object->font_24, al_map_rgb(204, 0, 102), 160, 320, 1, "%c%c%c%c%c",
                                  object->name[0],
                                  object->name[1],
                                  object->name[2],
                                  object->name[3],
                                  object->name[4]
                                 );
                    break;
                }

                break;
            }
        }
    }
}

