#include <stdio.h>
#include <string.h>
#include <conio.h> 
#include <graphics.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "interface.h"
#include "character.h"
#include "card.h"
#include "battle.h"
#include "draw.h"
#define PI 3.1415926535
static int state_init;
static int state_option;
static int bless_option[4]; 
const int enemy_number;
double width, height;
static int type[3];
static int card_bought[4];
static int card_lose[3];
static int map_choice_n;
static int flag;
static int flag_shop;
static int flag_treasure; 
int layer;
int p;
extern card_p[3];
//char color[20][15] = {"Black", "Dark Gray", "Gray", "Light Gray", "White", 
//"Red", "Yellow", "Green", "Cyan", "Blue", "Magenta"};

static char bless[20][105] = {"Get 100 money!", "Get a random card!", "Lose a random card!", 
							"Add 10 Max Health!"};
static int bless_chosen[20];
static int bless_num;
static void initBlessingChoose()
{
	int i;
	for(i = 0; i < bless_num; i ++)
	{
		bless_chosen[i] = 0;
	}
}
static int getABlessing()
{
	int p;
	p = rand() % bless_num;
	while(bless_chosen[p] == 1) p = (p + 1) % bless_num;
	bless_chosen[p] = 1;
	return p;
}

static void KeyboardEventProcess_Init(int key, int event)
{
	switch (event) 
	{
	 	case KEY_DOWN:
			 switch (key) 
			 {
			     
                case VK_UP: /*上移键*/
                 	if(state_init != NEW)
		        	{
		        		SetEraseMode(TRUE);
		        		MovePen(width / 10 - 0.25, height * (2.4 - state_init * 0.4) / 5 + 0.08);
		        		DrawArrow(20, 0);
		        		if(state_init == INTRODUCTION)
		        		{
		        			SetPointSize(18);
							MovePen(width * 3.6 / 10, height * 3.2 / 5);
							DrawTextString("Choose your role, try to clime the tower and defeat ");
							MovePen(width * 3.6 / 10, height * 2.8 / 5);
							DrawTextString("the boss in the spire. You have three energy at first. ");
							MovePen(width * 3.6 / 10, height * 2.4 / 5);
							DrawTextString("Then, you can spend energy on using cards to attack, ");
							MovePen(width * 3.6 / 10, height * 2.0 / 5);
							DrawTextString("defend and strengthen. After every battle, you can choose ");
							MovePen(width * 3.6 / 10, height * 1.6 / 5);
							DrawTextString("to get cards and gain money. Meanwhile, you could get the ");
							MovePen(width * 3.6 / 10, height * 1.2 / 5);
							DrawTextString("chance to relax and go shopping. Dear warrior, build ");
							MovePen(width * 3.6 / 10, height * 0.8 / 5);
						    DrawTextString("your cards, explore the highest levels of the tower! ");
						}
						if(state_init == QUESTION)
		        		{
		        			SetPointSize(14);
							MovePen(width * 3.6 / 10, height * 3.2 / 5);
							DrawTextString("Strength: Increases attack damage by X.");
							MovePen(width * 3.6 / 10, height * 2.8 / 5);
							DrawTextString("Weak: target deals 25% less attack damage. ");
							MovePen(width * 3.6 / 10, height * 2.4 / 5);
							DrawTextString("Vulnerable: Target takes 50% more damage from attacks. ");
							MovePen(width * 3.6 / 10, height * 2.0 / 5);
							DrawTextString("Frail: Block gained from cards is reduced by 25%. ");
							MovePen(width * 3.6 / 10, height * 1.6 / 5);
							DrawTextString("Poison: At the beginning of its turn, the target loses X HP and 1 stack of poison.");
							MovePen(width * 3.6 / 10, height * 1.2 / 5);
							DrawTextString("Health: When health = 0, character/enemy will die. ");
							MovePen(width * 3.6 / 10, height * 0.8 / 5);
						    DrawTextString("Block: Decrease the damage by X. ");
						}
		        		state_init --;
		        		SetEraseMode(FALSE);
		        		MovePen(width / 10 - 0.25, height * (2.4 - state_init * 0.4) / 5 + 0.08);
		        		DrawArrow(20, 0);
		        		if(state_init == INTRODUCTION)
		        		{
		        			SetPointSize(18);
							MovePen(width * 3.6 / 10, height * 3.2 / 5);
							DrawTextString("Choose your role, try to clime the tower and defeat ");
							MovePen(width * 3.6 / 10, height * 2.8 / 5);
							DrawTextString("the boss in the spire. You have three energy at first. ");
							MovePen(width * 3.6 / 10, height * 2.4 / 5);
							DrawTextString("Then, you can spend energy on using cards to attack, ");
							MovePen(width * 3.6 / 10, height * 2.0 / 5);
							DrawTextString("defend and strengthen. After every battle, you can choose ");
							MovePen(width * 3.6 / 10, height * 1.6 / 5);
							DrawTextString("to get cards and gain money. Meanwhile, you could get the ");
							MovePen(width * 3.6 / 10, height * 1.2 / 5);
							DrawTextString("chance to relax and go shopping. Dear warrior, build ");
							MovePen(width * 3.6 / 10, height * 0.8 / 5);
						    DrawTextString("your cards, explore the highest levels of the tower! ");
						}
					}
				    break;                     
			    case VK_DOWN:/*下移键*/
			     	if(state_init != QUESTION)
		        	{
		        		SetEraseMode(TRUE);
		        		MovePen(width / 10 - 0.25, height * (2.4 - state_init * 0.4) / 5 + 0.08);
		        		DrawArrow(20, 0);
		        		if(state_init == INTRODUCTION)
		        		{
		        			SetPointSize(18);
							MovePen(width * 3.6 / 10, height * 3.2 / 5);
							DrawTextString("Choose your role, try to clime the tower and defeat ");
							MovePen(width * 3.6 / 10, height * 2.8 / 5);
							DrawTextString("the boss in the spire. You have three energy at first. ");
							MovePen(width * 3.6 / 10, height * 2.4 / 5);
							DrawTextString("Then, you can spend energy on using cards to attack, ");
							MovePen(width * 3.6 / 10, height * 2.0 / 5);
							DrawTextString("defend and strengthen. After every battle, you can choose ");
							MovePen(width * 3.6 / 10, height * 1.6 / 5);
							DrawTextString("to get cards and gain money. Meanwhile, you could get the ");
							MovePen(width * 3.6 / 10, height * 1.2 / 5);
							DrawTextString("chance to relax and go shopping. Dear warrior, build ");
							MovePen(width * 3.6 / 10, height * 0.8 / 5);
						    DrawTextString("your cards, explore the highest levels of the tower! ");
						}
		        		state_init ++;
		        		SetEraseMode(FALSE);
		        		MovePen(width / 10 - 0.25, height * (2.4 - state_init * 0.4) / 5 + 0.08);
		        		DrawArrow(20, 0);
		        		if(state_init == INTRODUCTION)
		        		{
		        			SetPointSize(18);
							MovePen(width * 3.6 / 10, height * 3.2 / 5);
							DrawTextString("Choose your role, try to clime the tower and defeat ");
							MovePen(width * 3.6 / 10, height * 2.8 / 5);
							DrawTextString("the boss in the spire. You have three energy at first. ");
							MovePen(width * 3.6 / 10, height * 2.4 / 5);
							DrawTextString("Then, you can spend energy on using cards to attack, ");
							MovePen(width * 3.6 / 10, height * 2.0 / 5);
							DrawTextString("defend and strengthen. After every battle, you can choose ");
							MovePen(width * 3.6 / 10, height * 1.6 / 5);
							DrawTextString("to get cards and gain money. Meanwhile, you could get the ");
							MovePen(width * 3.6 / 10, height * 1.2 / 5);
							DrawTextString("chance to relax and go shopping. Dear warrior, build ");
							MovePen(width * 3.6 / 10, height * 0.8 / 5);
						    DrawTextString("your cards, explore the highest levels of the tower! ");
						}
						if(state_init == QUESTION)
		        		{
		        			SetPointSize(14);
							MovePen(width * 3.6 / 10, height * 3.2 / 5);
							DrawTextString("Strength: Increases attack damage by X.");
							MovePen(width * 3.6 / 10, height * 2.8 / 5);
							DrawTextString("Weak: target deals 25% less attack damage. ");
							MovePen(width * 3.6 / 10, height * 2.4 / 5);
							DrawTextString("Vulnerable: Target takes 50% more damage from attacks. ");
							MovePen(width * 3.6 / 10, height * 2.0 / 5);
							DrawTextString("Frail: Block gained from cards is reduced by 25%. ");
							MovePen(width * 3.6 / 10, height * 1.6 / 5);
							DrawTextString("Poison: At the beginning of its turn, the target loses X HP and 1 stack of poison.");
							MovePen(width * 3.6 / 10, height * 1.2 / 5);
							DrawTextString("Health: When health = 0, character/enemy will die. ");
							MovePen(width * 3.6 / 10, height * 0.8 / 5);
						    DrawTextString("Block: Decrease the damage by X. ");
						}
					}
                    break;
                case VK_RETURN:/*回车键*/
                	if(state_init == NEW)
                	{
                		cancelKeyboardEvent();
                		flag = 1;
                		startNewGame_1();
					}
		        	if(state_init == CONTINUE) continueGame();
		        	if(state_init == EXIT) 
		        	{
		        		exitGame();
					}
                	break;
			 }
			 break;
		case KEY_UP:
			 break;
	 }	 
}
static void KeyboardEventProcess_Start(int key, int event)
{
	switch (event) 
	{
	 	case KEY_DOWN:
			 switch (key) 
			 {
			     
                case VK_LEFT: /*左移键*/
                 	if(state_character != IRONCLAD && flag)
		        	{
		        		SetEraseMode(TRUE);
		        		MovePen(width * (state_character + 1) / 3, height * 1 / 3 - 0.4);
						DrawArrow(20, PI / 2);
						DrawCharacter(width / 2, height * 3 / 5);
						DrawCharacterString();
		        		state_character --;
		        		SetEraseMode(FALSE);
		        		MovePen(width * (state_character + 1) / 3, height * 1 / 3 - 0.4);
		        		DrawArrow(20, PI / 2);
		        		DrawCharacter(width / 2, height * 3 / 5);
		        		DrawCharacterString();
					}
				    break;                     
			    case VK_RIGHT:/*右移键*/
			     	if(state_character != SILENTER && flag)
		        	{
		        		SetEraseMode(TRUE);
		        		MovePen(width * (state_character + 1) / 3, height * 1 / 3 - 0.4);
						DrawArrow(20, PI / 2);
						DrawCharacter(width / 2, height * 3 / 5);
						DrawCharacterString();
		        		state_character ++;
		        		SetEraseMode(FALSE);
		        		MovePen(width * (state_character + 1) / 3, height * 1 / 3 - 0.4);
		        		DrawArrow(20, PI / 2);
		        		DrawCharacter(width / 2, height * 3 / 5);
		        		DrawCharacterString();
					}
                    break;
                case VK_UP:/*上移键*/
			     	if(state_option != 0 && !flag)
		        	{
		        		SetEraseMode(TRUE);
		        		MovePen(width / 6 - 0.4, height * (4.8 - state_option) / 9 - 0.1);
		        		DrawArrow(20, 0);
		        		state_option --;
		        		SetEraseMode(FALSE);
		        		MovePen(width / 6 - 0.4, height * (4.8 - state_option) / 9 - 0.1);
		        		DrawArrow(20, 0);
					}
                    break;
                case VK_DOWN:/*下移键*/
			     	if(state_option != 3 && !flag)
		        	{
		        		SetEraseMode(TRUE);
		        		MovePen(width / 6 - 0.4, height * (4.8 - state_option) / 9 - 0.1);
		        		DrawArrow(20, 0);
		        		state_option ++;
		        		SetEraseMode(FALSE);
		        		MovePen(width / 6 - 0.4, height * (4.8 - state_option) / 9 - 0.1);
		        		DrawArrow(20, 0);
					}
                    break;
                case VK_RETURN:/*回车键*/
                	if(flag) 
                	{
		        		initNowCharacter(state_character);
		        		storeState(0);
                		cancelKeyboardEvent();
                		startNewGame_2();
					}else if(!flag)
                	{
                		layer = 1;
                		switch(bless_option[state_option])
                		{
                			case 0:
                				changeState(0, 0, MONEY, 100);
                				break;
                			case 1:
                				chooseCard();
                				break;
                			case 2:
                				{
                					int p;
                					p = rand() % cards_number;
                					loseCard(c_card[p].id);
								}
                				break;
                			case 3:
                				changeState(0, 0, MAX_HEALTH, 10);
                				break;
						}
						storeState(0);
                		getRandomMap(layer);
					}
                	break;
			 }
			 break;
		case KEY_UP:
			 break;
	 }	 
}	

static void KeyboardEventProcess_Choose(int key, int event)
{
	switch (event) 
	{
	 	case KEY_DOWN:
			switch (key) 
			{
                case 49: /*1 键*/
                	nowEvent = type[0];
                 	switch(type[0])
					{
						case NORMAL_BATTLE: case HARD_BATTLE: case BOSS_BATTLE:
							freeCharacter();
							storeState(0);
							battleEvent(type[0]);
							break;
						case REST:
							freeCharacter();
							storeState(0);
							restEvent();
							break;
						case SHOP:
							{
								int i;
								freeCharacter();
								storeState(0);
								for(i = 0; i < 3; i ++)
								{
									if(now_character->id == IRONCLAD) p = rand() % 41 + ANGER;
									else p = rand() % 32 + ACROBATICS;
									card_p[i] = p;
									card_bought[i] = 0;
									flag_shop = 0;
								}
							}
							shopEvent(); 
							break;
						case TREASURE:
							freeCharacter();
							storeState(0);
							treasureEvent();
							break;
					}
				    break;                     
			    case 50:/*2 键*/
			    	nowEvent = type[1];
			     	switch(type[1])
					{
						case NORMAL_BATTLE: case HARD_BATTLE: case BOSS_BATTLE:
							freeCharacter();
							storeState(0);
							battleEvent(type[1]);
							break;
						case REST:
							freeCharacter();
							storeState(0);
							restEvent();
							break;
						case SHOP:
							{
								int i;
								freeCharacter();
								storeState(0);
								for(i = 0; i < 3; i ++)
								{
									if(now_character->id == IRONCLAD) p = rand() % 41 + ANGER;
									else p = rand() % 32 + ACROBATICS;
									card_p[i] = p;
									card_bought[i] = 0;
									flag_shop = 0;
								}
							}
							shopEvent(); 
							break;
						case TREASURE:
							freeCharacter();
							storeState(0);
							treasureEvent();
							break;
					}
                    break;
                case 51:/*3 键*/
                	nowEvent = type[2];
			     	switch(type[2])
					{
						case NORMAL_BATTLE: case HARD_BATTLE: case BOSS_BATTLE:
							freeCharacter();
							storeState(0);
							battleEvent(type[2]);
							break;
						case REST:
							freeCharacter();
							storeState(0);
							restEvent();
							break;
						case SHOP:
							{
								int i;
								freeCharacter();
								storeState(0);
								for(i = 0; i < 3; i ++)
								{
									if(now_character->id == IRONCLAD) p = rand() % 41 + ANGER;
									else p = rand() % 32 + ACROBATICS;
									card_p[i] = p;
									card_bought[i] = 0;
									flag_shop = 0;
								}
							}
							shopEvent(); 
							break;
						case TREASURE:
							freeCharacter();
							storeState(0);
							treasureEvent();
							break;
					}
                    break;
			}
			break;
		case KEY_UP:
			break;
	 }	 
}

static void KeyboardEventProcess_Rest(int key, int event)
{
	switch (event) 
	{
	 	case KEY_DOWN:
			 switch (key) 
			 {
                case 49: /*1 键*/
                 	changeState(0, 0, NOW_HEALTH, 0.25 * now_character->max_health);
                 	layer ++;
                 	getRandomMap(layer);
				    break;                     
			    case 50:/*2 键*/
				    {
				    	int p;
				    	int i;
				     	for(i = 0; i < cards_number; i ++)
				     	{
				     		if(c_card[i].upgrade == 0) break; 
						}
						if(i == cards_number) 
						{
							MovePen(width * 1 / 2, height * 1 / 4);
							SetPointSize(18);
							DrawTextString_Middle("All Cards have been upgraded.");
						}else
						{
							p = rand() % cards_number;
					     	while(c_card[p].upgrade == 1) p = (p + 1) % cards_number;
					     	upgradeCard(p);
					     	layer ++;
		                 	getRandomMap(layer);
						}
	                    break;
					}
			 }
			 break;
		case KEY_UP:
			 break;
	 }	 
}
static void KeyboardEventProcess_ShopEvent(int key, int event)
//商店 
{
	switch (event) 
	{
	 	case KEY_DOWN:
			switch (key) 
			{
			    case 49: /*1 键*/
			    	if(flag_shop == 0 && now_character->money >= card[card_p[0]].rarity * 50 && card_bought[0] == 0)
			    	{
			    		card_bought[0] = 1;
			    		getCard(card_p[0]);
	                 	changeState(0, 0, MONEY, -1 * card[card_p[0]].rarity * 50);
	                 	shopEvent();
			    	}else if(flag_shop == 1)
                	{
                		loseCard(card_lose[0]);
                		
                		shopEvent();
                		flag_shop = 0;
					}
                 	break;                   
			    case 50:/*2 键*/
			    	if(flag_shop == 0 && now_character->money >= card[card_p[1]].rarity * 50 && card_bought[1] == 0)
			     	{
			     		card_bought[1] = 1;
			     		getCard(card_p[1]);
				     	changeState(0, 0, MONEY, -1 * card[card_p[1]].rarity * 50);
				     	shopEvent();
			     	}else if(flag_shop == 1)
                	{
                		loseCard(card_lose[1]);
                		shopEvent();
                		flag_shop = 0;
					}
					break;
                case 51:/*3 键*/
	                if(flag_shop == 0 && now_character->money >= card[card_p[2]].rarity * 50 && card_bought[2] == 0)
	                {
	                	card_bought[2] = 1;
	                	getCard(card_p[2]);
						changeState(0, 0, MONEY, -1 * card[card_p[2]].rarity * 50);
						shopEvent();
					}else if(flag_shop == 1)
                	{
                		loseCard(card_lose[2]);
                		shopEvent();
                		flag_shop = 0;
					}
                    break;
                case 52: //4键 烧牌 
                	if(flag_shop == 0 && now_character->money >= 50 && card_bought[3] == 0)
                	{
                		int i;
                		double x, y;
                		InitGraphics();
						width = GetWindowWidth();
						height = GetWindowHeight();
						for(i = 0; i < 3; i ++)
						{
							int p;
							double dx = width / 6, dy = height / 4;
							p = rand() % cards_number;
							card_lose[i] = c_card[p].id;
							x = width * (i * 2 + 1) / 6, y = height / 2;
							MovePen(x - dx + 0.3, y - dy);
							DrawLine(2 * (dx - 0.3), 0);
							DrawLine(0, 2 * dy);
							DrawLine(-2 * (dx - 0.3), 0);
							DrawLine(0, -2 * dy);
							MovePen(x, y - dy - 0.4);
							SetPointSize(16);
							if(i == 0) DrawTextString_Middle("1");
							else if(i == 1) DrawTextString_Middle("2");
							else DrawTextString_Middle("3");
							MovePen(x, y);
							SetPointSize(24);
							DrawTextString_Middle(card[card_lose[i]].name);
						}
						changeState(0, 0, MONEY, -50);
						card_bought[3] = 1;
						flag_shop = 1;
                	}
					break;
				case 81:
					if(flag_shop == 0)
					{
						cancelKeyboardEvent(KeyboardEventProcess_ShopEvent);
					    getRandomMap(++layer);
					}
					break;
            }
		case KEY_UP:
			break;
	 }	 
}
static void KeyboardEventProcess_TreasureEvent(int key, int event)
//遗物 
{
	flag_treasure = 0;
	switch (event) 
	{
	 	case KEY_DOWN:
			 switch (key) 
			 {
                case VK_RETURN: /*1 键*/
                	if(!flag_treasure)
                	{
                		MovePen(width * 2 / 3 - 0.3, height * 9 / 10);
	                 	DrawLine(width * 1 / 3 - 0.1, 0);
						DrawLine(0, height * -4 / 5);
						DrawLine(width * -1 / 3 + 0.1, 0);
						DrawLine(0, height * 4 / 5);
						flag_treasure = 1;
                	}
                	else if(flag_treasure)
                	{
                		layer ++;
                		getRandomMap(layer);
                	}
					break;                     
			 }
			 break;
		case KEY_UP:
			break;
	 }	 
}
void initInterface() /*初始化界面*/
{
	int key;
	
	char title[] = "Slay the Spire";
	char startBotton[] = "New Game";
	char continueBotton[] = "Continue Game";
	char exitBotton[] = "Exit Game";  
	char introductionBotton[]  = "Game Introduction";
	char questionBotton[] = "Game Question";
	double mid_w;
	double mid_h;
	double stringlength;
	InitGraphics();
	width = GetWindowWidth();
	height = GetWindowHeight();
	mid_w = width / 2;
	mid_h = height / 2;
	
	/*Print the title*/
	SetPointSize(64);
	//SetPenColor("Magenta");
	MovePen(mid_w, height * 3 / 4);
	DrawTextString_Middle(title);/*使文字居中输出*/
	/*Print the bottons*/
	SetPointSize(20);
	MovePen(width / 10 - 0.25, height * 2.4 / 5 + 0.08);
	DrawArrow(20, 0);
	MovePen(width / 10, height * 2.4 / 5);
	DrawTextString(startBotton);
	MovePen(width / 10, height * 2 / 5);
	DrawTextString(continueBotton);
	MovePen(width / 10, height * 1.6 / 5);
	DrawTextString(exitBotton);
	MovePen(width / 10, height * 1.2 / 5);
	DrawTextString(introductionBotton);
	MovePen(width / 10, height * 0.8 / 5);
	DrawTextString(questionBotton);
	
	state_init = NEW;
	SetPointSize(50);
	registerKeyboardEvent(KeyboardEventProcess_Init);/*注册init键盘消息回调函数*/
	
}

void startNewGame_1()/*新游戏*/
{
	flag = 1;
	state_character = IRONCLAD;
	InitGraphics();
	width = GetWindowWidth();
	height = GetWindowHeight();
	SetPointSize(40);
	MovePen(width / 2, height * 3 / 4);
	DrawTextString_Middle("Choose Your Character");/*使文字居中输出*/
	
	SetPointSize(24);
	DrawCharacter(width / 2, height * 3 / 5);
	DrawCharacterString();
	MovePen(width * 1 / 3, height * 1 / 3);
	DrawTextString_Middle("The Ironclad");
	MovePen(width * 1 / 3, height * 1 / 3 - 0.4);
	DrawArrow(20, PI / 2);
	MovePen(width * 2 / 3, height * 1 / 3);
	DrawTextString_Middle("The Silenter");
	
	registerKeyboardEvent(KeyboardEventProcess_Start);/*注册start键盘消息回调函数*/
	
}
void startNewGame_2()
{
	//state_character = IRONCLAD;
	double cx;
	bless_num = 4;
	flag = 0;
	InitGraphics();
	width = GetWindowWidth();
	height = GetWindowHeight();
	SetPointSize(40);
	MovePen(width / 2, height * 3 / 4);
	DrawTextString_Middle("Choose your blessing!");/*使文字居中输出*/
	SetPointSize(22);
	state_option = 0;
	initBlessingChoose();
	//InitGraphics();
	// 根据角色标志画 图片
	//startNewGame_1();
	
	MovePen(width / 6 - 0.4, height * 4.8 / 9 - 0.1);
	DrawArrow(20, 0);
	MovePen(width / 6, height * 4.5 / 9);
	DrawLine(0, 0.3);
	MovePen(width / 6 + 0.1, height * 4.5 / 9 + 0.1);
	bless_option[0] = getABlessing();
	DrawTextString(bless[bless_option[0]]);
	cx = GetCurrentX();
	MovePen(width / 6, height * 4.5 / 9);
	DrawLine(cx - 1.6, 0);
	
	MovePen(width / 6, height * 3.5 / 9);
	DrawLine(0, 0.3);
	MovePen(width / 6 + 0.1, height * 3.5 / 9 + 0.1);
	bless_option[1] = getABlessing();
	DrawTextString(bless[bless_option[1]]);
	cx = GetCurrentX();
	MovePen(width / 6, height * 3.5 / 9);
	DrawLine(cx - 1.6, 0);
	
	MovePen(width / 6, height * 2.5 / 9);
	DrawLine(0, 0.3);
	MovePen(width / 6 + 0.1, height * 2.5 / 9 + 0.1);
	bless_option[2] = getABlessing();
	DrawTextString(bless[bless_option[2]]);
	cx = GetCurrentX();
	MovePen(width / 6, height * 2.5 / 9);
	DrawLine(cx - 1.6, 0);
	
	MovePen(width / 6, height * 1.5 / 9);
	DrawLine(0, 0.3);
	MovePen(width / 6 + 0.1, height * 1.5 / 9 + 0.1);
	bless_option[3] = getABlessing();
	DrawTextString(bless[bless_option[3]]);
	cx = GetCurrentX();
	MovePen(width / 6, height * 1.5 / 9);
	DrawLine(cx - 1.6, 0);
	
	registerKeyboardEvent(KeyboardEventProcess_Start);
}

void continueGame()/*继续*/
{
	getStoredState(); 
	switch(nowEvent)
	{
		case NORMAL_BATTLE: case HARD_BATTLE: case BOSS_BATTLE:
			battleEvent(-1);
			break;
		case REST:
			restEvent();
			break;
		case SHOP:
			shopEvent(); 
			break;
		case TREASURE:
			treasureEvent();
			break;
	}
}
void exitGame()/*退出*/
{
	ExitGraphics();
}
void getRandomMap(int layer)/*生成一条随机的图（有起点，有终点，起点入度为 0，中点出度为 0）*/
{
	int i; 
	int p;
	map_choice_n = rand() % 3 + 1;
	if(layer == 53)
	{
		InitGraphics();
		width = GetWindowWidth();
		height = GetWindowHeight();
		SetPointSize(28);
		MovePen(width / 2, height / 2 + 0.5);
		DrawTextString_Middle("You win! But some things are still acting.");
		MovePen(width / 2, height / 2 - 0.5);
		DrawTextString_Middle("Continue climbing the tower and slay the spire more! ");
		return ;
	}
	if(layer == 1)
	{
		type[0] = NORMAL_BATTLE;
		type[1] = NORMAL_BATTLE;
		type[2] = NORMAL_BATTLE;
		map_choice_n = 3;
	}else if(layer % 13 == 0)
	{
		type[0] = BOSS_BATTLE;
		map_choice_n = 1;
	}else if(layer % 7 == 0)
	{
		type[0] = SHOP;
		map_choice_n = 1;
	}else if(layer % 10 == 0)
	{
		type[0] = HARD_BATTLE;
		map_choice_n = 1;
	}else
	{
		for(i = 0; i < map_choice_n; i ++)
		{
			p = rand() % 10000;
			if(p < 5000) type[i] = NORMAL_BATTLE;
			else if(p < 5500) type[i] = HARD_BATTLE;
			else if(p < 8500) type[i] = REST;
			else type[i] = SHOP;
			//type[i] = NORMAL_BATTLE;
		}
		
	}
	showMap();
	cancelKeyboardEvent();
	registerKeyboardEvent(KeyboardEventProcess_Choose);
}
void showMap()
{
	double x, y;
	int i;
	char s1[50];
	InitGraphics();
	width = GetWindowWidth();
	height = GetWindowHeight();
	SetPointSize(28);
	MovePen(width / 2, height * 4 / 5);
	strcpy(s1, "Layer: ");
	integerToString(layer);
	strcat(s1, trans);
	DrawTextString_Middle(s1);
	SetPointSize(22);
	for(i = 0; i < map_choice_n; i ++)
	{
		x = width * (i + 1) / (map_choice_n + 1), y = height / 2;
		MovePen(x - 0.8, y - 1);
		DrawLine(1.6, 0);
		DrawLine(0, 2);
		DrawLine(-1.6, 0);
		DrawLine(0, -2);
		MovePen(x, y - 1.4);
		if(i == 0) DrawTextString_Middle("1");
		else if(i == 1) DrawTextString_Middle("2");
		else DrawTextString_Middle("3");
		MovePen(x, y);
		switch(type[i])
		{
			case NORMAL_BATTLE:
				DrawTextString_Middle("Normal battle");
				break;
			case HARD_BATTLE:
				DrawTextString_Middle("Hard battle");
				break;
			case REST:
				DrawTextString_Middle("rest");
				break;

			case SHOP:
				DrawTextString_Middle("Shop");
				break;
			case TREASURE:
				DrawTextString_Middle("Treasure box");
				break;
			case BOSS_BATTLE:
				DrawTextString_Middle("Boss battle");
				break;
		}
		
	}

}
static void DrawCharacterString()
{
	int t_size = GetPointSize();
	SetPointSize(16);
	if(state_character == IRONCLAD)
	{
		MovePen(width * 1 / 3 - 1.5, height * 2 / 3 - 0.8);
		DrawTextString("HP:    ");
		integerToString(the_character[state_character].max_health);
		DrawTextString_Middle(trans);
		MovePen(width * 1 / 3 - 1.5, height * 2 / 3 - 1.2);
		DrawTextString("Relic: Burning Blood");
		MovePen(width * 1 / 3 - 1.5, height * 2 / 3 - 1.6);
		DrawTextString("At the end of combat, heal 6 HP.");
	}else if(state_character == SILENTER)
	{
		MovePen(width * 2 / 3 - 0.5, height * 2 / 3 - 0.8);
		DrawTextString("HP:    ");
		integerToString(the_character[state_character].max_health);
		DrawTextString_Middle(trans);
		MovePen(width * 2 / 3 - 0.5, height * 2 / 3 - 1.2);
		DrawTextString("Relic: Ring of the Snake");
		MovePen(width * 2 / 3 - 0.5, height * 2 / 3 - 1.6);
		DrawTextString("At the start of each combat, ");
		MovePen(width * 2 / 3 - 0.5, height * 2 / 3 - 1.8);
		DrawTextString("draw 2 additional cards.");
	}
	SetPointSize(t_size);
}
void restEvent()/*休息*/
{
	InitGraphics();
	width = GetWindowWidth();
	height = GetWindowHeight();
	MovePen(width * 1 / 3, height * 2 / 3);
	SetPointSize(24);
	DrawTextString_Middle("Rest");
	MovePen(width * 1 / 3, height * 2 / 3 - 1);
	SetPointSize(12);
	DrawTextString_Middle("Heal 25% of the Max Health.");
	MovePen(width * 1 / 3, height * 2 / 3 - 1.5);
	SetPointSize(12);
	DrawTextString_Middle("1");
	
	MovePen(width * 2 / 3, height * 2 / 3);
	SetPointSize(24);
	DrawTextString_Middle("Upgrade Card");
	MovePen(width * 2 / 3, height * 2 / 3 - 1);
	SetPointSize(12);
	DrawTextString_Middle("Upgrade a RANDOM Card.");
	MovePen(width * 2 / 3, height * 2 / 3 - 1.5);
	SetPointSize(12);
	DrawTextString_Middle("2");
	
	cancelKeyboardEvent();
	registerKeyboardEvent(KeyboardEventProcess_Rest);
}


void shopEvent()/*商店*/
{
	double x, y;
	double dx = width / 6, dy = height / 5;
	int i;
	int j;
	char s1[50];
	InitGraphics();
	width = GetWindowWidth();
	height = GetWindowHeight();
	MovePen(width * 1 / 2, height * 9 / 10);
	SetPointSize(24);

	
	DrawTextString_Middle("Shop Event");
	MovePen(width * 3 / 4 - 0.5, height * 1 / 3);
	SetPointSize(12);
	DrawTextString("press Q to leave the shop.");
	MovePen(width * 3 / 4 - 0.5, height * 1 / 3 - 0.5);
	DrawTextString("press number to but different goods.");

	MovePen(width * 1 / 4 - 0.5, height * 1 / 3);
	SetPointSize(12);
	strcpy(s1, "Money: ");
	integerToString(now_character->money);
	strcat(s1, trans);
	DrawTextString(s1);
	
	SetEraseMode(FALSE);
	if(card_bought[3] == 1) SetEraseMode(TRUE);
	MovePen(width * 1 / 2 - 0.5 *dx, height * 1 / 4 + 0.5 * dx);
	DrawLine(dx * 1, 0);
	DrawLine(0, -1 * dx);
	DrawLine(-1 * dx, 0);
	DrawLine(0, 1 * dx);
	MovePen(width * 1 / 2 - 0.3 * dx, height * 1 / 4 +  0.3 * dx);
	DrawLine(0.6 * dx, -0.6 * dx);
	MovePen(width * 1 / 2 - 0.3 * dx, height * 1 / 4 -  0.3 * dx);
	DrawLine(0.6 * dx, 0.6 * dx);
	MovePen(width * 1 / 2, height * 1 / 4 - 0.5 * dx - 0.4);
	DrawTextString_Middle("4 cost: 50");
	SetEraseMode(FALSE);
	for(i = 0; i < 3; i ++)
	{
		//int p;
		SetEraseMode(FALSE);
		if(card_bought[i] == 1) SetEraseMode(TRUE);
		x = width * (i * 2 + 1) / 6, y = height * 2 / 3;
		MovePen(x - dx + 0.3, y - dy);
		DrawLine(2 * (dx - 0.3), 0);
		DrawLine(0, 2 * dy);
		DrawLine(-2 * (dx - 0.3), 0);
		DrawLine(0, -2 * dy);
		MovePen(x, y - dy - 0.4);
		if(i == 0) 
		{
			int cost_money; 
			strcpy(s1, "1 cost: ");
			if(card[card_p[i]].rarity == COMMON) cost_money = 50;
			else if(card[card_p[i]].rarity == UNCOMMON) cost_money = 100;
			else if(card[card_p[i]].rarity == RARE) cost_money = 150;
			integerToString(cost_money);
			strcat(s1, trans);
			strcat(s1, " Money. ");
			DrawTextString_Middle(s1);
		}
		else if(i == 1)
		{
			int cost_money;
			strcpy(s1, "2 cost: ");
			if(card[card_p[i]].rarity == COMMON) cost_money = 50;
			else if(card[card_p[i]].rarity == UNCOMMON) cost_money = 100;
			else if(card[card_p[i]].rarity == RARE) cost_money = 150;
			integerToString(cost_money);
			strcat(s1, trans);
			strcat(s1, " Money. ");
			DrawTextString_Middle(s1);

		}
		else
		{
			int cost_money;
			strcpy(s1, "3 cost: ");
			if(card[card_p[i]].rarity == COMMON) cost_money = 50;
			else if(card[card_p[i]].rarity == UNCOMMON) cost_money = 100;
			else if(card[card_p[i]].rarity == RARE) cost_money = 150;
			integerToString(cost_money);
			strcat(s1, trans);
			strcat(s1, " Money. ");
			DrawTextString_Middle(s1);

		}
		MovePen(x, y + dy - 0.25);
		SetPointSize(20);
		DrawTextString_Middle(card[card_p[i]].name);
		j = 2;
		MovePen(x, y + dy - j * 0.25);
		j ++;
		SetPointSize(12);
		integerToString(card[card_p[i]].energy_cost);
		strcpy(s1, "Energy cost: ");
		strcat(s1, trans);
		DrawTextString_Middle(s1);
		
		if(card[card_p[i]].attack != 0)
		{
			MovePen(x, y + dy - j * 0.25);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Cause ");
			integerToString(card[card_p[i]].attack);
			strcat(s1, trans);
			strcat(s1, " Attack. ");
			DrawTextString_Middle(s1);
		}
		if(card[card_p[i]].block != 0)
		{
			MovePen(x, y + dy - j * 0.25);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Gain ");
			integerToString(card[card_p[i]].block);
			strcat(s1, trans);
			strcat(s1, " Block. ");
			DrawTextString_Middle(s1);
		}
		if(card[card_p[i]].strength != 0)
		{
			if(card[card_p[i]].strength > 0)
			{
				MovePen(x, y + dy - j * 0.25);
				j ++;
				strcpy(s1, "");
				strcat(s1, "Gain ");
				integerToString(card[card_p[i]].strength);
				strcat(s1, trans);
				strcat(s1, " Strength. ");
				DrawTextString_Middle(s1);
			}
			if(card[card_p[i]].strength < 0)
			{
				MovePen(x, y + dy - j * 0.25);
				j ++;
				strcpy(s1, "");
				strcat(s1, "Cause ");
				integerToString(card[card_p[i]].strength * (-1));
				strcat(s1, trans);
				strcat(s1, " Strength lost. ");
				DrawTextString_Middle(s1);
			}

		}
		if(card[card_p[i]].poison != 0)
		{
			MovePen(x, y + dy - j * 0.25);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Cause ");
			integerToString(card[card_p[i]].poison);
			strcat(s1, trans);
			strcat(s1, " Poison. ");
			DrawTextString_Middle(s1);
		}
		if(card[card_p[i]].vulnerable != 0)
		{
			MovePen(x, y + dy - j * 0.25);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Cause ");
			integerToString(card[card_p[i]].vulnerable);
			strcat(s1, trans);
			strcat(s1, " Vulnerable. ");
			DrawTextString_Middle(s1);
		}
		if(card[card_p[i]].weak != 0)
		{
			MovePen(x, y + dy - j * 0.25);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Cause ");
			integerToString(card[card_p[i]].weak);
			strcat(s1, trans);
			strcat(s1, " Weak. ");
			DrawTextString_Middle(s1);
		}
		if(card[card_p[i]].draw != 0)
		{
			MovePen(x, y + dy - j * 0.25);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Draw ");
			integerToString(card[card_p[i]].draw);
			strcat(s1, trans);
			strcat(s1, " card. ");
			DrawTextString_Middle(s1);
		}
		if(card[card_p[i]].discard != 0)
		{
			MovePen(x, y + dy - j * 0.25);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Discard ");
			integerToString(card[card_p[i]].discard);
			strcat(s1, trans);
			strcat(s1, " card. ");
			DrawTextString_Middle(s1);
		}
		if(card[card_p[i]].consume != 0)
		{
			MovePen(x, y + dy - j * 0.25);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Consume ");
			integerToString(card[card_p[i]].consume);
			strcat(s1, trans);
			strcat(s1, " card. ");
			DrawTextString_Middle(s1);
		}
		switch(card[card_p[i]].id)
		{
			case ANGER:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Increase this card's A-");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("-ttack by 1 this battle."); 
				break;
			case BODY_SLAM:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Cause Attack equal to");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("your current Block."); 
				break;
			case CLASH:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Can only be used if all");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Card Type are an Attack."); 
				break;
			case HEAVY_BLADE: 
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Add 3 times of Strength to Attack.");
				break;
			case BLOODLETTING:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Gain 2 Energy");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Lose 3 Health.");
				break; // Gain 2(3) Energy
			case ENTRENCH:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Double your current Block.");
				break; 
			case HEMOKINESIS: case POWER_THROUGH:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Lose 2 Health.");
				break; 
			case RAMPAGE:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Increase this card's A-");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("-ttack by 5 this battle."); 
				break;
			case SECOND_WIND:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Consume all non-Attack cards, gain");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("5 Block for each card Consumed."); 
				break;
			case SEEING_RED:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Gain 2 energy.");
				break;
			case SEVER_SOUL:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Consume all non-Attack cards.");
				break;
			case SPOT_WEAKNESS: 
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Only when the enemy intends to Attack.");
				break;
			case FEED:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("If this Kills an enemy, ");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("gain 3 permanent Max Health."); 
				break;
			case FIEND_FIRE:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Exhaust all cards in your hand.");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Each card will cause 7 Attack."); 
				break; 
			case LIMIT_BREAK:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Double your current Strength.");
				break; 
			case OFFERING:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Lose 6 Health.");
				break;
			case REAPER:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Heal Health equal to Attack.");
			case BANE:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("If the enemy is Poisoned, ");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("double the Attack.");
				break;
			case POISON_EXTRACT:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("gain Block equal to an enemy's Poison.");
				break; 
			case CALCULATED_GAMBLE:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Discard all hand card and");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("draw same number of cards.");
				break;
			case CATALYST:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Double an enemy's Poison.");
				break;
			case CONCENTRATE:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Gain 2 Energy.");
				break;
			case TACTICIAN:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("If it is Discarded, ");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("gain 1 Energy.");
				break;
			case ADRENALINE:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Gain 1 Energy.");
				break;
			case CORPSE_EXPLOSION:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("When the enemy was Killed, ");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("cause Attack equal to its");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("max Health to ALL enemies.");
				break; 
			case GLASS_KNIFE:
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Decrease this card's A- ");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("-ttack by 4 this battle.");
				break;
			case GRAND_FINALE: 
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("Can only be used if no");
				MovePen(x, y + dy - j * 0.25);
				j ++;
				DrawTextString_Middle("cards in the Draw Pile."); 
				break;
		}
		MovePen(x, y + dy - j * 0.25);
		j ++;
		strcpy(s1, "");
		if(card[card_p[i]].confirm == 0)
		{
			strcat(s1, "Object: All. ");
		}else
		{
			strcat(s1, "Object: One. ");
		}
		DrawTextString_Middle(s1);
		if(card[card_p[i]].usage == -1)
		{
			MovePen(x, y + dy - j * 0.25);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Consumed. ");
			DrawTextString_Middle(s1);
		}else if(card[card_p[i]].usage == 0)
		{
			MovePen(x, y + dy - j * 0.25);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Unplayable. ");
			DrawTextString_Middle(s1);
		}
	}
	SetEraseMode(FALSE);
	cancelKeyboardEvent();
	registerKeyboardEvent(KeyboardEventProcess_ShopEvent);
}
void treasureEvent()
{
	InitGraphics();
	width = GetWindowWidth();
	height = GetWindowHeight();
	MovePen(width * 1 / 11, height * 9 / 10);
	SetPointSize(16);
	DrawTextString("press ENTER to open the treasure");
	MovePen(width * 1 / 2, height * 8 / 9);
	SetPointSize(24);
	DrawTextString_Middle("Treasure Event");
	//画宝箱
	MovePen(width * 1 / 10, height * 1 / 2);
	DrawLine(0, height * -1 / 3);
	DrawLine(width * 1 / 7, height * -1 / 9);
	DrawLine(width * 2 / 7, height * 2 / 9);
	
	DrawLine(0, height * 1 / 3);
	DrawLine(width * -1 / 7, height * 1 / 9);
	DrawLine(width * -2 / 7, height * -2 / 9);
	
	DrawLine(width * 1 / 7, height * -1 / 9);
	DrawLine(width * 2 / 7, height * 2 / 9);
	MovePen(width * 17 / 70, height * 7 / 18);
	DrawLine(0, height * -1 / 3);
//	MovePen(width * 37 / 70, height * 3 / 18);
//	DrawLine(0, height * -1 / 3);
//	MovePen(width * 1 / 10, height * 1 / 2);
//	DrawLine(width * 2 / 7, height * 2 / 9);
//	DrawLine(width * 1 / 7, height * -1 / 9);
	
	MovePen(width * 1 / 10, height * 7 / 18);
	DrawLine(width * 1 / 7, height * -1 / 9);
	DrawLine(width * 2 / 7, height * 2 / 9);
	
	MovePen(width * 27 / 70 - 0.5, height * 4 / 9 - 0.3);
	DrawLine(0, height * -1 / 10);
	MovePen(width * 27 / 70 + 0.5, height * 4 / 9 + 0.3);
	DrawLine(0, height * -1 / 10);
	cancelKeyboardEvent();
	registerKeyboardEvent(KeyboardEventProcess_TreasureEvent);
}
/*
 predefined color names:
 *
 *    Black, Dark Gray, Gray, Light Gray, White,
 *    Red, Yellow, Green, Cyan, Blue, Magenta
*/
