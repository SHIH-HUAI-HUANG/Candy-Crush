#include "Game.h"
#include "function.h"

// Function : Let all 0 float on the top.
int **DropCandy(int **data)
{
    int temp[ROW][COL] = {0};
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            temp[i][j] = data[i][j];
            data[i][j] = 0;
            cout << "data = " << data[i][j] << endl;
        }
    }
    /************** Algorethm ******************/
    int count;    // for the times of check
    int nowCheck; // for temp matrix
    for (int k = 0; k < COL; k++)
    {
        nowCheck = ROW - 1;
        count = ROW - 1;
        for (int l = 0; l < ROW; l++)
        {
            if (temp[nowCheck][k] != 0)
            {
                data[count][k] = temp[nowCheck][k];
                count--;
            }
            nowCheck--;
        }
    }
    PrintIntMatrix(data, ROW, COL);
    return data;
}

// Function : Check the candy can crush
bool CheckCanCrush(int **data)
{
    int zero = 0;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (data[i][j] == 0)
                zero++;
        }
    }

    if (zero == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Function : memory allocation for candy's information
Candy **CreateCandy(int row, int col)
{
    Candy **address = (Candy **)calloc(row, sizeof(Candy *));
    for (int i = 0; i < row; i++)
    {
        address[i] = (Candy *)calloc(col, sizeof(Candy));
    }
    return address;
}

// Function : Set initial location for candys
Candy **SetInitialLocation(Candy **candy, int **data)
{
    int flag = ROW - 1;
    int number = ROW - 1;
    int count = 1;
    for (int j = 0; j < COL; j++)
    {
        for (int i = 0; i < ROW; i++)
        {
            if (data[number][j] != 0)
            {
                candy[flag][j].initialY = 22 + 40 * number;
                flag--;
            }
            number--;
        }
        while (flag >= 0)
        {
            candy[flag][j].initialY = 22 - 40 * count;

            flag--;
            count++;
            cout << "flag = " << flag << endl;
        }
        flag = ROW - 1;
        number = ROW - 1;
        count = 1;
    }

    return candy;
}

// Function : After candys drop, fill up all empty location.
int **RandomCandy(int **matrix)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (matrix[i][j] == 0)
                matrix[i][j] = rand() % 6 + 1;
        }
    }
    return matrix;
}

// Function : all dropping candys change their location.
Candy **DropMove(Candy **candy)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (candy[i][j].initialY != (22 + 40 * i))
                candy[i][j].initialY = candy[i][j].initialY + DROP_SPEED;
        }
    }
    return candy;
}

// Function : if all location is right, game_state set GAME.
Object *DropFinishCheck(Object *object, int **data, Candy **candy)
{
    int **temp = CreateIntArray2d(ROW, COL);
    for (int k = 0; k < ROW; k++)
    {
        for (int l = 0; l < COL; l++)
        {
            temp[k][l] = data[k][l];
        }
    }
    temp = CrushCheck(ROW, COL, temp);
    printf("\n===== in the drop 11111111\n");
    PrintIntMatrix(temp, ROW, COL);
    printf("\n===== in the drop 22222222\n");
    int count = 0, zero = 0;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (candy[i][j].initialY != (22 + 40 * i))
                count++;
            /***************************/
            if (temp[i][j] == 0)
                zero++;
        }
    }

    if (count == 0)
    {
        if (zero == 0)
        {
            object->state = GAME;
        }
        else
        {
            object->state = CRUSH;
        }
    }
    return object;
}

void PrintdropCandy(Object *object, int **data, Candy **candy)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            switch (data[i][j])
            {
            case 1:
                al_draw_bitmap_region(object->candy, 8, 0, 44, 32, 24 + CANDY_W * j, candy[i][j].initialY, 0);
                break;
            case 2:
                al_draw_bitmap_region(object->candy, 61, 0, 34, 32, 24 + CANDY_W * j, candy[i][j].initialY, 0);
                break;
            case 3:
                al_draw_bitmap_region(object->candy, 116, 0, 32, 32, 24 + CANDY_W * j, candy[i][j].initialY, 0);
                break;
            case 4:
                al_draw_bitmap_region(object->candy, 170, 0, 32, 32, 24 + CANDY_W * j, candy[i][j].initialY, 0);
                break;
            case 5:
                al_draw_bitmap_region(object->candy, 223, 0, 34, 32, 24 + CANDY_W * j, candy[i][j].initialY, 0);
                break;
            case 6:
                al_draw_bitmap_region(object->candy, 276, 0, 33, 32, 24 + CANDY_W * j, candy[i][j].initialY, 0);
                break;
            }
        }
    }
}

