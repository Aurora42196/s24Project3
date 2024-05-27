//
//  Actor.h
//  s24Project3
//
//  Created by Cameron Maiden on 5/15/24.
//

#ifndef Actor_h
#define Actor_h

#include "utilities.h"
#include <vector>
#include "GameObject.h"
/// Game Plan: Actors.h will contain the class declarations for the Actor base class and its derived class Player
/// The Monster derived class will be in its own file since there are a wide variance of classes derived from Monster
/// The implementations of the Actor base class and Player derived class will be in the source file Actor.cpp

///////////////////////////////////////////////////////////////////////////
// Actor (Base Class)
///////////////////////////////////////////////////////////////////////////

class Temple; // Every Actor object have to be associated to a temple object
class Weapon; // Every actor has a reference to a weapon

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
    Actor(Temple* tp, int r, int c, char sym);
    virtual ~Actor() {};
    
    // Accessors
        // Inline function implementations (getter functions)
    int row() const { return m_row; };
    int col() const { return m_col; };
    int getHealth() const { return m_health; };
    int getArmor() const { return m_armor; };
    int getStrength() const { return m_strength; };
    int getDexterity() const { return m_dexterity; };
    int getSleepTimer() const { return m_sleepTimer; };
    char getSymbol() const { return m_symbol; };
    Temple* getTemple() const { return m_temple; };
    Weapon* getWeapon() const { return m_weapon; };
    virtual std::string getName() const = 0;
    
    // Mutators
        // Inline function implementations
    void setRow(int r) { m_row = r; };
    void setCol(int c) { m_col = c; };
    void setHealth(int h) { m_health = h; };
    void setArmor(int a) { m_armor = a; };
    void setStrength(int s) { m_strength = s; };
    void setDexterity(int d) { m_dexterity = d; };
    void castSleep(int s) { m_sleepTimer = s; };
    void setTemple(Temple* tp) { m_temple = tp; };
    void setWeapon(Weapon* wp) { m_weapon = wp; };
        
        // Non-inline declarations
    virtual void move(char dir)/* = 0*/; // move for the player
    void attackActor(char dir);

        /// All Actors move differently, so they will all have their unique implementations.
        /// If I am not able to impelemnt all the move functions by the deadline, they will default moving an any random direction
    
private:
    Temple* m_temple;
    // Add later: weapon will be a pointer to a game object
    int m_row;
    int m_col;
    char m_symbol;
    int m_health;
    int m_armor;
    int m_strength;
    int m_dexterity;
    int m_sleepTimer;
    Weapon* m_weapon;
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
    bool hasGoldenIdol();
    int getInventorySize() { return m_nItems; };
    void showInventory() const;
    virtual std::string getName() const { return "Player"; };
    
    
    // Mutators
    bool pickUpObject();
    virtual void move(char dir);
    
//    virtual char getSymbol() const { return PLAYER_SYMBOL; };
    
private:
    // A Player has an inventory of items (array of game objects)
    int m_nItems; // keeps track of how many items are in the inventory
    std::vector<GameObject*> m_inventory;
    
};

#endif /* Actor_h */
