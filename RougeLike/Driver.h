#include "Player.h"
#include "Item.h"
#include <vector>
#include "tilelib.h"
#include "Cell.h"
#include <Windows.h>
#include <iostream>
#include <cstdlib>

using namespace std;

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
	// vector current locations of objects
	vector< Item > Items;
	// vector current locations of enemies
	vector< Creature> Enemies;
	// player's location and stats
	Player Player1;

	void update();
	void draw();
	void BuildWorld();
	void splash(int x, int y, int rec);
	void link();
	void flood();
	void corridorLink(int me_x, int me_y, int target_x, int target_y);


};
	