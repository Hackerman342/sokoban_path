#include <iostream>
#include "Coordinate.cpp"

void print_coord_vector(std::vector < Coordinate > vec, bool dist_flag);
// void print_pair_vector(std::vector < std::pair <int, int>> vec);

void print_coord_vector(std::vector < Coordinate > vec, bool print_dist)
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

}

// void print_pair_vector(std::vector < std::pair <int, int>> vec)
// {
//     for (int i=0; i<vec.size(); i++)
//     {
//         std::cout << "(" << vec[i].first << ", " << vec[i].second << ")";
//         if ( i < vec.size() - 1){std::cout << ", ";}
//         else{std::cout <<"\n";}
//     }

// }