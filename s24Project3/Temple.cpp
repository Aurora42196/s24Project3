//
//  Temple.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/19/24.
//

#include "Temple.h"
#include "globals.h"
#include "utilities.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Temple::Temple(int nRows, int nCols)
    : m_rows(nRows),m_cols(nCols)
{
    // Checks if the size of the temple floor is valid, if this code runs, something went terribly wrong
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Temple created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
}

Temple::~Temple()
{
    
}

void Temple::display() const
{
    // Position (row,col) in the temple coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // This implementation will start with one big room before trying to create multiple rooms with corridors
    // Fill the grid with walls on the outer border (wall is 2 layers thick)
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
        {
            if (r <= 1 || r >= MAXROWS-2 || c <= 1 || c >= MAXCOLS-2)
                grid[r][c] = WALL_SYMBOL;
            else
                grid[r][c] = ' ';
        }
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
}

/// Checks if any future objects created will remain within the walls of the temple
bool Temple::isInBounds(int r ,int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}
