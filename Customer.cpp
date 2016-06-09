//
// Created by ivanedo on 15-05-16.
//

#include "Customer.h"
#include <iostream>

Customer::Customer(const int id, const double x, const double y, const int demand, const int earliest_time, const int latest_time, const int service_time, Graph *graph) : id(id), x(x), y(y), demand(demand), earliest_time(earliest_time), latest_time(latest_time), service_time(service_time), graph(graph) { }

int Customer::get_id() {
    return id;
}

double Customer::get_x() {
    return x;
}

double Customer::get_y() {
    return y;
}

int Customer::get_demand() {
    return demand;
}

int Customer::get_earliest_time() {
    return earliest_time;
}

int Customer::get_latest_time() {
    return latest_time;
}

int Customer::get_service_time() {
    return service_time;
}

void Customer::print() {
    std::cout << "Customer Id: " << id << std::endl;
    std::cout << "X coordinate: " << x << std::endl;
    std::cout << "Y coordinate: " << y << std::endl;
    std::cout << "Demand: " << demand << std::endl;
    std::cout << "Ready time: " << earliest_time << std::endl;
    std::cout << "Due date: " << latest_time << std::endl;
    std::cout << "Service time: " << service_time << std::endl;
}