//
// Created by ivanedo on 15-05-16.
//

#ifndef VRPTW_ACO_GRAPH_H
#define VRPTW_ACO_GRAPH_H
#include <deque>
#include <string>
#include "Customer.h"
#include "Edge.h"

class Graph {
private:
    int vehicle_number;
    int vehicle_capacity;
    std::string name;
    std::deque<Customer*> customers;
    std::deque<Edge*> edges;

public:

    void parse(std::ifstream &fin_instance);
    ~Graph();
    int get_vehicle_number();
    int get_vehicle_capacity();
    std::string get_name();
    Customer* get_customer(int id);
    long double distance_cost_between(Customer* c1, Customer* c2);
    void create_edges();
    void print();
    void print_customers();
    void print_edges();

};


#endif //VRPTW_ACO_GRAPH_H
