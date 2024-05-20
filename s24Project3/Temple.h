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
    Actor* player() const { return m_player; };
    void display() const;
    
    // Mutators
    bool addPlayer(int r, int c);
    
private:
    int m_rows;
    int m_cols;
    char m_grid[MAXROWS][MAXCOLS];
    Actor* m_player;
    
    // Helper functions
    bool isInBounds(int r, int c) const;
};

#endif /* Temple_h */
