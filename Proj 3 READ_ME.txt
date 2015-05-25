Project 3 READ_ME
===================================

I. Classes
	a. Actor
		1. Player
		2. Monster
		3. 
	b. Object
		1. Weapons
			i. Mace
			ii. Short Sword
			iii.
		2. Scrolls
			i.
		3. Golden Idol

II. Dungeon
	a. Large room
		a. exit staircase
	b. Making random layer 
		b. start with path
		c. add rooms
			i. vary # of rooms
			ii. vary x_scale and y_scale
	c. Generate new level
	d. Add bits and pieces

III. Algorithsm
	a. Search algoriths for:
		a. Goblins
		b. ...

//////////////////////////////////////////////////

Algorithms:

	//if prev char == ... and cur char == @ (aka you're standing on the object )
	//user must prress 'g'
void Actor::pickObject(char symbol)
{
	//get pointer at that location use polymorphism 
	//special message
	//add to inventory 
}

makeDungeonLevel(int level)
{
	//make path
	//add rooms(place exit)

	//add objects (don't need member func)
	//add ALL LEVEL critters (don't need member fun)
	//add the player 

	//add critters specific by level 
	case 1:

	case 2:

	case 3:

	case 4:
		//add golden scroll!!!
}
\

\
===================================================

To Do:
Fangs::putToSleep(Player* p);

Actor::move()
Actor::attack(Actor* a)
Actor::drop(Oject* obj)
Actor::isDead()
Actor::canMove()

//don't know where data is
Monster::Monster(int row, int col)
	:Actor(...)
Monster::attack()
Monster::move()
Monster::drop()

Boeymen::Bogeymen(int row, int col)
	:Actor(...)
	//random values needed for strength and dexterity
Bogeymen::attack()
Bogeymen::move()
Bogymen::drop()

SnakeWomen::SnakeWomen(int row, int col)
	:Actor(...)
	//random values needed for strength and dexterity
SnakeWomen::attack()
SnakeWomen::move()
SnakeWomen::drop()

Dragon::Dragon(int row, int col)
	:Actor(...)
	//random values needed for strength and dexterity
Dragon::attack()
Dragon::drop()
Dragon:regainPts()

Goblin::Goblin(int row, int col)
	:Actor(...)
	random values needed for strength and dexterity
Goblin::Goblin()
Goblin::move()
Goblin::drop()

//add dungeon pointer to inherited classes of Actor in paramters
		and in the private variable

//~Game(); 

determine how to randomly place players, critters, objects 

fix equation for adding critters

inventory function 

add char dir into each of the move functions 

add char symbol to each of derived objects

add virtual destructors to base classes

make sure to delete new memory 
====================================================================

5/13 - Removed sleep member variable in Actor class name
	   Added object and player derived classes, but left most 
	   		functions blank
	   				-many need variable determined by probabilities 
 		
 		multiple inheritence is NOT needed; need to check nonvirtual 
 				base class not allowed error 

 		pseudo code for creating dungeon algorithms   

 	Pick-up spot: 
 			assign character symbols to players and objects
 			move player function
 			set up dungeon 
 			figure out how to use probability and random #s 

 5/13 - implemented addPlayer() in dungeon
 		updated dungeon pointer parameter in Actor and Player

 5/17 - got random path maker function to work (still think rows/columns are off)
 		got Itinery to show up when pressing 'i'
 		got rooms to be added onto paths
 			created vector<Coord>m_coords that holds coordinates of all open spaces 
 			Coord class implemented in Dungeon header 

 		//next: 
 		//clean up files 
 		//add probability and randomness 
 		//fix weapon problem: add player's initial short_sword to the inventory 
 		//picking up and dropping objects
 		//start algorithms: Bogeymen and start Goblin 

 		//next next:
 		//attack! 

 5/18 - fixed double inheritence for Object class
 		able to add weapons and display inventory
 		created testForObj(int r, int c, Object* o) that tests the surrounding area
 			if an oject is present; reserves the pointer in Object* o
 		added press 'g' to pick up object to switch statement in game.cpp

 		//next:
 		//test picking up objects
 		//implement dropping objects 
 		//clean up files 
 		//alrorithms... 