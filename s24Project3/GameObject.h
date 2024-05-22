//
//  GameObject.h
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#ifndef GameObject_h
#define GameObject_h

#include "Temple.h"
#include <string>


class GameObject
{
public:
    // Constructor/destructor
    GameObject(Temple* tp, int r, int c, std::string nm);
    ~GameObject();
    
    // Accessors
        // Inline function implementations
    int row() const { return m_row; };
    int col() const { return m_col; };
    
private:
    // Data members
    int m_row;
    int m_col;
    std::string m_name; // Each game object has a unique name
    Temple* m_temple;
};
#endif /* GameObject_h */
