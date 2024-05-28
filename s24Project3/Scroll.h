//
//  Scroll.hpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#ifndef Scroll_hpp
#define Scroll_hpp

#include "GameObject.h"
#include <string>
class Player;
class Scroll : public GameObject
{
public:
    Scroll(Temple* tp, int r, int c);
    virtual ~Scroll() {};
    
    // Accessors
    Player* getPlayer() { return m_player; };
    virtual std::string getName() = 0;
    virtual std::string actionString() = 0;
    
    // Mutators
    void setPlayer(Player* pp) { m_player = pp; };
    virtual void castEffect() = 0;
    
private:
    Player* m_player;
    
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
/// Scroll of Teleportation
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Teleportation : public Scroll
{
public:
    Teleportation(Temple* tp, int r, int c);
    virtual ~Teleportation() {};
    
    // Accessors
    virtual std::string getName() { return "scroll of teleportation"; };
    virtual std::string actionString() { return "You feel your body wrenched in space and time."; };

    // Mutators
    virtual void castEffect();
    
private:
    // Helper functions
    bool isInBounds(int r ,int c);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Scroll of Improve Armor
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ImproveArmor : public Scroll
{
public:
    ImproveArmor(Temple* tp, int r, int c);
    virtual ~ImproveArmor() {};
    
    // Accessors
    virtual std::string getName() { return "scroll of improve armor"; };
    virtual std::string actionString() { return "Your armor glows blue."; };
    
    // Mutators
    virtual void castEffect();
private:
    
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Scroll of Raise Strength
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RaiseStrength : public Scroll
{
public:
    RaiseStrength(Temple* tp, int r, int c);
    virtual ~RaiseStrength() {};
    
    // Accessors
    virtual std::string getName() { return "scroll of raise strength"; };
    virtual std::string actionString() { return "Your muscles bulge."; };
    
    // Mutators
    virtual void castEffect();
    
private:
    
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Scroll of Enhance Health
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EnhanceHealth : public Scroll
{
public:
    EnhanceHealth(Temple* tp, int r, int c);
    virtual ~EnhanceHealth() {};
    
    // Accessors
    virtual std::string getName() { return "scroll of enhance health"; };
    virtual std::string actionString() { return "You feel your heart beating stronger."; };
    
    // Mutators
    virtual void castEffect();
    
private:
    
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Scroll of Enhance Dexterity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EnhanceDexterity : public Scroll
{
public:
    EnhanceDexterity(Temple* tp, int r, int c);
    virtual ~EnhanceDexterity() {};
    
    // Accessors
    virtual std::string getName() { return "scroll of enhance dexterity"; };
    virtual std::string actionString() { return "You feel like less of a klutz."; };
    
    // Mutators
    virtual void castEffect();
    
private:
    
};

#endif /* Scroll_hpp */
