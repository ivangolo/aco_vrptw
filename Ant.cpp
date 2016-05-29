//
// Created by ivanedo on 17-05-16.
//

#include "Ant.h"
#include "Colony.h"
#include <random>
#include <algorithm>

Ant::Ant(Colony *colony, Graph *graph) : colony(colony), graph(graph) {
    solution = new Solution(graph);  // Initialize solution
    remaining_capacity = graph->get_vehicle_capacity();
    unvisited_customers = graph->get_customers_ids();
}

Ant::~Ant() {
    delete solution;
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

        if(last_vertex->get_earliest_time() + last_vertex->get_service_time() + edge->get_travel_time() <= next_vertex->get_latest_time()) {  // time constraint
            return true;
        }

    }
    return false;
}

void Ant::restart_remaining_capacity() {
    remaining_capacity = graph->get_vehicle_capacity();
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
    std::deque<Edge*> edges = graph->get_edges(last_vertex, unvisited_customers);
    std::deque<Edge*>::iterator max = std::max_element(edges.begin(), edges.end(), [this] (Edge* a, Edge* b) {
        return (a->get_pheromone()*std::pow(a->get_etha(), colony->get_beta())) < (b->get_pheromone()*std::pow(b->get_etha(), colony->get_beta()));
    });

    Customer *first = graph->get_customer((*max)->get_components().first);
    Customer *second = graph->get_customer((*max)->get_components().second);

    return last_vertex->get_id() != first->get_id() ? first : second;
}

Customer* Ant::random_proportional_rule(Customer *last_vertex) {
    std::deque<Edge*> edges = graph->get_edges(last_vertex, unvisited_customers);

    long double sum_weights = 0;
    std::deque<std::pair<Edge*, long double>> weights;
    std::for_each(edges.begin(), edges.end(), [this, &weights, &sum_weights](Edge* edge) {
        long double weight = std::pow(edge->get_pheromone(), colony->get_alpha()) * std::pow(edge->get_etha(), colony->get_beta());
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

Solution* Ant::construct_solution() {
    solution->add_customer(0); // depot as starting point
    // greedy process here

    while(!unvisited_customers.empty()) {

        Customer *last_visited = solution->last_visited_vertex();
        Customer *next_customer = next_move(last_visited);

        // check feasibility here
        if(is_feasible(last_visited, next_customer)) {
            // add the next customer to the solution
            solution->add_customer(next_customer->get_id());
            unvisited_customers.erase(std::remove(unvisited_customers.begin(), unvisited_customers.end(), last_visited->get_id()), unvisited_customers.end());
        } else {
            // Return to the depot
            solution->add_customer(0);
            // restart remaining capacity
            restart_remaining_capacity();
        }

    }

    return solution;
}