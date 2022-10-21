#include "Game.h"
#include "function.h"

int main(int argc, char **argv)
{
    srand(time(NULL));
    Object *object;
    object = ObjectInit();
    AllegroDriverInit(object);

    object = LoadPicture(object);
    int **data;
    data = CreateIntArray2d(ROW, COL);
    data = RandomArray2d(ROW, COL, data);
    data = CrushCheck(ROW, COL, data);
    data = CandyNoConnect(data, ROW, COL);
    Candy **candy = CreateCandy(ROW, COL);
    al_get_keyboard_state(&object->keyboardState);


    while(!object->finish)
    {
        EventCheck(object, data, candy);
        al_rest(0.05);
        al_flip_display();

        // cout << object->mouse.previousX << ", " << object->mouse.x << ", " << object->mouse.candyX << object->mouse.candyY <<  endl;
        // PrintIntMatrix(data, ROW, COL);
        // cout << "state = " << object->state << "  crush run times = " << object->crush_run_times << endl;
    }

    ScoreSort(object);
    FillOutCSV(object->player);
    FreeAllegroObject(object);
    FreeMatrix(data, ROW);
    return 0;
}
