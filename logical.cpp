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
}  // namespace Simulation