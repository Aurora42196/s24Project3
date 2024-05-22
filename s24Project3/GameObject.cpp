//
//  GameObject.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#include "GameObject.h"
#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////
///
GameObject::GameObject(Temple* tp, int r, int c, string nm)
 :m_temple(tp), m_row(r), m_col(c), m_name(nm)
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
// Accessor Function Implementations
///////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////
// Mutator Function Implementations
///////////////////////////////////////////////////////////////////////////
