#include <iostream>
#include <vector>
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

bool Coordinate::check_for_goal(std::vector < Coordinate > goals)
{
    for (int i=0; i<goals.size(); i++)
    {
        if (goals[i].x == this->x && goals[i].y == this->y )
        {
            std::cout << "Reached Goal! \n";
            std::cout << "(" << this->x  << ", " << this->y << ") \n";
            return true;
        }
    }
    return false;
}

