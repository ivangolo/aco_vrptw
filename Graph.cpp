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
    fin_instance >> vehicle_capacity;
    fin_instance >> vehicle_number;
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

long double Graph::distance_cost_between(Customer* c1, Customer* c2) {
    return std::hypot(c1->get_x() - c2->get_x(), c1->get_y() - c2->get_y());
}

void Graph::create_edges() {
    for (std::deque<Customer*>::iterator source = customers.begin(); source != customers.end(); ++source) {

        for (std::deque<Customer*>::iterator target = source; target != customers.end(); ++target) {

            if ((*source)->get_id() != (*target)->get_id()) {
                double long cost = distance_cost_between(*source, *target);
                edges.push_back(new Edge(std::make_pair((*source)->get_id(), (*target)->get_id()), cost, this));
            }

        }
    }
}

void Graph::print_customers() {
    std::cout << "::::::::::::::: Customers :::::::::::::::" << std::endl;
    for (std::deque<Customer*>::iterator customer = customers.begin(); customer != customers.end(); ++customer) {
        std::cout << "::::::::::::::::::::::::::::::::::::::::" << std::endl;
        (*customer)->print();

    }
}

void Graph::print_edges() {
    std::cout << "::::::::::::::: Edges :::::::::::::::" << std::endl;
    for (std::deque<Edge*>::iterator edge = edges.begin(); edge != edges.end(); ++edge) {
        (*edge)->print();
    }
}

void Graph::print() {
    std::cout << "Instance name: " << name << std::endl;
    std::cout << "Vehicle number: " << vehicle_number << std::endl;
    std::cout << "Vehicle capacity: " << vehicle_capacity << std::endl;
    std::cout << "Number of Customers: " << customers.size() - 1 << std::endl;
    std::cout << "Number of Edges: " << edges.size() << std::endl;

    print_customers();
    print_edges();
}