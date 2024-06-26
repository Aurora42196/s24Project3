//
//  GameObject.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#include "GameObject.h"
#include "globals.h"
#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////
///
GameObject::GameObject(Temple* tp, int r, int c, char sym)
 :m_temple(tp), m_row(r), m_col(c), m_symbol(sym)
{
    
}

///////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////
///
GameObject::~GameObject()
{
    
}

///////////////////////////////////////////////////////////////////////////
// Golden Idol Function Implementations
///////////////////////////////////////////////////////////////////////////

GoldenIdol::GoldenIdol(Temple* tp, int r, int c)
 :GameObject(tp, r, c, IDOL_SYMBOL)
{
    setName("golden idol");
}

///////////////////////////////////////////////////////////////////////////
// Staircase Function Implementations
///////////////////////////////////////////////////////////////////////////

Staircase::Staircase(Temple* tp, int r, int c)
 :GameObject(tp, r, c, STAIRS_SYMBOL)
{
    
}
