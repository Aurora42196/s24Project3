// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.
#include "globals.h"
class Temple;


class Game
{
public:
        // Constructor/destructor
    Game(int goblinSmellDistance);
    ~Game();
    
        // Mutators
    void play();
private:
    Temple* m_temple;
};

#endif // GAME_INCLUDED
