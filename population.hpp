#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

#include "individual.hpp"

#define DEFAULT_PLACE_INDEX -1

struct Place {
  int firstIndex_, secondIndex_;
  Place();
  void Add_Index(int newIndex);
  bool isFull();
  bool isHalfFull();
  // bool isEmpty();
};

struct GenerationData {
  int passiveNumber, aggressiveNumber, adaptableNumber;
  GenerationData();
};

class Population {
 private:
  //  Singleton
  static std::shared_ptr<Population> population_ptr;
  Population(double reproductionRate, int startingPopulation,
             double startingPercentage)
      : reproductionRate_(reproductionRate),
        maxPopulation_(round(startingPopulation / startingPercentage) * 2),
        currentPercentage_(startingPercentage) {}
  // Variables
  double reproductionRate_;
  const int maxPopulation_;
  double currentPercentage_;
  std::unordered_map<int, Individual> group_;
  static int NextId;

 public:
  // Singleton
  static std::shared_ptr<Population> Population_instance(
      double reproductionRate, int startingPopulation,
      double startingPercentage);
  // Methods
  // // Getters
  void Get_Id_list(std::vector<int>& namesList) const;
  int Get_maxPopulation() const;
  int Get_genMaxPopulation() const;
  double Get_reproductionRate() const;
  // // Miscellaneous
  void Generate_individual(Behavior behavior);
  void Generate_individual(int parent_Id);
  void Kill_individual(int Individual_Id);
  void Calculate_currentPercentage();
  void Interaction(Place& place);
  GenerationData WriteTo_GenerationData();
  void SaveSimulationToFile(std::vector<GenerationData> const& data,
                            std::ofstream& file);
  int Size();
};

#endif