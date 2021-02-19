#include "Actor.h"
#include "StudentWorld.h"
#include <vector>
#include "GraphObject.h"
#include <cstdlib>
#include "GameController.h"
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


void GhostRacer::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    if (this->getX() <= getWorld()->LEFT_EDGE)
    {
        if (getDirection() > 90)
        {
            setHealth(-10);
            setDirection(82);
            getWorld()->playSound(SOUND_VEHICLE_CRASH);
        }
    }

}

void Actor::setSpeed(int xs, int ys)
{
    m_xSpeed = xs;
    m_ySpeed = ys;
}

void BorderLines::doSomething()
{
//    int vert_speed = this->getVertSpeed() - m_ghost.getVertSpeed();
    // HOW TO GET GHOST RACERS VERT SPEED (DO YOU PASS IN A POINTER TO THE GHOST RACER WHEN YOU CREATE THE BORDERLINES?)
    GhostRacer* ghost = getWorld()->getGhost();
    int vert_speed = this->getVertSpeed() - ghost->getVertSpeed();
    int horiz_speed = this->getHorizSpeed();
    int new_y = this->getY() + vert_speed;
    int new_x = this-> getX() + horiz_speed;
    this->moveTo(new_x, new_y);
    if (new_x > VIEW_WIDTH || new_x < 0 || new_y > VIEW_HEIGHT || new_y < 0)
    {
        this->setAlive(false);
    }
}
