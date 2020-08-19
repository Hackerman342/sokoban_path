#include <iostream>
#include "Coordinate.h"
#pragma once

// Class file for Coordinate class
// Used to represent each node (grid space)
// in the Sokoban Path activity

// Default constrctor
Coordinate::Coordinate(){}

// Useful constructor
Coordinate::Coordinate(int x, int y, int dist)
{
    this->x = x;
    this->y = y;
    this->dist = dist;
}

// Destructor
Coordinate::~Coordinate(){}
