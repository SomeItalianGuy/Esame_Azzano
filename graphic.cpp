#include "graphic.hpp"

namespace Graphic {

std::string ColorText(const std::string& text, const std::string& color) {
  return color + text + "\033[0m";
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
         std::string(" individuals you would like: ");
}

}  // namespace Graphic