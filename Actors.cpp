#include "Actors.h"

Actor::Actor(Dungeon* d, int row, int col, int hit, Weapon* w, int armor, int strength, int dex, char symbol, string name)
	:m_dungeon(d), c_r(row), c_c(col), h_pts(hit), m_weapon(w), a_points(armor), m_strength(strength), d_pts(dex), m_symbol(symbol), m_name(name)
{
	m_temp = ' '; 
	max_h_pts = 99;
	m_opponent = nullptr;
}


Actor::~Actor()
{
	delete m_dungeon;
	delete m_weapon;
}

void Actor::moveActor(int f_row, int f_col, int p_row, int p_col)
{	
	if (m_dungeon->getChar(f_row, f_col) == ')' || m_dungeon->getChar(f_row, f_col) == '?' || m_dungeon->getChar(f_row, f_col) == '>' || m_dungeon->getChar(f_row, f_col) == '&')
	{
		char temp_var = m_dungeon->getChar(f_row, f_col);
		m_dungeon->changeGrid(p_row, p_col, m_temp);
		m_dungeon->changeGrid(f_row, f_col, m_symbol);
		m_temp = temp_var;
	}
	else
	{
		m_dungeon->changeGrid(p_row, p_col, m_temp);
		m_temp = m_dungeon->getChar(f_row, f_col);
		m_dungeon->changeGrid(f_row, f_col, m_symbol);
	
	}
	
}

bool Actor::moveMonster(int target_row, int target_col)
{
	return true; 
}

///////MUTATOR FUNCTIONS///////////////////
bool Actor::move(char dir)
{
	bool can_attack = false;

	int maxCanMove = 0;

	switch (dir)
	{
	case ARROW_LEFT: maxCanMove = c_c - 1;
		break;

	case ARROW_RIGHT: maxCanMove = m_dungeon->cols() - c_c;
		break;

	case ARROW_UP: maxCanMove = c_r - 1;
		break;

	case ARROW_DOWN: maxCanMove = m_dungeon->rows() - c_r;
		break;
	}
	if (maxCanMove == 0) //against wall
		return can_attack;

	int rowDelta;
	int colDelta;

	//if not valid move
	if (!(directionToDeltas(dir, rowDelta, colDelta))) return can_attack;
	//if there is a wall
	if (m_dungeon->getChar(c_r + rowDelta, c_c + colDelta) == '#') return can_attack;

	//if there is not a monster there
	if (m_dungeon->getChar(c_r + rowDelta, c_c + colDelta) != 'B' && m_dungeon->getChar(c_r + rowDelta, c_c + colDelta) != 'G'
		&& m_dungeon->getChar(c_r + rowDelta, c_c + colDelta) != 'S' && m_dungeon->getChar(c_r + rowDelta, c_c + colDelta) != 'D')
	{
		//actually move in the array
		moveActor(c_r + rowDelta, c_c + colDelta, c_r, c_c);

		//change the member variables 
		c_r += rowDelta;
		c_c += colDelta;

		return can_attack;
	}

	//there is a monster there, so attack it!
	//Actor* opponent = nullptr;

	if (m_dungeon->ifCritter(c_r + rowDelta, c_c + colDelta))
	{
		vector<Actor*>v = m_dungeon->getCritters();
		for (int i = 0; i < v.size(); i++)
		{
			if (m_dungeon->getCritters()[i]->row() == c_r + rowDelta && m_dungeon->getCritters()[i]->col() == c_c + colDelta)
			{
				m_opponent = m_dungeon->getCritters()[i];
				break;
			}

		}
		can_attack = true;

	}
	return can_attack; 
}

void Player::attack(Actor* opponent)
{
	//calculating if you hit
	bool hit = false;
	string result = "misses";
	int attacker_pts = getDex() + getWeapon()->getDex();
	int defender_pts = opponent->getDex() + opponent->getArmor();
	if (randInt(attacker_pts) >= randInt(defender_pts))
		hit = true;

	if (hit)
	{
		result = "hits";
		int damage_pts = randInt(getStrength() + getWeapon()->getDamage());
		//change opponent's hit_pts
		opponent->changeHits(damage_pts);

		if (opponent->isDead())
		{
			killMonster(opponent);
			cout << name() << ' ' << getWeapon()->getAction() << "at the " << opponent->name() << " dealing a final blow." << endl;
			return;
		}
	}
	//else missed attack

	cout << name() << ' ' << getWeapon()->getAction() << " at the " << opponent->name() << " and " << result << '.' << endl;

}


void Actor::attack(Actor* opponent) //for the monsters to use
{
	//calculating if you hit
	bool hit = false;
	string result = "misses";
	int attacker_pts = d_pts + m_weapon->getDex();
	int defender_pts = opponent->getDex() + opponent->getArmor();
	if (randInt(attacker_pts) >= randInt(defender_pts))
		hit = true;

	if (hit)
	{
		result = "hits";
		int damage_pts = randInt(m_strength + m_weapon->getDamage());
		//change opponent's hit_pts
		opponent->changeHits(damage_pts);

		if (opponent->isDead())
		{
			cout << m_name << ' ' << m_weapon->getAction() << " at the " << opponent->name() << " dealing a final blow." << endl;
			return;
		}
	}
	//else missed attack

	cout << m_name << ' ' << m_weapon->getAction() << " at the " << opponent->name() << " and " << result << '.' << endl;

}

void Actor::switchWeapon(Weapon* w)
{
	m_weapon = w;
}

void Actor::changeTemp(char c)
{
	m_temp = c; 
}

void Actor::drop() //only for monsters 
{}



///////GETTER FUNCTIONS///////////////////

Dungeon* Actor::getDungeon()
{
	return m_dungeon; 
}

bool Actor::directionToDeltas(char dir, int& rowDelta, int& colDelta)
{
	switch (dir)
	{
	case ARROW_UP:     rowDelta = -1; colDelta = 0; break;
	case ARROW_DOWN:   rowDelta = 1; colDelta = 0; break;
	case ARROW_LEFT:   rowDelta = 0; colDelta = -1; break;
	case ARROW_RIGHT:  rowDelta = 0; colDelta = 1; break;
	default:     return false;
	}
	return true;
}

bool Actor::canMove()
{
	//test surrounding areas for #
	return true;
}

bool Actor::isDead()
{
	if (h_pts <= 0) return true;
	else return false;
}

string Actor::name()
{
	return m_name; 
}


void Actor::killMonster(Actor* a)
{

	//delete from vector
	int cur_size = m_dungeon->getCritters().size();

	for (int i = 0; i < cur_size; i++)
	{
		if (a->isDead())//if dead
		{
			for (int i = 0; i < m_dungeon->getCritters().size(); )
			{
				if ((m_dungeon->getCritters()[i])->isDead())
				{
					//erase

					for (int j = i; j < m_dungeon->getCritters().size() - 1; ++j)
					{
						m_dungeon->getCritters()[j] = m_dungeon->getCritters()[j + 1];
					}

					//delete(m_dungeon->getCritters()[m_dungeon->getCritters().size() - 1]);
					m_dungeon->getCritters().pop_back();
					m_dungeon->getPlayer()->changeTemp(' ');
					cur_size = m_dungeon->getCritters().size();
				}
				else ++i;
			}

		}
	}

	//delete from grid
	m_dungeon->changeGrid(a->row(), a->col(), ' ');

	//drop weapon
	a->drop();

	//message 
}

/////////////////////////////////////////////////////////
//				PLAYER
/////////////////////////////////////////////////////////

Player::Player(int row, int col, Dungeon* d, Weapon* w)
	:Actor(d, row, col, 20, w, 2, 2, 2, '@', "Player")
{
	addToInv(w);
} 

Player::~Player()
{
	for (int i = 0; i < m_inventory.size(); i++)
	{
		delete m_inventory[i];
	}
}

void Player::exchangeObject()
{
	bool loop = true;
	int index; 
	char choice = getCharacter();
	while (loop)
	{
		//convert char to index of vector 
		index = choice - 97; //a == 0 
		if (index < 0 || index > m_inventory.size() - 1)
		{
			cout << "Sorry, that is not a valid entry!" << endl;
			//let user pick again
			loop = true;
		}
		else loop = false;//valid user input, break out of loop 
	}

	//determine if scroll or weapon
	Weapon* w = dynamic_cast<Weapon*>(m_inventory[index]); //try to convert to weapon
	if (w != nullptr) //points to a Weapon
	{
		switchWeapon(w);
	}

}

void Player::readScroll()
{
	bool loop = true;
	int index;
	char choice = getCharacter();
	while (loop)
	{
		//convert char to index of vector 
		index = choice - 97; //a == 0 
		if (index < 0 || index > m_inventory.size() - 1)
		{
			cout << "Sorry, that is not a valid entry!" << endl;
			//let user pick again
			loop = true;
		}
		else loop = false;//valid user input, break out of loop 
	}

	//determine if scroll or weapon
	Scroll* s = dynamic_cast<Scroll*>(m_inventory[index]); //try to convert to weapon
	if (s != nullptr) //points to a Weapon
	{
		s->read(this);
		clearScreen();
		getDungeon()->display(""); 
		cout << "You read a " << s->name() << ". ";
		cout << s->message() << endl;

	}

}

void Player::addToInv(Object* w)
{
	if (m_inventory.size() < 25)
	{
		m_inventory.push_back(w);
	}
	else cout << "Your knapsack is full ;you can't pick that up." << endl;
}

void Player::displayInv()
{
	cout << "Inventory:" << endl;
	char first = 'a'; 

	for (int i = 0; i < m_inventory.size(); i++)
	{
		cout << first << ". " << m_inventory[i]->name();
		cout << endl;
		++first; 
	}
}

void Player::pickObject(int r, int c)
{
	//get pointer as specific coordinates 
	for (int i = 0; i < getDungeon()->getObjects().size(); i++)
	{
		//if find object with matching coordintes 
		if (getDungeon()->getObjects()[i]->row() == r && getDungeon()->getObjects()[i]->col() == c)
		{
			//push pointer into invventory 
			addToInv(getDungeon()->getObjects()[i]);
			return; //don't want to add all items with the designated coordinates 
		}
	}
}


/////////////////////////////////////////////////////////
//				BOGEYMEN
/////////////////////////////////////////////////////////

Bogeymen::Bogeymen(int row, int col, Dungeon* d, Weapon* w)
	:Actor(d, row, col, randInt(5) + 5, w, randInt(2) + 1, randInt(2) + 1, 2, 'B', "Bogeymen")
{}

Bogeymen::~Bogeymen()
{}

bool Bogeymen::moveMonster(int target_row, int target_col)
{
	//own row and column, player's row and column
	int c_row = row();
	int c_col = col();
	if (smell(target_row, target_col, SMELL_POWER))
	{
		//futrue row, future col, current row, current col
		moveActor(row(), col(), c_row, c_col);//move on the grid
		if (target_row == row() && target_col == col()) return true;//if lands on Player
		else return false; 

	}
}


bool Bogeymen::smell(int er ,int ec, int smell_power)
{
	return Actor::smell(er, ec, 5);
}


void Bogeymen::drop()
{
	if (trueWithProbability(0.10))
	{
		getDungeon()->addObject("Magic axe", row(), col());
	}
	//Bogeyman 1/10 chance drop magic axe
}


bool Actor::smell(int er, int ec, int smell_power)
{
	//Euclidean distance
	int c_distance = abs(er - c_r) + abs(ec - c_c);
	if (c_distance > smell_power) return false; //can't move, too far away

	//check all four directions 
	//move North
	if (m_dungeon->getChar(c_r - 1, c_c) == '@' ||  m_dungeon->getChar(c_r - 1, c_c) == ' ' || m_dungeon->getChar(c_r - 1, c_c) == '?' || m_dungeon->getChar(c_r - 1, c_c) == ')' || m_dungeon->getChar(c_r - 1, c_c) == '>' || m_dungeon->getChar(c_r - 1, c_c) == '&')//check for valid moving position 
	{
		if ((abs(c_r - 1 - er) + abs(c_c - ec)) < c_distance)  //moving away from monster
		{
			if (m_dungeon->getChar(c_r - 1, c_c) == '@')
			{
				attack(m_dungeon->getPlayer());
				return false; //can't actually update coordinates b/c player is in the way
			}
			c_r -= 1; //update moved coordinate 
			return true;
		}
	}

	//move East
	if (m_dungeon->getChar(c_r, c_c + 1) == '@' || m_dungeon->getChar(c_r, c_c + 1) == ' ' || m_dungeon->getChar(c_r, c_c + 1) == '?' || m_dungeon->getChar(c_r, c_c + 1) == ')' || m_dungeon->getChar(c_r, c_c + 1) == '>' || m_dungeon->getChar(c_r, c_c + 1) == '&')
	{
		if ((abs(c_r - er) + abs(c_c + 1 - ec)) < c_distance) //moving away from monster
		{

			if (m_dungeon->getChar(c_r, c_c + 1) == '@')
			{
				attack(m_dungeon->getPlayer());
				return false;
			}

			c_c += 1;//update moved coordinate 

			return true;
		}
	}



	//move South
	if (m_dungeon->getChar(c_r + 1, c_c) == '@' || m_dungeon->getChar(c_r + 1, c_c) == ' ' || m_dungeon->getChar(c_r + 1, c_c) == '?' || m_dungeon->getChar(c_r + 1, c_c) == ')' || m_dungeon->getChar(c_r + 1, c_c) == '>' || m_dungeon->getChar(c_r + 1, c_r) == '&')
	{
		if ((abs(c_r + 1 - er) + abs(c_c - ec)) < c_distance)
		{//moving away from monster
			if (m_dungeon->getChar(c_r + 1, c_c) == '@')
			{
				attack(m_dungeon->getPlayer());
				return false; 
			}
			c_r += 1; //update moved coordinate 

			return true;
		}
	}


	//move West
	if (m_dungeon->getChar(c_r, c_c - 1) == '@' ||  m_dungeon->getChar(c_r, c_c - 1) == ' ' || m_dungeon->getChar(c_r, c_c - 1) == '?' || m_dungeon->getChar(c_r, c_c - 1) == ')' || m_dungeon->getChar(c_r, c_c - 1) == '>' || m_dungeon->getChar(c_r, c_c - 1) == '&')
	{
		if ((abs(c_r - er) + abs(c_c - 1 - ec)) < c_distance) //moving away from monster
		{
			if (m_dungeon->getChar(c_r, c_c - 1) == '@')
			{
				attack(m_dungeon->getPlayer());
				return false;
			}
			c_c -= 1;//update moved coordinate 

			return true;
		}

	}
		else return false; //can't move
}



/////////////////////////////////////////////////////////
//				SNAKEWOMEN
/////////////////////////////////////////////////////////

SnakeWomen::SnakeWomen(int row, int col, Dungeon* d, Weapon* w)
	:Actor(d, row, col, rand()%4 + 3, w, 2, 3, 3, 'S', "Snake Women")
{
}

SnakeWomen::~SnakeWomen()
{}

bool SnakeWomen::moveMonster(int target_row, int target_col)
{
	//own row and column, player's row and column
	int c_row = row();
	int c_col = col();
	if (smell(target_row, target_col, SMELL_POWER))
	{
		//futrue row, future col, current row, current col
		moveActor(row(), col(), c_row, c_col);//move on the grid
		if (target_row == row() && target_col == col()) return true;//if lands on Player
		else return false;

	}
	
}

void SnakeWomen::drop()
{
	if (trueWithProbability(1.0/3.0) && getDungeon()->ifBlank(row(), col()))
	{
		getDungeon()->addObject("Fangs", row(), col());
	}
	//SnakeWomen 1/3 will drop fangs
}

/////////////////////////////////////////////////////////
//				DRAGON
/////////////////////////////////////////////////////////


Dragon::Dragon(int row, int col, Dungeon* d, Weapon* w)
	:Actor(d, row, col, randInt(5)+20, w, 4, 4, 4, 'D', "Dragon")
{
}

//remember, no move() function

Dragon::~Dragon()
{}

bool Dragon::moveMonster(int target_row, int target_col)
{
	//own row and column, player's row and column
	int c_row = row();
	int c_col = col();
	if (smell(target_row, target_col, SMELL_POWER))
	{
		//futrue row, future col, current row, current col
		moveActor(row(), col(), c_row, c_col);//move on the grid
		if (target_row == row() && target_col == col()) return true;//if lands on Player
		else return false;

	}
	
}

void Dragon::drop()
{
	
	//100% will drop an item
	if (!getDungeon()->ifBlank(row(), col())) return; 

		switch(rand() % 5)
	{
		case 1:
		{
			getDungeon()->addObject("Teleportation", row(), col());
		}
		break;

		case 2:
		{
			getDungeon()->addObject("Improve armor", row(), col());
		}
		break;

		case 3:
		{
			getDungeon()->addObject("Raise strength", row(), col());
		}
		break;

		case 4:
		{
			getDungeon()->addObject("Enhance health", row(), col());
		}
		break;
	}
			
	
}

//new function
void Dragon::regainPts()
{
	//if hit points < max
		//hit pts++
}

/////////////////////////////////////////////////////////
//				GOBLINS
/////////////////////////////////////////////////////////

Goblin::Goblin(int row, int col, Dungeon* d, Weapon* w)
	:Actor(d, row, col, randInt(5) + 15, w, 3, 1, 1, 'G', "Golbin"), SMELL_POWER(getDungeon()->getSmellDistance())
{
	
}

Goblin::~Goblin()
{}

bool Goblin::moveMonster(int target_row, int target_col)
{
	/*
	//own row and column, player's row and column
	int sr = row();
	int sc = col();

	int c_row = row();
	int c_col = col(); 
	if (getDungeon()->getChar(row(), col()) == '@')
	if (smell(sr,sc, target_row, target_col, 5,  0))//HARDCODED SMELL POWER
	{
		//futrue row, future col, current row, current col
		this->moveActor(sr, sc, c_row, c_col);
	}
		else
	{
		//futrue row, future col, current row, current col
		moveActor(row(), col(), c_row, c_col);//move on the grid
		clearScreen();
		getDungeon()->display(""); 
	}
	*/

	//own row and column, player's row and column
	int c_row = row();
	int c_col = col();
	int f_row = row();
	int f_col = col();
	//(int& sr, int& sc, int target_row, int target_col, int smell_power, int& step_count)
	//int step_count = 0; 

	char temp[MAXROWS][MAXCOLS];
	for (int i = 0; i < MAXCOLS; i++)
	{
		for (int j = 0; j < MAXROWS; j++)
		{
			temp[i][j] = getDungeon()->getChar(i, j);
		}
	}

	int north_steps = 0;
	int east_steps = 0;
	int west_steps = 0;
	int south_steps = 0; 

	bool north = smell(f_row-1, f_col, target_row, target_col , SMELL_POWER, north_steps, temp);
	bool east = smell(f_row, f_col+1, target_row, target_col, SMELL_POWER, east_steps, temp);
	bool south = smell(f_row+1, f_col, target_row, target_col, SMELL_POWER, south_steps, temp);
	bool west = smell(f_row, f_col-1, target_row, target_col, SMELL_POWER, west_steps, temp);

	int min = 9999; 
	int row = c_row;
	int col = c_col;
	if (north && north_steps < min)
	{
		row = f_row - 1;
		col = f_col; 
		min = north_steps;
	}
	if (east && east_steps < min)
	{
		row = f_row;
		col = f_col+1;
		min = east_steps;
	}
	if (south && south_steps < min)
	{
		row = f_row + 1;
		col = f_col;
		min = south_steps;
	}
	if (west && west_steps < min)
	{
		row = f_row;
		col = f_col-1;
		min = west_steps;
	}

		//futrue row, future col, current row, current col
		moveActor(row, col, c_row, c_col);//move on the grid
		if (row == getDungeon()->getPlayer()->row() && col == getDungeon()->getPlayer()->col()) return true;
		else return false; 
}


void Goblin::drop()
{
	if (trueWithProbability(1.0 /3.0) && getDungeon()->ifBlank(row(), col()))
	{
		if (trueWithProbability(.50))
		{
			getDungeon()->addObject("Fangs", row(), col());
		}
		else getDungeon()->addObject("Magic axe", row(), col());
	}
	//goblin 1/3 chance drop either magic axe or fangs
}



bool Goblin::smell(int sr, int sc, int target_row, int target_col, int smell_power, int& step_count, char (&temp)[MAXROWS][MAXCOLS])
{
	
	int first_step_r = 0;
	int first_step_c = 0;

	//check # of steps
	if (step_count > smell_power) return false;

	//base case
	//start and finish are the same 
	if (sr == target_row && sc == target_col)
	{
		sr = first_step_r;
		sc = first_step_c;

		return true;
	}

	//record the 1st step taken
	/*if (step_count == 1)
	{
		first_step_r = sr;
		first_step_c = sc;
	}*/

	//recursive steps

	//move North
	if (temp[sr - 1][sc] != 'x' && (getDungeon()->getChar(sr - 1, sc) == ' ' || getDungeon()->getChar(sr - 1, sc) == '?' || getDungeon()->getChar(sr - 1, sc) == ')' || getDungeon()->getChar(sr - 1, sc) == '>' || getDungeon()->getChar(sr - 1, sc) == '&'  || getDungeon()->getChar(sr - 1, sc) == ')' || getDungeon()->getChar(sr - 1, sc) == '>' || getDungeon()->getChar(sr - 1, sc) == '@'))
	{
		++step_count;
		temp[sr - 1][sc] = 'x'; 
		if (smell(sr - 1, sc, target_row, target_col, smell_power, step_count, temp))
		{
			
			return true;
		}
		else
			step_count--;
	}

	
	//move East 
	if (temp[sr][sc + 1] != 'x' && (getDungeon()->getChar(sr, sc + 1) == ' ' || getDungeon()->getChar(sr, sc + 1) == '?' || getDungeon()->getChar(sr, sc + 1) == ')' || getDungeon()->getChar(sr, sc + 1) == '>' || getDungeon()->getChar(sr, sc + 1) == '&' || getDungeon()->getChar(sr - 1, sc) == ')' || getDungeon()->getChar(sr - 1, sc) == '>' || getDungeon()->getChar(sr - 1, sc) == '@'))
	{
		++step_count;
		temp[sr][sc+1] = 'x';
		if (smell(sr, sc + 1, target_row, target_col, smell_power, step_count, temp))
		{

			return true;
		}
		else
			step_count--;
	}

	//move South
	if (temp[sr + 1][sc] != 'x' && (getDungeon()->getChar(sr + 1, sc) == ' ' || getDungeon()->getChar(sr + 1, sc) == '?' || getDungeon()->getChar(sr + 1, sc) == ')' || getDungeon()->getChar(sr + 1, sc) == '>' || getDungeon()->getChar(sr + 1, sc) == '&' || getDungeon()->getChar(sr - 1, sc) == ')' || getDungeon()->getChar(sr - 1, sc) == '>' || getDungeon()->getChar(sr - 1, sc) == '@'))
	{
		++step_count;
		temp[sr + 1][sc] = 'x';
		if (smell(sr + 1, sr, target_row, target_col, smell_power, step_count, temp))
		{
			
			return true;
		}
		else
			step_count--;
	}


	//move West
	if (temp[sr][sc - 1] != 'x' && (getDungeon()->getChar(sr, sc - 1) == ' ' || getDungeon()->getChar(sr, sc - 1) == '?' || getDungeon()->getChar(sr, sc - 1) == ')' || getDungeon()->getChar(sr, sc - 1) == '>' || getDungeon()->getChar(sr, sc - 1) == '&') ||  getDungeon()->getChar(sr - 1, sc) == ')' || getDungeon()->getChar(sr - 1, sc) == '>' || getDungeon()->getChar(sr - 1, sc) == '@')
	{
		++step_count;
		temp[sr][sc - 1] = 'x';
		if (smell(sr, sc - 1, target_row, target_col, smell_power, step_count, temp))
		{
			
			return true; 
		}
		else
			step_count--;
	}


}

/*
bool Goblin::smell(int& sr, int& sc, int target_row, int target_col, int smell_power, int& step_count)
{
	int first_step_r = 0;
	int first_step_c = 0;


	//check # of steps
	if (step_count > 15) return false;

	//base case
	//start and finish are the same 
	if (sr == target_row && sc == target_col)
	{
		sr = first_step_r;
		sc = first_step_c;

		return true;
	}

	//record the 1st step taken
	if (step_count == 1)
	{
		first_step_r = sr;
		first_step_c = sc;
	}

	//recursive steps

	//move North
	if (getDungeon()->getChar(sr - 1, sc) == ' ' || getDungeon()->getChar(sr - 1, sc) == '?' || getDungeon()->getChar(sr - 1, sc) == ')' || getDungeon()->getChar(sr - 1, sc) == '>' || getDungeon()->getChar(sr - 1, sc) == '&')
	{
		++step_count;
		smell(sr -= 1, sc, target_row, target_col, smell_power, step_count);
	}

	//move South
	if (getDungeon()->getChar(sr + 1, sc) == ' ' || getDungeon()->getChar(sr + 1, sc) == '?' || getDungeon()->getChar(sr + 1, sc) == ')' || getDungeon()->getChar(sr + 1, sc) == '>' || getDungeon()->getChar(sr + 1, sc) == '&')
	{
		++step_count;
		smell(sr += 1, sc, target_row, target_col, smell_power, step_count);
	}

	//move East 
	if (getDungeon()->getChar(sr, sc + 1) == ' ' || getDungeon()->getChar(sr, sc + 1) == '?' || getDungeon()->getChar(sr, sc + 1) == ')' || getDungeon()->getChar(sr, sc + 1) == '>' || getDungeon()->getChar(sr, sc + 1) == '&')
	{
		++step_count;
		smell(sr, sc += 1, target_row, target_col, smell_power, step_count);
	}

	//move West
	if (getDungeon()->getChar(sr, sc - 1) == ' ' || getDungeon()->getChar(sr, sc - 1) == '?' || getDungeon()->getChar(sr, sc - 1) == ')' || getDungeon()->getChar(sr, sc - 1) == '>' || getDungeon()->getChar(sr, sc - 1) == '&')
	{
		++step_count;
		smell(sr, sc -= 1, target_row, target_col, smell_power, step_count);
	}

}
*/