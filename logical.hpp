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
void EraseRandomIndividual(std::shared_ptr<Population>& population,
                           std::shared_ptr<RNGHelper>& RNG,
                           std::vector<int>& idList);
template <class T>
void InitializeVectorAndIndex(std::vector<T>& vector, std::vector<int>& indexes,
                              int nSamples);
void SetRandomPlaces(std::vector<int>& idList, std::shared_ptr<RNGHelper>& RNG,
                     std::vector<Place>& places, std::vector<int>& placesIndex);
void GenerateNextGeneration(std::shared_ptr<RNGHelper>& RNG,
                            std::shared_ptr<Population>& population,
                            std::vector<int>& idList);
void PrintGenerationResults(std::shared_ptr<Population>& population,
                            GenerationData& currentGenerationData,
                            GenerationData& previousGenerationData);
}  // namespace Simulation

#endif