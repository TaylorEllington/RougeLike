#include "Item.h"


int Item::getRemaingUses(){
	return uses;
}
int Item::getTile(){
	return tile;
}
int Item::getBoostDamage(){
	return boostDamage;
}
int Item::getBoostMulti(){
	return boostMulti;
}
void Item::rollItem(){
	//only allow item to be created once
	if(setup != true){
		setup = true;
		uses = rand() %100;
		boostDamage = rand() % 50;
		type = rand() % 3;
		
			tile=0x254; //weapon
		
		

	}
}