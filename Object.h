#ifndef OBJECT_H
#define OBJECT_H

#include<string>
#include "Dungeon.h"
#include "utilities.h"

class Player; 

using namespace std; 

class Object 
{
public:
	Object(string name, int row, int col, char symbol);
	virtual ~Object(); 
	string name(); 
	char symbol();
	int row();
	int col();
private:
	string m_name;
	char m_symbol; 
	int c_r;
	int c_c; 
};


////////////////////////////////////////////////////
//			WEAPON CLASS
////////////////////////////////////////////////////

class Weapon :public Object 
{
public:
	Weapon(string name, string action, int bonus, int damage, int row, int col); 
	int getDamage();
	int getDex();
	string getAction(); 
private:
	string m_action;
	int dex_bonus;
	int m_damage;
};

/////////////////////////////////////////////////

class Mace : public Weapon
{
public:
	Mace(int row, int col);
private:

};

////////////////////////////////////////////////

class Short_sword : public Weapon
{
public:
	Short_sword(int row, int col);
private:

};

///////////////////////////////////////////////

class Long_sword : public Weapon
{
public:
	Long_sword(int row, int col);
private:

};

////////////////////////////////////////////////

class Magic_axe : public Weapon
{
public:
	Magic_axe(int row, int col);
private:

};

////////////////////////////////////////////////

class Fangs : public Weapon
{
public:
	Fangs(int row, int col);
	void putToSleep(Player* p);
private:

};

///////////////////////////////////////////////////////////////////////////////////////////////
//		SCROLLS 
///////////////////////////////////////////////////////////////////////////////////////////////

class Scroll : public Object 
{
public:
	Scroll(int row, int col, Player* p, string name, string message); 

	virtual void read(Player* p); 

	string message()
	{
		return m_message;
	}
	
private:
	string m_message; 
	

};

//////////////////////////////////////////////////////////

class Teleportation: public Scroll
{
public:
	Teleportation(int row, int col, Player* p)
		:Scroll(row, col, p, "scroll of teleportation", "Your body your body wrenched in space and time.") {}
	virtual void read(Player* p); 
};

class ImproveArmor : public Scroll
{
public:
	ImproveArmor(int row, int col, Player* p)
		:Scroll(row, col, p, "scroll of enhance armor", "Your armor glows blue.") {}
	virtual void read(Player* p);
};

class RaiseStrength : public Scroll
{
public:
	RaiseStrength(int row, int col, Player* p)
		:Scroll(row, col, p, "scroll of strength", "Your muscles bulge.") {}
	virtual void read(Player* p);
};

class EnhanceHealth : public Scroll
{
public:
	EnhanceHealth(int row, int col, Player* p)
		:Scroll(row, col, p, "scroll of enhance health", "You feel your heart beating stronger.") {}
	virtual void read(Player* p);
};

class EnhanceDexterity : public Scroll
{
public:
	EnhanceDexterity(int row, int col, Player* p)
		:Scroll(row, col, p, "scroll of dexterity", "You feel like less of a kltuz." ) {}
	virtual void read(Player* p);
};

////////////////////////////////////

class GoldenIdol : public Object
{
public:
	GoldenIdol(int row, int col)
		:Object("Golden idol" ,row, col, '&') {}
	void endGame(); 
};


#endif