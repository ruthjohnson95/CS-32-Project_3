// Game.cpp

#include "Game2.h"
#include <iostream>

using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{	
	//create dungeon
	m_dungeon = new Dungeon(4);
	m_dungeon->createDungeonLevel();
}

Game::~Game()
{
	delete m_dungeon;
}

void Game::play()
{ 
	m_dungeon->display("");

	while (!(m_dungeon->getPlayer()->isDead())  && m_dungeon->getLevel() <5 )
	{
		char action;
		action = getCharacter();
		clearScreen();
		//m_dungeon->display("");

		switch (action)
		{
		default: //if bad move, don't move
			cout << '\a' << endl; //beep
				continue; 
		case 'q':
			return; 
		case 'g':
		{
			Object* o = nullptr;

			if (m_dungeon->testForObj(m_dungeon->getPlayer()->row(), m_dungeon->getPlayer()->col(), o))
			{
				m_dungeon->getPlayer()->addToInv(o);
				//delete from the grid
				m_dungeon->changeGrid(o->row(), o->col(), ' ');
				m_dungeon->getPlayer()->changeTemp(' ');
				clearScreen();
				m_dungeon->display("");
				cout << "You pick up a " << o->name() << endl;
			}
			break;
		}
		case 'w':
		{
			clearScreen();
			m_dungeon->getPlayer()->displayInv();
			m_dungeon->getPlayer()->exchangeObject();

			clearScreen();
			m_dungeon->display("");

			cout << "You are wielding " << m_dungeon->getPlayer()->getWeapon()->name() << "." << endl;

			break;
		}

		case 'r':
		{
			clearScreen();
			m_dungeon->getPlayer()->displayInv();
			m_dungeon->getPlayer()->readScroll();
			break;
		}

		case 'i':
		{
			clearScreen();
			m_dungeon->getPlayer()->displayInv();
			action = getCharacter();
			clearScreen();
			m_dungeon->display("");
			break;
		}
		case '>':
		{
			if (m_dungeon->getPlayer()->getTemp() == '>')
			{
				m_dungeon->increaseLevel();
				clearScreen();
				m_dungeon->createDungeonLevel();
				m_dungeon->getPlayer()->changeTemp(' ');
				break;
			}
		}
		 

		case '&':
		{
			if (m_dungeon->getPlayer()->getTemp() == '&')
			{
				cout << "Congratulations, you won!" << endl;
				return; 
			}
		}
		break;

		case 'h':
		case 'j':
		case 'k':
		case 'l':
		{
			bool play = (m_dungeon->getPlayer()->move(action));
			m_dungeon->display("");
			if (play)
			{
				m_dungeon->getPlayer()->attack(m_dungeon->getPlayer()->getOpponent());
			}
					
			//Monsters take their turn
			for (int i = 0; i < m_dungeon->getCritters().size(); ++i)
			{

				m_dungeon->getCritters()[i]->moveMonster(m_dungeon->getPlayer()->row(), m_dungeon->getPlayer()->col());

				Actor* monster = m_dungeon->getCritters()[i];
				//attack if player is surrounding a monster
				//check North
				if (m_dungeon->getChar(monster->row() - 1, monster->col()) == '@')
				{
					monster->attack(m_dungeon->getPlayer());
				}
				//check South
				if (m_dungeon->getChar(monster->row() + 1, monster->col()) == '@')
				{
					monster->attack(m_dungeon->getPlayer());
				}
				//check East
				if (m_dungeon->getChar(monster->row(), monster->col() + 1) == '@')
				{
					monster->attack(m_dungeon->getPlayer());
				}
				//check West
				if (m_dungeon->getChar(monster->row(), monster->col() - 1) == '@')
				{
					monster->attack(m_dungeon->getPlayer());
				}
			} //end of for loop
			break;
		}//end of case statement

		
		}//end of switch  

		//clearScreen();
	}
	clearScreen();
	//m_dungeon->display("");

}



/*
cout << "Press q to exit game." << endl;
while (getCharacter() != 'q'){
*/

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.

