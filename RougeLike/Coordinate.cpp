#include "coordinate.h"

coordinate::coordinate(){};

coordinate::coordinate(int start_x_coord, int start_y_coord){
	x= start_x_coord;
	y= start_y_coord;
	//max_X= max_x_coord;
	//max_Y= max_y_coord;
}
void coordinate::up(){

    y--;
}
void coordinate::down(){
	y++;
}

void coordinate::left(){
	x--;
}
void coordinate::right(){
    x++;
}
int coordinate::get_x(){
	return x;
}
int coordinate::get_y(){
	return y;
}
void coordinate::teleport(int new_x, int new_y){
	x= new_x;
	y= new_y;
}
void coordinate::teleport(coordinate new_coord){


	teleport(new_coord.get_x(), new_coord.get_y());

}




