//
// Created by ivanedo on 17-05-16.
//

#ifndef VRPTW_ACO_ANT_H
#define VRPTW_ACO_ANT_H

class Colony;

class Ant {
private:
    Colony *colony;
    // solution structure

public:
    Ant(Colony *colony) : colony(colony) { }
};


#endif //VRPTW_ACO_ANT_H
