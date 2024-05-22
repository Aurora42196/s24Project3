// Game.cpp

#include "Game.h"
#include "Temple.h"
#include "Actor.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
 :m_temple(nullptr), m_player(nullptr)
{
    // create the Temple of Doom
    m_temple = new Temple(m_player, MAXROWS,MAXCOLS, 0);
    
    // Add a player, if the randomly generated coordinate is occupied
    // (i.e. wall or monster already exists there), then a new coordinate will
    // be generated until the addPlayer returns true
    int rPlayer = randInt(1, MAXROWS);
    int cPlayer = randInt(1, MAXCOLS);
    while ( !(addPlayer(rPlayer, cPlayer)) )
    {
        //        cerr << "coordinate out of bounds" << endl;
        rPlayer = randInt(1, MAXROWS);
        cPlayer = randInt(1, MAXCOLS);
    }
    m_temple->setPlayer(m_player);
}

Game::~Game()
{
    delete m_temple;
}

bool Game::addPlayer(int r, int c)
{
    if (!isInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player where a wall exists
    if (m_temple->getGridValue(r-1, c-1) == WALL_SYMBOL)
        return false;

      // Dynamically allocate new Player and add it to the temple
    m_player = new Player(m_temple, r, c);
    m_temple->addToGrid(r, c, PLAYER_SYMBOL);
    return true;
}
void Game::play()
{
    m_temple->display();
    Actor* ap = m_temple->getPlayer();
    if (ap == nullptr)
        return;
    
    char command;
    while ((command = getCharacter()) && command != 'q' && ap->getHealth() > 0)
        {
            switch (command)
            {
                case ARROW_LEFT:
                case ARROW_RIGHT:
                case ARROW_UP:
                case ARROW_DOWN:
                    ap->move(command);
                    break;
    
                default:
                    cout << '\a' << endl; // beep
                    break;
            }
            m_temple->display();
        };
    
//    do {
//        switch (char ch = getCharacter())
//        {
//            case ARROW_LEFT:
//            case ARROW_RIGHT:
//            case ARROW_UP:
//            case ARROW_DOWN:
//                ap->move(ch);
//                break;
//                
//            default:
//                break;
//        }
//        m_temple->display();
//    } while (getCharacter() != 'q' && ap->getHealth() > 0);
}

///////////////////////////////////////////////////////////////////////////
// Helper function implementations
///////////////////////////////////////////////////////////////////////////

/// Checks if any future objects created will remain within the walls of the temple
bool Game::isInBounds(int r ,int c) const
{
    return (r >= 1  &&  r <= m_temple->rows()  &&  c >= 1  &&  c <= m_temple->cols() && m_temple->getGridValue(r-1, c-1) != WALL_SYMBOL);
}

// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons,
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.
