#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include<climits>

#include "Coordinate.cpp"
#include "Sokoban.cpp"


int main( int argc, char* argv[] )
{
    /* Print debug information as problem is solved.
    The functions in Sokoban.cpp all have their own
    debug_flag boolean for individual debugging */
    bool debug_flag = false;

    // Read map_file arg given in command line
    std::string map_file;
    if( argc == 2 ){map_file = argv[1];}
    else {std::cout << "No map file passed in \n"; return 0;}

    // Initialize Sokoban object
    Sokoban sokoban_path;
    // Read & unpack map file
    sokoban_path.read_map(map_file);

    // Find commands for agent to follow
    // returns "no path" if not possible
    // returns "" if agent starts at goal
    std::string path_result;
    path_result = sokoban_path.Dijkstras_path_search();
    std::cout << path_result;

    return 0;
}
