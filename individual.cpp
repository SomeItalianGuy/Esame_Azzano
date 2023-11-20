#include "individual.hpp"

#include <iostream>

Individual::Individual(Behavior new_behavior)
    : behavior_(new_behavior), food_(DEFAULT_FOOD) {}

Individual::Individual() : behavior_(Behavior::Passive) {}

const double Individual::GetFood() const { return food_; }

const Behavior Individual::GetBehavior() const { return behavior_; }

void Individual::SetFood(double new_food) { food_ = new_food; }