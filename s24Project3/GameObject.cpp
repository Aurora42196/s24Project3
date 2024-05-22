//
//  GameObject.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#include "GameObject.h"
#include <iostream>

using namespace std;

GameObject::GameObject(Temple* tp, int r, int c, string nm)
 :m_temple(tp), m_row(r), m_col(c), m_name(nm)
{
//    if (m_temple->isInBounds(<#int r#>, <#int c#>)) {
//        <#statements#>
//    }
}

GameObject::~GameObject()
{
    
}

