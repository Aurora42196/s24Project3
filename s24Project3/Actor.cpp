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
#include "Scroll.h"
#include "Monster.h"
#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Actor function implementations
///////////////////////////////////////////////////////////////////////////

Actor::Actor(Temple* tp, int r, int c, char sym)
: m_temple(tp), m_row(r), m_col(c), m_symbol(sym), m_health(0), m_armor(0), m_strength(0), m_dexterity(0), m_sleepTimer(0)
{}

void Actor::attackActor(char dir)
{
    Actor* attacker = this;
    Actor* defender = nullptr;
    if(getSymbol() == PLAYER_SYMBOL) //if player called the attack function, then the player is the attacker and the monster is the defender. Otherwise, the monster is the attacker and player is the defender
    {
        switch (dir) // This is to determine which monster the player wants to attack based on the direction the Player pressed on the keyboard
        {
            case ARROW_UP:
                defender = getTemple()->isMonsterAt(row()-1, col());
                break;
            case ARROW_DOWN:
                defender = getTemple()->isMonsterAt(row()+1, col());
                break;
            case ARROW_LEFT:
                defender = getTemple()->isMonsterAt(row(), col()-1);
                break;
            case ARROW_RIGHT:
                defender = getTemple()->isMonsterAt(row(), col()+1);
                break;
            default:
                return;
                break;
        }
    }
    else // a monster called the attack function and the player is the one defending the attack
    {
        defender = getTemple()->getPlayer();
    }
    
    Weapon* attWeapon = attacker->getWeapon();
    int attackerPoints = attacker->getDexterity() + attWeapon->getDexterityBonus();
    
    int defenderPoints = defender->getDexterity() + defender->getArmor();
    
    int damagePoints = randInt(0, getStrength() + attWeapon->getWeaponDamage()-1);
    
    string action = getName() + " " + attWeapon->getAction() + defender->getName();
    if(randInt(1, attackerPoints) >= randInt(1, defenderPoints))
    {
        defender->setHealth(defender->getHealth() - damagePoints);
        
        if(defender->getHealth() <= 0)
        {
            if(getSymbol() == PLAYER_SYMBOL) //Only remove from the grid if it's the monster that gets killed, not the player
            {
                getTemple()->removeMonsterFromGrid(defender->row(), defender->col());
            }
            action += " dealing a final blow.";
        }
        else
        {
            if(attWeapon->getName() == "magic fangs of sleep") //If the attacker has the magic fangs of sleep, there is a 1 in 5 chance that the defender will fall asleep
            {
                if(trueWithProbability(0.20))
                {
                    defender->castSleep(randInt(2, 6));
                    action += " and hits, putting " + defender->getName() + " to sleep.";
                }
                else
                {
                    action += " and hits."; //defender took damage but did not fall asleep
                }
            }
            else
            {
                action += " and hits."; //defender took damage from a weapon that is not the magic fangs
            }
        }
    }
    else
    {
        action += " and misses.";
    }
    
    getTemple()->addAction(action);
}


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
                tp->removeObjectFromGrid(i);
                m_nItems++;
                string pickup;
                if(templeObject->getSymbol() == SCROLL_SYMBOL)
                {
                    Scroll* sp = dynamic_cast<Scroll*>(templeObject);
                    sp->setPlayer(this);
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
    else // Iventory has reached capacity
    {
        string action = "Your knapsack is full; you can't pick that up.";
        tp->addAction(action);
        return false;
    }
    return false;
}

void Player::equipWeapon()
{
    clearScreen();
    
    // starts with the character 'a' and increments with each item in the inventory
    cout << "Inventory:" << endl;
    for (int i = 0; i < m_nItems; i++)
    {
        cout << " " << (char)('a' + i) << ". " << m_inventory[i]->getName() << endl;
    }
    
    // char represented as an integer so we can directly access the vector element desired
    int choice = getCharacter();
    int index = choice - 'a';
    string action;
    // If the index is bigger than the amount of items in the vector or the char choice is not a letter (referencing the ASCII table), do nothing
    if(index >= m_nItems || choice < 97 || choice > 122)
        return;
    
    Weapon* wp = dynamic_cast<Weapon*>(m_inventory[index]);
    if (wp != nullptr)
    {
        setWeapon(wp);
        action = "You are wielding " + wp->getName();
        getTemple()->addAction(action);
    }
    else
    {
        action = "You can't wield " + m_inventory[index]->getName();
        getTemple()->addAction(action);
    }
}

void Player::readScroll()
{
    clearScreen();
    
    // starts with the character 'a' and increments with each item in the inventory
    cout << "Inventory:" << endl;
    for (int i = 0; i < m_nItems; i++)
    {
        cout << " " << (char)('a' + i) << ". " << m_inventory[i]->getName() << endl;
    }
    
    // char represented as an integer so we can directly access the vector element desired
    int choice = getCharacter();
    int index = choice - 'a';
    string action;
    // If the index is bigger than the amount of items in the vector or the char choice is not a letter (referencing the ASCII table), do nothing
    if(index >= m_nItems || choice < 97 || choice > 122)
        return;
    
    Scroll* sp = dynamic_cast<Scroll*>(m_inventory[index]);
    if (sp != nullptr)
    {
        
        action = "You read the scroll called " + sp->getName();
        getTemple()->addAction(action);
        sp->castEffect();
        delete m_inventory[index];
        m_inventory.erase(m_inventory.begin() + index);
        m_nItems--;
    }
    else
    {
        action = "You can't read a " + m_inventory[index]->getName();
        getTemple()->addAction(action);
    }
}

void Player::decidedMove(char dir)
{
    /// This is my own version of move based on a combination of decodeDirection and
    /// detemineNewPosition from project 1. The player is only allowed to move in the direction
    /// dir as long as there is no wall or monster at the new position, otherwise the player doesn't
    /// move and the Monsters take their turn. This will also work if the player moves on top of a game
    /// object. The game object will remain in the same place unless it gets picked up
    
    switch (dir) {
        case ARROW_UP:
//            if((getTemple()->grid(row()-1, col())) == WALL_SYMBOL)
//                return;
            if(getTemple()->isMonsterAt(row()-1, col()) != nullptr)
                attackActor(ARROW_UP);
            else
            {
                dir = getTemple()->grid(row()-1,col()); // decode the direction
                if (dir == ' ' || dir == WEAPON_SYMBOL || dir == SCROLL_SYMBOL || dir == IDOL_SYMBOL || dir == STAIRS_SYMBOL) // determine if the new position is a valid place to move
                {
                    getTemple()->addToGrid(row(), col(), ' '); // clear the space the player is moving from
                    setRow(row()-1); // alter the players position
                    getTemple()->addToGrid(row(), col(), getSymbol()); // show the change to player's position in the grid
                }
            }
            break;
            
        case ARROW_DOWN:
            if(getTemple()->isMonsterAt(row()+1, col()) != nullptr)
                attackActor(ARROW_DOWN);
            else
            {
                dir = getTemple()->grid(row()+1,col());
                if(dir == ' '|| dir == WEAPON_SYMBOL || dir == SCROLL_SYMBOL || dir == IDOL_SYMBOL || dir == STAIRS_SYMBOL)
                {
                    getTemple()->addToGrid(row(), col(), ' ');
                    setRow(row()+1);
                    getTemple()->addToGrid(row(), col(), getSymbol());
                }
            }
            break;
            
        case ARROW_LEFT:
            if(getTemple()->isMonsterAt(row(), col()-1) != nullptr)
                attackActor(ARROW_LEFT);
            else
            {
                dir = getTemple()->grid(row(),col()-1);
                if(dir == ' '|| dir == WEAPON_SYMBOL || dir == SCROLL_SYMBOL || dir == IDOL_SYMBOL || dir == STAIRS_SYMBOL)
                {
                    getTemple()->addToGrid(row(), col(), ' ');
                    setCol(col()-1);
                    getTemple()->addToGrid(row(), col(), getSymbol());
                }
            }
            break;
            
        case ARROW_RIGHT:
            if(getTemple()->isMonsterAt(row(), col()+1) != nullptr)
                attackActor(ARROW_RIGHT);
            else
            {
                dir = getTemple()->grid(row(),col()+1);
                if(dir == ' '|| dir == WEAPON_SYMBOL || dir == SCROLL_SYMBOL || dir == IDOL_SYMBOL || dir == STAIRS_SYMBOL)
                {
                    getTemple()->addToGrid(row(), col(), ' ');
                    setCol(col()+1);
                    getTemple()->addToGrid(row(), col(), getSymbol());
                }
            }
            break;
            
        default:
            cerr << "invalid char for player::move()" << endl; // this should never be called, if it does something went terribly wrong
            break;
    }
}

