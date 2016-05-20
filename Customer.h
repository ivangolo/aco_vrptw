//
// Created by ivanedo on 15-05-16.
//

#ifndef VRPTW_ACO_CUSTOMER_H
#define VRPTW_ACO_CUSTOMER_H

class Graph;

class Customer {
private:
    const int id;
    const double x;
    const double y;
    const int demand;
    const int ready_time;  // 'Ready time' is the earliest time at which service may start at the given customer/depot.
    const int due_date;  // 'Due date' is the latest time at which service may start at the given customer/depot.
    const int service_time;
    Graph *graph;

public:
    Customer(const int id, const double x, const double y, const int demand, const int ready_time, const int due_date, const int service_time, Graph *graph);
    const int get_id() const;
    const double get_x() const;
    const double get_y() const;
    const int get_demand() const;
    const int get_ready_time() const;
    const int get_due_date() const;
    const int get_service_time() const;
    void print();
};


#endif //VRPTW_ACO_CUSTOMER_H
