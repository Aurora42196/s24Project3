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
    GameObject(Temple* tp, int r, int c, char sym);
    virtual ~GameObject();
    
    // Accessors
        // Inline function implementations
    int row() const { return m_row; };
    int col() const { return m_col; };
    char getSymbol() const { return m_symbol; };
    std::string getName() { return m_name; };
    
    // Mutators
    void setName(std::string nm) { m_name = nm; };
    
private:
    // Data members
    Temple* m_temple;
    int m_row;
    int m_col;
    char m_symbol;
    std::string m_name; // Each game object has a unique name
};

class GoldenIdol : public GameObject
{
public:
    GoldenIdol(Temple* tp, int r, int c);
    virtual ~GoldenIdol() {};
private:
    
};

class Staircase : public GameObject
{
public:
    Staircase(Temple* tp, int r, int c);
    virtual ~Staircase() {};
private:
    
};

#endif /* GameObject_h */
