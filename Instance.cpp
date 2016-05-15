//
// Created by ivanedo on 15-05-16.
//

#include "Instance.h"
#include <algorithm>
#include <memory>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>

Instance::~Instance() {
    std::for_each(customers.begin(), customers.end(), std::default_delete<Customer>());
}

void Instance::parse(std::ifstream &fin_instance) {
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
        Customer *customer = new Customer(id, x, y, demand, ready, due, service);
        customers.push_back(customer);
    }

    fin_instance.close();
}

int Instance::get_vehicle_number() {
    return vehicle_number;
}

int Instance::get_vehicle_capacity() {
    return vehicle_capacity;
}

std::string Instance::get_name() {
    return name;
}

void Instance::print() {
    std::cout << "Instance name: " << name << std::endl;
    std::cout << "Vehicle number: " << vehicle_number << std::endl;
    std::cout << "Vehicle capacity: " << vehicle_capacity << std::endl;
    std::cout << "::::::::::::::: Customers :::::::::::::::" << std::endl;
    for (std::deque<Customer*>::iterator customer_iter = customers.begin(); customer_iter != customers.end(); ++customer_iter) {
        std::cout << "::::::::::::::::::::::::::::::::::::::::" << std::endl;
        (*customer_iter)->print();

    }
}