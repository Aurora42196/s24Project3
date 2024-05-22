//
//  GameObject.h
//  s24Project3
//
//  Created by Cameron Maiden on 5/22/24.
//

#ifndef GameObject_h
#define GameObject_h

#include <string>

class GameObject
{
public:
    // Constructor/destructor
    GameObject();
    ~GameObject();
    int row() const { return m_row; };
    int col() const { return m_col; };
    
private:
    int m_row;
    int m_col;
    std::string m_name; // Each game object has a unique name
};
#endif /* GameObject_h */
