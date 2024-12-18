#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#define MAX 105
enum CSTATE
{
	MAX_HEALTH = 0,
	NOW_HEALTH,
	BLOCK, 
	STRENGTH,
	FRAIL,
	POISON,
	VULNERABLE,
	WEAK,
	MONEY,
	RELIC
}; 

enum CHARATER
{
	IRONCLAD = 0,
	SILENTER = 1
};
enum ENEMY
{
	LITTLE_SLIM = 0, 
	HARD_SLIM, 
	BOSS_SLIM,
	LOUSE, 
	CULTIST, 
	GREMLIN_NOB,
    SENTRY, 
	NEMESIS,
	LAGAVULIN, 
    TIME_EATER, 
	THE_MAW,
    HEXAGHOST
};
enum RELICS
{
	RELIC_0 = 1,     /*Burning Blood 在战斗结束时，回复6点生命。*/
	RELIC_1,     /* Ring of the Snake 在每场战斗开始时，额外抽 2 张牌。*/
	RELIC_2,     /*Blood Vial 在每场战斗开始时，回复 2 点生命。*/
	RELIC_3,     /* Centennial Puzzle   你在每场战斗中第一次损伤生命时，抽 3 张牌。*/
	RELIC_4,	 /*Dream Catcher 每当你 休息 时，可以增加一张牌到你的牌组。*/
	RELIC_5,	 /* Lantern 在每场战斗的第一回合获得一点能量。*/
	RELIC_6,	 /*Orichalcum 如果你在回合结束时没有任何 格挡 ，获得 6点 格挡。*/
	RELIC_7,	 /* Red Skull 当你的生命值等于或低于 50% 时， 你获得额外 3点 力量。*/
	RELIC_8,	 /*Regal Pillow 在 休息 时额外回复 15 点生命。*/
	RELIC_9,	 /*Smiling Mask 商人的卡牌移除服务现在价格永远是 50 金币。*/
	RELIC_10,	 /*Snake Skull 每当你给予敌人 中毒 状态时，额外给予 1层 中毒*/
	RELIC_11,	 /*Strawberry  拾起时，将你的最大生命值提升 7.*/
	RELIC_12,	 /*Meal Ticket 每当你进入商店房间时，回复 15 点生命*/
	RELIC_13,    /*Anchor 每场战斗开始时获得 10点 格挡*/
	RELIC_14,    /*Pear 拾起时，将你的最大生命值提升15*/
	RELIC_15,    /* Calipers 在你的回合开始时，不再失去所有 格挡 ，而是失去 15 点 格挡 。*/
	RELIC_16,    /*Old Coin 拾起时，获得 300 金币*/
	RELIC_17,    /*Philosopher's Stone 在每回合开始时获得一点能量。所有敌人初始获得 1点 力量。*/
	RELIC_18,    /* Ectoplasm 你不能再获得任何 金币 。在回合开始时获得一点能量。*/
	RELIC_19,    /*Tiny House 拾起时。 获得 100 金币 。  将你的最大生命值提升 10。 力量+2；*/
};
enum ENEMY_TYPE
{
	NORMAL, HARD, BOSS
};
struct CHARATER_STATE
{

	int max_health;
	int now_health; 
	int block;
	int strength;
	int poison;
	int vulnerable;
	int frail;
	int weak;
	int relic_num;
	int money;
	int enemy_type;
	int id;
	struct CHARATER_STATE *next;

}the_character[5], the_enemy[100], *now_enemy[5], *now_character;
char inscribe_relics[25][100];
int state_character;
int relics[MAX];
int relic_n;
int now_enemy_n;
int max_energy;
int now_energy;

void initCharacter();//角色初始化属性 
void initEnemy();
void initNowEnemy(int layer, int enemy_type);
void initNowCharacter(int id);
void changeState(int type, int pos, int state, int number);

void changeRelic(int boolean, int index);// boolean = 0: 丢弃; boolean = 1: 获得 

void freeEnemy(int n);
void freeCharacter();
void getStoredState();
void init_relics();
void storeState(int n);
#undef MAX
#endif
