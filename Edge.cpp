//
// Created by ivanedo on 17-05-16.
//

#include "Edge.h"
#include <iostream>

Edge::Edge(const std::pair<int, int> &components, const long double cost, Graph *graph) : components(components), cost(cost), graph(graph) {
    etha = 1/cost;
}

long double Edge::get_distance_cost() {
    return cost;
}

long double Edge::get_travel_time() {
    return cost;
}

std::pair<int, int> Edge::get_components() {
    return components;
}

long double Edge::get_initial_pheromone() {
    return initial_pheromone;
}

void Edge::set_initial_pheromone(long double initial_pheromone) {
    this->initial_pheromone = initial_pheromone;
    this->pheromone = initial_pheromone;
}

long double Edge::get_pheromone() {
    return pheromone;
}

void Edge::set_pheromone(long double pheromone) {
    this->pheromone = pheromone;
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

void Edge::print_components() {
    std::cout << "(" << components.first << ", " << components.second <<  ")";
}
