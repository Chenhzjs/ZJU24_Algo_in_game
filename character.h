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
	RELIC_0 = 1,     /*Burning Blood ��ս������ʱ���ظ�6��������*/
	RELIC_1,     /* Ring of the Snake ��ÿ��ս����ʼʱ������� 2 ���ơ�*/
	RELIC_2,     /*Blood Vial ��ÿ��ս����ʼʱ���ظ� 2 ��������*/
	RELIC_3,     /* Centennial Puzzle   ����ÿ��ս���е�һ����������ʱ���� 3 ���ơ�*/
	RELIC_4,	 /*Dream Catcher ÿ���� ��Ϣ ʱ����������һ���Ƶ�������顣*/
	RELIC_5,	 /* Lantern ��ÿ��ս���ĵ�һ�غϻ��һ��������*/
	RELIC_6,	 /*Orichalcum ������ڻغϽ���ʱû���κ� �� ����� 6�� �񵲡�*/
	RELIC_7,	 /* Red Skull ���������ֵ���ڻ���� 50% ʱ�� ���ö��� 3�� ������*/
	RELIC_8,	 /*Regal Pillow �� ��Ϣ ʱ����ظ� 15 ��������*/
	RELIC_9,	 /*Smiling Mask ���˵Ŀ����Ƴ��������ڼ۸���Զ�� 50 ��ҡ�*/
	RELIC_10,	 /*Snake Skull ÿ���������� �ж� ״̬ʱ��������� 1�� �ж�*/
	RELIC_11,	 /*Strawberry  ʰ��ʱ��������������ֵ���� 7.*/
	RELIC_12,	 /*Meal Ticket ÿ��������̵귿��ʱ���ظ� 15 ������*/
	RELIC_13,    /*Anchor ÿ��ս����ʼʱ��� 10�� ��*/
	RELIC_14,    /*Pear ʰ��ʱ��������������ֵ����15*/
	RELIC_15,    /* Calipers ����ĻغϿ�ʼʱ������ʧȥ���� �� ������ʧȥ 15 �� �� ��*/
	RELIC_16,    /*Old Coin ʰ��ʱ����� 300 ���*/
	RELIC_17,    /*Philosopher's Stone ��ÿ�غϿ�ʼʱ���һ�����������е��˳�ʼ��� 1�� ������*/
	RELIC_18,    /* Ectoplasm �㲻���ٻ���κ� ��� ���ڻغϿ�ʼʱ���һ��������*/
	RELIC_19,    /*Tiny House ʰ��ʱ�� ��� 100 ��� ��  ������������ֵ���� 10�� ����+2��*/
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

void initCharacter();//��ɫ��ʼ������ 
void initEnemy();
void initNowEnemy(int layer, int enemy_type);
void initNowCharacter(int id);
void changeState(int type, int pos, int state, int number);

void changeRelic(int boolean, int index);// boolean = 0: ����; boolean = 1: ��� 

void freeEnemy(int n);
void freeCharacter();
void getStoredState();
void init_relics();
void storeState(int n);
#undef MAX
#endif
