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
    const int ready_time;
    const int due_date;
    const int service_time;
    Graph *graph;

public:

    Customer(const int id, const double x, const double y, const int demand, const int ready_time, const int due_date, const int service_time, Graph *graph) : id(id), x(x), y(y), demand(demand), ready_time(ready_time), due_date(due_date), service_time(service_time), graph(graph) { }

    const int get_id() const {
        return id;
    }

    const double get_x() const {
        return x;
    }

    const double get_y() const {
        return y;
    }

    const int get_demand() const {
        return demand;
    }

    const int get_ready_time() const {
        return ready_time;
    }

    const int get_due_date() const {
        return due_date;
    }

    const int get_service_time() const {
        return service_time;
    }

    void print();
};


#endif //VRPTW_ACO_CUSTOMER_H
