

#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "Actors.h"
#include "Game2.h"

using namespace std; 

//Global constants 
const int MAXROWS = 7; //70;
const int MAXCOLS = 7; //18;

class Object;
class Actor;
class Player;
class Game;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

class Dungeon
{
public:
	Dungeon(int m_level, Game* g);
	void makeRoom(int s_r, int s_c, int x_scale, int y_scale);
	bool pathExists(int sr, int sc, int er, int ec);
	bool notWall(int r, int c);

	void addPlayer(int row, int col);
	void addCritter(char symbol, int row, int col);
	void addObject(string name, int row, int col);
	void display(string message);
	bool ifCritter(int r, int c);
	bool ifBlank(int r, int c);

	
	vector<Actor*>& getCritters();
	vector<Object*>getObjects();
	char getChar(int row, int col); 
	Player* getPlayer();
	int rows() const;
	int cols() const;

	void changeGrid(int row, int col, char c);
	void createDungeonLevel();
	void increaseLevel();
	bool testForObj(int r, int c, Object* &o); 
	int getLevel();
	int getSmellDistance();

private:
	Player* m_player;
	Game* m_game;
	int m_level;
	int m_rows;
	int m_cols;
	int m_goblin_smell_distance; 
	//char d_grid[MAXROWS][MAXCOLS];
	char d_grid[18][70];
	//int test[70][18];
	//vector of Critter pointers (enemies)
	vector<Actor*>m_Critters;
	//vector of Objects
	vector<Object*>m_Objects; 
	//vector of Coordinates
	vector<Coord>m_Coords; 
};


#endif