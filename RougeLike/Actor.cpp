#include "Actor.h"


int Actor::getHealth(){
	return health;
}
int Actor::getMana(){
	return mana;
}
int Actor::getDamageDie(){
	return damagDie;
	}
int Actor::getDamageMulti(){
	return damageMulti;
}
int Actor::getDef(){
	return def;
}
int Actor::getTile(){
	return tile;
}

//is it alive?
bool Actor::isAlive(){
	if(health > 0){
		return true;
	}else{
		return false;
	}
}

//set up creature
void Actor::birth(int health_, int mana_ , int damage_ , int multi_ , int def_, int tile_, string name_){
	health = health_;
	mana = mana_;
	damagDie = damage_;
	damageMulti = multi_;
	def= def_;
	tile = tile_;
	name = name_;

}