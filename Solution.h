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
    std::vector<Edge*> paths;

public:
    Solution(Graph *grap);
    void add_edge(Edge* edge);
    Customer* last_visited_customer();
    void print();
    void print_lite();
    const std::vector<Edge*>& get_paths() const;
    void set_paths(std::vector<Edge*> paths);
    void restart();
    double distance();
    double balance();
    int number_of_vehicles();
    double waiting_time();
    std::vector<double> objectives_values();
};


#endif //VRPTW_ACO_SOLUTION_H
