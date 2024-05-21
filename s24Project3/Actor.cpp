//
//  Actors.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/15/24.
//

#include "Actor.h"
#include "globals.h"

///////////////////////////////////////////////////////////////////////////
// Actor function implementations
///////////////////////////////////////////////////////////////////////////

Actor::Actor(Temple* tp, int r, int c)
: m_temple(tp), m_row(r), m_col(c), m_sleepTimer(0)
{}

void Actor::move(char dir)
{}

///////////////////////////////////////////////////////////////////////////
// Player function implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Temple* tp, int r, int c)
 : Actor(tp, r, c) 
{
    setHealth(INITIAL_PLAYER_HEALTH);
    setArmor(2);
    setStrength(2);
    setDexterity(2);
}

Player::~Player()
{}

void Player::move(char dir)
{
    return;
}

///////////////////////////////////////////////////////////////////////////
// Monster function implementations
///////////////////////////////////////////////////////////////////////////
