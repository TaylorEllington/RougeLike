#include "Entity.h"
#include <cstdlib>
class Item: Entity
{
public:
	int getRemaingUses();
	int getTile();
	int getBoostDamage();
	int getBoostMulti();
	void rollItem();
	int getItemType();
	
private:
	void roll();
	int uses;
	int tile;
	int boostDamage;
	int boostMulti;
	bool setup;
	int type;
};

