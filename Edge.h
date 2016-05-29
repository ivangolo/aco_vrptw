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
    double initial_pheromone;
    double pheromone;  // current pheromone
    Graph* graph;

public:
    Edge(const std::pair<int, int> &components, const long double cost, Graph *graph);
    const long double get_distance_cost() const;
    const long double get_travel_time() const;
    const std::pair<int, int> get_components() const;
    long double get_etha();
    double get_initial_pheromone();
    double get_pheromone();
    void set_initial_pheromone(double initial_pheromone);
    void print();
};


#endif //VRPTW_ACO_EDGE_H
