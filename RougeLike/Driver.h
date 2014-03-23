
#include <vector>
#include "levelMap.h"
#include "tilelib.h"
#include "Coordinate.h"
#include "Cell.h"
#include "Actor.h"
#include "actorManager.h"
#include <Windows.h>
#include <iostream>
#include <cstdlib>




class Driver{

public:
	Driver();
	void run();
	

private:
	int tile_count_X;
	int tile_count_Y;
	//drawer object
	// array[][] current level map
	Cell** map;
	levelMap Map;
	// vector current locations of objects
	//vector< Item > Items;
	// vector current locations of enemies
	actorManager ActorManager;
	// player's location and stats
	//Actor Player;


	void update();
	void draw();
	void BuildWorld();
	void splash(int x, int y, int rec);
	void link();
	void flood();
	void drawLog();
	void corridorLink(int me_x, int me_y, int target_x, int target_y);



};
	