//
//  Monster.h
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#ifndef Monster_h
#define Monster_h

#include "Actor.h"
#include <string>
#include <queue>
#include <stack>
class Temple;

///////////////////////////////////////////////////////////////////////////
// Monster (Derived from Actor)
///////////////////////////////////////////////////////////////////////////

class Monster: public Actor
{
    /// All Monsters can:
    ///     *Do anything an Actor can do
    ///     *Handle a turn action
    /// All Monsters store:
    ///     *Statistics
    ///     *Drops an item upon death
public:
    // Constructor/destructor
    Monster(Temple* tp, int r, int c, char sym);
    virtual ~Monster();
    
    // Accessors
    virtual std::string getName() const = 0;
    // Mutators
    virtual void move() = 0; // Every monster moves in a unique way
    virtual void decidedMove(char dir);
    virtual void dropItem(Monster* mp, int r, int c);
    
private:
    // All monsters have an item to drop
    // Helper functions
//    bool determineNewPosition(int& r, int& c, int dir) const;
//    bool decodeDirection(char dir);
    
    
};

///////////////////////////////////////////////////////////////////////////
// Types of Monsters (Derived from Monster)
///////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Bogeyman

class Bogeyman : public Monster
{
public:
    Bogeyman(Temple* tp, int r, int c);
    virtual ~Bogeyman();
    
    // Accesors
    virtual std::string getName() const { return "the Bogeyman"; };
    
    // Mutators
    virtual void move();

private:
        
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Snakewoman

class Snakewoman : public Monster
{
public:
    Snakewoman(Temple* tp, int r, int c);
    virtual ~Snakewoman();
    
    // Accessors
    virtual std::string getName() const { return "the Snakewoman"; };
    
    // Mutators
    virtual void move();

private:
    
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Dragon

class Dragon : public Monster
{
public:
    Dragon(Temple* tp, int r, int c);
    virtual ~Dragon();
    
    //Accessors
    virtual std::string getName() const { return "the Dragon"; };

    // Mutator
    virtual void move();
private:
    
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Goblin

class Goblin : public Monster
{
public:
    Goblin(Temple* tp, int r, int c);
    virtual ~Goblin();
    
    //Accessors
    virtual std::string getName() const { return "the Goblin"; };
    
    // Mutators
    virtual void move();

private:
    // Helper functions
    class Coord
    {
    public:
        Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
        int r() const { return m_row; }
        int c() const { return m_col; }
    private:
        int m_row;
        int m_col;
    };
    
    bool pathExists(char grid [][MAXCOLS], int sr, int sc, int er, int ec, int depth, std::stack<char>& wp);
    
};

#endif /* Monster_h */
