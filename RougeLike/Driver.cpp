
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
	ActorManager.Log.logSetup();
}
void Driver::draw(){
	int start_x =  ActorManager.Player.location.get_x() - (tl_xres() /2);
	int start_y =  ActorManager.Player.location.get_y() - (tl_yres() /2);

	int stop_x = start_x + tl_xres();
	int stop_y = start_y + tl_yres();

	int log_x = stop_x -10;
	int log_y = stop_y - 10;
	
	tl_framestart(0);
	for(int y= start_y; y < (Map.get_y_dim() + start_y) ; y++){
	   //draw map
		for(int x = start_x; x < (Map.get_x_dim() + start_x) ; x++){
				tl_rendertile(Map.get_tile(x, y), x - start_x , y- start_y);
				
				
			}
		}
		for(int a = 0; a < ActorManager.loot.size(); a++){
		
		if( ActorManager.loot[a].location.get_x() >= start_x && ActorManager.loot[a].location.get_x() <= stop_x && ActorManager.loot[a].location.get_y() >= start_y && ActorManager.loot[a].location.get_y() <= stop_y){
			tl_rendertile( ActorManager.loot[a].getTile() , ActorManager.loot[a].location.get_x() - start_x , ActorManager.loot[a].location.get_y()- start_y);
			
		}

	}

	
	for(int a = 0; a < ActorManager.enemies.size(); a++){
		
		if( ActorManager.enemies[a].location.get_x() >= start_x && ActorManager.enemies[a].location.get_x() <= stop_x && ActorManager.enemies[a].location.get_y() >= start_y && ActorManager.enemies[a].location.get_y() <= stop_y){
			tl_rendertile( ActorManager.enemies[a].getTile() , ActorManager.enemies[a].location.get_x() - start_x , ActorManager.enemies[a].location.get_y()- start_y);
			
		}

	}

	//drawLog();
		tl_rendertile( '@' ,(tl_xres() / 2) ,(tl_yres() / 2) );
		


}
void Driver::update(){
	for(int x = 0; x < ActorManager.enemies.size(); x++){
		if(!ActorManager.enemies[x].isAlive()){
			Map.setOccupied(ActorManager.enemies[x].location.get_x() ,ActorManager.enemies[x].location.get_y() , false);
			ActorManager.enemies.erase(ActorManager.enemies.begin() + x);
		}
	}
	for(int z= 0; z < ActorManager.enemies.size(); z++){
		if(ActorManager.rangeToPlayer(z) == 1){
			ActorManager.fight(z, -1);
			ActorManager.Log.fight( ActorManager.enemies[z].getName(),"Player");
		}else if(ActorManager.rangeToPlayer(z) < 3 && ActorManager.rangeToPlayer(z) >1 ){

			Map.setOccupied(ActorManager.enemies[z].location.get_x(), ActorManager.enemies[z].location.get_y(), false);
			if(ActorManager.enemies[z].location.get_x() > ActorManager.Player.location.get_x() ) {
				ActorManager.enemies[z].location.left();
				Map.setOccupied(ActorManager.enemies[z].location.get_x() , ActorManager.enemies[z].location.get_y() , true);
			}

			if(ActorManager.enemies[z].location.get_x() < ActorManager.Player.location.get_x() ) {
				ActorManager.enemies[z].location.right();
				Map.setOccupied(ActorManager.enemies[z].location.get_x() , ActorManager.enemies[z].location.get_y() , true);
			}

			if(ActorManager.enemies[z].location.get_y() < ActorManager.Player.location.get_y() ) {
				ActorManager.enemies[z].location.down();
				Map.setOccupied(ActorManager.enemies[z].location.get_x() , ActorManager.enemies[z].location.get_y() , true);
			}

			if(ActorManager.enemies[z].location.get_y() > ActorManager.Player.location.get_y() ) {
				ActorManager.enemies[z].location.up();
				Map.setOccupied(ActorManager.enemies[z].location.get_x() , ActorManager.enemies[z].location.get_y() , true);
			}
		}
		


	}
	ActorManager.pickUp(ActorManager.whatIsAt(ActorManager.Player.location.get_x() , ActorManager.Player.location.get_y() ) );
	

}
void Driver::run(){
	int x_dim = 800;
	int y_dim = 600;
	int y_pos =1;
	int x_pos = 1;

	    
	    tl_framestart(0);
		for(;;){


		draw();
		bool attacking = false;
		int attackIndex = -1;
		
		

		if(tl_keywentdown("escape")  || !ActorManager.isPlayerAlive()){
			break;
		} 
		if (tl_keywentdown("down")){
			if(   Map.can_step(ActorManager.Player.location.get_x(), ActorManager.Player.location.get_y() + 1) ) {
			    ActorManager.Player.location.down();
			}else if(Map.isOccupied(ActorManager.Player.location.get_x(), ActorManager.Player.location.get_y() + 1)){
				attackIndex = ActorManager.whoIsAt(ActorManager.Player.location.get_x(), ActorManager.Player.location.get_y() + 1);
				attacking = true;
			}
			update();
		}
		if (tl_keywentdown("up")){
			if(   Map.can_step(ActorManager.Player.location.get_x()   , ActorManager.Player.location.get_y() - 1 ) ) {
			     ActorManager.Player.location.up();
			}else if(Map.isOccupied(ActorManager.Player.location.get_x()   , ActorManager.Player.location.get_y() - 1 )){
				attackIndex = ActorManager.whoIsAt(ActorManager.Player.location.get_x(), ActorManager.Player.location.get_y() - 1);
				attacking = true;
			}
			update();
		}
		if (tl_keywentdown("left")){
			if(   Map.can_step(ActorManager.Player.location.get_x()-1, ActorManager.Player.location.get_y()) ) {
			     ActorManager.Player.location.left();
			}else if(Map.isOccupied(ActorManager.Player.location.get_x()-1, ActorManager.Player.location.get_y())){
				attackIndex = ActorManager.whoIsAt(ActorManager.Player.location.get_x()-1, ActorManager.Player.location.get_y() );
				attacking = true;
			}
			update();
		}
		if (tl_keywentdown("right")){
			if(   Map.can_step(ActorManager.Player.location.get_x()+1, ActorManager.Player.location.get_y()) ) {
			     ActorManager.Player.location.right();
			}else if(Map.isOccupied(ActorManager.Player.location.get_x()+1, ActorManager.Player.location.get_y())){
				attackIndex = ActorManager.whoIsAt(ActorManager.Player.location.get_x()+1, ActorManager.Player.location.get_y());
				attacking = true;
			}
			update();
		}

		//is attacking
		if((attacking) && (attackIndex != -1 )){
			
			ActorManager.fight(-1, attackIndex);
			ActorManager.Log.fight("Player", ActorManager.enemies[attackIndex].getName());

		}
		
		
    }
}
void Driver::BuildWorld(){
	int decider;
	coordinate  temp;
	temp =  Map.setup(100, 100, 20) ;
	ActorManager.Player.location.teleport(temp.get_x(), temp.get_y() );
	ActorManager.Player.birth(50,100,40,10,3,0x000,"Player1");
	
	//put 1 creature in each room
	

	for( int a = 1; a < Map.getNumberOfRooms(); a++){
		Actor temp;
		Item  * tempItem = new Item;
		decider = rand() % 10;
		tempItem->rollItem();
		
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
		tempItem->location.teleport(Map.getRoomX(a), Map.getRoomY(a));
		ActorManager.enemies.push_back(temp);
		ActorManager.loot.push_back(*tempItem);

		
	}
	
}
void Driver::drawLog(){
	tl_scale(2);
	int log_x_res = tl_xres() / 4;
	int log_y_res = tl_yres() / 8;
	string log_out = ActorManager.Log.getLogForOutput();
	for (int x =(tl_xres() - log_x_res) ; x < tl_xres(); x++){
		tl_rendertile(log_out[tl_xres() - x] ,x, log_y_res);
	}


	tl_scale(1);
}
