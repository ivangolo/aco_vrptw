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
    // std::cout << "q aleatorio generado: " << q <<  std::endl;
    if(q <= colony->get_q0()) {
        // std::cout << "follow the pseudorandom proportional rule" << std::endl;
        // follow the pseudorandom proportional rule
        return pseudorandom_proportional_rule(last_vertex);
    }
    // follow the random proportional rule
    // std::cout << "follow the random proportional rule" << std::endl;
    return random_proportional_rule(last_vertex);
}

Customer* Ant::pseudorandom_proportional_rule(Customer *last_vertex) {
    std::vector<Edge*> edges = graph->get_edges(last_vertex, unvisited_customers);
//    std::for_each(edges.begin(), edges.end(), [](Edge* edge) {
//        edge->print();
//    });

    std::vector<Edge*>::iterator max = std::max_element(edges.begin(), edges.end(), [this] (Edge* a, Edge* b) {
        return (a->get_pheromone()*std::pow(a->get_etha(), colony->get_beta())) < (b->get_pheromone()*std::pow(b->get_etha(), colony->get_beta()));
    });

    Customer *first = graph->get_customer((*max)->get_components().first);
    Customer *second = graph->get_customer((*max)->get_components().second);

    return last_vertex->get_id() != first->get_id() ? first : second;
}

Customer* Ant::random_proportional_rule(Customer *last_vertex) {
    std::vector<Edge*> edges = graph->get_edges(last_vertex, unvisited_customers);
//    std::for_each(edges.begin(), edges.end(), [](Edge* edge) {
//        edge->print();
//    });

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

void Ant::return_to_the_depot() {
    solution->add_customer(0);
    restart_remaining_capacity();
}

void Ant::run() {
    solution->add_customer(0); // depot as starting point

    while(!unvisited_customers.empty()) {
        Customer *last_visited = solution->last_visited_vertex();
        Customer *next_customer = next_move(last_visited);

        // check feasibility here
        if(is_feasible(last_visited, next_customer)) {
            // add the next customer to the solution
            solution->add_customer(next_customer->get_id());
            // decreasing capacity
            remaining_capacity -= next_customer->get_demand();
            // removing from unvisited customers
            unvisited_customers.erase(std::remove(unvisited_customers.begin(), unvisited_customers.end(), next_customer->get_id()), unvisited_customers.end());
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
    long double new_pheromone = (1 - colony->get_evaporation())*old_pheromone + colony->get_evaporation()*edge->get_initial_pheromone();
    edge->set_pheromone(new_pheromone);
}

void Ant::restart() {
    // restart capacity
    remaining_capacity = graph->get_vehicle_capacity();
    // restart unvisited customers list
    unvisited_customers = graph->get_customers_ids();
    // restart solution tour
    solution->restart();

}

void Ant::print_unvisited_customers() {
    std::cout << "Unvisited: [";
    copy(unvisited_customers.begin(), unvisited_customers.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "]"<< std::endl;

}
