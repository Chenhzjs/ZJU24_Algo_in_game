//#include <stdio.h>
#include <string.h>
//#include <conio.h> 
#include <graphics.h>
#include <math.h>
#include <windows.h>
//#include <stdlib.h>
#include <time.h>

#include "character.h"
#include "card.h"
#include "battle.h"
#include "draw.h"
#define PI 3.1415926535

static int card_option;
static int enemy_option;
extern double width, height;
static int flag;
static int action_type[10][10];
static int action_type_num[10];
static int action_value[10][10];
static int show_n_time;
static int enemy_death[10];
static int enemy_alive_n;
static int timeflag;
int card_p[3];
static int turn; //0 character  1 enemy
extern layer;
static int flag_discard;
static int flag_consume;
static int battle_round;
extern getRandomMap(int roundn);
static void TimerEventProcess(int timeID)
{
	switch(timeID)
	{
		case 0:
			SetPointSize(12);
//			MovePen(width / 2, height * 1 / 5 + 0.05);
//			DrawTextString_Middle("The card cannot be used.");

			SetEraseMode(timeflag);
			MovePen(width / 2, height * 2 / 5 + 0.1);
			DrawTextString_Middle("The card cannot be used.");
			timeflag = 1 - timeflag;
			show_n_time ++;
			if(show_n_time == 1) 
			{
				cancelTimer(0);
			}
			//SetEraseMode(FALSE);
			break;
		case 1:
			SetPointSize(12);
			SetEraseMode(timeflag);
			MovePen(width / 2, height * 2 / 5 + 0.1);
			DrawTextString_Middle("Insufficient energy to use this card.");
			timeflag = 1 - timeflag;
			show_n_time ++;
			if(show_n_time == 1) 
			{
				cancelTimer(1);
			}
			//SetEraseMode(FALSE);
			break;
		case 2:
			{
				int i, k;
				double x, y;
				SetPointSize(12);
				SetEraseMode(timeflag);
				show_n_time ++;
				i = (show_n_time - 1) / 2;
				while(enemy_death[i] == 1 && i < now_enemy_n)
				{
					show_n_time += 2;
					i = i + 1;
				}
				k  = 1;
				while(enemy_death[i + k] == 1 && i + k < now_enemy_n)
				{
					k = k + 1;
				}
				if(timeflag == 1 && i + k < now_enemy_n)
				{
					x = width * (i + k + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
					y = height * 3 / 5 + 0.5;
					DrawEnemyAct(x, y, i + k);
				}
				enemyActing(i);
				if(now_character->now_health <= 0)
				{
					InitGraphics();
					width = GetWindowWidth();
					height = GetWindowHeight();
					cancelTimer(2);
					cancelKeyboardEvent();
					cancelTimerEvent();
					MovePen(width / 2, height / 2);
					SetPointSize(28);
					SetPenColor("RED");
					DrawTextString_Middle("YOU DIE! GAME OVER!");
					SetPenColor("BLACK");
				}
				timeflag = 1 - timeflag;
				if(show_n_time >= 2 * now_enemy_n) 
				{
					cancelTimer(2);
					turn = 0;
					changeState(0, 0, BLOCK, -1 * now_character->block);
					++ battle_round;
					battleInterface();
				}
				//SetEraseMode(FALSE);
				break;
			}
		case 3:
			{
				int i, k;
				double x, y;
				SetPointSize(12);
				timeflag = 1;
				SetEraseMode(timeflag);
				for(i = 0; i < now_enemy_n; i ++)
				{
					
					SetPenColor("RED");
					x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
					y = height * 1 / 2;
					MovePen(x - 0.5, y + 0.5);
					DrawLine(1, -1);
					MovePen(x - 0.5, y - 0.5);
					DrawLine(1, 1);
					
					SetPenColor("Violet");
					x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
					y = height * 1 / 2;
					y = y + 0.4;
					MovePen(x, y - 0.4);
					DrawArrow(40, PI / -2);
					MovePen(x - 0.4, y - 0.4);
					DrawArrow(40, PI / -2);
					MovePen(x + 0.4, y - 0.4);
					DrawArrow(40, PI / -2);
					SetPenColor("BLACK");
				}
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				
				x =  width * 0.45;
				y = height * 1 / 2 - 0.1;
				MovePen(x, y);
				DrawLine(width / 2, 0);
				
				SetPenColor("GREEN");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				Line(x, x + 0.3, y + 0.4, y + 0.2);
				Line(x + 0.3, x, y + 0.2, y - 0.4);
				Line(x, x - 0.3, y + 0.4, y + 0.2);
				Line(x - 0.3, x, y + 0.2, y - 0.4);
				
				SetPenColor("BLUE");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x - 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x + 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				
				SetPenColor("BLACK");
				cancelTimer(3);
				
				SetEraseMode(FALSE);
				break;
			}
	}
}
static void KeyboardEventProcess_Battle(int key, int event)
{
	switch (event) 
	{
	 	case KEY_DOWN:
			switch (key) 
			{
                case VK_LEFT: /*���Ƽ�*/
                	if(turn == 0)
	                 	if(flag == 0)
	                 	{
	                 		if(card_option != 0 && handn != 0)
		                 	{
		                 		double startx = 1;
								double dx = (width - startx * 2) / 10;
								double dy = height / 5 - 0.4;
		                		SetEraseMode(TRUE);
		            			MovePen(startx + dx * (11 - handn) / 2 + dx * card_option, dy + 0.3);
		    					DrawArrow(20, PI / -2);
		    					DrawDetailedCard(hand[card_option]);
		    					
		            			card_option --;
		            			
		            			SetEraseMode(FALSE);
		            			MovePen(startx + dx * (11 - handn) / 2 + dx * card_option, dy + 0.3);
		            			DrawArrow(20, PI / -2); 
		            			DrawDetailedCard(hand[card_option]);
		                	}
						}else
						{
							if(enemy_option != 0)
							{
								double x, y;
								int k = 1;
								erasePreviousEnemyState(enemy_option);
								SetEraseMode(TRUE);
								
								DrawDetailedCard(hand[card_option]);
								
								while(now_enemy[enemy_option - k]->now_health <= 0 && enemy_option - k != 0) k ++;
								if(enemy_option - k != -1 && now_enemy[enemy_option - k]->now_health > 0) enemy_option -= k;
								
								SetEraseMode(FALSE);
								
								showEnemyState(enemy_option);
								if(handn != 0) DrawDetailedCard(hand[card_option]);
							}
							
						}
				    break;                     
			    case VK_RIGHT:/*���Ƽ�*/
			    	if(turn == 0)
				     	if(flag == 0)
				     	{
					     	if(card_option != handn - 1 && handn != 0)
		        			{
		        				double startx = 1;
								double dx = (width - startx * 2) / 10;
								double dy = height / 5 - 0.4;
		            			SetEraseMode(TRUE);
		            			MovePen(startx + dx * (11 - handn) / 2 + dx * card_option, dy + 0.3);
		       					DrawArrow(20, PI / -2);
		       					DrawDetailedCard(hand[card_option]);
		       					
		             			card_option ++;
		             			
		             			SetEraseMode(FALSE);
		             			MovePen(startx + dx * (11 - handn) / 2 + dx * card_option, dy + 0.3);
		             			DrawArrow(20, PI / -2);
		             			if(handn != 0) DrawDetailedCard(hand[card_option]);
		             		}
						}else
						{
							if(enemy_option != now_enemy_n - 1)
							{
								double x, y;
								int k = 1;
								erasePreviousEnemyState(enemy_option);
								SetEraseMode(TRUE);
								
								DrawDetailedCard(hand[card_option]);
								
								while(now_enemy[enemy_option + k]->now_health <= 0 && enemy_option + k != now_enemy_n - 1) k ++;
								if(enemy_option + k != now_enemy_n && now_enemy[enemy_option + k]->now_health > 0) enemy_option += k;
								
								SetEraseMode(FALSE);
								
								showEnemyState(enemy_option);
								DrawDetailedCard(hand[card_option]);
							}
						}
                    break;
                case VK_RETURN:/*�س���*/
                	if(turn == 0)
					{
                		if(flag_discard != 0)
                		{
                			int i;
                			
                			SetEraseMode(TRUE);
							DrawCard();
							discardCard(flag_discard);
							if(handn == 0) 
							{
								SetEraseMode(FALSE);
								flag_discard = 0;
								card_option = 0;
								DrawCard();
								break;
							}
							g_card[hand[card_option]].card_state = DISCARD; 
							discardn ++;
							flag_discard --;
							SetEraseMode(FALSE);
							if(flag_discard != 0) discardCard(flag_discard);
							for(i = card_option; i < handn - 1; i ++)
							{
								hand[i] = hand[i + 1];
							}
							handn --;
							card_option = 0;
							DrawCard();
						}else if(flag_consume != 0)
						{
							int i;
                			SetEraseMode(TRUE);
							DrawCard();
							consumeCard(flag_consume);
							if(handn == 0) 
							{
								SetEraseMode(FALSE);
								flag_discard = 0;
								card_option = 0;
								DrawCard();
								break;
							}
							g_card[hand[card_option]].card_state = CONSUMED; 
							consumedn ++;
							flag_consume --;
							SetEraseMode(FALSE);
							
							if(flag_consume != 0) consumeCard(flag_consume);
							for(i = card_option; i < handn - 1; i ++)
							{
								hand[i] = hand[i + 1];
							}
							handn --;
							card_option = 0;
							DrawCard();
						}else if(flag_discard == 0 && flag_discard == 0)
						{
							int i;
		                	double x, y;
		                	SetEraseMode(TRUE);
		                	for(i = 0; i < now_enemy_n; i ++)
							{
								
								x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
								y = height * 3 / 5 + 0.5;
								if(now_enemy[i]->now_health <= 0) continue;
								DrawEnemyAct(x, y, i);
							}
							SetEraseMode(FALSE);
		                	useCard(hand[card_option]);
		                	SetEraseMode(FALSE);
		                	if(now_character->now_health <= 0)
							{
								InitGraphics();
								width = GetWindowWidth();
								height = GetWindowHeight();
								cancelTimer(2);
								cancelKeyboardEvent();
								cancelTimerEvent();
								MovePen(width / 2, height / 2);
								SetPointSize(28);
								SetPenColor("RED");
								DrawTextString_Middle("YOU DIE! GAME OVER!");
								SetPenColor("BLACK");
							}
		                	for(i = 0; i < now_enemy_n; i ++)
							{
								x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
								y = height * 3 / 5 + 0.5;
								if(now_enemy[i]->now_health <= 0) continue;
								DrawEnemyAct(x, y, i);
							}
		                	enemy_option = now_enemy_n - 1;
				        	for(i = now_enemy_n - 1; i >= 0; i --)
				        	{
				        		SetEraseMode(TRUE);
				        		showEnemyState(i);
				        		if(enemy_death[i] == 0 && now_enemy[i]->now_health <= 0)
				        		{
				        			DrawEnemy(now_enemy_n);
				        			SetEraseMode(TRUE);
				        			x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
									y = height * 3 / 5 + 0.5;
				        			DrawEnemyAct(x, y, i);
				        			enemy_alive_n --;
				        			SetEraseMode(FALSE);
				        			enemy_death[i] = 1;
								}
								if(enemy_death[i] == 0 && enemy_option > i)
								{
									enemy_option = i;
								}
							}
							SetEraseMode(FALSE);
							showEnemyState(enemy_option);
							SetEraseMode(FALSE);
							card_option = 0;
							DrawCard();
							if(handn != 0)
							{
								DrawDetailedCard(hand[card_option]);
							}
		                	if(enemy_alive_n == 0) 
							{
								layer ++;
								changeState(0, 0, VULNERABLE, -1 * now_character->vulnerable);
								changeState(0, 0, WEAK, -1 * now_character->weak);
								changeState(0, 0, FRAIL, -1 * now_character->frail);
								changeState(0, 0, BLOCK, -1 * now_character->block);
								if(now_character->id ==IRONCLAD) changeState(0, 0, NOW_HEALTH, 6);
								freeEnemy(now_enemy_n);
								freeCharacter();
								storeState(now_enemy_n);
								cancelTimerEvent();
								cancelKeyboardEvent();
								battleInterface();
								chooseCard();
							}
							flag = 0; 
						}
					}
                	break;
				case 69:/*e*/
					if(turn == 0)
					{
						if(flag_discard == 0 && flag_consume == 0)
						{
							int i = 0;
							int j;
							double x, y;
							SetEraseMode(TRUE);
		                	for(i = 0; i < now_enemy_n; i ++)
							{
								
								x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
								y = height * 3 / 5 + 0.5;
								if(now_enemy[i]->now_health <= 0) continue;
								DrawEnemyAct(x, y, i);
							}
							SetEraseMode(FALSE);
							erasePreviousEnemyState(enemy_option);
							for(i = 0; i < now_enemy_n; i ++)
							{
								if(enemy_death[i] == 1) continue;
								if(now_enemy[i]->poison != 0)
								{
									changeState(1, i, NOW_HEALTH, now_enemy[i]->poison * -1);
									changeState(1, i, POISON, -1);
								}
							}
							for(i = 0; i < now_enemy_n; i ++)
							{
								x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
								y = height * 3 / 5 + 0.5;
								if(now_enemy[i]->now_health <= 0) continue;
								DrawEnemyAct(x, y, i);
							}
		                	enemy_option = now_enemy_n - 1;
				        	for(i = now_enemy_n - 1; i >= 0; i --)
				        	{
				        		SetEraseMode(TRUE);
				        		showEnemyState(i);
				        		if(enemy_death[i] == 0 && now_enemy[i]->now_health <= 0)
				        		{
				        			DrawEnemy(now_enemy_n);
				        			SetEraseMode(TRUE);
				        			x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
									y = height * 3 / 5 + 0.5;
				        			DrawEnemyAct(x, y, i);
				        			enemy_alive_n --;
				        			SetEraseMode(FALSE);
				        			enemy_death[i] = 1;
								}
								if(enemy_death[i] == 0 && enemy_option > i)
								{
									enemy_option = i;
								}
							}
							if(enemy_alive_n == 0) 
							{
								layer ++;
								changeState(0, 0, VULNERABLE, -1 * now_character->vulnerable);
								changeState(0, 0, WEAK, -1 * now_character->weak);
								changeState(0, 0, FRAIL, -1 * now_character->frail);
								changeState(0, 0, BLOCK, -1 * now_character->block);
								if(now_character->id ==IRONCLAD) changeState(0, 0, NOW_HEALTH, 6);
								freeEnemy(now_enemy_n);
								freeCharacter();
								storeState(now_enemy_n);
								cancelTimerEvent();
								cancelKeyboardEvent();
								chooseCard();
							}
							SetEraseMode(FALSE);
							showEnemyState(enemy_option);
							erasePreviousCharacterState();
							changeState(0, 0, VULNERABLE, -1);
							changeState(0, 0, WEAK, -1);
							changeState(0, 0, FRAIL, -1);
							showCharacterState();
							turn = 1;
							startTimer(2, 800);
							timeflag = 0;
							show_n_time = 0;
							SetEraseMode(TRUE);
							x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
							y = height * 3 / 5 + 0.5;
							DrawEnemyAct(x, y, enemy_option);
							DrawCard();
							DrawDetailedCard(card_option);
							for(j = 0; j < handn; j ++)
							{
								g_card[hand[j]].card_state = DISCARD; 
							}
							discardn += handn;
							handn = 0;
							SetEraseMode(FALSE);
							DrawCard();
						}
					}
					break;
				case VK_SPACE:
					if(turn == 0)
						if(flag_discard == 0 && flag_consume == 0)
						{
							if(flag == 0)
							{
								//int i;
								flag = 1;
	//		       				if(enemy_death[enemy_option] == 1)
	//		       				{
	//		       					for(i = 0; i < now_enemy_n; i ++)
	//		       					{
	//		       						if(enemy_death[i] == 0)
	//		       						{
	//		       							enemy_option = i;
	//		       							break;
	//									}
	//								}
	//							}
	//							showEnemyState(enemy_option);
							}else
							{
								
								flag = 0;
			       				if(handn == 0) break;
							}
						}
					break;
			}
			
		case KEY_UP:
			break;
	 }	 
}

static void KeyboardEventProcess_ChooseCard(int key, int event)
{
	switch (event) 
	{
	 	case KEY_DOWN:
			switch (key) 
			{
			    case 49: /*1 ��*/
                 	getCard(card_p[0]);
                 	cancelKeyboardEvent(KeyboardEventProcess_ChooseCard);
                 	getRandomMap(layer);
				    break;                     
			    case 50:/*2 ��*/
			     	getCard(card_p[1]);
			     	cancelKeyboardEvent(KeyboardEventProcess_ChooseCard);
			     	getRandomMap(layer);
                    break;
                case 51:/*3 ��*/
			     	getCard(card_p[2]);
			     	cancelKeyboardEvent(KeyboardEventProcess_ChooseCard);
			     	getRandomMap(layer);
                    break;
                case 52:
                	cancelKeyboardEvent(KeyboardEventProcess_ChooseCard);
			     	getRandomMap(layer);
					break;
				
            }
		case KEY_UP:
			break;
	 }	 
}
void battleEvent(int battle)/*ս��*/
{


	int i;
	enemy_option = 0;
	card_option = 0;
	max_energy = 3;
	
	cancelKeyboardEvent();
	registerTimerEvent(TimerEventProcess);
	registerKeyboardEvent(KeyboardEventProcess_Battle);
	
	if(battle == NORMAL_BATTLE)
	{
		initNowEnemy(layer, NORMAL);
		
	}else if(battle == HARD_BATTLE)
	{
		initNowEnemy(layer, HARD); 
	}else if(battle == BOSS_BATTLE)
	{
		initNowEnemy(layer, BOSS);
	}
	freeCharacter();
	storeState(now_enemy_n);
	//while(enemy_death < now_enemy_n)
	gameCard();
	for(i = 0; i <= now_enemy_n; i ++)
	{
		enemy_death[i] = 0;
	}
	enemy_alive_n = now_enemy_n;
	drawn = cards_number, handn = 0, discardn = 0, consumedn = 0;
	battle_round = 1;
	turn = 0; 
	battleInterface();

}
void battleInterface()
{
	int i;
	InitGraphics();
	width = GetWindowWidth();
	height = GetWindowHeight();
	now_energy = max_energy;
	flag = 0;
	SetEraseMode(FALSE);
	DrawBattleRound(battle_round);
	DrawCharacter(width / 4, height * 3 / 5);
	DrawBotton();
	DrawEnemy(now_enemy_n);
	if(now_character->id == SILENTER && battle_round == 1) getRandomCard(7);
	else getRandomCard(5);
	for(i = 0; i < now_enemy_n; i ++)
	{
		if(enemy_death[i] == 0)
		{
			changeState(1, i, VULNERABLE, -1);
			changeState(1, i, WEAK, -1);
			changeState(1, i, POISON, -1);
		}
	}
	for(i = 0; i < now_enemy_n; i ++)
	{
		double x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
		double y = height * 3 / 5 + 0.5;
		if(now_enemy[i]->now_health <= 0) continue;
		getRandomEnemyAct(i);
		DrawEnemyAct(x, y, i);
	}
	enemy_option = 0;
	flag_discard = 0;
	flag_consume = 0;

	showCharacterState();
	if(enemy_death[enemy_option] == 1)
	{
		for(i = 0; i < now_enemy_n; i ++)
		{
			if(enemy_death[i] == 0)
			{
				enemy_option = i;
				break;
			}
		}
	}
	showEnemyState(enemy_option); 
	DrawCard();
	 
} 
void useCard(int number)
{
	int i;
	double x, y;
	int attack, block;
	if(handn == 0) return ;
	if(g_card[number].usage == 0)
	{
		cancelTimer(0);
		SetEraseMode(TRUE);
		DrawCard();
		startTimer(0, 1000);
		show_n_time = 0;
		timeflag = 1;
		SetPointSize(12);
		SetEraseMode(FALSE);
		MovePen(width / 2, height * 2 / 5 + 0.1);
		DrawTextString_Middle("The card cannot be used.");
	}else if(g_card[number].energy_cost > now_energy)
	{
		cancelTimer(1);
		startTimer(1, 1000);
		SetEraseMode(TRUE);
		DrawCard();
		show_n_time = 0;
		timeflag = 1;
		SetPointSize(12);
		
		SetEraseMode(FALSE);
		MovePen(width / 2, height * 2 / 5 + 0.1);
		DrawTextString_Middle("Insufficient energy to use this card.");
	}else
	{
		SetEraseMode(TRUE);
		DrawDetailedCard(hand[card_option]);
		SetEraseMode(FALSE);
		startTimer(3, 500);
		switch(g_card[number].id)
		{
			case ANGER:
				SetPenColor("RED");
				x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				attack = g_card[number].attack + now_character->strength;
				if(now_enemy[enemy_option]->vulnerable != 0)
				{
					attack = attack * 1.5;
				}
				if(now_character->weak != 0)
				{
					attack = attack * 0.75;
				}
				erasePreviousEnemyState(enemy_option); 
				changeState(1, enemy_option, NOW_HEALTH, attack * -1);
				showEnemyState(enemy_option);
				if(g_card[number].upgrade == 0) g_card[number].attack ++;
				else g_card[number].attack += 2;
				break;
			case BODY_SLAM:
				SetPenColor("RED");
				x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				attack = now_character->block + now_character->strength;
				if(now_enemy[enemy_option]->vulnerable != 0)
				{
					attack = attack * 1.5;
				}
				if(now_character->weak != 0)
				{
					attack = attack * 0.75;
				}
				erasePreviousEnemyState(enemy_option); 
				changeState(1, enemy_option, NOW_HEALTH, attack * -1);
				showEnemyState(enemy_option);
				break;
			case CLASH:
				for(i = 0; i < handn; i ++)
				{
					if(g_card[hand[i]].type != ATTACK) break;
				}
				if(i == handn)
				{
					SetPenColor("RED");
					x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
					y = height * 1 / 2;
					MovePen(x - 0.5, y + 0.5);
					DrawLine(1, -1);
					MovePen(x - 0.5, y - 0.5);
					DrawLine(1, 1);
					SetPenColor("BLACK");
					attack = g_card[number].attack + now_character->strength;
					if(now_enemy[enemy_option]->vulnerable != 0)
					{
						attack = attack * 1.5;
					}
					if(now_character->weak != 0)
					{
						attack = attack * 0.75;
					}
					erasePreviousEnemyState(enemy_option); 
					changeState(1, enemy_option, NOW_HEALTH, attack * -1);
					showEnemyState(enemy_option);
				}else
				{
					cancelTimer(0);
					startTimer(0, 1000);
					show_n_time = 0;
					timeflag = 1;
					SetPointSize(12);
					SetEraseMode(FALSE);
					MovePen(width / 2, height * 2 / 5 + 0.1);
					DrawTextString_Middle("The card cannot be used.");
					return ;
				}
				break;
			case HEAVY_BLADE: 
				SetPenColor("RED");
				x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				if(g_card[number].upgrade == 0) g_card[number].attack + now_character->strength * 3;
				else attack = g_card[number].attack + now_character->strength * 5;
				if(now_enemy[enemy_option]->vulnerable != 0)
				{
					attack = attack * 1.5;
				}
				if(now_character->weak != 0)
				{
					attack = attack * 0.75;
				}
				erasePreviousEnemyState(enemy_option); 
				changeState(1, enemy_option, NOW_HEALTH, attack * -1);
				showEnemyState(enemy_option);
				break;
			case BLOODLETTING:
				SetPenColor("BLUE");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x - 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x + 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				
				SetPenColor("RED");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				erasePreviousCharacterState(); 
				changeState(0, 0, NOW_HEALTH, -3);
				showCharacterState();
				SetEraseMode(TRUE);
				DrawCard();
				SetEraseMode(FALSE);
				if(g_card[number].upgrade == 0) now_energy += 2;
				else now_energy += 3;
				break; 
			case ENTRENCH:
				SetPenColor("GREEN");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				Line(x, x + 0.3, y + 0.4, y + 0.2);
				Line(x + 0.3, x, y + 0.2, y - 0.4);
				Line(x, x - 0.3, y + 0.4, y + 0.2);
				Line(x - 0.3, x, y + 0.2, y - 0.4);
				SetPenColor("BLACK");
				erasePreviousCharacterState(); 
				changeState(0, 0, BLOCK, now_character->block);
				showCharacterState();
				break; 
			case HEMOKINESIS: 
				SetPenColor("RED");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				attack = g_card[number].attack + now_character->strength;
				if(now_enemy[enemy_option]->vulnerable != 0)
				{
					attack = attack * 1.5;
				}
				if(now_character->weak != 0)
				{
					attack = attack * 0.75;
				}
				erasePreviousEnemyState(enemy_option); 
				changeState(1, enemy_option, NOW_HEALTH, attack * -1);
				showEnemyState(enemy_option);
				erasePreviousCharacterState(); 
				changeState(0, 0, NOW_HEALTH, -2);
				showCharacterState();
				break;
			case POWER_THROUGH:
				SetPenColor("RED");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				erasePreviousCharacterState(); 
				changeState(0, 0, NOW_HEALTH, -2);
				showCharacterState();
				SetPenColor("GREEN");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				Line(x, x + 0.3, y + 0.4, y + 0.2);
				Line(x + 0.3, x, y + 0.2, y - 0.4);
				Line(x, x - 0.3, y + 0.4, y + 0.2);
				Line(x - 0.3, x, y + 0.2, y - 0.4);
				SetPenColor("BLACK");
				erasePreviousCharacterState(); 
				changeState(0, 0, BLOCK, g_card[number].block);
				showCharacterState();
				break; 
			case RAMPAGE:
				SetPenColor("RED");
				x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				attack = g_card[number].attack + now_character->strength;
				if(now_enemy[enemy_option]->vulnerable != 0)
				{
					attack = attack * 1.5;
				}
				if(now_character->weak != 0)
				{
					attack = attack * 0.75;
				}
				erasePreviousEnemyState(enemy_option); 
				changeState(1, enemy_option, NOW_HEALTH, attack * -1);
				showEnemyState(enemy_option);
				if(g_card[number].upgrade == 0) g_card[number].attack += 5;
				else g_card[number].attack += 8;
				break;
			case SECOND_WIND:
				{
					int tt = 0;
					int j;
					SetPenColor("GREEN");
					x = width / 4 - 0.5;
					y = height * 1 / 2;
					Line(x, x + 0.3, y + 0.4, y + 0.2);
					Line(x + 0.3, x, y + 0.2, y - 0.4);
					Line(x, x - 0.3, y + 0.4, y + 0.2);
					Line(x - 0.3, x, y + 0.2, y - 0.4);
					SetPenColor("BLACK");
					SetEraseMode(TRUE);
					DrawCard();
					SetEraseMode(FALSE);
					for(i = 0; i < handn; i ++)
					{
						if(g_card[hand[i]].type != ATTACK)
						{
							tt ++;
							g_card[hand[i]].card_state = CONSUMED;
							consumedn ++;
							for(j = i; j < handn - 1; j ++)
							{
								hand[j] = hand[j + 1];
							}
							handn --;
						}
					}
					erasePreviousCharacterState(); 
					changeState(0, 0, BLOCK, tt * g_card[number].block);
					showCharacterState();
					break;
				}
			case SEEING_RED:
				SetPenColor("BLUE");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x - 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x + 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				SetPenColor("BLACK");
				SetEraseMode(TRUE);
				DrawCard();
				SetEraseMode(FALSE);
				now_energy += 2;
				break;
			case SEVER_SOUL:
				{
					int tt = 0;
					int j;
					SetPenColor("RED");
					x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
					y = height * 1 / 2;
					MovePen(x - 0.5, y + 0.5);
					DrawLine(1, -1);
					MovePen(x - 0.5, y - 0.5);
					DrawLine(1, 1);
					SetPenColor("BLACK");
					for(i = 0; i < handn; i ++)
					{
						if(g_card[hand[i]].type != ATTACK)
						{
							tt ++;
							g_card[hand[i]].card_state = CONSUMED;
							consumedn ++;
							for(j = i; j < handn - 1; j ++)
							{
								hand[j] = hand[j + 1];
							}
							handn --;
						}
					}
					attack = g_card[number].attack + now_character->strength;
					if(now_enemy[enemy_option]->vulnerable != 0)
					{
						attack = attack * 1.5;
					}
					if(now_character->weak != 0)
					{
						attack = attack * 0.75;
					}
					erasePreviousEnemyState(enemy_option); 
					changeState(1, enemy_option, NOW_HEALTH, attack * -1);
					showEnemyState(enemy_option);
					break;
				}
				break;
			case SPOT_WEAKNESS: 
			{
				int action;
				int total = action_type_num[number];
				for(i = 0; i < total; i ++)
				{
					action = action_type[number][i];
			
					if(action == ENEMY_ATTACK)
					{
						SetPenColor("BLUE");
						x = width / 4 - 0.5;
						y = height * 1 / 2;
						MovePen(x, y + 0.4);
						DrawArrow(40, PI / 2);
						MovePen(x - 0.4, y + 0.4);
						DrawArrow(40, PI / 2);
						MovePen(x + 0.4, y + 0.4);
						DrawArrow(40, PI / 2);
						SetPenColor("BLACK");
						erasePreviousCharacterState(); 
						changeState(0, 0, STRENGTH, g_card[number].strength);
						showCharacterState();
						break;
					}
				}		
				if(i == total) 
				{
					cancelTimer(0);
					startTimer(0, 1000);
					show_n_time = 0;
					timeflag = 1;
					SetPointSize(12);
					SetEraseMode(FALSE);
					MovePen(width / 2, height * 2 / 5 + 0.1);
					DrawTextString_Middle("The card cannot be used.");
					return ;
				}
				break;
			}
			case FEED:
				SetPenColor("RED");
				x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				if(g_card[number].upgrade == 0) attack = g_card[number].attack + now_character->strength * 3;
				else attack = g_card[number].attack + now_character->strength * 5;
				if(now_enemy[enemy_option]->vulnerable != 0)
				{
					attack = attack * 1.5;
				}
				if(now_character->weak != 0)
				{
					attack = attack * 0.75;
				}
				erasePreviousEnemyState(enemy_option); 
				changeState(1, enemy_option, NOW_HEALTH, attack * -1);
				showEnemyState(enemy_option);
				if(now_enemy[enemy_option]->now_health <= 0) 
				{
					SetPenColor("BLUE");
					x = width / 4 - 0.5;
					y = height * 1 / 2;
					MovePen(x, y + 0.4);
					DrawArrow(40, PI / 2);
					MovePen(x - 0.4, y + 0.4);
					DrawArrow(40, PI / 2);
					MovePen(x + 0.4, y + 0.4);
					DrawArrow(40, PI / 2);
					SetPenColor("BLACK");
					erasePreviousCharacterState(); 
					if(g_card[number].upgrade == 0) changeState(0, 0, MAX_HEALTH, 3);
					else changeState(0, 0, MAX_HEALTH, 4);
					showCharacterState();
				}
				break;
			case FIEND_FIRE:
				for(i = 0; i < handn; i ++)
				{
					g_card[hand[i]].card_state = CONSUMED;
				}
				SetPenColor("RED");
				x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				attack = (g_card[number].attack + now_character->strength) * handn;
				if(now_enemy[enemy_option]->vulnerable != 0)
				{
					attack = attack * 1.5;
				}
				if(now_character->weak != 0)
				{
					attack = attack * 0.75;
				}
				erasePreviousEnemyState(enemy_option); 
				changeState(1, enemy_option, NOW_HEALTH, attack * -1);
				showEnemyState(enemy_option);
				SetEraseMode(TRUE);
				DrawCard();
				consumedn += handn;
				handn = 0;
				return ;
				break; 
			case LIMIT_BREAK:
				SetPenColor("BLUE");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x - 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x + 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				SetPenColor("BLACK");
				erasePreviousCharacterState(); 
				changeState(0, 0, STRENGTH, now_character->strength);
				showCharacterState();
				break; 
			case OFFERING:
				SetPenColor("BLUE");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x - 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x + 0.4, y + 0.4);
				DrawArrow(40, PI / 2);

				SetPenColor("RED");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				erasePreviousCharacterState(); 
				changeState(0, 0, NOW_HEALTH, -6);
				showCharacterState();
				if(g_card[number].upgrade == 0) getRandomCard(3);
				else getRandomCard(5);
				now_energy += 2;
				SetEraseMode(TRUE);
				DrawCard();
				SetEraseMode(FALSE);
				break;
			case REAPER:
				SetPenColor("RED");
				x =  width * 0.45;
				y = height * 1 / 2 - 0.1;
				MovePen(x, y);
				DrawLine(width / 2, 0);

				SetPenColor("BLUE");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x - 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x + 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				SetPenColor("BLACK");
				int attack = g_card[number].attack + now_character->strength;
				if(now_enemy[enemy_option]->vulnerable != 0)
				{
					attack = attack * 1.5;
				}
				if(now_character->weak != 0)
				{
					attack = attack * 0.75;
				}
				erasePreviousEnemyState(enemy_option); 
				for(i = 0; i < now_enemy_n; i ++)
				{
					changeState(1, i, NOW_HEALTH, attack * -1);
				}
				showEnemyState(enemy_option);
				erasePreviousCharacterState(); 
				changeState(0, 0, NOW_HEALTH, now_enemy_n * attack);
				showCharacterState();
			case BANE:
				SetPenColor("RED");
				x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				attack = g_card[number].attack + now_character->strength;
				if(now_enemy[enemy_option]->poison != 0) attack *= 2;
				if(now_enemy[enemy_option]->vulnerable != 0)
				{
					attack = attack * 1.5;
				}
				if(now_character->weak != 0)
				{
					attack = attack * 0.75;
				}
				erasePreviousEnemyState(enemy_option); 
				changeState(1, enemy_option, NOW_HEALTH, attack * -1);
				showEnemyState(enemy_option);
				break;
			case POISON_EXTRACT:
				SetPenColor("GREEN");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				Line(x, x + 0.3, y + 0.4, y + 0.2);
				Line(x + 0.3, x, y + 0.2, y - 0.4);
				Line(x, x - 0.3, y + 0.4, y + 0.2);
				Line(x - 0.3, x, y + 0.2, y - 0.4);
				SetPenColor("BLACK");
				erasePreviousCharacterState(); 
				changeState(0, 0, BLOCK, now_enemy[enemy_option]->poison);
				showCharacterState();
				break; 
			case CALCULATED_GAMBLE:
				{
					int handnn = handn - 1;
					SetEraseMode(TRUE);
					DrawCard();
					SetEraseMode(FALSE);
					for(i = 0; i < handn; i ++)
					{
						if(hand[i] != number) g_card[hand[i]].card_state = DISCARD;
					}
					hand[0] = number;
					handn = 1;
					card_option = 0;
					DrawCard();
					getRandomCard(handnn - 1);
				}
				break;
			case CATALYST:
				SetPenColor("Violet");
				x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
				y = height * 1 / 2;
				y = y + 0.4;
				MovePen(x, y - 0.4);
				DrawArrow(40, PI / -2);
				MovePen(x - 0.4, y - 0.4);
				DrawArrow(40, PI / -2);
				MovePen(x + 0.4, y - 0.4);
				DrawArrow(40, PI / -2);
				SetPenColor("BLACK");
				erasePreviousEnemyState(enemy_option); 
				if(g_card[number].upgrade == 0) changeState(1, enemy_option, POISON, now_enemy[enemy_option]->poison);
				else changeState(1, enemy_option, POISON, now_enemy[enemy_option]->poison * 2);
				showEnemyState(enemy_option);
				break;
			case CONCENTRATE:
				SetPenColor("BLUE");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x - 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x + 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				SetPenColor("BLACK");
				SetEraseMode(TRUE);
				DrawCard();
				SetEraseMode(FALSE);
				
				if(g_card[number].upgrade == 0) discardCard(3);
				else discardCard(2);
				now_energy += 2;
				break;
			case ADRENALINE:
				SetPenColor("BLUE");
				x = width / 4 - 0.5;
				y = height * 1 / 2;
				MovePen(x, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x - 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				MovePen(x + 0.4, y + 0.4);
				DrawArrow(40, PI / 2);
				SetPenColor("BLACK");
				SetEraseMode(TRUE);
				DrawCard();
				SetEraseMode(FALSE);
				if(g_card[number].upgrade == 0) now_energy += 1;
				else now_energy += 2;
				getRandomCard(2);
				break;
			case CORPSE_EXPLOSION:
				SetPenColor("RED");
				x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				attack = g_card[number].attack + now_character->strength;
				if(now_enemy[enemy_option]->vulnerable != 0)
				{
					attack = attack * 1.5;
				}
				if(now_character->weak != 0)
				{
					attack = attack * 0.75;
				}
				erasePreviousEnemyState(enemy_option); 
				changeState(1, enemy_option, NOW_HEALTH, attack * -1);
				showEnemyState(enemy_option);
				if(now_enemy[enemy_option]->now_health <= 0) 
				{
					for(i = 0; i < now_enemy_n; i ++)
					{
						if(i == enemy_option) continue;
						SetPenColor("RED");
						x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
						y = height * 1 / 2;
						MovePen(x - 0.5, y + 0.5);
						DrawLine(1, -1);
						MovePen(x - 0.5, y - 0.5);
						DrawLine(1, 1);
						SetPenColor("BLACK");
						changeState(1, i, NOW_HEALTH, -1 * now_enemy[enemy_option]->max_health);
					}
				}
				break; 
			case GLASS_KNIFE:
				SetPenColor("RED");
				x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
				y = height * 1 / 2;
				MovePen(x - 0.5, y + 0.5);
				DrawLine(1, -1);
				MovePen(x - 0.5, y - 0.5);
				DrawLine(1, 1);
				SetPenColor("BLACK");
				attack = g_card[number].attack + now_character->strength;
				if(now_enemy[enemy_option]->vulnerable != 0)
				{
					attack = attack * 1.5;
				}
				if(now_character->weak != 0)
				{
					attack = attack * 0.75;
				}
				erasePreviousEnemyState(enemy_option); 
				changeState(1, enemy_option, NOW_HEALTH, attack * -1);
				showEnemyState(enemy_option);
				g_card[number].attack -= 4;
				break;
			case GRAND_FINALE: 
				{
					if(drawn == 0) 
					{
						SetPenColor("RED");
						x =  width * 0.45;
						y = height * 1 / 2 - 0.1;
						MovePen(x, y);
						DrawLine(width / 2, 0);
						SetPenColor("BLACK");

						int attack = g_card[number].attack + now_character->strength;
						if(now_enemy[enemy_option]->vulnerable != 0)
						{
							attack = attack * 1.5;
						}
						if(now_character->weak != 0)
						{
							attack = attack * 0.75;
						}
						erasePreviousEnemyState(enemy_option); 
						for(i = 0; i < now_enemy_n; i ++)
						{
							changeState(1, i, NOW_HEALTH, attack * -1);
						}
						showEnemyState(enemy_option);
					}else
					{
						cancelTimer(0);
						startTimer(0, 1000);
						show_n_time = 0;
						timeflag = 1;
						SetPointSize(12);
						SetEraseMode(FALSE);
						MovePen(width / 2, height * 2 / 5 + 0.1);
						DrawTextString_Middle("The card cannot be used.");
						return ;
					}
				}
				break;
			default:
				//if(g_card[number].type == ATTACK)
				{
					if(g_card[number].draw != 0)
					{
						SetEraseMode(TRUE);
						DrawCard();
						if(g_card[number].draw > 0) getRandomCard(g_card[number].draw);
					}
					if(g_card[number].discard != 0)
					{
						if(g_card[number].discard > 0)
						{
							flag_discard = g_card[number].discard;
							SetEraseMode(FALSE);
							discardCard(flag_discard);
						}
						if(g_card[number].discard < 0)
						{
							flag_discard = handn;
							SetEraseMode(FALSE);
							discardCard(flag_discard);
						}
					}
					if(g_card[number].consume != 0)
					{
						if(g_card[number].consume > 0)
						{
							flag_consume = g_card[number].consume;
							SetEraseMode(FALSE);
							consumeCard(flag_consume);
						} 
						if(g_card[number].consume < 0)
						{
							flag_consume = handn;
							SetEraseMode(FALSE);
							consumeCard(flag_consume);
						} 
					}
					if(g_card[number].confirm == CONFIRM)
					{
						
						if(g_card[number].attack != 0)
						{
							SetPenColor("RED");
							x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
							y = height * 1 / 2;
							MovePen(x - 0.5, y + 0.5);
							DrawLine(1, -1);
							MovePen(x - 0.5, y - 0.5);
							DrawLine(1, 1);
							SetPenColor("BLACK");
						//	if(timeflag == 0)
							{
								int attack = g_card[number].attack + now_character->strength;
								if(now_enemy[enemy_option]->vulnerable != 0)
								{
									attack = attack * 1.5;
								}
								if(now_character->weak != 0)
								{
									attack = attack * 0.75;
								}
								erasePreviousEnemyState(enemy_option); 
								changeState(1, enemy_option, NOW_HEALTH, attack * -1);
								showEnemyState(enemy_option);
							}
						}
						if(g_card[number].block != 0)
						{
							SetPenColor("GREEN");
							x = width / 4 - 0.5;
							y = height * 1 / 2;
							Line(x, x + 0.3, y + 0.4, y + 0.2);
							Line(x + 0.3, x, y + 0.2, y - 0.4);
							Line(x, x - 0.3, y + 0.4, y + 0.2);
							Line(x - 0.3, x, y + 0.2, y - 0.4);
							SetPenColor("BLACK");
						//	if(timeflag == 0)
							{
								int block = g_card[number].block;
								if(now_character->frail != 0)
								{
									block = block * 0.75;
								}
								erasePreviousCharacterState(); 
								changeState(0, 0, BLOCK, block);
								showCharacterState(); 
							}
						}
						if(g_card[number].strength != 0)
						{
							if(g_card[number].strength > 0)
							{
								SetPenColor("BLUE");
								x = width / 4 - 0.5;
								y = height * 1 / 2;
								MovePen(x, y + 0.4);
								DrawArrow(40, PI / 2);
								MovePen(x - 0.4, y + 0.4);
								DrawArrow(40, PI / 2);
								MovePen(x + 0.4, y + 0.4);
								DrawArrow(40, PI / 2);
								SetPenColor("BLACK");
							//	if(timeflag == 0)
								{
									erasePreviousCharacterState(); 
									changeState(0, 0, STRENGTH, g_card[number].strength);
									showCharacterState(); 
								}
							}
							if(g_card[number].strength < 0) 
							{
								SetPenColor("Violet");
								x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
								y = height * 1 / 2;
								y = y + 0.4;
								MovePen(x, y - 0.4);
								DrawArrow(40, PI / -2);
								MovePen(x - 0.4, y - 0.4);
								DrawArrow(40, PI / -2);
								MovePen(x + 0.4, y - 0.4);
								DrawArrow(40, PI / -2);
								SetPenColor("BLACK");
							//	if(timeflag == 0)
								{
									erasePreviousEnemyState(enemy_option); 
									changeState(1, enemy_option, STRENGTH, g_card[number].strength);
									showEnemyState(enemy_option);
								}
							}
							
						}
						if(g_card[number].poison != 0)
						{
							SetPenColor("Violet");
							x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
							y = height * 1 / 2;
							y = y + 0.4;
							MovePen(x, y - 0.4);
							DrawArrow(40, PI / -2);
							MovePen(x - 0.4, y - 0.4);
							DrawArrow(40, PI / -2);
							MovePen(x + 0.4, y - 0.4);
							DrawArrow(40, PI / -2);
							SetPenColor("BLACK");
						//	if(timeflag == 0)
							{
								erasePreviousEnemyState(enemy_option); 
								changeState(1, enemy_option, POISON, g_card[number].poison);
								showEnemyState(enemy_option);
							}
						}
						if(g_card[number].vulnerable != 0)
						{
							SetPenColor("Violet");
							x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
							y = height * 1 / 2;
							y = y + 0.4;
							MovePen(x, y - 0.4);
							DrawArrow(40, PI / -2);
							MovePen(x - 0.4, y - 0.4);
							DrawArrow(40, PI / -2);
							MovePen(x + 0.4, y - 0.4);
							DrawArrow(40, PI / -2);
							SetPenColor("BLACK");
						//	if(timeflag == 0)
							{
								erasePreviousEnemyState(enemy_option); 
								changeState(1, enemy_option, VULNERABLE, g_card[number].vulnerable);
								showEnemyState(enemy_option);
							}
						}
						if(g_card[number].weak != 0)
						{
							SetPenColor("Violet");
							x = width * (enemy_option + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
							y = height * 1 / 2;
							y = y + 0.4;
							MovePen(x, y - 0.4);
							DrawArrow(40, PI / -2);
							MovePen(x - 0.4, y - 0.4);
							DrawArrow(40, PI / -2);
							MovePen(x + 0.4, y - 0.4);
							DrawArrow(40, PI / -2);
							SetPenColor("BLACK");
						//	if(timeflag == 0)
							{
								erasePreviousEnemyState(enemy_option); 
								changeState(1, enemy_option, WEAK, g_card[number].weak);
								showEnemyState(enemy_option);
							}
						}
					}else if(g_card[number].confirm == NOT_CONFIRM)
					{
						if(g_card[number].attack != 0)
						{
							SetPenColor("RED");
							x =  width * 0.45;
							y = height * 1 / 2 - 0.1;
							MovePen(x, y);
							DrawLine(width / 2, 0);
							SetPenColor("BLACK");

							int attack = g_card[number].attack + now_character->strength;
							if(now_enemy[enemy_option]->vulnerable != 0)
							{
								attack = attack * 1.5;
							}
							if(now_character->weak != 0)
							{
								attack = attack * 0.75;
							}
							erasePreviousEnemyState(enemy_option); 
							for(i = 0; i < now_enemy_n; i ++)
							{
								changeState(1, i, NOW_HEALTH, attack * -1);
							}
							showEnemyState(enemy_option);
							
						}
						if(g_card[number].strength != 0)
						{
							if(g_card[number].strength < 0) 
							{
								SetPenColor("BLUE");
								x = width / 4 - 0.5;
								y = height * 1 / 2;
								MovePen(x, y + 0.4);
								DrawArrow(40, PI / 2);
								MovePen(x - 0.4, y + 0.4);
								DrawArrow(40, PI / 2);
								MovePen(x + 0.4, y + 0.4);
								DrawArrow(40, PI / 2);
								SetPenColor("BLACK");
								for(i = 0; i < now_enemy_n; i ++)
								{
									SetPenColor("Violet");
									x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
									y = height * 1 / 2;
									y = y + 0.4;
									MovePen(x, y - 0.4);
									DrawArrow(40, PI / -2);
									MovePen(x - 0.4, y - 0.4);
									DrawArrow(40, PI / -2);
									MovePen(x + 0.4, y - 0.4);
									DrawArrow(40, PI / -2);
									SetPenColor("BLACK");
								}
								//if(timeflag == 0)
								{
									erasePreviousEnemyState(enemy_option); 
									for(i = 0; i < now_enemy_n; i ++)
									{
										changeState(1, i, STRENGTH, g_card[number].strength);
									}
									showEnemyState(enemy_option);
								}
							}
						}
						if(g_card[number].poison != 0)
						{
							for(i = 0; i < now_enemy_n; i ++)
							{
								SetPenColor("Violet");
								x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
								y = height * 1 / 2;
								y = y + 0.4;
								MovePen(x, y - 0.4);
								DrawArrow(40, PI / -2);
								MovePen(x - 0.4, y - 0.4);
								DrawArrow(40, PI / -2);
								MovePen(x + 0.4, y - 0.4);
								DrawArrow(40, PI / -2);
								SetPenColor("BLACK");
							}
						//	if(timeflag == 0)
							{
								erasePreviousEnemyState(enemy_option); 
								for(i = 0; i < now_enemy_n; i ++)
								{
									changeState(1, i, POISON, g_card[number].poison);
								}
								showEnemyState(enemy_option);
							}
						}
						if(g_card[number].vulnerable != 0)
						{
							for(i = 0; i < now_enemy_n; i ++)
							{
								SetPenColor("Violet");
								x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
								y = height * 1 / 2;
								y = y + 0.4;
								MovePen(x, y - 0.4);
								DrawArrow(40, PI / -2);
								MovePen(x - 0.4, y - 0.4);
								DrawArrow(40, PI / -2);
								MovePen(x + 0.4, y - 0.4);
								DrawArrow(40, PI / -2);
								SetPenColor("BLACK");
							}
						//	if(timeflag == 0)
							{
								erasePreviousEnemyState(enemy_option); 
								for(i = 0; i < now_enemy_n; i ++)
								{
									changeState(1, i, VULNERABLE, g_card[number].vulnerable);
								}
								showEnemyState(enemy_option);
							}
						}
						if(g_card[number].weak != 0)
						{
							for(i = 0; i < now_enemy_n; i ++)
							{
								SetPenColor("Violet");
								x = width * (i + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
								y = height * 1 / 2;
								y = y + 0.4;
								MovePen(x, y - 0.4);
								DrawArrow(40, PI / -2);
								MovePen(x - 0.4, y - 0.4);
								DrawArrow(40, PI / -2);
								MovePen(x + 0.4, y - 0.4);
								DrawArrow(40, PI / -2);
								SetPenColor("BLACK");
							}
						//	if(timeflag == 0)
							{
								erasePreviousEnemyState(enemy_option); 
								for(i = 0; i < now_enemy_n; i ++)
								{
									changeState(1, i, WEAK, g_card[number].weak);
								}
								showEnemyState(enemy_option);
							}
						}
					}
				}
				break;
		}

		SetEraseMode(TRUE);
		DrawCard();
		
		if(g_card[number].usage == 1)
		{
			g_card[number].card_state = DISCARD; 
			discardn ++;
		}
		else if(g_card[number].usage == -1) 
		{
			g_card[number].card_state = CONSUMED;
			consumedn ++;
		}
		now_energy -= g_card[number].energy_cost;
		
		for(i = card_option; i < handn - 1; i ++)
		{
			hand[i] = hand[i + 1];
		}
		handn --;
		
	}
}
static void DrawBattleRound(int battle_round)
{
	char s[20] = "Round ";
	MovePen(width / 2, height * 4 / 5);
	integerToString(battle_round);
	SetPointSize(24);
	strcat(s, trans);
	DrawTextString_Middle(s);
} 

void integerToString(int number)
{
	int x;
	int i;
	int t = 0;
	char ch;
	if(number == 0)
	{
		trans[t] = '0';
		t ++;
	}
	while(number != 0)
	{
		x = number % 10;
		trans[t] = x + '0';
		number = number / 10;
		t ++;
	}
	for(i = 0; i < t / 2; i ++)
	{
		ch = trans[i];
		trans[i] = trans[t - 1 - i];
		trans[t - 1 - i] = ch;
	}
	trans[t] = '\0';
}


void DrawCharacter(int x, int y)
{
	double r = 0.2;
	MovePen(x, y);
	DrawCircle(r);
	MovePen(x - r * cos(PI * 75/ 180), y - r * sin(PI * 75 / 180));
	DrawLine(r * cos(PI * 75 / 180) - height / 5 / tan(PI * 75 / 180), r * sin(PI * 75 / 180) - height / 5);
	DrawLine(height / 5 / tan(PI * 75 / 180) * 2, 0);
	MovePen(x + r * cos(PI * 75 / 180), y - r * sin(PI * 75 / 180));
	DrawLine(height / 5 / tan(PI * 75 / 180) - r * cos(PI * 75 / 180), r * sin(PI * 75 / 180) - height / 5);
	if(state_character == IRONCLAD)
	{
		MovePen(x + height / 5 / tan(PI * 70 / 180) / 2 , y - height / 10);
		DrawLine(1 * cos(0.25 * PI), 1 * sin(0.25 * PI));
		MovePen(x + height / 5 / tan(PI * 70 / 180) / 2 + cos(0.25 * PI) / 3, y - height / 10 + sin(0.25 * PI) / 3);
		DrawLine(0.2 * cos(0.75 * PI), 0.2 * sin(0.75 * PI));
		MovePen(x + height / 5 / tan(PI * 70 / 180) / 2 + cos(0.25 * PI) / 3, y - height / 10 + sin(0.25 * PI) / 3); 
		DrawLine(-0.2 * cos(0.75 * PI), -0.2 * sin(0.75 * PI));
	} 
	if(state_character == SILENTER)
	{
		MovePen(x + height / 5 / tan(PI * 70 / 180) / 2 , y - height / 10);
		DrawLine(1 * cos(0.25 * PI), 1 * sin(0.25 * PI));
		MovePen(x + height / 5 / tan(PI * 70 / 180) / 2 + cos(0.25 * PI) / 5 + 0.3 * cos(PI / 4), y - height / 10 + sin(0.25 * PI) / 5 - 0.3 * cos(PI / 4));
		DrawArc(0.3, 0.3, -45, 180);
		DrawLine(0.6 * cos(0.25 * PI), -0.6 * sin(0.25 * PI));
	}

}
static void DrawEnemy(int number)
{
	double size;
	double x, y;
	int i;
	int enemy;
	for(i = 0; i < number; i ++)
	{
		enemy = now_enemy[i]->id;
		x = width * (i + 1) / (number + 1) / 2.3 + width * 0.45;
		y = height * 2 / 5;
		SetEraseMode(FALSE);
		if(now_enemy[i]->now_health <= 0) SetEraseMode(TRUE);
		if(enemy == LITTLE_SLIM || enemy == HARD_SLIM || enemy == BOSS_SLIM)
		{
			if(enemy == LITTLE_SLIM) size = 0.4;
			else if(enemy == HARD_SLIM) size = 0.7;
			else size = 1.5;
			MovePen(x + size, y);
			DrawArc(size, size, 0, 180);
			MovePen(x - size, y);
			DrawArc(size / sin(PI * 15 / 180), size / sin(PI * 15 / 180), -105, 30);
		}
		if(enemy == LOUSE)
		{
			size = 0.3;
			MovePen(x - size, y);
			DrawArc(size, size, 180, -90);
			DrawArc(size * 2, size, 90, -90);
			Line(x - size, x + 2 * size, y, y);
			MovePen(x - size * 2 / 5, y + size / 3);
			DrawArc(0.02, 0.02, 0, 360);
		}
		if(enemy == CULTIST)
		{
			size = 0.2;
			MovePen(x, height * 3 / 5);
			DrawCircle(size);
			MovePen(x - size * cos(PI * 75/ 180), height * 3 / 5 - size * sin(PI * 75 / 180));
			DrawLine(size * cos(PI * 75 / 180) - height / 5 / tan(PI * 75 / 180), size * sin(PI * 75 / 180) - height / 5);
			DrawLine(height / 5 / tan(PI * 75 / 180) * 2, 0);
			MovePen(x + size * cos(PI * 75 / 180), height * 3 / 5 - size * sin(PI * 75 / 180));
			DrawLine(height / 5 / tan(PI * 75 / 180) - size * cos(PI * 75 / 180), size * sin(PI * 75 / 180) - height / 5);
		}
		if(enemy == GREMLIN_NOB)
		{
			MovePen(x - 0.4, y);
			AlphaLine(1.3, PI / 2);
			DrawArc(0.8, 0.3, 180, -180);
			AlphaLine(1.3, - PI / 2);
			MovePen(x - 0.2, y + 0.3);
			AlphaLine(1.2, 0);
			MovePen(x - 0.2, y + 0.7);
			AlphaLine(1.2, 0);
			MovePen(x - 0.2, y + 1.1);
			AlphaLine(1.2, 0);
			MovePen(x + 0.4, y + 0.2);
			AlphaLine(1, PI / 2);
			MovePen(x + 0.2, y + 1.6);
			AlphaLine(0.2, PI / 2);
			MovePen(x + 0.6, y + 1.6);
			AlphaLine(0.2, PI / 2);
			DrawArc(0.15, 0.15, -90, 90);
			AlphaLine(0.15, PI / 2);
			DrawArc(0.15, 0.15, 0, 90);
			AlphaLine(0.4, - PI );
			DrawArc(0.15, 0.15, 90, 90);
			AlphaLine(0.2, - PI / 2);
			DrawArc(0.15, 0.15, 180, 90);
			MovePen(x + 0.6, y + 2);
			DrawCircle(0.1);
			MovePen(x + 0.23, y + 2);
			DrawCircle(0.1);
			MovePen(x + 0.55, y + 1.8);
			DrawArc(0.15, 0.15, -30, -120);
			DrawArc(0.15, 0.05, -150, 120);
		}
		if(enemy == SENTRY)
		{
			size = 0.15;
			MovePen(x, height * 2.5 / 5);
			DrawCircle(size);
			Line(x, x - 0.4, y, height * 2.5 / 5);
			Line(x - 0.4, x, height * 2.5 / 5, height * 3 / 5);
			Line(x, x + 0.4, height * 3 / 5, height * 2.5 / 5);
			Line(x + 0.4, x, height * 2.5 / 5, y);
		}
		
		if(enemy == LAGAVULIN)
		{
			MovePen(x + 0.4, height * 2.1 / 5);
			DrawArc(0.6, 0.4, 0, 360);
			MovePen(x - 0.4, height * 2.5 / 5);
			DrawCircle(0.13);
			MovePen(x + 0.06, height * 2.5 / 5);
			AlphaLine(0.17, PI / 4);
	        MovePen(x + 0.06, height * 2.5 / 5);
	        AlphaLine(0.17, PI / 4 * 3);
	        MovePen(x + 0.06, height * 2.5 / 5);
	        AlphaLine(0.17, PI / 4 * 5);
	        MovePen(x + 0.06, height * 2.5 / 5);
	        AlphaLine(0.17, PI / 4 * 7);
	        MovePen(x + 0.8, height * 2.1 / 5);
			DrawArc(1, 0.6, 0, -180);
			DrawArc(3, 1.8, 180, -58);
			MovePen(x + 0.8, height * 2.1 / 5);
			DrawArc(3, 2.5, 0, 38);
			
		}
		if(enemy == TIME_EATER)
		{
			MovePen(x + 0.45, y + 0.4);
			DrawCircle(1.2);
			MovePen(x + 0.45, y + 0.4);
			DrawArrow(90, PI / 2);/*12*/
			MovePen(x + 0.45, y + 0.4);
			DrawArrow(90, PI / 3);/*1*/
			MovePen(x + 0.45, y + 0.4);
			DrawArrow(90, PI / 6);/*2*/
			MovePen(x + 0.45, y + 0.4);
			DrawArrow(90, 0.06);/*3*/
			MovePen(x + 0.45, y + 0.4);
			DrawArrow(90, -PI / 2);/*6*/
			MovePen(x + 0.45, y + 0.4);
			DrawArrow(90, -PI / 3);/*5*/
			MovePen(x + 0.45, y + 0.4);
			DrawArrow(90, -PI / 6);/*4*/
			MovePen(x + 0.45, y + 0.4);
			DrawArrow(90, -PI / 6 * 4);/*7*/
			MovePen(x + 0.45, y + 0.4);
			DrawArrow(90, -PI / 6 * 5);/*8*/
			MovePen(x + 0.45, y + 0.4);
			DrawArrow(90, -PI );/*9*/
			MovePen(x + 0.45, y + 0.4);
			DrawArrow(90, PI / 6 * 4);/*11*/
			MovePen(x + 0.45, y + 0.4);
			DrawArrow(90, PI / 6 * 5);/*10*/
			SetPointSize(20);
			MovePen(x + 0.45, y + 1.36);
			DrawTextString_Middle("12");
			MovePen(x + 0.9, y + 1.24);
			DrawTextString_Middle("1");
			MovePen(x + 1.25, y + 0.88);
			DrawTextString_Middle("2");
			MovePen(x + 1.5, y + 0.4);
			DrawTextString_Middle("3");
			MovePen(x + 1.3, y - 0.2);
			DrawTextString_Middle("4");
			MovePen(x + 0.9, y - 0.55);
			DrawTextString_Middle("5");
			MovePen(x + 0.45, y - 0.67);
			DrawTextString_Middle("6");
			MovePen(x, y + 1.24);
			DrawTextString_Middle("11");
			MovePen(x - 0.35, y + 0.88);
			DrawTextString_Middle("10");
			MovePen(x - 0.6, y + 0.4);
			DrawTextString_Middle("9");
			MovePen(x - 0.38, y - 0.18);
			DrawTextString_Middle("4");
			MovePen(x, y - 0.55);
			DrawTextString_Middle("5");
			
			
		}
		if(enemy == THE_MAW)
		{
			MovePen(x - 0.6, y + 0.8);
			DrawArc(0.7, 0.5, 110, -220);
			AlphaLine(0.3, 1.0 / 3 * PI);
			AlphaLine(0.3, - 1.0 / 3 * PI);
			MovePen(x - 0.6, y + 0.8);
			AlphaLine(0.3, - 1.0 / 3 * PI);
			AlphaLine(0.3, 1.0 / 3 * PI);
			MovePen(x - 0.6, y + 0.8);
			DrawArc(0.7, 0.5, 110, -45);
			AlphaLine(0.3, - 1.6 / 3 * PI);
			AlphaLine(0.32, 0.3 / 3 * PI);
			MovePen(x - 0.6, y + 0.8);
			DrawArc(0.7, 0.5, 110, -220);
			DrawArc(0.7, 0.5, -110, 45);
			AlphaLine(0.3, 1.6 / 3 * PI);
			AlphaLine(0.32, - 0.3 / 3 * PI);
            MovePen(x - 0.6, y + 0.8);
            DrawArc(1.5, 1.3, 160, -320);
		}
		if(enemy == HEXAGHOST)
		{
			size = 0.2;
			MovePen(x + 0.3, y + 0.5);
			AlphaLine(0.4, 1.0 / 6 * PI);
			AlphaLine(0.4, 3.0 / 6 * PI);
			AlphaLine(0.4, 5.0 / 6 * PI);
			AlphaLine(0.4, 7.0 / 6 * PI);
			AlphaLine(0.4, 9.0 / 6 * PI);
			AlphaLine(0.4, 11.0 / 6 * PI);
			MovePen(x + 0.3, y + 0.9);
			DrawCircle(1.2);
			MovePen(x + 1.15, y + 0.9);
			DrawArc(0.85, 0.85, 0, 60);
			MovePen(x + 0.3 - 0.85 / 2, y + 0.9 + 0.85 * sin(PI / 3));
			DrawArc(0.85, 0.85, 120, 60);
			MovePen(x + 0.3 - 0.85 / 2, y + 0.9 - 0.85 * sin(PI / 3));
			DrawArc(0.85, 0.85, 240, 60);
		}
		SetEraseMode(FALSE);
	}

	
}
static void enemyActing(int number)
{
	char s[100] = "";
	int i;
	int action;
	int value;
	int total = action_type_num[number];
	double x, y;
	
	for(i = 0; i < total; i ++)
	{
		action = action_type[number][i];
		value = action_value[number][i];

		if(action == ENEMY_ATTACK)
		{
			SetPenColor("RED");
			x = width / 4 - 0.5;
			y = height * 1 / 2;
			MovePen(x - 0.5, y + 0.5);
			DrawLine(1, -1);
			MovePen(x - 0.5, y - 0.5);
			DrawLine(1, 1);
			SetPenColor("BLACK");
			int attack = value;
				
			if(now_character->vulnerable != 0)
			{
				attack = attack * 1.5;
			}
			if(now_enemy[number]->weak != 0)
			{
				attack = attack * 0.75;
			}
			if(timeflag == 0)
			{
				
				if(attack <= now_character->block)
				{
					erasePreviousCharacterState();
					changeState(0, 0, BLOCK, -1 * attack);
					showCharacterState();
				}
				else 
				{
					erasePreviousCharacterState();
					changeState(0, 0, NOW_HEALTH, now_character->block - attack);
					changeState(0, 0, BLOCK, -1 * now_character->block);
					showCharacterState();
				}
			}
		}else if(action == ENEMY_BLOCK)
		{
			SetPenColor("GREEN");
			x = width * (number + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
			y = height * 1 / 2;
			Line(x, x + 0.3, y + 0.4, y + 0.2);
			Line(x + 0.3, x, y + 0.2, y - 0.4);
			Line(x, x - 0.3, y + 0.4, y + 0.2);
			Line(x - 0.3, x, y + 0.2, y - 0.4);
			SetPenColor("BLACK");
			if(timeflag == 0)
			{
				erasePreviousEnemyState(number);
				changeState(1, number, BLOCK, value);
				showEnemyState(number);
				
			}
		}
		else if(action == ENEMY_STRENGTH && value < 0 || 
				action == ENEMY_VULNERABLE || action == ENEMY_WEAK || action == ENEMY_FRAIL)
		{
			SetPenColor("Violet");
			x = width / 4 - 0.5;
			y = height * 1 / 2;
			y = y + 0.4;
			MovePen(x, y - 0.4);
			DrawArrow(40, PI / -2);
			MovePen(x - 0.4, y - 0.4);
			DrawArrow(40, PI / -2);
			MovePen(x + 0.4, y - 0.4);
			DrawArrow(40, PI / -2);
			SetPenColor("BLACK");
			if(timeflag == 0)
			{
				if(action == ENEMY_STRENGTH)
				{
					erasePreviousCharacterState();
					changeState(0, 0, STRENGTH, value);
					showCharacterState();
				}
				else if(action == ENEMY_VULNERABLE)
				{
					erasePreviousCharacterState();
					changeState(0, 0, VULNERABLE, value);
					showCharacterState();
				}else if(action == ENEMY_WEAK)
				{
					erasePreviousCharacterState();
					changeState(0, 0, WEAK, value);
					showCharacterState();
				}else if(action == ENEMY_FRAIL)
				{
					erasePreviousCharacterState();
					changeState(0, 0, FRAIL, value);
					showCharacterState();
				}
			}
		}
		else if(action == ENEMY_STRENGTH && value > 0 || action == ENEMY_HEAL)
		{
			SetPenColor("BLUE");
			x = width * (number + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
			y = height * 1 / 2;
			MovePen(x, y + 0.4);
			DrawArrow(40, PI / 2);
			MovePen(x - 0.4, y + 0.4);
			DrawArrow(40, PI / 2);
			MovePen(x + 0.4, y + 0.4);
			DrawArrow(40, PI / 2);
			SetPenColor("BLACK");
			if(timeflag == 0)
			{
				if(action == ENEMY_STRENGTH)
				{
					erasePreviousEnemyState(number);
					changeState(1, number, STRENGTH, value);
					showEnemyState(number);
				}else if(action == ENEMY_HEAL)
				{
					erasePreviousEnemyState(number);
					changeState(1, number, NOW_HEALTH, value);
					showEnemyState(number);
				}
			}
		}else if(action == ENEMY_UNKNOWN)
		{
			if(timeflag == 0)
			{
				
			}
		}
	}
}
static void DrawEnemyAct(double x, double y, int number)
{
	char s[100] = "";
	int i;
	int action;
	int value;
	int total = action_type_num[number];
	int g[10];
	for(i = 0; i < 10; i ++)
	{
		g[i] = 0;
	}
	for(i = 0; i < total; i ++)
	{
		action = action_type[number][i];
		value = action_value[number][i];

		if(action == ENEMY_ATTACK)
		{
			if(g[0] == 0)
			{
				int attack = value;
				Line(x - 0.1, x + 0.2, y - 0.1, y + 0.2);
				Line(x - 0.1, x + 0.1, y + 0.2, y - 0.1);
				MovePen(x + 0.25, y);
				SetPointSize(22);
				if(now_character->vulnerable != 0)
				{
					attack = attack * 1.5;
				}
				if(now_enemy[number]->weak != 0)
				{
					attack = attack * 0.75;
				}
				integerToString(attack);
				DrawTextString(trans);
			}
			g[0] ++;
		}else if(action == ENEMY_BLOCK)
		{
			if(g[1] == 0)
			{
				Line(x, x + 0.15, y + 0.2, y + 0.1);
				Line(x + 0.15, x, y + 0.1, y - 0.2);
				Line(x, x - 0.15, y + 0.2, y + 0.1);
				Line(x - 0.15, x, y + 0.1, y - 0.2);
				
			}
			g[1] ++;
		}
		else if(action == ENEMY_STRENGTH && value < 0 || 
				action == ENEMY_VULNERABLE || action == ENEMY_WEAK || action == ENEMY_FRAIL)
		{
			if(g[2] == 0)
			{
				y = y + 0.2;
				MovePen(x, y - 0.2);
				DrawArrow(20, PI / -2);
				MovePen(x - 0.2, y - 0.2);
				DrawArrow(20, PI / -2);
				MovePen(x + 0.2, y - 0.2);
				DrawArrow(20, PI / -2);
			}
			g[2] ++;
		}
		else if(action == ENEMY_STRENGTH && value > 0 || action == ENEMY_HEAL)
		{
			if(g[3] == 0)
			{
				MovePen(x, y + 0.2);
				DrawArrow(20, PI / 2);
				MovePen(x - 0.2, y + 0.2);
				DrawArrow(20, PI / 2);
				MovePen(x + 0.2, y + 0.2);
				DrawArrow(20, PI / 2);
			}
			g[3] ++;
		}else if(action == ENEMY_UNKNOWN)
		{
			if(g[action] == 0)
			{
				MovePen(x, y);
				DrawArc(0.07, 0.07, -90, 270);
				MovePen(x, y);
				DrawLine(0, -0.04);
				MovePen(x, y - 0.16);
				DrawArc(0.01, 0.01, -90, 360);
			}
			g[4] ++;
		}
	}
}
static void getRandomEnemyAct(int number)
{
	int i, j;
	int p;
	double x, y;
	int enemy;
	enemy = now_enemy[number]->id;

	x = width * (number + 1) / (now_enemy_n + 1) / 2 + width / 2;
	y = height * 2 / 5;
	if(enemy == LITTLE_SLIM)
	{
		action_type_num[number] = 1;
		p = rand() % 3;
		if(p == 0)
		{
			action_type[number][0] = ENEMY_FRAIL;
			action_value[number][0] = 1;
		}else if(p == 1)
		{
			action_type[number][0] = ENEMY_WEAK;
			action_value[number][0] = 1;
		}else
		{
			action_type[number][0] = ENEMY_ATTACK;
			action_value[number][0] = 6;
		}
	}
	if(enemy == HARD_SLIM)
	{
		action_type_num[number] = 1;
		p = rand() % 3;
		if(p == 0)
		{
			action_type[number][0] = ENEMY_FRAIL;
			action_value[number][0] = 2;
		}else if(p == 1)
		{
			action_type[number][0] = ENEMY_WEAK;
			action_value[number][0] = 2;
		}else
		{
			action_type[number][0] = ENEMY_ATTACK;
			action_value[number][0] = 18;
		}
	}
	if(enemy == BOSS_SLIM)
	{
		action_type_num[number] = 1;
		if(battle_round != 1)
		{
			action_type[number][0] = ENEMY_ATTACK;
			action_value[number][0] = 6 + 3 * (battle_round - 1);
		}else
		{
			action_type[number][0] = ENEMY_UNKNOWN;
			action_value[number][0] = 0;
		}
	}
	if(enemy == LOUSE)
	{
		action_type_num[number] = 1;
		p = rand() % 2;
		if(p == 0)
		{
			action_type[number][0] = ENEMY_ATTACK;
			action_value[number][0] = 6;
		}else if(p == 1)
		{
			action_type[number][0] = ENEMY_STRENGTH;
			action_value[number][0] = 3;
		}
	}
	if(enemy == CULTIST)
	{
		action_type_num[number] = 1;
		if(battle_round != 1)
		{
			action_type[number][0] = ENEMY_ATTACK;
			action_value[number][0] = 6 + 3 * (battle_round - 2);
		}else
		{
			action_type[number][0] = ENEMY_UNKNOWN;
			action_value[number][0] = 0;
		}
		
	}
	if(enemy == GREMLIN_NOB)
	{
		int flag = 0;
		p = rand() % 2;
		if(now_enemy[number]->now_health <= now_enemy[number]->max_health / 3) flag = 1;
		if(p == 0)
		{
			action_type_num[number] = 2;
			action_type[number][0] = ENEMY_ATTACK;
			action_value[number][0] = 9 + flag * 3;
			action_type[number][1] = ENEMY_VULNERABLE;
			action_value[number][1] = 2;
		}else if(p == 1)
		{
			action_type_num[number] = 1;
			action_type[number][0] = ENEMY_ATTACK;
			action_value[number][0] = 18 + flag * 6;
		}
	}
	if(enemy == SENTRY)
	{
		p = rand() % 2;
		if(p == 0)
		{
			action_type_num[number] = 1;
			action_type[number][0] = ENEMY_ATTACK;
			action_value[number][0] = 10;
		}else if(p == 1)
		{
			action_type_num[number] = 1;
			action_type[number][0] = ENEMY_UNKNOWN;
		}
	}
	if(enemy == NEMESIS)
	{
		p = rand() % 2;
		if(p == 0)
		{
			action_type_num[number] = 1;
			action_type[number][0] = ENEMY_ATTACK;
			action_value[number][0] = 20;
		}else if(p == 1)
		{
			action_type_num[number] = 1;
			action_type[number][0] = ENEMY_BLOCK;
			action_value[number][0] = 20;
		}
	}
	if(enemy == LAGAVULIN)
	{
		p = rand() % 2;
		if(battle_round <= 2)
		{
			action_type_num[number] = 1;
			action_type[number][0] = ENEMY_BLOCK;
			action_value[number][0] = 8; 
		}else if(battle_round == 3)
		{
			action_type_num[number] = 1;
			action_type[number][0] = ENEMY_UNKNOWN;
		}else if(p == 0)
		{
			action_type_num[number] = 2;
			action_type[number][0] = ENEMY_FRAIL;
			action_value[number][0] = 2;
			action_type[number][1] = ENEMY_ATTACK;
			action_value[number][1] = 10;
		}else
		{
			action_type_num[number] = 1;
			action_type[number][0] = ENEMY_ATTACK;
			action_value[number][0] = 20;
		}
	}
	if(enemy == TIME_EATER)
	{
		if(battle_round == 1)
		{
			action_type_num[number] = 4;
			action_type[number][0] = ENEMY_VULNERABLE;
			action_value[number][0] = 2;
			action_type[number][1] = ENEMY_FRAIL;
			action_value[number][1] = 2;
			action_type[number][2] = ENEMY_WEAK;
			action_value[number][2] = 2;
			action_type[number][3] = ENEMY_STRENGTH;
			action_value[number][3] = -2;
		}else if(now_enemy[number]->now_health  <= now_enemy[number]->max_health / 2)
		{
			action_type_num[number] = 1;
			action_type[number][0] = ENEMY_HEAL;
			action_value[number][0] = 50;
		}else 
		{
			action_type_num[number] = 1;
			action_type[number][1] = ENEMY_ATTACK;
			action_value[number][1] = 18;
		}
	}
	if(enemy == THE_MAW)
	{
		p = rand() % 3;
		if(p == 0)
		{
			action_type_num[number] = 2;
			action_type[number][0] = ENEMY_FRAIL;
			action_value[number][0] = 2;
			action_type[number][1] = ENEMY_ATTACK;
			action_value[number][1] = 10;
		}else if(p == 1)
		{
			action_type_num[number] = 2;
			action_type[number][0] = ENEMY_STRENGTH;
			action_value[number][0] = 3;
			action_type[number][1] = ENEMY_ATTACK;
			action_value[number][1] = 9;
		}else
		{
			action_type_num[number] = 1;
			action_type[number][0] = ENEMY_ATTACK;
			action_value[number][0] = 20;
		}
	}
	if(enemy == HEXAGHOST)
	{
		if((battle_round - 1) % 6 == 0)
		{
			action_type_num[number] = 2;
			action_type[number][0] = ENEMY_VULNERABLE;
			action_value[number][0] = 2;
			action_type[number][1] = ENEMY_ATTACK;
			action_value[number][1] = 6;
		}else if((battle_round - 1) % 6 == 1)
		{
			action_type_num[number] = 1;
			action_type[number][1] = ENEMY_ATTACK;
			action_value[number][1] = 9;
		}else if((battle_round - 1) % 6 == 2)
		{
			action_type_num[number] = 2;
			action_type[number][0] = ENEMY_BLOCK;
			action_value[number][0] = 6;
			action_type[number][1] = ENEMY_ATTACK;
			action_value[number][1] = 6;
		}else if((battle_round - 1) % 6 == 3)
		{
			action_type_num[number] = 2;
			action_type[number][0] = ENEMY_STRENGTH;
			action_value[number][0] = 1;
			action_type[number][1] = ENEMY_BLOCK;
			action_value[number][1] = 6;
		}else if((battle_round - 1) % 6 == 4)
		{
			action_type_num[number] = 2;
			action_type[number][0] = ENEMY_VULNERABLE;
			action_value[number][0] = 6;
			action_type[number][1] = ENEMY_ATTACK;
			action_value[number][1] = 6;
		}else if((battle_round - 1) % 6 == 5)
		{
			action_type_num[number] = 1;
			action_type[number][1] = ENEMY_ATTACK;
			action_value[number][1] = 18;
		}
	}
}
static void DrawCardType(double x, double y, int number)
{
	switch(g_card[number].type)
	{
		case ATTACK:
			Line(x, x, y + 0.2, y - 0.25);
			Line(x - 0.1, x + 0.1, y - 0.1, y - 0.1);
			break;
		case SKILL:
			Line(x - 0.2, x + 0.2, y - 0.1, y - 0.1);
			Line(x - 0.2, x - 0.2, y - 0.1, y + 0.1);
			Line(x + 0.2, x + 0.2, y - 0.1, y + 0.1);
			Line(x - 0.2, x - 0.1, y + 0.1, y);
			Line(x - 0.1, x, y, y + 0.1);
			Line(x, x + 0.1, y + 0.1, y);
			Line(x + 0.1, x + 0.2, y, y + 0.1);
			break;
		case POWER:
			Line(x - 0.07, x + 0.07, y - 0.2, y - 0.2);
			Line(x - 0.07, x - 0.07, y - 0.2, y);
			Line(x - 0.07, x - 0.14, y, y);
			Line(x - 0.14, x, y, y + 0.2);
			Line(x + 0.07, x + 0.07, y - 0.2, y);
			Line(x + 0.07, x + 0.14, y, y);
			Line(x + 0.14, x, y, y + 0.2);
			break;
		case STATUS:
			MovePen(x, y);
			DrawArc(0.07, 0.07, -90, 270);
			MovePen(x, y);
			DrawLine(0, -0.04);
			MovePen(x, y - 0.16);
			DrawArc(0.01, 0.01, -90, 360);
			break;
		case CURSE:
			MovePen(x, y);
			DrawArc(0.1, 0.1, -90, 360);
			MovePen(x - 0.05, y + 0.05);
			DrawArc(0.02, 0.02, -90, 360);
			MovePen(x + 0.05, y + 0.05);
			DrawArc(0.02, 0.02, -90, 360);
			Line(x - 0.12, x + 0.12, y, y - 0.05);
			Line(x - 0.12, x + 0.12, y - 0.05, y);
			break;
	}
}
static void DrawCard()
{
	int i, j;
	double startx = 1;
	double dx = (width - startx * 2) / 10;
	double dy = height / 5 - 0.4;
	char s[15];
	SetPointSize(16);
	j = 0;
	int flag = 0;
	for(i = 0; i < handn; i ++)
	{
		MovePen(startx + i * dx + dx * (10 - handn) / 2, 0);
		DrawRectangle(dx, dy, 0);
		DrawCardType(startx + i * dx + dx * (10 - handn) / 2 + dx / 2, dy / 2, hand[i]);
	}
	MovePen(startx / 4, 0.3);
	DrawRectangle(dx / 2, dy / 2, 0);
	MovePen(startx / 4 + dx / 4, 0.3 + dy / 4 - 0.05);
	integerToString(drawn);
	DrawTextString_Middle(trans);
	
	MovePen(width - startx / 4 - dx / 2, 0.3);
	DrawRectangle(dx / 2, dy / 2, 0);
	MovePen(width - startx / 4 - dx / 4, 0.3 + dy / 4 - 0.05);
	integerToString(discardn);
	DrawTextString_Middle(trans);
	
	MovePen(width - startx / 4 - dx / 4, 0.3 + dy / 2 + 0.5);
	DrawCircle(0.2);
	MovePen(width - startx / 4 - dx / 4, 0.3 + dy / 2 + 0.45);
	integerToString(consumedn);
	DrawTextString_Middle(trans);
	
	MovePen(startx * 3 / 4 + dx / 4, 0.3 + dy / 2 + 0.5);
	DrawCircle(0.3);
	MovePen(startx * 3 / 4 + dx / 4, 0.3 + dy / 2 + 0.45);
	integerToString(max_energy);
	strcpy(s, trans);
	strcpy(s, "/");
	integerToString(now_energy);
	strcpy(s, trans);
	DrawTextString_Middle(s);
	
	if(handn != 0)
	{
		MovePen(startx + dx * (11 - handn) / 2 + dx * card_option, dy + 0.3);
		DrawArrow(20, PI / -2);
		DrawDetailedCard(hand[card_option]);
	}

}

void DrawDetailedCard(int number)
{
	int size = GetPointSize();
	
	SetPointSize(10);
	char s1[105];
	double x, y;
	x = width / 2;
	y = height * 2 / 5 - 0.2;
	MovePen(x, y);
	DrawTextString_Middle(g_card[number].name);
	MovePen(x, y - 0.3);
	integerToString(g_card[number].energy_cost);
	strcpy(s1, "Energy cost: ");
	strcat(s1, trans);
	DrawTextString_Middle(s1);
	MovePen(x, y - 0.6);
	strcpy(s1, "");
	if(g_card[number].attack != 0)
	{
		int attack = g_card[number].attack;
		if(now_enemy[enemy_option]->vulnerable != 0)
		{
			attack = attack * 1.5;
		}
		if(now_character->weak != 0)
		{
			attack = attack * 0.75;
		}
		strcat(s1, "Cause ");
		integerToString(attack);
		strcat(s1, trans);
		strcat(s1, " attack. ");
	}
	if(g_card[number].block != 0)
	{
		int block = g_card[number].block;
		if(now_character->frail != 0)
		{
			block = block * 0.75;
		}
		strcat(s1, "Gain ");
		integerToString(block);
		strcat(s1, trans);
		strcat(s1, " block. ");
	}
	if(g_card[number].strength != 0)
	{
		if(g_card[number].strength > 0)
		{
			strcat(s1, "Gain ");
			integerToString(g_card[number].strength);
			strcat(s1, trans);
			strcat(s1, " strength. ");
		}
		if(g_card[number].strength < 0)
		{
			strcat(s1, "Cause ");
			integerToString(g_card[number].strength * (-1));
			strcat(s1, trans);
			strcat(s1, " strength lost. ");
		}
	}
	if(g_card[number].poison != 0)
	{
		strcat(s1, "Cause ");
		integerToString(g_card[number].poison);
		strcat(s1, trans);
		strcat(s1, " poison. ");
	}
	if(g_card[number].vulnerable != 0)
	{
		strcat(s1, "Cause ");
		integerToString(g_card[number].vulnerable);
		strcat(s1, trans);
		strcat(s1, " vulnerable. ");
	}
	if(g_card[number].weak != 0)
	{
		strcat(s1, "Cause ");
		integerToString(g_card[number].weak);
		strcat(s1, trans);
		strcat(s1, " weak. ");
	}
	if(g_card[number].draw != 0)
	{
		strcat(s1, "Draw ");
		integerToString(g_card[number].draw);
		strcat(s1, trans);
		strcat(s1, " card. ");
	}
	if(g_card[number].discard != 0)
	{
		strcat(s1, "Discard ");
		integerToString(g_card[number].discard);
		strcat(s1, trans);
		strcat(s1, " card. ");
	}
	if(g_card[number].consume != 0)
	{
		strcat(s1, "Consume ");
		integerToString(g_card[number].consume);
		strcat(s1, trans);
		strcat(s1, " card. ");
	}
	DrawTextString_Middle(s1);
	MovePen(x, y - 0.9);
	switch(g_card[number].id)
	{
		case ANGER:
			DrawTextString_Middle("Increase this card's Attack by 1 this battle.");
			break;
		case BODY_SLAM:
			DrawTextString_Middle("Cause Attack equal to your current Block.");
			break;
		case CLASH:
			DrawTextString_Middle("Can only be used if all Card Type are an Attack.");
			break;
		case HEAVY_BLADE: 
			DrawTextString_Middle("Add 3 times of Strength to Attack.");
			break;
		case BLOODLETTING:
			DrawTextString_Middle("Gain 2 Energy. Lose 3 Health.");
			break; // Gain 2(3) Energy
		case ENTRENCH:
			DrawTextString_Middle("Double your current Block.");
			break; 
		case HEMOKINESIS: case POWER_THROUGH:
			DrawTextString_Middle("Lose 2 Health.");
			break; 
		case RAMPAGE:
			DrawTextString_Middle("Increase this card's Attack by 5 this battle.");
			break;
		case SECOND_WIND:
			DrawTextString_Middle("Consume all non-Attack cards, gain 5 Block for each card Consumed.");
			break;
		case SEEING_RED:
			DrawTextString_Middle("Gain 2 energy.");
			break;
		case SEVER_SOUL:
			DrawTextString_Middle("Consume all non-Attack cards.");
			break;
		case SPOT_WEAKNESS: 
			DrawTextString_Middle("when the enemy intends to Attack.");
			break;
		case FEED:
			DrawTextString_Middle("If this Kills an enemy, gain 3 permanent Max Health.");
			break;
		case FIEND_FIRE:
			DrawTextString_Middle("Exhaust all cards in your hand. Each card will cause 7 Attack.");
			break; 
		case LIMIT_BREAK:
			DrawTextString_Middle("Double your current Strength.");
			break; 
		case OFFERING:
			DrawTextString_Middle("Lose 6 Health.");
			break;
		case REAPER:
			DrawTextString_Middle("Heal Health equal to Attack.");
			break;
		case BANE:
			DrawTextString_Middle("If the enemy is Poisoned, double the Attack.");
			break;
		case POISON_EXTRACT:
			DrawTextString_Middle("gain Block equal to an enemy's Poison.");
			break; 
		case CALCULATED_GAMBLE:
			DrawTextString_Middle("Discard all hand card and draw same number of cards.");
			break;
		case CATALYST:
			DrawTextString_Middle("Double an enemy's Poison.");
			break;
		case CONCENTRATE:
			DrawTextString_Middle("Gain 2 Energy.");
			break;
		case TACTICIAN:
			DrawTextString_Middle("If it is Discarded, gain 1 Energy.");
			break;
		case ADRENALINE:
			DrawTextString_Middle("Gain 1 Energy.");
			break;
		case CORPSE_EXPLOSION:
			DrawTextString_Middle("When the enemy was Killed, cause Attack equal to its max Health to ALL enemies.");
			break; 
		case GLASS_KNIFE:
			DrawTextString_Middle("Decrease this card's Attack by 4 this battle. ");
			break;
		case GRAND_FINALE: 
			DrawTextString_Middle("Can only be used if no cards in the Draw Pile.");
			break;
	}
	strcpy(s1, "");
	if(g_card[number].confirm == 0)
	{
		strcat(s1, "Object: All. ");
	}else
	{
		strcat(s1, "Object: One. ");
	}
	if(g_card[number].usage == -1)
	{
		strcat(s1, "The card can only be used once. ");
	}
	MovePen(x, y - 1.2);
	DrawTextString_Middle(s1);
	SetPointSize(size);
}
static void DrawBotton()
{
	SetPointSize(12);
	SetPenColor("Red");
	MovePen(width * 1 / 2, height * 29 / 30);
	DrawTextString("Press 'LEFT' and 'RIGHT' to move the Arrow.");
	MovePen(width * 1 / 2, height * 28 / 30);
	DrawTextString("Press 'E' to end the Character Round.");
	MovePen(width * 1 / 2, height * 27 / 30);
	DrawTextString("Press 'SPACE' to switch the focus between Card and Enemy");
    SetPenColor("Black");
    
	if(state_character == IRONCLAD) 
	{
		SetPointSize(24);
		MovePen(0.2, height * 19 / 20);
		DrawTextString("Ironclad");
		SetPointSize(12);
		MovePen(0.2, height * 17 / 20);
		DrawTextString("Relic: burning blood (At the end of combat, heal 6 HP.)");		
	}
	else if(state_character == SILENTER) 
	{
		SetPointSize(24);
		MovePen(0.2, height * 19 / 20);
		DrawTextString("Silenter");
		SetPointSize(12);
		MovePen(0.2, height * 17 / 20);
		DrawTextString("Relic: the ring of snake (At the start of each combat, draw 2 additional cards.)");
	}
	MovePen(width * 6 / 8, height / 5 + 0.5);
	DrawLine(- 0.5, - 0.2);
	DrawLine(0.5, - 0.2);
	DrawLine(0.5, 0.2);
	DrawLine(-0.5, 0.2);
	SetPointSize(16);
	MovePen(width * 6 / 8, height / 5 + 0.25);
	DrawTextString_Middle("End");
}
void chooseCard()
{
	double x, y;
	double width, height;
	int i;
	int j;
	char s1[50];
	InitGraphics();
	width = GetWindowWidth();
	height = GetWindowHeight();
	cancelKeyboardEvent();
	registerKeyboardEvent(KeyboardEventProcess_ChooseCard);
	/*
	get RILIC
	x = width / 2;
	y = height / 5;
	MovePen(x, y);
	DrawTextString_Middle("4: SKIP");
	get MONEY
	x = width / 2;
	y = height / 5;
	MovePen(x, y);
	DrawTextString_Middle("4: SKIP");
	
	*/
	x = width / 2;
	y = height * 4 / 5 + 0.5;
	MovePen(x, y);
	SetPointSize(20);
	DrawTextString_Middle("Get 25 Money.");
	changeState(0, 0, MONEY, 25); 
	
	x = width / 2;
	y = height / 5 - 1;
	MovePen(x, y);
	SetPointSize(12);
	DrawTextString_Middle("4: SKIP");
	for(i = 0; i < 3; i ++)
	{
		int p;
		double dx = width / 6, dy = height / 4;
		if(now_character->id == IRONCLAD) p = rand() % 41 + ANGER;
		else p = rand() % 32 + ACROBATICS;
		card_p[i] = p;
		x = width * (i * 2 + 1) / 6, y = height / 2;
		MovePen(x - dx + 0.3, y - dy);
		DrawLine(2 * (dx - 0.3), 0);
		DrawLine(0, 2 * dy);
		DrawLine(-2 * (dx - 0.3), 0);
		DrawLine(0, -2 * dy);
		MovePen(x, y - dy - 0.4);
		if(i == 0) DrawTextString_Middle("1");
		else if(i == 1) DrawTextString_Middle("2");
		else DrawTextString_Middle("3");
		MovePen(x, y + dy - 0.4);
		SetPointSize(20);
		DrawTextString_Middle(card[p].name);
		j = 2;
		MovePen(x, y + dy - j * 0.4);
		j ++;
		SetPointSize(12);
		integerToString(card[p].energy_cost);
		strcpy(s1, "Energy cost: ");
		strcat(s1, trans);
		DrawTextString_Middle(s1);
		
		if(card[p].attack != 0)
		{
			MovePen(x, y + dy - j * 0.4);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Cause ");
			integerToString(card[p].attack);
			strcat(s1, trans);
			strcat(s1, " Attack. ");
			DrawTextString_Middle(s1);
		}
		if(card[p].block != 0)
		{
			MovePen(x, y + dy - j * 0.4);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Gain ");
			integerToString(card[p].block);
			strcat(s1, trans);
			strcat(s1, " Block. ");
			DrawTextString_Middle(s1);
		}
		if(card[p].strength != 0)
		{
			if(card[p].strength > 0)
			{
				MovePen(x, y + dy - j * 0.4);
				j ++;
				strcpy(s1, "");
				strcat(s1, "Gain ");
				integerToString(card[p].strength);
				strcat(s1, trans);
				strcat(s1, " Strength. ");
				DrawTextString_Middle(s1);
			}
			if(card[p].strength < 0)
			{
				MovePen(x, y + dy - j * 0.4);
				j ++;
				strcpy(s1, "");
				strcat(s1, "Cause ");
				integerToString(card[p].strength * (-1));
				strcat(s1, trans);
				strcat(s1, " Strength lost. ");
				DrawTextString_Middle(s1);
			}

		}
		if(card[p].poison != 0)
		{
			MovePen(x, y + dy - j * 0.4);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Cause ");
			integerToString(card[p].poison);
			strcat(s1, trans);
			strcat(s1, " Poison. ");
			DrawTextString_Middle(s1);
		}
		if(card[p].vulnerable != 0)
		{
			MovePen(x, y + dy - j * 0.4);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Cause ");
			integerToString(card[p].vulnerable);
			strcat(s1, trans);
			strcat(s1, " Vulnerable. ");
			DrawTextString_Middle(s1);
		}
		if(card[p].weak != 0)
		{
			MovePen(x, y + dy - j * 0.4);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Cause ");
			integerToString(card[p].weak);
			strcat(s1, trans);
			strcat(s1, " Weak. ");
			DrawTextString_Middle(s1);
		}
		if(card[p].draw != 0)
		{
			MovePen(x, y + dy - j * 0.4);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Draw ");
			integerToString(card[p].draw);
			strcat(s1, trans);
			strcat(s1, " card. ");
			DrawTextString_Middle(s1);
		}
		if(card[p].discard != 0)
		{
			MovePen(x, y + dy - j * 0.4);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Discard ");
			integerToString(card[p].discard);
			strcat(s1, trans);
			strcat(s1, " card. ");
			DrawTextString_Middle(s1);
		}
		if(card[p].consume != 0)
		{
			MovePen(x, y + dy - j * 0.4);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Consume ");
			integerToString(card[p].consume);
			strcat(s1, trans);
			strcat(s1, " card. ");
			DrawTextString_Middle(s1);
		}
		switch(card[p].id)
		{
			case ANGER:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Increase this card's A-");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("-ttack by 1 this battle."); 
				break;
			case BODY_SLAM:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Cause Attack equal to");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("your current Block."); 
				break;
			case CLASH:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Can only be used if all");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Card Type are an Attack."); 
				break;
			case HEAVY_BLADE: 
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Add 3 times of Strength to Attack.");
				break;
			case BLOODLETTING:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Gain 2 Energy");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Lose 3 Health.");
				break; // Gain 2(3) Energy
			case ENTRENCH:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Double your current Block.");
				break; 
			case HEMOKINESIS: case POWER_THROUGH:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Lose 2 Health.");
				break; 
			case RAMPAGE:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Increase this card's A-");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("-ttack by 5 this battle."); 
				break;
			case SECOND_WIND:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Consume all non-Attack cards, gain");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("5 Block for each card Consumed."); 
				break;
			case SEEING_RED:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Gain 2 energy.");
				break;
			case SEVER_SOUL:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Consume all non-Attack cards.");
				break;
			case SPOT_WEAKNESS: 
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Only when the enemy intends to Attack.");
				break;
			case FEED:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("If this Kills an enemy, ");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("gain 3 permanent Max Health."); 
				break;
			case FIEND_FIRE:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Exhaust all cards in your hand.");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Each card will cause 7 Attack."); 
				break; 
			case LIMIT_BREAK:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Double your current Strength.");
				break; 
			case OFFERING:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Lose 6 Health.");
				break;
			case REAPER:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Heal Health equal to Attack.");
			case BANE:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("If the enemy is Poisoned, ");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("double the Attack.");
				break;
			case POISON_EXTRACT:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("gain Block equal to an enemy's Poison.");
				break; 
			case CALCULATED_GAMBLE:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Discard all hand card and");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("draw same number of cards.");
				break;
			case CATALYST:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Double an enemy's Poison.");
				break;
			case CONCENTRATE:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Gain 2 Energy.");
				break;
			case TACTICIAN:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("If it is Discarded, ");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("gain 1 Energy.");
				break;
			case ADRENALINE:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Gain 1 Energy.");
				break;
			case CORPSE_EXPLOSION:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("When the enemy was Killed, ");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("cause Attack equal to its");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("max Health to ALL enemies.");
				break; 
			case GLASS_KNIFE:
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Decrease this card's A- ");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("-ttack by 4 this battle.");
				break;
			case GRAND_FINALE: 
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("Can only be used if no");
				MovePen(x, y + dy - j * 0.4);
				j ++;
				DrawTextString_Middle("cards in the Draw Pile."); 
				break;
		}
		MovePen(x, y + dy - j * 0.4);
		j ++;
		strcpy(s1, "");
		if(card[p].confirm == 0)
		{
			strcat(s1, "Object: All. ");
		}else
		{
			strcat(s1, "Object: One. ");
		}
		DrawTextString_Middle(s1);
		if(card[p].usage == -1)
		{
			MovePen(x, y + dy - j * 0.4);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Consumed. ");
			DrawTextString_Middle(s1);
		}else if(card[p].usage == 0)
		{
			MovePen(x, y + dy - j * 0.4);
			j ++;
			strcpy(s1, "");
			strcat(s1, "Unplayable. ");
			DrawTextString_Middle(s1);
		}
	}
}
void showCharacterState()
{
	char s[105];
	
	MovePen(0, height / 5 * 4);
	DrawLine(width / 8 + 0.2, 0);
	DrawLine(0, -1 * height / 7 * 2);
	DrawLine(-1 * width / 8 - 0.2, 0);
	
	SetPointSize(12);
	
	strcpy(s, "Health: ");
	DrawHealth(0.05, 0.15, height / 5 * 4 - 0.2);
	MovePen(0.05 + 0.2, height / 5 * 4 - 0.3);
	DrawTextString(s);
	integerToString(now_character->now_health);
	strcpy(s, trans);
	strcat(s, " / ");
	integerToString(now_character->max_health);
	strcat(s, trans);
	MovePen(width / 8 - 0.05 +0.2, height / 5 * 4 - 0.3);
	DrawTextString_Right(s);
	
	strcpy(s, "Block: ");
	DrawBlock(0.05, 0.02, height / 5 * 4 - 0.55);
	MovePen(0.05 + 0.2, height / 5 * 4 - 0.6);
	DrawTextString(s);
	integerToString(now_character->block);
	strcpy(s, trans);
	MovePen(width / 8 - 0.05 + 0.2, height / 5 * 4 - 0.6);
	DrawTextString_Right(s);
	
	strcpy(s, "Strength: ");
	DrawStrength(0.025, 0.075, height / 5 * 4 - 0.85);
	MovePen(0.05 + 0.2, height / 5 * 4 - 0.9);
	DrawTextString(s);
	integerToString(now_character->strength);
	strcpy(s, trans);
	MovePen(width / 8 - 0.05 + 0.2, height / 5 * 4 - 0.9);
	DrawTextString_Right(s);
	
	strcpy(s, "Vulnerable: ");
	DrawVulnerable(0.07, 0.07, height / 5 * 4 - 1.1);
	MovePen(0.05 + 0.2, height / 5 * 4 - 1.2);
	DrawTextString(s);
	integerToString(now_character->vulnerable);
	strcpy(s, trans);
	MovePen(width / 8 - 0.05 + 0.2, height / 5 * 4 - 1.2);
	DrawTextString_Right(s);
	
	strcpy(s, "Weak: ");
	DrawWeak(0.03, 0.09, height / 5 * 4 - 1.5);	
	MovePen(0.05 + 0.2, height / 5 * 4 - 1.5);
	DrawTextString(s);
	integerToString(now_character->weak);
	strcpy(s, trans);
	MovePen(width / 8 - 0.05 + 0.2, height / 5 * 4 - 1.5);
	DrawTextString_Right(s);
	
	strcpy(s, "Frail: ");
	DrawFrail(0.07, 0.09, height / 5 * 4 - 1.85);	
	MovePen(0.05 + 0.2, height / 5 * 4 - 1.8);
	DrawTextString(s);
	integerToString(now_character->frail);
	strcpy(s, trans);
	MovePen(width / 8 - 0.05 + 0.2, height / 5 * 4 - 1.8);
	DrawTextString_Right(s);
}
void showEnemyState(int number)
{
	char s[105];
	double x, y;
	x = width * (number + 1) / (now_enemy_n + 1) / 2.3 + width * 0.45;
	y = height * 3 / 5 + 2;
	MovePen(x, y);
	DrawArrow(20, PI / -2);
	
	MovePen(width, height / 5 * 4);
	DrawLine(width / -8, 0);
	DrawLine(0, -1 * height / 7 * 2);
	DrawLine(1 * width / 8, 0);
	
	SetPointSize(12);
	
	strcpy(s, "Health: ");
	MovePen(width * 7 / 8 + 0.05, height / 5 * 4 - 0.3);
	DrawTextString(s);
	integerToString(now_enemy[number]->now_health);
	strcpy(s, trans);
	strcat(s, " / ");
	integerToString(now_enemy[number]->max_health);
	strcat(s, trans);
	MovePen(width - 0.05, height / 5 * 4 - 0.3);
	DrawTextString_Right(s);
	
	strcpy(s, "Block: ");
	MovePen(width * 7 / 8 + 0.05, height / 5 * 4 - 0.6);
	DrawTextString(s);
	integerToString(now_enemy[number]->block);
	strcpy(s, trans);
	MovePen(width - 0.05, height / 5 * 4 - 0.6);
	DrawTextString_Right(s);
	
	strcpy(s, "Strength: ");
	MovePen(width * 7 / 8 + 0.05, height / 5 * 4 - 0.9);
	DrawTextString(s);
	integerToString(now_enemy[number]->strength);
	strcpy(s, trans);
	MovePen(width - 0.05, height / 5 * 4 - 0.9);
	DrawTextString_Right(s);
	
	strcpy(s, "Vulnerable: ");
	MovePen(width * 7 / 8 + 0.05, height / 5 * 4 - 1.2);
	DrawTextString(s);
	integerToString(now_enemy[number]->vulnerable);
	strcpy(s, trans);
	MovePen(width - 0.05, height / 5 * 4 - 1.2);
	DrawTextString_Right(s);
	
	strcpy(s, "Weak: ");
	MovePen(width * 7 / 8 + 0.05, height / 5 * 4 - 1.5);
	DrawTextString(s);
	integerToString(now_enemy[number]->weak);
	strcpy(s, trans);
	MovePen(width - 0.05, height / 5 * 4 - 1.5);
	DrawTextString_Right(s);
	
	strcpy(s, "Poison: ");
	MovePen(width * 7 / 8 + 0.05, height / 5 * 4 - 1.8);
	DrawTextString(s);
	integerToString(now_enemy[number]->poison);
	strcpy(s, trans);
	MovePen(width - 0.05, height / 5 * 4 - 1.8);
	DrawTextString_Right(s);
}
void erasePreviousCharacterState()
{
	SetEraseMode(TRUE);
	showCharacterState();
	SetEraseMode(FALSE);
}
void erasePreviousEnemyState(int number)
{
	SetEraseMode(TRUE);
	showEnemyState(number);
	SetEraseMode(FALSE);
}

void discardCard(int total)
{
	int size = GetPointSize();
	SetPointSize(18);
	char s[50];
	MovePen(width / 2, height * 1 / 2);
	strcpy(s, "Discard ");
	integerToString(total);
	strcat(s, trans);
	strcat(s, " Card"); 
	DrawTextString_Middle(s);
	SetPointSize(size);
}
void consumeCard(int total)
{
	int size = GetPointSize();
	SetPointSize(18);
	char s[50];
	MovePen(width / 2, height * 1 / 2);
	strcpy(s, "Consume ");
	integerToString(total);
	strcat(s, trans);
	strcat(s, " Card"); 
	DrawTextString_Middle(s);
	SetPointSize(size);
}

