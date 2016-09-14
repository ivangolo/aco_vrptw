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

void Solution::calc_distance() {
    if(paths.empty()) {
        this->distance_ = 0;
    }
    double distance = 0;
    std::for_each(paths.begin(), paths.end(), [&distance] (Edge *edge) {
        distance += edge->get_distance_cost();
    });
    this->distance_ = distance;
}

void Solution::calc_number_of_vehicles() {
    if (paths.empty()) {
        this->number_of_vehicles_ = 0;
    }
    int number_of_vehicles = 0;
    std::for_each(paths.begin(), paths.end(), [&number_of_vehicles] (Edge* edge) {
        if(edge->get_components().second == 0) {
            number_of_vehicles++;
        }
    });
    this->number_of_vehicles_ = number_of_vehicles;
}

void Solution::restart() {
    std::vector<Edge*>().swap(paths);
}

void Solution::calc_balance() {
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
    this->balance_ = *max - *min;
}

void Solution::calc_waiting_time() {
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
    this->waiting_time_ = waiting_time;
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

double Solution::balance() {
    return balance_;
}

double Solution::distance() {
    return distance_;
}

double Solution::waiting_time() {
    return waiting_time_;
}

int Solution::number_of_vehicles() {
    return number_of_vehicles_;
}

std::vector<double> Solution::objectives_values() {
    std::vector<char> objectives = graph->get_objectives();
    std::vector<double> values;
    for (auto o : objectives) {
        switch (o) {
            case 'b': values.push_back(balance());
                break;
            case 'd': values.push_back(distance());
                break;
            case 'v': values.push_back((double)number_of_vehicles());
                break;
            // case 'w': values.push_back(waiting_time());
            //     break;
            default:;
        }
    }
    return values;
}

std::vector<int> Solution::tour() {
    std::vector<int> tour;
    tour.push_back(0);
    for (auto edge : paths) {
        tour.push_back(edge->get_components().second);
    }
    return tour;
}

void Solution::calc_objectives() {
    calc_balance();
    calc_distance();
    calc_number_of_vehicles();
    // calc_waiting_time();
}
