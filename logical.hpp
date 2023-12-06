#ifndef LOGICAL_HPP
#define LOGICAL_HPP

#include <array>
#include <iostream>
#include <limits>
#include <typeinfo>

#include "graphic.hpp"
#include "individual.hpp"
#include "population.hpp"
#include "rnghelper.hpp"

namespace Logistics {
template <typename T, int N>
void GetValidatedInput(T& inputTovalidate, std::string inputMessage,
                       std::array<bool, N> conditions,
                       std::array<std::string, N> errorMessages);
template <class T>
void InitializeVectorAndIndex(std::vector<T>& vector, std::vector<int>& indexes,
                              int nSamples);

void PrintGenerationResults(std::shared_ptr<Population>& population,
                            GenerationData& currentGenerationData,
                            GenerationData& previousGenerationData);
}  // namespace Logistics

#endif