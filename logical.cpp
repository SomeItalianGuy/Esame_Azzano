#include "logical.hpp"

namespace Logistics {
template <typename T>
T GetValidatedInput(std::string inputMessage,
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
          << std::type_info(typeid(T)).name() << '\n';
    } else if (rules.size() > 0) {
      bool isValid = true;
      for (auto rule : rules) {
        isValid = rule.m_condition(validatedInput);
        if (!isValid) {
          std::cout << rule.m_errorMsg << '\n';
          break;
        }
      }
      if (isValid) {
        return validatedInput;
      }
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

}  // namespace Logistics