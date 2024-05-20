//
//  Actor.h
//  s24Project3
//
//  Created by Cameron Maiden on 5/15/24.
//

#ifndef Actor_h
#define Actor_h

#include "utilities.h"
/// Game Plan: Actors.h will contain the class declarations for the Actor base class and its derived classes Player and Monster
/// The implementations of the base class and derived classes will be in the source file Actor.cpp
class Temple; // Every Actor object have to be associated to a temple

class Actor // Base Class
{
    /// All Actors can:
    ///     *move one space
    ///     *attack a target
    /// All Actors store:
    ///     *their position
    ///     *current weapon
    ///     *status information (hit points, armor, strength, dexterity)
    ///     *sleep time
public:
    
    // Constructor/destructor
    Actor();
    virtual ~Actor();
    
    // Accessors
    int row() const { return m_row; };
    int col() const { return m_col; };
    int health() const { return m_health; };
    int armor() const { return m_armor; };
    int strength() const { return m_strength; };
    int dexterity() const { return m_dexterity; };
    int sleepTimer() const { return m_sleepTimer; };
    // Mutators
    
private:
    Temple* m_temple;
    // Add later: weapon will be a pointer to a game object
    int m_row;
    int m_col;
    int m_health;
    int m_armor;
    int m_strength;
    int m_dexterity;
    int m_sleepTimer;
};

class Player: public Actor
{
public:
    // Constructor/destructor
    Player(Temple* tp, int r, int c);
    virtual ~Player();
    
    // Accessors
    
    // Mutators
    
private:
    // Every player has an inventory of items (array of game objects)
    
};

#endif /* Actor_h */
