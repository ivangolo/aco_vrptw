//
// Created by ivanedo on 17-05-16.
//

#ifndef VRPTW_ACO_COLONY_H
#define VRPTW_ACO_COLONY_H
#include <deque>
#include "Ant.h"

class Colony {
private:
    const double alpha;
    const double beta;
    const int ant_number;
    std::deque<Ant*> ants;

public:

    Colony(const double alpha, const double beta, const int ant_number) : alpha(alpha), beta(beta),
                                                                          ant_number(ant_number) {

        // creating the ants
        for (int i = 0; i < ant_number; ++i) {
            ants.push_back(new Ant(this));
        }
    }

    ~Colony();

    const double get_alpha() const {
        return alpha;
    }

    const double get_beta() const {
        return beta;
    }

    const int get_ant_number() const {
        return ant_number;
    }
};


#endif //VRPTW_ACO_COLONY_H
