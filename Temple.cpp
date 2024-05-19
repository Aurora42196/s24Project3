//
//  Temple.cpp
//  s24Project3
//
//  Created by Cameron Maiden on 5/19/24.
//

#include "Temple.h"
#include "globals.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Temple::Temple(int nRows, int nCols)
    : m_rows(nRows),m_cols(nCols)
{
    // Checks if the size of the temple floor is valid, if this code runs, something went terribly wrong
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Temple created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
}

Temple::~Temple()
{
    
}
