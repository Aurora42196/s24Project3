//
//  Monster.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#include <iostream>
#include "Temple.h"
#include "Monster.h"
#include "globals.h"
#include "Weapon.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
// Monster function implementations
///////////////////////////////////////////////////////////////////////////
///
// Constructor
Monster::Monster(Temple *tp, int r, int c, char sym)
 :Actor(tp, r, c, sym)
{
    
}

// Destructor
Monster::~Monster()
{
    
}


///////////////////////////////////////////////////////////////////////////
// Mutator function implementations
///////////////////////////////////////////////////////////////////////////
///

void Monster::move()
{
    char dir = '\0';
    int moveDir = randInt(4);
    
    switch (moveDir)
    {
        case 0: // MOVE UP
            dir = getTemple()->grid(row()-1,col()); // decode the direction
            if (dir == ' '|| dir == WEAPON_SYMBOL || dir == SCROLL_SYMBOL || dir == IDOL_SYMBOL || dir == STAIRS_SYMBOL) // determine if the new position is a valid place to move
            {
                getTemple()->addToGrid(row(), col(), ' '); // clear the space the player is moving from
                setRow(row()-1); // alter the players position
                getTemple()->addToGrid(row(), col(), getSymbol()); // show the change to player's position in the grid
            }
            break;
            
        case 1: // MOVE DOWN
            dir = getTemple()->grid(row()+1,col());
            if(dir == ' '|| dir == WEAPON_SYMBOL || dir == SCROLL_SYMBOL || dir == IDOL_SYMBOL || dir == STAIRS_SYMBOL)
            {
                getTemple()->addToGrid(row(), col(), ' ');
                setRow(row()+1);
                getTemple()->addToGrid(row(), col(), getSymbol());
            }
            break;
            
        case 2: // MOVE LEFT
            dir = getTemple()->grid(row(),col()-1);
            if(dir == ' '|| dir == WEAPON_SYMBOL || dir == SCROLL_SYMBOL || dir == IDOL_SYMBOL || dir == STAIRS_SYMBOL)
            {
                getTemple()->addToGrid(row(), col(), ' ');
                setCol(col()-1);
                getTemple()->addToGrid(row(), col(), getSymbol());
            }
            break;
            
        case 3: // MOVE RIGHT
            dir = getTemple()->grid(row(),col()+1);
            if(dir == ' '|| dir == WEAPON_SYMBOL || dir == SCROLL_SYMBOL || dir == IDOL_SYMBOL || dir == STAIRS_SYMBOL)
            {
                getTemple()->addToGrid(row(), col(), ' ');
                setCol(col()+1);
                getTemple()->addToGrid(row(), col(), getSymbol());
            }
            break;
            
        default:
            cerr << "invalid char for monster::move()" << endl; // this should never be called, if it does something went terribly wrong
            break;
    }
}

//void Monster::attackPlayer(/*Monster* attacker*/)
//{
//    Weapon* weapon = /*attacker->*/getWeapon();
//    Player* pp = getTemple()->getPlayer();
//    int attackerPoints = /*attacker->*/getDexterity() + weapon->getDexterityBonus();
//    
//    int defenderPoints = pp->getDexterity() + weapon->getDexterityBonus();
//    
//    int damagePoints = randInt(0, getStrength() + weapon->getWeaponDamage()-1);
//    
//    string action = getName() + " " + weapon->getAction() + pp->getName();
//    if(randInt(1, attackerPoints) >= randInt(1, defenderPoints))
//    {
//        pp->setHealth(pp->getHealth() - damagePoints);
//        if(pp->getHealth() <= 0)
//            action += ", dealing a final blow.";
//        else
//            action += " and hits.";
//    }
//    else
//    {
//        action += " and misses.";
//    }
//    
//    getTemple()->addAction(action);
//}

void Monster::dropItem()
{
    
}

///////////////////////////////////////////////////////////////////////////
// Helper function implementations
///////////////////////////////////////////////////////////////////////////

bool Monster::determineNewPosition(int& r, int& c, int dir) const
{
    //    switch (dir)
    //    {
    //      case UP:     if (r <= 1)      return false; else r--; break;
    //      case DOWN:   if (r >= rows()) return false; else r++; break;
    //      case LEFT:   if (c <= 1)      return false; else c--; break;
    //      case RIGHT:  if (c >= cols()) return false; else c++; break;
    //      default:     return false;
    //    }
    return true;
}

bool Monster::decodeDirection(char dir)
{
    return false;
}


///////////////////////////////////////////////////////////////////////////
// Bogeyman function implementations
///////////////////////////////////////////////////////////////////////////
///
// Constructor
Bogeyman::Bogeyman(Temple* tp, int r, int c)
 :Monster(tp, r, c, BOGEYMAN_SYMBOL)
{
    setHealth(randInt(5, 10));
    setStrength(randInt(2, 3));
    setDexterity(randInt(2, 3));
    setArmor(2);
    
    Weapon* starterWeapon;
    starterWeapon = new ShortSword();
    setWeapon(starterWeapon);
}

Bogeyman::~Bogeyman()
{
    
}

//void Bogeyman::move()
//{
//    
//}

///////////////////////////////////////////////////////////////////////////
// Snakewoman function implementations
///////////////////////////////////////////////////////////////////////////
///
// Constructor
Snakewoman::Snakewoman(Temple* tp, int r, int c)
 :Monster(tp, r, c, SNAKEWOMAN_SYMBOL)
{
    setHealth(randInt(3, 6));
    setStrength(2);
    setDexterity(3);
    setArmor(3);
    
    Weapon* starterWeapon;
    starterWeapon = new MagicFangs();
    setWeapon(starterWeapon);
}

Snakewoman::~Snakewoman()
{
    
}

//void Snakewoman::move()
//{
//    
//}

///////////////////////////////////////////////////////////////////////////
// Dragon function implementations
///////////////////////////////////////////////////////////////////////////
///
// Constructor
Dragon::Dragon(Temple* tp, int r, int c)
 :Monster(tp, r, c, DRAGON_SYMBOL)
{
    setHealth(randInt(20, 25));
    setStrength(4);
    setDexterity(4);
    setArmor(4);
    
    Weapon* starterWeapon;
    starterWeapon = new LongSword();
    setWeapon(starterWeapon);
}

Dragon::~Dragon()
{
    
}

void Dragon::move(char dir)
{
    return; // Dragons do not move, since they want to protect their treasure
}

///////////////////////////////////////////////////////////////////////////
// Goblin function implementations
///////////////////////////////////////////////////////////////////////////
///
// Constructor
Goblin::Goblin(Temple* tp, int r, int c)
 :Monster(tp, r, c, GOBLIN_SYMBOL)
{
    setHealth(randInt(15, 20));
    setStrength(3);
    setDexterity(1);
    setArmor(1);
    
    Weapon* starterWeapon;
    starterWeapon = new ShortSword();
    setWeapon(starterWeapon);
}

//void Goblin::move()
//{
//    return;
//}

Goblin::~Goblin()
{
    
}
