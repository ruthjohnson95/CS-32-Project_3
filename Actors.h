#ifndef ACTORS_H
#define ACTORS_H

#include "Object.h"
#include "Dungeon.h"
#include "utilities.h"

#include<string>
#include <iostream>
#include<vector>
#include <cmath>

using namespace std; 

class Weapon;
class Actor; 
class Object; 
class Dungeon; 

class Actor 
{
public:
	Actor(Dungeon* d, int row, int col, int hit, Weapon* w, int armor, int strength, int dex, char symbol, string name);
	virtual ~Actor(); 

	//MUTATOR FUNCTIONS//
		//moves actor's member variables 
	bool move(char dir);
		//moves coordinates on the grid 
	virtual void moveActor(int p_row, int p_co, int c_row, int c_col);
		//attacks another Actor
	virtual void attack(Actor* a);
		//helper function
	bool directionToDeltas(char dir, int& rowDelta, int& colDelta);
		//changes the Actor's weapon
	void switchWeapon(Weapon* w);
		//changes temp character 
	void changeTemp(char c);

	
	// smell for Monsters
	virtual bool smell(int er, int ec, int smell_power);
	//moves for Monsters; implements the smell 
	virtual bool moveMonster(int target_row, int target_col);
	//drops an object; takes into accout the probability 
	virtual void drop();
	//deletes a Monster from the grid and the vector of Monsters
	void killMonster(Actor* a);

	//GETTER FUNCTIONS
	string name();
	virtual Dungeon* getDungeon();
	bool canMove();
	bool isDead();
		
	////IN LINE FUNCTIONS///////////////

	Weapon* getWeapon()
	{
		return m_weapon;
	}

	char getTemp()
	{
		return m_temp; 
	}

	int row()
	{
		return c_r;
	}
	int col()
	{
		return c_c;
	}

	void changeArmor(int value)
	{
		a_points += value;
	}
	void changeDex(int value)
	{
		d_pts += value;
	}
	void changeStrength(int value)
	{
		m_strength += value;
	}
	void changeMaxHit(int value)
	{
		max_h_pts += value;
	}
	
	int getHitPoints()
	{
		return h_pts; 
	}

	int getArmor()
	{
		return a_points;
	}

	int getStrength()
	{
		return m_strength;
	}

	int getDex()
	{
		return d_pts; 
	}
	void changeHits(int amount)
	{
		h_pts-=amount; 
	}

	void cheat()
	{
		h_pts = 50;
		m_strength = 9; 
	}

	Actor* getOpponent()
	{
		return m_opponent;
	}

	void changeRow(int row)
	{
		c_r = row;
	}

	void changeCol(int col)
	{
		c_c = col; 
	}

private:
	//pertaining to actor
	string m_name;
	char m_symbol;
	Weapon* m_weapon; 
	int max_h_pts;
	int a_points; //armor points (0-99)
	int m_strength; //strength points (0-99)
	int d_pts; //dexterity points (0-99)
	int h_pts; //hit points (0-99)
	Actor* m_opponent;

	//pertaining to actor's dungeon
	Dungeon* m_dungeon; 
	int c_r; //current row of actor 
	int c_c; //current column of actor
	char m_temp;	
	
};

/////////////////////////////////////////////////////////

class Player : public Actor
{
public:
	Player(int col, int row, Dungeon* d, Weapon* w);
	virtual ~Player();
	virtual void attack(Actor* opponent);

	//functions for inventory
	void addToInv(Object* w);
	void displayInv();
	void exchangeObject();
	void readScroll(); 

	void pickObject(int r, int c);

private:
	vector<Object*>m_inventory;
};


/////////////////////////////////////////////////////////

	//NOTE: only on level 2 or above
class Bogeymen : public Actor
{
public:
	Bogeymen(int row, int col, Dungeon* d, Weapon* w);
	virtual ~Bogeymen();
	virtual bool moveMonster(int target_row, int target_col);
	virtual void drop();
	virtual bool smell(int er, int ec, int smell_power);

 private:
	const int SMELL_POWER = 5; 

};

/////////////////////////////////////////////////////////

//NOTE: on ALL levels
class SnakeWomen : public Actor
{
public:
	SnakeWomen(int row, int col, Dungeon* d, Weapon* w);
	virtual ~SnakeWomen();
	virtual bool moveMonster(int target_row, int target_col);
	virtual void drop();

private:
	const int SMELL_POWER = 3;

};

/////////////////////////////////////////////////////////

//NOTE: on only level 3 or deeper
class Dragon : public Actor
{
public:
	Dragon(int row, int col, Dungeon* d, Weapon* w);
	virtual ~Dragon();
	virtual bool moveMonster(int target_row, int target_col);
	virtual void drop();

	//Dragons can regain pts
	void regainPts();

private:
	const int SMELL_POWER = 0; 

};
/////////////////////////////////////////////////////////

//NOTE: on ALL levels
class Goblin : public Actor
{
public:
	Goblin(int row, int col, Dungeon* d, Weapon* w);
	virtual ~Goblin();
	bool moveMonster(int target_row, int target_col); 
	virtual bool smell(int& sr, int& sc, int target_row, int target_col, int smell_power, int step_count);
	virtual void drop();

private:
	const int SMELL_POWER = 15; 
};

/////////////////////////////////////////////////////////

#endif 
