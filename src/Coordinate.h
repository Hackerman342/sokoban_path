#include <iostream>
#include <vector>
#pragma once

// Header file for Coordinate class
// Used to represent each node (grid space)
// in the Sokoban Path activity

class Coordinate
{
private:

public:

    // Default constrctor
    Coordinate();
    // Useful constructor
    Coordinate(int x, int y, int dist);
    // Destructor
    ~Coordinate();

    int x;
    int y;
    int dist;

    bool check_for_goal(std::vector < Coordinate > goals);
};
