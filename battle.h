#ifndef _BATTLE_H_
#define _BATTLE_H_
enum {
	NORMAL_BATTLE = 0,
	HARD_BATTLE,
	BOSS_BATTLE,
	REST,
	SHOP,
	TREASURE,
	EVENT
};
enum {
	ENEMY_ATTACK = 0,
	ENEMY_BLOCK,
	ENEMY_STRENGTH,
	ENEMY_HEAL,
	ENEMY_VULNERABLE,
	ENEMY_WEAK,
	ENEMY_FRAIL,
	ENEMY_UNKNOWN,
};
char trans[10];

static void DrawBotton();

static void DrawCardType(double x, double y, int number);

static void DrawCard();

static void DrawEnemy(int number);

static void DrawEnemyAct(double x, double y, int number);

void DrawDetailedCard(int number);

static void DrawBattleRound(int battle_round);

void showCharacterState();

void showEnemyState(int number);

void DrawCharacter(int x, int y);

void chooseCard();

static void getRandomEnemyAct(int number);

void erasePreviousEnemyState(int number);

void erasePreviousCharacterState();

static void enemyActing(int number);

void useCard(int number);

void discardCard(int total);
 
void consumeCard(int total);

void battleEvent(int type);

void battleInterface();

void integerToString(int number);

#endif 
