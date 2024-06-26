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
 :m_temple(nullptr), m_player(nullptr), m_level(0), m_smell(goblinSmellDistance)
{
    // create the Temple of Doom
    m_temple = new Temple(m_player, MAXROWS,MAXCOLS, m_level);
    
    // Add a player, if the randomly generated coordinate is occupied
    // (i.e. wall or monster already exists there), then a new coordinate will
    // be generated until the addPlayer returns true
    int rPlayer = randInt(MAXROWS);
    int cPlayer = randInt(MAXCOLS);
    while ( !(addPlayer(rPlayer, cPlayer)) )
    {
        //        cerr << "coordinate out of bounds" << endl;
        rPlayer = randInt(MAXROWS);
        cPlayer = randInt(MAXCOLS);
    }
    m_temple->setPlayer(m_player);
    m_temple->setSmellDistance(goblinSmellDistance);
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
    if (m_temple->grid(r, c) != ' '/* && m_temple->grid(r, c) != WEAPON_SYMBOL && m_temple->grid(r, c) != SCROLL_SYMBOL*/)
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
    m_temple->setSmellDistance(m_smell);
    int rPlayer = randInt(MAXROWS);
    int cPlayer = randInt(MAXCOLS);
    while ( !(isInBounds(rPlayer, cPlayer)) )
    {
        rPlayer = randInt(MAXROWS);
        cPlayer = randInt(MAXCOLS);
    }
    m_player->setTemple(m_temple);
    m_player->setRow(rPlayer);
    m_player->setCol(cPlayer);
    m_temple->addToGrid(rPlayer, cPlayer, m_player->getSymbol());
}

void Game::play()
{
    m_temple->display();
    Actor* ap = m_temple->getPlayer();
    if (ap == nullptr)
        return;
    
    char command;
    while ((command = getCharacter()) && command != 'q' && ap->getHealth() > 0 && !(m_player->hasGoldenIdol()))
        {
            if(trueWithProbability(0.10))
                m_player->heal();
            if(m_player->getSleepTimer() <= 0)
            {
                switch (command)
                {
                    case ARROW_LEFT:
                    case ARROW_RIGHT:
                    case ARROW_UP:
                    case ARROW_DOWN:
                        ap->decidedMove(command);
                        break;
                        
                    case 'i':
                        m_player->showInventory();
                        break;
                        
                    case 'g':
                        m_player->pickUpObject();
                        break;
                        
                    case 'r':
                        m_player->readScroll();
                        break;
                        
                    case 'w':
                        m_player->equipWeapon();
                        break;
                        
                    case 'c': // allows the player to cheat the game
                        m_player->setHealth(50);
                        m_player->setMaxHealth(50);
                        m_player->setStrength(9);
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
            }
            // This means the player is asleep and cannot take any action until they wake up, the monsters take their turn even when the player is asleep
            else
            {
                m_player->wakeUp();
            }
            
            if(command != '>') // The monsters will not take a turn after immediately going to the next level
            {
                m_temple->monstersTakeTurn();
            }
            m_temple->display();

            if(m_player->hasGoldenIdol())
            {
                cout << "Congratulations, you won!" << endl;
                cout << "Press q to quit the game." << endl;
            }
            
            if(m_player->getHealth() <= 0)
            {
                cout << "Press q to quit the game." << endl;
            }
        };
    
    
}


///////////////////////////////////////////////////////////////////////////
// Helper function implementations
///////////////////////////////////////////////////////////////////////////

/// Checks if any future objects created will remain within the walls of the temple
bool Game::isInBounds(int r ,int c) const
{
    return (m_temple->grid(r, c) == ' ');
}

