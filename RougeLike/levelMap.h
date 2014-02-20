#pragma once
#include "Cell.h"
#include <iostream>
#include "Coordinate.h"
#include <cstdlib>

enum Tile{};

class levelMap{
public:
	//levelMap();
	//levelMap(int x_size, int y_size);

	coordinate setup(int, int ,int);

	int get_tile(int x, int y);
	int get_x_dim();
	int get_y_dim();
	bool can_step(int x, int y);
	coordinate levelGen();

	int getRoomX(int index);
	int getRoomY(int index);
	int getNumberOfRooms();

    void setOccupied(int x, int y, bool status);


	~levelMap();
private:
	Cell ** Map;
	int x_dim;
	int y_dim;
	void splash(int x, int y, int rec);
	void corridorLink(int me_x, int me_y, int target_x, int target_y);
	int  number_of_rooms;
	int * x;
	int * y;


};