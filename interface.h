#ifndef _INTERFACE_H_
#define _INTERFACE_H_
enum {NEW = 0, CONTINUE, EXIT, INTRODUCTION, QUESTION};
int nowEvent;
void initInterface(); /*��ʼ������*/
static void DrawCharacterString();
void startNewGame_1();/*����Ϸ*/

void continueGame();/*����*/

void exitGame();/*�˳�*/

void getRandomMap(int layer);/*����һ�������ͼ������㣬���յ㣬������Ϊ 0���е����Ϊ 0��*/

void showMap(); 

void restEvent();/*��Ϣ*/

void shopEvent();/*�̵�*/

void treasureEvent();

void startNewGame_2();

#endif 
