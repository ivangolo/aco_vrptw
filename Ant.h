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
    std::vector<int> unvisited_customers;

public:
    Ant(Colony *colony, Graph *graph);
    ~Ant();
    void run();
    double generate_random_number();
    bool is_feasible(Customer *last_vertex, Customer *next_vertex);
    Customer* next_move(Customer *last_vertex);
    Customer* pseudorandom_proportional_rule(Customer *last_vertex);
    Customer* random_proportional_rule(Customer *last_vertex);
    void restart_remaining_capacity();
    void return_to_the_depot();
    void local_pheromone_trail_update(Edge * edge);
    void print_unvisited_customers();
    void restart();
    Solution* get_solution();

};


#endif //VRPTW_ACO_ANT_H
