
#include "Driver.h"


Driver::Driver(){

	int x_dim = 1500;
	int y_dim = 800;

	tile_count_X = 32;  //CHANGE NUMBER OF TILES
	tile_count_Y =25;   //CHANGE NUMBER OF TILES

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
	int number_of_rooms = 5;  //CHANGE TO ADD ROOMS
	int x[11];
	int y[11];

	//makes empty space
	for(int y= 0; y < tile_count_Y; y++){
	    map[y] = new Cell[tile_count_X];
		for(int x = 0; x < tile_count_X; x++){
			map[y][x].Floor = 0x000;
		}
	}
	
	//pick center of rooms
	for( int a = 0; a < number_of_rooms; a++){
	
		x[a] = (rand() % (tile_count_X - 6)) + 3;
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
		corridorLink(x[0], y[0], x[1], y[1]);
		for(int g = 1; g< number_of_rooms; g++){
			corridorLink(x[g-1], y[g-1], x[g], y[g]);
		}

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


void Driver::corridorLink(int me_x, int me_y, int target_x, int target_y){

	map[me_y][me_x].Floor= 0x128;

	if(me_x == target_x){

		//ensure walls are bounded
		if(map[me_y+1][me_x+1].Floor == 0x000){
				map[me_y+1][me_x+1].Floor = 0x129;
		}
		if(map[me_y-1][me_x+1].Floor == 0x000){
				map[me_y-1][me_x+1].Floor = 0x129;
		}

		if(map[me_y-1][me_x-1].Floor == 0x000){
				map[me_y-1][me_x-1].Floor = 0x129;
		}
		if(map[me_y+1][me_x-1].Floor == 0x000){
				map[me_y+1][me_x-1].Floor = 0x129;
		}

		if(me_y == target_y){
		//done
		}else if(me_y > target_y){
			//ensure walls are bounded
			if(map[me_y-1][me_x+1].Floor == 0x000){
				map[me_y-1][me_x+1].Floor = 0x129;
			}
			if(map[me_y-1][me_x-1].Floor == 0x000){
				map[me_y-1][me_x-1].Floor = 0x129;
			}
			//recurse
			corridorLink(me_x, me_y-1, target_x, target_y);

		}else if(me_y < target_y){
			//ensure walls are bounded
			if(map[me_y+1][me_x+1].Floor == 0x000){
				map[me_y+1][me_x+1].Floor = 0x129;
			}
			if(map[me_y+1][me_x-1].Floor == 0x000){
				map[me_y+1][me_x-1].Floor = 0x129;
			}
			//recurse
			corridorLink(me_x , me_y+1, target_x, target_y);
		}

	}else if(me_x > target_x){

		//ensure walls are bounded
		if(map[me_y-1][me_x-1].Floor == 0x000){
			map[me_y-1][me_x-1].Floor = 0x129;
		}
		if(map[me_y+1][me_x-1].Floor == 0x000){
			map[me_y+1][me_x-1].Floor = 0x129;
		}
		//recurse
		corridorLink(me_x-1, me_y, target_x, target_y);

	}else if(me_x < target_x){
		if(map[me_y-1][me_x+1].Floor == 0x000){
			map[me_y-1][me_x+1].Floor = 0x129;
		}
		if(map[me_y+1][me_x+1].Floor == 0x000){
			map[me_y+1][me_x+1].Floor = 0x129;
		}

		corridorLink(me_x+1 , me_y, target_x, target_y);
	}
		

}