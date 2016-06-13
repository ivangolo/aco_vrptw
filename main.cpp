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
        {"phi", required_argument, 0, 'p' },
        {"xi", required_argument, 0, 'x' },
        {"ants", required_argument, 0, 'k'},
        {"iterations", required_argument, 0, 'i'},
        {"q0", required_argument, 0, 'q'},
        {"initial-pheromone", required_argument, 0, 't'},
        {0, 0, 0, 0}
};

int main(int argc, char *argv[]) {
    std::string instance_filename;
    double beta, phi, xi, initial_pheromone, q0;
    int colony_size, max_iterations, opt = 0, long_index = 0;
    while((opt = getopt_long(argc, argv, "f:b:p:x:k:i:q:t:", long_options, &long_index)) != -1) {
        std::istringstream iss_tm(optarg);
        switch (opt) {
            case 'f': instance_filename = optarg;
                break;
            case 'b': iss_tm >> beta;
                break;
            case 'p': iss_tm >> phi;
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
            default: print_usage();
                return EXIT_FAILURE;
       }
    }

    std::ifstream fin_instance(instance_filename);
    if(!fin_instance.is_open()) {
        std::cerr << "Error al intentar abrir el archivo " << instance_filename << ". " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    if(phi < 0 || phi > 1) {
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

    Graph *graph = new Graph();
    graph->parse(fin_instance);
    fin_instance.close();
    Colony *ant_colony;
    ant_colony = new Colony(beta, phi, xi, colony_size, max_iterations, q0, initial_pheromone, graph);  // beta, evaporation, local evaporation, ants, iterations, q0, initial pheromone, graph pointer
    ant_colony->run();
    delete ant_colony;
    delete graph;


}

void print_usage() {
    std::cout << "Usage: aco_vrptw []" << std::endl;
}
