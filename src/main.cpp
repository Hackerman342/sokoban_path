#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::cout << "Started" << std::endl;
    // Initialize variables
	int w = 0, h = 0;
	int start, length, c, INT_MAX;
    bool flag = false;
	std::vector <int> goals, free_space, boxes;

	// Read map file to character string
	std::ifstream input("input_samples/00_sample.in");
    std::string s_map((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());
    std::cout << "Imported map" << std::endl;
    std::cout << s_map << std::endl;

    // Step through map to characterize map
    length = s_map.size();
    for (int i =0; i<length; i++){
        c = s_map[i];
        if (c == '#' && !flag){w++;}
        else if (c == '\n'){h++; flag = true;}
        else if (c == '@'){start = i;}
        else if (c == '.'){goals.push_back(i);}
        else if (c == ' '){free_space.push_back(i);}
        else if (c == '$'){boxes.push_back(i);}
    }
    std::cout << "free spaces" << std::endl;
    for (int i=0; i<free_space.size(); i++){std::cout << free_space[i] << ", ";}
    std::cout << std::endl << "start" << std::endl;
    std::cout << start;
    std::cout << std::endl << "goals" << std::endl;
    for (int i=0; i<goals.size(); i++){std::cout << goals[i] << ", ";}
    std::cout << std::endl << "boxes" << std::endl;
    for (int i=0; i<boxes.size(); i++){std::cout << boxes[i] << ", ";}
    std::cout << std::endl;



    /// Dijkstra's Algorithm to find goal

    // Initialize all free spaces as unchecked nodes
    // Initialize all initial distance values to INT_MAX
    // Initialize possible moves: {Up, Down, Left, Right}
    std::vector <int> checked;
    std::vector <int> unchecked = free_space;
    std::vector <int> dist(free_space.size(),INT_MAX);
    std::vector <int> moves{-1*(w+1), w+1, -1, 1};
    int pos = start, posdist = 0;
    //int *ind;


    for (int i=0; i<dist.size(); i++){std::cout << dist[i] << "  " << unchecked[i] << std::endl;}
    //while(unchecked.size()>0){
    for (int h = 0; h < 3; h++){
        for(int i = 0; i < moves.size(); i++){

            // Check if possible moves around current position are unchecked free space
            //auto ind = find(unchecked.begin(), unchecked.end(), pos+moves[i]);
            for(int j = 0; j < unchecked.size(); j++){
                if(unchecked[j] == pos+moves[i]){
                    dist[j] = posdist+1;
                    std::cout << "match  " << dist[j] << "  " << pos+moves[i] << std::endl;

                }
            }

        }
        posdist++;




    }

    for (int i=0; i<dist.size(); i++){std::cout << dist[i] << "  " << unchecked[i] << std::endl;}


    return 0;
}
