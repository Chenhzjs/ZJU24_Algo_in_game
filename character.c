#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <conio.h> 
#include <graphics.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "character.h"
#include "card.h"
extern trans[10];
extern layer;
extern cards_number;
extern nowEvent;
static void writeCharacter(int max_health, int now_health, 
	int money, int relic, int id)
{
	the_character[id].max_health = max_health;
	the_character[id].now_health = now_health;
	the_character[id].money = money;
	the_character[id].relic_num = 1;
	the_character[id].id = id;
	relics[relic] = 1;
}

static void writeEnemy(int max_health, int now_health, 
    int block, int strength, int id, int enemy_type)
{
	the_enemy[id].max_health = max_health;
	the_enemy[id].now_health = now_health;
	the_enemy[id].block = block;
	the_enemy[id].strength = strength;
	the_enemy[id].id = id;
	the_enemy[id].enemy_type = enemy_type;
	
	the_enemy[id].poison = 0;
	the_enemy[id].vulnerable = 0;
	the_enemy[id].weak = 0;
}

void initCharacter()
{
	writeCharacter(80, 80, 150, RELIC_0, IRONCLAD);
	writeCharacter(70, 70, 99, RELIC_1, SILENTER);
}

void initEnemy()
{
	writeEnemy(12, 12, 0, 0, LITTLE_SLIM, NORMAL);/*С��ʷ��ķ*/
	writeEnemy(55, 55, 0, 0, HARD_SLIM, HARD);/*�е�ʷ��ķ*/
	writeEnemy(150, 150, 0, 0, BOSS_SLIM, BOSS);/*ʷ��ķ�ϴ�*/
	writeEnemy(15, 15, 0, 0, LOUSE, NORMAL);/*ʭ��*/
	writeEnemy(50, 50, 0, 0, CULTIST, NORMAL);/*а��ͽ*/
	writeEnemy(80, 80, 0, 1, GREMLIN_NOB, HARD);/*�ؾ�����?*/
	writeEnemy(40, 40, 0, 0, SENTRY, HARD);/*����*/
	writeEnemy(200, 200, 0, 0, NEMESIS, HARD);/*�췣*/
	writeEnemy(120, 120, 8, 0, LAGAVULIN, HARD);/*�ּ�ά��*/
	writeEnemy(450, 450, 0, 0, TIME_EATER, BOSS);/*ʱ��������*/
	writeEnemy(300, 300, 0, 0, THE_MAW, HARD);/*�޿�*/
	writeEnemy(250, 250, 0, 0, HEXAGHOST, BOSS);/*��������*/
}
static void writeNowEnemy(struct CHARATER_STATE *p, int id, int layer)
{
	p->max_health = the_enemy[id].max_health + ((layer - 1) / 15) * 15;
	p->now_health = the_enemy[id].now_health + ((layer - 1) / 15) * 15;
	p->block = the_enemy[id].block;
	p->strength = the_enemy[id].strength;
	p->poison = the_enemy[id].poison;
	p->vulnerable = the_enemy[id].vulnerable;
	p->weak = the_enemy[id].weak;
	p->id = the_enemy[id].id;
	p->enemy_type = the_enemy[id].enemy_type;
	p->next = NULL;
}
void initNowEnemy(int layer, int enemy_type)
{
	int p;
	int i;
	struct CHARATER_STATE *head = NULL;
	if(enemy_type == NORMAL)
	{
		p = rand() % 3;
		switch(p)
		{
			case 0:
				now_enemy_n = 3;
				for(i = 0; i < now_enemy_n; i ++)
				{
					head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
					writeNowEnemy(head, LITTLE_SLIM, layer);
					now_enemy[i] = head;
				}
				break;
			case 1:
				now_enemy_n = 2;
				for(i = 0; i < now_enemy_n; i ++)
				{
					head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
					writeNowEnemy(head, LOUSE, layer);
					now_enemy[i] = head;
				}
				break;
			case 2:
				now_enemy_n = 1;
				for(i = 0; i < now_enemy_n; i ++)
				{
					head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
					writeNowEnemy(head, CULTIST, layer);
					now_enemy[i] = head;
				}
				break;
		}
	
	}
	if(enemy_type == HARD)
	{
		p = rand() % 3;
		switch(p)
		{
			case 0:
				now_enemy_n = 3;
				for(i = 0; i < now_enemy_n; i ++)
				{
					head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
					writeNowEnemy(head, SENTRY, layer);
					now_enemy[i] = head;
				}
				break;
			case 1:
				now_enemy_n = 1;
				for(i = 0; i < now_enemy_n; i ++)
				{
					head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
					writeNowEnemy(head, GREMLIN_NOB, layer);
					now_enemy[i] = head;
				}
				break;
			case 2:
				now_enemy_n = 1;
				for(i = 0; i < now_enemy_n; i ++)
				{
					head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
					writeNowEnemy(head, LAGAVULIN, layer);
					now_enemy[i] = head;
				}
				break;
			case 3:
				now_enemy_n = 2;
				for(i = 0; i < now_enemy_n; i ++)
				{
					head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
					writeNowEnemy(head, HARD_SLIM, layer);
					now_enemy[i] = head;
				}
				break;
			case 4:
				now_enemy_n = 1;
				for(i = 0; i < now_enemy_n; i ++)
				{
					head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
					writeNowEnemy(head, THE_MAW, layer);
					now_enemy[i] = head;
				}
				break;
			case 5:
				now_enemy_n = 1;
				for(i = 0; i < now_enemy_n; i ++)
				{
					head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
					writeNowEnemy(head, NEMESIS, layer);
					now_enemy[i] = head;
				}
				break;
		}
	
	}
	if(enemy_type == BOSS)
	{
		p = rand() % 3;
		switch(p)
		{
			case 0:
				now_enemy_n = 1;
				for(i = 0; i < now_enemy_n; i ++)
				{
					head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
					writeNowEnemy(head, BOSS_SLIM, layer);
					now_enemy[i] = head;
				}
				break;
			case 1:
				now_enemy_n = 1;
				for(i = 0; i < now_enemy_n; i ++)
				{
					head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
					writeNowEnemy(head, TIME_EATER, layer);
					now_enemy[i] = head;
				}
				break;
			case 2:
				now_enemy_n = 1;
				for(i = 0; i < now_enemy_n; i ++)
				{
					head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
					writeNowEnemy(head, HEXAGHOST, layer);
					now_enemy[i] = head;
				}
				break;
		}
	
	}
}

void initNowCharacter(int id)
{
	int i;
	struct CHARATER_STATE *head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
	head->max_health = the_character[id].max_health;
	head->now_health = the_character[id].now_health;
	head->money = the_character[id].money;
	head->relic_num = the_character[id].relic_num;
	head->id = the_character[id].id;
	head->block = 0;
	head->strength = 0;
	head->vulnerable = 0;
	head->weak = 0;
	head->frail = 0;

	head->next = NULL;
	now_character = head;
	cards_number = 0;
	if(id == IRONCLAD)
	{
		for(i = 0; i < 5; i ++)
		{
			getCard(STRIKE);
		}
		for(i = 0; i < 4; i ++)
		{
			getCard(DEFEND);
		} 
		getCard(BASH);
	}
	if(id == SILENTER)
	{
		for(i = 0; i < 5; i ++)
		{
			getCard(STRIKE);
		}
		for(i = 0; i < 5; i ++)
		{
			getCard(DEFEND);
		}
		getCard(SURVIVOR);
		getCard(NEUTRALIZE);
	}
}
static void copyCharacterState(struct CHARATER_STATE *p)
{
	p->max_health = now_character->max_health;
	p->now_health = now_character->now_health;
	p->block = now_character->block;
	p->strength = now_character->strength;
	p->poison = now_character->poison;
	p->frail = now_character->frail;
	p->vulnerable = now_character->vulnerable;
	p->weak = now_character->weak;
	p->money = now_character->money;
	p->id = now_character->id;
	p->relic_num = now_character->relic_num;
}
static void copyEnemyState(struct CHARATER_STATE *p, int id)
{
	p->max_health = now_enemy[id]->max_health;
	p->now_health = now_enemy[id]->now_health;
	p->block = now_enemy[id]->block;
	p->strength = now_enemy[id]->strength;
	p->poison = now_enemy[id]->poison;
	p->vulnerable = now_enemy[id]->vulnerable;
	p->weak = now_enemy[id]->weak;
	p->money = now_enemy[id]->money;
	p->id = now_enemy[id]->id;
	p->enemy_type = now_enemy[id]->enemy_type;
}
void changeState(int type, int pos, int state, int number) // type 0 character   1 enemy
{
	if(type == 0) erasePreviousCharacterState();
	else if(type == 1) erasePreviousEnemyState(pos);
	struct CHARATER_STATE *p = NULL;
	if(type == 0)
	{
		p = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
		copyCharacterState(p);
		switch(state)
		{
			case MAX_HEALTH:
				p->max_health += number;
				if(number > 0) p->now_health += number;
				else if(p->now_health > p->max_health) p->now_health = p->max_health;
				break;
			case NOW_HEALTH:
				p->now_health += number;
				if(p->now_health > p->max_health) p->now_health = p->max_health; 
				if(p->now_health <= 0) p->now_health = 0;
				break;
			case BLOCK:
				p->block += number;
				if(p->block > 999) p->block = 999;
				
				break;
			case STRENGTH:
				p->strength += number;
				if(p->strength > 999) p->strength = 999;
				break;
			case VULNERABLE:
				p->vulnerable += number;
				if(p->vulnerable > 999) p->vulnerable = 999;
				if(p->vulnerable <= 0) p->vulnerable = 0;
				break;
			case WEAK:
				p->weak += number;
				if(p->weak > 999) p->weak = 999;
				if(p->weak <= 0) p->weak = 0;
				break;
			case FRAIL:
				p->frail += number;
				if(p->frail > 999) p->frail = 999;
				if(p->frail <= 0) p->frail = 0;
				break;
			case MONEY:
				p->money += number;
				if(p->money < 0) p->money = 0;
				break;
			case RELIC:
				if(number < 0)
				{
					number = -1 * number;
					relics[number] = 0;
				}else
				{
					relics[number] = 1;
				}
				break;
		}
		p->next = now_character;
		now_character = p;
	}
	if(type == 1)
	{
		p = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
		copyEnemyState(p, pos);
		switch(state)
		{
			case MAX_HEALTH:
				p->max_health += number;
				if(number > 0) p->now_health += number;
				else if(p->now_health > p->max_health) p->now_health = p->max_health;
				break;
			case NOW_HEALTH:
				if (number < 0) {
					if (p->block < -number) {
						number = number + p->block;
						p->block = 0;
					} else {
						p->block += number; 
						number = 0;
					}
				}
				p->now_health += number;
				if(p->now_health > p->max_health) p->now_health = p->max_health; 
				if(p->now_health <= 0) p->now_health = 0;
				break;
			case BLOCK:
				p->block += number;
				if(p->block > 999) p->block = 999;
				break;
			case STRENGTH:
				p->strength += number;
				if(p->strength > 999) p->strength = 999;
				break;
			case POISON:
				p->poison += number;
				if(p->poison > 999) p->poison = 999;
				if(p->poison <= 0) p->poison = 0;
				break;
			case VULNERABLE:
				p->vulnerable += number;
				if(p->vulnerable > 999) p->vulnerable = 999;
				if(p->vulnerable <= 0) p->vulnerable = 0;
				break;
			case WEAK:
				p->weak += number;
				if(p->weak > 999) p->weak = 999;
				if(p->weak <= 0) p->weak = 0;
				break;
		}
		p->next = now_enemy[pos];
		now_enemy[pos] = p;
	}
}

void freeEnemy(int n)
{
	struct CHARATER_STATE *head = NULL;
	int j;
	struct CHARATER_STATE *f = NULL;
	for(j = 0; j < n; j ++)
	{
		f = now_enemy[j];
		for(head = now_enemy[j]->next; head != NULL; head = head->next)
		{
			free(f);
			f = head;
		}
	}
}
void freeCharacter()
{
	struct CHARATER_STATE *head = NULL;
	int j;
	struct CHARATER_STATE *f = NULL;
	f = now_character;
	if(f->next = NULL) return ;
	for(head = f; head->next != NULL; head = f)
	{
		f = f->next;
		free(head);
	}
	now_character->next = NULL;
}

void getStoredState()
{
	FILE *fp, * fp1;      
	struct CHARATER_STATE *head = NULL;
	int i;
	int n;
	int max_health, now_health, relic_num, money, id;

	if((fp=fopen("game.txt","r")) == NULL)
	{	 
   	    exit(0);
	}
	fscanf(fp, "%d", &nowEvent);
	fscanf(fp, "%d", &layer);
	fscanf(fp,"%d%d%d%d%d", &max_health, &now_health, &relic_num, &money, &id);
	head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
	head->max_health = max_health;
	head->now_health = now_health;
	head->money = money;
	head->relic_num = relic_num;
	head->id = id;
	head->block = 0;
	head->strength = 0;
	head->vulnerable = 0;
	head->weak = 0;
	head->frail = 0;
	head->next = NULL;
	now_character = head;

	for(i = 0; i < relic_n; i ++)
	{
		fscanf(fp, "%d", &relics[i]);
	}
	fscanf(fp, "%d", &now_enemy_n);

	for(i = 0; i < now_enemy_n; i ++)
	{
		fscanf(fp, "%d", &id);
		head = (struct CHARATER_STATE *)malloc(sizeof(struct CHARATER_STATE));
		writeNowEnemy(head, id, layer);
		now_enemy[i] = head;
	}

	fscanf(fp, "%d", &n);
	for(i = 0; i < n; i ++)
	{
		fscanf(fp, "%d", &id);
		getCard(id);
	}
	if(fclose(fp))
	{
		exit(0);
	}
}

void storeState(int n)
{
	FILE *fp;
	struct CHARATER_STATE *head = NULL;
	int i, j;
	if((fp=fopen("game.txt","w+")) == NULL)
	{	 
   	    exit(0);
	}
	fprintf(fp, "%d\n", nowEvent);
	fprintf(fp, "%d\n", layer);
	for(head = now_character; head->next != NULL; head = head->next) ;
	fprintf(fp,"%d %d %d %d %d\n", now_character->max_health, now_character->now_health, now_character->relic_num, now_character->money, now_character->id);
	for(i = 0; i < relic_n; i ++)
	{
		fprintf(fp, "%d ", relics[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp, "%d\n", n);
	for(j = 0; j < n; j ++)
	{
		fprintf(fp, "%d ", now_enemy[j]->id);
	}
	fprintf(fp, "\n");
	
	fprintf(fp, "%d\n", cards_number);
	for(i = 0; i < cards_number; i ++)
	{
		fprintf(fp, "%d ", c_card[i].id);
	}
	fprintf(fp, "\n");
	if(fclose(fp))
	{
		exit(0);
	}
}

void init_relics()
{
    strcpy(inscribe_relics[1], "End of the battle, restore 6 health.");
    strcpy(inscribe_relics[2], "Beginning of each battle, draw an additional 2 cards.");
    strcpy(inscribe_relics[3], "Beginning of each battle, restore 2 health.");
    strcpy(inscribe_relics[4], "Draw 3 cards when damaged first time in each battle.");
    strcpy(inscribe_relics[5], "Lose your whole money. Increase 1 energy limit");
    strcpy(inscribe_relics[6], "Gain 1 energy in the first round of each battle.");
    strcpy(inscribe_relics[7], "If you don't have blocks in the end, gain 6 blocks.");
    strcpy(inscribe_relics[8], "When your health <= 50%, gain 3 strength.");
    strcpy(inscribe_relics[9], "Restores an additional 15 health during rest.");
    strcpy(inscribe_relics[10], "Removal service is permanently priced at 50 gold coins.");
    strcpy(inscribe_relics[11], "When causing a poisoned state, give one more.");
    strcpy(inscribe_relics[12], "When picking up, increase your maximum health by 7.");
    strcpy(inscribe_relics[13], "When entering a store room, restore 15 health.");
    strcpy(inscribe_relics[14], "Gain 10 blocks at the beginning of each battle");
    strcpy(inscribe_relics[15], "When picking up, increase 15 maximum health ");
    strcpy(inscribe_relics[16], "You will not lose all blocks, but instead lose 15 blocks");
    strcpy(inscribe_relics[17], "When picking up, obtain 300 coins.");
    strcpy(inscribe_relics[18], "Increase 1 energy limit. Enemies gain 1 strength.");
    strcpy(inscribe_relics[19], "Obtain 100 gold coins. Gain 10 maximum health, 2 strength.");
    strcpy(inscribe_relics[20], "50% discount on all products.");
}

