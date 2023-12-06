#include "logical.hpp"

namespace Logistics {
template <typename T, unsigned int N>
void GetValidatedInput(T& inputTovalidate, std::string inputMessage,
                       std::array<bool, N> conditions,
                       std::array<std::string, N> errorMessages) {
  while (true) {
    std::cout << inputMessage;
    bool isCorrectInputType = (std::cin >> inputTovalidate);
    if (!isCorrectInputType) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout
          << "Could not correctly convert input type, the wanted type is: "
          << std::type_info(typeid(T)) << '\n';
    } else if (N > 0) {
      for (int i = 0; i < N; i++) {
        if (!conditions[i]) {
          std::cout << errorMessages[i] << '\n';
          break;
        }
      }
    } else {
      break;
    }
  }
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

void PrintGenerationResults(std::shared_ptr<Population>& population,
                            GenerationData& currentGenerationData,
                            GenerationData& previousGenerationData) {}
}  // namespace Logistics