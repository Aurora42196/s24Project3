//
//  Weapon.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#include "Weapon.h"
#include <string>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Weapon function implementations
///////////////////////////////////////////////////////////////////////////
///
Weapon::Weapon(Temple* tp, int r, int c, std::string nm)
 : GameObject(tp,r,c,nm), m_action(nullptr), m_dexterityBonus(0), m_weaponDamage(0)
{
    
}

Weapon::~Weapon()
{
    
}

Mace::Mace(Temple* tp, int r, int c)
 :Weapon(tp,r,c, getName())
{
    setDexterityBonus(0);
    setWeaponDamage(2);
}

ShortSword::ShortSword(Temple* tp, int r, int c)
 :Weapon(tp,r,c, getName())
{
    setDexterityBonus(0);
    setWeaponDamage(2);
}

LongSword::LongSword(Temple* tp, int r, int c)
 :Weapon(tp,r,c, getName())
{
    setDexterityBonus(2);
    setWeaponDamage(4);
}

MagicAxe::MagicAxe(Temple* tp, int r, int c)
 :Weapon(tp,r,c, getName())
{
    setDexterityBonus(5);
    setWeaponDamage(5);
}

MagicFangs::MagicFangs(Temple* tp, int r, int c)
 :Weapon(tp,r,c, getName())
{
    setDexterityBonus(3);
    setWeaponDamage(2);
}




