// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.
#include "globals.h"
class Temple;
class Player;

class Game
{
public:
        // Constructor/destructor
    Game(int goblinSmellDistance);
    ~Game();
    
        // Mutators
    bool addPlayer(int r, int c);
    void goToNextLevel();
    void play();
    
private:
    // Data members
    Temple* m_temple;
    Player* m_player;
    int m_level; // keeps track of what level the player is currently on
    
    // Helper functions
    bool isInBounds(int r ,int c) const;
};

#endif // GAME_INCLUDED
