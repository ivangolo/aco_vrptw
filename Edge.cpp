//
// Created by ivanedo on 17-05-16.
//

#include "Edge.h"
#include <iostream>

Edge::Edge(const std::pair<int, int> &edge, const long double cost, Graph *graph) : edge(edge), cost(cost), graph(graph) {
    etha = 1/cost;
}

const long double Edge::get_cost() const {
    return cost;
}

double Edge::get_initial_pheromone() {
    return initial_pheromone;
}

void Edge::set_initial_pheromone(double initial_pheromone) {
    this->initial_pheromone = initial_pheromone;
    this->pheromone = initial_pheromone;
}

double Edge::get_pheromone() {
    return pheromone;
}

long double Edge::get_etha() {
    return etha;
}

void Edge::print() {
    std::cout << "Edge: " << "(" << edge.first << ", " << edge.second << ")" << std::endl;
    std::cout << "Distance cost: " << cost << std::endl;
}