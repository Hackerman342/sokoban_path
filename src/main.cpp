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
    std::cout << "Started \n";
    // Initialize variables
	int x = 0, y = 0; // Define coordinate system
	int length;
    char c;
	std::vector < Coordinate > walls, free_space, boxes, goals;
    Coordinate start;

	// Read map file to character string
	std::ifstream input("input_samples/00_sample.in");
    std::string s_map((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());
    std::cout << "Imported map \n";
    std::cout << s_map << "\n";
    std::cout <<"Coordinates defined as \n";
    std::cout <<"(0,0) origin in top left \n";
    std::cout <<"x increases with rows, y with columns \n\n";

    // Step through map to characterize map
    // Initialize all distance values to INT_MAX
    length = s_map.size();
    for (int i =0; i<length; i++){
        c = s_map[i];

        if (c == ' '){
            free_space.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '#'){
            walls.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '.'){
            goals.push_back(Coordinate(x, y, INT_MAX));
            free_space.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '@'){
            start = Coordinate(x, y, INT_MAX);
            free_space.push_back(Coordinate(x, y, INT_MAX));}
        else if (c == '+'){
            start = Coordinate(x, y, INT_MAX);
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

    // Initialize all free spaces as unchecked nodes
    // Initialize all initial distance values to INT_MAX
    // Initialize possible moves: {Up, Down, Left, Right}
    std::vector < Coordinate > checked;
    std::vector < Coordinate > unchecked = free_space;
    // std::vector <int> dist(free_space.size(),INT_MAX);
    // std::pair <int, int> curr_pos = start;

    // Check if start is already at goal
    for (int i=0; i<goals.size(); i++)
    {
        if (goals[i].x == start.x && goals[i].y == start.y )
        {
            std::cout << "Already at goal \n";
        }
    }


    // for (int i=0; i<dist.size(); i++){std::cout << dist[i] << "  " << unchecked[i] << std::endl;}
    // while(unchecked.size()>0){

    //     std::vector<int>::iterator it = std::find(vecOfNums.begin(), vecOfNums.end(), 22);

    // }
    // for (int h = 0; h < 3; h++){
    //     for(int i = 0; i < moves.size(); i++){

    //         // Check if possible moves around current position are unchecked free space
    //         //auto ind = find(unchecked.begin(), unchecked.end(), pos+moves[i]);
    //         for(int j = 0; j < unchecked.size(); j++){
    //             if(unchecked[j] == pos+moves[i]){
    //                 dist[j] = posdist+1;
    //                 std::cout << "match  " << dist[j] << "  " << pos+moves[i] << std::endl;

    //             }
    //         }

    //     }
    //     posdist++;

    // }

    // for (int i=0; i<dist.size(); i++){std::cout << dist[i] << "  " << unchecked[i] << std::endl;}


    return 0;
}
