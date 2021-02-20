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

//Border Lines
const int borderDirection = 0;
const int borderDepth = 2;
const double borderSize = 2.0;
const int borderYSpeed = -4;
const int borderXSpeed = 0;

class Actor : public GraphObject
{
public:
    Actor (int imageID, double startX, double startY, int dir, double size, int depth, bool alive, bool collideable, StudentWorld* world) :
            GraphObject(imageID, startX, startY, dir, size, depth),
            m_world(world), m_alive(alive), m_collideable(collideable), m_depth(depth) {};
    bool retAlive() {return m_alive;};
    
    virtual void doSomething() = 0;
    StudentWorld* getWorld() {return m_world;};
    int getImageID();
    void setSpeed(int xs, int ys);
    int getVertSpeed(){return m_ySpeed;}
    int getHorizSpeed(){return m_xSpeed;}
    bool isAlive(){return m_alive;}
    void setAlive(bool set){m_alive = set;}
    bool isBorderLine();
    bool isCollideable(){return m_collideable;}
    int getDepth(){return m_depth;}
//    virtual ~Actor();
    
private:
    bool m_alive;
    bool m_collideable;
    int m_xSpeed;
    int m_ySpeed;
    int m_depth;
    StudentWorld* m_world;
};

class GhostRacer : public Actor
{
public:
    GhostRacer(StudentWorld* world)
    : Actor(IID_GHOST_RACER, INITIAL_X, INITIAL_Y, INITIAL_DIRECTION, SIZE, DEPTH, true, true, world), m_health(INITIAL_HEALTH), m_spray(INITIAL_SPRAY)
    {};
    virtual void doSomething();
    void setHealth(int amount){m_health = m_health + amount;}
private:
    int m_health;
    int m_spray;
};

class BorderLines : public Actor
{
public:
    BorderLines (int imageID, double startX, double startY, StudentWorld* world) :
    Actor (imageID, startX, startY, borderDirection, borderSize, borderDepth, true, false, world) {
        setSpeed(0, -4);
//        m_ghost =
    };
    virtual void doSomething();
    
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
