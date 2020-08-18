#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cout << "Started" << endl;
    // Initialize variables
	int w = 0, h = 0;
	int start, length, c;
    bool flag = false;
	vector <int> goals, free_space;

	// Read map file to character string
	ifstream input("input_samples/00_sample.in");
    string s_map((istreambuf_iterator<char>(input)),istreambuf_iterator<char>());
    //cout << s_map << endl;

    // Step through map to characterize map
    length = s_map.size();
    for (int i =0; i<length; i++){
        c = s_map[i];
        if (c == '#' && !flag){w++;}
        if (c == '\n'){h++; flag = true;}
        if (c == '@'){start = i;}
        if (c == '.'){goals.push_back(i);}
        if (c == ' '){free_space.push_back(i);}
    }
    //for (int i=0; i<free_space.size(); i++){cout << free_space[i] << endl;}
    //cout << start << "  " << goals[0] << "  " << goals[1] << endl;
    //cout << s_map[16] << s_map[17] << s_map[18] << s_map[19];


    /// Dijkstra's Algorithm to find goal

    // Initialize all free spaces as unchecked nodes
    // Initialize all initial distance values to INT_MAX
    // Initialize possible moves: {Up, Down, Left, Right}
    vector <int> checked;
    vector <int> unchecked = free_space;
    vector <int> dist(free_space.size(),INT_MAX);
    vector <int> moves{-1*(w+1), w+1, -1, 1};
    int pos = start, posdist = 0;
    //int *ind;


    for (int i=0; i<dist.size(); i++){cout << dist[i] << "  " << unchecked[i] << endl;}
    //while(unchecked.size()>0){
    for (int h = 0; h < 3; h++){
        for(int i = 0; i < moves.size(); i++){

            // Check if possible moves around current position are unchecked free space
            //auto ind = find(unchecked.begin(), unchecked.end(), pos+moves[i]);
            for(int j = 0; j < unchecked.size(); j++){
                if(unchecked[j] == pos+moves[i]){
                    dist[j] = posdist+1;
                    cout << "match  " << dist[j] << "  " << pos+moves[i] << endl;

                }
            }

        }
        posdist++;




    }

    for (int i=0; i<dist.size(); i++){cout << dist[i] << "  " << unchecked[i] << endl;}


    return 0;
}
