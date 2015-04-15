#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

//							What about: Bullets, the Exit 
//
//
//																	GraphObject
//																	     |
//											  --------------------------Actor---------------------------------------
//											 /					|			|										|
//								ShootingDamageActor				Factory		  Walls		     		 -----------Goodies-----------------------
//								/		  |		  \												/			 |					   |	  \
//							Robots		Player		Hole						Restore Health Goodies	   Extra Life Goodies	Jewel	Ammo Goodies
//							/	\	
//					SnarlBots	Kleptobots
//								/       \
//						AngryKleptobot  RegularKleptobot
//
//
//

class StudentWorld;

class Actor : public  GraphObject
{
public:
	Actor(const int imageID, int startX, int startY, Direction startDirection, StudentWorld* StuWrldAccess) : GraphObject(imageID, startX, startY, startDirection)
		, m_aliveStatus(true), ActorID(imageID), whetherseeAbleActor(true), m_StuworldAccessThisObj(StuWrldAccess), isThisObjectAKelptobot(false)
	{
		GraphObject::setVisible(true);
	}
	virtual ~Actor(){ ; }

	virtual void doSomething() = 0;		// every actor will do something different
			
	const int IdOfActor(){ return ActorID; }
	StudentWorld* studentworld_ptrtoTHIS(){ return m_StuworldAccessThisObj; }

	bool getAliveStatus(){ return m_aliveStatus; }
	void setAliveStatus(bool setStatus){ m_aliveStatus = setStatus; }

	void setSeeAbilityActor(bool setto) { whetherseeAbleActor = setto; }
	bool SeeAbilityActor(){ return whetherseeAbleActor; }

	void setisThisObjectAKelptobot(bool TrueORFalse){ isThisObjectAKelptobot = TrueORFalse; }
	bool getIfThisObjectAKelptobot(){ return isThisObjectAKelptobot; }

private:
	
	bool m_aliveStatus;		// if something gets destroyed or picked up its no longer alive
	bool whetherseeAbleActor;
	const int ActorID;
	StudentWorld* m_StuworldAccessThisObj;	// you use this so that other objects can access it
	bool isThisObjectAKelptobot;

};

class ShootingDamageActor : public Actor		// for actors that shoot stuff and get hit and have damage		// DO HOLES HAVE A DIRECTION???
{
	// Notice: Player, robots, and holes can be attacked but only players and robots can shoot
			// holes were attacked by boulders and bullets can attack the player or robot
public:
	ShootingDamageActor(int imageID, int startX, int startY, Direction startDirection, StudentWorld* StuWrldAccess) : Actor(imageID, startX, startY, startDirection, StuWrldAccess) { ; }
	//~ShootingDamageActor();

	void setHealth(int ammtOfHealthToSetTo)
	{
		m_totalHealthLeft = ammtOfHealthToSetTo;
	}
	virtual ~ShootingDamageActor(){ ; }

	int totalHealthLeft(){ return m_totalHealthLeft; }
	//void setTotalHealth(int health){	m_totalHealthLeft = health;	}
	void hitByBullet() { m_totalHealthLeft -= 2; }
	

private:

	int m_totalHealthLeft;
	
	
};


class Player : public ShootingDamageActor
{
public:
	Player(int startX, int startY, StudentWorld* StuWrldAccess) : ShootingDamageActor(IID_PLAYER, startX, startY, right, StuWrldAccess)
	{
		ShootingDamageActor::setHealth(20);		// the initial health of the Player is 20
		//GraphObject::setVisible(true);
		setNumOfBullets(20);		// the number of bullets is 20

						// Still need to set the ammo.............
	}
	void setNumOfBullets(int number) { m_totalBullets = number; }
	int numOfBullets(){ return m_totalBullets; }
	virtual ~Player() {}
	void doSomething();		// every actor will do something different
	
private:

	int m_totalBullets;
};

class Bullet : public Actor
{
public: 
	Bullet(int startX, int startY, StudentWorld* StuWrldAccess, Direction whatDirection) : Actor(IID_BULLET, startX, startY, whatDirection, StuWrldAccess)
		, m_continueInDirection(whatDirection)
	{}
	virtual ~Bullet(){}
	void doSomething();

private:
	Direction m_continueInDirection;

};

class Hole : public ShootingDamageActor
{
public:
	Hole(int startX, int startY, StudentWorld* StuWrldAccess) : ShootingDamageActor(IID_HOLE, startX, startY, none, StuWrldAccess)
	{
		// ??? ShootingDamageActor::setHealth();
		//GraphObject::setVisible(true);
	}
	virtual~Hole(){}
	void doSomething();

private:
};

class Boulder : public ShootingDamageActor 
{
public:
	Boulder(int startX, int startY, StudentWorld* StuWrldAccess) : ShootingDamageActor(IID_BOULDER, startX, startY, none, StuWrldAccess)
	{
		//GraphObject::setVisible(true);
		ShootingDamageActor::setHealth(10);
	}
	virtual ~Boulder(){}
	void doSomething();
private:

};




 

class Wall : public Actor		// walls have start direction of none
{
public:
	Wall(int startX, int startY, StudentWorld* StuWrldAccess) : Actor(IID_WALL, startX, startY, none, StuWrldAccess) 
	{ 
		//GraphObject::setVisible(true);
	}
	
	virtual ~Wall(){}
	void doSomething() {}		// every actor will do something different
	
private:

};

class Exit : public Actor
{
public:
	Exit(int startX, int startY, StudentWorld* StuWrldAccess) : Actor(IID_EXIT, startX, startY, none, StuWrldAccess)
	{
		GraphObject::setVisible(false);
		Actor::setSeeAbilityActor(false);
	}

	void doSomething();
	virtual ~Exit()
	{}
private:

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////									GOODIES +																    //////////////
//////////////											DERIVED																//////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Goodies : public Actor
{
public:
	Goodies(const int imageID, int startX, int startY, Direction startDirection, StudentWorld* StuWrldAccess) : Actor(imageID, startX, startY, startDirection, StuWrldAccess) {}
	void doSomething();			// all goodies essentially do the same thing besides a few things and check for those few things based on their IDs
	virtual ~Goodies() {}
};


class ExtraLifeGoodie : public Goodies
{
public: 

	ExtraLifeGoodie(int startX, int startY, StudentWorld* StuWrldAccess) : Goodies(IID_EXTRA_LIFE, startX, startY, none, StuWrldAccess)
	{ 
		//GraphObject::setVisible(true);
	}
	virtual ~ExtraLifeGoodie(){}
	
private:

};

class RestoreHealthGoodie : public Goodies
{
public:
	RestoreHealthGoodie(int startX, int startY, StudentWorld* StuWrldAccess) : Goodies(IID_RESTORE_HEALTH, startX, startY, none, StuWrldAccess)
	{
		//GraphObject::setVisible(true);
	}
	virtual ~RestoreHealthGoodie() {}
private:
};

class AmmoGoodie : public Goodies
{
public:
	AmmoGoodie(int startX, int startY, StudentWorld* StuWrldAccess) : Goodies(IID_AMMO, startX, startY, none, StuWrldAccess)
	{
		//GraphObject::setVisible(true);
	}
	virtual ~AmmoGoodie(){}
private:
};

class Jewel : public Goodies
{
public:
	Jewel(int startX, int startY, StudentWorld* StuWrldAccess) : Goodies(IID_JEWEL, startX, startY, none, StuWrldAccess)
	{
		//GraphObject::setVisible(true);
	}
	virtual ~Jewel() {}
private:
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////									Robots +																    //////////////
//////////////											DERIVED																//////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Robots : public ShootingDamageActor
{
public:
	Robots(int startX, int startY, StudentWorld* StuWrldAccess, Direction whatDirection, const int objectID) : ShootingDamageActor(objectID, startX, startY, whatDirection, StuWrldAccess)
		, delay(0), untilDelayisOver(1)
	{
		//GraphObject::setVisible(true);
		//ShootingDamageActor::setHealth(10);
		setDelayofTime();
	}
	
	virtual ~Robots() {};

	//ONLY CALLED IN THE CONSTRUCTOR
	void setDelayofTime();

	int getDelay() { return delay; }
	int getUntilDelayisOver(){ return untilDelayisOver; }
	void setDelay(int x) { delay = x; }
	void untilDelayisOverToSTART() { untilDelayisOver = 1; }
	void INCREMENT_untilDelayisOver() { untilDelayisOver++; }


	

private:


	int delay;
	int untilDelayisOver;
	

};

class SnarlBots : public Robots
{
public:
	SnarlBots(int startX, int startY, StudentWorld* StuWrldAccess, Direction whatDirection) : Robots(startX, startY, StuWrldAccess, whatDirection, IID_SNARLBOT)
		
	{
		//GraphObject::setVisible(true);
		ShootingDamageActor::setHealth(10);
		
	}
	virtual ~SnarlBots() {}


	
	void doSomething();
private:

};


class KleptoBots : public Robots
{
public:
	KleptoBots(int startX, int startY, StudentWorld* StuWrldAccess,const int RobotID) : Robots(startX, startY, StuWrldAccess, right, RobotID)
		, containsGoodie(false)
	{
		//GraphObject::setVisible(true);
		
		distanceBeforeTurning = rand() % 5 + 1;			// generates a random number between 1 and 6 inclusive

	}

	virtual ~KleptoBots() {}

	//only used by Kleptobots//////////////////////////
	void setContainsGoodie(bool statement){ containsGoodie = statement; }
	bool getWhetherContainsGoodie() { return containsGoodie; }

	void moveBeforeTurning();

	void storeGoodieInfo(int xcoord, int ycoord, int GoodieID)
	{
		StoredGoodieXcoord = xcoord;
		StoredGoodieYcoord = ycoord;
		StoredGoodieID = GoodieID;
	}

	int getStoredGoodieXcoord() { return StoredGoodieXcoord; }
	int getStoredGoodieYcoord() { return StoredGoodieYcoord; }
	int getStoredGoodieID() { return StoredGoodieID; }

	Direction randomDirectionGenerator()
	{
		int randomVal = rand()%4+1;
		switch(randomVal)
		{
		case 1: 
			return up;
		case 2:
			return down;
		case 3:
			return right;
		case 4:
			return left;
		}
	}

	void doSomething();
private:

	bool containsGoodie;
	int StoredGoodieXcoord;
	int StoredGoodieYcoord;
	int StoredGoodieID;

	int distanceBeforeTurning;

};


class RegularKleptoBots : public KleptoBots
{
public:

	RegularKleptoBots(int startX, int startY, StudentWorld* StuWrldAccess) : KleptoBots(startX, startY, StuWrldAccess, IID_KLEPTOBOT)
	{
		setisThisObjectAKelptobot(true);
		ShootingDamageActor::setHealth(5);
	}
	virtual	~RegularKleptoBots(){}

private:



};


class AngryKleptoBots : public KleptoBots
{
public:

	AngryKleptoBots(int startX, int startY, StudentWorld* StuWrldAccess) : KleptoBots(startX, startY, StuWrldAccess, IID_ANGRY_KLEPTOBOT)
	{
		setisThisObjectAKelptobot(true);
		ShootingDamageActor::setHealth(8);
	}
	virtual ~AngryKleptoBots() {}


private:



};


class KleptobotFactory : public Actor
{
public:
	KleptobotFactory(int startX, int startY, StudentWorld* StuWrldAccess, const int KelptobotType) : Actor(IID_ROBOT_FACTORY, startX, startY, none, StuWrldAccess)
		, WHATTYPEOFKLEPTOBOTS(KelptobotType), numKleptobotsInArea(0)
	{}
	 virtual ~KleptobotFactory() {}
	void doSomething();
	int countNumKelptobotsInArea();

private:
	const int WHATTYPEOFKLEPTOBOTS;	
	int numKleptobotsInArea;

};









#endif // ACTOR_H_
