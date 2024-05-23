//
//  Temple.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/19/24.
//

#include "Temple.h"
#include "globals.h"
#include "utilities.h"
#include "Actor.h"
#include "Monster.h"
#include <iostream>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////

Temple::Temple(Actor* ap, int nRows, int nCols, int level)
: m_player(ap), m_rows(nRows), m_cols(nCols), m_level(level), m_nMonsters(0)
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
//    m_grid = new char[MAXROWS][MAXCOLS];
    int r, c;
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
        {
            if (r <= 1 || r >= MAXROWS-2 || c <= 1 || c >= MAXCOLS-2)
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
    
    //Add the monsters to the dungeon, we'll start with adding only Bogeymen
    int M = randInt(2, 5*(m_level+1)+1);
    for (; M > 0; M--)
    {
        //        cerr << "coordinate out of bounds" << endl;
        int rMonster = randInt(1, MAXROWS);
        int cMonster = randInt(1, MAXCOLS);
        while (!(addMonster(rMonster, cMonster)))
        {
            rMonster = randInt(1, MAXROWS);
            cMonster = randInt(1, MAXCOLS);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////

Temple::~Temple()
{
    // delete the player
    delete m_player;
    
    // delete the dynamically allocated grid
//    for(int i = 0; i < MAXROWS; i++)
//    {
//        delete [] m_grid[i];
//    }
//    delete [] m_grid;
}

///////////////////////////////////////////////////////////////////////////
// Accessor function implementations
///////////////////////////////////////////////////////////////////////////

bool Temple::isPlayerAt(int r, int c) const
{
    return m_player != nullptr  &&
           m_player->row() == r  &&  m_player->col() == c;
}

void Temple::display() const
{
    // Position (row,col) in the temple coordinate system is represented in
    // the array element grid[row-1][col-1]

//    // Indicate player's position
//    if (m_player != nullptr)
//    {
//        char& gridChar = m_grid[m_player->row()-1][m_player->col()-1];
//        if (gridChar == ' ')
//            gridChar = '@';
//    }
    
    // Draw the grid
    clearScreen();
    for (int r = 0; r < rows(); r++)
    {
        for (int c = 0; c < cols(); c++)
        {
                cout << m_grid[r][c];
        }
        cout << endl;
    }
    
    // Display Player's statistics
    cout << "Level: " << getLevel() // This will be changed at a later time
    << ", Hit points: " << m_player->getHealth()
    << ", Armor: " << m_player->getArmor()
    << ", Strength: " << m_player->getStrength()
    << ", Dexterity: " << m_player->getDexterity();
    cout << endl;
    
/// Used as a test to verify the player was placed within the temple floor and not on top of any existing walls
//    if (m_player != nullptr) {
//        cerr << "Player is placed at: (" << m_player->row() << ","<< m_player->col() << ")" << endl;
//    }
    
}

///////////////////////////////////////////////////////////////////////////
// Mutator function implementations
///////////////////////////////////////////////////////////////////////////

//bool Temple::addPlayer(int r, int c)
//{
//    if ( ! isInBounds(r, c))
//        return false;
//
//      // Don't add a player if one already exists
//    if (m_player != nullptr)
//        return false;
//
//      // Don't add a player where a wall exists
//    if (m_grid[r-1][c-1] == WALL_SYMBOL)
//        return false;
//
//      // Dynamically allocate new Player and add it to the temple
//    m_player = new Player(this, r, c);
//    m_grid[r-1][c-1] = PLAYER_SYMBOL;
//    return true;
//}

void Temple::addToGrid(int r, int c, char ch)
{
    m_grid[r-1][c-1] = ch;
}

bool Temple::addMonster(int r, int c)
{
    if (!isInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a monster where a wall or another monster exists
    if (getGridValue(r-1, c-1) != ' ')
        return false;

      // Dynamically allocate new Player and add it to the temple
    Monster* newMonster = new Bogeyman(this, r, c);
    m_monsters.push_back(newMonster);
    addToGrid(r, c, m_monsters[m_nMonsters]->getSymbol());
    m_nMonsters++;
    return true;
}

void Temple::monstersTakeTurn()
{
    for( int i = 0; i < m_nMonsters; i++)
    {
        m_monsters[i]->move();
    }
}


/////////////////////////////////////////////////////////////////////////////
//// Helper function implementations
/////////////////////////////////////////////////////////////////////////////
//
///// Checks if any future objects created will remain within the walls of the temple
bool Temple::isInBounds(int r ,int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols && m_grid[r-1][c-1] != WALL_SYMBOL);
}
