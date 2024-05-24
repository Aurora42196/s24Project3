//
//  Scroll.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#include "Scroll.h"

Scroll::Scroll(Temple* tp, int r, int c)
 :GameObject(tp, r, c, SCROLL_SYMBOL)
{
    
}

Teleportation::Teleportation(Temple* tp, int r, int c)
 :Scroll(tp, r, c)
{
    setName(getName());
}

void Teleportation::castEffect()
{
    
}

ImproveArmor::ImproveArmor(Temple* tp, int r, int c)
 :Scroll(tp, r, c)
{
    setName(getName());
}

RaiseStrength::RaiseStrength(Temple* tp, int r, int c)
 :Scroll(tp, r, c)
{
    setName(getName());
}

EnhanceHealth::EnhanceHealth(Temple* tp, int r, int c)
 :Scroll(tp, r, c)
{
    setName(getName());
}

EnhanceDexterity::EnhanceDexterity(Temple* tp, int r, int c)
 :Scroll(tp, r, c)
{
    setName(getName());
}
