#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <fstream>

#include "graphic.hpp"
#include "individual.hpp"
#include "logical.hpp"
#include "population.hpp"
#include "rnghelper.hpp"
#include "roothelper.hpp"

class Simulation {
 private:
  std::shared_ptr<RNGHelper> s_RNG;
  std::shared_ptr<Population> s_population;
  std::vector<int> s_idList, s_availablePlacesIndex;
  std::vector<Place> s_availablePlaces;
  std::vector<GenerationData> s_simulationData;
  void EraseRandomIndividual();
  void SetRandomPlaces();
  void GenerateNextGeneration();
  void SaveGenerationData();
  void PrintPassiveOutput();
  void PrintAggressiveOutput();
  void PrintAdaptableOutput();
  void PrintGenerationResults();

 public:
  Simulation(std::string seed, int passiveNumber, int aggressiveNumber,
             int adaptableNumber);
  static std::shared_ptr<Simulation> GetSimulationFromInput();
  bool PopulationIsExtinct();
  void RunGenerations(int N);
  void SaveSimulationToFile();
};

#endif