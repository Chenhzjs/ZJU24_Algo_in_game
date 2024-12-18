#ifndef _CARD_H_
#define _CARD_H_

int cards_number;
int total_cards_number;
int drawn, handn, discardn, consumedn;
enum CARD_STATE
{
	DRAW = 0, HAND, DISCARD, CONSUMED
};
enum CARD_TYPE
{ 
	ATTACK = 0, SKILL, POWER, STATUS, CURSE
};
enum CARD_CONFIRM
{
	CONFIRM = 1, NOT_CONFIRM = 0
};
enum CARD_RARITY
{
	STARTER = 0, COMMON, UNCOMMON, RARE 
};
enum CARD_ID
{
	STRIKE = 0, //Deal 6(9) damage.
	DEFEND, //Gain 5(8) Block.
	/*IRONCLAD  43*/ 
	BASH, //Deal 8(10) damage. Apply 2(3) Vulnerable.
	ANGER, //Deal 6(8) damage. Increase this card's damage by 1(2) this battle.
		BODY_SLAM, // Deal damage equal to your current Block
		CLASH, // Can only be played if every card in your hand is an Attack. Deal 14(18) damage.
	CLEAVE, //Deal 8(11) damage to ALL enemies.
	CLOTHESLINE, //Deal 12(14) damage. Apply 2(3) Icon Weak 
//		FLEX, //Gain 2(4) Icon Strength.At the end of your turn, lose 2(4) Strength
//		HAVOC, //Play the top card of your draw pile and Exhaust it.
	HEADBUTT, //Deal 9(12) damage. Get an card from the draw pile.
		HEAVY_BLADE, //Deal 14 damage.  Strength affects Heavy Blade 3(5) times.
	IRON_WAVE, //Gain 5(7) Block.Deal 5(7) damage.
	POMMEL_STRIKE, //Deal 9(10) damage. Draw 1(2) card(s).
	SHRUG_IT_OFF, //Gain 8(11) Icon Block. Draw 1 card.
	SWORD_BOOMERANG, //Deal 4(6) damage to all enemy.
	THUNDERCLAP, //Deal 4(7) damage and apply 1 Vulnerable to ALL enemies.
	TRUE_GRIT, //Gain 7(10) Block. Exhaust a card from your hand.
	TWIN_STRIKE, //Deal 10(14) damage.
//		WARCRY, //Draw 1(2) card(s). Place a card from your hand on top of your draw pile. Exhaust.
	BATTLE_TRANCE, //Draw 2(3) cards. 
		BLOODLETTING, //Lose 3 HP. Gain 2(3) Energy
	BURNING_PACT, //Exhaust 1 card. Draw 2(3) cards.
	CARNAGE, //Exhausted. Deal 20(28) damage.
		DARK_EMBRACE, //consume 3(5) cards, draw 2 card.
	DISARM, //Enemy loses 2(3) Strength. Exhaust.
//		DROPKICK, //Deal 5(8) damage. If the enemy is Icon Vulnerable, gain 1 energy and draw 1 card.
		ENTRENCH, //Double your current Block.
//		FEEL_NO_PAIN, //Whenever a card is Exhausted, gain 3(4) Block.
	GHOSTY_ARMOR, //Consumed. Gain 10(13) Block.
		HEMOKINESIS, //Lose 2 HP. Deal 15(20) damage.
	INFLAME, //Gain 2(3) Strength
	INTIMIDATE, //Apply 1(2) Weak to ALL enemies. Exhaust.
		POWER_THROUGH, //Lose 2 Health. Gain 15(20) Block.
		RAMPAGE, //Deal 8 damage. Increase this card's damage by 5(8) this combat.
		SECOND_WIND, //Exhaust all non-Attack cards in your hand and gain 5(7) Block for each card Exhausted.
		SEEING_RED, //Gain 2 energy. Exhaust.
//		SENTINEL, //Gain 5(8) Block. If this card is Exhausted, gain 2(3) energy.
		SEVER_SOUL, //Exhaust all non-Attack cards in your hand. Deal 16(22) damage.
	SHOCKWAVE, //Apply 3(5) Weak and Vulnerable Vulnerable to ALL enemies.Exhaust.
		SPOT_WEAKNESS, //If the enemy intends to attack, gain 3(4) Strength.
	UPPERCUT, //Deal 13 damage. Apply 1(2) Weak. Apply 1(2) Vulnerable.
//		BERSERK, //Gain 2(1) Icon Vulnerable. At the start of your turn, gain 1 Energy.
	BLUDGEN, //Deal 32(42) damage
//		EXHUME, //Put a card from your Exhaust pile into your hand. Exhaust.
		FEED, //Deal 10(12) damage. If this kills a non-minion enemy, gain 3(4) permanent Max HP. Exhaust.
		FIEND_FIRE, //Exhaust all cards in your hand. Deal 7(10) damage for each Exhausted card. Exhaust.
	IMMOLATE, //Deal 21(28) damage to ALL enemies.
	IMPERVIOUS, //Gain 30(40) Block. Exhaust.
		LIMIT_BREAK, //Double your Strength Strength. Exhaust(Don't Exhaust).
		OFFERING, //Lose 6 HP. Gain 2 energy. Draw 3(5) cards. Exhaust.
		REAPER, //Deal 4(5) damage to ALL enemies. Heal Health equal to Attack. Exhaust.
	/*SILENTER 34*/
	NEUTRALIZE, //Deal 3(4) damage. Apply 1(2) Weak 
	SURVIVOR, //Gain 8(11) Block. Discard a card.
	ACROBATICS, //Draw 3(4) cards. Discard 1 card.
	BACKFLIP, //Gain 5(8) Block. Draw 2 cards
		BANE, //Deal 7(10) damage. If the enemy is Poisoned, deal 7(10) damage again.
	DAGGER_SPRAY, //Deal 4(6) damage to ALL enemies twice.
	DAGGER_THROW, //Deal 9(12) damage. Draw 1 card. Discard 1 card.
	DEADLY_POISON, //Apply 5(7) Poison.
	DEFLECT, //Gain 4(7) Block.
	POISONED_STAB, //Deal 6(8) damage. Apply 3(4) Poison.
	PREPARED, //Draw 1(2) card(s). Discard 1(2) card(s).
	QUICK_SLASH, //Deal 8(12) damage. Draw 1 card.
	SLICE, //Deal 6(9) damage.
	SUCKER_PUNCH, //Deal 7(9) damage. Apply 1(2) Weak.
	BACKSTAB, //Deal 11(15) damage. Exhaust.
		POISON_EXTRACT, //gain Block equal to a enemy's Poison
	BOUNCING_FLASK, //Apply 3 Poison to a random enemy 3(4) times.
		CALCULATED_GAMBLE, //Discard your hand, then draw that many cards. Exhaust. (Don't exhaust)
		CATALYST, //Double(Triple) an enemy's Poison. Exhaust.
		CONCENTRATE, //Discard 3(2) cards. Gain 2 Energy.
	CRIPPLING_CLOUD, //Apply 4(7) Poison and 2 Icon Weak Weak to ALL enemies. Exhaust.
	DASH, //Gain 10(13) Block. Deal 10(13) damage.
//		ESCAPE_PLAN, //Draw 1 card. If you draw a Skill, gain 3(5) Block.
		EXPERTISE, //Draw cards until you have 10 cards in your hand. 2(1) energy cost
//		FLECHETTES, //Deal 4(6) damage for each Skill in your hand.
//		HEEL_HOOK, //Deal 5(8) damage. If the enemy is Weak, Gain 1 Energy and draw 1 card.
	LEG_SWEEP, //Apply 2(3) Weak. Gain 11(14) Block.
	REFLEX, //Unplayable. If this card is discarded from your hand, draw 2(3) cards.
	RIDDLE_WITH_HOLES, //Deal 3(4) damage 5 times.
//		SKEWER, //Deal 7(10) damage X times.
		TACTICIAN, // Unplayable. If this card is discarded from your hand, gain 1(2) Energy.
	TERROR, //Apply 99 Icon Vulnerable Vulnerable. Exhaust.
		ADRENALINE, //Gain 1(2) Energy. Draw 2 cards. Exhaust.
//		AFTER_IMAGE, //(Innate.)Whenever you play a card, gain 1 Block.
		CORPSE_EXPLOSION, //cause 15 Attack, When the enemy was Killed, cause Attack equal to its max Health to ALL enemies.
	DIE_DIE_DIE, //Deal 13(17) damage to ALL enemies. Exhaust.
		GLASS_KNIFE, //Deal 16(24) Attack. Decrease the damage of this card by 4 this combat.
		GRAND_FINALE, //Can only be played if there are no cards in your draw pile. Deal 50(60) damage to ALL enemies.
//		MALAISE, //Enemy loses X(+1) Strength. Apply X(+1) Icon Weak Weak. Exhaust.
	UNLOAD, //Deal 14(18) damage.
};
struct CARD
{
	char name[20];
	int number;
	int usage; // 只能用一次的卡 -1， 其他的卡 1 不能打出的牌 0 
	int id;
	int energy_cost; //negetive: lose energy;   positive: gain energy;
	int upgrade;
	int attack;
	int block;
	int strength;
	int poison;
	int vulnerable;
	int weak;
	int type;
	int rarity;
	int draw;
	int discard;
	int consume; // 任意 -1， 不消耗 0， 消耗n n 
	int card_state;
	int confirm;
	char discription1[100];
	char discription2[100];
}card[205], c_card[205], g_card[205];
int hand[10];
void getRandomCard(int n);
void initCard();
void gameCard();
void getCard(int id);

void loseCard(int id);


void upgradeCard(int number);

void changedCardState(int number, int card_state);

void shuffleCards();
#endif
