#include "Game.h"
#include "function.h"

// Function : Memory allocate
// Input    :
// Output   :
int **CreateIntArray2d(int row, int col)
{
    int **address = (int **)calloc(row, sizeof(int *));
    for (int i = 0; i < row; i++)
    {
        address[i] = (int *)calloc(col, sizeof(int));
    }
    return address;
}

int **RandomArray2d(int row, int col, int **arr)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            arr[i][j] = rand() % 6 + 1;
        }
    }
    return arr;
}

// Function : If map apper over 3 candys, turning all to 0.
// Input    :
// Output   :
int **CrushCheck(int row, int col, int **arr)
{
    int temp1[row][col] = {0};
    int temp2[row][col] = {0};

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            temp1[i][j] = arr[i][j];
            temp2[i][j] = arr[i][j];
        }
    }
    /********************** check ROW **********************/
    for (int i = 0; i < row; i++)
    {
        int counts = 1;
        for (int j = 0; j < col; j++)
        {
            if (j == col)
            {
                if (counts >= 3)
                {
                    int pos = j;
                    while (counts > 0)
                    {
                        temp1[i][pos] = 0;
                        pos--;
                        counts--;
                    }
                }
                counts = 1;
            }
            else
            {
                if (arr[i][j] == arr[i][j + 1])
                {
                    counts++;
                }
                else
                {
                    if (counts >= 3)
                    {
                        int pos = j;
                        while (counts > 0)
                        {
                            temp1[i][pos] = 0;
                            pos--;
                            counts--;
                        }
                    }
                    counts = 1;
                }
            }
        }
    }
    /********************** check COL **********************/
    for (int j = 0; j < col; j++)
    {
        int counts = 1;
        for (int i = 0; i < row; i++)
        {
            if (i == (row - 1))
            {
                if (counts >= 3)
                {
                    int pos = i;
                    while (counts > 0)
                    {
                        temp2[pos][j] = 0;
                        pos--;
                        counts--;
                    }
                }
                counts = 1;
            }
            else
            {
                if (arr[i][j] == arr[i + 1][j])
                {
                    counts++;
                }
                else
                {
                    if (counts >= 3)
                    {
                        int pos = i;
                        while (counts > 0)
                        {
                            temp2[pos][j] = 0;
                            pos--;
                            counts--;
                        }
                    }
                    counts = 1;
                }
            }
        }
    }
    /*****************************************************/
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if ((temp1[i][j] == 0) || (temp2[i][j] == 0))
                arr[i][j] = 0;
        }
    }
    return arr;
}

// Function : Initial function for Allegro
void AllegroDriverInit(Object *allegroObject)
{
    /* first, set up Allegro and the graphics mode */
    al_init();             // initialize Allegro
    al_install_keyboard(); // install the keyboard for Allegro to use
    al_init_image_addon();
    al_install_audio();     // install sound driver
    al_init_acodec_addon(); //處理音檔用for .wav
    al_install_mouse();
    al_init_font_addon(); // install font addons
    al_init_ttf_addon();  // TureType Font addon also support .ttc
    al_init_native_dialog_addon();
    al_init_primitives_addon();
    al_reserve_samples(2);

    allegroObject->finish = false;
    allegroObject->score = 0;
    allegroObject->state = START;
    allegroObject->swap_times = 0;
    allegroObject->can_swap = true; // first swap move
    allegroObject->run_times = 1;
    allegroObject->crush_run_times = 10; // anime for candy 100 -> 66 -> 33 per 10 times.

    allegroObject->display = al_create_display(WINDOWS_W, WINDOWS_H);
    al_set_window_title(allegroObject->display, "Candy Crush");
    al_set_window_position(allegroObject->display, 780, 220);

    /* Envent queue **/
    allegroObject->timer = al_create_timer(1.0 / FPS);
    allegroObject->event_queue = al_create_event_queue();
    al_register_event_source(allegroObject->event_queue, al_get_mouse_event_source()); // al_get_mouse_event_source 讓我們所創造的視窗可以檢測到滑鼠
    al_register_event_source(allegroObject->event_queue, al_get_display_event_source(allegroObject->display));
    al_register_event_source(allegroObject->event_queue, al_get_keyboard_event_source());
    al_register_event_source(allegroObject->event_queue, al_get_timer_event_source(allegroObject->timer));
    al_start_timer(allegroObject->timer);

    allegroObject->sample = al_load_sample("./WorldMap.wav");
    allegroObject->instance = al_create_sample_instance (allegroObject->sample);
    voice_init( allegroObject->instance, &(allegroObject->mixer), &(allegroObject->voice));
    al_set_sample_instance_gain(allegroObject->instance, 0.5);
    al_set_sample_instance_playmode(allegroObject->instance, ALLEGRO_PLAYMODE_LOOP);

    allegroObject->sample2 = al_load_sample("./Fruit.wav");
    allegroObject->instance2 = al_create_sample_instance (allegroObject->sample2);
    voice_init( allegroObject->instance2, &(allegroObject->mixer2), &(allegroObject->voice2));
    al_set_sample_instance_gain(allegroObject->instance2, 0.5);
    al_set_sample_instance_playmode(allegroObject->instance2, ALLEGRO_PLAYMODE_LOOP);

    ReadCSV(allegroObject->player);
    allegroObject->name_length = 0;
}

// Function : Memery allocation for struct of Object
Object *ObjectInit()
{
    Object *addr = (Object *)calloc(1, sizeof(Object));
    addr->player = CreatePlayer(5);
    return addr;
}

// Function : loading all address of picture, incuding size of display
Object *LoadPicture(Object *object)
{
    object->candy = al_load_bitmap("./picture/candy100.png");
    object->candy66 = al_load_bitmap("./picture/candy66.png");
    object->candy33 = al_load_bitmap("./picture/candy33.png");
    object->hide = al_load_bitmap("./picture/game_hide_candy.png");
    object->cover = al_load_bitmap("./picture/cover_start.png");
    object->coverRank = al_load_bitmap("./picture/cover_rank.png");
    object->coverPlay = al_load_bitmap("./picture/cover_game.png");
    object->play_mark = al_load_bitmap("./picture/icon_play.png");
    object->ranks = al_load_bitmap("./picture/icon_rank.png");
    object->exit = al_load_bitmap("./picture/icon_exit.png");

    object->font_24 = al_load_font("ARIAL.TTF", 24, 0);

    return object;
}

// Function : Print the Matrix
void PrintIntMatrix(int **matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int **CandyNoConnect(int **matrix, int row, int col)
{
    int counts;
    do
    {
        counts = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (matrix[i][j] == 0)
                {
                    counts++;
                    matrix[i][j] = rand() % 6 + 1;
                }
            }
        }
        matrix = CrushCheck(row, col, matrix);

    }
    while (counts != 0);
    return matrix;
}

void FreeMatrix(int **matrix, int row)
{
    for (int i = 0; i < row; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void PrintInitCandy(Object *object, int **data)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {

            switch (data[i][j])
            {
            case 1:
                al_draw_bitmap_region(object->candy, 8, 0, 44, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 2:
                al_draw_bitmap_region(object->candy, 61, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 3:
                al_draw_bitmap_region(object->candy, 116, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 4:
                al_draw_bitmap_region(object->candy, 170, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 5:
                al_draw_bitmap_region(object->candy, 223, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 6:
                al_draw_bitmap_region(object->candy, 276, 0, 33, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            }
        }
    }
}

int **CandyChange(Object *object, int **data)
{
    int delta_x, delta_y, temp;
    delta_x = object->mouse.x - object->mouse.previousX;
    delta_y = object->mouse.y - object->mouse.previousY;
    if (abs(delta_x) > abs(delta_y))
    {
        if (delta_x > 0)
        {
            temp = data[object->mouse.candyX][object->mouse.candyY];
            data[object->mouse.candyX][object->mouse.candyY] = data[object->mouse.candyX][object->mouse.candyY + 1];
            data[object->mouse.candyX][object->mouse.candyY + 1] = temp;
            object->candy_move = RIGHT;
        }
        else if (delta_x < 0)
        {
            temp = data[object->mouse.candyX][object->mouse.candyY];
            data[object->mouse.candyX][object->mouse.candyY] = data[object->mouse.candyX][object->mouse.candyY - 1];
            data[object->mouse.candyX][object->mouse.candyY - 1] = temp;
            object->candy_move = LEFT;
        }
    }
    else if (abs(delta_y) > abs(delta_x))
    {
        if (delta_y > 0)
        {
            temp = data[object->mouse.candyX][object->mouse.candyY];
            data[object->mouse.candyX][object->mouse.candyY] = data[object->mouse.candyX + 1][object->mouse.candyY];
            data[object->mouse.candyX + 1][object->mouse.candyY] = temp;
            object->candy_move = DOWN;
        }
        else if (delta_y < 0)
        {
            temp = data[object->mouse.candyX][object->mouse.candyY];
            data[object->mouse.candyX][object->mouse.candyY] = data[object->mouse.candyX - 1][object->mouse.candyY];
            data[object->mouse.candyX - 1][object->mouse.candyY] = temp;
            object->candy_move = UP;
        }
    }

    return data;
}

Object *SwapDirection(Object *object)
{
    int delta_x, delta_y;
    delta_x = object->mouse.x - object->mouse.previousX;
    delta_y = object->mouse.y - object->mouse.previousY;
    if (abs(delta_x) > abs(delta_y))
    {
        if (delta_x > 0)
        {
            object->candy_move = RIGHT;
        }
        else if (delta_x < 0)
        {
            object->candy_move = LEFT;
        }
    }
    else if (abs(delta_y) > abs(delta_x))
    {
        if (delta_y > 0)
        {
            object->candy_move = DOWN;
        }
        else if (delta_y < 0)
        {
            object->candy_move = UP;
        }
    }
    return object;
}

void FreeAllegroObject(Object *object)
{
    al_destroy_bitmap(object->cover);
    al_destroy_bitmap(object->coverPlay);
    al_destroy_bitmap(object->candy);
    al_destroy_bitmap(object->candy33);
    al_destroy_bitmap(object->candy66);
    al_destroy_bitmap(object->coverRank);
    al_destroy_bitmap(object->exit);
    al_destroy_bitmap(object->hide);
    al_destroy_display(object->display);
    al_shutdown_font_addon();
    free(object);
}

void voice_init(ALLEGRO_SAMPLE_INSTANCE *instance, ALLEGRO_MIXER **mixer, ALLEGRO_VOICE **voice)
{
    //創建聲音輸出buffer
    *mixer = al_create_mixer(al_get_sample_instance_frequency(instance), al_get_sample_instance_depth(instance), al_get_sample_instance_channels(instance));
    //創建聲音輸出連接口
    *voice = al_create_voice(al_get_sample_instance_frequency(instance), al_get_sample_instance_depth(instance), al_get_sample_instance_channels(instance));
    al_attach_sample_instance_to_mixer(instance, *mixer);//將聲音物件link buffer
    al_attach_mixer_to_voice(*mixer, *voice);//將buffer link 輸出連接口
}












