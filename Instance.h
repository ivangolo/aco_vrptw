//
// Created by ivanedo on 15-05-16.
//

#ifndef VRPTW_ACO_INSTANCE_H
#define VRPTW_ACO_INSTANCE_H
#include <deque>
#include <string>
#include "Customer.h"

class Instance {
private:
    int vehicle_number;
    int vehicle_capacity;
    std::string name;
    std::deque<Customer*> customers;


public:

    void parse(std::ifstream &fin_instance);

    ~Instance();

    int get_vehicle_number();
    int get_vehicle_capacity();
    std::string get_name();

    void print();

};


#endif //VRPTW_ACO_INSTANCE_H
