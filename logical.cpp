#include "logical.hpp"

namespace Simulation {
template <class T>
T GetValidatedInput(std::string inputMessage, bool inputIsOk,
                    std::string firstErrorMessage,
                    std::string secondErrorMessage) {
  T validatedInput;
  while (true) {
    std::cout << inputMessage << '\n';
    bool isCorrectInputType = (std::cin >> validatedInput);
    if (!inputIsOk) {
      std::cout << firstErrorMessage << '\n';
    } else if (!isCorrectInputType) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << secondErrorMessage << '\n';
    } else {
      break;
    }
  }
  return validatedInput;
}
void EraseRandomIndividual(std::shared_ptr<Population>& population,
                           std::shared_ptr<RNGHelper>& RNG,
                           std::vector<int>& idList) {
  int randomId = RNG->GetRandomInt(0, idList.size() - 1);
  auto id = idList.begin() + randomId;
  population->Kill_individual(idList[randomId]);
  idList.erase(id);
}
template <class T>
void InitializeVectorAndIndex(std::vector<T>& vector, std::vector<int>& indexes,
                              int nSamples) {
  if (!vector.empty() || !indexes.empty()) {
    throw std::runtime_error(
        "A vector in function 'InitializeVectorAndIndex' was not empty");
  }
  for (int i = 0; i < nSamples; i++) {
    vector.push_back(T());
    indexes.push_back(i);
  }
}
void SetRandomPlaces(std::vector<int>& idList, std::shared_ptr<RNGHelper>& RNG,
                     std::vector<Place>& places,
                     std::vector<int>& placesIndex) {
  for (auto& id : idList) {
    int randomPosition = RNG->GetRandomInt(0, placesIndex.size() - 1);
    Place& randomPlace = places[placesIndex[randomPosition]];
    randomPlace.Add_Index(id);

    if (randomPlace.isFull()) {
      placesIndex.erase(placesIndex.begin() + randomPosition);
    }
  }
}
void GenerateNextGeneration(std::shared_ptr<RNGHelper>& RNG,
                            std::shared_ptr<Population>& population,
                            std::vector<int>& idList) {
  for (std::vector<int>::size_type i = 0; i < idList.size(); i++) {
    if (!RNG->probability(population->Get_IndividualFood(idList[i]))) {
      auto it = idList.begin() + i;
      population->Kill_individual(idList[i]);
      idList.erase(it);
    } else if (RNG->probability(population->Get_IndividualFood(idList[i]) -
                                1)) {
      population->Generate_individual(idList[i]);
    }
  }
}
void PrintGenerationResults(std::shared_ptr<Population>& population,
                            GenerationData& currentGenerationData,
                            GenerationData& previousGenerationData) {}
}  // namespace Simulation