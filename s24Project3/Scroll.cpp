//
//  Scroll.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#include "Scroll.h"
#include "Actor.h"
#include <string>
using namespace std;

Scroll::Scroll(Temple* tp, int r, int c)
 :GameObject(tp, r, c, SCROLL_SYMBOL), m_player(nullptr)
{
    
}

bool Scroll::isInBounds(int r, int c)
{
    return ((m_player->getTemple()->grid(r, c)) == ' ');
}

Teleportation::Teleportation(Temple* tp, int r, int c)
 :Scroll(tp, r, c)
{
    setName(getName());
}

void Teleportation::castEffect()
{
    Player* pp = getPlayer();
    if(pp != nullptr)
    {
        int rPlayer = randInt(MAXROWS);
        int cPlayer = randInt(MAXCOLS);
        while ( !(isInBounds(rPlayer, cPlayer)) )
        {
            rPlayer = randInt(MAXROWS);
            cPlayer = randInt(MAXCOLS);
        }
        pp->getTemple()->grid(pp->row(), pp->col()) = ' ';
        pp->setRow(rPlayer);
        pp->setCol(cPlayer);
        pp->getTemple()->addToGrid(rPlayer, cPlayer, pp->getSymbol());
        pp->getTemple()->addAction(actionString());
    }
}

ImproveArmor::ImproveArmor(Temple* tp, int r, int c)
 :Scroll(tp, r, c)
{
    setName(getName());
}

void ImproveArmor::castEffect()
{
    Player* pp = getPlayer();
    if(pp != nullptr)
    {
        pp->setArmor(pp->getArmor() + randInt(1, 3));
        pp->getTemple()->addAction(actionString());
    }
}

RaiseStrength::RaiseStrength(Temple* tp, int r, int c)
 :Scroll(tp, r, c)
{
    setName(getName());
}

void RaiseStrength::castEffect()
{
    Player* pp = getPlayer();
    if(pp != nullptr)
    {
        pp->setStrength(pp->getStrength() + randInt(1, 3));
        pp->getTemple()->addAction(actionString());
    }
}

EnhanceHealth::EnhanceHealth(Temple* tp, int r, int c)
 :Scroll(tp, r, c)
{
    setName(getName());
}

void EnhanceHealth::castEffect()
{
    Player* pp = getPlayer();
    if(pp != nullptr)
    {
        pp->setMaxHealth(pp->getMaxHealth() + randInt(3, 8));
        pp->getTemple()->addAction(actionString());
    }
}

EnhanceDexterity::EnhanceDexterity(Temple* tp, int r, int c)
 :Scroll(tp, r, c)
{
    setName(getName());
}

void EnhanceDexterity::castEffect()
{
    Player* pp = getPlayer();
    if(pp != nullptr)
    {
        pp->setDexterity(pp->getDexterity() + 1);
        pp->getTemple()->addAction(actionString());
    }
}
