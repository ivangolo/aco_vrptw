//
// Created by ivanedo on 15-05-16.
//

#include "Customer.h"
#include <iostream>
#include <cmath>

void Customer::print() {
    std::cout << "Customer Id: " << id << std::endl;
    std::cout << "X coordinate: " << x << std::endl;
    std::cout << "Y coordinate: " << y << std::endl;
    std::cout << "Demand: " << demand << std::endl;
    std::cout << "Ready time: " << ready_time << std::endl;
    std::cout << "Due date: " << due_date << std::endl;
    std::cout << "Service time: " << service_time << std::endl;
}