#include "graphic.hpp"

namespace Graphic {

std::string ColorText(const std::string& text, const std::string& color) {
  return color + text + "\033[0m";
}
template <int N>
std::string ColoredConditionString(const std::string& text,
                                   std::array<bool, N> conditions,
                                   std::array<std::string, N> colors) {
  for (int i = 0; i < N; i++) {
    if (conditions[i]) {
      return ColorText(text, colors[i]);
    }
  }
}

void PrintSeparationLines() {
  std::cout << "-----------------------------------------------------"
               "--------"
               "-----------------------------------------------------"
               "--------"
               "---------------------------------\n";
}

void PrintStats(const std::string& initialText, double percentage, int integer,
                const std::string& lastText) {
  std::cout << initialText << std::fixed << std::setprecision(2) << percentage
            << "%  " << integer << "  (" << lastText << ")\n";
  std::cout << '\n';
}
std::string AskForPopulationInput(const std::string& textToColor,
                                  const std::string& color) {
  return std::string("Please input the number of ") +
         ColorText(textToColor, color) +
         std::string("individuals you would like: ");
}

}  // namespace Graphic