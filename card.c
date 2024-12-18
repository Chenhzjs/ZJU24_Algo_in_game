#include "card.h"
#include <time.h>
#include <graphics.h>
#include <windows.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

static void writeCard(int usage, int id, int energy_cost, int upgrade,
	int attack, int block, int strength,
	int poison, int vulnerable, int weak,
	int type, int rarity, int draw,	int discard,
	int consume, int card_state, int confirm)
{
	card[id].usage = usage;
	card[id].id = id;
	card[id].energy_cost = energy_cost;
	card[id].upgrade = upgrade;
	card[id].attack = attack;
	card[id].block = block;
	card[id].strength = strength;
	card[id].poison = poison;
	card[id].vulnerable = vulnerable;
	card[id].weak = weak;
	card[id].type = type;
	card[id].rarity = rarity;
	card[id].draw = draw;
	card[id].discard = discard;
	card[id].consume = consume;
	card[id].card_state = card_state;
	card[id].confirm = confirm;
}
void initCard()
{
	writeCard(1, BASH, 2, 0, 8, 0, 0, 0, 2, 0, ATTACK, STARTER, 0, 0, 0, DRAW, 1);
	strcpy(card[BASH].name, "bash");
	
	writeCard(1, DEFEND, 1, 0, 0, 5, 0, 0, 0, 0, SKILL, STARTER, 0, 0, 0, DRAW, 1); 
	strcpy(card[DEFEND].name, "defend");
	
	writeCard(1, STRIKE, 1, 0, 6, 0, 0, 0, 0, 0, ATTACK, STARTER, 0, 0, 0, DRAW, 1);
	strcpy(card[STRIKE].name, "strike");
	
	writeCard(1, ANGER, 0, 0, 6, 0, 0, 0, 0, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[ANGER].name, "anger");
	
	writeCard(1, BODY_SLAM, 1, 0, 0, 0, 0, 0, 0, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 1);//DEAL DAMAGE EQUAL TO BLOCK
	strcpy(card[BODY_SLAM].name, "body slam");
	
	writeCard(1, CLEAVE, 1, 0, 8, 0, 0, 0, 0, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 0);
	strcpy(card[CLEAVE].name, "cleave");
	
	writeCard(1, CLASH, 1, 0, 14, 0, 0, 0, 0, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 1);//
	strcpy(card[CLASH].name, "clash");
	
	writeCard(1, CLOTHESLINE, 2, 0, 12, 0, 0, 0, 0, 2, ATTACK, COMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[CLOTHESLINE].name, "clothesline");
	
	writeCard(1, HEADBUTT, 1, 0, 9, 0, 0, 0, 0, 0, ATTACK, COMMON, 1, 0, 0, DRAW, 1);
	strcpy(card[HEADBUTT].name, "headbutt");
	
	writeCard(1, HEAVY_BLADE, 2, 0, 14, 0, 0, 0, 0, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[HEAVY_BLADE].name, "heavy blade");
	
	writeCard(1, IRON_WAVE, 1, 0, 5, 5, 0, 0, 0, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[IRON_WAVE].name, "iron_wave");
	
	writeCard(1, POMMEL_STRIKE, 1, 0, 9, 0, 0, 0, 0, 0, ATTACK, COMMON, 1, 0, 0, DRAW, 1);
	strcpy(card[POMMEL_STRIKE].name, "pommel strike");
	
	writeCard(1, SHRUG_IT_OFF, 1, 0, 0, 8, 0, 0, 0, 0, SKILL, COMMON, 1, 0, 0, DRAW, 0);
	strcpy(card[SHRUG_IT_OFF].name, "shrug it off");
	
	writeCard(1, SWORD_BOOMERANG, 1, 0, 4, 0, 0, 0, 0, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 0);//3 times, RANDOM ENEMY
	strcpy(card[SWORD_BOOMERANG].name, "sword boomerang");
	
	writeCard(1, THUNDERCLAP, 1, 0, 4, 0, 0, 0, 1, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 0);
	strcpy(card[THUNDERCLAP].name, "thunderclap");
	
	writeCard(1, TRUE_GRIT, 1, 0, 0, 7, 0, 0, 0, 0, SKILL, COMMON, 0, 0, 1, DRAW, 0);
	strcpy(card[TRUE_GRIT].name, "true grit");
	
	writeCard(1, TWIN_STRIKE, 1, 0, 10, 0, 0, 0, 0, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 1);//TWICE
	strcpy(card[TWIN_STRIKE].name, "twin strike");
	
	writeCard(1, BATTLE_TRANCE, 0, 0, 0, 0, 0, 0, 0, 0, SKILL, UNCOMMON, 2, 0, 0, DRAW, 0);
	strcpy(card[BATTLE_TRANCE].name, "battle trance");
	
	writeCard(1, BLOODLETTING, 0, 0, 0, 0, 0, 0, 0, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);//LOSE 3 HP, GAIN 2 ENERGY
	strcpy(card[BLOODLETTING].name, "bloodletting");
	
	writeCard(1, BURNING_PACT, 1, 0, 0, 0, 0, 0, 0, 0, SKILL, UNCOMMON, 2, 0, 1, DRAW, 1);
	strcpy(card[BURNING_PACT].name, "burning pact");
	
	writeCard(-1, CARNAGE, 2, 0, 20, 0, 0, 0, 0, 0, ATTACK, UNCOMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[CARNAGE].name, "carnage");
	
	writeCard(1, DARK_EMBRACE, 2, 0, 0, 0, 0, 0, 0, 0, POWER, UNCOMMON, 2, 0, 3, DRAW, 0);
	strcpy(card[DARK_EMBRACE].name, "dark embrace");
	
	writeCard(-1, DISARM, 1, 0, 0, 0, -2, 0, 0, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);//ENEMY LOSES 2 STRENGTH
	strcpy(card[DISARM].name, "disarm");
	
	writeCard(1, ENTRENCH, 2, 0, 0, 0, 0, 0, 0, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);//DOUBLE YOUR BLOCK
	strcpy(card[ENTRENCH].name, "entrench");

	writeCard(-1, GHOSTY_ARMOR, 1, 0, 0, 10, 0, 0, 0, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);
	strcpy(card[GHOSTY_ARMOR].name, "ghosty armor");
	
	writeCard(1, HEMOKINESIS, 0, 0, 15, 0, 0, 0, 0, 0, ATTACK, UNCOMMON, 0, 0, 0, DRAW, 1);//LOSE 2 HP
	strcpy(card[HEMOKINESIS].name, "hemokinesis");
	
	writeCard(1, INFLAME, 1, 0, 0, 0, 2, 0, 0, 0, POWER, UNCOMMON, 0, 0, 0, DRAW, 0);
	strcpy(card[INFLAME].name, "inflame");
	
	writeCard(-1, INTIMIDATE, 0, 0, 0, 0, 0, 0, 0, 1, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);
	strcpy(card[INTIMIDATE].name, "intimidate");
	
	writeCard(1, POWER_THROUGH, 1, 0, 0, 15, 0, 0, 0, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);
	strcpy(card[POWER_THROUGH].name, "power through");
	
	writeCard(1, RAMPAGE, 1, 0, 8, 0, 0, 0, 0, 0, ATTACK, UNCOMMON, 0, 0, 0, DRAW, 1);//INCREASE 5 DAMAGE
	strcpy(card[RAMPAGE].name, "rampage");
	
	writeCard(1, SECOND_WIND, 1, 0, 0, 5, 0, 0, 0, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);//EXHAUST ALL NON-ATTACK CARDS
	strcpy(card[SECOND_WIND].name, "second wind");
	
	writeCard(-1, SEEING_RED, 1, 0, 0, 0, 0, 0, 0, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);//GAIN 2 ENERGY
	strcpy(card[SEEING_RED].name, "seeing red");
	
	writeCard(1, SEVER_SOUL, 2, 0, 16, 0, 0, 0, 0, 0, ATTACK, UNCOMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[SEVER_SOUL].name, "sever soul");
	
	writeCard(-1, SHOCKWAVE, 2, 0, 0, 0, 0, 0, 3, 3, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);
	strcpy(card[SHOCKWAVE].name, "shockwave");
	
	writeCard(1, SPOT_WEAKNESS, 1, 0, 0, 0, 3, 0, 0, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);
	strcpy(card[SPOT_WEAKNESS].name, "spot weakness");
	
	writeCard(1, UPPERCUT, 2, 0, 13, 0, 0, 0, 1, 1, ATTACK, UNCOMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[UPPERCUT].name, "uppercut");
	
	writeCard(1, BLUDGEN, 3, 0, 32, 0, 0, 0, 0, 0, ATTACK, RARE, 0, 0, 0, DRAW, 1);
	strcpy(card[BLUDGEN].name, "bludgen");
	
	writeCard(-1, FEED, 1, 0, 10, 0, 0, 0, 0, 0, ATTACK, RARE, 0, 0, 0, DRAW, 1);//RAISE 3 MAX HP
	strcpy(card[FEED].name, "feed");
	
	writeCard(-1, FIEND_FIRE, 2, 0, 7, 0, 0, 0, 0, 0, ATTACK, RARE, 0, 0, 0, DRAW, 1);//EXHAUSTED ALL CARDS IN HAND,DEAL (7 * N) DAMAGE
	strcpy(card[FIEND_FIRE].name, "fiend fire");
	
	writeCard(1, IMMOLATE, 2, 0, 21, 0, 0, 0, 0, 0, ATTACK, RARE, 0, 0, 0, DRAW, 0);//TO ALL ENEMIES, ADD A BURN TO DISCARD PILE
	strcpy(card[IMMOLATE].name, "immolate");
	
	writeCard(-1, IMPERVIOUS, 2, 0, 0, 30, 0, 0, 0, 0, SKILL, RARE, 0, 0, 0, DRAW, 0);
	strcpy(card[IMPERVIOUS].name, "impervious");
	
	writeCard(-1, LIMIT_BREAK, 1, 0, 0, 0, -1, 0, 0, 0, SKILL, RARE, 0, 0, 0, DRAW, 0);//DOUBLE STRENGTH
	strcpy(card[LIMIT_BREAK].name, "limit break");
	
	writeCard(-1, OFFERING, 0, 0, 0, 0, 0, 0, 0, 0, SKILL, RARE, 3, 0, 0, DRAW, 0);//LOSE 6 HP, GAIN 2 ENERGY
	strcpy(card[OFFERING].name, "offering");
	
	writeCard(-1, REAPER, 2, 0, 4, 0, 0, 0, 0, 0, ATTACK, RARE, 0, 0, 0, DRAW, 0);//HEAL HP EQUAL TO YNBLOCKED DAMAGE
	strcpy(card[REAPER].name, "reaper");
	//IRONCLAD
	writeCard(1, NEUTRALIZE, 0, 0, 3, 0, 0, 0, 0, 1, ATTACK, STARTER, 0, 0, 0, DRAW, 1);
	strcpy(card[NEUTRALIZE].name, "neutralize");
	
	writeCard(1, SURVIVOR, 1, 0, 0, 8, 0, 0, 0, 0, SKILL, STARTER, 0, 1, 0, DRAW, 1);
	strcpy(card[SURVIVOR].name, "survivor");
	
	writeCard(1, ACROBATICS, 1, 0, 0, 0, 0, 0, 0, 0, SKILL, COMMON, 3, 1, 0, DRAW, 1);
	strcpy(card[ACROBATICS].name, "acrobatics");
	
	writeCard(1, BACKFLIP, 1, 0, 0, 5, 0, 0, 0, 0, SKILL, COMMON, 2, 0, 0, DRAW, 0);
	strcpy(card[BACKFLIP].name, "backflip");
	
	writeCard(1, BANE, 1, 0, 7, 0, 0, 0, 0, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 1);//IF POISONED, DEAL 7 DAMAGE AGAIN
	strcpy(card[BANE].name, "bane");
	
	writeCard(1, DAGGER_SPRAY, 1, 0, 4, 0, 0, 0, 0, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 0);//TO ALL ENEMIES TWICE
	strcpy(card[DAGGER_SPRAY].name, "dagger spary");
	
	writeCard(1, DAGGER_THROW, 1, 0, 9, 0, 0, 0, 0, 0, ATTACK, COMMON, 1, 1, 0, DRAW, 1);
	strcpy(card[DAGGER_THROW].name, "dagger throw");
	
	writeCard(1, DEADLY_POISON, 1, 0, 0, 0, 0, 5, 0, 0, SKILL, COMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[DEADLY_POISON].name, "deadly poison");
	
	writeCard(1, DEFLECT, 0, 0, 0, 4, 0, 0, 0, 0, SKILL, COMMON, 0, 0, 0, DRAW, 0);
	strcpy(card[DEFLECT].name, "deflect");
	
	writeCard(1, POISONED_STAB, 1, 0, 6, 0, 0, 3, 0, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[POISONED_STAB].name, "poisoned stab");
	
	writeCard(1, PREPARED, 0, 0, 0, 0, 0, 0, 0, 0, SKILL, COMMON, 1, 1, 0, DRAW, 1);
	strcpy(card[PREPARED].name, "prepared");
	
	writeCard(1, QUICK_SLASH, 0, 0, 8, 0, 0, 0, 0, 0, ATTACK, COMMON, 1, 0, 0, DRAW, 1);
	strcpy(card[QUICK_SLASH].name, "quick slash");
	
	writeCard(1, SLICE, 0, 0, 6, 0, 0, 0, 0, 0, ATTACK, COMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[SLICE].name, "slice");
	
	writeCard(1, SUCKER_PUNCH, 0, 0, 7, 0, 0, 0, 0, 1, ATTACK, COMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[SUCKER_PUNCH].name, "sucker punch");
	
	writeCard(-1, BACKSTAB, 0, 0, 11, 0, 0, 0, 0, 0, ATTACK, UNCOMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[BACKSTAB].name, "backstab");
	
	writeCard(1, POISON_EXTRACT, 2, 0, 0, -1, 0, 0, 0, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 1);//
	strcpy(card[POISON_EXTRACT].name, "poison extract");
	
	writeCard(1, BOUNCING_FLASK, 2, 0, 0, 0, 0, 3, 0, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);
	strcpy(card[BOUNCING_FLASK].name, "bouncing flask");
	
	writeCard(-1, CALCULATED_GAMBLE, 0, 0, 0, 0, 0, 0, 0, 0, SKILL, UNCOMMON, -1, -1, 0, DRAW, 1);
	strcpy(card[CALCULATED_GAMBLE].name, "calculated gamble");
	
	writeCard(-1, CATALYST, 1, 0, 0, 0, 0, -1, 0, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 1);//DOUBLE THE POISON
	strcpy(card[CATALYST].name, "catalyst");
	
	writeCard(1, CONCENTRATE, 0, 0, 0, 0, 0, 0, 0, 0, SKILL, UNCOMMON, 0, 3, 0, DRAW, 0);
	strcpy(card[CONCENTRATE].name, "concentrate");
	
	writeCard(-1, CRIPPLING_CLOUD, 2, 0, 0, 0, 0, 4, 0, 2, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);
	strcpy(card[CRIPPLING_CLOUD].name, "cripping cloud");
	
	writeCard(1, DASH, 2, 0, 10, 10, 0, 0, 0, 0, ATTACK, UNCOMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[DASH].name, "dash");

	writeCard(1, EXPERTISE, 2, 0, 0, 0, 0, 0, 0, 0, SKILL, UNCOMMON, -1, 0, 0, DRAW, 0);//UNTIL 6 IN HAND
	strcpy(card[EXPERTISE].name, "expertise");

	writeCard(1, LEG_SWEEP, 2, 0, 0, 11, 0, 0, 0, 2, SKILL, UNCOMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[LEG_SWEEP].name, "leg sweep");
	
	writeCard(0, REFLEX, 0, 0, 0, 0, 0, 0, 0, 0, SKILL, UNCOMMON, -1, 0, 0, DRAW, 0);//IF IT IS DISCARDED, DRAW 2 CARDS
	strcpy(card[REFLEX].name, "reflex");
	
	writeCard(1, RIDDLE_WITH_HOLES, 2, 0, 3, 0, 0, 0, 0, 0, ATTACK, UNCOMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[RIDDLE_WITH_HOLES].name, "riddle with holes");
	
	writeCard(0, TACTICIAN, 0, 0, 0, 0, 0, 0, 0, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 0);//IF DISCARDED, GAIN 1 ENERGY
	strcpy(card[TACTICIAN].name, "tactician");
	
	writeCard(-1, TERROR, 1, 0, 0, 0, 0, 0, 99, 0, SKILL, UNCOMMON, 0, 0, 0, DRAW, 1);
	strcpy(card[TERROR].name, "terror");
	
	writeCard(-1, ADRENALINE, 0, 0, 0, 0, 0, 0, 0, 0, SKILL, RARE, 2, 0, 0, DRAW, 0);//GAIN 1 ENERGY
	strcpy(card[ADRENALINE].name, "adrenaline");
	
	writeCard(1, CORPSE_EXPLOSION, 2, 0, 15, 0, 0, 0, 0, 0, SKILL, RARE, 0, 0, 0, DRAW, 1);//WHEN AN ENEMY DIES, DEAL DAMAGE EQUAL TO ITS MAX HP TO ALL ENEMIES
	strcpy(card[CORPSE_EXPLOSION].name, "corpse explosion");
	
	writeCard(-1, DIE_DIE_DIE, 1, 0, 13, 0, 0, 0, 0, 0, ATTACK, RARE, 0, 0, 0, DRAW, 0);//TO ALL ENEMIES
	strcpy(card[DIE_DIE_DIE].name, "die die die");
	
	writeCard(1, GLASS_KNIFE, 1, 0, 16, 0, 0, 0, 0, 0, ATTACK, RARE, 0, 0, 0, DRAW, 1);//TWICE, DECREASE 2 DAMAGE THIS COMBAT
	strcpy(card[GLASS_KNIFE].name, "glass knife");
	
	writeCard(1, GRAND_FINALE, 0, 0, 50, 0, 0, 0, 0, 0, ATTACK, RARE, 0, 0, 0, DRAW, 0);//CAN ONLY BE PLAYED IF THERE ARE NO CARDS IN DRAW PILE
	strcpy(card[GRAND_FINALE].name, "grand finale");

	writeCard(1, UNLOAD, 1, 0, 14, 0, 0, 0, 0, 0, ATTACK, RARE, 0, 0, 0, DRAW, 1);//DISCARD ALL NON-ATTACK CARDS
	strcpy(card[UNLOAD].name, "unload");
	total_cards_number = 78;
	//SILENT
}

void shuffleCards()
{
	int i;
	for(i = 0; i < cards_number; i ++)
	{
		if(g_card[i].card_state == DISCARD)
		{
			g_card[i].card_state = DRAW;
		}
	}
	drawn = discardn;
	discardn = 0;
}

void getRandomCard(int n)
{
	int p;
	int i;
	for(i = 0; i < n; i ++)
	{
		if(drawn <= 0) shuffleCards();
		p = rand() % cards_number;
		while(g_card[p].card_state != DRAW) p = (p + 1) % cards_number;
		g_card[p].card_state = HAND;
		hand[handn] = p;
		handn ++;
		drawn --;
	}
}
void gameCard()
{
	int i;
	for(i = 0; i < cards_number; i ++)
	{
		strcpy(g_card[i].name, c_card[i].name);
		g_card[i].number = c_card[i].number;
		g_card[i].usage = c_card[i].usage;
		g_card[i].id = c_card[i].id;
		g_card[i].energy_cost = c_card[i].energy_cost;
		g_card[i].upgrade = c_card[i].upgrade;
		g_card[i].attack = c_card[i].attack;
		g_card[i].block = c_card[i].block;
		g_card[i].strength = c_card[i].strength;
		g_card[i].poison = c_card[i].poison;
		g_card[i].vulnerable = c_card[i].vulnerable;
		g_card[i].weak = c_card[i].weak;
		g_card[i].type = c_card[i].type;
		g_card[i].rarity = c_card[i].rarity;
		g_card[i].draw = c_card[i].draw;
		g_card[i].discard = c_card[i].discard;
		g_card[i].consume = c_card[i].consume;
		g_card[i].card_state = c_card[i].card_state;
		g_card[i].confirm = c_card[i].confirm; 
	}
}

void getCard(int id)
{
	strcpy(c_card[cards_number].name, card[id].name);
	c_card[cards_number].number = cards_number;
	c_card[cards_number].usage = card[id].usage;
	c_card[cards_number].id = card[id].id;
	c_card[cards_number].energy_cost = card[id].energy_cost;
	c_card[cards_number].upgrade = card[id].upgrade;
	c_card[cards_number].attack = card[id].attack;
	c_card[cards_number].block = card[id].block;
	c_card[cards_number].strength = card[id].strength;

	c_card[cards_number].poison = card[id].poison;
	c_card[cards_number].vulnerable = card[id].vulnerable;
	c_card[cards_number].weak = card[id].weak;

	c_card[cards_number].type = card[id].type;
	c_card[cards_number].rarity = card[id].rarity;
	c_card[cards_number].draw = card[id].draw;
	c_card[cards_number].discard = card[id].discard;
	c_card[cards_number].consume = card[id].consume;
	c_card[cards_number].card_state = card[id].card_state;
	c_card[cards_number].confirm = card[id].confirm;
	cards_number ++;
}
void loseCard(int id)
{
	int i, j;
	for(i = 0; i < cards_number; i ++)
	{
		if(c_card[i].id == id)
		{
			for(j = i; j < cards_number - 1; j ++)
			{
				strcpy(c_card[j].name, c_card[j + 1].name);
				c_card[j].number = c_card[j + 1].number;
				c_card[j].usage = c_card[j + 1].usage;
				c_card[j].id = c_card[j + 1].id;
				c_card[j].energy_cost = c_card[j + 1].energy_cost;
				c_card[j].upgrade = c_card[j + 1].upgrade;
				c_card[j].attack = c_card[j + 1].attack;
				c_card[j].block = c_card[j + 1].block;
				c_card[j].strength = c_card[j + 1].strength;
				c_card[j].poison = c_card[j + 1].poison;
				c_card[j].vulnerable = c_card[j + 1].vulnerable;
				c_card[j].weak = c_card[j + 1].weak;
				c_card[j].type = c_card[j + 1].type;
				c_card[j].rarity = c_card[j + 1].rarity;
				c_card[j].draw = c_card[j + 1].draw;
				c_card[j].discard = c_card[j + 1].discard;
				c_card[j].consume = c_card[j + 1].consume;
				c_card[j].card_state = c_card[j + 1].card_state;
				c_card[j].confirm = c_card[j + 1].confirm; 
			}
			break;
		}
	}
	cards_number --;
}

void upgradeCard(int number)
{
	c_card[number].upgrade = 1;
	switch(c_card[number].id)
	{
		case BASH:
			c_card[number].attack = 10;
			c_card[number].vulnerable = 3;
			break;
		case DEFEND:
			c_card[number].block = 8;
			break;
		case STRIKE:
			c_card[number].attack = 9;
			break;
		case ANGER:
			c_card[number].attack = 8;
			break;
		case BODY_SLAM:
			c_card[number].energy_cost = 0;
			break;
		case CLASH:
			c_card[number].attack = 18;
			break;
		case CLEAVE:
			c_card[number].attack = 11;
			break;
		case CLOTHESLINE:
			c_card[number].attack = 14;
			c_card[number].weak = 3;
			break;
		
		case HEADBUTT:
			c_card[number].attack = 12;
			break;
		case HEAVY_BLADE: //Strength affects Heavy Blade 3(5) times.
			
			break;
		case IRON_WAVE:
			c_card[number].attack = 7;
			c_card[number].block = 7;
			break;
		case POMMEL_STRIKE:
			c_card[number].attack = 10;
			c_card[number].draw = 2;
			break;
		case SHRUG_IT_OFF:
			c_card[number].block = 11;
			break;
		case SWORD_BOOMERANG:
			c_card[number].attack = 12;
			break;
		case THUNDERCLAP:
			c_card[number].attack = 7;
			break;
		case TRUE_GRIT:
			c_card[number].block = 10;
			break;
		case TWIN_STRIKE:
			c_card[number].attack = 14;
			break;
		case BATTLE_TRANCE:
			c_card[number].draw = 3;
			break;
		case BLOODLETTING:
			//gain 3 energy
			break;
		case BURNING_PACT:
			c_card[number].draw = 3;
			break;
		case CARNAGE:
			c_card[number].attack = 28;
			break;
		case DARK_EMBRACE:
			c_card[number].consume = 5;
			break;
		case DISARM:
			c_card[number].strength = -3;
			break;
		
		case ENTRENCH:
			c_card[number].energy_cost = 1;
			break;
		
		case GHOSTY_ARMOR:
			c_card[number].block = 13;
			break;
		case HEMOKINESIS:
			c_card[number].attack = 20;
			break;
		case INFLAME:
			c_card[number].strength = 3;
			break;
		case INTIMIDATE:
			c_card[number].weak = 12;
			break;
		case POWER_THROUGH:
			c_card[number].block = 20;
			break;
		case RAMPAGE:
			//increase damage by 8
			break;
		case SECOND_WIND:
			c_card[number].block = 7;
			break;
		case SEEING_RED:
			c_card[number].energy_cost = 0;
			break;
		
		case SEVER_SOUL:
			c_card[number].attack = 22;
			break;
		case SHOCKWAVE:
			c_card[number].weak = 5;
			break;
		case SPOT_WEAKNESS:
			c_card[number].strength = 4;
			break;
		case UPPERCUT:
			c_card[number].weak = 2;
			c_card[number].vulnerable = 2;
			break;
		
		case BLUDGEN:
			c_card[number].attack = 42;
			break;
		
		case FEED:
			c_card[number].attack = 12;
			break;
		case FIEND_FIRE:
			c_card[number].attack = 10;
			break;
		case IMMOLATE:
			c_card[number].attack = 28;
			break;
		case IMPERVIOUS:
			c_card[number].block = 40;
			break;
		case OFFERING:
			c_card[number].draw = 5;
			break;
		case REAPER:
			c_card[number].attack = 5;
			break;
			//silent
		case NEUTRALIZE:
			c_card[number].attack = 4;
			c_card[number].weak = 2;
			break;
		case SURVIVOR:
			c_card[number].block = 11;
			break;
		case ACROBATICS:
			c_card[number].draw = 4;
			break;
		case BACKFLIP:
			c_card[number].block = 8;
			break;
		case BANE:
			c_card[number].attack = 10;
			break;
		case DAGGER_SPRAY:
			c_card[number].attack = 6;
			break;
		case DAGGER_THROW:
			c_card[number].attack = 12;
			break;
		case DEADLY_POISON:
			c_card[number].poison = 7;
			break;
		case DEFLECT:
			c_card[number].block = 7;
			break;
		case POISONED_STAB:
			c_card[number].attack = 8;
			c_card[number].poison = 4;
			break;
		case PREPARED:
			c_card[number].draw = 2;
			c_card[number].discard = 2;
			break;
		case QUICK_SLASH:
			c_card[number].attack = 12;
			break;
		case SLICE:
			c_card[number].attack = 9;
			break;
		case SUCKER_PUNCH:
			c_card[number].attack = 9;
			c_card[number].weak = 2;
			break;
		case BACKSTAB:
			c_card[number].attack = 15; 
			break;
		case POISON_EXTRACT:
			c_card[number].energy_cost = 1;
			break;
		case BOUNCING_FLASK:
			c_card[number].poison = 12;
			break;
		case CALCULATED_GAMBLE:
			c_card[number].usage = 1;
			break;
		case CATALYST:
			//triple the poison
			break;
		case CONCENTRATE:
			c_card[number].discard = 2;
			break;
		case CRIPPLING_CLOUD:
			c_card[number].poison = 7;
			break;
		case DASH:
			c_card[number].block = 13;
			break;
		
		case EXPERTISE:
			c_card[number].energy_cost = 1;
			break;
	
		case LEG_SWEEP:
			c_card[number].weak = 3;
			c_card[number].block = 14;
			break;
		case REFLEX:
			break;
		case RIDDLE_WITH_HOLES:
			c_card[number].attack = 20;
			break;
		
		case TACTICIAN:
			//gain 2 energy
			break;
		case TERROR:
			c_card[number].energy_cost = 0;
			break;
		case ADRENALINE:
			//gain 2 energy
			break;
		
		case CORPSE_EXPLOSION:
			c_card[number].attack = 20;
			break;
		case DIE_DIE_DIE:
			c_card[number].attack = 17;
			break;
		case GLASS_KNIFE:
			c_card[number].attack = 24;
			break;
		case GRAND_FINALE:
			c_card[number].attack = 60;
			break;
		
		case UNLOAD:
			c_card[number].attack = 18;
			break;
			
	}

}

void changedCardState(int number, int card_state)
{
	g_card[number].card_state = card_state;
}

