//
// Created by ivanedo on 17-05-16.
//

#include "Colony.h"
#include <algorithm>
#include <memory>

Colony::~Colony() {
    std::for_each(ants.begin(), ants.end(), std::default_delete<Ant>());
}