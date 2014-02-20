#pragma once

#include "coordinate.h"
#include <string>

using namespace std;

class Actor{
	
public:
	coordinate location;

	//getters
	int getHealth();
	int getMana();
	int getDamageDie();
	int getDamageMulti();
	int getDef();
	int getTile();

	//is it alive?
	bool isAlive();

	//set up creature
	void birth(int, int, int, int, int, int, string);

private:


	//stat block
	int health;
	int mana;
	int damagDie;
	int damageMulti;
	int def;
	int tile;
	string name;
	
};