#include "simulation.hpp"

#include "graphic.hpp"
#include "individual.hpp"
#include "logical.hpp"
#include "population.hpp"
#include "rnghelper.hpp"

void Simulation::EraseRandomIndividual() {
  int randomId = s_RNG->GetRandomInt(0, s_idList.size() - 1);
  auto id = s_idList.begin() + randomId;
  s_population->Kill_individual(s_idList[randomId]);
  s_idList.erase(id);
}

void Simulation::SetRandomPlaces() {
  for (auto& id : s_idList) {
    int randomPosition =
        s_RNG->GetRandomInt(0, s_availablePlacesIndex.size() - 1);
    Place& randomPlace =
        s_availablePlaces[s_availablePlacesIndex[randomPosition]];
    randomPlace.Add_Index(id);

    if (randomPlace.isFull()) {
      s_availablePlacesIndex.erase(s_availablePlacesIndex.begin() +
                                   randomPosition);
    }
  }
}

void Simulation::GenerateNextGeneration() {
  for (std::vector<int>::size_type i = 0; i < s_idList.size(); i++) {
    if (!s_RNG->probability(s_population->Get_IndividualFood(s_idList[i]))) {
      auto it = s_idList.begin() + i;
      s_population->Kill_individual(s_idList[i]);
      s_idList.erase(it);
    } else if (s_RNG->probability(
                   s_population->Get_IndividualFood(s_idList[i]) - 1)) {
      s_population->Generate_individual(1, s_idList[i]);
    }
  }
}

void Simulation::SaveGenerationData() {
  s_simulationData.push_back(s_population->WriteTo_GenerationData());
}

void Simulation::PrintPassiveOutput() {
  Graphic::PrintStats(
      Graphic::ColorText("Passive", BLUE_TEXT).append(" individuals: "),
      s_simulationData.back().GetPassivePercentage(),
      s_simulationData.back().passiveNumber,
      Graphic::ColoredConditionString<2>(
          std::to_string(
              s_simulationData.back().passiveNumber -
              s_simulationData[s_simulationData.size() - 2].passiveNumber),
          {(s_simulationData.back().passiveNumber -
            s_simulationData[s_simulationData.size() - 2].passiveNumber) > 0,
           (s_simulationData.back().passiveNumber -
            s_simulationData[s_simulationData.size() - 2].passiveNumber) < 0},
          {GREEN_TEXT.append("+"), RED_TEXT}));
}

void Simulation::PrintAggressiveOutput() {
  Graphic::PrintStats(
      Graphic::ColorText("Aggressive", YELLOW_TEXT).append(" individuals: "),
      s_simulationData.back().GetAggressivePercentage(),
      s_simulationData.back().aggressiveNumber,
      Graphic::ColoredConditionString<2>(
          std::to_string(
              s_simulationData.back().aggressiveNumber -
              s_simulationData[s_simulationData.size() - 2].aggressiveNumber),
          {(s_simulationData.back().aggressiveNumber -
            s_simulationData[s_simulationData.size() - 2].aggressiveNumber) > 0,
           (s_simulationData.back().aggressiveNumber -
            s_simulationData[s_simulationData.size() - 2].aggressiveNumber) <
               0},
          {GREEN_TEXT.append("+"), RED_TEXT}));
}

void Simulation::PrintAdaptableOutput() {
  Graphic::PrintStats(
      Graphic::ColorText("Adaptable", MAGENTA_TEXT).append(" individuals: "),
      s_simulationData.back().GetPassivePercentage(),
      s_simulationData.back().adaptableNumber,
      Graphic::ColoredConditionString<2>(
          std::to_string(
              s_simulationData.back().adaptableNumber -
              s_simulationData[s_simulationData.size() - 2].adaptableNumber),
          {(s_simulationData.back().adaptableNumber -
            s_simulationData[s_simulationData.size() - 2].adaptableNumber) > 0,
           (s_simulationData.back().adaptableNumber -
            s_simulationData[s_simulationData.size() - 2].adaptableNumber) < 0},
          {GREEN_TEXT.append("+"), RED_TEXT}));
}

void Simulation::PrintGenerationResults() {
  Graphic::PrintSeparationLines();
  std::cout << "After " << s_simulationData.size()
            << " generations, here is how the population is split up:" << '\n';
  std::cout << '\n';
  PrintPassiveOutput();
  std::cout << '\n';
  PrintAggressiveOutput();
  std::cout << '\n';
  PrintAdaptableOutput();
  std::cout << '\n';
  Graphic::PrintSeparationLines();
}

Simulation::Simulation(std::string seed, int passiveNumber,
                       int aggressiveNumber, int adaptableNumber)
    : s_RNG(RNGHelper::instance(seed)),
      s_population(Population::Population_instance(
          s_RNG->GetRandomDouble(3.5, 4),
          passiveNumber + aggressiveNumber + adaptableNumber,
          s_RNG->GetRandomDouble(0.01, 0.99))) {
  s_population->Generate_individual(passiveNumber, Behavior::Passive);
  s_population->Generate_individual(aggressiveNumber, Behavior::Aggressive);
  s_population->Generate_individual(adaptableNumber, Behavior::Adaptable);
  SaveGenerationData();
}

std::shared_ptr<Simulation> Simulation::GetSimulationFromInput() {
  std::string seed;
  Logistics::GetValidatedInput<std::string, 0>(
      seed,
      std::string(
          "Please input the seed of this simulation, it can be a number, a "
          "sentence or just a character: "),
      {}, {});
  int passiveNumber, aggressiveNumber, adaptableNumber;
  Logistics::GetValidatedInput<int, 1>(
      passiveNumber,
      Graphic::AskForPopulationInput(std::string("Passive"), BLUE_TEXT),
      {passiveNumber >= 0},
      {std::string("The input number must be more than 0")});
  Logistics::GetValidatedInput<int, 1>(
      aggressiveNumber,
      Graphic::AskForPopulationInput(std::string("Aggressive"), YELLOW_TEXT),
      {aggressiveNumber >= 0},
      {std::string("The input number must be more than 0")});
  Logistics::GetValidatedInput<int, 1>(
      adaptableNumber,
      Graphic::AskForPopulationInput(std::string("Adaptable"), MAGENTA_TEXT),
      {adaptableNumber >= 0},
      {std::string("The input number must be more than 0")});
  std::shared_ptr<Simulation> simulation(
      new Simulation(seed, passiveNumber, aggressiveNumber, adaptableNumber));
  return simulation;
}

bool Simulation::PopulationIsExtinct() {
  return s_population->Size() == 0 ? true : false;
}

void Simulation::RunGenerations(int N) {
  for (int i = 0; i < N; i++) {
    s_population->Get_IdList(s_idList);
    s_population->Calculate_currentPercentage();
    while (s_population->Size() > s_population->Get_genMaxPopulation()) {
      EraseRandomIndividual();
    }
    Logistics::InitializeVectorAndIndex<Place>(
        s_availablePlaces, s_availablePlacesIndex,
        round(s_population->Get_genMaxPopulation() / 2.));
    SetRandomPlaces();
    for (auto& place : s_availablePlaces) {
      s_population->Interaction(place);
    }
    GenerateNextGeneration();
    SaveGenerationData();
    PrintGenerationResults();
    s_availablePlaces.clear();
    s_availablePlacesIndex.clear();
    s_idList.clear();
    if (PopulationIsExtinct()) {
      std::cout << "Population was led to extinction" << '\n';
      break;
    }
  }
}