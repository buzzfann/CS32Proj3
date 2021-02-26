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

//Agent
const int AGENTDEPTH = 0;

//Pedestrian
const int PED_DIR = 0;
const int PED_HP = 2;

//Human
const double HUM_SIZE = 2.0;

//Zombie Pedestrian
const double ZOMB_SIZE = 3.0;
const int STARTING_TICKS = 0;


//Actor superclass
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

class Agent : public Actor
{
public:
    Agent(StudentWorld* world, int imageID, double x, double y, double size, int dir, int hp) :
    Actor{imageID, x, y, dir, size, AGENTDEPTH, true, true, world}, m_hp(hp){};
//    virtual bool isCollisionAvoidanceWorthy() const;

      // Get hit points.
    int getHP() const {return m_hp;}

      // Increase hit points by hp.
    void setHP(int hp) {m_hp = m_hp +hp;}

      // Do what the spec says happens when hp units of damage is inflicted.
      // Return true if this agent dies as a result, otherwise false.
//    virtual bool takeDamageAndPossiblyDie(int hp);

      // What sound should play when this agent is damaged but does not die?
//    virtual int soundWhenHurt();

      // What sound should play when this agent is damaged and dies?
//    virtual int soundWhenDie();
    
private:
    int m_hp;
};

class GhostRacer : public Agent
{
public:
    GhostRacer(StudentWorld* world)
    : Agent(world,IID_GHOST_RACER, INITIAL_X, INITIAL_Y, SIZE, INITIAL_DIRECTION, INITIAL_HEALTH), m_health(INITIAL_HEALTH), m_spray(INITIAL_SPRAY)
    {};
    virtual void doSomething();
//    void setHealth(int amount){m_health = m_health + amount;}
    int getNumSprays() const {return m_spray;}

      // Increase the number of holy water projectiles the object has.
    void increaseSprays(int amt) {m_spray = m_spray + amt;}
//    void decLives()

      // Spin as a result of hitting an oil slick.
    void spin();
private:
    int m_health;
    int m_spray;
    int m_lives;
};

class Pedestrian : public Agent
{
public:
    Pedestrian(StudentWorld* world, int imageID, double x, double y, double size) :
    Agent(world, imageID, x, y, size, PED_DIR, PED_HP), m_movementPlan(0) {} ;
//    virtual int soundWhenHurt() const;
//    virtual int soundWhenDie() const;

      // Get the pedestrian's horizontal speed
//
//      // Set the pedestrian's horizontal speed
//    void setHorizSpeed(int s);
    int getMovementPlan() {return m_movementPlan;}
    void incrementMovementPlan() {m_movementPlan-=1;}
    void setMovementPlan(int num) {m_movementPlan = num;}
      // Move the pedestrian.  If the pedestrian doesn't go off screen and
      // should pick a new movement plan, pick a new plan.
    void moveAndPossiblyPickPlan();
private:
    int m_movementPlan;
};

class HumanPedestrian : public Pedestrian
{
public:
    HumanPedestrian(StudentWorld* world, double x, double y) :
    Pedestrian(world, IID_HUMAN_PED, x, y, HUM_SIZE), m_world(world) {};
    virtual void doSomething();
//    virtual bool beSprayedIfAppropriate();
//    virtual bool takeDamageAndPossiblyDie(int hp);
//    int soundWhenHurt() const {}
private:
    StudentWorld* m_world;
};

class ZombiePedestrian : public Pedestrian
{
public:
    ZombiePedestrian(StudentWorld* world, double x, double y) :
    Pedestrian(world, IID_ZOMBIE_PED, x, y, ZOMB_SIZE), m_world(world), m_ticks(STARTING_TICKS) {};
    virtual void doSomething();
    void getHit(int damage);
    int getTicks() {return m_ticks;}
    void addToTicks(int tickChange) {m_ticks = m_ticks + tickChange;}
    void setTicks(int newTicks) {m_ticks = newTicks;}
//    virtual bool beSprayedIfAppropriate();
private:
    StudentWorld* m_world;
    int m_ticks;
};
//
//class ZombieCab : public Agent
//{
//public:
//    ZombieCab(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual bool beSprayedIfAppropriate();
//};
//
//class Spray : public Actor
//{
//public:
//    Spray(StudentWorld* sw, double x, double y, int dir);
//    virtual void doSomething();
//};
//
//class GhostRacerActivatedObject : public Actor
//{
//public:
//    GhostRacerActivatedObject(StudentWorld* sw, int imageID, double x, double y, double size, int dir);
//    virtual bool beSprayedIfAppropriate();
//
//      // Do the object's special activity (increase health, spin Ghostracer, etc.)
//    virtual void doActivity(GhostRacer* gr) = 0;
//
//      // Return the object's increase to the score when activated.
//    virtual int getScoreIncrease() const = 0;
//
//      // Return the sound to be played when the object is activated.
//    virtual int getSound() const;
//
//      // Return whether the object dies after activation.
//    virtual bool selfDestructs() const = 0;
//
//      // Return whether the object is affected by a holy water projectile.
//    virtual bool isSprayable() const = 0;
//};
//
//class OilSlick : public GhostRacerActivatedObject
//{
//public:
//    OilSlick(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual void doActivity(GhostRacer* gr);
//    virtual int getScoreIncrease() const;
//    virtual int getSound() const;
//    virtual bool selfDestructs() const;
//    virtual bool isSprayable() const;
//};
//
//class HealingGoodie : public GhostRacerActivatedObject
//{
//public:
//    HealingGoodie(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual void doActivity(GhostRacer* gr);
//    virtual int getScoreIncrease() const;
//    virtual bool selfDestructs() const;
//    virtual bool isSprayable() const;
//};
//
//class HolyWaterGoodie : public GhostRacerActivatedObject
//{
//public:
//    HolyWaterGoodie(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual void doActivity(GhostRacer* gr);
//    virtual int getScoreIncrease() const;
//    virtual bool selfDestructs() const;
//    virtual bool isSprayable() const;
//};
//
//class SoulGoodie : public GhostRacerActivatedObject
//{
//public:
//    SoulGoodie(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual void doActivity(GhostRacer* gr);
//    virtual int getScoreIncrease() const;
//    virtual int getSound() const;
//    virtual bool selfDestructs() const;
//    virtual bool isSprayable() const;
//};

#endif // ACTOR_H_
