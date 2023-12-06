#ifndef LOGICAL_HPP
#define LOGICAL_HPP

#include <functional>
#include <iostream>
#include <limits>
#include <typeinfo>

#include "graphic.hpp"
#include "individual.hpp"
#include "population.hpp"
#include "rnghelper.hpp"

template <typename T>
struct ValidationRule {
  std::function<bool(T)> m_condition;
  std::string m_errorMsg;
};

namespace Logistics {
template <typename T>
T GetValidatedInput(std::string inputMessage,
                    std::vector<ValidationRule<T>> rules);
template <class T>
void InitializeVectorAndIndex(std::vector<T>& vector, std::vector<int>& indexes,
                              int nSamples);

}  // namespace Logistics

#endif