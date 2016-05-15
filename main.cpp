#include <iostream>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include "Instance.h"

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

    Instance *instance = new Instance();
    instance->parse(fin_instance);
    instance->print();
    delete instance;

    return 0;
}