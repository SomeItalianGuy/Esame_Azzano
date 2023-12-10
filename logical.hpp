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
                    std::vector<ValidationRule<T>> rules);

template <typename T>
void InitializeVectorAndIndex(std::vector<T>& vector, std::vector<int>& indexes,
                              int nSamples);

};  // namespace Logic

#endif