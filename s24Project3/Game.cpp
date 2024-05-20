// Game.cpp

#include "Game.h"
#include "utilities.h"
#include "Temple.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
    // create the Temple of Doom
    m_temple = new Temple(MAXROWS,MAXCOLS);
    
    // Add a player
    int rPlayer = randInt(1, MAXROWS);
    int cPlayer = randInt(1, MAXCOLS);
    
    while (!(m_temple->addPlayer(rPlayer, cPlayer)))
    {
        cerr << "coordinate out of bounds" << endl;
        rPlayer = randInt(1, MAXROWS);
        cPlayer = randInt(1, MAXCOLS);
    }
}

Game::~Game()
{
    delete m_temple;
}

void Game::play()
{
    //    cout << "The game hasn't been implemented yet." << endl;
    
    m_temple->display();
    Actor* p = m_temple->player();
    if (p == nullptr)
        return;
    cout << "Press q to exit game." << endl;
    while (getCharacter() != 'q')
        ;
}

// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons,
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.
