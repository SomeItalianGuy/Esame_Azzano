#include "simulation.hpp"

#define SEPARATION_LINES                                                       \
  "--------------------------------------------------------------------------" \
  "------------------------------------------------------------------\n"

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
  int passiveVariation =
      s_simulationData.back().passiveNumber -
      s_simulationData[s_simulationData.size() - 2].passiveNumber;
  Graphic::PrintStats(
      Graphic::ColorText("Passive", BLUE_TEXT).append(" individuals: "),
      s_simulationData.back().GetPassivePercentage(),
      s_simulationData.back().passiveNumber,
      Graphic::ColorText(
          std::to_string(passiveVariation),
          passiveVariation > 0 ? GREEN_TEXT.append("+") : RED_TEXT));
}

void Simulation::PrintAggressiveOutput() {
  int aggressiveVariation =
      s_simulationData.back().aggressiveNumber -
      s_simulationData[s_simulationData.size() - 2].aggressiveNumber;
  Graphic::PrintStats(
      Graphic::ColorText("Aggressive", YELLOW_TEXT).append(" individuals: "),
      s_simulationData.back().GetAggressivePercentage(),
      s_simulationData.back().aggressiveNumber,
      Graphic::ColorText(
          std::to_string(aggressiveVariation),
          aggressiveVariation > 0 ? GREEN_TEXT.append("+") : RED_TEXT));
}

void Simulation::PrintAdaptableOutput() {
  int adaptableVariation =
      s_simulationData.back().adaptableNumber -
      s_simulationData[s_simulationData.size() - 2].adaptableNumber;
  Graphic::PrintStats(
      Graphic::ColorText("Adaptable", MAGENTA_TEXT).append(" individuals: "),
      s_simulationData.back().GetAdaptablePercentage(),
      s_simulationData.back().adaptableNumber,
      Graphic::ColorText(
          std::to_string(adaptableVariation),
          adaptableVariation > 0 ? GREEN_TEXT.append("+") : RED_TEXT));
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
  auto seed = Logic::GetValidatedInput<std::string>(
      "Please input the seed of this simulation, it can be a number, a "
      "sentence or just a character: ",
      {{[](std::string str) {
          (void)str;  // Per evitare warning
          return true;
        },
        ""}});
  int passiveNumber = Logic::GetValidatedInput<int>(
      Graphic::AskForPopulationInput(std::string("Passive"), BLUE_TEXT),
      {{[](int numberToValidate) { return numberToValidate > 0; },
        "The passive number cannot be less than 0"}});
  int aggressiveNumber = Logic::GetValidatedInput<int>(
      Graphic::AskForPopulationInput(std::string("Aggressive"), YELLOW_TEXT),
      {{[](int numberToValidate) { return numberToValidate > 0; },
        "The aggressive number cannot be less than 0"}});
  int adaptableNumber = Logic::GetValidatedInput<int>(
      Graphic::AskForPopulationInput(std::string("Adaptable"), MAGENTA_TEXT),
      {{[](int numberToValidate) { return numberToValidate > 0; },
        "The adaptable number cannot be less than 0"}});
  return std::shared_ptr<Simulation>(
      new Simulation(seed, passiveNumber, aggressiveNumber, adaptableNumber));
}

bool Simulation::PopulationIsExtinct() { return s_population->Size() == 0; }

void Simulation::RunGenerations(int N) {
  for (int i = 0; i < N; i++) {
    s_population->Get_IdList(s_idList);
    s_population->Calculate_currentPercentage();
    while (s_population->Size() > s_population->Get_genMaxPopulation()) {
      EraseRandomIndividual();
    }
    Logic::InitializeVectorAndIndex<Place>(
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

void Simulation::SaveSimulationToFile() {
  std::string fileName = Logic::GetValidatedInput<std::string>(
      "Please input the name of the file in which you want to save this "
      "simulation: ",
      {{[](std::string str) { return str.ends_with(".txt"); },
        "The file name must end with the extension '.txt'"}});

  std::string title = Logic::GetValidatedInput<std::string>(
      "Please input the title for the simulation to be saved: ",
      {{[](std::string str) {
          (void)str;
          return true;
        },
        ""}});

  std::ofstream fstream;
  fstream.open(fileName, std::ios::app);
  fstream << "\t\t\t\t\t\t\t\t\t\t" << title << "\n\n\n";
  fstream << "Here are the parameters used for this simulation:\n";
  fstream << "Max Population: " << s_population->Get_maxPopulation()
          << "\t\tReproduction Rate: " << s_population->Get_reproductionRate() << '\n';
  fstream << SEPARATION_LINES;
  fstream << "Here is the user-generated initial population:\n\n";
  fstream << "Passive individuals:    " << std::fixed << std::setprecision(2)
          << s_simulationData[0].GetPassivePercentage() << "\t"
          << s_simulationData[0].passiveNumber << "\n\n";
  fstream << "Aggressive individuals: " << std::fixed << std::setprecision(2)
          << s_simulationData[0].GetAggressivePercentage() << "\t"
          << s_simulationData[0].aggressiveNumber << "\n\n";
  fstream << "Adaptable individuals:  " << std::fixed << std::setprecision(2)
          << s_simulationData[0].GetAdaptablePercentage() << "\t"
          << s_simulationData[0].adaptableNumber << "\n\n";
  fstream << SEPARATION_LINES << '\n';
  for (long unsigned int i = 1; i < s_simulationData.size() - 1; i++) {
    int passiveVariation = s_simulationData[i].passiveNumber - s_simulationData[i - 1].passiveNumber;
    int aggressiveVariation = s_simulationData[i].aggressiveNumber - s_simulationData[i - 1].aggressiveNumber;
    int adaptableVariation = s_simulationData[i].adaptableNumber - s_simulationData[i - 1].adaptableNumber ;
    fstream << "Here is how the  population is divided on generation number "
            << i + 1 << "\n\n";
    fstream << "Passive Individuals:    " << std::fixed << std::setprecision(2)
            << s_simulationData[i].GetPassivePercentage() << "\t" << s_simulationData[i].passiveNumber << "\t(" << passiveVariation  << ")\n\n";
    fstream << "Aggressive Individuals: " << std::fixed << std::setprecision(2)
            << s_simulationData[i].GetAggressivePercentage() << "\t" << s_simulationData[i].aggressiveNumber << "\t(" << aggressiveVariation  << ")\n\n";
    fstream << "Adaptable Individuals:  " << std::fixed << std::setprecision(2)
            << s_simulationData[i].GetAdaptablePercentage() << "\t" << s_simulationData[i].adaptableNumber << "\t(" << adaptableVariation << ")\n\n";
            fstream << SEPARATION_LINES << '\n';
  }
}