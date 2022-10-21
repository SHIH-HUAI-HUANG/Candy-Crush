#include "Game.h"
#include "function.h"


void ScoreSort(Object *object)
{
    int number = 5 - 1;
    for (int i = 0; i < 5; i++)
    {

        if (object->score > object->player[i].score)
        {
            while (number > i)
            {
                object->player[number].score = object->player[number-1].score;
                object->player[number].mame[0] = object->player[number - 1].mame[0];
                object->player[number].mame[1] = object->player[number - 1].mame[1];
                object->player[number].mame[2] = object->player[number - 1].mame[2];
                object->player[number].mame[3] = object->player[number - 1].mame[3];
                object->player[number].mame[4] = object->player[number - 1].mame[4];
                number--;
            }
            object->player[i].score = object->score;
            object->player[i].mame[0] = object->name[0];
            object->player[i].mame[1] = object->name[1];
            object->player[i].mame[2] = object->name[2];
            object->player[i].mame[3] = object->name[3];
            object->player[i].mame[4] = object->name[4];
            i = 5; // stop for-loop, stop to compare score
        }
    }
}


Player *CreatePlayer (int number)
{
    Player *player = (Player *) calloc(number, sizeof(Player));
    return player;
}

void ReadCSV (Player *player)
{
    FILE *fp;
    fp = fopen("score.csv", "r");

    if (!fp)
    {
        fprintf(stderr, "failed to open file for reading\n");
    }

    char line[50];
    char *result = NULL;
    fgets(line, 50, fp);
    int i = 0;

    while(fgets(line, 50, fp) != NULL)
    {
        int j = 0;
        result = strtok(line, ",");
        while( result != NULL )
        {
            switch (j)
            {
            case 0:
                sscanf(result, "%s", player[i].mame);
                break;

            case 1:
                player[i].score = atof(result);

                break;
            }
            result = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    fclose (fp);
}


void FillOutCSV (Player *player)
{
    FILE *csv;
    if( (csv = fopen("score.csv", "w")) == NULL )
    {
        puts("Fail to open file!");
        exit(0);
    }
    fprintf(csv, "Name,score\n");
    for (int i = 0; i < 5; i++)
    {
        fprintf(csv, "%s,%d\n", player[i].mame, player[i].score
               );
    }
    fclose (csv);
}



// Function : type the player's name
void CheckKeyboardDown(Object *object)
{
    if (object->state == OVER)
    {
        switch( object->events.keyboard.keycode )
        {
        case ALLEGRO_KEY_ENTER:
            object->state = START;
            break;
        case ALLEGRO_KEY_BACKSPACE:
            if(object->name_length == 0) break;
            object->name_length -= 1;
            object->name[object->name_length] = 0;
            break;
        case ALLEGRO_KEY_A:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'A';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_B:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'B';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_C:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'C';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_D:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'D';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_E:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'E';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_F:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'F';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_G:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'G';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_H:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'H';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_I:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'I';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_J:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'J';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_K:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'K';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_L:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'L';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_M:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'M';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_N:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'N';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_O:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'O';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_P:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'P';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_Q:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'Q';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_R:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'R';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_S:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'S';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_T:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'T';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_U:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'U';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_V:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'V';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_W:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'W';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_X:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'X';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_Y:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'Y';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_Z:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = 'Z';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_0:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = '0';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_1:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = '1';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_2:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = '2';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_3:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = '3';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_4:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = '4';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_5:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = '5';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_6:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = '6';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_7:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = '7';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_8:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = '8';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_9:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = '9';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_COMMA:
            if(object->name_length >= 5) break;
            //必免與格式重複
            //object->name[object->name_length] = ',';
            //object->name_length += 1;
            break;
        case ALLEGRO_KEY_FULLSTOP:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = '.';
            object->name_length += 1;
            break;
        case ALLEGRO_KEY_MINUS:
            if(object->name_length >= 5) break;
            object->name[object->name_length] = '-';
            object->name_length += 1;
            break;

        }
    }
}


















