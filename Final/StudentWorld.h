#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>
#include "Actor.h"


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    ~StudentWorld();
    GhostRacer* getGhost() {return m_ghost;}
    void setGoodieTrue() {addNewGoodie = true;}
//    bool checkPosition(double x, double y);

private:
    GhostRacer* m_ghost;
    std::vector<Actor*> actors;
    int calcDeltaY;
    bool firstTime;
    bool addNewGoodie;
};

#endif // STUDENTWORLD_H_
