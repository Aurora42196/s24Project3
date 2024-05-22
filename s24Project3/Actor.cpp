//
//  Actors.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/15/24.
//

#include "Actor.h"
#include "Temple.h"
#include "globals.h"
#include <iostream>
using namespace std;

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
    char element;
    
    
    switch (dir) {
        case ARROW_UP:
            element = getTemple()->getGridValue(row()-1,col());
            if (element == ' ') {
                getTemple()->addToGrid(row(), col(), element);
                setRow(row()-1);
                getTemple()->addToGrid(row(), col(), PLAYER_SYMBOL);
            }
            break;
            
        case ARROW_DOWN:
            element = getTemple()->getGridValue(row()+1,col());
            if(element == ' ')
            {
                getTemple()->addToGrid(row(), col(), element);
                setRow(row()+1);
                getTemple()->addToGrid(row(), col(), PLAYER_SYMBOL);
            }
            break;
            
        case ARROW_LEFT:
            element = getTemple()->getGridValue(row(),col()-1);
            if(element == ' ')
            {
                getTemple()->addToGrid(row(), col(), element);
                setCol(col()-1);
                getTemple()->addToGrid(row(), col(), PLAYER_SYMBOL);
            }
            break;
            
        case ARROW_RIGHT:
            element = getTemple()->getGridValue(row(),col()+1);
            if(element == ' ')
            {
                getTemple()->addToGrid(row(), col(), element);
                setCol(col()+1);
                getTemple()->addToGrid(row(), col(), PLAYER_SYMBOL);
            }
            break;
            
        default:
            cerr << "Player couldn't move" << endl;
            break;
    }
}

///////////////////////////////////////////////////////////////////////////
// Monster function implementations
///////////////////////////////////////////////////////////////////////////
