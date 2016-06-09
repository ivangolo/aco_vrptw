//
// Created by ivanedo on 17-05-16.
//

#ifndef VRPTW_ACO_EDGE_H
#define VRPTW_ACO_EDGE_H


#include <utility>
class Graph;

class Edge {
private:
    const std::pair<int, int> components;
    const long double cost;
    long double etha;  // heuristic value
    long double initial_pheromone;
    long double pheromone;  // current pheromone
    Graph* graph;

public:
    Edge(const std::pair<int, int> &components, const long double cost, Graph *graph);
    long double get_distance_cost();
    long double get_travel_time();
    std::pair<int, int> get_components();
    long double get_etha();
    long double get_initial_pheromone();
    long double get_pheromone();
    void set_initial_pheromone(long double initial_pheromone);
    void set_pheromone(long double pheromone);
    void print();
};


#endif //VRPTW_ACO_EDGE_H
