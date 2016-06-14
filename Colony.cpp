//
// Created by ivanedo on 17-05-16.
//

#include "Colony.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <ctime>

Colony::Colony(const double beta, const double phi, const double xi, const int size, const int max_iterations, const double q0, const double initial_pheromone, Graph *graph) : beta(beta), phi(phi), xi(xi), size(size), max_iterations(max_iterations), q0(q0), initial_pheromone(initial_pheromone), graph(graph) {
    create_ants();
    best_solution = new Solution(graph);
    deposit_initial_pheromone();
}

void Colony::create_ants() {
    for (int i = 0; i < size; ++i) {
        ants.push_back(new Ant(this, graph));
    }
}

Colony::~Colony() {
    std::for_each(ants.begin(), ants.end(), std::default_delete<Ant>());
    std::for_each(pareto_front.begin(), pareto_front.end(), std::default_delete<Solution>());
    // delete best_solution;
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

    save_pareto_front();
}

void Colony::save_best_solution() {
    std::vector<Ant*>::iterator min_ant = std::min_element(ants.begin(), ants.end(), [] (Ant *ant_a, Ant *ant_b) {
        return ant_a->get_solution()->distance() < ant_b->get_solution()->distance();
    });

    if((*min_ant)->get_solution()->distance() < best_solution->distance() || best_solution->distance() == 0) {
        best_solution->set_paths((*min_ant)->get_solution()->get_paths());
    }
}

void Colony::restart_ants() {
    for (auto ant : ants) {
        ant->restart();
    }
}

void Colony::global_update_pheromone_trail() {
    std::vector<double> means = mean_objectives();

    for (auto solution : pareto_front) {

        for (auto edge : solution->get_paths()) {
            long double old_pheromone = edge->get_pheromone();
            long double new_pheromone = (1 - phi)*old_pheromone + phi*(1.0/(means[0]));
            edge->set_pheromone(new_pheromone);
        }

    }

}

void Colony::step() {

    for (auto ant : ants) {
        ant->run();
    }

    update_pareto_front();

    global_update_pheromone_trail();

    restart_ants();

    std::cout << ":::::::Pareto front:::::::" << std::endl;
    print_pareto_front();
}

bool Colony::dominates(const std::vector<double> &v, const std::vector<double> &w) {
    if (v == w) {
        return false;
    }

    size_t sum = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        sum += v[i] <= w[i];
    }
    return sum == v.size();
}

void Colony::update_pareto_front() {
    for (auto ant : ants) {

        if (pareto_front.empty()) {
            pareto_front.push_back(new Solution(*(ant->get_solution())));
            continue;
        }

        bool dominated = false;
        bool present = false;
        std::vector<double> objectives = ant->get_solution()->objectives_values();
        for (auto it = pareto_front.begin(); it != pareto_front.end();) {

            if (dominates((*it)->objectives_values(), objectives)) {
                dominated = true;
                break;
            }

            if (ant->get_solution()->tour() == (*it)->tour()) {
                present = true;
                break;
            }

            if (dominates(objectives, (*it)->objectives_values())) {
                delete *it;
                it = pareto_front.erase(it);

            } else {
                ++it;
            }

        }

        if (dominated || present) {
            continue;
        } else {
            pareto_front.push_back(new Solution(*(ant->get_solution())));
        }
    }

}

std::vector<double> Colony::mean_objectives() {
    std::vector<double> mean_objectives = pareto_front.front()->objectives_values();
    size_t size = mean_objectives.size();
    std::for_each(pareto_front.begin() + 1, pareto_front.end(), [&mean_objectives, size] (Solution *solution) {
        std::vector<double> objectives = solution->objectives_values();

        for (size_t i = 0; i < size; ++i) {
            mean_objectives[i] += objectives[i];
        }

    });

    for (size_t i = 0; i < size; ++i) {
        mean_objectives[i] /= pareto_front.size();
    }

    // distance, vehicles, balance, waiting time
    return mean_objectives;
}

void Colony::save_pareto_front() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    char datetime[50];
    std::strftime(datetime, sizeof(datetime), "%Y%m%d%H%M%S", &tm);
    std::string directory = "../pareto/";
    std::string filename_parameters = directory + std::string(datetime) + std::to_string(graph->get_customers_number()) + "_" + graph->get_name() + "_" + "parameters.txt";
    std::string filename_solutions = directory + std::string(datetime) + std::to_string(graph->get_customers_number()) + "_" + graph->get_name() + "_" + "pareto.txt";
    std::ofstream parameters_file(filename_parameters);
    std::ofstream pareto_file(filename_solutions);

    parameters_file << "Instance name: " << graph->get_name() << std::endl;
    parameters_file << "Total customers: " << graph->get_customers_number() << std::endl;
    parameters_file << "ACS parameters: " << std::endl;
    parameters_file << "\tBeta: " << beta << std::endl;
    parameters_file << "\tPhi: " << phi << std::endl;
    parameters_file << "\tXi: " << xi << std::endl;
    parameters_file << "\tAnts: " << size << std::endl;
    parameters_file << "\tq0: " << q0 << std::endl;
    parameters_file << "\tMax. iterations: " << max_iterations << std::endl;
    parameters_file << "\tInitial pheromone: " << initial_pheromone << std::endl;
    parameters_file << "\tNumber of solutions: " << pareto_front.size() << std::endl;

    pareto_file << "#" << std::endl;
    for (auto solution : pareto_front) {
        std::vector<double> v = solution->objectives_values();
        for (size_t i = 0; i < v.size(); ++i) {
            pareto_file << v[i] << " ";
        }
        pareto_file << std::endl;
    }
    pareto_file << "#" << std::endl;

    parameters_file.close();
    pareto_file.close();
}

void Colony::print_pareto_front() {
    for (auto solution : pareto_front) {
        std::vector<double> v = solution->objectives_values();
        for (size_t i = 0; i < v.size(); ++i) {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;
    }
}
