//
// Created by ivanedo on 18-05-16.
//

#include "Solution.h"
#include <algorithm>

Solution::Solution(Graph *graph) : graph(graph) { }

void Solution::add_customer(int customer_id) {
    customers.push_back(customer_id);
}

bool Solution::has_customer(int customer_id) {
    std::deque<int>::iterator position = std::find(customers.begin(), customers.end(), customer_id);
    return (position != customers.end()); //true if process is found, false in the other case
}

Customer* Solution::last_visited_vertex() {
    graph->get_customer(customers.back());
}