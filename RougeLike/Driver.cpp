
#include "Driver.h"


Driver::Driver(){

	int x_dim = 1500;
	int y_dim = 800;

	
	tile_count_X = 40;  //CHANGE NUMBER OF TILES
	tile_count_Y =25;   //CHANGE NUMBER OF TILES


	tl_init("title", x_dim ,y_dim,"tiles", 32,3);
	
	int x_pos = 1;
	int y_pos = 1;
	int temp=0;
	BuildWorld();
}
void Driver::draw(){
	int start_x =  ActorManager.Player.location.get_x() - (tl_xres() /2);
	int start_y =  ActorManager.Player.location.get_y() - (tl_yres() /2);

	int stop_x = start_x + tl_xres();
	int stop_y = start_y + tl_yres();

	
	

	tl_framestart(0);
	for(int y= start_y; y < (Map.get_y_dim() + start_y) ; y++){
	   //draw map
		for(int x = start_x; x < (Map.get_x_dim() + start_x) ; x++){
				tl_rendertile(Map.get_tile(x, y), x - start_x , y- start_y);
			}
		}

	
	for(int a = 0; a < ActorManager.enemies.size(); a++){
		
		if( ActorManager.enemies[a].location.get_x() >= start_x && ActorManager.enemies[a].location.get_x() <= stop_x && ActorManager.enemies[a].location.get_y() >= start_y && ActorManager.enemies[a].location.get_y() <= stop_y){
			tl_rendertile( ActorManager.enemies[a].getTile() , ActorManager.enemies[a].location.get_x() - start_x , ActorManager.enemies[a].location.get_y()- start_y);
			
		}

	}
		tl_rendertile( '@' ,(tl_xres() / 2) ,(tl_yres() / 2) );


}
void Driver::update(){


}
void Driver::run(){
	int x_dim = 800;
	int y_dim = 600;
	int y_pos =1;
	int x_pos = 1;

	    //ActorManager.Player.location.teleport(3,3);
	    tl_framestart(0);
		for(;;){

		//process user input
		//update game state
		//draw

		
		//tl_framestart(0);
		draw();

		
		

		if(tl_keywentdown("escape")){
			break;
		} 
		if (tl_keywentdown("down")){
			if(   Map.can_step(ActorManager.Player.location.get_x(), ActorManager.Player.location.get_y() + 1) ) {
			    ActorManager.Player.location.down();
			}
			//x_pos++;
		}
		if (tl_keywentdown("up")){
			if(   Map.can_step(ActorManager.Player.location.get_x()   , ActorManager.Player.location.get_y() - 1 ) ) {
			     ActorManager.Player.location.up();
			}
			//x_pos--;
		}
		if (tl_keywentdown("left")){
			if(   Map.can_step(ActorManager.Player.location.get_x()-1, ActorManager.Player.location.get_y()) ) {
			     ActorManager.Player.location.left();
			}
			//y_pos--;
		}
		if (tl_keywentdown("right")){
			if(   Map.can_step(ActorManager.Player.location.get_x()+1, ActorManager.Player.location.get_y()) ) {
			     ActorManager.Player.location.right();
			}
			//y_pos++;
		}
		
		
    }
}
void Driver::BuildWorld(){
	
	coordinate  temp;
	temp =  Map.setup(100, 100, 20) ;
	ActorManager.Player.location.teleport(temp.get_x(), temp.get_y() );


	//put 1 creature in each room;
	int decider;
	for( int a = 1; a < Map.getNumberOfRooms(); a++){
		Actor temp;
		decider = rand() % 10;
		
        if( decider == 0){
			temp.birth(100,100,6,4,30,0x96,"creep");
			temp.location.teleport(Map.getRoomX(a), Map.getRoomY(a));
			OutputDebugString("1");
		} else if( decider == 1){
			temp.birth(100,100,6,4,30,0x85,"creep");
			temp.location.teleport(Map.getRoomX(a), Map.getRoomY(a));
			OutputDebugString("2");
		} else if( decider == 2){
			temp.birth(100,100,6,4,30,0xA1,"creep");
			temp.location.teleport(Map.getRoomX(a), Map.getRoomY(a));
	    } else if( decider == 3){
			temp.birth(100,100,6,4,30,0xAD,"creep");
			temp.location.teleport(Map.getRoomX(a), Map.getRoomY(a));
		} else if( decider == 4){
			temp.birth(100,100,6,4,30,0xB1,"creep");
			temp.location.teleport(Map.getRoomX(a), Map.getRoomY(a));
	    } else if( decider == 5){
			temp.birth(100,100,6,4,30,0xBF,"creep");
			temp.location.teleport(Map.getRoomX(a), Map.getRoomY(a));
		} else if( decider == 6){
			temp.birth(100,100,6,4,30,0xBE,"creep");
			temp.location.teleport(Map.getRoomX(a), Map.getRoomY(a));
	    } else if( decider == 7){
			temp.birth(100,100,6,4,30,0xD9,"creep");
			temp.location.teleport(Map.getRoomX(a), Map.getRoomY(a));
		} else if( decider == 8){
			temp.birth(100,100,6,4,30,0xDA,"creep");
			temp.location.teleport(Map.getRoomX(a), Map.getRoomY(a));
	    } else if( decider == 9){
			temp.birth(100,100,6,4,30,0x0DB,"creep");
			temp.location.teleport(Map.getRoomX(a), Map.getRoomY(a));

		}
		Map.setOccupied( Map.getRoomX(a), Map.getRoomY(a), true);
		ActorManager.enemies.push_back(temp);

		
	}
	
}
