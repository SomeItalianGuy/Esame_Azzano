#include <iostream>
#include <limits>
#include <random>
#include <sstream>

#include "individual.hpp"
#include "population.hpp"
#include "rnghelper.hpp"

int main() {
  try {
  int passiveNumber = -1;
  int aggressiveNumber = -1;
  int adaptableNumber = -1;
  std::string userStringInput;

  std::cout << '\n' << '\n';

  std::cout
      << "Welcome to behavioral evolution,\n"
      << "in this simulation we recognize three types of behaviors:\n"
      << '\n'

      << "-Passive :    tries to divide food equally with its bretheren;\n"
      << '\n'

      << "-Aggressive : will try to steal most of the food it finds "
         "but gets exhasted when it has to compete;\n"
      << '\n'

      << "-Adaptable :  it will give most of the food if it encounters "
         "a Passive individual,\n"
      << "              but will not tolerate Aggressive individuals.\n"
      << '\n'

      << "-------------------------------------------------------------"
         "-------------------------------------------------------------"
         "---------------------------------\n"
      << '\n'

      << "Now, to get started, we will ask you to insert some "
         "parameters for your personal simulation.\n"

      << "Please input a seed, it can be a character, a word, a "
         "sentence or a number: ";
  std::cout << '\n';
  std::cin >> userStringInput;
  std::shared_ptr<RNGHelper> RNG = RNGHelper::instance(userStringInput);
  std::cout << '\n';

  while (passiveNumber < 0) {
    std::cout
        << "Please input the number of Passive individuals you would like: ";
    bool is_failing = !(std::cin >> passiveNumber);
    if (passiveNumber < 0) {
      std::cout << '\n';
      std::cout << "The number of Passive individuals must be higher than 0!\n";
    }
    if (is_failing) {
      std::cout << '\n';
      passiveNumber = -1;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "The number of Passive individuals must be a number "
                   "higher than 0!\n";
    }
  }
  std::cout << '\n';
  while (aggressiveNumber < 0) {
    std::cout << "Please input the number of Aggressive individuals "
                 "you would like: ";
    bool is_failing = !(std::cin >> aggressiveNumber);
    if (aggressiveNumber < 0) {
      std::cout << '\n';
      std::cout << "The number of Aggressive individuals must "
                   "be higher than 0!\n";
    }
    if (is_failing) {
      std::cout << '\n';
      std::cout << "The number of Aggressive individuals must "
                   "be a number "
                   "higher than 0!\n";
      aggressiveNumber = -1;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::cout << '\n';
  while (adaptableNumber < 0) {
    std::cout << "Please input the number of Adaptable individuals "
                 "indviduals you would like: ";
    bool is_failing = !(std::cin >> adaptableNumber);
    if (adaptableNumber < 0) {
      std::cout << '\n';
      std::cout << "The number of Adaptable individuals must "
                   "be higher than 0!\n";
    }
    if (is_failing) {
      std::cout << '\n';
      std::cout << "The number of Adaptable individuals must "
                   "be a number "
                   "higher than 0!\n";
      adaptableNumber = -1;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::shared_ptr<Population> population = Population::Population_instance(
      RNG->GetRandomDouble(3.5, 4.),
      passiveNumber + aggressiveNumber + adaptableNumber,
      RNG->GetRandomDouble(0., 1.));

  for (int i = 0; i < passiveNumber; ++i) {
    population->Generate_individual(Behavior::Passive);
  }
  for (int i = 0; i < aggressiveNumber; ++i) {
    population->Generate_individual(Behavior::Aggressive);
  }
  for (int i = 0; i < adaptableNumber; ++i) {
    population->Generate_individual(Behavior::Adaptable);
  }

  std::vector<Place> availablePlaces;
  std::vector<int> availablePlacesIndex;
  std::vector<GenerationData> simulatioData;

  simulatioData.push_back(population->WriteTo_GenerationData());

    std::cout << '\n';
    std::cout << "Now we are set to go, here is a list of all the possible "
                 "commands:\n "
              << "-run [value]          : lets you run a number equal to value of generations, for each generation prints"
                 "the number of individuals for each behavior;\n"
              << "-q          : lets you quit the simulation.\n"
              << '\n';
    int userIntInput;

    std::cout << "What would you like to do?\n";
    std::cout << '\n';
    while (std::cin >> userStringInput) {
      if(std::cin.peek() == '\n') {
        userIntInput = 0;
      } else {
        std::cin >> userIntInput;
      }
    }
  } catch (std::range_error& error) {
    std::cout << error.what() << '\n';
  } catch (std::overflow_error& error) {
    std::cout << error.what() << '\n';
  } catch (...) {
    std::cout << "Unkown error has occured" << '\n';
  }
}