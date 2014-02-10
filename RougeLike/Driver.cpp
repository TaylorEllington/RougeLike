
#include "Driver.h"


Driver::Driver(){

	int x_dim = 1500;
	int y_dim = 800;

	tile_count_X = 47;
	tile_count_Y =25;

	tl_init("title", x_dim ,y_dim,"tiles", 32,3);

	int x_pos = 0;
	int y_pos = 0;
	int temp=0;

	BuildWorld();
}

void Driver::draw(){
for(int y= 0; y < tile_count_Y; y++){
	   
		for(int x = 0; x < tile_count_X; x++){
			tl_rendertile(map[y][x].Floor, x, y);
		}
	}

}

void Driver::update(){


}



void Driver::run(){
	int x_dim = 800;
	int y_dim = 600;
	int y_pos =1;
	int x_pos = 1;

		for(;;){

		//process user input
		//update game state
		//draw

		
		tl_framestart(0);
		draw();
		tl_rendertile( '@' ,y_pos,x_pos);
		if(tl_keywentdown("escape")){
			break;
		} 
		if (tl_keywentdown("down")){
			x_pos++;
		}
		if (tl_keywentdown("up")){
			x_pos--;
		}
		if (tl_keywentdown("left")){
			y_pos--;
		}
		if (tl_keywentdown("right")){
			y_pos++;
		}
		
		
    }
}


void Driver::BuildWorld(){
	map = new Cell*[ tile_count_Y];
	int number_of_rooms = 11;
	int x[11];
	int y[11];

	//makes grass
	for(int y= 0; y < tile_count_Y; y++){
	    map[y] = new Cell[tile_count_X];
		for(int x = 0; x < tile_count_X; x++){
			map[y][x].Floor = 0x000;
		}
	}
	
	//pick center of rooms
	for( int a = 0; a < number_of_rooms; a++){
	
		x[a] = (rand() % (tile_count_X - 4)) + 2;
		y[a] = (rand() % (tile_count_Y - 6)) + 3;

	}
	//splash rooms
	for( int a = 0; a < number_of_rooms; a++){
	
		map[y[a]][x[a]].Floor = 0x101;

	}
	for (int b = 0; b <number_of_rooms; b++){
		splash(x[b] , y[b], 5);
		
	}
	//connect rooms
	//flood fill



}

void Driver::splash(int x, int y, int rec){
	if( x > 0 && x < (tile_count_X-1) && y > 0 && y < (tile_count_Y-1) && rec > 0){
		if( map[y][x].Floor != 0x128){
		     map[y][x].Floor = 0x128;
		}

		 
			splash(x+1 , y+1 , rec-1 );
			splash(x , y+1 , rec-1 );
			splash(x-1 , y+1 , rec-1 );

			splash(x-1 , y , rec-1 );
			splash(x+1 , y , rec-1 );

			splash(x+1 , y-1 , rec-1 );
			splash(x , y-1 , rec-1 );
			splash(x-1 , y-1 , rec-1 );


	} else if ( x == 0 || x == (tile_count_X-1) || y == 0 || y == (tile_count_Y-1) || rec == 0){

			if( map[y][x].Floor != 0x128){
		     map[y][x].Floor = 0x129;
		}
	}

}


