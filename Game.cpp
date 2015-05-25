// Game.cpp

#include "Game.h"
#include <iostream>

using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
	//m_dungeon->createDungeonLevel(0);
}

Game::~Game()
{
	delete m_dungeon; 
}

void Game::play()
{
	cout << "Press q to exit game." << endl;
	while (getCharacter() != 'q'){
		while (!m_dungeon->player()->isDead())
		{
			//display the dungeon
			m_dungeon->display();

			//get user's input
			string action;
			getline(cin, action);

			//NOT SURE WHAT THIS IS...???
			/*
			if (action.size() == )
			p->stand();
			*/
			//else
			switch (action[0])
			{
			default: //if bad move, don't move
				//case for inventory 
				cout << '\a' << endl; //beep
				continue;
			case 'q': return;
			case 'h':
			case 'j':
			case 'k':
			case 'l':
				m_dungeon->player()->move(getCharacter());
				break;
				//case for inventory
			case 'i':
			case 'w':
			case 'r':
				m_dungeon->player()->Inventory();
			}
			m_dungeon->display();
		}
	}
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.


