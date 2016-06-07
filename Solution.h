//
// Created by ivanedo on 18-05-16.
//

#ifndef VRPTW_ACO_SOLUTION_H
#define VRPTW_ACO_SOLUTION_H


#include <vector>
#include "Graph.h"

class Solution {
private:
    Graph *graph;
    std::vector<int> tour;

public:
    Solution(Graph *grap);
    void add_customer(int customer_id);
    Customer*  last_visited_vertex();
    void print();
    const std::vector<int>& get_tour() const;
    void set_tour(std::vector<int> tour);
    void restart();
    double cost();
    int number_of_vehicles();
};


#endif //VRPTW_ACO_SOLUTION_H
