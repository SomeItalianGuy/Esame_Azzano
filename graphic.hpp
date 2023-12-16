#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#define RED_TEXT std::string("\033[1;31m")
#define GREEN_TEXT std::string("\033[1;32m")
#define BLUE_TEXT std::string("\033[1;34m")
#define YELLOW_TEXT std::string("\033[1;33m")
#define MAGENTA_TEXT std::string("\033[1;35m")

#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace Graphic {
std::string ColorText(const std::string& text, const std::string& color);

void PrintSeparationLines();
void PrintStats(const std::string& initialText, double percentage, int integer,
                const std::string& lastText);

std::string AskForPopulationInput(const std::string& textToColor,
                                  const std::string& color);
std::string IntToString(int number);

}  // namespace Graphic

#endif