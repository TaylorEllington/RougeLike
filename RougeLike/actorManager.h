#pragma once

#include "Actor.h"
#include "Player.h"
#include <vector>
using namespace std;

class actorManager{
public:
	


	vector<Actor> enemies;
	Player Player;

private:
	bool inRange();


};