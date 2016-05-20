//
// Created by ivanedo on 17-05-16.
//

#ifndef VRPTW_ACO_ANT_H
#define VRPTW_ACO_ANT_H

#include "Solution.h"

class Colony;

class Ant {
private:
    Colony *colony;
    Graph *graph;
    Solution *solution;
    int remaining_capacity;

public:
    Ant(Colony *colony, Graph *graph);
    ~Ant();
    Solution* construct_solution();
    double generate_random_q();
    bool is_feasible(int i, int j);
    std::deque<int> feasible_neighborhood(int customer_id);
    // void local_update_of_pheromone();

    // construct solution here
    // add a new customer in a greedy way (only feasable addings)
    // until all customers are visited
    // calculate solution cost
    // compare with best solution found so far
    // deposit pheromone after solution construction (local update)

};


#endif //VRPTW_ACO_ANT_H
