#include "actorManager.h"


	void actorManager::fight(int atkr, int defr){
		Actor* attacker;
		Actor* defender;

		if(atkr == -1){
			attacker = &Player;

		
		}else {
			attacker = &enemies[atkr];
		}
		if(defr == -1){
			defender = &Player;
		} else {
			defender = &enemies[defr];
		}

		
		if(defr>=0 && defr< enemies.size() ){
			defender = &enemies[defr];
		}

		int damage;
		int def;

		
		damage = rand() % attacker->getDamageDie() ;
		damage = damage * attacker->getDamageMulti();

		def = defender->getDef();

		defender->doDamage(damage-def);

		


	}
	bool actorManager::isAlive(int index){
		if( enemies[index].getHealth() > 0){
			return true;
		}else{
			return false;
		}
	}
	bool actorManager::isPlayerAlive(){

		if( Player.getHealth() > 0){
			return true;
		}else{
			return false;
		}
	}
	int actorManager::rangeToPlayer(int index){
		int x = Player.location.get_x() - enemies[index].location.get_x();
		int y = Player.location.get_y() - enemies[index].location.get_y();

		int total =(int) sqrt((double)((x*x) + (y*y)));

		return total;
	}
	int actorManager::whoIsAt(int x, int y){
		int itsMe = -1;
		for(int a= 0;a < enemies.size(); a++){
			if(enemies[a].location.get_x() == x && enemies[a].location.get_y() == y){
				itsMe = a;
			}
		}
		return itsMe;
		

	}
	int actorManager::whatIsAt(int x, int y){
		int itsMe = -1;
		
		for(int a= 0;a <loot.size() ; a++){
			if(loot[a].location.get_x() == x && loot[a].location.get_y() == y){
				itsMe = a;
			}
		}
		return itsMe;
		

	}
	void actorManager::pickUp(int index){
		if (index > -1){
		Item temp;
		temp = loot[index];
		loot.erase(loot.begin() + index);
		inventory.push_back(temp);
		}
	}