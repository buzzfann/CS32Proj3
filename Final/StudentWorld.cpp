#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <cmath>
using namespace std;



GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    calcDeltaY = 0;
    firstTime = true;
    addNewGoodie = false;
    m_ghost = nullptr;
    actors.clear();
}

int StudentWorld::init()
{
    int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
    int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
    // add in new ghostracer
    m_ghost = new GhostRacer( this);
    int N = VIEW_HEIGHT/SPRITE_HEIGHT;
    // add yellow borders
    for (int j = 0; j < N; j++)
    {
        actors.push_back (new BorderLines(IID_YELLOW_BORDER_LINE, LEFT_EDGE, j*SPRITE_HEIGHT, this));
        actors.push_back (new BorderLines(IID_YELLOW_BORDER_LINE, RIGHT_EDGE, j*SPRITE_HEIGHT, this));
    }

    // add white border lines````
    int M = VIEW_HEIGHT / (4*SPRITE_HEIGHT);
    //left white border
    for (int j = 0; j < M; j++)
    {
        actors.push_back (new BorderLines(IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH/3, j * (4*SPRITE_HEIGHT), this));
        actors.push_back (new BorderLines(IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH/3, j * (4*SPRITE_HEIGHT), this));
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    for (Actor* a : actors)
    {
        if (a->isAlive())
        {
            a->doSomething();
            // check if alive
            if (!m_ghost->isAlive())
            {
                return GWSTATUS_PLAYER_DIED;
            }
        }
    }
    m_ghost->doSomething();
    
    
    // remove dead actors
    vector<Actor*>::iterator i = actors.begin();
    for (Actor* a : actors)
    {
        if (!a->isAlive())
        {
            i = actors.erase(i);
            delete a;
        }
        i++;
    }
    // add actors
    calcDeltaY = calcDeltaY + 5 + m_ghost->getVertSpeed();
    int new_border_y = VIEW_HEIGHT - SPRITE_HEIGHT;
    int delta_y = calcDeltaY;
    if (firstTime && calcDeltaY >= SPRITE_HEIGHT)
    {
        actors.push_back (new BorderLines(IID_WHITE_BORDER_LINE, ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH/3, new_border_y, this));
        actors.push_back (new BorderLines(IID_WHITE_BORDER_LINE, ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH/3, new_border_y, this));
        calcDeltaY = 0;
        firstTime = false;
    }
    if (delta_y >= SPRITE_HEIGHT)
    {
        // add yellow lines
        actors.push_back(new BorderLines(IID_YELLOW_BORDER_LINE, ROAD_CENTER - ROAD_WIDTH/2, new_border_y, this));
        actors.push_back(new BorderLines(IID_YELLOW_BORDER_LINE, ROAD_CENTER + ROAD_WIDTH/2, new_border_y, this));
    }
    if (delta_y >= 4*SPRITE_HEIGHT)
    {
        // add white lines
        actors.push_back (new BorderLines(IID_WHITE_BORDER_LINE, ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH/3, new_border_y, this));
        actors.push_back (new BorderLines(IID_WHITE_BORDER_LINE, ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH/3, new_border_y, this));
        calcDeltaY = -2;
    }
    
    //human peds
    int level = getLevel();
    int humFirstMax = 200-level*10;
    int ChanceHumanPed = max(humFirstMax, 30) + 1;
    int randNum = rand() % ChanceHumanPed;
    if (randNum == 0)
    {
        int width =VIEW_WIDTH + 1;
        int height =VIEW_HEIGHT + 1;
        int randX = rand() % width;
        int randY = rand() % height;
        actors.push_back(new HumanPedestrian (this, randX, randY));
    }
    
    //zombie peds
    int zomFirstMax = 100-level*10;
    int ChanceZomPed = max(zomFirstMax, 30) + 1;
    int randZomNum = rand() % ChanceZomPed;
    if (randZomNum == 0)
    {
        int width =VIEW_WIDTH + 1;
        int height =VIEW_HEIGHT + 1;
        int randX = rand() % width;
        int randY = rand() % height;
        actors.push_back(new ZombiePedestrian (this, randX, randY));
    }
    

//    decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (Actor* a : actors)
    {
        delete a;
    }
    actors.clear();
    delete m_ghost;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}
