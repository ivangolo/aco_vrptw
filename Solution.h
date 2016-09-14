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
    double distance_;
    double balance_;
    int number_of_vehicles_;
    double waiting_time_;

public:
    Solution(Graph *grap);
    void add_edge(Edge* edge);
    Customer* last_visited_customer();
    void print();
    void print_lite();
    void print_tour();
    const std::vector<Edge*>& get_paths() const;
    void set_paths(std::vector<Edge*> paths);
    void restart();
    void calc_objectives();
    void calc_distance();
    double distance();
    void calc_balance();
    double balance();
    void calc_number_of_vehicles();
    int number_of_vehicles();
    void calc_waiting_time();
    double waiting_time();
    std::vector<double> objectives_values();
    std::vector<int> tour();

};


#endif //VRPTW_ACO_SOLUTION_H
