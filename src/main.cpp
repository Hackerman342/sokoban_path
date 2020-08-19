#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "sokoban_util.cpp"

int main()
{
    std::cout << "Started \n";
    // Initialize variables
	int x = 0, y = 0; // Define coordinate system
	int length, c, INT_MAX;
    // bool flag = false;
    std::pair <int, int> start;
	std::vector < std::pair <int, int>> walls, free_space, boxes, goals;

	// Read map file to character string
	std::ifstream input("input_samples/00_sample.in");
    std::string s_map((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());
    std::cout << "Imported map \n";
    std::cout << s_map << "\n";
    std::cout <<"Coordinates defined as \n";
    std::cout <<"(0,0) origin in top left \n";
    std::cout <<"x increases with rows, y with columns \n\n";

    // Step through map to characterize map
    length = s_map.size();
    for (int i =0; i<length; i++){
        c = s_map[i];
        if (c == ' '){
            free_space.push_back(std::make_pair(x, y));}
        else if (c == '#'){
            walls.push_back(std::make_pair(x, y));}
        else if (c == '.'){
            goals.push_back(std::make_pair(x, y));
            free_space.push_back(std::make_pair(x, y));}
        else if (c == '@'){
            start = std::make_pair(x, y);
            free_space.push_back(std::make_pair(x, y));}
        else if (c == '+'){
            start = std::make_pair(x, y);
            goals.push_back(std::make_pair(x, y));
            free_space.push_back(std::make_pair(x, y));}
        else if (c == '$'){
            boxes.push_back(std::make_pair(x, y));}
        else if (c == '*'){
            boxes.push_back(std::make_pair(x, y));
            goals.push_back(std::make_pair(x, y));}
        else if (c == '\n'){
            x++; y = -1;}
        y++;
    }

    // Print map details
    std::cout << "start \n";
    std::cout << "(" << start.first << ", " << start.second << ")\n";
    std::cout << "goals \n";
    print_pair_vector(goals);
    std::cout << "free space \n";
    print_pair_vector(free_space);
    std::cout << "walls \n";
    print_pair_vector(walls);
    std::cout << "boxes \n";
    print_pair_vector(boxes);


    // /// Dijkstra's Algorithm to find goal

    // // Initialize all free spaces as unchecked nodes
    // // Initialize all initial distance values to INT_MAX
    // // Initialize possible moves: {Up, Down, Left, Right}
    // std::vector <int> checked;
    // std::vector <int> unchecked = free_space;
    // std::vector <int> dist(free_space.size(),INT_MAX);
    // std::vector <int> moves{-1*(w+1), w+1, -1, 1};
    // int pos = start, posdist = 0;
    // //int *ind;


    // for (int i=0; i<dist.size(); i++){std::cout << dist[i] << "  " << unchecked[i] << std::endl;}
    // //while(unchecked.size()>0){
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
