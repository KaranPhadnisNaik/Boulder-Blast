#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
void Player::doSomething()
{
	if (!getAliveStatus())
	{
		return;
	}


	if (totalHealthLeft() <= 0){
		setAliveStatus(false);
		studentworld_ptrtoTHIS()->playSound(SOUND_PLAYER_DIE);
		return;
	}

	
	// TAKES IN COMMAND FOR DIRECTION
	int ch;
	if (studentworld_ptrtoTHIS()->getKey(ch))
	{
		// user hit a key this tick!
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			setDirection(left);
			if (getX() > 0 && studentworld_ptrtoTHIS()->isThisSpaceWalkable(getX() - 1, getY()))
			{
				if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX() - 1, getY(), IID_BOULDER))
				{// write a function that finds the boulder at that location (return a pointer to that boulder) and pushes it one space in that direction
					
					studentworld_ptrtoTHIS()->ObjectHere(getX() - 1, getY(), IID_BOULDER)->moveTo(getX() - 2, getY());
				}


				GraphObject::moveTo(getX() - 1, getY());
				
			}
			break;
		case KEY_PRESS_RIGHT:
			setDirection(right);
			if (getX() < VIEW_WIDTH - 1 && studentworld_ptrtoTHIS()->isThisSpaceWalkable(getX() + 1, getY()))
			{
				if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX() + 1, getY(), IID_BOULDER))
				{	// write a function that finds the boulder at that location (return a pointer to that boulder) and pushes it one space in that direction
					studentworld_ptrtoTHIS()->ObjectHere(getX() + 1, getY(), IID_BOULDER)->moveTo(getX() + 2, getY());
				}
				GraphObject::moveTo(getX() + 1, getY());
				
			}
			break;
		case KEY_PRESS_UP:
			setDirection(up);
			if (getY() < VIEW_WIDTH - 1 && studentworld_ptrtoTHIS()->isThisSpaceWalkable(getX(), getY() + 1))
			{
				if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY()+1, IID_BOULDER))
				{	// write a function that finds the boulder at that location (return a pointer to that boulder) and pushes it one space in that direction
					studentworld_ptrtoTHIS()->ObjectHere(getX(), getY() + 1, IID_BOULDER)->moveTo(getX(), getY() + 2);
					// else if that space is a hole
					// delete the boulder at the current and delete the hole at that is next to it 
				}
				GraphObject::moveTo(getX(), getY() + 1);
			}
			break;
		case KEY_PRESS_DOWN:
			setDirection(down);
			if (getY() > 0 && studentworld_ptrtoTHIS()->isThisSpaceWalkable(getX(), getY() - 1))
			{
				if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY() - 1, IID_BOULDER))
				{	// write a function that finds the boulder at that location (return a pointer to that boulder) and pushes it one space in that direction
					studentworld_ptrtoTHIS()->ObjectHere(getX(), getY() - 1, IID_BOULDER)->moveTo(getX(), getY() - 2);
				}
				GraphObject::moveTo(getX(), getY() - 1);
				
			}
			break;
		case KEY_PRESS_ESCAPE:
			studentworld_ptrtoTHIS()->decLives();
		//	studentworld_ptrtoTHIS()->getLives();
			// you need to decrement the values;
			break;
		case KEY_PRESS_SPACE:
			//fire a bullet

			if (m_totalBullets > 0)
			{
				//cout << studentworld_ptrtoTHIS()->listOfActors().size();
				switch (getDirection())		// if the player is faceing a certain direction
				{
					
				case up:
					studentworld_ptrtoTHIS()->listOfActors().push_back(new Bullet(getX(), getY() + 1, studentworld_ptrtoTHIS(), getDirection()));
					break;
				case down:
					studentworld_ptrtoTHIS()->listOfActors().push_back(new Bullet(getX(), getY() - 1, studentworld_ptrtoTHIS(), getDirection()));
					break;
				case right:
					studentworld_ptrtoTHIS()->listOfActors().push_back(new Bullet(getX() + 1, getY(), studentworld_ptrtoTHIS(), getDirection()));
					break;
				case left:
					studentworld_ptrtoTHIS()->listOfActors().push_back(new Bullet(getX() - 1, getY(), studentworld_ptrtoTHIS(), getDirection()));
					break;
				}
				//cout << studentworld_ptrtoTHIS()->listOfActors().size();
				m_totalBullets--;
				
				studentworld_ptrtoTHIS()->playSound(SOUND_PLAYER_FIRE);
			
			// the do somethings of the bullets should continue in the path that they were fired and be destroyed depending on where and does damage if it is a certain type
			}

			break;
		}
	}
}


void Hole::doSomething()
{
	if (!getAliveStatus())
		return;

	if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_BOULDER))	//is space where hole is a boulder?
	{
		//setVisible(false);
		setAliveStatus(false);	
		// set the boulder's alive status to false
		//studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_BOULDER)->setVisible(false);
		studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_BOULDER)->setAliveStatus(false);
	}
}

void Boulder::doSomething()
{
	if (!getAliveStatus())
		return;
	
	if (totalHealthLeft() == 0)
	{
		
		setAliveStatus(false);
		return;
	}
	
}


void Goodies::doSomething()
{
	if (!getAliveStatus())
		return;

	
	int xCoordinateOfGoodie = getX();
	int yCoordinateOfGoodie = getY();

	// if the player lands on where the "goodie" 
	if (studentworld_ptrtoTHIS()->accessPlayer()->getX() == xCoordinateOfGoodie && studentworld_ptrtoTHIS()->accessPlayer()->getY() == yCoordinateOfGoodie && SeeAbilityActor())
		// icrement lives and set the the goodie to dead
	{
		if (IdOfActor() == IID_EXTRA_LIFE){
			// icrement lives and score and set the the goodie to dead
			studentworld_ptrtoTHIS()->incLives();
			studentworld_ptrtoTHIS()->playSound(SOUND_GOT_GOODIE);
			studentworld_ptrtoTHIS()->increaseScore(1000);
			
		}

		if (IdOfActor() == IID_RESTORE_HEALTH)
		{
			// set health to 20 and icnrease score by 500 and set goodie to dead
			studentworld_ptrtoTHIS()->accessPlayer()->setHealth(20);
			studentworld_ptrtoTHIS()->playSound(SOUND_GOT_GOODIE);
			studentworld_ptrtoTHIS()->increaseScore(500);
		}
		
		
		if (IdOfActor() == IID_AMMO)
		{
			int totalBullets = studentworld_ptrtoTHIS()->accessPlayer()->numOfBullets();
			studentworld_ptrtoTHIS()->accessPlayer()->setNumOfBullets(totalBullets + 20);
			studentworld_ptrtoTHIS()->playSound(SOUND_GOT_GOODIE);
			studentworld_ptrtoTHIS()->increaseScore(100);

		}

		if (IdOfActor() == IID_JEWEL)
		{ 
			
			studentworld_ptrtoTHIS()->increaseScore(50);
			studentworld_ptrtoTHIS()->playSound(SOUND_GOT_GOODIE);
			studentworld_ptrtoTHIS()->reduceJewelsby1();

			// check if number of jewels are 0 to make the 

		}

		
		setAliveStatus(false);


	}
}


void Exit::doSomething()
{
	if (!getAliveStatus())
		return;

	if (studentworld_ptrtoTHIS()->accessPlayer()->getX() == getX() && studentworld_ptrtoTHIS()->accessPlayer()->getY() == getY() && SeeAbilityActor())
	{
		int bonus = studentworld_ptrtoTHIS()->bonusScore();
		studentworld_ptrtoTHIS()->increaseScore(2000 + bonus);				// increase the score by 2000 for landing on exit plus the bonus remaing
		studentworld_ptrtoTHIS()->playSound(SOUND_FINISHED_LEVEL);
		setAliveStatus(false);		// so if the exit is no longer alive
		//studentworld_ptrtoTHIS()->playSound(SOUND_REVEAL_EXIT);
	}
}



void Bullet::doSomething()
{
	// get the ID of the object at this location
		// if that object is a player, robot, or boulder do damage and get destroyed

		// if that object is a wall or factor the bullet should get destroyed
	// if the object is anything else do nothing and just go over it



	// check first square
		
	if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_BOULDER))	// boulder
	{


		if (studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_BOULDER)->getAliveStatus()){
			studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_BOULDER)->hitByBullet();
			setAliveStatus(false);
		}
		return;
	}

	if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_SNARLBOT))	// snarlbot
	{
		if (studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_SNARLBOT)->getAliveStatus())
		{
			studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_SNARLBOT)->hitByBullet();
			setAliveStatus(false);
			studentworld_ptrtoTHIS()->playSound(SOUND_ROBOT_IMPACT);
		}
		return;
	}
	if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_KLEPTOBOT))	// kleptobot
	{
		if (studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_KLEPTOBOT)->getAliveStatus())
		{
			studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_KLEPTOBOT)->hitByBullet();
			setAliveStatus(false);
			studentworld_ptrtoTHIS()->playSound(SOUND_ROBOT_IMPACT);
		}
		return;
	}
	if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_ANGRY_KLEPTOBOT))	// angry kleptobots
	{
		if (studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_ANGRY_KLEPTOBOT)->getAliveStatus())
		{
			studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_ANGRY_KLEPTOBOT)->hitByBullet();
			setAliveStatus(false);
			studentworld_ptrtoTHIS()->playSound(SOUND_ROBOT_IMPACT);
		}
		return;
	}

	if (studentworld_ptrtoTHIS()->accessPlayer()->getX() == getX() && studentworld_ptrtoTHIS()->accessPlayer()->getY() == getY())	// player
	{
		if (studentworld_ptrtoTHIS()->accessPlayer()->getAliveStatus())
		{
			studentworld_ptrtoTHIS()->accessPlayer()->hitByBullet();
			setAliveStatus(false);
			studentworld_ptrtoTHIS()->playSound(SOUND_PLAYER_IMPACT);
		}
		return;
	}

	// factor here
	if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_WALL) || studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_ROBOT_FACTORY)) // wall or factor
	{
		setAliveStatus(false);
		return;
	}

	switch (getDirection())
	{

		case up:
			moveTo(getX(), getY() + 1);
			break;
		case down:
			moveTo(getX(), getY() - 1);
			break;
		case right:
			moveTo(getX() + 1, getY());
			break;
		case left:
			moveTo(getX() - 1, getY());
			break;

		}
	
	if(studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_BOULDER))	// boulder
	{


		if (studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_BOULDER)->getAliveStatus()){
			studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_BOULDER)->hitByBullet();
			setAliveStatus(false);
		}
		return;
	}

	if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_SNARLBOT))	// snarlbot
	{
		if (studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_SNARLBOT)->getAliveStatus())
		{
			studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_SNARLBOT)->hitByBullet();
			setAliveStatus(false);
			studentworld_ptrtoTHIS()->playSound(SOUND_ROBOT_IMPACT);
		}
		return;
	}

	if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_KLEPTOBOT))	// kleptobot
	{
		if (studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_KLEPTOBOT)->getAliveStatus())
		{
			studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_KLEPTOBOT)->hitByBullet();
			setAliveStatus(false);
			studentworld_ptrtoTHIS()->playSound(SOUND_ROBOT_IMPACT);
		}
		return;
	}

	if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_ANGRY_KLEPTOBOT))	// angry kleptobots
	{
		if (studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_ANGRY_KLEPTOBOT)->getAliveStatus())
		{
			studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IID_ANGRY_KLEPTOBOT)->hitByBullet();
			setAliveStatus(false);
			studentworld_ptrtoTHIS()->playSound(SOUND_ROBOT_IMPACT);
		}
		return;
	}


	if (studentworld_ptrtoTHIS()->accessPlayer()->getX() == getX() && studentworld_ptrtoTHIS()->accessPlayer()->getY() == getY())	// player
	{
		if (studentworld_ptrtoTHIS()->accessPlayer()->getAliveStatus())
		{
			studentworld_ptrtoTHIS()->accessPlayer()->hitByBullet();
			setAliveStatus(false);
			studentworld_ptrtoTHIS()->playSound(SOUND_PLAYER_IMPACT);
		}
		return;
	}

	// factor here
	if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_WALL) || studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_ROBOT_FACTORY)) // wall or factor
	{
		setAliveStatus(false);
		return;
	}
}

void Robots::setDelayofTime()
{
	unsigned int lvl = studentworld_ptrtoTHIS()->GameWorld::getLevel();
	delay = (28 - lvl) / 4;
	if (delay < 3)
		delay = 3;
}


void SnarlBots::doSomething()
{

	if (!getAliveStatus())
		return;

	if (totalHealthLeft() == 0){
		setAliveStatus(false);
		studentworld_ptrtoTHIS()->playSound(SOUND_ROBOT_DIE);
		studentworld_ptrtoTHIS()->increaseScore(100);
		return;
	}

	
	if (getDelay() == getUntilDelayisOver())
	{
		untilDelayisOverToSTART();
		bool canThisFireABullet = true;
		// fire a bullet and return
		if (IdOfActor() == IID_SNARLBOT)
		{
			if (getDirection() == up )
			{		// if the player is on the same x coordinate and larger y coordinate as the robot
				if (getX() == studentworld_ptrtoTHIS()->accessPlayer()->getX() && studentworld_ptrtoTHIS()->accessPlayer()->getY() > getY())
				{
					for (int y = getY() + 1; y < studentworld_ptrtoTHIS()->accessPlayer()->getY(); y++)// check all the spaces between the player and the robot if there is an object
					{
						if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenFiring(getX(), y)){
							canThisFireABullet = false;
						}

					}
					// fire bullets and return
					if (canThisFireABullet){
					studentworld_ptrtoTHIS()->listOfActors().push_back(new Bullet(getX(), getY() + 1, studentworld_ptrtoTHIS(), getDirection()));
					studentworld_ptrtoTHIS()->playSound(SOUND_ENEMY_FIRE);
					return;
					}

				}
			}
			if( getDirection() == down)
			{
				if (getX() == studentworld_ptrtoTHIS()->accessPlayer()->getX() && studentworld_ptrtoTHIS()->accessPlayer()->getY() < getY())
				{
					for (int y = getY() - 1; y > studentworld_ptrtoTHIS()->accessPlayer()->getY(); y--)
					{
						if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenFiring(getX(), y)){
							canThisFireABullet = false;;
						}

					}
					if (canThisFireABullet){
						studentworld_ptrtoTHIS()->listOfActors().push_back(new Bullet(getX(), getY() - 1, studentworld_ptrtoTHIS(), getDirection()));
						studentworld_ptrtoTHIS()->playSound(SOUND_ENEMY_FIRE);
						return;
					}
				}
				

			}

			if (getDirection() == right)
			{
				if (getY() == studentworld_ptrtoTHIS()->accessPlayer()->getY() && studentworld_ptrtoTHIS()->accessPlayer()->getX() > getX())
				{
					for (int x = getX() + 1; x < studentworld_ptrtoTHIS()->accessPlayer()->getX(); x++)
					{
						if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenFiring(x, getY())){
							canThisFireABullet = false;;
						}

					}
					if (canThisFireABullet){
						studentworld_ptrtoTHIS()->listOfActors().push_back(new Bullet(getX() + 1, getY(), studentworld_ptrtoTHIS(), getDirection()));
						studentworld_ptrtoTHIS()->playSound(SOUND_ENEMY_FIRE);
						return;
					}
				}
			}
			if (getDirection() == left)
			{
				if (getY() == studentworld_ptrtoTHIS()->accessPlayer()->getY() && studentworld_ptrtoTHIS()->accessPlayer()->getX() < getX())
				{
					for (int x = getX() - 1; x > studentworld_ptrtoTHIS()->accessPlayer()->getX(); x--)
					{
						if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenFiring(x, getY())){
							canThisFireABullet = false;;
						}

					}
					if (canThisFireABullet){
						studentworld_ptrtoTHIS()->listOfActors().push_back(new Bullet(getX() - 1, getY(), studentworld_ptrtoTHIS(), getDirection()));
						studentworld_ptrtoTHIS()->playSound(SOUND_ENEMY_FIRE);
						return;
					}

				}
			}


		}
		

		// move and return
		switch (getDirection())
		{
		case up:
			if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() + 1))
			{
				moveTo(getX(), getY() + 1);
			}
			else
			{
				setDirection(down);
			}
			break;
		case down:
			if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() - 1))
			{
				moveTo(getX(), getY() - 1);
			}
			else
			{
				setDirection(up);
			}
			break;
		case right:
			if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() + 1, getY()))
			{
				moveTo(getX()+1, getY());
			}
			else
			{
				setDirection(left);
			}
			break;
		case left:
			if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() - 1, getY()))
			{
				moveTo(getX() - 1, getY());
			}
			else
			{
				setDirection(right);
			}
			break;

		}



	}
	INCREMENT_untilDelayisOver();


}




void KleptoBots::doSomething()
{

	if (!getAliveStatus())
		return;

	if (totalHealthLeft() <= 0){
		setAliveStatus(false);		// set robot to dead
		if (getWhetherContainsGoodie())	// drop goodie where robot dies and make it visible
		{
			studentworld_ptrtoTHIS()->ACTORObjectHere(getStoredGoodieXcoord(), getStoredGoodieYcoord(), getStoredGoodieID())->moveTo(getX(), getY());
			studentworld_ptrtoTHIS()->ACTORObjectHere(getX(), getY(), getStoredGoodieID())->setVisible(true);
			studentworld_ptrtoTHIS()->ACTORObjectHere(getX(), getY(), getStoredGoodieID())->setSeeAbilityActor(true);
		}
		studentworld_ptrtoTHIS()->playSound(SOUND_ROBOT_DIE);	// do whatever score increases needed
		

		// different for angry
		if (IdOfActor() == IID_KLEPTOBOT)
			studentworld_ptrtoTHIS()->increaseScore(10);
		if (IdOfActor() == IID_ANGRY_KLEPTOBOT)
			studentworld_ptrtoTHIS()->increaseScore(20);

		
		return;
	}
	
	if (getDelay() == getUntilDelayisOver())
	{
		untilDelayisOverToSTART();

		//check if the space that the kleptobot is on is a goodie
		if (studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_AMMO) || studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_EXTRA_LIFE) || studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_RESTORE_HEALTH))
		{
			if (!containsGoodie){
				int v1 = rand() % 10;		// chooses random number from  0-9
				if (v1 == 2)
				{
					const int GoodieID = studentworld_ptrtoTHIS()->getThisGoodieIDandSetInvisible(getX(), getY());
					if (GoodieID != IID_JEWEL || GoodieID != 9999)
					{
					storeGoodieInfo(getX(), getY(), GoodieID);		// stores the location of goodie
					studentworld_ptrtoTHIS()->playSound(SOUND_ROBOT_MUNCH);
					containsGoodie = true;
					return;
					}
				}
			}
		}







		// check if it can  fire


		bool canThisFireABullet = true;
		// fire a bullet and return
		if (IdOfActor() == IID_ANGRY_KLEPTOBOT)
		{
			if (getDirection() == up)
			{		// if the player is on the same x coordinate and larger y coordinate as the robot
				if (getX() == studentworld_ptrtoTHIS()->accessPlayer()->getX() && studentworld_ptrtoTHIS()->accessPlayer()->getY() > getY())
				{
					for (int y = getY() + 1; y < studentworld_ptrtoTHIS()->accessPlayer()->getY(); y++)// check all the spaces between the player and the robot if there is an object
					{
						if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenFiring(getX(), y)){
							canThisFireABullet = false;
						}

					}
					// fire bullets and return
					if (canThisFireABullet){
						studentworld_ptrtoTHIS()->listOfActors().push_back(new Bullet(getX(), getY() + 1, studentworld_ptrtoTHIS(), getDirection()));
						studentworld_ptrtoTHIS()->playSound(SOUND_ENEMY_FIRE);
						return;
					}

				}
			}
			if (getDirection() == down)
			{
				if (getX() == studentworld_ptrtoTHIS()->accessPlayer()->getX() && studentworld_ptrtoTHIS()->accessPlayer()->getY() < getY())
				{
					for (int y = getY() - 1; y > studentworld_ptrtoTHIS()->accessPlayer()->getY(); y--)
					{
						if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenFiring(getX(), y)){
							canThisFireABullet = false;;
						}

					}
					if (canThisFireABullet){
						studentworld_ptrtoTHIS()->listOfActors().push_back(new Bullet(getX(), getY() - 1, studentworld_ptrtoTHIS(), getDirection()));
						studentworld_ptrtoTHIS()->playSound(SOUND_ENEMY_FIRE);
						return;
					}
				}


			}

			if (getDirection() == right)
			{
				if (getY() == studentworld_ptrtoTHIS()->accessPlayer()->getY() && studentworld_ptrtoTHIS()->accessPlayer()->getX() > getX())
				{
					for (int x = getX() + 1; x < studentworld_ptrtoTHIS()->accessPlayer()->getX(); x++)
					{
						if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenFiring(x, getY())){
							canThisFireABullet = false;;
						}

					}
					if (canThisFireABullet){
						studentworld_ptrtoTHIS()->listOfActors().push_back(new Bullet(getX() + 1, getY(), studentworld_ptrtoTHIS(), getDirection()));
						studentworld_ptrtoTHIS()->playSound(SOUND_ENEMY_FIRE);
						return;
					}
				}
			}
			if (getDirection() == left)
			{
				if (getY() == studentworld_ptrtoTHIS()->accessPlayer()->getY() && studentworld_ptrtoTHIS()->accessPlayer()->getX() < getX())
				{
					for (int x = getX() - 1; x > studentworld_ptrtoTHIS()->accessPlayer()->getX(); x--)
					{
						if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenFiring(x, getY())){
							canThisFireABullet = false;;
						}

					}
					if (canThisFireABullet){
						studentworld_ptrtoTHIS()->listOfActors().push_back(new Bullet(getX() - 1, getY(), studentworld_ptrtoTHIS(), getDirection()));
						studentworld_ptrtoTHIS()->playSound(SOUND_ENEMY_FIRE);
						return;
					}

				}
			}


		}


















		// implement the movement
		switch (getDirection())
		{
		case up:
			if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() + 1) && distanceBeforeTurning > 0)	// if there is no obstacle in the way
			{
				
				// continue in the direction that you are going
				moveTo(getX(), getY() + 1);
				distanceBeforeTurning--;
				return;
			}
			else if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() + 1) || distanceBeforeTurning == 0 )
			{
				distanceBeforeTurning = rand() % 5 + 1;	// chose number between 1 and 6
				while (true)
				{
					Direction DirTocheck = randomDirectionGenerator();
					if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() + 1) && studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() - 1)
						&& studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() + 1, getY()) && studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() - 1, getY()))
					{
						setDirection(DirTocheck);
						break;
					}
										
					if (DirTocheck == up)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() + 1))
						{
							setDirection(DirTocheck);
								moveTo(getX(), getY() + 1);
								distanceBeforeTurning--;
							
							break;
						}
					}
					if (DirTocheck == down)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() - 1))
						{
							setDirection(DirTocheck);
								moveTo(getX(), getY() - 1);
								distanceBeforeTurning--;
							
							break;
						}
					}
					if (DirTocheck == right)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX()+1, getY()))
						{
							setDirection(DirTocheck);
								moveTo(getX() + 1, getY());
								distanceBeforeTurning--;
							
							break;
						}
					}
					if (DirTocheck == left)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX()-1, getY()))
						{
							setDirection(DirTocheck);
								moveTo(getX() - 1, getY());
								distanceBeforeTurning--;
							
							break;
						}
					}
				}
				return;
			}
			break;
		case down:
			if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() - 1) && distanceBeforeTurning > 0)	// if there is no obstacle in the way
			{

				// continue in the direction that you are going
				studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IdOfActor())->moveTo(getX(), getY() - 1);
				distanceBeforeTurning--;
				return;
			}
			else if (distanceBeforeTurning == 0 || studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() - 1))
			{
				distanceBeforeTurning = rand() % 5 + 1;	// chose number between 1 and 6
				while (true)
				{
					Direction DirTocheck = randomDirectionGenerator();
					if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() + 1) && studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() - 1)
						&& studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() + 1, getY()) && studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() - 1, getY()))
					{
						setDirection(DirTocheck);
						break;
					}

					if (DirTocheck == up)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() + 1))
						{
							setDirection(DirTocheck);
								moveTo(getX(), getY() + 1);
								distanceBeforeTurning--;
							
							break;
						}
					}
					if (DirTocheck == down)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() - 1))
						{
							setDirection(DirTocheck);
								moveTo(getX(), getY() - 1);
								distanceBeforeTurning--;
							
							break;
						}
					}
					if (DirTocheck == right)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() + 1, getY()))
						{
							setDirection(DirTocheck);
								moveTo(getX() + 1, getY());
								distanceBeforeTurning--;
							
							break;
						}
					}
					if (DirTocheck == left)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() - 1, getY()))
						{
							setDirection(DirTocheck);
								moveTo(getX() - 1, getY());
								distanceBeforeTurning--;
							
							break;
						}
					}
				}
				return;
			}
			break;
		case right:
			if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() + 1, getY()) && distanceBeforeTurning > 0)	// if there is no obstacle in the way
			{

				// continue in the direction that you are going
				studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IdOfActor())->moveTo(getX()+1, getY());
				distanceBeforeTurning--;
				return;
			}
			else if (distanceBeforeTurning == 0 || studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX()+1, getY()))
			{
				distanceBeforeTurning = rand() % 5 + 1;	// chose number between 1 and 6
				while (true)
				{
					Direction DirTocheck = randomDirectionGenerator();
					if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() + 1) && studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() - 1)
						&& studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() + 1, getY()) && studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() - 1, getY()))
					{
						setDirection(DirTocheck);
						break;
					}

					if (DirTocheck == up)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() + 1))
						{
							setDirection(DirTocheck);
								moveTo(getX(), getY() + 1);
								distanceBeforeTurning--;
							
							break;
						}
					}
					if (DirTocheck == down)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() - 1))
						{
							setDirection(DirTocheck);
								moveTo(getX(), getY() - 1);
								distanceBeforeTurning--;
							
							break;
						}
					}
					if (DirTocheck == right)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() + 1, getY()))
						{
							setDirection(DirTocheck);
								moveTo(getX() + 1, getY());
								distanceBeforeTurning--;
							
							break;
						}
					}
					if (DirTocheck == left)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() - 1, getY()))
						{
							setDirection(DirTocheck);
								moveTo(getX() - 1, getY());
								distanceBeforeTurning--;
							
							break;
						}
					}
				}
				return;
			}
			break;
		case left:
			if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() - 1, getY()) && distanceBeforeTurning > 0)	// if there is no obstacle in the way
			{

				// continue in the direction that you are going
				studentworld_ptrtoTHIS()->ObjectHere(getX(), getY(), IdOfActor())->moveTo(getX() - 1, getY());
				distanceBeforeTurning--;
				return;
			}
			else if (distanceBeforeTurning == 0 || studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() - 1, getY()))
			{
				distanceBeforeTurning = rand() % 5 + 1;	// chose number between 1 and 6
				while (true)
				{
					Direction DirTocheck = randomDirectionGenerator();
					if (studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() + 1) && studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() - 1)
						&& studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() + 1, getY()) && studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() - 1, getY()))
					{
						setDirection(DirTocheck);
						break;
					}

					if (DirTocheck == up)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() + 1))
						{
							setDirection(DirTocheck);
								moveTo(getX(), getY() + 1);
								distanceBeforeTurning--;
							
							break;
						}
					}
					if (DirTocheck == down)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX(), getY() - 1))
						{
							setDirection(DirTocheck);
						
								moveTo(getX(), getY() - 1);
								distanceBeforeTurning--;
							
							break;
						}
					}
					if (DirTocheck == right)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() + 1, getY()))
						{
							setDirection(DirTocheck);
								moveTo(getX() + 1, getY());
								distanceBeforeTurning--;
							
							break;
						}
					}
					if (DirTocheck == left)
					{
						if (!studentworld_ptrtoTHIS()->IsThisSpaceAnOBSTACLEwhenMoving(getX() - 1, getY()))
						{
							setDirection(DirTocheck);
								moveTo(getX() - 1, getY());
								distanceBeforeTurning--;
							
							break;
						}
					}
				}
				return;
			}
			break;
			
		}



	}
	INCREMENT_untilDelayisOver();
	


}
/*

void KleptoBots::moveBeforeTurning(const int RobotID)
{
	
}
*/








void KleptobotFactory::doSomething()
{


	if (studentworld_ptrtoTHIS()->isActorHereaKleptobot(getX(), getY()))
		return;

	if (countNumKelptobotsInArea() >= 3)
		return;

	if (countNumKelptobotsInArea() < 3)	// there are fewer than 3 kleptobots and the factory's space isnt where a kelptobot is located
	{
		int oneOutta50Chance = rand() % 50;	// picks one number from 0 to 49
		if (oneOutta50Chance == 3)
		{
		
			if (WHATTYPEOFKLEPTOBOTS == IID_ANGRY_KLEPTOBOT && !studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_ANGRY_KLEPTOBOT) && countNumKelptobotsInArea() < 3){
				studentworld_ptrtoTHIS()->listOfActors().push_back(new AngryKleptoBots(getX(), getY(), studentworld_ptrtoTHIS()));
				studentworld_ptrtoTHIS()->playSound(SOUND_ROBOT_BORN);
			}
			if (WHATTYPEOFKLEPTOBOTS == IID_KLEPTOBOT &&  !studentworld_ptrtoTHIS()->isthisSpaceanOBJECT(getX(), getY(), IID_KLEPTOBOT) && countNumKelptobotsInArea() < 3){
					studentworld_ptrtoTHIS()->listOfActors().push_back(new RegularKleptoBots(getX(), getY(), studentworld_ptrtoTHIS()));
					studentworld_ptrtoTHIS()->playSound(SOUND_ROBOT_BORN);
			}
				
		}
	}
}

int KleptobotFactory::countNumKelptobotsInArea()
{
	numKleptobotsInArea = 0;
	// map the region
	int maxXval = getX() + 3;
	int minXval = getX() - 3;
	int maxYval = getY() + 3;
	int minYval = getY() - 3;

	if (maxYval >= 15)
		maxYval = 14;
	if (maxXval >= 15)
		maxXval = 14;
	if (minXval <= 0)
		minXval = 0;
	if (minYval <= 0)
		minYval = 0;

	int x;
	int y;
	for (x = minXval; x <= maxXval; x++)
	{
		for (y = minYval; y <= maxYval; y++)
		{
			numKleptobotsInArea += studentworld_ptrtoTHIS()->isActorHereaKleptobot(x, y);
			//cout << numKleptobotsInArea << endl;
		}
	}

	return numKleptobotsInArea;
}