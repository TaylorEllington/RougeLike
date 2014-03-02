#pragma once
#include "levelMap.h";
#include "Actor.h"
#include "Player.h"
#include <vector>
using namespace std;

class actorManager{
public:
	


	vector<Actor> enemies;
	Actor Player;

	void fight(int atkr, int defr);
	bool isAlive(int index);
	bool isPlayerAlive();
	int rangeToPlayer(int index);
	int whoIsAt(int x, int y);



private:
	bool inRange();


};