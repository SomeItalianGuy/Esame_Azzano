#ifndef LOGICAL_HPP
#define LOGICAL_HPP

#include <iostream>
#include <limits>

#include "graphic.hpp"
#include "individual.hpp"
#include "population.hpp"
#include "rnghelper.hpp"

namespace Simulation {
template <class T>
T GetValidatedInput(std::string inputMessage, bool inputIsOk,
                    std::string firstErrorMessage,
                    std::string secondErrorMessage);
}  // namespace Simulation

#endif