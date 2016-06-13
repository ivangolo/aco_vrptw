//
// Created by ivanedo on 17-05-16.
//

#ifndef VRPTW_ACO_COLONY_H
#define VRPTW_ACO_COLONY_H
#include <vector>
#include "Ant.h"

class Colony {
private:
    const double beta;
    const double phi;  // pheromone's evaporation rate (global update)
    const double xi; // pheromone's evaporation rate (local update)
    const int size;
    const int max_iterations;
    const double q0;
    const double initial_pheromone;  // tau_0
    std::vector<Ant*> ants;
    Graph *graph;
    Solution *best_solution;
    std::vector<Solution*> pareto_front;

public:
    Colony(const double beta, const double phi, const double xi, const int size, const int max_iterations, const double q0, const double initial_pheromone, Graph *graph);
    ~Colony();
    void create_ants();
    double get_beta();
    double get_local_evaporation();
    double get_q0();
    void deposit_initial_pheromone();
    void run();
    void step();
    void save_best_solution();
    void global_update_pheromone_trail();
    void restart_ants();
    bool dominates(const std::vector<double> &v, const std::vector<double> &w);
    void update_pareto_front();
    std::vector<double> mean_objectives();
    void save_pareto_front();
    void print_pareto_front();


    /*
    Un vector u = {u_1, u_2, ..., u_k} domina a otro v = {v_1, v_2, ..., v_k}
    si y solo si u es parcialmente menor a v, i.e, para todo i en {1, 2, ..., k},
    u_i <= v_i y existe al menos un i en {1, 2, ..., k} tal que u_i < v_i.
    */
};
#endif //VRPTW_ACO_COLONY_H
