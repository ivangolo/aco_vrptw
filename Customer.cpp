//
// Created by ivanedo on 15-05-16.
//

#include "Customer.h"
#include <iostream>

Customer::Customer(const int id, const double x, const double y, const int demand, const int ready_time, const int due_date, const int service_time, Graph *graph) : id(id), x(x), y(y), demand(demand), ready_time(ready_time), due_date(due_date), service_time(service_time), graph(graph) { }

const int Customer::get_id() const {
    return id;
}

const double Customer::get_x() const {
    return x;
}

const double Customer::get_y() const {
    return y;
}

const int Customer::get_demand() const {
    return demand;
}

const int Customer::get_ready_time() const {
    return ready_time;
}

const int Customer::get_due_date() const {
    return due_date;
}

const int Customer::get_service_time() const {
    return service_time;
}

void Customer::print() {
    std::cout << "Customer Id: " << id << std::endl;
    std::cout << "X coordinate: " << x << std::endl;
    std::cout << "Y coordinate: " << y << std::endl;
    std::cout << "Demand: " << demand << std::endl;
    std::cout << "Ready time: " << ready_time << std::endl;
    std::cout << "Due date: " << due_date << std::endl;
    std::cout << "Service time: " << service_time << std::endl;
}