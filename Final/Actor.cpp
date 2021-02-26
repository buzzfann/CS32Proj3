#include "Actor.h"
#include "StudentWorld.h"
#include <vector>
#include "GraphObject.h"
#include <cstdlib>
#include "GameController.h"
#include <cmath>
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//move an actor
void moveActor(Actor* a)
{
    GhostRacer* ghost = a->getWorld()->getGhost();
    int vert_speed = a->getVertSpeed() - ghost->getVertSpeed();
    int horiz_speed = a->getHorizSpeed();
    int new_y = a->getY() + vert_speed;
    int new_x = a->getX() + horiz_speed;
    a->moveTo(new_x, new_y);
    if (new_x > VIEW_WIDTH || new_x < 0 || new_y > VIEW_HEIGHT || new_y < 0)
    {
        a->setAlive(false);
        return;
    }
}

//check if overlaps
bool checkOverlap(Actor* a, GhostRacer* ghost)
{
//    Compute the delta_x between A and B (which is the absolute value of the distance between A’s center x coordinate and B’s center x coordinate).
//    2. Compute the delta_y between A and B (which is the absolute value of the distance between A’s center y coordinate and B’s center y coordinate).
//    3. Compute the sum of the radiuses of A and B. While most of our graphics are rectangular, you can treat them a bit like a circle to simplify things.
//    4. If delta_x < radius_sum*.25 AND delta_y < radius_sum*.6 then the two objects
//    2 are said to overlap
    double delta_x = abs(a->getX() - ghost->getX());
    double delta_y = abs(a->getY() - ghost->getY());
    double sumRadius = a->getRadius() + ghost->getRadius();
    if (delta_x < sumRadius*0.25 && delta_y < sumRadius*0.6)
    {
        return true;
    }
    else return false;
}

void GhostRacer::doSomething()
{
    int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
    int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
    if (!isAlive())
    {
        return;
    }
    if (this->getX() <= LEFT_EDGE)
    {
        if (getDirection() > 90)
        {
            setHP(-10);
            setDirection(82);
            getWorld()->playSound(SOUND_VEHICLE_CRASH);
        }
    }
    else if (getX() >= RIGHT_EDGE)
    {
        if (getDirection() < 90)
        {
            setHP(-10);
            setDirection(98);
            getWorld()->playSound(SOUND_VEHICLE_CRASH);
        }
    }
    // check if key pressed
    else
    {
        int ch;
        if (getWorld()->getKey(ch))
        {
            switch(ch)
            {
//                case KEY_PRESS_SPACE:
//                    break;
                case KEY_PRESS_LEFT:
                    if (getDirection() >= 114)
                    {
                        break;
                    }
                    setDirection(getDirection() + 8);
                    break;
                case KEY_PRESS_RIGHT:
                    if (getDirection() <= 66)
                    {
                        break;
                    }
                    setDirection(getDirection() - 8);
                    break;
                case KEY_PRESS_UP:
                    if (getVertSpeed() < 5)
                    {
                        setSpeed(getHorizSpeed(), getVertSpeed() + 1);
                    }
                    break;
                case KEY_PRESS_DOWN:
                    if (getVertSpeed() > -1)
                    {
                        setSpeed(getHorizSpeed(), getVertSpeed() - 1);
                    }
                    break;

            }
        }
    }
    //move
    double max_shift_per_tick = 4.0;
    int direction = getDirection();
    double directRadians = direction * M_PI/180;
    double delta_x = cos(directRadians) * max_shift_per_tick;
    double cur_x = getX();
    double cur_y = getY();
    moveTo(cur_x + delta_x, cur_y);

}

void Actor::setSpeed(int xs, int ys)
{
    m_xSpeed = xs;
    m_ySpeed = ys;
}

bool Actor::isBorderLine()
{
    if (getDirection() == borderDirection && getDepth() == borderDepth && isCollideable() == false && getSize() == borderSize)
    {
        return true;
    }
    return false;
}

void BorderLines::doSomething()
{
//    GhostRacer* ghost = getWorld()->getGhost();
//    int vert_speed = this->getVertSpeed() - ghost->getVertSpeed();
//    int horiz_speed = this->getHorizSpeed();
//    int new_y = this->getY() + vert_speed;
//    int new_x = this->getX() + horiz_speed;
//    this->moveTo(new_x, new_y);
//    if (new_x > VIEW_WIDTH || new_x < 0 || new_y > VIEW_HEIGHT || new_y < 0)
//    {
//        this->setAlive(false);
//        return;
//    }
    moveActor(this);
}

//pedestrian movement plan
void Pedestrian::moveAndPossiblyPickPlan()
{
    // generate random int from -3 to 3
    int randInt = rand() % 7 - 3;
    setSpeed(randInt, getVertSpeed());
    int newRandInt = rand() % 29 + 4;
    setMovementPlan(newRandInt);
    if (getHorizSpeed() < 0)
    {
        setDirection(180);
    }
    else
        setDirection(0);
}

void HumanPedestrian::doSomething()
{
    //check if alive
    if (!isAlive())
    {
        return;
    }
    //get ghostRacer
    GhostRacer* ghost = getWorld()->getGhost();
    if (checkOverlap(this, ghost))
    {
        m_world->decLives();
        return;
        //        level end
    }

    //move
    moveActor(this);
    
    //decrement movement plan distance
    incrementMovementPlan();
    if (getMovementPlan() > 0)
        return;
    else
    {
        moveAndPossiblyPickPlan();
    }
}

void ZombiePedestrian::doSomething()
{
    //check if alive
    if (!isAlive())
    {
        return;
    }
    
    GhostRacer* ghost = getWorld()->getGhost();
    if (checkOverlap(this, ghost))
    {
        ghost->setHP(-5);
        getHit(-2);
        return;
    }
    bool isLeft = false;
    bool isRight = false;
    
    if (getX() - ghost->getX() <= 30)
    {
        isRight = true;
    }
    else if (ghost->getX() - getX() <= 30)
    {
        isLeft = true;
    }
    if ((isLeft || isRight) && getY() == ghost->getY())
    {
        setDirection(270);
        if (isLeft && !isRight)
        {
            setSpeed(1, getVertSpeed());
        }
        else if (isRight && !isLeft)
        {
            setSpeed(-1, getVertSpeed());
        }
        else
        {
            setSpeed(0, getVertSpeed());
        }
        addToTicks(-1);
        if (getTicks() <= 0)
        {
            m_world->playSound(SOUND_ZOMBIE_ATTACK);
            setTicks(20);
        }
    }
    // move zombie
    moveActor(this);
    
    if (getMovementPlan() > 0)
    {
        incrementMovementPlan();
        return;
    }
    else
    {
        moveAndPossiblyPickPlan();
    }
}

void ZombiePedestrian::getHit(int damage)
{
    GhostRacer* ghost = getWorld()->getGhost();
    this->setHP(-damage);
    if (getHP() <= 0)
    {
        setAlive(false);
        m_world->playSound(SOUND_PED_DIE);
        if (!checkOverlap(this, ghost))
        {
            int randInt = rand() % 5 + 1;
            if (randInt == 1)
            {
                m_world->setGoodieTrue();
            }
            m_world->increaseScore(150);
        }
    }
    else
    {
        m_world->playSound(SOUND_PED_HURT);
    }
}
