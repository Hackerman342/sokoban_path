# sokoban_path
Find the optimal path in a 2D search space

## Overview
This exercise is based on the introductory exercise (not a course requirement) for KTH Course DD2380 - Artificial Intelligence.
I didn't take DD2380, but chose to complete this as an exercise in improving my C++ abilities.

Details for the exercise can be found at [Sokoban pathfinding exercise](https://kth.kattis.com/problems/kth.ai.sokobanpathfinding)

## Current Status
This program successfully finds the optimal path from the starting position to an open goal pose if one is available WITHOUT pushing any boxes.
The optimal path is found with Dijkstra's algorithm.

### Possible Future Improvements
Possible future improvements / expansions include:
* Finding the optimal path while utilizing the ability to push boxes.
    * A weight would be given to every push so there is a balance between walking further vs pushing boxes in finding the optimal path.
        * (e.g. pushing a box one space could be equivalent to walking 5 open spaces)
* Incorporating moving obstacles into the map. e.g:
    * Walls that slide back and forth between two spots
        * The walls would slide for every step taken by the agent, so a certain path would require reaching a certain moving obstacle with either an even or odd number of steps to successfully pass through.
    * Gates that open and close
        * Same idea as moving walls
    * Enemy agents to avoid
* Adding a distance heuristic to Dijkstra's search Algorithm to find the optimal path faster (as with A*)

## Basic Running
* Compile with: `$ g++ -o exe_Name ScriptName.cpp`
    * `g++ -o bin/sokoban_path src/main.cpp`
* Execute with: `$ ./exe_name map_file`
    * `./bin/sokoban_path input_samples\00_sample.in`