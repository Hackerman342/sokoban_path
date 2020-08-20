#include <iostream>
#include <vector>
#include "Coordinate.cpp"
#pragma once

// Header file for Sokoban class
// Used to represent each node (grid space)
// in the Sokoban Path activity

class Sokoban
{
private:

public:

    // Default constrctor
    Sokoban();
    // Map file constructor
    Sokoban(std::string map_file);
    // Destructor
    ~Sokoban();

    // Coordinate categories
    Coordinate start;
	std::vector < Coordinate > walls;
    std::vector < Coordinate > free_space;
    std::vector < Coordinate > boxes;
    std::vector < Coordinate > goals;

    // Useful Functions
    void read_map(std::string map_file);
    std::string Dijkstras_path_search();
    static void print_coord_vector(std::vector < Coordinate > vec, bool dist_flag);

};
