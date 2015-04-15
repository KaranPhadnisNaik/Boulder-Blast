#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include "GameConstants.h"
//#include "GraphObject.h"
#include <string>
#include <list>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class StudentWorld;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
		list<Actor*>::iterator iter;
		iter = setofActors.begin();
		for (; iter != setofActors.end(); ++iter)		// note that end is just past the end of the vector
		{

			*iter = nullptr;

		}
		setofActors.clear();

		m_player = nullptr;
		return;
	}

	~StudentWorld()
	{
		list<Actor*>::iterator iter;
		iter = setofActors.begin();
		for (; iter != setofActors.end(); ++iter)		// note that end is just past the end of the vector
		{

			delete *iter;

		}
		setofActors.clear();

		delete m_player;
		return;
	}
	// EMPTY DESCRUCTOR BECAUSE CLEAN UP DOES ALL THE WORK

	virtual int init()
	{

		bonusScoreLeft = 1000;		// sets the bonus score
		numberofJewelsLeft = 0;

	//////////////////////	/*not allowed to use assetDirectory*////////////////////////////////////////
		Level lev(assetDirectory());
		Level::LoadResult result = lev.loadLevel(leveltextfunct());// load different levels ? Right now it can only read the first
		if (result == Level::load_fail_file_not_found || getLevel() > 99){
			return GWSTATUS_PLAYER_WON;
		}
		else if (result == Level::load_fail_bad_format)
			return GWSTATUS_LEVEL_ERROR;
		else if (result == Level::load_success)
		{


			for (int x = 0; x < VIEW_WIDTH; x++)	// refers to the columns
			{
				for (int y = 0; y < VIEW_HEIGHT; y++)		// refers to the rows
				{
					Level::MazeEntry ge = lev.getContentsOf(x, y); // x=5, y=10

					// NOTE: DO YOU WANT TO BE ABLE TO PUSH A object EVERYTIME YOU DISOVER WHERE IT IS

					switch (ge)
					{
					case Level::empty:
									
						break;
					case Level::exit:
						setofActors.push_back(new Exit(x, y, this));
						break;
					case Level::player:
						m_player = new Player (x, y, this);															// CREATE PLAYER HERE
						break;
					case Level::horiz_snarlbot:
						setofActors.push_back(new SnarlBots(x, y, this, GraphObject::right));
						break;
					case Level::vert_snarlbot:
						setofActors.push_back(new SnarlBots(x, y, this, GraphObject::down));
						break;
					case Level::kleptobot_factory:
						setofActors.push_back(new KleptobotFactory(x, y, this, IID_KLEPTOBOT));
						break;
					case Level::angry_kleptobot_factory:
						setofActors.push_back(new KleptobotFactory(x, y, this, IID_ANGRY_KLEPTOBOT));
						break;
					case Level::wall:
						setofActors.push_back(new Wall(x, y, this));
						break;
					case Level::boulder:
						setofActors.push_back(new Boulder(x, y, this));
						break;
					case Level::hole:
						setofActors.push_back(new Hole(x, y, this));
						break;
					case Level::jewel:
						setofActors.push_back(new Jewel(x, y, this));
						numberofJewelsLeft++;		// increases the number of jewels
						break;
					case Level::restore_health:
						setofActors.push_back(new RestoreHealthGoodie(x, y, this));
						break;
					case Level::extra_life:
						setofActors.push_back(new ExtraLifeGoodie(x, y, this));
						break;
					case Level::ammo:
						setofActors.push_back(new AmmoGoodie(x, y, this));
						break;

					}
				}
			}


		}

		//cout << setofActors.size() << endl;

		return GWSTATUS_CONTINUE_GAME;

	}/// SOMETHING WRONG WITH THE BRACES
	
	
	virtual int move()
	{
		  // This code is here merely to allow the game to build, run, and terminate after hitting enter a few times 
		

		
		setDisplayText();
		
		list<Actor*>::iterator iter = setofActors.begin();
		for (; iter != setofActors.end(); ++iter)
		{
			(*iter)->doSomething();
			
			if (m_player->totalHealthLeft() <= 0)
			{
				decLives();
				playSound(SOUND_PLAYER_DIE);
				return GWSTATUS_PLAYER_DIED;
			}
			if (isLevelComplete())			// maybe check if the exit is no longer in the list
			{
				//increaseScoreAppropriately(); // <----- this was already done in the dosomething for the exit
				return GWSTATUS_FINISHED_LEVEL;
			}

		}
		 
		unsigned int livesBeforePlayerdoesSomething = getLives();
		m_player->doSomething();

		// Remove newly-dead actors after each tick
		removeDeadObjects();

		
		// Reduce the current bonus for the Level by one
		reduceBonusScore();

		
		// If the player has collected all of the Jewels on the level, then we
		// must expose the Exit so the player can advance to the next level
		if (numberofJewelsLeft == 0)
		{
			//exposeTheExitInTheMaze(); // make the exit visible
			list<Actor*>::iterator iter = setofActors.begin();
			for (; iter != setofActors.end(); ++iter)		
			{
				if ((*iter)->IdOfActor() == IID_EXIT)
				{
					(*iter)->GraphObject::setVisible(true);
					(*iter)->Actor::setSeeAbilityActor(true);
					playSound(SOUND_REVEAL_EXIT);
					numberofJewelsLeft--;					// this is preventing it from going into the loop again and keep playing sound
				}
			}
			
		}
		// return the proper result
		
		if (getLives() < livesBeforePlayerdoesSomething)
			return GWSTATUS_PLAYER_DIED;
		
		if (isLevelComplete())			// maybe check if the exit is no longer in the list
		{
			//increaseScoreAppropriately(); // <----- this was already done in the dosomething for the exit
			return GWSTATUS_FINISHED_LEVEL;
		}
		// the player hasn’t completed the current level and hasn’t died, so
		// continue playing the current level

		
		return GWSTATUS_CONTINUE_GAME;
	}

	
	
	virtual void cleanUp()
	{
		
		/*SHOULD BE COMPLETE*/
		list<Actor*>::iterator iter;
		iter = setofActors.begin();
		for (; iter != setofActors.end(); ++iter)		// note that end is just past the end of the vector
		{
			
			delete *iter;
		
		}
		setofActors.clear();

		delete m_player;
		return;
	}

	list<Actor*>& listOfActors() { return setofActors; }
	Player* accessPlayer() { return m_player; }

	// implemented in cpp file
	bool isThisSpaceWalkable(int xcoord, int ycoord); 
	bool isthisSpaceEmpty(int xcoord, int ycoord);
	bool isthisSpaceanOBJECT(int xcoord, int ycoord, const int OBJECT_ID);
	bool IsThisSpaceAnOBSTACLEwhenMoving(int xcoord, int ycoord);
	bool IsThisSpaceAnOBSTACLEwhenFiring(int xcoord, int ycoord);
	const int getThisGoodieIDandSetInvisible(int xcoord, int ycoord);
	Actor* ACTORObjectHere(int xcoord, int ycoord, const int OBJECT_ID);
	int isActorHereaKleptobot(int xcoord, int ycoord);
	string leveltextfunct();
	void removeDeadObjects();
	void setDisplayText();
	void reduceBonusScore()
	{
		if (bonusScoreLeft > 0)
		bonusScoreLeft -= 1;
	}


	string formatString(int score, int level, int lives, int health, int ammo, unsigned int bonus);
	

	unsigned int bonusScore() { return bonusScoreLeft; }
	int totalJewelsLeft(){ return numberofJewelsLeft; }
	void reduceJewelsby1() { numberofJewelsLeft--; }
	ShootingDamageActor* ObjectHere(int xcoord, int ycoord, const int OBJECT_ID);
	bool isLevelComplete();

	
	

private:

	list<Actor*> setofActors;		// will contain all actors besides the player
	Player* m_player;
	int bonusScoreLeft;
	int numberofJewelsLeft;

};

#endif // STUDENTWORLD_H_
