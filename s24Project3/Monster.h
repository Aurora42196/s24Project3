//
//  Monster.h
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#ifndef Monster_h
#define Monster_h

#include "Actor.h"
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
private:
    
    
};
#endif /* Monster_h */
