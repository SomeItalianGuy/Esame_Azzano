#include "logical.hpp"

#include "population.hpp"

template <typename T>
T Logic::GetValidatedInput(std::string inputMessage,
                           std::vector<ValidationRule<T>> rules) {
  T validatedInput;
  while (true) {
    std::cout << inputMessage;
    bool isCorrectInputType = (bool)(std::cin >> validatedInput);
    if (!isCorrectInputType) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout
          << "Could not correctly convert input type, the wanted type is: "
          << typeid(T).name() << "\n \n";
    } else if (rules.size() > 0) {
      bool isValid = true;
      for (auto rule : rules) {
        isValid = rule.m_condition(validatedInput);
        if (!isValid) {
          std::cout << rule.m_errorMsg << "\n \n";
          break;
        }
      }
      if (isValid) {
        std::cout << '\n';
        return validatedInput;
      }
    }
  }
}

template <typename T>
void Logic::InitializeVectorAndIndex(std::vector<T>& vector,
                                     std::vector<int>& indexes, int nSamples) {
  if (!vector.empty() || !indexes.empty()) {
    throw std::runtime_error(
        "A vector in function 'InitializeVectorAndIndex' was not empty");
  }
  for (int i = 0; i < nSamples; i++) {
    vector.push_back(T());
    indexes.push_back(i);
  }
}

// Istanzio GetValidatedInput
template int Logic::GetValidatedInput<int>(
    std::string inputMessage, std::vector<ValidationRule<int>> rules);
template double Logic::GetValidatedInput<double>(
    std::string inputMessage, std::vector<ValidationRule<double>> rules);
template float Logic::GetValidatedInput<float>(
    std::string inputMessage, std::vector<ValidationRule<float>> rules);
template std::string Logic::GetValidatedInput<std::string>(
    std::string inputMessage, std::vector<ValidationRule<std::string>> rules);
template char Logic::GetValidatedInput<char>(
    std::string inputMessage, std::vector<ValidationRule<char>> rules);

// Istanzio InitializeVectorAndIndex
template void Logic::InitializeVectorAndIndex<int>(std::vector<int>& vector,
                                                   std::vector<int>& indexes,
                                                   int nSamples);
template void Logic::InitializeVectorAndIndex<double>(
    std::vector<double>& vector, std::vector<int>& indexes, int nSamples);
template void Logic::InitializeVectorAndIndex<float>(std::vector<float>& vector,
                                                     std::vector<int>& indexes,
                                                     int nSamples);
template void Logic::InitializeVectorAndIndex<std::string>(
    std::vector<std::string>& vector, std::vector<int>& indexes, int nSamples);
template void Logic::InitializeVectorAndIndex<char>(std::vector<char>& vector,
                                                    std::vector<int>& indexes,
                                                    int nSamples);
// Istanzio appositamente per questa simulazione
template void Logic::InitializeVectorAndIndex<Place>(std::vector<Place>& vector,
                                                     std::vector<int>& indexes,
                                                     int nSamples);