//
//  Actor.h
//  s24Project3
//
//  Created by Cameron Maiden on 5/15/24.
//

#ifndef Actor_h
#define Actor_h

//#include <string>
#include "utilities.h"
/// Game Plan: Actors.h will contain the class declarations for the Actor base class and its derived classes Player and Monster
/// The implementations of the base class and derived classes will be in the source file Actor.cpp

///////////////////////////////////////////////////////////////////////////
// Actor (Base Class)
///////////////////////////////////////////////////////////////////////////

class Temple; // Every Actor object have to be associated to a temple object

class Actor // Base Class
{
    /// All Actors can:
    ///     *move one space
    ///     *attack a target
    /// All Actors store:
    ///     *their position (row, col)
    ///     *current weapon
    ///     *status information (hit points/health, armor, strength, dexterity)
    ///     *sleep time
public:
    
    // Constructor/destructor
    Actor(Temple* tp, int r, int c);
    virtual ~Actor() {};
    
    // Accessors
        // Inline function implementations
    int row() const { return m_row; };
    int col() const { return m_col; };
    int health() const { return m_health; };
    int armor() const { return m_armor; };
    int strength() const { return m_strength; };
    int dexterity() const { return m_dexterity; };
    int sleepTimer() const { return m_sleepTimer; };
    
    // Mutators
        // Inline function implementations
    void setHealth(int h) { m_health = h; };
    void setArmor(int a) { m_armor = a; };
    void setStrength(int s) { m_strength = s; };
    void setDexterity(int d) { m_dexterity = d; };
    void castSleep(int s) { m_sleepTimer = s; };
        
        // Non-inline declarations
    virtual void move(char dir);
        /// All Actors move differently, so they will all have their unique implementations.
        /// If I am not able to impelemnt all the move functions by the deadline, they will default moving an any random direction
    
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

///////////////////////////////////////////////////////////////////////////
// Player (Derived from Actor)
///////////////////////////////////////////////////////////////////////////

class Player: public Actor
{
public:
    // Constructor/destructor
    Player(Temple* tp, int r, int c);
    virtual ~Player();
    
    // Accessors
    
    // Mutators
    virtual void move(char dir);
    
private:
    // A Player has an inventory of items (array of game objects)
    
};

///////////////////////////////////////////////////////////////////////////
// Monster (Derived from Actor)
///////////////////////////////////////////////////////////////////////////

#endif /* Actor_h */
