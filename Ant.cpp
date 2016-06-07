//
// Created by ivanedo on 17-05-16.
//

#include "Ant.h"
#include "Colony.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <iterator>

Ant::Ant(Colony *colony, Graph *graph) : colony(colony), graph(graph) {
    solution = new Solution(graph);  // Initialize solution
    remaining_capacity = graph->get_vehicle_capacity();
    last_arrival_time = graph->get_customer(0)->get_earliest_time();
    unvisited_customers = graph->get_customers_ids();
}

Ant::~Ant() {
    delete solution;
}

Solution* Ant::get_solution() {
    return solution;
}

double Ant::generate_random_number() {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<> distr(0, 1);
    return distr(generator);
}

bool Ant::is_feasible(Customer *last_vertex, Customer *next_vertex) {
    // check capacity and time constraints
    Edge *edge = graph->get_edge(last_vertex->get_id(), next_vertex->get_id());
    if(next_vertex->get_demand() <= remaining_capacity) {  // capacity constraint

        if (last_arrival_time + last_vertex->get_service_time() + edge->get_travel_time() <= next_vertex->get_latest_time()) {  // time constraint
            return true;
        }
    }
    return false;
}

std::vector<Edge*> Ant::feasible_edges(Customer *last_vertex) {
    std::vector<Edge*> feasibles;
    for (auto j = unvisited_customers.begin(); j != unvisited_customers.end(); ++j) {
        if(is_feasible(last_vertex, graph->get_customer(*j))) {
            feasibles.push_back(graph->get_edge(last_vertex->get_id(), *j));
        }
    }
    return feasibles;
}

Customer* Ant::next_move(Customer *last_vertex) {
    double q = generate_random_number();
    if(q <= colony->get_q0()) {
        // follow the pseudorandom proportional rule
        return pseudorandom_proportional_rule(last_vertex);
    }
    // follow the random proportional rule
    return random_proportional_rule(last_vertex);
}

Customer* Ant::pseudorandom_proportional_rule(Customer *last_vertex) {
    std::vector<Edge*> edges = feasible_edges(last_vertex);
    if (edges.empty()) {
        return NULL;
    }
    std::vector<Edge*>::iterator max = std::max_element(edges.begin(), edges.end(), [this] (Edge* a, Edge* b) {
        return (a->get_pheromone()*std::pow(a->get_etha(), colony->get_beta())) < (b->get_pheromone()*std::pow(b->get_etha(), colony->get_beta()));
    });

    Customer *first = graph->get_customer((*max)->get_components().first);
    Customer *second = graph->get_customer((*max)->get_components().second);
    return last_vertex->get_id() != first->get_id() ? first : second;
}

Customer* Ant::random_proportional_rule(Customer *last_vertex) {
    std::vector<Edge*> edges = feasible_edges(last_vertex);
    if (edges.empty()) {
        return NULL;
    }
    long double sum_weights = 0;
    std::deque<std::pair<Edge*, long double>> weights;
    std::for_each(edges.begin(), edges.end(), [this, &weights, &sum_weights](Edge* edge) {
        long double weight = edge->get_pheromone() * std::pow(edge->get_etha(), colony->get_beta());
        weights.push_back(std::make_pair(edge, weight));
        sum_weights += weight;
    });

    long double pick = generate_random_number() * sum_weights;
    long double current = 0;
    auto weight = weights.begin();
    for (; weight != weights.end(); ++weight) {
        current += (*weight).second;
        if (current >= pick) {
            break;
        }
    }
    Customer *first = graph->get_customer((*weight).first->get_components().first);
    Customer *second = graph->get_customer((*weight).first->get_components().second);
    return last_vertex->get_id() != first->get_id() ? first : second;
}

void Ant::make_customer_visited(int customer_id) {
    solution->add_customer(customer_id);
    unvisited_customers.erase(std::remove(unvisited_customers.begin(), unvisited_customers.end(), customer_id), unvisited_customers.end());
}

void Ant::return_to_the_depot() {
    solution->add_customer(0);
    last_arrival_time = graph->get_customer(0)->get_earliest_time();
    remaining_capacity = graph->get_vehicle_capacity();
}

void Ant::run() {
    solution->add_customer(0); // depot as starting point
    while(!unvisited_customers.empty()) {
        Customer *last_visited = solution->last_visited_vertex();
        Customer *next_customer = next_move(last_visited);

        if (next_customer) {
            // update last arrival time
            update_last_arrival_time(last_visited, next_customer);
            // decreasing capacity
            update_capacity(next_customer);
            // add the next customer to the solution and remove it from unvisited customers
            make_customer_visited(next_customer->get_id());
            // do local pheromone trail update
            local_pheromone_trail_update(graph->get_edge(last_visited->get_id(), next_customer->get_id()));
        } else {
            // Return to the depot
            return_to_the_depot();
            // do local pheromone trail update
            local_pheromone_trail_update(graph->get_edge(last_visited->get_id(), 0));
        }
    }
    solution->add_customer(0); // depot as final point
}


void Ant::local_pheromone_trail_update(Edge *edge) {
    long double old_pheromone = edge->get_pheromone();
    long double new_pheromone = (1 - colony->get_local_evaporation())*old_pheromone + colony->get_local_evaporation()*edge->get_initial_pheromone();
    edge->set_pheromone(new_pheromone);
}

void Ant::restart() {
    // restart capacity
    remaining_capacity = graph->get_vehicle_capacity();
    // restart unvisited customers list
    unvisited_customers = graph->get_customers_ids();
    // set earliest arrival time last customer
    last_arrival_time = graph->get_customer(0)->get_earliest_time();
    // restart solution tour
    solution->restart();
}

void Ant::update_last_arrival_time(Customer *last_vertex, Customer *new_customer) {
    Edge *edge = graph->get_edge(last_vertex->get_id(), new_customer->get_id());
    if (last_arrival_time + last_vertex->get_service_time() + edge->get_travel_time() > new_customer->get_earliest_time()) {
        last_arrival_time +=  last_vertex->get_service_time() + edge->get_travel_time();
    } else {
        last_arrival_time = new_customer->get_earliest_time();
    }
}

void Ant::update_capacity(Customer *new_customer) {
    remaining_capacity -= new_customer->get_demand();
}
