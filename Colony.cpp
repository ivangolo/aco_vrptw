//
// Created by ivanedo on 17-05-16.
//

#include "Colony.h"
#include <algorithm>
#include <iostream>
#include <memory>

Colony::Colony(const double beta, const double phi, const double xi, const int size, const int max_iterations, const double q0, const double initial_pheromone, Graph *graph) : beta(beta), phi(phi), xi(xi), size(size), max_iterations(max_iterations), q0(q0), initial_pheromone(initial_pheromone), graph(graph) {
    create_ants();
    best_solution = new Solution(graph);
}

void Colony::create_ants() {
    for (int i = 0; i < size; ++i) {
        ants.push_back(new Ant(this, graph));
    }
}

Colony::~Colony() {
    std::for_each(ants.begin(), ants.end(), std::default_delete<Ant>());
    delete best_solution;
}

double Colony::get_beta(){
    return beta;
}

double Colony::get_local_evaporation(){
    return xi;
}

double Colony::get_q0() {
    return q0;
}

void Colony::deposit_initial_pheromone() {
    for (std::vector<Edge*>::const_iterator edge = graph->get_edges().begin(); edge != graph->get_edges().end(); ++edge) {
        (*edge)->set_initial_pheromone(initial_pheromone);
    }
}

void Colony::run() {
    for (int i = 1; i <= max_iterations; ++i) {
        std::cout << "::::::::::::::::::::::::::::::::::Iteration: " << i << " :::::::::::::::::::::::::::::::::" << std::endl;
        step();
    }
}

void Colony::save_best_solution() {
    std::vector<Ant*>::iterator min_ant = std::min_element(ants.begin(), ants.end(), [] (Ant *ant_a, Ant *ant_b) {
        return ant_a->get_solution()->cost() < ant_b->get_solution()->cost();
    });

    if((*min_ant)->get_solution()->cost() < best_solution->cost() || best_solution->cost() == 0) {
        best_solution->set_tour((*min_ant)->get_solution()->get_tour());
    }
}

void Colony::restart_ants() {
    for (std::vector<Ant*>::iterator ant = ants.begin(); ant != ants.end(); ++ant) {
        (*ant)->restart();
    }
}

void Colony::global_update_pheromone_trail() {
    long double best_solution_cost = best_solution->cost();
    for (std::vector<int>::const_iterator v = best_solution->get_tour().begin(); v != best_solution->get_tour().end() - 1; ++v) {
        Edge *edge = graph->get_edge(*v, *(v+1));
        long double old_pheromone = edge->get_pheromone();
        long double new_pheromone = (1 - phi)*old_pheromone + phi*(1.0/best_solution_cost);
        edge->set_pheromone(new_pheromone);
    }
}

void Colony::step() {

    for (std::vector<Ant*>::iterator ant = ants.begin(); ant != ants.end(); ++ant) {
        (*ant)->run();
    }

    // get best solution
    save_best_solution();
    std::cout << "Best solution: " << std::endl;
    best_solution->print();
    // global update of pheromone trails
    global_update_pheromone_trail();

    restart_ants();
}