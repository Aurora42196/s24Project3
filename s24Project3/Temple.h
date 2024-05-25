//
//  Temple.h
//  s24Project3
//
//  Created by Cameron Maiden on 5/19/24.
//

#ifndef Temple_h
#define Temple_h

#include <vector>
#include "globals.h"
#include "utilities.h"
#include "Game.h"


class Actor;
class Monster;
class GameObject;

class Temple
{
public:
    // Constructor/destructor
    Temple(Actor* ap, int nRows, int nCols, int level);
    ~Temple();
    
    // Accessors
        // Inline function implementations
    int rows() const { return m_rows; };
    int cols() const { return m_cols; };
    int getLevel() const { return m_level; };
    char& getGridValue( int r, int c) { return m_grid[r-1][c-1]; };
    Actor* getPlayer() const { return m_player; };
    bool isPlayerAt(int r, int c) const;
    bool isWeaponAt(int r, int c) const;
    bool isScrollAt(int r, int c) const;
    bool isMonsterAt(int r, int c, char& result) const;
    void display() const;
    
    
    // Mutators
    void setPlayer(Actor* ap) { m_player = ap; };
//    bool addPlayer(int r, int c);
    void addToGrid(int r, int c, char ch);
    bool addMonster(int r, int c, int randomizer);
    bool addGameObjects(int r, int c, int randomizer);
    void monstersTakeTurn();

    
    
private:
    // Data members
    Actor* m_player;
    int m_rows;
    int m_cols;
    int m_level;
    int m_nMonsters;
    int m_nGameObjects;
    char m_grid[MAXROWS][MAXCOLS];
    std::vector<Monster*> m_monsters;
    std::vector<GameObject*> m_objects;
    
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
