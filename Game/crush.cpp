#include "Game.h"
#include "function.h"

Object *CrushState(Object *object, int **data)
{
    int **dataTemp1 = CreateIntArray2d(ROW, COL);
    int **dataTemp2 = CreateIntArray2d(ROW, COL);
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            dataTemp1[i][j] = data[i][j];
            dataTemp2[i][j] = data[i][j];
        }
    }
    dataTemp1 = CrushCheck(ROW, COL, dataTemp1);
    for (int k = 0; k < ROW; k++)
    {
        for (int l = 0; l < COL; l++)
        {
            if (dataTemp1[k][l] == 0)
                dataTemp2[k][l] = dataTemp2[k][l] + 10;
        }
    }
    if (5 < object->crush_run_times && object->crush_run_times <= 10)
    {
        printf("66\n");
        // 66
        Print66Candy(object, dataTemp2);
        object->crush_run_times--;
    }
    else if (0 < object->crush_run_times && object->crush_run_times <= 5)
    {
        // 33
        Print33Candy(object, dataTemp2);
        object->crush_run_times--;
    }

    return object;
}

void Print66Candy(Object *object, int **data)
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
            case 11:
                al_draw_bitmap_region(object->candy66, 8, 0, 44, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 12:
                al_draw_bitmap_region(object->candy66, 61, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 13:
                al_draw_bitmap_region(object->candy66, 116, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 14:
                al_draw_bitmap_region(object->candy66, 170, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 15:
                al_draw_bitmap_region(object->candy66, 223, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 16:
                al_draw_bitmap_region(object->candy66, 276, 0, 33, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            }
        }
    }
}

void Print33Candy(Object *object, int **data)
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
            case 11:
                al_draw_bitmap_region(object->candy33, 8, 0, 44, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 12:
                al_draw_bitmap_region(object->candy33, 61, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 13:
                al_draw_bitmap_region(object->candy33, 116, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 14:
                al_draw_bitmap_region(object->candy33, 170, 0, 32, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 15:
                al_draw_bitmap_region(object->candy33, 223, 0, 34, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            case 16:
                al_draw_bitmap_region(object->candy33, 276, 0, 33, 32, 24 + CANDY_W * j, 22 + CANDY_H * i, 0);
                break;
            }
        }
    }
}

int CountScore(int **matrix)
{
    int score = 0;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (matrix[i][j] == 0)
                score++;
        }
    }

    return score * POINT;
}
