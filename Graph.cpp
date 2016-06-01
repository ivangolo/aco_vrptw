//
// Created by ivanedo on 15-05-16.
//

#include "Graph.h"
#include <algorithm>
#include <memory>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>

Graph::~Graph() {
    std::for_each(customers.begin(), customers.end(), std::default_delete<Customer>());
    std::for_each(edges.begin(), edges.end(), std::default_delete<Edge>());
}

void Graph::parse(std::ifstream &fin_instance) {
    std::string tmp;
    fin_instance >> name;
    fin_instance >> tmp;  // VEHICLE
    fin_instance >> tmp;  // NUMBER
    fin_instance >> tmp;  // CAPACITY
    fin_instance >> vehicle_number;
    fin_instance >> vehicle_capacity;
    fin_instance >> tmp;  // CUSTOMER
    while(tmp.compare("SERVICE") != 0) {
        fin_instance >> tmp;
    }
    fin_instance >> tmp;  // TIME
    // reading customers data
    for(int id,x,y,demand,ready,due,service; fin_instance >>id>>x>>y>>demand>>ready>>due>>service;) {
        Customer *customer = new Customer(id, x, y, demand, ready, due, service, this);
        customers.push_back(customer);
    }

    // creating the edges between customers
    create_edges();
}

int Graph::get_vehicle_number() {
    return vehicle_number;
}

int Graph::get_vehicle_capacity() {
    return vehicle_capacity;
}

std::string Graph::get_name() {
    return name;
}

Customer* Graph::get_customer(int id) {
    return customers[id];
}

Edge* Graph::get_edge(int i, int j) {
    std::vector<Edge*>::iterator it =  find_if(edges.begin(), edges.end(), [i, j] (Edge *edge) {
                        int first = edge->get_components().first;
                        int second = edge->get_components().second;
                        return ((i == first && j == second) || (i == second && j == first));
                    });
    return *it;
}

long double Graph::distance_cost_between(Customer* c1, Customer* c2) {
    return std::hypot(c1->get_x() - c2->get_x(), c1->get_y() - c2->get_y());
}

void Graph::create_edges() {
    for (std::vector<Customer*>::iterator source = customers.begin(); source != customers.end(); ++source) {

        for (std::vector<Customer*>::iterator target = source; target != customers.end(); ++target) {

            if ((*source)->get_id() != (*target)->get_id()) {
                long double cost = distance_cost_between(*source, *target);
                edges.push_back(new Edge(std::make_pair((*source)->get_id(), (*target)->get_id()), cost, this));
            }

        }
    }
}

const std::vector<Customer*>& Graph::get_customers() const {
    return customers;
}

const std::vector<Edge*>& Graph::get_edges() const {
    return edges;
}

std::vector<Edge*> Graph::get_edges(Customer *c1) {
    std::vector<Edge*> selection(edges.size());

    auto it = std::copy_if (edges.begin(), edges.end(), selection.begin(), [c1] (Edge *i) {
        return (i->get_components().first == c1->get_id() || i->get_components().second == c1->get_id());
    } );

    selection.resize(std::distance(selection.begin(), it));

    return selection;
}

std::vector<Edge*> Graph::get_edges(Customer *c1, std::vector<int> customers) {
    std::vector<Edge*> selection;
    for (std::vector<int>::iterator i = customers.begin(); i != customers.end(); ++i) {
        selection.push_back(get_edge(c1->get_id(), get_customer(*i)->get_id()));
    }
    return selection;
}

std::vector<int> Graph::get_customers_ids() {
    std::vector<int> ids(customers.size() - 1);
    std::iota(ids.begin(), ids.end(), 1);
    return ids;
}

unsigned long Graph::get_customers_number() {
    return customers.size();
}

void Graph::print_customers(std::vector<Customer*> customers_vec) {
    std::cout << "::::::::::::::: Customers :::::::::::::::" << std::endl;
    for (std::vector<Customer*>::iterator customer = customers_vec.begin(); customer != customers_vec.end(); ++customer) {
        std::cout << "::::::::::::::::::::::::::::::::::::::::" << std::endl;
        (*customer)->print();

    }
}

void Graph::print_edges(std::vector<Edge*> edges_vec) {
    std::cout << "::::::::::::::: Edges :::::::::::::::" << std::endl;
    for (std::vector<Edge*>::iterator edge = edges_vec.begin(); edge != edges_vec.end(); ++edge) {
        (*edge)->print();
    }
}

void Graph::print() {
    std::cout << "Instance name: " << name << std::endl;
    std::cout << "Vehicle number: " << vehicle_number << std::endl;
    std::cout << "Vehicle capacity: " << vehicle_capacity << std::endl;
    std::cout << "Number of Customers: " << customers.size() - 1 << std::endl;
    std::cout << "Number of Edges: " << edges.size() << std::endl;

    print_customers(customers);
    print_edges(edges);
}