//
//  Temple.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/19/24.
//

#include <iostream>
#include <cstdlib>
#include <queue>
#include "Temple.h"
#include "globals.h"
#include "utilities.h"
#include "Actor.h"
#include "Monster.h"
#include "Weapon.h"
#include "Scroll.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////

Temple::Temple(Player* pp, int nRows, int nCols, int level)
: m_player(pp), m_rows(nRows), m_cols(nCols), m_level(level), m_nMonsters(0), m_nGameObjects(0)
{
    // Checks if the size of the temple floor is valid. If this code runs, something went terribly wrong
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Temple created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    
    // This implementation will start with one big room before trying to create multiple rooms with corridors
    // Fill the grid with walls on the outer border (wall is 2 layers thick)
    // Position (row,col) in the temple coordinate system is represented in
    // the array element grid[row-1][col-1]
    
    int borderRandomizer = randInt(2, 4);
    int r, c;
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
        {
            if (r <= borderRandomizer || r >= MAXROWS-borderRandomizer || c <= borderRandomizer || c >= MAXCOLS-borderRandomizer)
                m_grid[r][c] = WALL_SYMBOL;
            else
                m_grid[r][c] = ' ';
        }
    }
    
    ///////////////////////////////////////////////////////////////////////////
    // Room generator
    ///////////////////////////////////////////////////////////////////////////
    ///rectangle sizes will range from 4x4 to 8x8
    //    // fill grid with walls
    //    int r, c;
    //    for (r = 0; r < rows(); r++)
    //    {
    //        for (c = 0; c < cols(); c++)
    //        {
    //                m_grid[r][c] = WALL_SYMBOL;
    //        }
    //    }
    //
    //    int numRooms = randInt(3, 5);
    //    cerr << "number of rooms generated: " << numRooms << endl;
    //    while (numRooms > 0)
    //    {
    //        int rectangleOriginRow = randInt(1, MAXROWS-1);
    //        int rectangleOriginCol = randInt(1, MAXCOLS-1);
    //        int roomRowSize = randInt(8, 10);
    //        int roomColsize = randInt(8, 10);
    //        for (r = 0; r < roomRowSize; r++)
    //        {
    //            if(rectangleOriginRow + r == MAXROWS-1) // row reached the bottom of the bounds of the temple
    //                break;
    //
    //            for(c = 0; c < roomColsize; c++)
    //            {
    //                if(rectangleOriginCol + c == MAXCOLS-1)
    //                    break;
    //                else
    //                    m_grid[rectangleOriginRow + r][rectangleOriginCol + c] = ' ';
    //            }
    //        }
    //        numRooms--;
    //    }
    
    //Add the staircase if the player is on level 0-3,
    //esle add the golden idol if the player is on level 4
    if (m_level == 4) // place golden idol instead of staircase
    {
        int rObject = randInt(MAXROWS);
        int cObject = randInt(MAXCOLS);
        while (!(addGameObjects(rObject, cObject, 11)))
        {
            rObject = randInt(MAXROWS);
            cObject = randInt(MAXCOLS);
        }
    }
    
    if (m_level <= 3) // place staircase instead of golden idol
    {
        int rObject = randInt(MAXROWS);
        int cObject = randInt(MAXCOLS);
        while (!(addGameObjects(rObject, cObject, 12)))
        {
            rObject = randInt(MAXROWS);
            cObject = randInt(MAXCOLS);
        }
    }
    
    //Add the monsters to the Temple
    
    int M = randInt(2, 5*(m_level+1)+1);
    for (; M > 0; M--)
    {
        int monsterRandomizer;
        if (m_level <= 1)
            monsterRandomizer = randInt(1, 2);
        else if (m_level == 2)
            monsterRandomizer = randInt(1, 3);
        else // m_level > 2
            monsterRandomizer = randInt(1, 4);
        int rMonster = randInt(MAXROWS);
        int cMonster = randInt(MAXCOLS);
        while (!(addMonster(rMonster, cMonster, monsterRandomizer)))
        {
            rMonster = randInt(MAXROWS);
            cMonster = randInt(MAXCOLS);
        }
    }
    
    // Add the game objects to the Temple, only 2-3 weapons or scrolls can
    // be placed in the temple on the first turn
    int numObjects = randInt(2, 3);
    for (; numObjects > 0; numObjects--)
    {
        int gameObjectRandomizer = randInt(1, 7);
        int rObject = randInt(MAXROWS);
        int cObject = randInt(MAXCOLS);
        while (!(addGameObjects(rObject, cObject, gameObjectRandomizer)))
        {
            rObject = randInt(MAXROWS);
            cObject = randInt(MAXCOLS);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////

Temple::~Temple()
{
    // delete the dynamically allocated monsters
    for(int i = 0; i < m_nMonsters; i++)
    {
        delete m_monsters[i];
    }
    m_monsters.clear();
    
    // delete the dynamically allocated game objects
    for(int i = 0; i < m_nGameObjects; i++)
    {
        delete m_objects[i];
    }
    m_objects.clear();
}

///////////////////////////////////////////////////////////////////////////
// Accessor function implementations
///////////////////////////////////////////////////////////////////////////

bool Temple::isPlayerAt(int r, int c) const
{
    return m_player != nullptr  &&
    m_player->row() == r  &&  m_player->col() == c;
}

bool Temple::isWeaponAt(int r, int c) const
{
    for(int i = 0; i < m_nGameObjects; i++)
    {
        int rObject = m_objects[i]->row();
        int cObject = m_objects[i]->col();
        if(rObject == r && cObject == c && m_objects[i]->getSymbol() == ')')
            return true;
    }
    return false;
}

bool Temple::isScrollAt(int r, int c) const
{
    for(int i = 0; i < m_nGameObjects; i++)
    {
        int rObject = m_objects[i]->row();
        int cObject = m_objects[i]->col();
        if(rObject == r && cObject == c && m_objects[i]->getSymbol() == '?')
            return true;
    }
    return false;
}

//bool Temple::isMonsterAt(int r, int c, char& result) const
//{
//    for(int i = 0; i < m_nMonsters; i++)
//    {
////        if(m_monsters[i] != nullptr)
////        {
//            int rMonster = m_monsters[i]->row();
//            int cMonster = m_monsters[i]->col();
//            if(rMonster == r && cMonster == c)
//            {
//                result = m_monsters[i]->getSymbol();
//                return true;
//            }
////        }
//    }
//    return false;
//}

Monster* Temple::isMonsterAt(int r, int c) const
{
    for(int i = 0; i < m_nMonsters; i++)
    {
        //        if(m_monsters[i] != nullptr)
        //        {
        int rMonster = m_monsters[i]->row();
        int cMonster = m_monsters[i]->col();
        if(rMonster == r && cMonster == c)
        {
            return m_monsters[i];
        }
        //        }
    }
    return nullptr;
}

bool Temple::isIdolAt(int r, int c) const
{
    for(int i = 0; i < m_nGameObjects; i++)
    {
        int rObject = m_objects[i]->row();
        int cObject = m_objects[i]->col();
        if(rObject == r && cObject == c && m_objects[i]->getSymbol() == '&')
            return true;
    }
    return false;
}

bool Temple::isStaircaseAt(int r, int c) const
{
    for(int i = 0; i < m_nGameObjects; i++)
    {
        int rObject = m_objects[i]->row();
        int cObject = m_objects[i]->col();
        if(rObject == r && cObject == c && m_objects[i]->getSymbol() == '>')
            return true;
    }
    return false;
}

void Temple::display()
{
    // Position (row,col) in the temple coordinate system is represented in
    // the array element grid[row-1][col-1]
    
    // Draw the grid
    clearScreen();
    for (int r = 0; r < rows(); r++)
    {
        for (int c = 0; c < cols(); c++)
        {
            Monster* monster = isMonsterAt(r, c);
            //            char monsterSymbol;
            if(isWeaponAt(r, c))
            {
                if(isPlayerAt(r, c))
                    cout << PLAYER_SYMBOL;
                //                else if(isMonsterAt(r, c, monsterSymbol))
                else if (monster != nullptr)
                {
                    cout << monster->getSymbol();
                }
                else
                    cout << WEAPON_SYMBOL;
            }
            else if (isScrollAt(r, c))
            {
                if(isPlayerAt(r, c))
                    cout << PLAYER_SYMBOL;
                //                else if(isMonsterAt(r, c, monsterSymbol))
                //                    cout << monsterSymbol;
                else if (monster != nullptr)
                {
                    cout << monster->getSymbol();
                }
                else
                    cout << SCROLL_SYMBOL;
            }
            else if (isIdolAt(r, c))
            {
                if(isPlayerAt(r, c))
                    cout << PLAYER_SYMBOL;
                //                else if(isMonsterAt(r, c, monsterSymbol))
                //                    cout << monsterSymbol;
                else if (monster != nullptr)
                {
                    cout << monster->getSymbol();
                }
                else
                    cout << IDOL_SYMBOL;
            }
            else if (isStaircaseAt(r, c))
            {
                if(isPlayerAt(r, c))
                    cout << PLAYER_SYMBOL;
                //                else if(isMonsterAt(r, c, monsterSymbol))
                //                    cout << monsterSymbol;
                else if (monster != nullptr)
                {
                    cout << monster->getSymbol();
                }
                else
                    cout << STAIRS_SYMBOL;
            }
            else
                cout << m_grid[r][c];
        }
        cout << endl;
    }
    
    // Display Player's statistics
    cout << "Level: " << getLevel()
    << ", Hit points: " << m_player->getHealth()
    << ", Armor: " << m_player->getArmor()
    << ", Strength: " << m_player->getStrength()
    << ", Dexterity: " << m_player->getDexterity();
    cout << endl;
    
    displayActions();
    
    /// Used as a test to verify the player was placed within the temple floor and not on top of any existing walls
    /// This code was also used to see if any game objects got picked up properly
    //    if (m_player != nullptr) {
    //        cerr << "Player is placed at: (" << m_player->row() << ","<< m_player->col() << ")" << endl;
    //    }
        for(int i = 0; i < m_nGameObjects; i++)
        {
            cerr << m_objects[i]->getName() << " is placed at: (" << m_objects[i]->row() << ","<< m_objects[i]->col() << ")" << endl;
        }
    
}

void Temple::displayActions()
{
    cout << endl;
    while (!m_actions.empty())
    {
        cout << m_actions.front() << endl;
        m_actions.pop();
    }
}

///////////////////////////////////////////////////////////////////////////
// Mutator function implementations
///////////////////////////////////////////////////////////////////////////


void Temple::addToGrid(int r, int c, char ch)
{
    m_grid[r][c] = ch;
}

void Temple::removeObjectFromGrid(int i)
{
    m_objects.erase(m_objects.begin()+i);
    m_nGameObjects--;
}

void Temple::removeMonsterFromGrid(int r, int c)
{
    for(int i = 0; i < m_nMonsters; i++)
    {
        int rMonster = m_monsters[i]->row();
        int cMonster = m_monsters[i]->col();
        if(rMonster == r && cMonster == c)
        {
//            m_monsters[i]->setRow(-1);
//            m_monsters[i]->setCol(-1);
            m_monsters[i]->dropItem(m_monsters[i], r, c);
            delete m_monsters[i];
            m_monsters.erase(m_monsters.begin() + i);
            m_nMonsters--;
//            grid(rMonster, cMonster) = ' ';
            return;
        }
    }
}


bool Temple::addMonster(int r, int c, int randomizer)
{
    if (!isInBounds(r, c))
        return false;
    
    // Don't add a monster where a wall or another monster exists
    if (grid(r, c) != WEAPON_SYMBOL && grid(r, c) != SCROLL_SYMBOL && grid(r, c) != ' ')
        return false;
    
    // Dynamically allocate new Monster and add it to the temple
    Monster* newMonster = nullptr;
    switch (randomizer) {
        case 1:
            newMonster = new Snakewoman(this, r, c);
            break;
        case 2:
            newMonster = new Goblin(this, r, c);
            break;
        case 3:
            newMonster = new Bogeyman(this, r, c);
            break;
        case 4:
            newMonster = new Dragon(this, r, c);
            break;
        default:
            return false;
            break;
    }
    m_monsters.push_back(newMonster);
    addToGrid(r, c, m_monsters[m_nMonsters]->getSymbol());
    m_nMonsters++;
    return true;
}

bool Temple::addGameObjects(int r, int c, int randomizer)
{
    if (!isInBounds(r, c))
        return false;
    
    // Don't add a monster where a wall or another object exists
    if (grid(r, c) == WALL_SYMBOL || grid(r, c) == WEAPON_SYMBOL || grid(r, c) == SCROLL_SYMBOL)
        return false;
    
    // Dynamically allocate new Monster and add it to the temple
    GameObject* newGameObject;
    switch (randomizer) {
        case 1:
            newGameObject = new ShortSword(this, r, c);
            break;
        case 2:
            newGameObject = new LongSword(this, r, c);
            break;
        case 3:
            newGameObject = new Mace(this, r, c);
            break;
        case 4:
            newGameObject = new ImproveArmor(this, r, c);
            break;
        case 5:
            newGameObject = new RaiseStrength(this, r, c);
            break;
        case 6:
            newGameObject = new EnhanceHealth(this, r, c);
            break;
        case 7:
            newGameObject = new EnhanceDexterity(this, r, c);
            break;
            // Objects 8, 9, and 10 will be called explicitly since they can
            // only be added to the temple when a monster is killed
        case 8:
            newGameObject = new MagicAxe(this, r, c);
            break;
        case 9:
            newGameObject = new MagicFangs(this, r, c);
            break;
        case 10:
            newGameObject = new Teleportation(this, r, c);
            break;
        case 11:
            newGameObject = new GoldenIdol(this, r, c);
            break;
        case 12:
            newGameObject = new Staircase(this, r, c);
            break;
        default:
            return false;
            break;
    }
    m_objects.push_back(newGameObject);
    m_objects[m_nGameObjects] = newGameObject;
    addToGrid(r, c, m_objects[m_nGameObjects]->getSymbol());
    m_nGameObjects++;
    return true;
}

void Temple::addAction(string action)
{
    m_actions.push(action);
}

void Temple::monstersTakeTurn()
{
    for( int i = 0; i < m_nMonsters; i++)
    {
        Player* pp = getPlayer();
        int rowdiff = m_monsters[i]->row() - pp->row();
        int coldiff = m_monsters[i]->col() - pp->col();
        
        // if orthogonally adjacent, the monster piortizes attacking the player
        
        if(rowdiff == 0  &&  coldiff == 1) //Attack right
        {
            m_monsters[i]->attackActor(ARROW_RIGHT);
        }
        else if (rowdiff == 0  &&  coldiff == -1) //Attack left
        {
            m_monsters[i]->attackActor(ARROW_LEFT);
        }
        else if (coldiff == 0  &&  rowdiff == -1) //Attack downward
        {
            m_monsters[i]->attackActor(ARROW_DOWN);
        }
        else if (coldiff == 0  &&  rowdiff == 1) //Attack upward
        {
            m_monsters[i]->attackActor(ARROW_UP);
        }
        // if the monster is not adjacent, it will move closer to the player
        else
        {
            m_monsters[i]->move();
        }
    }
}


/////////////////////////////////////////////////////////////////////////////
//// Helper function implementations
/////////////////////////////////////////////////////////////////////////////
//
///// Checks if any future objects created will remain within the walls of the temple
bool Temple::isInBounds(int r ,int c) const
{
    return (r >= 0  &&  r < m_rows  &&  c >= 0  &&  c < m_cols && m_grid[r][c] != WALL_SYMBOL);
}
