//
//  Actors.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/15/24.
//

#include "Actor.h"
#include "Temple.h"
#include "globals.h"
#include "Weapon.h"
#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Actor function implementations
///////////////////////////////////////////////////////////////////////////

Actor::Actor(Temple* tp, int r, int c, char sym)
: m_temple(tp), m_row(r), m_col(c), m_symbol(sym), m_health(0), m_armor(0), m_strength(0), m_dexterity(0), m_sleepTimer(0)
{}

void Actor::move(char dir)
{}


///////////////////////////////////////////////////////////////////////////
// Player function implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Temple* tp, int r, int c)
 : Actor(tp, r, c, PLAYER_SYMBOL), m_nItems(0)
{
    setHealth(INITIAL_PLAYER_HEALTH);
    setArmor(2);
    setStrength(2);
    setDexterity(2);
    
    Weapon* starterWeapon;
    starterWeapon = new ShortSword();
    setWeapon(starterWeapon);
    m_inventory.push_back(starterWeapon);
    m_nItems++;
}

Player::~Player()
{
    for (int i = 0; i < m_nItems; i++)
    {
        delete m_inventory[i];
    }
}

///////////////////////////////////////////////////////////////////////////
// Accessor function implementations
///////////////////////////////////////////////////////////////////////////
///
bool Player::hasGoldenIdol()
{
    for (int i = 0; i < m_nItems; i++)
    {
        if (m_inventory[i]->getSymbol() == IDOL_SYMBOL)
            return true;
    }
    return false;
}

void Player::showInventory() const
{
    clearScreen();
// starts with the character 'a' and increments with each item in the inventory
    cout << "Inventory:" << endl;
    for (int i = 0; i < m_nItems; i++)
    {
        cout << " " << (char)('a' + i) << ". " << m_inventory[i]->getName() << endl;
    }
    getCharacter();
}

///////////////////////////////////////////////////////////////////////////
// Mutator function implementations
///////////////////////////////////////////////////////////////////////////
///
bool Player::pickUpObject()
{
    int rPlayer = row();
    int cPlayer = col();
    Temple* tp = getTemple();
    if(m_nItems < INVENTORY_CAPACITY)
    {
        for (int i = 0; i < tp->getNumGameObjects(); i++)
        {
            GameObject* templeObject = tp->getGameObjectAt(i);
            if(templeObject->getSymbol() == STAIRS_SYMBOL) // you can't pick up the staircase
                continue;
            if(templeObject->row() == rPlayer && templeObject->col() == cPlayer)
            {
                templeObject->setRow(-1);
                templeObject->setCol(-1);
                m_inventory.push_back(templeObject);
                tp->removeFromGrid(i);
                m_nItems++;
                string pickup;
                if(templeObject->getSymbol() == SCROLL_SYMBOL)
                {
                    pickup = "You pick up a scroll called " + (templeObject->getName());
                }
                else
                {
                    pickup = "You pick up " + (templeObject->getName());
                }
                tp->addAction(pickup);
                
                return true;
            }
        }
    }
    else
        return false;
    return false;
}

void Player::move(char dir)
{
    /// This is my own version of move based on a combination of decodeDirection and
    /// detemineNewPosition from project 1. The player is only allowed to move in the direction
    /// dir as long as there is no wall or monster at the new position, otherwise the player doesn't
    /// move and the Monsters take their turn. This will also work if the player moves on top of a game
    /// object. The game object will remain in the same place unless it gets picked up (TEST IF THIS WORKS!!)
    switch (dir) {
        case ARROW_UP:
            if((getTemple()->grid(row()-1, col())) == WALL_SYMBOL)
                return;
            dir = getTemple()->grid(row()-1,col()); // decode the direction
            if (dir == ' ' || dir == WEAPON_SYMBOL || dir == SCROLL_SYMBOL || dir == IDOL_SYMBOL || dir == STAIRS_SYMBOL) // determine if the new position is a valid place to move
            {
                getTemple()->addToGrid(row(), col(), ' '); // clear the space the player is moving from
                setRow(row()-1); // alter the players position
                getTemple()->addToGrid(row(), col(), getSymbol()); // show the change to player's position in the grid
            }
            break;
            
        case ARROW_DOWN:
            dir = getTemple()->grid(row()+1,col());
            if(dir == ' '|| dir == WEAPON_SYMBOL || dir == SCROLL_SYMBOL || dir == IDOL_SYMBOL || dir == STAIRS_SYMBOL)
            {
                getTemple()->addToGrid(row(), col(), ' ');
                setRow(row()+1);
                getTemple()->addToGrid(row(), col(), getSymbol());
            }
            break;
            
        case ARROW_LEFT:
            dir = getTemple()->grid(row(),col()-1);
            if(dir == ' '|| dir == WEAPON_SYMBOL || dir == SCROLL_SYMBOL || dir == IDOL_SYMBOL || dir == STAIRS_SYMBOL)
            {
                getTemple()->addToGrid(row(), col(), ' ');
                setCol(col()-1);
                getTemple()->addToGrid(row(), col(), getSymbol());
            }
            break;
            
        case ARROW_RIGHT:
            dir = getTemple()->grid(row(),col()+1);
            if(dir == ' '|| dir == WEAPON_SYMBOL || dir == SCROLL_SYMBOL || dir == IDOL_SYMBOL || dir == STAIRS_SYMBOL)
            {
                getTemple()->addToGrid(row(), col(), ' ');
                setCol(col()+1);
                getTemple()->addToGrid(row(), col(), getSymbol());
            }
            break;
            
        default:
            cerr << "invalid char for player::move()" << endl; // this should never be called, if it does something went terribly wrong
            break;
    }
}

