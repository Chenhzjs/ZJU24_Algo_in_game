#ifndef _INTERFACE_H_
#define _INTERFACE_H_
enum {NEW = 0, CONTINUE, EXIT, INTRODUCTION, QUESTION};
int nowEvent;
void initInterface(); /*初始化界面*/
static void DrawCharacterString();
void startNewGame_1();/*新游戏*/

void continueGame();/*继续*/

void exitGame();/*退出*/

void getRandomMap(int layer);/*生成一条随机的图（有起点，有终点，起点入度为 0，中点出度为 0）*/

void showMap(); 

void restEvent();/*休息*/

void shopEvent();/*商店*/

void treasureEvent();

void startNewGame_2();

#endif 
