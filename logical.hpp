#ifndef LOGICAL_HPP
#define LOGICAL_HPP

#include <functional>
#include <iostream>
#include <limits>
#include <typeinfo>

template <typename T>
struct ValidationRule {
  std::function<bool(T)> m_condition;
  std::string m_errorMsg;
};

namespace Logic {

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

// bool StringEndsWith(std::string str, std::string endChars);
};  // namespace Logic

#endif