#include "log.h"


void gamelog::logSetup(){
	Log.push_back("          ");
	Log.push_back("          ");
	Log.push_back("          ");
	Log.push_back("          ");
}
void gamelog::findItem(string item){
	
	Log.push_back("You found a " + item + "\n");
}
void gamelog::fight(string attkr, string defnr){
	Log.push_back(attkr+ " Hit " + defnr + " for damage\n");
} 
string gamelog::getLogForOutput(){
	string holder;
	if(Log.size() <= 4)
		for( int x = 0; x < Log.size(); x++){
			holder = holder + Log[x]; 
	}else {
		for( int z= Log.size() - 4; z < Log.size(); z++){
			holder = holder + Log[z]; 
		}
	}
	return holder;
}