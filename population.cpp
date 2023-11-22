#include "population.hpp"

#include <iostream>

// Place Methods

Place::Place()
    : firstIndex_(DEFAULT_PLACE_INDEX), secondIndex_(DEFAULT_PLACE_INDEX) {}

void Place::Add_Index(int newIndex) {
  if (firstIndex_ == DEFAULT_PLACE_INDEX) {
    firstIndex_ = newIndex;
  } else if (secondIndex_ == DEFAULT_PLACE_INDEX) {
    secondIndex_ = newIndex;
  } else {
    std::cout << "Too many indexes in one place\n";
  }
}

bool Place::isFull() {
  if (firstIndex_ != DEFAULT_PLACE_INDEX &&
      secondIndex_ != DEFAULT_PLACE_INDEX) {
    return true;
  }
  return false;
}

bool Place::isHalfFull() {
  if (firstIndex_ != DEFAULT_PLACE_INDEX &&
      secondIndex_ == DEFAULT_PLACE_INDEX) {
    return true;
  }
  return false;
}

// bool Place::isEmpty() {
//   if (firstIndex_ == DEFAULT_PLACE_INDEX &&
//       secondIndex_ == DEFAULT_PLACE_INDEX) {
//     return true;
//   }
//   return false;
// }

// GenerationData

GenerationData::GenerationData()
    : passiveNumber(0), aggressiveNumber(0), adaptableNumber(0) {}

// Singleton Class

std::shared_ptr<Population> Population::population_ptr;

std::shared_ptr<Population> Population::Population_instance(
    double reproductionRate, int startingPopulation,
    double startingPercentage) {
  if (!population_ptr) {
    population_ptr = std::shared_ptr<Population>(new Population(
        reproductionRate, startingPopulation, startingPercentage));
  }
  return population_ptr;
}

// Class methods

int Population::NextId = 0;

// Getters

void Population::Get_IdList(std::vector<int>& namesList) const {
  for (auto& entity : group_) {
    namesList.push_back(entity.first);
  }
}

int Population::Get_maxPopulation() const { return maxPopulation_; }

int Population::Get_genMaxPopulation() const {
  return round(maxPopulation_ * currentPercentage_);
}

double Population::Get_reproductionRate() const { return reproductionRate_; }

double Population::Get_IndividualFood(int Individual_id) {
  return group_[Individual_id].GetFood();
}

// Miscellaneous

void Population::Generate_individual(Behavior behavior) {
  // group_[NextId] = Individual(behavior);
  group_.insert(std::make_pair(NextId, Individual(behavior)));
  ++NextId;
  if (NextId == INT32_MAX) {
    throw std::range_error("NextId has reached the limit for integer values");
  }
}

void Population::Generate_individual(int parent_Id) {
  Generate_individual(group_[parent_Id].GetBehavior());
}

void Population::Kill_individual(int Individual_Id) {
  group_.erase(Individual_Id);
}

void Population::Calculate_currentPercentage() {
  currentPercentage_ =
      reproductionRate_ * currentPercentage_ * (1 - currentPercentage_);

  if (currentPercentage_ >= 1) {
    throw std::overflow_error(
        "Current percentage is larger than 1, simulation connot continue\n");
  }
}

void Population::Interaction(Place& place) {
  if (place.isFull()) {
    if (group_[place.firstIndex_].GetBehavior() == Behavior::Passive) {
      if (group_[place.secondIndex_].GetBehavior() == Behavior::Passive) {
        group_[place.firstIndex_].SetFood(1.);
        group_[place.secondIndex_].SetFood(1.);
        return;
      } else if (group_[place.secondIndex_].GetBehavior() ==
                 Behavior::Aggressive) {
        group_[place.firstIndex_].SetFood(0.5);
        group_[place.secondIndex_].SetFood(1.5);
        return;
      } else if (group_[place.secondIndex_].GetBehavior() ==
                 Behavior::Adaptable) {
        group_[place.firstIndex_].SetFood(1.5);
        group_[place.secondIndex_].SetFood(0.5);
        return;
      }
    } else if (group_[place.firstIndex_].GetBehavior() ==
               Behavior::Aggressive) {
      if (group_[place.secondIndex_].GetBehavior() == Behavior::Passive) {
        group_[place.firstIndex_].SetFood(1.5);
        group_[place.secondIndex_].SetFood(0.5);
        return;
      } else if (group_[place.secondIndex_].GetBehavior() ==
                 Behavior::Aggressive) {
        group_[place.firstIndex_].SetFood(0.);
        group_[place.secondIndex_].SetFood(0.);
        return;
      } else if (group_[place.secondIndex_].GetBehavior() ==
                 Behavior::Adaptable) {
        group_[place.firstIndex_].SetFood(0.5);
        group_[place.secondIndex_].SetFood(1.5);
        return;
      }
    } else if (group_[place.firstIndex_].GetBehavior() == Behavior::Adaptable) {
      if (group_[place.secondIndex_].GetBehavior() == Behavior::Passive) {
        group_[place.firstIndex_].SetFood(0.5);
        group_[place.secondIndex_].SetFood(1.5);
        return;
      } else if (group_[place.secondIndex_].GetBehavior() ==
                 Behavior::Aggressive) {
        group_[place.firstIndex_].SetFood(1.5);
        group_[place.secondIndex_].SetFood(0.5);
        return;
      } else if (group_[place.secondIndex_].GetBehavior() ==
                 Behavior::Adaptable) {
        group_[place.firstIndex_].SetFood(1.);
        group_[place.secondIndex_].SetFood(1.);
        return;
      }
    } else {
      std::cout << "Unknown type of behavior\n";
    }
  } else if (place.isHalfFull()) {
    group_[place.firstIndex_].SetFood(2);
  } else {
  }
  // Per il caso di default (luogo vuoto) non deve succedere nulla
}

GenerationData Population::WriteTo_GenerationData() {
  GenerationData generationData;
  for (auto const& entity : group_) {
    if (entity.second.GetBehavior() == Behavior::Passive) {
      generationData.passiveNumber++;
    } else if (entity.second.GetBehavior() == Behavior::Aggressive) {
      generationData.aggressiveNumber++;
    } else {
      generationData.adaptableNumber++;
    }
  }
  return generationData;
}

void Population::SaveSimulationToFile(std::vector<GenerationData> const& data,
                                      std::ofstream& file) {
  if (file.is_open()) {
    file << "Starting population:\n";
    file << '\n';
    file << "Passive individuals number: " << data[0].passiveNumber << '\n';
    file << '\n';
    file << "Aggressive individuals number: " << data[0].aggressiveNumber
         << '\n';
    file << '\n';
    file << "Adaptable individuals number: " << data[0].adaptableNumber << '\n';
    file << '\n';
    file << "Total population: "
         << data[0].passiveNumber + data[0].aggressiveNumber +
                data[0].adaptableNumber
         << '\n';
    file << '\n';
    for (unsigned long int i = 1; i < data.size(); i++) {
      file << "Generation number " << i << '\n';
      file << '\n';
      file << '\n';
      file << "Passive individuals number: " << data[i].passiveNumber << " ("
           << data[i - 1].passiveNumber - data[i].passiveNumber << ")\n";
      file << '\n';
      file << "Aggressive individuals number: " << data[i].aggressiveNumber
           << " (" << data[i - 1].aggressiveNumber - data[i].aggressiveNumber
           << ")\n";
      file << '\n';
      file << "Adaptable individuals number: " << data[i].adaptableNumber
           << " (" << data[i - 1].adaptableNumber - data[i].adaptableNumber
           << ")\n";
      file << '\n';
      file << "Total population: "
           << data[i].passiveNumber + data[i].aggressiveNumber +
                  data[i].adaptableNumber
           << " ("
           << data[i - 1].passiveNumber + data[i - 1].aggressiveNumber +
                  data[i - 1].adaptableNumber - data[i].passiveNumber +
                  data[i].aggressiveNumber + data[i].adaptableNumber
           << ")\n";
      file << '\n';
    }
  } else {
    std::cout << "Couldn't open file" << '\n';
  }
}

int Population::Size() { return group_.size(); }