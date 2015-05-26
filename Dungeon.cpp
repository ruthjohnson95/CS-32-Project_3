#include "Dungeon.h"
//#include "utilities.h"


Dungeon::Dungeon(int level)
{
	//set level
	m_level = level; 
	m_player = nullptr;
	//Fill grid with #s
	for (int i = 0; i < MAXCOLS; i++)
	{
		for (int j = 0; j < MAXROWS; j++)
		{
			d_grid[i][j] = '#';
		
		}
	}
}

void Dungeon::addPlayer(int row, int col)
{
	if (m_level == 0)
	{
		//create a player
		Weapon* s = new Short_sword(row, col); 
		m_player = new Player(row, col, this, s);
		d_grid[row][col] = '@';
	}
	//place the player in the grid
	else
	{
	d_grid[m_player->row()][m_player->row()] = ' ';
	d_grid[row][col] = '@';
	m_player->changeRow(row);
	m_player->changeCol(col);
	}

}

void Dungeon::display(string message)
{
	for (int i = 0; i < MAXCOLS; i++)
	{
		for (int j = 0; j < MAXROWS; j++)
		{
			cout << d_grid[i][j];
		}
		cout << endl;
	}

	//messages
	cout << "Dungeon Level: " << m_level << ", Hit points: " << m_player->getHitPoints() << ", Strength: " << m_player->getStrength() << ", Dexterity: " << m_player->getDex() << endl; 
	cout << endl; 
}


bool Dungeon::notWall(int r, int c)
{
	if (r == 0 || r == MAXCOLS-1) return false;
	else if (c == 0 || c == MAXROWS-1) return false;
	else return true; 
}

bool Dungeon::pathExists(int sr, int sc, int er, int ec)
{
	d_grid[sr][sc] = ' ';
	m_Coords.push_back(Coord(sr, sc)); 

	while (sc != ec)
	{
		switch (rand() % 4)
		{
		case 0: //move North
			if (d_grid[sr - 1][sc] != ' ' && notWall(sr - 1, sc))
			{
				if (pathExists(sr -= 1, sc, er, ec)) return true;
			}
			break;

		case 1: //move South
			if (d_grid[sr + 1][sc] != ' '&& notWall(sr + 1, sc))
			{
				//recursively search the move from position
				if (pathExists(sr += 1, sc, er, ec))
					return true;
			}
			break;

		case 2: 

			//move East
			if (d_grid[sr][sc + 1] != ' ' && notWall(sr, sc + 1))
			{
				//recursively search the move from position
				if (pathExists(sr, sc += 1, er, ec))return true;
			}
			break; 

		default: return true; 
		}
		
	}

}


void Dungeon::makeRoom(int s_r, int s_c, int x_scale, int y_scale)
{
	for (int i = s_r; i < s_r + y_scale; i++)
	{
		for (int j = s_c; j < s_c + x_scale; j++)
		{
			if (i>= MAXCOLS-1 || j >= MAXROWS-1)
			{
				return;
			}
			//add blank space
			d_grid[i][j] = ' ';
			m_Coords.push_back(Coord(i,j));

		}
	}
}

int Dungeon::rows() const
{
	return m_rows;
}

int Dungeon::cols() const
{
	return m_cols;
}


bool Dungeon::ifCritter(int r, int c)
{
	for (int i = 0; i < m_Critters.size(); i++)
	{
		for (int j = 0; j < m_Critters.size(); j++)
		{
			if (m_Critters[i]->row() == r && m_Critters[j]->col() == c)
				return true;
		}
	}
	return false; 
}

bool Dungeon::ifBlank(int r, int c)
{
	if (d_grid[r][c] == ' ') return true;
	else return false; 
}

vector<Actor*>& Dungeon::getCritters()
{
	return m_Critters;
}

Player* Dungeon::getPlayer()
{
	return m_player;
}

char Dungeon::getChar(int row, int col)
{
	return d_grid[row][col];
}

void Dungeon::addObject(string name, int row, int col)
{
	if (name == "Short sword")
	{
		m_Objects.push_back(new Short_sword(row, col));
		//add onto grid
		d_grid[row][col] = ')';
	}

	if (name == "Magic axe")
	{
		m_Objects.push_back(new Magic_axe(row, col));
		//add onto grid
		d_grid[row][col] = ')';
	}

	if (name == "Long sword")
		{
			m_Objects.push_back(new Long_sword(row, col));
			//add onto grid
			d_grid[row][col] = ')';
		}

		if (name == "Fangs")
		{
			{
				m_Objects.push_back(new Fangs(row, col));
				//add onto grid
				d_grid[row][col] = ')';
			}
		}

		//////Scrolls///////

		if (name == "Improve armor")
		{
			m_Objects.push_back(new ImproveArmor(row, col, m_player));
			d_grid[row][col] = '?';

		}
	
		if (name == "Teleporation")
		{
			m_Objects.push_back(new Teleportation(row, col, m_player));
			d_grid[row][col] = '?';

		}

		if (name == "Raise strength")
		{
			m_Objects.push_back(new RaiseStrength(row, col, m_player));
			d_grid[row][col] = '?';

		}


		if (name == "Enhance health")
		{
			m_Objects.push_back(new EnhanceHealth(row, col, m_player));
			d_grid[row][col] = '?';

		}

		if (name == "Enhance dexterity")
		{
			m_Objects.push_back(new EnhanceDexterity(row, col,m_player));
			d_grid[row][col] = '?';

		}

		///////////////////////////////////

		if (name == "Golden idol")
		{
			m_Objects.push_back(new GoldenIdol(row, col));
			d_grid[row][col] = '&';

		}

}


void Dungeon::addCritter(char symbol, int row, int col)
{
	switch (symbol)
	{

	case 'B':
		m_Critters.push_back(new Bogeymen(row, col, this, new Short_sword(row, col)));
		break;

	case 'S':
		m_Critters.push_back(new SnakeWomen(row, col, this, new Fangs(row, col)));
		break;

	case 'D':
		m_Critters.push_back(new Dragon(row, col, this, new Long_sword(row, col)));
		break;

	case 'G':
		m_Critters.push_back(new Goblin(row, col, this, new Short_sword(row, col)));
		break; 
	}

	//add onto grid
	d_grid[row][col] = symbol; 
}

void Dungeon::createDungeonLevel()
{
	makeRoom(1, 1, 60, 15);

	/*
	int a = 1 + rand() % 11;
	int b = 1 + rand() % 17;
	int c = randInt(10)+69;
	int d = randInt(10) + 69;
	

	if (pathExists(a, b, c, d))
	{
		for (int i = 0; i < randInt(5)+2; i++)
		{
			srand(static_cast<unsigned int>(time(0)));
			makeRoom(m_Coords[randInt(m_Coords.size() - 1)].r(), m_Coords[randInt(m_Coords.size() - 1)].c(), 5 + rand() % 20, 5 + rand() % 20);
		}
	}

	*/
	
	//randomly place player
	int index = 0 + rand() % m_Coords.size();

	//add player
	
		addPlayer(m_Coords[index].r(), m_Coords[index].c());
	
	
	//add staircase char
		if (m_level < 4)
		{
			index = 0 + rand() % m_Coords.size();
			d_grid[m_Coords[index].r()][m_Coords[index].c()] = '>';
		}

	//add Critters (1-5 each)
	
	int num_monsters = 2 + randInt(5 * (m_level + 1));
	int count = 0; 
	int row = 1;
	int col = 1; 

	while (count < num_monsters)
	{
		//all levels
		switch (rand() % 4)
		{
		case 0: //Bogeymen
			if (m_level >= 2)
			{
				index = randInt(m_Coords.size() - 1);
				row = m_Coords[index].r();
				col = m_Coords[index].c();

				//add in random spot
				if (ifBlank(row, col))
				{
					addCritter('B', row, col);
					++count; 
				}
			}
			break;

		case 1: //Snakewomen
			//all levels
		{

			index = randInt(m_Coords.size() - 1);
			row = m_Coords[index].r();
			col = m_Coords[index].c();

			//add in random spot
			if (ifBlank(row, col))
			{
				addCritter('S', row, col);
				++count; 
			}
		}
			break;

		case 2: //Dragons
			{
				if (m_level >= 3)
				{
					index = randInt(m_Coords.size() - 1);
					row = m_Coords[index].r();
					col = m_Coords[index].c();

					//add in random spot
					if (ifBlank(row, col))
					{
						addCritter('D', row, col);
						++count; 
					}
				}
			}
			break;

		case 3: //Goblins
			//all levels
		{
			index = randInt(m_Coords.size() - 1);
			row = m_Coords[index].r();
			col = m_Coords[index].c();

			//add in random spot
			if (ifBlank(row, col))
			{
				addCritter('G', row, col);
				++count; 
			}
		}
			break; 
		}
	}

	//ADD OBJECTS 
	count = 0;
	int num_items = randInt(2) + 2; 

	while (count < num_items)
	{
		//decide which objects to add
		int choice = rand() % 6; 
		
		switch (choice)
		{

		case 0:
		{
			index = randInt(m_Coords.size() - 1);
			row = m_Coords[index].r();
			col = m_Coords[index].c();

			//add in random spot
			if (ifBlank(row, col))
			{
				addObject("Short sword", row, col);
				++count; 
			}
		}
		break; 

		case 1:
		{
			index = randInt(m_Coords.size() - 1);
			row = m_Coords[index].r();
			col = m_Coords[index].c();

			//add in random spot
			if (ifBlank(row, col))
			{
				addObject("Long sword", row, col);
				++count; 
			}
		}
		break;

		case 2:
		{
			index = randInt(m_Coords.size() - 1);
			row = m_Coords[index].r();
			col = m_Coords[index].c();

			//add scrolls here 
			if (ifBlank(row, col))
			{
				addObject("Improve armor", row, col);
				++count;
			}
			break; 
		}

		case 3:
		{
			index = randInt(m_Coords.size() - 1);
			row = m_Coords[index].r();
			col = m_Coords[index].c();

			if (ifBlank(row, col))
			{
				addObject("Raise strength", row, col);
				++count; 
			}
			break;
		}

		case 4:
		{
			index = randInt(m_Coords.size() - 1);
			row = m_Coords[index].r();
			col = m_Coords[index].c();

			if (ifBlank(row, col))
			{
				addObject("Enhance health", row, col);
				++count; 
			}
			break;
		}

		case 5:
		{
			index = randInt(m_Coords.size() - 1);
			row = m_Coords[index].r();
			col = m_Coords[index].c();

			if (ifBlank(row, col))
			{
				addObject("Enhance dexterity", row, col);
				++count; 
			}
			break;
		}
		}
	} // end of while() loop


	count = 0; 

	//add golden scroll
	if (m_level == 4)
	{
		while (count < 1)
		{
			index = randInt(m_Coords.size() - 1);
			row = m_Coords[index].r();
			col = m_Coords[index].c();

			if (ifBlank(row, col))
			{
				addObject("Golden idol", row, col);
				++count; 
			}
		}
	}
}

void Dungeon::increaseLevel()
{
	++m_level;
}

int Dungeon::getLevel()
{
	return m_level;
}

void Dungeon::changeGrid(int row, int col, char c)
{
	d_grid[row][col] = c;
}

vector<Object*> Dungeon::getObjects()
{
	return m_Objects; 
}

bool Dungeon::testForObj(int r, int c, Object* &o)
{
	bool found = false; 

		int c_r = getPlayer()->row();
		int c_c = getPlayer()->col();
		
		if (getPlayer()->getTemp() == ')' || getPlayer()->getTemp() == '?') found = true;

		//locate pointer in object vector
		if (found)
		{
			for (int i = 0; i < m_Objects.size(); i++)
			{
				if (m_Objects[i]->row() == c_r && m_Objects[i]->col() == c_c)
					o = m_Objects[i];
			}
		}

		return found; 
}
