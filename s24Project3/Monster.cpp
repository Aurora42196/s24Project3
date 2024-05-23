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
void Monster::monstersTakeTurn()
{
    
}

void Monster::move()
{
    char dir = '\0';
    int moveDir = randInt(0, 3);
    switch (moveDir) 
    {
        case 0: // MOVE UP
            dir = getTemple()->getGridValue(row()-1,col()); // decode the direction
            if (dir == ' ') // determine if the new position is a valid place to move
            {
                getTemple()->addToGrid(row(), col(), dir); // clear the space the player is moving from
                setRow(row()-1); // alter the players position
                getTemple()->addToGrid(row(), col(), PLAYER_SYMBOL); // show the change to player's position in the grid
            }
            break;
            
        case 1: // MOVE DOWN
            dir = getTemple()->getGridValue(row()+1,col());
            if(dir == ' ')
            {
                getTemple()->addToGrid(row(), col(), dir);
                setRow(row()+1);
                getTemple()->addToGrid(row(), col(), PLAYER_SYMBOL);
            }
            break;
            
        case 2: // MOVE LEFT
            dir = getTemple()->getGridValue(row(),col()-1);
            if(dir == ' ')
            {
                getTemple()->addToGrid(row(), col(), dir);
                setCol(col()-1);
                getTemple()->addToGrid(row(), col(), PLAYER_SYMBOL);
            }
            break;
            
        case 3: // MOVE RIGHT
            dir = getTemple()->getGridValue(row(),col()+1);
            if(dir == ' ')
            {
                getTemple()->addToGrid(row(), col(), dir);
                setCol(col()+1);
                getTemple()->addToGrid(row(), col(), PLAYER_SYMBOL);
            }
            break;
            
        default:
            cerr << "invalid char for monster::move()" << endl; // this should never be called, if it does something went terribly wrong
            break;
    }
}

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
}

Bogeyman::~Bogeyman()
{
    
}
