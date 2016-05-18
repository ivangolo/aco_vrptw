//
// Created by ivanedo on 17-05-16.
//

#include "Edge.h"
#include <iostream>

void Edge::print() {
    std::cout << "Edge: " << "(" << edge.first << ", " << edge.second << ")" << std::endl;
    std::cout << "Distance cost: " << distance_cost << std::endl;
}