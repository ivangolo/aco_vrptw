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
    Colony *ant_colony = new Colony(1.0, 1.0, 1.0, 10, 10, 0.9, 1.0, graph);
    ant_colony->deposit_initial_pheromone();
    Customer *c1 = graph->get_customer(7);
    std::deque<int> v {1,2,5,9};
    std::deque<Edge*> edges = graph->get_edges(c1, v);
    graph->print_edges(edges);

    delete graph;
    delete ant_colony;
    return 0;
}