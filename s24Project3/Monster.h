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
    virtual std::string getName() = 0;
    
    // Mutators
    virtual void move();
    virtual void dropItem();
    
private:
    // All monsters have an item to drop
    // Helper functions
    bool determineNewPosition(int& r, int& c, int dir) const;
    bool decodeDirection(char dir); // Default Monster movement will move in any random direction
};

///////////////////////////////////////////////////////////////////////////
// Types of Monsters (Derived from Monster)
///////////////////////////////////////////////////////////////////////////
///
class Bogeyman : public Monster
{
public:
    Bogeyman(Temple* tp, int r, int c);
    virtual ~Bogeyman();
    
    virtual std::string getName() { return "bogeyman"; };
    
    // Mutator
//    virtual void move();

private:
    
};

class Snakewoman : public Monster
{
public:
    Snakewoman(Temple* tp, int r, int c);
    virtual ~Snakewoman();
    
    virtual std::string getName() { return "snakewoman"; };
    
    // Mutator
//    virtual void move();

private:
    
};

class Dragon : public Monster
{
public:
    Dragon(Temple* tp, int r, int c);
    virtual ~Dragon();
    
    virtual std::string getName() { return "dragon"; };

    // Mutator
    virtual void move();
private:
    
};

class Goblin : public Monster
{
public:
    Goblin(Temple* tp, int r, int c);
    virtual ~Goblin();
    
    virtual std::string getName() { return "goblin"; };
    
    // Mutator
//    virtual void move();

private:
    
};
#endif /* Monster_h */
