//
// Created by ivanedo on 18-05-16.
//

#include "Solution.h"
#include <algorithm>
#include <iostream>
#include <iterator>

Solution::Solution(Graph *graph) : graph(graph) {}

void Solution::print() {
    std::cout << "Solution sequence: [";
    std::cout << paths.front()->get_components().first << ", " << paths.front()->get_components().second << ", ";
    std::for_each(paths.begin() + 1, paths.end(), [] (Edge *edge) {
        std::cout << edge->get_components().second << ", ";
    });
    std::cout << "]" << std::endl;
    std::cout << "Cost: " << distance() << std::endl;
    std::cout << "Number of Vehicles: " << number_of_vehicles() << std::endl;
    std::cout << "Balance: " << balance() << std::endl;
    std::cout << "Total waiting time: " << waiting_time() << std::endl;
}

void Solution::print_lite() {
    std::vector<double> v = objectives_values();
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

void Solution::print_tour() {
    std::vector<int> t = tour();
    for (size_t i = 0; i < t.size(); ++i) {
        std::cout << t[i] << " ";
    }
    std::cout << std::endl;
}

double Solution::distance() {
    if(paths.empty()) {
        return 0;
    }
    double distance = 0;
    std::for_each(paths.begin(), paths.end(), [&distance] (Edge *edge) {
        distance += edge->get_distance_cost();
    });
    return distance;
}

int Solution::number_of_vehicles() {
    if (paths.empty()) {
        return 0;
    }
    int number_of_vehicles = 0;
    std::for_each(paths.begin(), paths.end(), [&number_of_vehicles] (Edge* edge) {
        if(edge->get_components().second == 0) {
            number_of_vehicles++;
        }
    });
    return number_of_vehicles;
}

void Solution::restart() {
    std::vector<Edge*>().swap(paths);
}

double Solution::balance() {
    double tmp = 0;
    std::vector<double> distances;
    std::for_each(paths.begin(), paths.end(), [&tmp, &distances] (Edge *edge) {
        tmp += edge->get_distance_cost();
        if (edge->get_components().second == 0) {
            distances.push_back(tmp);
            tmp = 0;
        }
    });
    auto min = std::min_element(distances.begin(), distances.end());
    auto max = std::max_element(distances.begin(), distances.end());
    return *max - *min;
}

double Solution::waiting_time() {
    double waiting_time = 0;
    double last_arrival_time = 0;
    std::for_each(paths.begin(), paths.end(), [this, &waiting_time, &last_arrival_time] (Edge *edge) {
        Customer *start = graph->get_customer(edge->get_components().first);
        Customer *end = graph->get_customer(edge->get_components().second);

        if (end->get_id() != 0) {

            if (last_arrival_time + start->get_service_time() + edge->get_travel_time() < end->get_earliest_time()) {
                waiting_time += end->get_earliest_time() - last_arrival_time - start->get_service_time() - edge->get_travel_time();
            } else {
                last_arrival_time += start->get_service_time() + edge->get_travel_time();
            }

        } else {
            last_arrival_time = 0;
        }

    });
    return waiting_time;
}

void Solution::add_edge(Edge *edge) {
    paths.push_back(edge);
}

Customer* Solution::last_visited_customer() {
    return graph->get_customer(paths.back()->get_components().second);
}

const std::vector<Edge*>& Solution::get_paths() const {
    return paths;
}

void Solution::set_paths(std::vector<Edge *> paths) {
    this->paths = paths;
}

std::vector<double> Solution::objectives_values() {
    std::vector<double> objectives {distance(), balance()};
    return objectives;
}

std::vector<int> Solution::tour() {
    std::vector<int> tour;
    tour.push_back(0);
    for (auto edge : paths) {
        tour.push_back(edge->get_components().second);
    }
    return tour;
}
