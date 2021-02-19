#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class StudentWorld;

//GhostRacer
const int INITIAL_DIRECTION = 90;
const double INITIAL_X = 128;
const double INITIAL_Y = 32;
const double SIZE = 4.0;
const int DEPTH = 0;
const double INITIAL_SPEED = 0.0;
const int INITIAL_SPRAY = 10;
const int INITIAL_HEALTH = 100;



class Actor : public GraphObject
{
public:
    Actor (int imageID, double startX, double startY, int dir, double size, int depth, int health, int spray, StudentWorld* world) :
            GraphObject(imageID, startX, startY, dir, size, depth),
            m_world(world), isAlive(true) {};
    bool retAlive() {return isAlive;};
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
    int getImageID();
//    virtual ~Actor();
    
private:
    bool isAlive;
    StudentWorld* m_world;
};

class GhostRacer : public Actor
{
public:
    GhostRacer(int startX, int startY, StudentWorld* world)
    : Actor(IID_GHOST_RACER, INITIAL_X, INITIAL_Y, INITIAL_DIRECTION, SIZE, DEPTH, INITIAL_HEALTH, INITIAL_SPRAY, world), alive(true)
    {};
    virtual void doSomething();
private:
    bool alive;
};

class BorderLines : public Actor
{
public:
    
    virtual void doSomething();
    int new_border_y = VIEW_HEIGHT - SPRITE_HEIGHT;
//    int delta_y = new_border_y -
//    if (delta_y >= SPRITE_HEIGHT)
//    {
//
//    }
    
private:
    
};

//class HumanPed : public Actor
//{
//public:
//    virtual void doSomething();
//private:
//
//};

#endif // ACTOR_H_
