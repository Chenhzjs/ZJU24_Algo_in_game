#include <stdio.h>
#include "interface.h"
#include "character.h"
int Main()
{
	srand((unsigned)time(NULL));
	relic_n = 21;
	initCharacter();
	initEnemy();
	initCard();
	initInterface();
	return 0;
}

