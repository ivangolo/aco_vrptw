//
// Created by ivanedo on 17-05-16.
//

#include "Edge.h"
#include <iostream>

Edge::Edge(const std::pair<int, int> &components, const long double cost, Graph *graph) : components(components), cost(cost), graph(graph) {
    etha = 1/cost;
}

const long double Edge::get_distance_cost() const {
    return cost;
}

const long double Edge::get_travel_time() const {
    return cost;
}

const std::pair<int, int> Edge::get_components() const {
    return components;
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
    std::cout << "Edge: " << "(" << components.first << ", " << components.second << ")" << std::endl;
    std::cout << "Distance cost: " << cost << std::endl;
    std::cout << "Pheromone: " << pheromone << std::endl;
    std::cout << "Etha: " << etha << std::endl;
}