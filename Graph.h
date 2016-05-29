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
    Edge* get_edge(int i, int j);
    long double distance_cost_between(Customer* c1, Customer* c2);
    void create_edges();
    void print();
    void print_customers(std::deque<Customer*> customers_vec);
    void print_edges(std::deque<Edge*> edges_vec);
    std::deque<Customer*>& get_customers();
    std::deque<Edge*>& get_edges();
    std::deque<Edge*> get_edges(Customer *c1);
    std::deque<Edge*> get_edges(Customer *c1, std::deque<int> customers);
    std::deque<int> get_customers_ids();
};


#endif //VRPTW_ACO_GRAPH_H
