#include <iostream>

void print_pair_vector(std::vector < std::pair <int, int>> vec);

void print_pair_vector(std::vector < std::pair <int, int>> vec)
{
    for (int i=0; i<vec.size(); i++)
        {
            std::cout << "(" << vec[i].first << ", " << vec[i].second << ")";
            if ( i < vec.size() - 1){std::cout << ", ";}
            else{std::cout <<"\n";}
        }

}