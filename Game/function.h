#ifndef FUNCTION_H
#define FUNCTION_H

#include "Game.h"

/* Algorithm for matrix **/
int **CreateIntArray2d(int row, int col);
int **RandomArray2d(int row, int col, int **arr);
int **CrushCheck(int row, int col, int **arr);
int **DropCandy(int **data);
void PrintIntMatrix(int **matrix, int row, int col);
int **CandyNoConnect(int **matrix, int row, int col);
int CountScore(int **matrix);
void FreeMatrix(int **matrix, int row);

/* Allegro              **/
void AllegroDriverInit(Object *allegroObject);
Object *ObjectInit();
Object *LoadPicture(Object *object);
void FreeAllegroObject(Object *object);

/* Event state control  **/
void EventCheck(Object *object, int **data, Candy **candy);
void PrintInitCandy(Object *object, int **data);
int **CandyChange(Object *object, int **data);

/* Swap                 **/
void PrintOneCandy(Object *object, int **data, int i, int j);
Object *SwapState(Object *object, int **data);
bool CheckCanCrush(int **data);
void PrintSwapBlock(Object *object);
Object *SwapDirection(Object *object);
void MoveCandy(Object *object, int **data);

/* Crush                **/
Object *CrushState(Object *object, int **data);
void Print33Candy(Object *object, int **data);
void Print66Candy(Object *object, int **data);

/* Drop                 **/
Candy **CreateCandy(int row, int col);
Candy **SetInitialLocation(Candy **candy, int **data);
int **RandomCandy(int **matrix);
void PrintdropCandy(Object *object, int **data, Candy **candy);
Candy **DropMove(Candy **candy);
Object *DropFinishCheck(Object *object, int **data, Candy **candy);

/* Score                **/
Player *CreatePlayer (int number);
void ReadCSV (Player *player);
void FillOutCSV (Player *player);
void ScoreSort(Object *object);
void CheckKeyboardDown(Object *object);

/** music             */
void voice_init(ALLEGRO_SAMPLE_INSTANCE *instance, ALLEGRO_MIXER **mixer, ALLEGRO_VOICE **voice);


#endif

