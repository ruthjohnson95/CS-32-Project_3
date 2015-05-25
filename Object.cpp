
#include "Object.h"

Object::Object(string name, int row, int col, char symbol)
	:m_name(name), c_r(row), c_c(col), m_symbol(symbol)
{}

Object::~Object()
{}

char Object::symbol()
{
	return m_symbol;
}

int Object::row()
{
	return c_r;
}

int Object::col()
{
	return c_c;
}

string Object::name()
{
	return m_name;
}

////////////////////////////////////////////////////
//			WEAPON CLASS
////////////////////////////////////////////////////

Weapon::Weapon(string name, string action, int bonus, int damage, int row, int col)
	: Object(name, row, col, ')')
{
	m_action = action;
	dex_bonus = bonus;
	m_damage = damage; 
}


int Weapon::getDamage()
{
	return m_damage;
}

int Weapon::getDex()
{
	return dex_bonus;
}

string Weapon::getAction()
{
	return m_action; 
}


////////////////////////////////////////////////////////////

Mace::Mace(int row, int col)
	:Weapon("Mace", "swings", 0 ,2, row, col)
{}

/////////////////

Short_sword::Short_sword(int row, int col)
	: Weapon("Short sword","swings", 0, 2, row , col)
{}

////////////////

Long_sword::Long_sword(int row, int col)
	: Weapon("Long sword","swings", 0, 4, row ,col)
{}

////////////////

Magic_axe::Magic_axe(int row, int col)
	: Weapon("Magic axe", "swings", 5, 5, row, col)
{}

////////////////

Fangs::Fangs(int row, int col)
	: Weapon("Magic fangs of sleep","bites", 3, 2, row, col)
{}

void Fangs::putToSleep(Player* p)
{
	//implementation here
}


//////////////////////////////////////////////////////////////////////////

Scroll::Scroll(int row, int col, Player* p, string name, string message)
	:Object(name, row, col, '?')
{
	m_message = message; 
}

void Scroll::read(Player* p)
{}

void Teleportation::read(Player* p)
{
	//get random coordinates to teleport to
	bool found = false;

	while(!found)
	{
		int new_row = randInt(MAXCOLS);
		int new_col = randInt(MAXROWS);
		if (p->getDungeon()->ifBlank(new_row, new_col))
		{
			//move player 
			p->moveMonster(new_row, new_col);
				found = true; 
		}
	}
}

void ImproveArmor::read(Player* p)
{
	p->changeArmor(randInt(2) + 1);
}

void RaiseStrength::read(Player* p)
{
	p->changeStrength(randInt(2) + 1);
}

void EnhanceHealth::read(Player* p)
{
	p->changeMaxHit(randInt(5)+3);
}

void EnhanceDexterity::read(Player* p)
{
	p->changeDex(1);
}

