#include "graphic.hpp"

namespace Simulation {

namespace graphic {
template <class T>
std::string ColorText(std::string& text, T color) {
  return color + text + "\033[0m";
}
template <class T>
std::string ColoredConditionString(std::string& text, bool& condition,
                                   T firstColor, T secondColor) {
  return condition ? ColorText<T>(text, firstColor)
                   : ColorText<T>(text, secondColor)
}

void PrintSeparationLines() {
  std::cout << "-----------------------------------------------------"
               "--------"
               "-----------------------------------------------------"
               "--------"
               "---------------------------------\n";
}

void PrintStats(std::string& initialText, double percentage, int integer,
                std::string& lastText) {
  std::cout << initialText << std::fixed << std::setprecision(2) << percentage
            << "%  " << integer << "  (" << lastText << ')\n';
  std::cout << '\n';
}
}  // namespace graphic
}  // namespace Simulation