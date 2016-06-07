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
    long double last_arrival_time;
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
    void make_customer_visited(int customer_id);
    void return_to_the_depot();
    void local_pheromone_trail_update(Edge * edge);
    void restart();
    void update_capacity(Customer *new_customer);
    void update_last_arrival_time(Customer *last_vertex, Customer *new_customer);
    std::vector<Edge*> feasible_edges(Customer *last_vertex);

    Solution* get_solution();

};


#endif //VRPTW_ACO_ANT_H
