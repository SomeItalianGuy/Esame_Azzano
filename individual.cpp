#include "individual.hpp"

#include <iostream>

Individual::Individual(Behavior new_behavior)
    : food_(DEFAULT_FOOD), behavior_(new_behavior) {}

Individual::Individual() : behavior_(Behavior::Passive) {}

double Individual::GetFood() const { return food_; }

Behavior Individual::GetBehavior() const { return behavior_; }

void Individual::SetFood(double new_food) { food_ = new_food; }