#include <iostream>
#include <getopt.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include "Graph.h"
#include "Colony.h"

void print_usage();

static struct option long_options[] = {
        {"file", required_argument,  0,  'f' },
        {"beta", required_argument,  0,  'b' },
        {"rho", required_argument, 0, 'r' },
        {"xi", required_argument, 0, 'x' },
        {"ants", required_argument, 0, 'k'},
        {"iterations", required_argument, 0, 'i'},
        {"q0", required_argument, 0, 'q'},
        {"initial-pheromone", required_argument, 0, 't'},
        {"objectives", required_argument, 0, 'o'},
        {0, 0, 0, 0}
};

int main(int argc, char *argv[]) {
    std::string instance_filename, objectives_str;
    double beta, rho, xi, initial_pheromone, q0;
    int colony_size, max_iterations, opt = 0, long_index = 0;
    while((opt = getopt_long(argc, argv, "f:b:r:x:k:i:q:t:o:", long_options, &long_index)) != -1) {
        std::istringstream iss_tm(optarg);
        switch (opt) {
            case 'f': instance_filename = optarg;
                break;
            case 'b': iss_tm >> beta;
                break;
            case 'r': iss_tm >> rho;
                break;
            case 'x': iss_tm >> xi;
                break;
            case 'k': iss_tm >> colony_size;
                break;
            case 'i': iss_tm >> max_iterations;
                break;
            case 'q': iss_tm >> q0;
                break;
            case 't': iss_tm >> initial_pheromone;
                break;
            case 'o': objectives_str = optarg;
                break;
            default: print_usage();
                return EXIT_FAILURE;
       }
    }

    std::ifstream fin_instance(instance_filename);
    if(!fin_instance.is_open()) {
        std::cerr << "Error al intentar abrir el archivo " << instance_filename << ". " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    if(rho < 0 || rho > 1) {
        std::cerr << "El parámetro phi debe estar en el intervalo [0,1]." << std::endl;
        return EXIT_FAILURE;
    }

    if(xi <= 0 || xi >= 1) {
        std::cerr << "El parámetro xi debe estar en el intervalo (0,1)." << std::endl;
        return EXIT_FAILURE;
    }

    if(q0 <= 0 || q0 >= 1) {
        std::cerr << "El parámetro q0 debe estar en el intervalo (0,1)." << std::endl;
        return EXIT_FAILURE;
    }

    if (objectives_str.empty()) {
        std::cerr << "Ningún objetivo ha sido indicado." << std::endl;
        return EXIT_FAILURE;
    }

    if (objectives_str.length() > 3) {
        std::cerr << "Demasiados objetivos." << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<char> objectives_v(objectives_str.begin(), objectives_str.end());
    std::vector<char> objectives = {'d', 'v', 'b'};

    for (auto o : objectives_v) {
        if (std::find(objectives.begin(), objectives.end(), o) == objectives.end()) {
            std::cerr << "Objetivo " << o << " desconocido" << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::sort(objectives_v.begin(), objectives_v.end());
    auto last = std::unique(objectives_v.begin(), objectives_v.end());
    objectives_v.erase(last, objectives_v.end());

    Graph *graph = new Graph();
    graph->parse(fin_instance);
    graph->set_objectives(objectives_v);
    fin_instance.close();
    Colony *ant_colony;
    ant_colony = new Colony(beta, rho, xi, colony_size, max_iterations, q0, initial_pheromone, graph);  // beta, evaporation, local evaporation, ants, iterations, q0, initial pheromone, objectives, graph pointer
    ant_colony->run();
    delete ant_colony;
    delete graph;

}

void print_usage() {
    std::cout << "Usage: aco_vrptw []" << std::endl;
}
