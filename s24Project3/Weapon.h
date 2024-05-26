//
//  Weapon.h
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#ifndef Weapon_h
#define Weapon_h

#include "GameObject.h"
#include <string>

///////////////////////////////////////////////////////////////////////////
// Weapn (Derived from GameObject)
///////////////////////////////////////////////////////////////////////////
///
class Weapon : public GameObject
{
public:
    Weapon(Temple* tp, int r, int c);
    Weapon() {}; // For weapons added to the player's inventory
    virtual ~Weapon();
    
    // Accessors
    virtual std::string getAction() = 0;
    virtual std::string getName() = 0;
    int getDexterityBonus() { return m_dexterityBonus; };
    int getWeaponDamage() { return m_weaponDamage; };
    
    // Mutators
    void setDexterityBonus(int db) { m_dexterityBonus = db; };
    void setWeaponDamage(int wd) { m_weaponDamage = wd; };
private:
    std::string m_action;
    int m_dexterityBonus;
    int m_weaponDamage;
};

///////////////////////////////////////////////////////////////////////////
// Types of Weapons (Derived from Weapon)
///////////////////////////////////////////////////////////////////////////
///
class Mace : public Weapon 
{
public:
    Mace(Temple* tp, int r, int c);
//    Mace() {setName(getName()); setDexterityBonus(0); setWeaponDamage(2);};
    virtual ~Mace() {};
    std::string getName() { return "mace"; };
    std::string getAction() { return "swings mace at "; };
private:
};

class ShortSword : public Weapon
{
public:
    ShortSword(Temple* tp, int r, int c);
    ShortSword() {setName(getName()); setDexterityBonus(0); setWeaponDamage(2);};
    virtual ~ShortSword() {};
    std::string getName() { return "short sword"; };
    std::string getAction() { return "slashes short sword at "; };
private:
};

class LongSword : public Weapon
{
public:
    LongSword(Temple* tp, int r, int c);
//    LongSword() {setName(getName()); setDexterityBonus(2); setWeaponDamage(4);};
    virtual ~LongSword() {};
    std::string getName() { return "long sword"; };
    std::string getAction() { return "swings long sword at "; };
private:
};

class MagicAxe : public Weapon
{
public:
    MagicAxe(Temple* tp, int r, int c);
//    MagicAxe() {setName(getName()); setDexterityBonus(5); setWeaponDamage(5);};
    virtual ~MagicAxe() {};
    std::string getName() { return "magic axe"; };
    std::string getAction() { return "chops magic axe at "; };
private:
};

class MagicFangs : public Weapon
{
public:
    MagicFangs(Temple* tp, int r, int c);
//    MagicFangs() {setName(getName()); setDexterityBonus(3); setWeaponDamage(2);};
    virtual ~MagicFangs() {};
    std::string getName() { return "magic fangs"; };
    std::string getAction() { return "strikes magic fangs at "; };
private:
};
#endif /* Weapon_h */
