
// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "utilities.h"
#include "Actors.h"
#include "Dungeon.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std; 
/*
class Dungeon; 
class Actor; 
class Object; 
class Player; 
*/


// You may add data members and other member functions to this class.

class Game
{
public:
	Game(int goblinSmellDistance);
	~Game(); 
	void play();
	
private:
	Dungeon* m_dungeon; 
	/*
	//dynamic vector of Actor pointers
	vector<Actor*>m_actors;
	//dynamic vector of Object pointers
	vector<Object*>m_objects;
	*/
};

#endif // GAME_INCLUDED


