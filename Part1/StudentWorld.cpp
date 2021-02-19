#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_ghost = nullptr;
    actors.clear();
}

int StudentWorld::init()
{
    // add in new ghostracer
    int startingX = 128;
    int startingY = 32;
    m_ghost = new GhostRacer(startingX, startingY, this);
    int N = VIEW_HEIGHT/SPRITE_HEIGHT;
    // add yellow borders
    for (int j = 0; j < N; j++)
    {
        actors.push_back (new BorderLines(IID_YELLOW_BORDER_LINE, LEFT_EDGE, j*SPRITE_HEIGHT, this));
        actors.push_back (new BorderLines(IID_YELLOW_BORDER_LINE, RIGHT_EDGE, j*SPRITE_HEIGHT, this));
    }

    // add white border lines
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
    decLives();
    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
    delete m_ghost;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}
