#include <iostream>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "Graph.h"
#include "Colony.h"

int main(int argc, char *argv[]) {
    std::string instance_filename;
    int tmp;
    if(argc == 1) {
        std::cout << "Ningún archivo indicado" << std::endl;
    }

    while((tmp = getopt(argc, argv, "f:")) != -1) {
        if(tmp == 'f') {
            instance_filename = optarg;
        } else {
            std::cout << "Nombre de parámetro incorrecto" << std::endl;
        }
    }

    std::ifstream fin_instance(instance_filename);

    if(!fin_instance.is_open()) {
        std::cerr << "Error al intentar abrir el archivo " << instance_filename << ". " << strerror(errno) <<       std::endl;
        return 1;
    }

    Graph *graph = new Graph();
    graph->parse(fin_instance);
    fin_instance.close();
    Colony *ant_colony;
    ant_colony = new Colony(1.0, 1.0, 0.01, 7, 5, 0.9, 1.0, graph);  // alfa, beta, evaporation, ants, iterations, q0, initial pheromone, graph pointer
    ant_colony->deposit_initial_pheromone();
    ant_colony->run();
    delete ant_colony;
    delete graph;

    return 0;
}