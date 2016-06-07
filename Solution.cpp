//
// Created by ivanedo on 18-05-16.
//

#include "Solution.h"
#include <algorithm>
#include <iostream>
#include <iterator>

Solution::Solution(Graph *graph) : graph(graph) { }

void Solution::add_customer(int customer_id) {
    tour.push_back(customer_id);
}

Customer* Solution::last_visited_vertex() {
    return graph->get_customer(tour.back());
}

void Solution::print() {
    std::cout << "Solution sequence: [";
    copy(tour.begin(), tour.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "]"<< std::endl;
    std::cout << "Cost: " << cost() << std::endl;
    std::cout << "Number of Vehicles: " << number_of_vehicles() << std::endl;
}

const std::vector<int>& Solution::get_tour() const {
    return tour;
}

void Solution::set_tour(std::vector<int> tour) {
    this->tour = tour;
}

double Solution::cost() {
    if(tour.empty()) {
        return 0;
    }

    double cost = 0;
    for (std::vector<int>::iterator v = tour.begin(); v != tour.end() - 1; ++v) {
        Edge *edge = graph->get_edge(*v, *(v+1));
        cost += edge->get_distance_cost();
    }

    return cost;
}

int Solution::number_of_vehicles() {
    if (tour.empty()) {
        return 0;
    }

    int number_of_vehicles = (int) std::count(tour.begin(), tour.end(), 0);
    number_of_vehicles -= 1;

    return number_of_vehicles;
}

void Solution::restart() {
    std::vector<int>().swap(tour);
}