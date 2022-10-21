#include "Game.h"
#include "function.h"

Object *SwapState(Object *object, int **data)
{
    int **dataTemp = CreateIntArray2d(ROW, COL);
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            dataTemp[i][j] = data[i][j];
        }
    }
    dataTemp = CandyChange(object, dataTemp);
    dataTemp = CrushCheck(ROW, COL, dataTemp);
    if (CheckCanCrush(dataTemp)) // After swap, candy is connect
    {
        PrintInitCandy(object, data);
        PrintSwapBlock(object);
        MoveCandy(object, data);
        if (object->swap_times < 40)
            object->swap_times = object->swap_times + 2;
        else if (object->swap_times == 40)
        {
            object->state = CRUSH;
            object->run_times = 1;
        }
    }
    else // After swap, candy is'nt connect
    {
        PrintInitCandy(object, data);
        PrintSwapBlock(object);
        MoveCandy(object, data);
        if (object->can_swap)
        {
            if (object->swap_times < 40)
                object->swap_times = object->swap_times + 2;
            else if (object->swap_times == 40)
            {
                object->can_swap = false;
            }
            object->run_times = 1;
        }
        else if (!object->can_swap)
        {
            if (object->swap_times > 0)
                object->swap_times = object->swap_times - 2;
            else if (object->swap_times == 0)
            {
                object->state = GAME;
                object->run_times = 1;
                object->can_swap = true;
            }
        }
    }

    free(dataTemp);
    return object;
}

void PrintSwapBlock(Object *object)
{
    al_draw_bitmap_region(object->coverPlay, 24 + 40 * object->mouse.candyY, 22 + 40 * object->mouse.candyX, 40, 40, 24 + 40 * object->mouse.candyY, 22 + 40 * object->mouse.candyX, 0);
    switch (object->candy_move)
    {
    case UP:
        al_draw_bitmap_region(object->coverPlay, 24 + 40 * object->mouse.candyY, 22 + 40 * (object->mouse.candyX - 1), 40, 40, 24 + 40 * object->mouse.candyY, 22 + 40 * (object->mouse.candyX - 1), 0);
        break;

    case DOWN:
        al_draw_bitmap_region(object->coverPlay, 24 + 40 * object->mouse.candyY, 22 + 40 * (object->mouse.candyX + 1), 40, 40, 24 + 40 * object->mouse.candyY, 22 + 40 * (object->mouse.candyX + 1), 0);
        break;

    case RIGHT:
        al_draw_bitmap_region(object->coverPlay, 24 + 40 * (object->mouse.candyY + 1), 22 + 40 * object->mouse.candyX, 40, 40, 24 + 40 * (object->mouse.candyY + 1), 22 + 40 * object->mouse.candyX, 0);
        break;

    case LEFT:
        al_draw_bitmap_region(object->coverPlay, 24 + 40 * (object->mouse.candyY + 1), 22 + 40 * object->mouse.candyX, 40, 40, 24 + 40 * (object->mouse.candyY - 1), 22 + 40 * object->mouse.candyX, 0);
        break;
    }
}

void PrintOneCandy(Object *object, int **data, int i, int j)
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

// Function : the mouse down is first candy, and move it
void MoveCandy(Object *object, int **data)
{
    int i = object->mouse.candyX;
    int j = object->mouse.candyY;
    int delta = object->swap_times;
    switch (object->candy_move)
    {
    case UP: /****************************** UP **********************************************/
        switch (data[i][j])
        {
        case 1:
            al_draw_bitmap_region(object->candy, 8, 0, 44, 32, 24 + CANDY_W * j, 22 + CANDY_H * i - delta, 0);
            break;
        case 2:
            al_draw_bitmap_region(object->candy, 61, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * i - delta, 0);
            break;
        case 3:
            al_draw_bitmap_region(object->candy, 116, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * i - delta, 0);
            break;
        case 4:
            al_draw_bitmap_region(object->candy, 170, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * i - delta, 0);
            break;
        case 5:
            al_draw_bitmap_region(object->candy, 223, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * i - delta, 0);
            break;
        case 6:
            al_draw_bitmap_region(object->candy, 276, 0, 33, 32, 24 + CANDY_W * j, 22 + CANDY_H * i - delta, 0);
            break;
        }
        switch (data[i - 1][j])
        {
        case 1:
            al_draw_bitmap_region(object->candy, 8, 0, 44, 32, 24 + CANDY_W * j, 22 + CANDY_H * (i - 1) + delta, 0);
            break;
        case 2:
            al_draw_bitmap_region(object->candy, 61, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * (i - 1) + delta, 0);
            break;
        case 3:
            al_draw_bitmap_region(object->candy, 116, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * (i - 1) + delta, 0);
            break;
        case 4:
            al_draw_bitmap_region(object->candy, 170, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * (i - 1) + delta, 0);
            break;
        case 5:
            al_draw_bitmap_region(object->candy, 223, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * (i - 1) + delta, 0);
            break;
        case 6:
            al_draw_bitmap_region(object->candy, 276, 0, 33, 32, 24 + CANDY_W * j, 22 + CANDY_H * (i - 1) + delta, 0);
            break;
        }
        break;

    case DOWN: /****************************** DOWN*********************************************/
        switch (data[i][j])
        {
        case 1:
            al_draw_bitmap_region(object->candy, 8, 0, 44, 32, 24 + CANDY_W * j, 22 + CANDY_H * i + delta, 0);
            break;
        case 2:
            al_draw_bitmap_region(object->candy, 61, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * i + delta, 0);
            break;
        case 3:
            al_draw_bitmap_region(object->candy, 116, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * i + delta, 0);
            break;
        case 4:
            al_draw_bitmap_region(object->candy, 170, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * i + delta, 0);
            break;
        case 5:
            al_draw_bitmap_region(object->candy, 223, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * i + delta, 0);
            break;
        case 6:
            al_draw_bitmap_region(object->candy, 276, 0, 33, 32, 24 + CANDY_W * j, 22 + CANDY_H * i + delta, 0);
            break;
        }
        switch (data[i + 1][j])
        {
        case 1:
            al_draw_bitmap_region(object->candy, 8, 0, 44, 32, 24 + CANDY_W * j, 22 + CANDY_H * (i + 1) - delta, 0);
            break;
        case 2:
            al_draw_bitmap_region(object->candy, 61, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * (i + 1) - delta, 0);
            break;
        case 3:
            al_draw_bitmap_region(object->candy, 116, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * (i + 1) - delta, 0);
            break;
        case 4:
            al_draw_bitmap_region(object->candy, 170, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * (i + 1) - delta, 0);
            break;
        case 5:
            al_draw_bitmap_region(object->candy, 223, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * (i + 1) - delta, 0);
            break;
        case 6:
            al_draw_bitmap_region(object->candy, 276, 0, 33, 32, 24 + CANDY_W * j, 22 + CANDY_H * (i + 1) - delta, 0);
            break;
        }
        break;

    case RIGHT: /****************************** RIGHT *********************************************/
        switch (data[i][j])
        {
        case 1:
            al_draw_bitmap_region(object->candy, 8, 0, 44, 32, 24 + CANDY_W * j + delta, 22 + CANDY_H * i, 0);
            break;
        case 2:
            al_draw_bitmap_region(object->candy, 61, 0, 34, 32, 24 + CANDY_W * j + delta, 22 + CANDY_H * i, 0);
            break;
        case 3:
            al_draw_bitmap_region(object->candy, 116, 0, 32, 32, 24 + CANDY_W * j + delta, 22 + CANDY_H * i, 0);
            break;
        case 4:
            al_draw_bitmap_region(object->candy, 170, 0, 32, 32, 24 + CANDY_W * j + delta, 22 + CANDY_H * i, 0);
            break;
        case 5:
            al_draw_bitmap_region(object->candy, 223, 0, 34, 32, 24 + CANDY_W * j + delta, 22 + CANDY_H * i, 0);
            break;
        case 6:
            al_draw_bitmap_region(object->candy, 276, 0, 33, 32, 24 + CANDY_W * j + delta, 22 + CANDY_H * i, 0);
            break;
        }
        switch (data[i][j + 1])
        {
        case 1:
            al_draw_bitmap_region(object->candy, 8, 0, 44, 32, 24 + CANDY_W * (j + 1) - delta, 22 + CANDY_H * i, 0);
            break;
        case 2:
            al_draw_bitmap_region(object->candy, 61, 0, 34, 32, 24 + CANDY_W * (j + 1) - delta, 22 + CANDY_H * i, 0);
            break;
        case 3:
            al_draw_bitmap_region(object->candy, 116, 0, 32, 32, 24 + CANDY_W * (j + 1) - delta, 22 + CANDY_H * i, 0);
            break;
        case 4:
            al_draw_bitmap_region(object->candy, 170, 0, 32, 32, 24 + CANDY_W * (j + 1) - delta, 22 + CANDY_H * i, 0);
            break;
        case 5:
            al_draw_bitmap_region(object->candy, 223, 0, 34, 32, 24 + CANDY_W * (j + 1) - delta, 22 + CANDY_H * i, 0);
            break;
        case 6:
            al_draw_bitmap_region(object->candy, 276, 0, 33, 32, 24 + CANDY_W * (j + 1) - delta, 22 + CANDY_H * i, 0);
            break;
        }
        break;

    case LEFT: /****************************** LEFT *********************************************/
        switch (data[i][j])
        {
        case 1:
            al_draw_bitmap_region(object->candy, 8, 0, 44, 32, 24 + CANDY_W * j - delta, 22 + CANDY_H * i, 0);
            break;
        case 2:
            al_draw_bitmap_region(object->candy, 61, 0, 34, 32, 24 + CANDY_W * j - delta, 22 + CANDY_H * i, 0);
            break;
        case 3:
            al_draw_bitmap_region(object->candy, 116, 0, 32, 32, 24 + CANDY_W * j - delta, 22 + CANDY_H * i, 0);
            break;
        case 4:
            al_draw_bitmap_region(object->candy, 170, 0, 32, 32, 24 + CANDY_W * j - delta, 22 + CANDY_H * i, 0);
            break;
        case 5:
            al_draw_bitmap_region(object->candy, 223, 0, 34, 32, 24 + CANDY_W * j - delta, 22 + CANDY_H * i, 0);
            break;
        case 6:
            al_draw_bitmap_region(object->candy, 276, 0, 33, 32, 24 + CANDY_W * j - delta, 22 + CANDY_H * i, 0);
            break;
        }
        switch (data[i][j - 1])
        {
        case 1:
            al_draw_bitmap_region(object->candy, 8, 0, 44, 32, 24 + CANDY_W * (j - 1) + delta, 22 + CANDY_H * i, 0);
            break;
        case 2:
            al_draw_bitmap_region(object->candy, 61, 0, 34, 32, 24 + CANDY_W * (j - 1) + delta, 22 + CANDY_H * i, 0);
            break;
        case 3:
            al_draw_bitmap_region(object->candy, 116, 0, 32, 32, 24 + CANDY_W * (j - 1) + delta, 22 + CANDY_H * i, 0);
            break;
        case 4:
            al_draw_bitmap_region(object->candy, 170, 0, 32, 32, 24 + CANDY_W * (j - 1) + delta, 22 + CANDY_H * i, 0);
            break;
        case 5:
            al_draw_bitmap_region(object->candy, 223, 0, 34, 32, 24 + CANDY_W * (j - 1) + delta, 22 + CANDY_H * i, 0);
            break;
        case 6:
            al_draw_bitmap_region(object->candy, 276, 0, 33, 32, 24 + CANDY_W * (j - 1) + delta, 22 + CANDY_H * i, 0);
            break;
        }
        break;
    }
}

