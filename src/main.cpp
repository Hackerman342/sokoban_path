#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include<climits>

#include "sokoban_util.cpp"
#include "Coordinate.cpp"

int main()
{
    // Initialize variables
	int x = 0, y = 0; // Define coordinate system
    Coordinate start;
	std::vector < Coordinate > walls, free_space, boxes, goals;

	// Read map file to character string
	std::ifstream input("input_samples/00_sample.in");
    std::string s_map((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());
    std::cout << "Imported map \n";
    std::cout << s_map;
    std::cout <<"Coordinates defined as \n";
    std::cout <<"(0,0) origin in top left \n";
    std::cout <<"x increases with rows, y with columns \n\n";

    // Step through map to characterize map
    // Initialize all distance values to INT_MAX
    // except for start which gets dist = 0

    for (char c : s_map){

        if (c == ' '){
            free_space.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '#'){
            walls.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '.'){
            goals.push_back(Coordinate(x, y, INT_MAX));
            free_space.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '@'){
            start = Coordinate(x, y, 0);
            free_space.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '+'){
            start = Coordinate(x, y, 0);
            goals.push_back(Coordinate(x, y, INT_MAX));
            free_space.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '$'){
            boxes.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '*'){
            boxes.push_back(Coordinate(x, y, INT_MAX));
            goals.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '\n'){
            x++; y = -1;}
        y++;
    }

    // Print map details
    bool print_dist = false;

    std::cout << "start \n";
    if (print_dist){
    std::cout << "(" << start.x << ", " << start.y <<  ", " << start.dist << ")\n";}
    else {std::cout << "(" << start.x << ", " << start.y << ")\n";}
    std::cout << "goals \n";
    print_coord_vector(goals, print_dist);
    std::cout << "free space \n";
    print_coord_vector(free_space, print_dist);
    std::cout << "walls \n";
    print_coord_vector(walls, print_dist);
    std::cout << "boxes \n";
    print_coord_vector(boxes, print_dist);


    // Dijkstra's Algorithm to find goal without moving boxes

    // Check if start is already at goal
    if (start.check_for_goal(goals))
    {
        std::cout << "Started at goal \n";
        return 0;
    }

    // Initialize all free spaces as unchecked nodes
    std::vector < Coordinate > checked;
    std::vector < Coordinate > unchecked = free_space;
    Coordinate curr_pos = start;
    int curr_ind, min_dist = INT_MAX;
    bool reached_goal = false;

    print_dist = true;
    std::cout << "unchecked \n";
    print_coord_vector(unchecked, print_dist);
    std::cout << "checked \n";
    print_coord_vector(checked, print_dist);

    // Find start in unchecked
    for (int i=0; i<unchecked.size(); i++)
    {
        if (unchecked[i].x == start.x && unchecked[i].y == start.y)
        {
            unchecked[i].dist = start.dist;
            curr_ind = i;
            break;
        }
    }

    std::cout << "unchecked \n";
    print_coord_vector(unchecked, print_dist);
    std::cout << "checked \n";
    print_coord_vector(checked, print_dist);
    std::cout << "Current index: " << curr_ind << "\n";

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
        if (curr_pos.check_for_goal(goals))
        {

            /*  FIND PATH FROM START TO GOAL */

            unchecked.erase(unchecked.begin() + curr_ind);
            checked.push_back(curr_pos);
            return 0;
        }
        else if (min_dist == INT_MAX)
        {
            std::cout << "No Path (without pushing boxes)";
            return 0;
        }
        // Reset min_dist
        min_dist = INT_MAX;

        std::cout << "current: " << curr_pos.x << ", " << curr_pos.y << ", " << curr_pos.dist << "\n";

        // Check all directions and update distance
        for (int i=0; i<unchecked.size(); i++){
            if (unchecked[i].x == curr_pos.x + 1 && unchecked[i].y == curr_pos.y)
            {
                unchecked[i].dist = std::min(unchecked[i].dist, curr_pos.dist + 1);
                // if (unchecked[i].check_for_goal(goals))
                // {
                //     reached_goal = true;
                //     break;
                // }
            }
            if (unchecked[i].x == curr_pos.x - 1 && unchecked[i].y == curr_pos.y)
            {
                unchecked[i].dist = std::min(unchecked[i].dist, curr_pos.dist + 1);
                // if (unchecked[i].check_for_goal(goals))
                // {
                //     reached_goal = true;
                //     break;
                // }
            }
            if (unchecked[i].x == curr_pos.x && unchecked[i].y == curr_pos.y + 1)
            {
                unchecked[i].dist = std::min(unchecked[i].dist, curr_pos.dist + 1);
                // if (unchecked[i].check_for_goal(goals))
                // {
                //     reached_goal = true;
                //     break;
                // }
            }
            if (unchecked[i].x == curr_pos.x && unchecked[i].y == curr_pos.y - 1)
            {
                unchecked[i].dist = std::min(unchecked[i].dist, curr_pos.dist + 1);
                // if (unchecked[i].check_for_goal(goals))
                // {
                //     reached_goal = true;
                //     break;
                // }
            }
        }
        unchecked.erase(unchecked.begin() + curr_ind);
        checked.push_back(curr_pos);

        std::cout << "unchecked \n";
        print_coord_vector(unchecked, print_dist);
        std::cout << "checked \n";
        print_coord_vector(checked, print_dist);
        std::cout << "Current index: " << curr_ind << "\n";

        if (reached_goal)
        {
            break;
        }
    }

    return 0;
}
