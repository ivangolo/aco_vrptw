//
// Created by ivanedo on 18-05-16.
//

#ifndef VRPTW_ACO_SOLUTION_H
#define VRPTW_ACO_SOLUTION_H


#include <deque>
#include "Graph.h"

class Solution {
private:
    Graph *graph;
    std::deque<int> customers;


public:
    Solution(Graph *grap);
    void add_customer(int customer_id);
    bool has_customer(int customer_id);
    Customer*  last_visited_vertex();
    // cost calculation
};


#endif //VRPTW_ACO_SOLUTION_H
