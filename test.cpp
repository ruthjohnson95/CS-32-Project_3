/*
#include "Game2.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	// The following call to srand ensures that each time you run the program,
	// you'll get a different series of random numbers generated, and thus
	// different randomly-generated levels, monsters, scrolls, etc.  If you
	// comment out this call, then each game you start will run the same up
	// until you change the way you attack a monster or do something else that	  // will call randInt in a different circumstance than you did before.
	// This repeatability could be useful for debugging.

	srand(static_cast<unsigned int>(time(0)));

	// Your program must use whatever value is passed to the Game constructor
	// as the distance a goblin can smell.  The spec stated this is 15.  Some
	// people might implement the recursive goblin algorithm for determining
	// the shortest path to the player in a way that takes an uncomfortably
	// long time for that distance.  If you're one of them, then until you
	// improve your algorithm, pass a value smaller than 15 to the game
	// constructor so your game is comfortable to play.

	Dungeon d(0);
	//d.makeRoom(1, 1, 60, 15);
	d.createDungeonLevel();
	
//	d.makePath(); 
//	d.pathExists(1, 1, 8,68);
//	d.foo(); 
	d.display("");
	//cout << "Press q to exit game." << endl;

//	d.makeRoom(1, 1, 4, 4);//1 1 40 14
	//d.display("");

	
	char action = getCharacter(); 
	while (action != 'q')
	{

		switch (action)
		{
		default: //if bad move, don't move
			//case for inventory 
			cout << '\a' << endl; //beep
			//	continue; 
		case 'g':
		{
			Object* o = nullptr;

			if (d.testForObj(d.getPlayer()->row(), d.getPlayer()->col(), o))
			{
				d.getPlayer()->addToInv(o);
				//delete from the grid
				d.changeGrid(o->row(), o->col(), ' ');
				d.getPlayer()->changeTemp(' ');
				clearScreen();
				d.display("");
				cout << "You pick up a " << o->name() << endl; 
			}
			break;
		}
		case 'w':
		{
			clearScreen();
			d.getPlayer()->displayInv();		
			d.getPlayer()->exchangeObject();
		
			clearScreen();
			d.display("");

			cout << "You are wielding " << d.getPlayer()->getWeapon()->name() << "." << endl;

			break;
		}

		case 'r':
		{
			clearScreen();
			d.getPlayer()->displayInv();	
			d.getPlayer()->readScroll();
			break; 
		}
			
		case 'i':
		{
			clearScreen();
			d.getPlayer()->displayInv();
			action = getCharacter();
			clearScreen();
			d.display("");
			break;
		}
		case 'h':
		case 'j':
		case 'k':
		case 'l':
		{
			d.getPlayer()->move(action);
			break;
		}
		
			
	}//end of switch  
		
		//Monsters take their turn
		for (int i = 0; i < d.getCritters().size(); ++i)
		{
			
			d.getCritters()[i]->moveMonster(d.getPlayer()->row(), d.getPlayer()->col());

			Actor* monster = d.getCritters()[i]; 
			//attack if player is surrounding a monster
				//check North
			if (d.getChar(monster->row()- 1, monster->col()) == '@')
				{
					monster->attack(d.getPlayer());
				}
				//check South
			if (d.getChar(monster->row() + 1, monster->col()) == '@')
			{
				monster->attack(d.getPlayer());
			}
				//check East
			if (d.getChar(monster->row(), monster->col() +1) == '@')
			{
				monster->attack(d.getPlayer());
			}
				//check West
			if (d.getChar(monster->row(), monster->col() -1) == '@')
			{
				monster->attack(d.getPlayer());
			}
		}


		action = getCharacter();

		clearScreen();
		d.display("");
		
	}
	
	system("pause");
	
	Game g(15);
	g.play();
	
	
}*/