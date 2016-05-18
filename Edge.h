//
// Created by ivanedo on 17-05-16.
//

#ifndef VRPTW_ACO_EDGE_H
#define VRPTW_ACO_EDGE_H


#include <utility>
class Graph;

class Edge {
private:
    const std::pair<int, int> edge;
    const long double distance_cost;
    Graph* graph;

public:

    Edge(const std::pair<int, int> &edge, const long double distance_cost, Graph *graph) : edge(edge), distance_cost(distance_cost), graph(graph) { }

    const double get_distance_cost() const {
        return distance_cost;
    }

    void print();
};


#endif //VRPTW_ACO_EDGE_H
