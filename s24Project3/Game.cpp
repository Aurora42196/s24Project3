// Game.cpp

#include "Game.h"
#include "Temple.h"
#include "Actor.h"
#include "utilities.h"
#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////
///
Game::Game(int goblinSmellDistance)
 :m_temple(nullptr), m_player(nullptr), m_level(0)
{
    // create the Temple of Doom
    m_temple = new Temple(m_player, MAXROWS,MAXCOLS, m_level);
    
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

///////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////
///
Game::~Game()
{
    delete m_temple;
    delete m_player;

}

///////////////////////////////////////////////////////////////////////////
// Mutator function implementations
///////////////////////////////////////////////////////////////////////////
///
bool Game::addPlayer(int r, int c)
{
    if (!isInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player where a wall or monster exists
    if (m_temple->getGridValue(r, c) != ' ' && m_temple->getGridValue(r, c) != WEAPON_SYMBOL && m_temple->getGridValue(r, c) != SCROLL_SYMBOL)
        return false;

      // Dynamically allocate new Player and add it to the temple
    m_player = new Player(m_temple, r, c);
    m_temple->addToGrid(r, c, m_player->getSymbol());
    return true;
}

void Game::goToNextLevel()
{
    delete m_temple;
    m_level++;
    m_temple = new Temple(m_player, MAXROWS,MAXCOLS, m_level);
    int rPlayer = randInt(1, MAXROWS);
    int cPlayer = randInt(1, MAXCOLS);
    while ( !(isInBounds(rPlayer, cPlayer)) )
    {
        //        cerr << "coordinate out of bounds" << endl;
        rPlayer = randInt(1, MAXROWS);
        cPlayer = randInt(1, MAXCOLS);
    }
    m_player->setTemple(m_temple);
    m_player->setRow(rPlayer-1);
    m_player->setCol(cPlayer-1);
    m_temple->addToGrid(rPlayer-1, cPlayer-1, m_player->getSymbol());
//    m_temple->setPlayer(m_player);
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
                case 'i':
                    m_player->showInventory();
                    break;
                case 'g':
                    m_player->pickUpObject();
                    break;
                    
                case 'c': // allows the player to cheat the game
                    m_player->setHealth(50);
                    m_player->setDexterity(9);
                    break;
    
                default:
                    cout << '\a' << endl; // beep
                    break;
                    
                case '>':
                    int rPlayer = m_player->row();
                    int cPlayer = m_player->col();
                    if(m_temple->isPlayerAt(rPlayer,cPlayer) == m_temple->isStaircaseAt(rPlayer, cPlayer))
                    {
                        goToNextLevel();
                    }
                    break;
            }
            m_temple->monstersTakeTurn();
            m_temple->display();
        };
}


///////////////////////////////////////////////////////////////////////////
// Helper function implementations
///////////////////////////////////////////////////////////////////////////

/// Checks if any future objects created will remain within the walls of the temple
bool Game::isInBounds(int r ,int c) const
{
    return (m_temple->getGridValue(r-1, c-1) == ' ');
}

