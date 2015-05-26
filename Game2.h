
// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Actors.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Dungeon;
class Actor;
class Object;
class Player;


// You may add data members and other member functions to this class.

class Game
{
public:
	Game(int goblinSmellDistance);
	~Game();
	void play();
	int getGoblinSmellDistance()
	{
		return m_goblinSmellDistance;
	}

private:
	Dungeon* m_dungeon;
	int m_goblinSmellDistance; 
};


#endif // GAME_INCLUDED


