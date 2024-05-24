//
//  Scroll.hpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#ifndef Scroll_hpp
#define Scroll_hpp

#include "GameObject.h"

class Scroll : public GameObject
{
public:
    Scroll(Temple* tp, int r, int c);
    virtual ~Scroll() {};
    
    // Accessors
    virtual std::string getName() = 0;
    
    // Mutators
    virtual void castEffect() = 0;
private:
    
};

class Teleportation : public Scroll
{
public:
    Teleportation(Temple* tp, int r, int c);
    virtual ~Teleportation() {};
    
    // Accessors
    virtual std::string getName() { return "scroll of teleportation"; };
    
    // Mutators
    virtual void castEffect();
private:
    
};

class ImproveArmor : public Scroll
{
public:
    ImproveArmor(Temple* tp, int r, int c);
    virtual ~ImproveArmor() {};
    
    // Accessors
    virtual std::string getName() { return "scroll of improve armor"; };
    
    // Mutators
    virtual void castEffect();
private:
    
};

class RaiseStrength : public Scroll
{
public:
    RaiseStrength(Temple* tp, int r, int c);
    virtual ~RaiseStrength() {};
    
    // Accessors
    virtual std::string getName() { return "scroll of raise strength"; };
    
    // Mutators
    virtual void castEffect();
private:
    
};

class EnhanceHealth : public Scroll
{
public:
    EnhanceHealth(Temple* tp, int r, int c);
    virtual ~EnhanceHealth() {};
    
    // Accessors
    virtual std::string getName() { return "scroll of enhance health"; };
    
    // Mutators
    virtual void castEffect();
private:
    
};

class EnhanceDexterity : public Scroll
{
public:
    EnhanceDexterity(Temple* tp, int r, int c);
    virtual ~EnhanceDexterity() {};
    
    // Accessors
    virtual std::string getName() { return "scroll of enhance dexterity"; };
    
    // Mutators
    virtual void castEffect();
private:
    
};

#endif /* Scroll_hpp */
