#include "levelMap.h"
coordinate levelMap::setup(int x_size, int y_size, int roomCount){
	number_of_rooms =(roomCount);
	
	x_dim = x_size;
	y_dim = y_size;
	Map = new Cell*[ y_size ];

	for(int y= 0; y < y_size; y++){
	    Map[y] = new Cell[ x_size ];
		for(int x = 0; x < x_size; x++){
			Map[y][x].Floor = 0x000;
		}
	}
	return (levelGen());
}

int levelMap::get_tile(int x, int y){
	if(x >= 0 && x < x_dim && y >= 0 && y < y_dim){
	    return Map[y][x].Floor;
	}else{
		return 0x000;
	}

}
int levelMap::get_x_dim(){
	return x_dim;
}
int levelMap::get_y_dim(){
	return y_dim;
}
bool levelMap::can_step(int x, int y){
	if(get_tile(x, y) == 0x128  && Map[y][x].Occupied != true){
		return true;
	}else{
		return false;
	}
}
levelMap::~levelMap(){
}
coordinate levelMap::levelGen(){
	//number_of_rooms =  new int(20);  //CHANGE TO ADD ROOMS
	x = new int[number_of_rooms];
	y = new int[number_of_rooms];

	//pick center of rooms
	for( int a = 0; a < number_of_rooms; a++){

		x[a] = (rand() % (x_dim - 6)) + 3;

		y[a] = (rand() % (x_dim - 6)) + 3;

	}
	//splash rooms
	for( int a = 0; a < number_of_rooms; a++){
	
		Map[y[a]][x[a]].Floor = 0x101;


	}
	for (int b = 0; b <number_of_rooms; b++){
		splash(x[b] , y[b], 5);
		
	}
	//connect rooms

		corridorLink(x[0], y[0], x[1], y[1]);
		for(int g = 1; g< number_of_rooms; g++){
			corridorLink(x[g-1], y[g-1], x[g], y[g]);
		}
		
		return( coordinate(x[0], y[0]) );

}
void levelMap::corridorLink(int me_x, int me_y, int target_x, int target_y){

	Map[me_y][me_x].Floor= 0x128;

	if(me_x == target_x){

		//ensure walls are bounded
		if(Map[me_y+1][me_x+1].Floor == 0x000){
				Map[me_y+1][me_x+1].Floor = 0x129;
		}
		if(Map[me_y-1][me_x+1].Floor == 0x000){
				Map[me_y-1][me_x+1].Floor = 0x129;
		}

		if(Map[me_y-1][me_x-1].Floor == 0x000){
				Map[me_y-1][me_x-1].Floor = 0x129;
		}
		if(Map[me_y+1][me_x-1].Floor == 0x000){
				Map[me_y+1][me_x-1].Floor = 0x129;
		}

		if(me_y == target_y){
		//done
		}else if(me_y > target_y){
			//ensure walls are bounded
			if(Map[me_y-1][me_x+1].Floor == 0x000){
				Map[me_y-1][me_x+1].Floor = 0x129;
			}
			if(Map[me_y-1][me_x-1].Floor == 0x000){
				Map[me_y-1][me_x-1].Floor = 0x129;
			}
			//recurse
			corridorLink(me_x, me_y-1, target_x, target_y);

		}else if(me_y < target_y){
			//ensure walls are bounded
			if(Map[me_y+1][me_x+1].Floor == 0x000){
				Map[me_y+1][me_x+1].Floor = 0x129;
			}
			if(Map[me_y+1][me_x-1].Floor == 0x000){
				Map[me_y+1][me_x-1].Floor = 0x129;
			}
			//recurse
			corridorLink(me_x , me_y+1, target_x, target_y);
		}

	}else if(me_x > target_x){

		//ensure walls are bounded
		if(Map[me_y-1][me_x-1].Floor == 0x000){
			Map[me_y-1][me_x-1].Floor = 0x129;
		}
		if(Map[me_y+1][me_x-1].Floor == 0x000){
			Map[me_y+1][me_x-1].Floor = 0x129;
		}
		//recurse
		corridorLink(me_x-1, me_y, target_x, target_y);

	}else if(me_x < target_x){
		if(Map[me_y-1][me_x+1].Floor == 0x000){
			Map[me_y-1][me_x+1].Floor = 0x129;
		}
		if(Map[me_y+1][me_x+1].Floor == 0x000){
			Map[me_y+1][me_x+1].Floor = 0x129;
		}

		corridorLink(me_x+1 , me_y, target_x, target_y);
	}
		

}
void levelMap::splash(int x, int y, int rec){
	if( x > 0 && x < (x_dim-1) && y > 0 && y < (y_dim-1) && rec > 0){
		if( Map[y][x].Floor != 0x128){
		     Map[y][x].Floor = 0x128;
		}

		 
			splash(x+1 , y+1 , rec-1 );
			splash(x , y+1 , rec-1 );
			splash(x-1 , y+1 , rec-1 );

			splash(x-1 , y , rec-1 );
			splash(x+1 , y , rec-1 );

			splash(x+1 , y-1 , rec-1 );
			splash(x , y-1 , rec-1 );
			splash(x-1 , y-1 , rec-1 );


	} else if ( x == 0 || x == (x_dim-1) || y == 0 || y == (y_dim-1) || rec == 0){

			if( Map[y][x].Floor != 0x128){
		     Map[y][x].Floor = 0x129;
		}
	}

}
int levelMap::getRoomX(int index){
	return x[ (index % number_of_rooms)];

}
int levelMap::getRoomY(int index){
	return y[ (index % number_of_rooms)];
}
int levelMap::getNumberOfRooms(){
	return number_of_rooms;
}
void levelMap::setOccupied(int x, int y, bool status){
	Map[y][x].Occupied= status;
}
bool levelMap::isOccupied(int x, int y){

	return Map[y][x].Occupied;
}
