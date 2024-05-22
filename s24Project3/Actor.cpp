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
    /// This is my own version of move based on a combination of decodeDirection and
    /// detemineNewPosition from project 1. The player is only allowed to move in the direction
    /// dir as long as there is no wall or monster at the new position, otherwise the player doesn't
    /// move and the Monsters take their turn. This will also work if the player moves on top of a game
    /// object. The game object will remain in the same place unless it gets picked up (TEST IF THIS WORKS!!)
    switch (dir) {
        case ARROW_UP:
            dir = getTemple()->getGridValue(row()-1,col()); // decode the direction
            if (dir == ' ') // determine if the new position is a valid place to move
            {
                getTemple()->addToGrid(row(), col(), dir); // clear the space the player is moving from
                setRow(row()-1); // alter the players position
                getTemple()->addToGrid(row(), col(), PLAYER_SYMBOL); // show the change to player's position in the grid
            }
            break;
            
        case ARROW_DOWN:
            dir = getTemple()->getGridValue(row()+1,col());
            if(dir == ' ')
            {
                getTemple()->addToGrid(row(), col(), dir);
                setRow(row()+1);
                getTemple()->addToGrid(row(), col(), PLAYER_SYMBOL);
            }
            break;
            
        case ARROW_LEFT:
            dir = getTemple()->getGridValue(row(),col()-1);
            if(dir == ' ')
            {
                getTemple()->addToGrid(row(), col(), dir);
                setCol(col()-1);
                getTemple()->addToGrid(row(), col(), PLAYER_SYMBOL);
            }
            break;
            
        case ARROW_RIGHT:
            dir = getTemple()->getGridValue(row(),col()+1);
            if(dir == ' ')
            {
                getTemple()->addToGrid(row(), col(), dir);
                setCol(col()+1);
                getTemple()->addToGrid(row(), col(), PLAYER_SYMBOL);
            }
            break;
            
        default:
            cerr << "invalid char for player::move()" << endl; // this should never be called, if it does something went terribly wrong
            break;
    }
}

///////////////////////////////////////////////////////////////////////////
// Monster function implementations
///////////////////////////////////////////////////////////////////////////
