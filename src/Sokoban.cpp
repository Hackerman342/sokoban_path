#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include<climits>

#include "Sokoban.h"
#include "Coordinate.cpp"

#pragma once

// Class file for Sokoban class
// Used to represent each node (grid space)
// in the Sokoban Path activity

// Default constrctor
Sokoban::Sokoban(){}

// Map file constrctor
Sokoban::Sokoban(std::string map_file)
{
    this->read_map(map_file);
}

// Destructor
Sokoban::~Sokoban(){}

void Sokoban::read_map(std::string map_file)
{
    // Print information as problem is solved
    bool debug_flag = false;

    // Initialize variables
	int x = 0, y = 0; // Define coordinate system

	// Read map file to character string
	std::ifstream input(map_file);
    std::string s_map((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());
    if (debug_flag)
    {
        std::cout << "Imported map \n";
        std::cout << s_map;
        std::cout <<"Coordinates defined as \n";
        std::cout <<"(0,0) origin in top left \n";
        std::cout <<"x increases with rows, y with columns \n\n";
    }

    // Step through map to characterize map
    // Initialize all distance values to INT_MAX
    // except for start which gets dist = 0
    for (char c : s_map){

        if (c == ' '){
            this->free_space.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '#'){
            this->walls.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '.'){
            this->goals.push_back(Coordinate(x, y, INT_MAX));
            this->free_space.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '@'){
            this->start = Coordinate(x, y, 0);
            this->free_space.push_back(Coordinate(x, y, 0));}
        else if (c == '+'){
            this->start = Coordinate(x, y, 0);
            this->goals.push_back(Coordinate(x, y, 0));
            this->free_space.push_back(Coordinate(x, y, 0));}
        else if (c == '$'){
            this->boxes.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '*'){
            this->boxes.push_back(Coordinate(x, y, INT_MAX));
            // Goals with boxes cannot be accessed without pushing
            // this->goals.push_back(Coordinate(x, y, INT_MAX));
            }
        else if (c == '\n'){
            x++; y = -1;}
        y++;
    }

    if (debug_flag)
    {
        // Print map details
        bool print_dist0 = false;

        std::cout << "start \n";
        if (print_dist0){
        std::cout << "(" << this->start.x << ", " << this->start.y <<  ", " << this->start.dist << ")\n";}
        else {std::cout << "(" << this->start.x << ", " << this->start.y << ")\n";}
        std::cout << "goals \n";
        this->print_coord_vector(this->goals, print_dist0);
        std::cout << "free space \n";
        this->print_coord_vector(this->free_space, print_dist0);
        std::cout << "walls \n";
        this->print_coord_vector(this->walls, print_dist0);
        std::cout << "boxes \n";
        this->print_coord_vector(this->boxes, print_dist0);
    }

    return;
}

std::string Sokoban::Dijkstras_path_search()
{
    // Print information as problem is solved
    bool debug_flag = false;

    // Check if start is already at goal
    if (this->start.check_for_goal(this->goals))
    {
        if (debug_flag){std::cout << "Started at goal \n";}
        return "";
    }

    // Initialize all free spaces as unchecked nodes
    std::vector < Coordinate > checked;
    std::vector < Coordinate > unchecked = this->free_space;
    Coordinate curr_pos = this->start;
    int curr_ind, min_dist = INT_MAX;

    bool print_dist = true;

    while(unchecked.size()>0){

        // Find lowest distance in unchecked
        for (int i=0; i<unchecked.size(); i++)
        {
            if (unchecked[i].dist <= min_dist)
            {
                min_dist = unchecked[i].dist;
                curr_pos = unchecked[i];
                curr_ind = i;
            }
        }
        if (curr_pos.check_for_goal(this->goals))
        {

            // FIND PATH FROM START TO GOAL
            if (debug_flag)
            {
                std::cout << "Reached Goal! \n";
                std::cout << "(" << curr_pos.x  << ", " << curr_pos.y << ") \n";
                std::cout << "Looking for path (backwards from goal) \n";
            }
            std::string path;
            while (true)
            {
                if (debug_flag){std::cout << "current: (" << curr_pos.x << ", " << curr_pos.y << ") \n";}
                for (Coordinate coord : checked)
                {
                    if (coord.x + 1 == curr_pos.x && coord.y == curr_pos.y)
                    {
                        path.append("D ");
                        curr_pos = coord;
                        break;
                    }
                    if (coord.x - 1 == curr_pos.x && coord.y == curr_pos.y)
                    {
                        path.append("U ");
                        curr_pos = coord;
                        break;
                    }
                    if (coord.x == curr_pos.x && coord.y + 1 == curr_pos.y)
                    {
                        path.append("R ");
                        curr_pos = coord;
                        break;
                    }
                    if (coord.x == curr_pos.x && coord.y - 1 == curr_pos.y)
                    {
                        path.append("L ");
                        curr_pos = coord;
                        break;
                    }

                }
                if (curr_pos.x == start.x && curr_pos.y == this->start.y)
                {
                    if (debug_flag)
                    {
                        std::cout << "final (start): (" << curr_pos.x << ", " << curr_pos.y << ") \n";
                        std::cout << "Found path \n";
                    }
                    path.pop_back();
                    std::reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
        else if (min_dist == INT_MAX)
        {
            if (debug_flag){std::cout << "No Path (without pushing boxes) \n";}
            return "no path";
        }
        // Reset min_dist
        min_dist = INT_MAX;

        if (debug_flag){std::cout << "current: " << curr_pos.x << ", " << curr_pos.y << ", " << curr_pos.dist << "\n";}

        // Check all directions and update distance
        for (int i=0; i<unchecked.size(); i++)
        {
            if (unchecked[i].x == curr_pos.x + 1 && unchecked[i].y == curr_pos.y)
            {
                unchecked[i].dist = std::min(unchecked[i].dist, curr_pos.dist + 1);
            }
            if (unchecked[i].x == curr_pos.x - 1 && unchecked[i].y == curr_pos.y)
            {
                unchecked[i].dist = std::min(unchecked[i].dist, curr_pos.dist + 1);
            }
            if (unchecked[i].x == curr_pos.x && unchecked[i].y == curr_pos.y + 1)
            {
                unchecked[i].dist = std::min(unchecked[i].dist, curr_pos.dist + 1);
            }
            if (unchecked[i].x == curr_pos.x && unchecked[i].y == curr_pos.y - 1)
            {
                unchecked[i].dist = std::min(unchecked[i].dist, curr_pos.dist + 1);
            }
        }

        // Update checked & unchecked vectors
        unchecked.erase(unchecked.begin() + curr_ind);
        checked.push_back(curr_pos);
        if (debug_flag)
        {
            std::cout << "checked \n";
            print_coord_vector(checked, print_dist);
        }

    }

    return "Something went wrong...";
}

void Sokoban::print_coord_vector(std::vector < Coordinate > vec, bool print_dist)
{
    if (print_dist)
    {
        for (int i=0; i<vec.size(); i++)
        {
            std::cout << "(" << vec[i].x << ", " << vec[i].y << ", " << vec[i].dist << ")";
            if ( i < vec.size() - 1){std::cout << ", ";}
            else{std::cout <<"\n";}
        }
    }
    else
    {
        for (int i=0; i<vec.size(); i++)
        {
            std::cout << "(" << vec[i].x << ", " << vec[i].y << ")";
            if ( i < vec.size() - 1){std::cout << ", ";}
            else{std::cout <<"\n";}
        }
    }
    return;
}