//
//  Temple.h
//  s24Project3
//
//  Created by Cameron Maiden on 5/19/24.
//

#ifndef Temple_h
#define Temple_h

#include "globals.h"

class Actor;

class Temple
{
public:
    // Constructor/destructor
    Temple(int nRows, int nCols);
    ~Temple();
    
    // Accessors
    int rows() const { return m_rows; };
    int cols() const { return m_cols; };
    int level() const { return m_level; };
    Actor* player() const { return m_player; };
    void display() const;
    
    // Mutators
    bool addPlayer(int r, int c);
    
    
private:
    
    int m_rows;
    int m_cols;
    int m_level;
    char m_grid[MAXROWS][MAXCOLS];
    Actor* m_player;
    
    ///////////////////////////////////////////////////////////////////////////
    // Class Invariants
    ///////////////////////////////////////////////////////////////////////////
    //
    // 0 < m_rows < MAXROWS
    // 0 < m_cols < MAXCOLS
    // 0 <= m_level < 5 (Levels range from 0 to 4)
    // grid must have 18 rows and 70 columns
    
    
    // Helper functions
    bool isInBounds(int r, int c) const;
};

#endif /* Temple_h */
