#include "Actor.h"
#include "StudentWorld.h"
#include <vector>
#include "GraphObject.h"
#include <cstdlib>
#include "GameController.h"
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

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
            setHealth(-10);
            setDirection(82);
            getWorld()->playSound(SOUND_VEHICLE_CRASH);
        }
    }
    else if (getX() >= RIGHT_EDGE)
    {
        if (getDirection() < 90)
        {
            setHealth(-10);
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
    int max_shift_per_tick = 4.0;
    int direction = getDirection();
    int directRadians = direction * M_PI/180;
    double delta_x = cos(directRadians) * max_shift_per_tick;
    double cur_x = getX();
    double cur_y = getY();
    moveTo(cur_x - delta_x, cur_y);
    //move
    

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
//    int vert_speed = this->getVertSpeed() - m_ghost.getVertSpeed();
    // HOW TO GET GHOST RACERS VERT SPEED (DO YOU PASS IN A POINTER TO THE GHOST RACER WHEN YOU CREATE THE BORDERLINES?)
    GhostRacer* ghost = getWorld()->getGhost();
    int vert_speed = this->getVertSpeed() - ghost->getVertSpeed();
    int horiz_speed = this->getHorizSpeed();
//    int horiz_speed = 0;
    int new_y = this->getY() + vert_speed;
    int new_x = this->getX() + horiz_speed;
    this->moveTo(new_x, new_y);
    if (new_x > VIEW_WIDTH || new_x < 0 || new_y > VIEW_HEIGHT || new_y < 0)
    {
        this->setAlive(false);
    }
}
