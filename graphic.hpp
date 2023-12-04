#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <iomanip>
#include <iostream>
#include <string>

namespace Simulation {

namespace graphic {
template <class T>
std::string ColorText(std::string& text, T Color);
template <class T>
std::string ColoredConditionString(std::string& text, bool& condition,
                                   T firstColor, T secondColor);
void PrintSeparationLines();
void PrintStats(std::string& initialText, double percentage, int integer,
                std::string& lastText);
}  // namespace graphic
}  // namespace Simulation

#endif