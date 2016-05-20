//
// Created by ivanedo on 17-05-16.
//

#include "Ant.h"
#include <random>

Ant::Ant(Colony *colony, Graph *graph) : colony(colony), graph(graph) {
    solution = new Solution(graph);  // Initialize solution
    remaining_capacity = graph->get_vehicle_capacity();
}

Ant::~Ant() {
    delete solution;
}

double Ant::generate_random_q() {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<> distr(0, 1);
    return distr(generator);
}

bool Ant::is_feasible(int i, int j) {
    // check capacity and time constraints

    return false;
}

std::deque<int> Ant::feasible_neighborhood(int customer_id) {
    std::deque<int> neighborhood;
    std::deque<Customer*>::iterator customer;
    for (customer = graph->get_customers().begin(); customer != graph->get_customers().end(); ++customer) {

        if((*customer)->get_id() != customer_id && !solution->has_customer((*customer)->get_id())) {

            if(is_feasible(customer_id, (*customer)->get_id())) {
                neighborhood.push_back((*customer)->get_id());
            }

        }
    }

    return neighborhood;
}

Solution* Ant::construct_solution() {
    solution->add_customer(0); // depot as starting point
    // greedy process here
    double q = generate_random_q();

    // do until all customers are visited
    // first, get the feasible movements from the last visited customer
    int last_visited = solution->last_visited_customer();

    if(last_visited == 0) {  // depot
        remaining_capacity = graph->get_vehicle_capacity();
    }

    // check if the last visited customer is the depot. In that case, we start a new route

    // std::deque<int> feasible_hood = feasible_neighborhood(last_visited);

    return solution;
}