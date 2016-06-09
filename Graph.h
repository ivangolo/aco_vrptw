//
// Created by ivanedo on 15-05-16.
//

#ifndef VRPTW_ACO_GRAPH_H
#define VRPTW_ACO_GRAPH_H
#include <vector>
#include <string>
#include "Customer.h"
#include "Edge.h"

class Graph {
private:
    int vehicle_number;
    int vehicle_capacity;
    std::string name;
    std::vector<Customer*> customers;
    std::vector<Edge*> edges;

public:

    void parse(std::ifstream &fin_instance);
    ~Graph();
    int get_vehicle_number();
    int get_vehicle_capacity();
    unsigned long get_customers_number();
    std::string get_name();
    Customer* get_customer(int id);
    Edge* get_edge(int start, int end);
    long double distance_between(Customer* c1, Customer* c2);
    void create_edges();
    bool check_edge(Customer *start, Customer *end);
    void print();
    void print_customers(std::vector<Customer*> customers_vec);
    void print_edges(std::vector<Edge*> edges_vec);
    const std::vector<Customer*>& get_customers() const ;
    const std::vector<Edge*>& get_edges() const;
    std::vector<Edge*> get_edges(Customer *c1);
    std::vector<Edge*> get_edges(Customer *c1, std::vector<int> customers);
    std::vector<int> get_customers_ids();
};


#endif //VRPTW_ACO_GRAPH_H
