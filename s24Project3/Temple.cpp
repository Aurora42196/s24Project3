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
#include <iostream>
#include <cstdlib>
using namespace std;

Temple::Temple(int nRows, int nCols)
: m_rows(nRows),m_cols(nCols), m_player(nullptr)
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
}

Temple::~Temple()
{
    delete m_player;
}

///////////////////////////////////////////////////////////////////////////
// Accessor function implementations
///////////////////////////////////////////////////////////////////////////

void Temple::display() const
{
    // Draw the grid
    clearScreen();
    for (int r = 0; r < rows(); r++)
    {
        for (int c = 0; c < cols(); c++)
            cout << m_grid[r][c];
        cout << endl;
    }
    
    // Display Player's current status information
    cout << "Level: " << 0 // This will be changed at a later time
    << ", Hit points: " << m_player->health()
    << ", Armor: " << m_player->armor()
    << ", Strength: " << m_player->strength()
    << ", Dexterity: " << m_player->dexterity();
    cout << endl;
    
    /// Used as a test to verify the player was placed within the temple floor and not on top of any existing walls
//    if (m_player != nullptr) {
//        cerr << "Player is placed at: (" << m_player->row() << ","<< m_player->col() << ")" << endl;
//    }
    
    
    
    
}

///////////////////////////////////////////////////////////////////////////
// Mutator function implementations
///////////////////////////////////////////////////////////////////////////

bool Temple::addPlayer(int r, int c)
{
    if ( ! isInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player where a wall exists
    if (m_grid[r-1][c-1] == WALL_SYMBOL)
        return false;

      // Dynamically allocate new Player and add it to the temple
    m_player = new Player(this, r, c);
    m_grid[r-1][c-1] = PLAYER_SYMBOL;
    return true;
}


///////////////////////////////////////////////////////////////////////////
// Helper function implementations
///////////////////////////////////////////////////////////////////////////

/// Checks if any future objects created will remain within the walls of the temple
bool Temple::isInBounds(int r ,int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols && m_grid[r-1][c-1] != WALL_SYMBOL);
}
