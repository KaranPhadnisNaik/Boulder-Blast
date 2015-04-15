#include "StudentWorld.h"
#include <string>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;


GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}


// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
string StudentWorld::formatString(int score, int level, int lives, int HitPoints, int ammo, unsigned int bonus)
{
	ostringstream oss;
	oss.fill('0');
	oss << "Score: " << setw(7) << score;
	oss << "  ";
	oss << "Level: " << setw(2) << level;
	oss << "  ";
	oss.fill(' ');
	oss << "Lives: " << setw(2) << lives;
	oss << "  ";
	int PercentageHealth = (HitPoints*5);
	oss << "Health: " << setw(3) << PercentageHealth << "%";
	oss << "  ";
	oss << "Ammo: " << setw(3) << ammo;
	oss << "  ";
	oss << "Bonus: " << setw(4) << bonus;
	string s = oss.str();

	return s;



}


string StudentWorld::leveltextfunct()
{
	ostringstream oss;
	string lvltext = "";
	if (getLevel() < 10)
		lvltext = "level0";
	else if (getLevel() >= 10)
		lvltext = "level";

	oss << lvltext << getLevel() << ".dat";
	string s = oss.str();
	return s;
}


void StudentWorld::setDisplayText()
{
	int score = getScore();
	int level = getLevel();
	unsigned int bonus = bonusScore();
	int livesLeft = getLives();
	int health = accessPlayer()->totalHealthLeft();
	int ammo = accessPlayer()->numOfBullets();

	string s = formatString(score, level, livesLeft, health, ammo, bonus);
	setGameStatText(s);
}



bool StudentWorld::isthisSpaceEmpty(int xcoord, int ycoord)				//checks if a certain space is empty
{
	list<Actor*>::iterator iter = setofActors.begin();
	for (; iter != setofActors.end(); ++iter)		// note that end is just past the end of the vector
	{
		if ((*iter)->getX() == xcoord && (*iter)->getY() == ycoord)	// meaning that there is an object there
		{
			return false;
		}
	}
	return true;
}

bool StudentWorld::isthisSpaceanOBJECT(int xcoord, int ycoord, const int OBJECT_ID)				//checks if a certain space is empty
{
	list<Actor*>::iterator iter = setofActors.begin();
	for (; iter != setofActors.end(); ++iter)		// note that end is just past the end of the vector
	{
		if ((*iter)->getX() == xcoord && (*iter)->getY() == ycoord)	// meaning that there is an object there
		{
			if ((*iter)->IdOfActor() == OBJECT_ID)
				return true;
		}
	}
	return false;
}

//only used for shootingDamage Actors
//THIS IS ONLY USED WHEN CHECKING FOR A SHOOTING DAMAGE ACTOR!!!!!!!!!!!!!!!!!
ShootingDamageActor* StudentWorld::ObjectHere(int xcoord, int ycoord, const int OBJECT_ID)
{
	list<Actor*>::iterator iter = setofActors.begin();
	for (; iter != setofActors.end(); ++iter)		// note that end is just past the end of the vector
	{
		if ((*iter)->getX() == xcoord && (*iter)->getY() == ycoord)	// meaning that there is an object there
		{
			if ((*iter)->IdOfActor() == OBJECT_ID)
			{
				ShootingDamageActor* temp = dynamic_cast<ShootingDamageActor*> (*iter);
				return temp;

				
			}
		}
	}
	return nullptr;
}

Actor* StudentWorld::ACTORObjectHere(int xcoord, int ycoord, const int OBJECT_ID)
{
	list<Actor*>::iterator iter = setofActors.begin();
	for (; iter != setofActors.end(); ++iter)		// note that end is just past the end of the vector
	{
		if ((*iter)->getX() == xcoord && (*iter)->getY() == ycoord)	// meaning that there is an object there
		{
			if ((*iter)->IdOfActor() == OBJECT_ID)
			{
				Actor* temp = (*iter);
				return temp;


			}
		}
	}
	return nullptr;
}



// will get the goodie's ID <-- only call this if you know a goodie is present at the spot
const int StudentWorld::getThisGoodieIDandSetInvisible(int xcoord, int ycoord)
{
	int Id = 9999; // no goodie here!
	list<Actor*>::iterator iter = setofActors.begin();
	for (; iter != setofActors.end(); ++iter)		// note that end is just past the end of the vector
	{
		if ((*iter)->getX() == xcoord && (*iter)->getY() == ycoord)	// meaning that there is an object there
		{
			if ((*iter)->IdOfActor() == IID_JEWEL)
			{
				Id = IID_JEWEL;
				return Id;
			}
			if ((*iter)->IdOfActor() == IID_AMMO )
			{
				 Id = IID_AMMO;
			}
			if ( (*iter)->IdOfActor() == IID_RESTORE_HEALTH )
			{
				 Id = IID_RESTORE_HEALTH;
			}
			if ((*iter)->IdOfActor() == IID_EXTRA_LIFE)
			{
				Id = IID_EXTRA_LIFE;
			}
			(*iter)->setVisible(false);
			(*iter)->setSeeAbilityActor(false);
			return Id;
		}
	}
	return Id;
}


void StudentWorld::removeDeadObjects()
{
	list<Actor*>::iterator iter = setofActors.begin();
	while (iter != setofActors.end())
	{
		if (!(*iter)->getAliveStatus())	// if they are dead we need to remove them
		{
			delete(*iter);
			setofActors.erase(iter++);
		}
		else
			iter++;
	}

	if (!m_player->getAliveStatus())
		delete m_player;

}


bool StudentWorld::isLevelComplete()
{
	list<Actor*>::iterator iter = setofActors.begin();
	for (; iter != setofActors.end(); ++iter)		// if there exists an exit in the list (the game is NOT over)
	{
		if ((*iter)->IdOfActor() == IID_EXIT)
			return false;
	}
	playSound(SOUND_FINISHED_LEVEL);
	return true;
}


bool StudentWorld::isThisSpaceWalkable(int xcoord, int ycoord)		
{
	list<Actor*>::iterator iter = setofActors.begin();
	for (; iter != setofActors.end(); ++iter)		// note that end is just past the end of the vector
	{
		if ((*iter)->getX() == xcoord && (*iter)->getY() == ycoord)	// meaning that there is an object there
		{	
			/*KEEP ADDING ON AS YOU TEST*/
			if ((*iter)->IdOfActor() == IID_HOLE ||(*iter)->IdOfActor() == IID_WALL || (*iter)->IdOfActor() == IID_SNARLBOT
				|| (*iter)->IdOfActor() == IID_KLEPTOBOT || (*iter)->IdOfActor() == IID_ANGRY_KLEPTOBOT || (*iter)->IdOfActor() == IID_ROBOT_FACTORY)
				return false;
			// check if its a boulder
			else if ((*iter)->IdOfActor() == IID_BOULDER)
			{
				switch (m_player->getDirection())
				{
					case GraphObject::up : 
						if (isthisSpaceanOBJECT(xcoord, ycoord + 1, IID_HOLE) || isthisSpaceEmpty(xcoord, ycoord + 1))
							return true;
						break;
					case GraphObject::down:
						if (isthisSpaceanOBJECT(xcoord, ycoord - 1, IID_HOLE) || isthisSpaceEmpty(xcoord, ycoord - 1))
							return true;
						break;
					case GraphObject::right:
						if (isthisSpaceanOBJECT(xcoord + 1, ycoord, IID_HOLE) || isthisSpaceEmpty(xcoord + 1, ycoord))
							return true;
						break;
					case GraphObject::left:
						if (isthisSpaceanOBJECT(xcoord - 1, ycoord, IID_HOLE) || isthisSpaceEmpty(xcoord - 1, ycoord))
							return true;
						break;
				}
				return false;
			}
			
		}

	}
	return true;
}


bool StudentWorld::IsThisSpaceAnOBSTACLEwhenMoving(int xcoord, int ycoord)
{
	if (xcoord == m_player->getX() && ycoord == m_player->getY())
		return true;

	list<Actor*>::iterator iter = setofActors.begin();
	for (; iter != setofActors.end(); ++iter)		// note that end is just past the end of the vector
	{
		if ((*iter)->getX() == xcoord && (*iter)->getY() == ycoord)	// meaning that there is an object there
		{
			if ((*iter)->IdOfActor() == IID_WALL || (*iter)->IdOfActor() == IID_PLAYER || (*iter)->IdOfActor() == IID_SNARLBOT || (*iter)->IdOfActor() == IID_BOULDER || (*iter)->IdOfActor() == IID_HOLE ||
				(*iter)->IdOfActor() == IID_KLEPTOBOT || (*iter)->IdOfActor() == IID_ANGRY_KLEPTOBOT || (*iter)->IdOfActor() == IID_ROBOT_FACTORY)
				return true;
		}
	}
	return false;
}

bool StudentWorld::IsThisSpaceAnOBSTACLEwhenFiring(int xcoord, int ycoord)
{

	list<Actor*>::iterator iter = setofActors.begin();
	for (; iter != setofActors.end(); ++iter)		// note that end is just past the end of the vector
	{
		if ((*iter)->getX() == xcoord && (*iter)->getY() == ycoord)	// meaning that there is an object there
		{
			if ((*iter)->IdOfActor() == IID_WALL || (*iter)->IdOfActor() == IID_SNARLBOT || (*iter)->IdOfActor() == IID_BOULDER || 
				(*iter)->IdOfActor() == IID_KLEPTOBOT || (*iter)->IdOfActor() == IID_ANGRY_KLEPTOBOT || (*iter)->IdOfActor() == IID_ROBOT_FACTORY)
				return true;
		}
	}
	return false;
}


int StudentWorld::isActorHereaKleptobot(int xcoord, int ycoord)
{
	list<Actor*>::iterator iter = setofActors.begin();
	for (; iter != setofActors.end(); ++iter)		// note that end is just past the end of the vector
	{
		if ((*iter)->getX() == xcoord && (*iter)->getY() == ycoord)	// meaning that there is an object there
		{
			if ((*iter)->getIfThisObjectAKelptobot())
				return 1;
			else
				return 0;
		}
	}
	return 0;
}