//
// Created by ivanedo on 17-05-16.
//

#include "Colony.h"
#include <algorithm>
#include <memory>

Colony::Colony(const double alpha, const double beta, const double rho, const int size, const int max_iterations, const double q0, const double initial_pheromone, Graph *graph) : alpha(alpha), beta(beta), rho(rho), size(size), max_iterations(max_iterations), q0(q0), initial_pheromone(initial_pheromone), graph(graph) {
    create_ants();
}

void Colony::create_ants() {
    for (int i = 0; i < size; ++i) {
        ants.push_back(new Ant(this, graph));
    }
}

Colony::~Colony() {
    std::for_each(ants.begin(), ants.end(), std::default_delete<Ant>());
}

const double Colony::get_alpha() const {
    return alpha;
}

const double Colony::get_beta() const {
    return beta;
}

const double Colony::get_rho() const {
    return rho;
}

const int Colony::get_size() const {
    return size;
}

const int Colony::get_max_iterations() const {
    return max_iterations;
}

const double Colony::get_q0() const {
    return q0;
}

void Colony::deposit_initial_pheromone() {
    std::deque<Edge*>::iterator edge;
    for (edge = graph->get_edges().begin(); edge != graph->get_edges().end(); ++edge) {
        (*edge)->set_initial_pheromone(initial_pheromone);
    }
}